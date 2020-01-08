#include "amf_n2.hpp"
#include "logger.hpp"
#include "sctp_server.hpp"
#include "itti.hpp"

using namespace amf;
extern itti_mw * itti_inst;
extern amf_n2  * amf_n2_inst;
  
  void amf_n2_task(void*);
  void amf_n2_task(void *args_p){
    const task_id_t task_id = TASK_AMF_N2;
    itti_inst->notify_task_ready(task_id);
    do{
      std::shared_ptr<itti_msg> shared_msg = itti_inst->receive_msg(task_id);
      auto *msg = shared_msg.get();
      switch(msg->msg_type){
        case NEW_SCTP_ASSOCIATION:{
          Logger::task_amf_n2().info("Received NEW_SCTP_ASSOCIATION");
          itti_new_sctp_association *m = dynamic_cast<itti_new_sctp_association*>(msg);
          amf_n2_inst->handle_itti_message(ref(*m));
        }
        break;
        case NG_SETUP_REQ:{
          Logger::task_amf_n2().info("Received NGSetupRequest message, handling");
          itti_ng_setup_request *m = dynamic_cast<itti_ng_setup_request*>(msg);
          amf_n2_inst->handle_itti_message(ref(*m));
        }
        break;
        default:
          Logger::task_amf_n2().info( "no handler for msg type %d", msg->msg_type);
      }
    }while(true);
  }

  amf_n2::amf_n2(const string &address, const uint16_t port_num) : ngap_app(address, port_num){
    if (itti_inst->create_task(TASK_AMF_N2, amf_n2_task, nullptr) ) {
      Logger::amf_n2().error( "Cannot create task TASK_AMF_N2" );
      throw std::runtime_error( "Cannot create task TASK_AMF_N2" );
    }
    Logger::task_amf_n2().startup( "Started" );
    Logger::task_amf_n2().debug("construct amf_n2 successfully");
  }
  amf_n2::~amf_n2(){}
/*
  void amf_n2::handle_receive(bstring payload, sctp_assoc_id_t assoc_id, sctp_stream_id_t stream, sctp_stream_id_t instreams, sctp_stream_id_t outstreams){
    Logger::amf_n2().debug("ngap handle sctp payload from sctp_server on assoc_id(%d), stream_id(%d), instreams(%d), outstreams(%d)", assoc_id,stream,instreams,outstreams);
    Logger::amf_n2().debug("receiving buffer(%p)",bdata(payload));
    printf("\nbuffer        0x");
    for(int i=0; i< payload->slen; i++){
      if(!payload->data[i])
        printf("00");
      else
        printf("%x",payload->data[i]);
    }
    printf("\n\n");
    int ret = sctp_s_38412.sctp_send_msg(assoc_id, stream, &payload);
    Logger::amf_n2().debug("sctp_s_38412.sctp_send_msg test with sending result(%d): 0 is OK, else not OK", ret);
  }
*/




/******************************************************** NGAP Messages Handlers******************************************************************/

void amf_n2::handle_itti_message(itti_new_sctp_association &new_assoc){    
}
void amf_n2::handle_itti_message(itti_ng_setup_request &ngsetupreq){
  Logger::amf_n2().debug("parameters(assoc_id(%d))(stream(%d))",ngsetupreq.assoc_id, ngsetupreq.stream);
  //association GlobalRANNodeID with assoc_id
  //store RAN Node Name in gNB context, if present
  //verify PLMN Identity and TAC with configuration and store supportedTAList in gNB context, if verified; else response NG SETUP FAILURE with cause "Unknown PLMN"(9.3.1.2, ts38413)
  //store Paging DRX in gNB context
  //encode NG SETUP RESPONSE message with information stored in configuration file and send_msg
}
//void amf_n2::handle_itti_message(itti_initial_ue_message &init_ue_msg){
  //create ngap-ue context and store in gNB context to store UE information in gNB, for example, here RAN UE NGAP ID and location information and RRC Establishment Cause
  //send NAS-PDU to NAS layer
//}



