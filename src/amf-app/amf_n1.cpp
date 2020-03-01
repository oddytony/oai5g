#include "amf_n1.hpp"
#include "itti.hpp"
#include "logger.hpp"
#include "RegistrationRequest.hpp"
#include "RegistrationReject.hpp"
#include "AuthenticationRequest.hpp"
#include "AuthenticationResponse.hpp"
#include "SecurityModeCommand.hpp"
#include "itti_msg_n2.hpp"
#include "amf_config.hpp"
#include "String2Value.hpp"
#include "sha256.hpp"
#include "nas_algorithms.hpp"
using namespace nas;
using namespace amf;
using namespace std;
using namespace config;

extern itti_mw * itti_inst;
extern amf_n1  * amf_n1_inst;
extern amf_config amf_cfg;

random_state_t                          random_state;
static uint8_t                          no_random_delta = 0;

void amf_n1_task(void*);
void amf_n1_task(void*){
  const task_id_t task_id = TASK_AMF_N1;
  itti_inst->notify_task_ready(task_id);
  do{
    std::shared_ptr<itti_msg> shared_msg = itti_inst->receive_msg(task_id);
    auto *msg = shared_msg.get();
    switch(msg->msg_type){
      case UL_NAS_DATA_IND:{//receive nas message buffer from amf_n2
        Logger::task_amf_n1().info("Received UL_NAS_DATA_IND");
        itti_uplink_nas_data_ind *m = dynamic_cast<itti_uplink_nas_data_ind*>(msg);
        amf_n1_inst->handle_itti_message(ref(*m));
      }break;
      default:
        Logger::task_amf_n1().error("no handler for msg type %d",msg->msg_type);
    }
  }while(true);
}



amf_n1::amf_n1(){
  if(itti_inst->create_task(TASK_AMF_N1, amf_n1_task, nullptr) ) {
    Logger::amf_n1().error( "Cannot create task TASK_AMF_N1" );
    throw std::runtime_error( "Cannot create task TASK_AMF_N1" );
  }
  Logger::task_amf_n1().startup( "Started" );
  Logger::task_amf_n1().debug("construct amf_n1 successfully");
}
amf_n1::~amf_n1(){}


/**************************************************** itti msg handlers *****************************************************/
void amf_n1::handle_itti_message(itti_uplink_nas_data_ind & nas_data_ind){
  long amf_ue_ngap_id = nas_data_ind.amf_ue_ngap_id;
  uint32_t ran_ue_ngap_id = nas_data_ind.ran_ue_ngap_id;
  bstring recved_nas_msg = nas_data_ind.nas_msg;
  bstring decoded_plain_msg;
  std::shared_ptr<nas_context> nc;
  if(is_amf_ue_id_2_nas_context(amf_ue_ngap_id))
    nc = amf_ue_id_2_nas_context(amf_ue_ngap_id);
  else{
    Logger::amf_n1().error("No existed nas_context with amf_ue_ngap_id(0x%x)", amf_ue_ngap_id);
    response_registration_reject_msg(_5GMM_CAUSE_ILLEGAL_UE, ran_ue_ngap_id, amf_ue_ngap_id);//cause??
  }
  SecurityHeaderType type;
  if(!check_security_header_type(type, (uint8_t*)bdata(recved_nas_msg))){
    Logger::amf_n1().error("not 5GS MOBILITY MANAGEMENT message");
    return;
  }
  switch(type){
    case PlainNasMsg:{
      decoded_plain_msg = recved_nas_msg;
    }break;
    case IntegrityProtected:{
    }break;
    case IntegrityProtectedAndCiphered:{
    }break;
    case IntegrityProtectedWithNew5GNASSecurityContext:{
    }break;
    case IntegrityProtectedAndCipheredWithNew5GNASSecurityContext:{ 
      uint32_t mac32 = 0;
      if(!nas_message_integrity_protected(nc.get()->security_ctx, NAS_MESSAGE_UPLINK, (uint8_t*)bdata(recved_nas_msg), blength(recved_nas_msg), mac32)){
      //IA0_5G
      }else{
        bool isMatched = false;
        if(!memcmp(&mac32, bdata(recved_nas_msg), 4)){
          isMatched = true;
        }
        if(!isMatched){
          Logger::amf_n1().error("received message not integrity matched");
          return;
        }else{
          if(!nas_message_cipher_protected(nc.get()->security_ctx, NAS_MESSAGE_DOWNLINK, recved_nas_msg, decoded_plain_msg)){
            Logger::amf_n1().error("decrypt nas message failure");
            return;
          } 
        }
      }
    }break;
  }
  if(nas_data_ind.is_nas_signalling_estab_req){
    Logger::amf_n1().debug("recv nas signalling establishment request ...");
    nas_signalling_establishment_request_handle(nas_data_ind.ran_ue_ngap_id, nas_data_ind.amf_ue_ngap_id, decoded_plain_msg);
    //change UE connection status CM-IDLE -> CM-CONNECTED
  }else{
    Logger::amf_n1().debug("recv uplink nas message ...");
    uplink_nas_msg_handle(nas_data_ind.ran_ue_ngap_id, nas_data_ind.amf_ue_ngap_id, decoded_plain_msg);
  }
}

/***************************************************** handlers for lower layer *************************/
void amf_n1::nas_signalling_establishment_request_handle(uint32_t ran_ue_ngap_id, long amf_ue_ngap_id, bstring plain_msg){
  uint8_t * buf = (uint8_t*)bdata(plain_msg);
  uint8_t message_type = *(buf+2);
  switch(message_type){
    case 0x7e:{//registration request
      registration_request_handle(true, ran_ue_ngap_id, amf_ue_ngap_id, plain_msg);
    }break;
  }
}

void amf_n1::uplink_nas_msg_handle(uint32_t ran_ue_ngap_id, long amf_ue_ngap_id, bstring plain_msg){
  uint8_t * buf = (uint8_t*)bdata(plain_msg);
  uint8_t message_type = *(buf+2);
  switch(message_type){
    case REGISTRATION_REQUEST:{//registration request
      registration_request_handle(false, ran_ue_ngap_id, amf_ue_ngap_id, plain_msg);
    }break;
    case AUTHENTICATION_RESPONSE:{
      authentication_response_handle(ran_ue_ngap_id, amf_ue_ngap_id, plain_msg);
    }break;
    case SECURITY_MODE_COMPLETE:{
      security_mode_complete_handle(ran_ue_ngap_id, amf_ue_ngap_id, plain_msg);
    }break;
  }

}

/***************************************************** nas message decode ****************************************************/

bool amf_n1::check_security_header_type(SecurityHeaderType & type, uint8_t *buffer){
  uint8_t octet = 0, decoded_size = 0;
  octet = *(buffer+decoded_size); decoded_size++;
  if(octet != 0x7e) return false;
  octet = *(buffer+decoded_size); decoded_size++;
  switch(octet&0x0f){
    case 0x0: type = PlainNasMsg; break;
    case 0x1: type = IntegrityProtected; break;
    case 0x2: type = IntegrityProtectedAndCiphered; break;
    case 0x3: type = IntegrityProtectedWithNew5GNASSecurityContext; break;
    case 0x4: type = IntegrityProtectedAndCipheredWithNew5GNASSecurityContext; break;
  }
  return true;
}

/************************************************* nas message handlers *****************************************************/
void amf_n1::registration_request_handle(bool isNasSig, uint32_t ran_ue_ngap_id, long amf_ue_ngap_id, bstring reg){
  //1. decode registration request message from liuyu
  RegistrationRequest *regReq = new RegistrationRequest();
  regReq->decodefrombuffer(nullptr, (uint8_t*)bdata(reg), blength(reg));
  //3. create nas context
  std::shared_ptr<nas_context> nc;
  if(!is_amf_ue_id_2_nas_context(amf_ue_ngap_id)){
    Logger::amf_n1().debug("no existing nas_context with amf_ue_ngap_id(0x%x) --> Create new one",amf_ue_ngap_id);
    nc = std::shared_ptr<nas_context>(new nas_context);
    set_amf_ue_ngap_id_2_nas_context(amf_ue_ngap_id, nc);
  }else{
    Logger::amf_n1().debug("existing nas_context with amf_ue_ngap_id(0x%x) --> Update",amf_ue_ngap_id);
    nc = amf_ue_id_2_nas_context(amf_ue_ngap_id); 
  }
  if(nc.get() == nullptr){
    response_registration_reject_msg(_5GMM_CAUSE_ILLEGAL_UE, ran_ue_ngap_id, amf_ue_ngap_id);
    return;
  }
  nc.get()->ctx_avaliability_ind = false;
  //2. analysis the message IEs(encode RegistrationReject, if possible)
  //2.2 check ie 5GS_Registration_type(Mandontary IE)
  uint8_t reg_type; bool is_follow_on_req_pending;
  if(regReq->get5GSRegistrationType(is_follow_on_req_pending, reg_type)){
    Logger::amf_n1().error("MIssing Mandontary IE 5GS Registration type ...");
    response_registration_reject_msg(_5GMM_CAUSE_INVALID_MANDATORY_INFO, ran_ue_ngap_id, amf_ue_ngap_id);
    return; 
  }
  nc.get()->registration_type = reg_type;
  nc.get()->follow_on_req_pending_ind = is_follow_on_req_pending;

  //2.3 check ie ngKSI(Mondantary IE) 
  uint8_t ngKSI = regReq->getngKSI();
  if(ngKSI == -1){
    Logger::amf_n1().error("MIssing Mandontary IE ngKSI ...");
    response_registration_reject_msg(_5GMM_CAUSE_INVALID_MANDATORY_INFO, ran_ue_ngap_id, amf_ue_ngap_id);
    return; 
  }
  nc.get()->ngKsi = ngKSI;

  //2.4 check ie 5gs mobility identity(Mondantary IE)
  uint8_t mobility_id_type = regReq->getMobilityIdentityType();
  switch(mobility_id_type){
    case SUCI:{
      nas::SUCI_imsi_t imsi;
      if(!regReq->getSuciSupiFormatImsi(imsi)){
        Logger::amf_n1().warn("No SUCI and IMSI for SUPI Format");
      }else{
        //nc.get()->imsi = //need interface to transfer SUCI_imsi_t to string
      }
    }break;
  }
  //2.4.1 try to get supi and format imsi
  //2.4.2 try to get 5g-guti
  //2.4.3 try to get ...
  //2.5 try to get ie non-current native nas key set identity(Optional IE), used for inter-system change from S1 to N1
  //2.6 try to get ie 5GMM Capability(Optional IE), not included for periodic registration updating procedure
  uint8_t _5g_mm_cap = regReq->get5GMMCapability();
  if(_5g_mm_cap == -1){
    Logger::amf_n1().warn("No Optional IE 5GMMCapability avaliable");
  }
  nc.get()->mmCapability = _5g_mm_cap;
  //2.7 try to get ie Ue Security capability(Optional IE),  not included for periodic registration updating procedure
  uint8_t encrypt_alg, integrity_alg;
  if(!regReq->getUeSecurityCapability(encrypt_alg, integrity_alg)){
    Logger::amf_n1().warn("No Optional IE UESecurityCapability avaliable");
  }
  nc.get()->ueSecurityCapEnc = encrypt_alg;
  nc.get()->ueSecurityCapInt = integrity_alg;
  //2.8 try to get ie Requested NSSAI(Optional IE), if provided
  std::vector<nas::SNSSAI_t> requestedNssai;
  if(!regReq->getRequestedNssai(requestedNssai)){
    Logger::amf_n1().warn("No Optional IE RequestedNssai avaliable");
  }
  nc.get()->requestedNssai = requestedNssai;
  //2.9 try to get ie Last visited registred TAI(OPtional IE), if provided
  //2.10 try to get ie S1 Ue network capability(OPtional IE), if ue supports S1 mode
  //2.11 try to get ie uplink data status(Optional IE), if UE has uplink user data to be sent
  //2.11 try to get ie pdu session status(OPtional IE), associated and active pdu sessions avaliable in UE
  //4. store nas informstion into nas_context
  //5. run different registration procedure
  switch(reg_type){
    case INITIAL_REGISTRATION:{
      run_initial_registration_procedure();//IEs?
    }break;
    case MOBILITY_REGISTRATION_UPDATING:{
      Logger::amf_n1().error("The network doesn't support mobility registration, reject ...");
    }break;
    case PERIODIC_REGISTRATION_UPDATING:{
      Logger::amf_n1().error("The network doesn't support periodic registration, reject ...");
    }break;
    case EMERGENCY_REGISTRATION:{
      if(!amf_cfg.is_emergency_support.compare("false")){
        Logger::amf_n1().error("The network doesn't support emergency registration, reject ...");
        response_registration_reject_msg(_5GMM_CAUSE_ILLEGAL_UE, ran_ue_ngap_id, amf_ue_ngap_id);//cause?
        return; 
      }
    }break;
  }
  //5. run specific procedure for registration
  nc.get()->ctx_avaliability_ind = true;
  run_registration_procedure(nc);
  //generation authentication vector, refer to openair-cn/tree/v0.5.0 (_emm_attach_identify())
  //if(!generate_authentication_vector()){}
  //encode AUTHENTICATION REQUEST message from liuyu
  //send itti msg to TASK_AMF_N2 with ID(DL_NAS_TRANSPORT)
}

/************************************************* authentication vector handlers ******************************************/
bool amf_n1::generate_authentication_vector(){}

/************************************************* context management functions *********************************/

bool amf_n1::is_amf_ue_id_2_nas_context(const long & amf_ue_ngap_id) const {
  std::shared_lock lock(m_amfueid2nas_context);
  return bool{amfueid2nas_context.count(amf_ue_ngap_id) > 0};
}

std::shared_ptr<nas_context> amf_n1::amf_ue_id_2_nas_context(const long & amf_ue_ngap_id) const {
  std::shared_lock lock(m_amfueid2nas_context);
  return amfueid2nas_context.at(amf_ue_ngap_id);
}

void amf_n1::set_amf_ue_ngap_id_2_nas_context(const long & amf_ue_ngap_id, std::shared_ptr<nas_context> nc){
  std::shared_lock lock(m_amfueid2nas_context);
  amfueid2nas_context[amf_ue_ngap_id] = nc;
}



/************************************************** to lower layer TASK_N2 *******************************************/
void amf_n1::itti_send_dl_nas_buffer_to_task_n2(bstring & b, uint32_t ran_ue_ngap_id, long amf_ue_ngap_id){
  itti_dl_nas_transport *msg = new itti_dl_nas_transport(TASK_AMF_N1, TASK_AMF_N2);
  msg->ran_ue_ngap_id = ran_ue_ngap_id;
  msg->amf_ue_ngap_id = amf_ue_ngap_id;
  msg->nas            = b;
  std::shared_ptr<itti_dl_nas_transport> i = std::shared_ptr<itti_dl_nas_transport>(msg);
  int ret = itti_inst->send_msg(i);
  if (0 != ret) {
    Logger::amf_n1().error( "Could not send ITTI message %s to task TASK_AMF_N2", i->get_msg_name());
  }
}

/*************************************************** response messages ***********************************************/
void amf_n1::response_registration_reject_msg(uint8_t cause_value, uint32_t ran_ue_ngap_id, long amf_ue_ngap_id){
  RegistrationReject *registrationRej = new RegistrationReject();
  registrationRej->setHeader(PLAIN_5GS_MSG);
  registrationRej->set_5GMM_Cause(cause_value);
  uint8_t buffer[1024] = {0};
  int encoded_size = registrationRej->encode2buffer(buffer, 1024);
  if(!encoded_size){
    Logger::nas_mm().error("encode RegistrationRej message error");
    return;
  }else{
    delete registrationRej;
  }
  bstring b = blk2bstr(buffer, encoded_size);
  itti_send_dl_nas_buffer_to_task_n2(b, ran_ue_ngap_id, amf_ue_ngap_id); 
}

/*************************************************** specific procedures running logic **********************************/
void amf_n1::run_registration_procedure(std::shared_ptr<nas_context> &nc){
  if(!nc.get()->ctx_avaliability_ind){
    Logger::amf_n1().error("nas context is not avaliable");
    return;
  }
  nc.get()->is_specific_procedure_for_registration_running = true;
  if(nc.get()->is_imsi_present){
    if(!nc.get()->is_auth_vectors_present){
      if(auth_vectors_generator(nc)){// all authentication in one(AMF)
        handle_auth_vector_successful_result(nc);
      }else{
        Logger::amf_n1().error("request authentication vectors failure");
        response_registration_reject_msg(_5GMM_CAUSE_ILLEGAL_UE, nc.get()->ran_ue_ngap_id, nc.get()->amf_ue_ngap_id);//cause?      
      }
    }else{
      ngksi_t ngksi = 0;
      if(nc.get()->security_ctx && nc.get()->security_ctx->ngksi != NAS_KEY_SET_IDENTIFIER_NOT_AVAILABLE){
        ngksi = (nc.get()->security_ctx->ngksi + 1) % (NGKSI_MAX_VALUE + 1);
        // ... how to handle?
      }
    }
  }else if(nc.get()->is_5g_guti_present){
    nc.get()->is_auth_vectors_present = false;
    // ... identification procedure
  }
}

/************************************************** authentication vectors **********************************************/
bool amf_n1::auth_vectors_generator(std::shared_ptr<nas_context>&nc){
  authentication_vectors_generator_in_udm(nc);
  authentication_vectors_generator_in_ausf(nc);
  for(int i =0; i< MAX_5GS_AUTH_VECTORS; i++){
    Authentication_5gaka::derive_kamf(nc.get()->imsi, nc.get()->_5g_av[i].kseaf, nc.get()->kamf[i], 0x0000);//second parameter: abba
  }
  return true;
}

bool amf_n1::authentication_vectors_generator_in_ausf(std::shared_ptr<nas_context>&nc){// A.5, 3gpp ts33.501
  uint8_t inputString[MAX_5GS_AUTH_VECTORS][24];
  uint8_t *xres[MAX_5GS_AUTH_VECTORS];
  uint8_t *rand[MAX_5GS_AUTH_VECTORS];
  for(int i=0; i<MAX_5GS_AUTH_VECTORS; i++){
    xres[i] = nc.get()->_5g_he_av[i].xres;
    rand[i] = nc.get()->_5g_he_av[i].rand;
    memcpy(&inputString[i][0], rand[i], 16);
    memcpy(&inputString[i][16], xres[i], 8);
    std::string input = (char*)inputString[i];
    std::string output = sha256(input);
    memcpy(nc.get()->_5g_av[i].hxres, (uint8_t*)output.c_str(), output.length());
    memcpy(nc.get()->_5g_av[i].rand, nc.get()->_5g_he_av[i].rand, 16);
    memcpy(nc.get()->_5g_av[i].autn, nc.get()->_5g_he_av[i].autn, 16);
    uint8_t kseaf[32];
    Authentication_5gaka::derive_kseaf(nc.get()->serving_network, nc.get()->_5g_he_av[i].kausf, kseaf);
    memcpy(nc.get()->_5g_av[i].kseaf, kseaf, 32);
  }
  return true;
}
bool amf_n1::authentication_vectors_generator_in_udm(std::shared_ptr<nas_context>&nc){
  uint8_t *sqn = NULL, *auts = nc.get()->auts;
  _5G_HE_AV_t *vector = nc.get()->_5g_he_av;
  //1. access to local mysql to fetch ue-related information
  if(!connect_to_mysql()){
    Logger::amf_n1().error("Cannot connect to mysql");
    return false;
  }
  mysql_auth_info_t mysql_resp;
  if(get_mysql_auth_info(nc.get()->imsi, mysql_resp)){
    if(auts){
      sqn = Authentication_5gaka::sqn_ms_derive(mysql_resp.opc, mysql_resp.key, auts, mysql_resp.rand);
      if(sqn){
        generate_random (vector[0].rand, RAND_LENGTH);
        mysql_push_rand_sqn (nc.get()->imsi, vector[0].rand, sqn);
        mysql_increment_sqn (nc.get()->imsi);
        free (sqn);
      }
      if(!get_mysql_auth_info(nc.get()->imsi, mysql_resp)){
        Logger::amf_n1().error("Cannot get data from mysql");
        return false;
      }
      sqn = mysql_resp.sqn;
      for(int i=0; i< MAX_5GS_AUTH_VECTORS; i++){
        generate_random(vector[i].rand, RAND_LENGTH);
        generate_5g_he_av_in_udm(mysql_resp.opc, nc.get()->imsi, mysql_resp.key, sqn, nc.get()->serving_network, vector[i]);//serving network name
      }
      mysql_push_rand_sqn (nc.get()->imsi, vector[MAX_5GS_AUTH_VECTORS - 1].rand, sqn);
    }else{
      for(int i=0; i< MAX_5GS_AUTH_VECTORS; i++){
        generate_random (vector[i].rand, RAND_LENGTH);
        sqn = mysql_resp.sqn;
        generate_5g_he_av_in_udm(mysql_resp.opc, nc.get()->imsi, mysql_resp.key, sqn, nc.get()->serving_network, vector[i]);//serving network name
      }
      mysql_push_rand_sqn (nc.get()->imsi, vector[MAX_5GS_AUTH_VECTORS - 1].rand, sqn);
    }
    mysql_increment_sqn (nc.get()->imsi);
  }else{
    Logger::amf_n1().error("Failed to fetch user data from mysql");
    return false;
  }
}

void amf_n1::generate_random(uint8_t *random_p, ssize_t length){
  if(!amf_cfg.auth_para.random.compare("true")){
    random_t random_nb;
    mpz_init_set_ui(random_nb, 0);
    pthread_mutex_lock(&random_state.lock);
    mpz_urandomb(random_nb, random_state.state, 8 * length);
    pthread_mutex_unlock(&random_state.lock);
    mpz_export(random_p, NULL, 1, length, 0, 0, random_nb);
    int   r = 0,  mask = 0, shift;
    for (int i = 0; i < length; i++) {
      if ((i % sizeof(i)) == 0)
        r = rand();
      shift = 8 * (i % sizeof(i));
      mask = 0xFF << shift;
      random_p[i] = (r & mask) >> shift;
    }
  }else{
    pthread_mutex_lock(&random_state.lock);
    for (int i = 0; i < length; i++) {
      random_p[i] = i + no_random_delta;
    }
    no_random_delta += 1;
    pthread_mutex_unlock(&random_state.lock);
  }
}
 void amf_n1::generate_5g_he_av_in_udm(const uint8_t opc[16], string imsi, uint8_t key[16], uint8_t sqn[6], std::string serving_network, _5G_HE_AV_t &vector){
  uint8_t                                 amf[] = { 0x80, 0x00 };
  uint8_t                                 mac_a[8];
  uint8_t                                 ck[16];
  uint8_t                                 ik[16];
  uint8_t                                 ak[6];
  uint64_t _imsi = fromString<uint64_t>(imsi); 
  Authentication_5gaka::f1(opc, key, vector.rand, sqn, amf, mac_a);// to compute MAC, Figure 7, ts33.102 
  Authentication_5gaka::f2345(opc, key, vector.rand, vector.xres, ck, ik, ak);// to compute XRES, CK, IK, AK
  Authentication_5gaka::generate_autn(sqn, ak, amf, mac_a, vector.autn);// generate AUTN
  Authentication_5gaka::derive_kausf(ck, ik, serving_network, sqn, ak, vector.kausf);//derive Kausf
  return;
}

void amf_n1::handle_auth_vector_successful_result(std::shared_ptr<nas_context> nc){
  Logger::amf_n1().debug("Received security vectors from AUSF/UDM, try to setup security with the UE");
  nc.get()->is_auth_vectors_present = true; 
  ngksi_t ngksi = 0;
  nc.get()->security_ctx = new nas_secu_ctx();
  if(nc.get()->security_ctx && nc.get()->security_ctx->ngksi != NAS_KEY_SET_IDENTIFIER_NOT_AVAILABLE)
    ngksi = (nc.get()->security_ctx->ngksi + 1) % (NGKSI_MAX_VALUE + 1);
  // ensure which vector is avaliable?
  int vindex = nc.get()->security_ctx->vector_pointer;
  if(!start_authentication_procedure(nc, vindex, ngksi)){
    Logger::amf_n1().error("start authentication procedure failure, reject...");
    response_registration_reject_msg(_5GMM_CAUSE_INVALID_MANDATORY_INFO, nc.get()->ran_ue_ngap_id, nc.get()->amf_ue_ngap_id); //cause? 
  }else{
    //update mm state -> COMMON-PROCEDURE-INITIATED
  }
}

bool amf_n1::start_authentication_procedure(std::shared_ptr<nas_context> nc, int vindex, uint8_t ngksi){
  Logger::amf_n1().debug("Starting authentication procedure ...");
  if(check_nas_common_procedure_on_going(nc)){
    Logger::amf_n1().error("existed nas common procedure on going, reject...");
    response_registration_reject_msg(_5GMM_CAUSE_INVALID_MANDATORY_INFO, nc.get()->ran_ue_ngap_id, nc.get()->amf_ue_ngap_id); //cause? 
    return false;
  }
  nc.get()->is_common_procedure_for_authentication_running = true;
  AuthenticationRequest * authReq = new AuthenticationRequest();
  authReq->setHeader(PLAIN_5GS_MSG);
  authReq->setngKSI(NAS_KEY_SET_IDENTIFIER_NATIVE, ngksi);
  uint8_t abba[2];
  abba[0] = 0x00;
  abba[1] = 0x00;
  authReq->setABBA(2, abba);
  uint8_t *rand = nc.get()->_5g_av[vindex].rand;
  if(rand)
    authReq->setAuthentication_Parameter_RAND(rand);
  uint8_t *autn = nc.get()->_5g_av[vindex].autn;
  if(autn)
    authReq->setAuthentication_Parameter_AUTN(autn);
  uint8_t buffer[1024] = {0};
  int encoded_size = authReq->encode2buffer(buffer, 1024);
  if(!encoded_size){
    Logger::nas_mm().error("encode Authentication Request message error");
    return false;
  }else{
    delete authReq;
  }
  bstring b = blk2bstr(buffer, encoded_size);
  itti_send_dl_nas_buffer_to_task_n2(b, nc.get()->ran_ue_ngap_id, nc.get()->amf_ue_ngap_id);
  return true;
}

bool amf_n1::check_nas_common_procedure_on_going(std::shared_ptr<nas_context> nc){
  if(nc.get()->is_common_procedure_for_authentication_running){
    Logger::amf_n1().debug("existed authentication procedure is running");
    return true;
  }
  if(nc.get()->is_common_procedure_for_identification_running){
    Logger::amf_n1().debug("existed identification procedure is running");
    return true;
  }
  if(nc.get()->is_common_procedure_for_security_mode_control_running){
    Logger::amf_n1().debug("existed SMC procedure is running");
    return true;
  }
  if(nc.get()->is_common_procedure_for_nas_transport_running){
    Logger::amf_n1().debug("existed nas transport procedure is running");
    return true;
  }
  return false;
}

void amf_n1::authentication_response_handle(uint32_t ran_ue_ngap_id, long amf_ue_ngap_id, bstring plain_msg){
  std::shared_ptr<nas_context> nc;
  if(!is_amf_ue_id_2_nas_context(amf_ue_ngap_id)){
    Logger::amf_n1().error("No existed nas context for UE with amf_ue_ngap_id(0x%x)", amf_ue_ngap_id);
    response_registration_reject_msg(_5GMM_CAUSE_ILLEGAL_UE, ran_ue_ngap_id, amf_ue_ngap_id);//cause?   
    return;
  }
  nc = amf_ue_id_2_nas_context(amf_ue_ngap_id);
  //0. stop timer? common procedure finished!
  nc.get()->is_common_procedure_for_authentication_running = false;
  // MM state: COMMON-PROCEDURE-INITIATED -> DEREGISTRED
  //1. decode AUTHENTICATION RESPONSE message(interfaces are not implemented, 2020-02-24)
  AuthenticationResponse *auth = new AuthenticationResponse();
  auth->decodefrombuffer(nullptr, (uint8_t*)bdata(plain_msg), blength(plain_msg));
  bstring resStar; bool isAuthOk = false;
  //2. get response RES*
  if(!auth->getAuthenticationResponseParameter(resStar)){
    Logger::amf_n1().warn("don't receive AuthenticationResponseParameter(RES*)");
  }else{
  //3. get stored XRES*
    string hxresStar = (char*)nc.get()->_5g_av[0].hxres;
  //4. calculate HRES* from received RES*, then compare with XRES stored in nas_context
    Logger::amf_n1().debug("Start to calculate HRES* from received RES*");
    string input = (char*)bdata(resStar);
    string output = sha256(input);
    if(!output.compare(hxresStar)){
      Logger::amf_n1().debug("Correct!! calculated HRES*(%s) == stored HXRES(%s)", output.c_str(), hxresStar.c_str());
      isAuthOk = true;
    }
  }
  //5. if successful, start SMC procedure; else if failure, response registration reject message with corresponding cause
  if(!isAuthOk){
    Logger::amf_n1().error("Authentication Failure for UE with amf_ue_ngap_id(0x%x)", amf_ue_ngap_id);
    response_registration_reject_msg(_5GMM_CAUSE_ILLEGAL_UE, ran_ue_ngap_id, amf_ue_ngap_id);//cause?   
    return;
  }else{
    if(!nc.get()->is_current_security_avaliable){
      if(!start_security_mode_control_procedure(nc)){
        Logger::amf_n1().error("Start SMC procedure failure");
      }else{
      // ...
      }
    }
  }
}

bool amf_n1::start_security_mode_control_procedure(std::shared_ptr<nas_context>nc){
  Logger::amf_n1().debug("Start Security Mode Control procedure");
  nc.get()->is_common_procedure_for_security_mode_control_running = true;
  bool      security_context_is_new = false;
  uint8_t   amf_nea = EA0_5G;
  uint8_t   amf_nia = IA0_5G;
  //decide which ea/ia alg used by UE, which is supported by network
  security_data_t *data = (security_data_t*)calloc(1, sizeof(security_data_t));
  nas_secu_ctx * secu_ctx = nc.get()->security_ctx;
  if(!data)
    Logger::amf_n1().error("cannot calloc memory for security_data_t");
  if(secu_ctx->sc_type == SECURITY_CTX_TYPE_NOT_AVAILABLE && nc.get()->is_common_procedure_for_security_mode_control_running){
    Logger::amf_n1().debug("Using INTEGRITY_PROTECTED_WITH_NEW_SECU_CTX for SecurityModeControl message");
    data->saved_selected_nea = secu_ctx->nas_algs.encryption;//emm_ctx->_security.selected_algorithms.encryption;
    data->saved_selected_nia = secu_ctx->nas_algs.integrity;
    data->saved_ngksi        = secu_ctx->ngksi;
    data->saved_overflow     = secu_ctx->dl_count.overflow;//emm_ctx->_security.dl_count.overflow;
    data->saved_seq_num      = secu_ctx->dl_count.seq_num;
    data->saved_sc_type      = secu_ctx->sc_type;
    secu_ctx->ngksi = nc.get()->ngKsi;
    secu_ctx->dl_count.overflow = 0;
    secu_ctx->dl_count.seq_num = 0;
    int rc = security_select_algorithms(nc.get()->ueSecurityCapEnc, nc.get()->ueSecurityCapInt, amf_nea, amf_nia);
    secu_ctx->sc_type = SECURITY_CTX_TYPE_FULL_NATIVE;
    Authentication_5gaka::derive_knas(NAS_INT_ALG, secu_ctx->nas_algs.integrity, nc.get()->_5g_av[secu_ctx->vector_pointer].kseaf, secu_ctx->knas_int);
    Authentication_5gaka::derive_knas(NAS_ENC_ALG, secu_ctx->nas_algs.encryption, nc.get()->_5g_av[secu_ctx->vector_pointer].kseaf, secu_ctx->knas_enc);
    security_context_is_new = true;
    nc.get()->is_current_security_avaliable = true;
  }  
  SecurityModeCommand *smc = new SecurityModeCommand();
  smc->setHeader(INTEGRITY_PROTECTED_WITH_NEW_SECU_CTX);
  uint8_t buffer[1024];
  int encoded_size = smc->encode2buffer(buffer, 1024);
  bstring intProtctedNas;
  encode_nas_message_protected(nc.get()->security_ctx, security_context_is_new, INTEGRITY_PROTECTED_WITH_NEW_SECU_CTX, NAS_MESSAGE_DOWNLINK, buffer, encoded_size, intProtctedNas);
  itti_send_dl_nas_buffer_to_task_n2(intProtctedNas, nc.get()->ran_ue_ngap_id, nc.get()->amf_ue_ngap_id); 
}

int amf_n1::security_select_algorithms(uint8_t nea, uint8_t nia, uint8_t amf_nea, uint8_t amf_nia){
  for(int i=0; i< 8; i++){
    if(nea & (0x80 >> amf_cfg.nas_cfg.prefered_ciphering_algorithm[i])){
      amf_nea = amf_cfg.nas_cfg.prefered_ciphering_algorithm[i];
      break;
    }
  }
  for(int i=0; i< 8; i++){
    if(nia & (0x80 >> amf_cfg.nas_cfg.prefered_integrity_algorithm[i])){
      amf_nia = amf_cfg.nas_cfg.prefered_integrity_algorithm[i];
      break;
    }
  }
  return 0;
}

void amf_n1::security_mode_complete_handle(uint32_t ran_ue_ngap_id, long amf_ue_ngap_id, bstring nas_msg){
}

void amf_n1::encode_nas_message_protected(nas_secu_ctx * nsc, bool is_secu_ctx_new, uint8_t security_header_type, uint8_t direction, uint8_t *input_nas_buf, int input_nas_len, bstring & protected_nas){
  uint8_t protected_nas_buf[1024];
  int encoded_size = 0;
  switch(security_header_type & 0x0f){
    case INTEGRITY_PROTECTED:{
    }break;
    case INTEGRITY_PROTECTED_AND_CIPHERED:{
    }break;
    case INTEGRITY_PROTECTED_WITH_NEW_SECU_CTX:{
      if(!nsc || !is_secu_ctx_new){
        Logger::amf_n1().error("security context is too old");
      }
      uint32_t mac32;
      if(!(nas_message_integrity_protected(nsc, NAS_MESSAGE_DOWNLINK, input_nas_buf, input_nas_len, mac32))){
        memcpy(protected_nas_buf, input_nas_buf, input_nas_len);
        encoded_size = input_nas_len;
      }else{
        protected_nas_buf[0] = EPD_5GS_MM_MSG;
        protected_nas_buf[1] = INTEGRITY_PROTECTED_WITH_NEW_SECU_CTX;
        memcpy((uint32_t*)&protected_nas_buf[2], &mac32, 1);
        protected_nas_buf[7] = (uint8_t)nsc->dl_count.seq_num;
        memcpy(&protected_nas_buf[8], input_nas_buf, input_nas_len);
        encoded_size = 7 + input_nas_len;
      }
    }break;
    case INTEGRITY_PROTECTED_AND_CIPHERED_WITH_NEW_SECU_CTX:{
    }break;
  }
  protected_nas = blk2bstr(protected_nas_buf, encoded_size);
}
bool amf_n1::nas_message_integrity_protected(nas_secu_ctx *nsc, uint8_t direction, uint8_t *input_nas, int input_nas_len, uint32_t &mac32){
  uint32_t count = 0x00000000;
  if(direction)
    count = 0x00000000 | ((nsc->dl_count.overflow & 0x0000ffff)<<8) | ((nsc->dl_count.seq_num & 0x000000ff));
  else
    count = 0x00000000 | ((nsc->ul_count.overflow & 0x0000ffff)<<8) | ((nsc->ul_count.seq_num & 0x000000ff));
  nas_stream_cipher_t stream_cipher = {0};
  uint8_t mac[4];
  stream_cipher.key = nsc->knas_int;
  stream_cipher.key_length = AUTH_KNAS_INT_SIZE;
  stream_cipher.count = count;
  stream_cipher.bearer = 0x00;      //33.501 section 8.1.1
  stream_cipher.direction = direction;// "1" for downlink
  stream_cipher.message = (uint8_t*)input_nas;
  stream_cipher.blength = input_nas_len << 3;
  switch(nsc->nas_algs.integrity & 0x0f){
    case IA0_5G:{
      return false;//plain msg
    }break;
    case IA1_128_5G:{
      nas_algorithms::nas_stream_encrypt_nia1 (&stream_cipher, mac);
      mac32 = ntohl(*((uint32_t*) & mac));
      return true;
    }break;
    case IA2_128_5G:{
      nas_algorithms::nas_stream_encrypt_nia2 (&stream_cipher, mac);
      mac32 = ntohl(*((uint32_t*) & mac));
      return true;
    }break;
  }
}

bool amf_n1::nas_message_cipher_protected(nas_secu_ctx *nsc, uint8_t direction, bstring input_nas, bstring &output_nas){
  uint32_t count = 0x00000000;
  if(direction)
    count = 0x00000000 | ((nsc->dl_count.overflow & 0x0000ffff)<<8) | ((nsc->dl_count.seq_num & 0x000000ff));
  else
    count = 0x00000000 | ((nsc->ul_count.overflow & 0x0000ffff)<<8) | ((nsc->ul_count.seq_num & 0x000000ff));
  nas_stream_cipher_t stream_cipher = {0};
  uint8_t mac[4];
  stream_cipher.key = nsc->knas_enc;
  stream_cipher.key_length = AUTH_KNAS_ENC_SIZE;
  stream_cipher.count = count;
  stream_cipher.bearer = 0x00;      //33.501 section 8.1.1
  stream_cipher.direction = direction;// "1" for downlink
  stream_cipher.message = (uint8_t*)bdata(input_nas);
  stream_cipher.blength = blength(input_nas) << 3;
  switch(nsc->nas_algs.encryption & 0x0f){
    case EA0_5G:{
      return false;
    }break;
    case EA1_128_5G:{
      nas_algorithms::nas_stream_encrypt_nea1 (&stream_cipher, (uint8_t*)bdata(output_nas)); 
    }break;
    case EA2_128_5G:{
      nas_algorithms::nas_stream_encrypt_nea2 (&stream_cipher, (uint8_t*)bdata(output_nas)); 
    }break;
  }
}

void amf_n1::run_initial_registration_procedure(){
}
