#include "logger.hpp"
#include "sctp_server.hpp"
#include "itti_msg_n2.hpp"
#include "itti.hpp"
#include "NGSetupRequest.hpp"
//extern "C"{
//  #include "Ngap_NGAP-PDU.h"
//}


using namespace sctp;
using namespace ngap;

extern itti_mw * itti_inst;

typedef int (*ngap_message_decoded_callback)(
    const sctp_assoc_id_t             assoc_id,
    const sctp_stream_id_t            stream,
    struct Ngap_NGAP_PDU *message_p
);

int ngap_amf_handle_ng_setup_request(const sctp_assoc_id_t             assoc_id,  const sctp_stream_id_t            stream,  struct Ngap_NGAP_PDU *message_p){
  Logger::ngap().debug("sending itti ng setup request message to TASK_AMF_N2");
  //need code from yangjian and send itti message to TASK_AMF_N2
  asn_fprint(stderr, &asn_DEF_Ngap_NGAP_PDU, message_p);
  NGSetupRequestMsg *ngSetupReq = new NGSetupRequestMsg();
  if(!ngSetupReq->decodefrompdu(message_p)){
    Logger::ngap().error("decoding ngsetuprequest message error");
    return -1;
  }
  //after decoding, need free(message_p)
  itti_ng_setup_request * itti_msg = new itti_ng_setup_request(TASK_NGAP, TASK_AMF_N2);
  itti_msg->assoc_id = assoc_id;
  itti_msg->stream = stream;
  itti_msg->ngSetupReq = ngSetupReq; 
  std::shared_ptr<itti_ng_setup_request> i = std::shared_ptr<itti_ng_setup_request>(itti_msg);
  int ret = itti_inst->send_msg(i);
  if (0 != ret) {
    Logger::ngap().error( "Could not send ITTI message %s to task TASK_AMF_N2", i->get_msg_name());
  } 
}

int ngap_amf_handle_initial_ue_message(const sctp_assoc_id_t             assoc_id,  const sctp_stream_id_t            stream,  struct Ngap_NGAP_PDU *message_p){
  Logger::ngap().debug("sending itti inital ue message to TASK_AMF_N2");
  asn_fprint(stderr, &asn_DEF_Ngap_NGAP_PDU, message_p);
  //decode INITIAL_UE_MESSAGE
  InitialUEMessageMsg * initUeMsg = new InitialUEMessageMsg();
  if(!initUeMsg->decodefrompdu(message_p)){
    Logger::ngap().error("decoding initialuemessage message error");
    return -1;
  }
  itti_initial_ue_message *init_ue_msg = new itti_initial_ue_message(TASK_NGAP, TASK_AMF_N2);
  init_ue_msg->assoc_id = assoc_id;
  init_ue_msg->stream = stream;
  init_ue_msg->initUeMsg = initUeMsg; 
  std::shared_ptr<itti_initial_ue_message> i = std::shared_ptr<itti_initial_ue_message>(init_ue_msg);
  int ret = itti_inst->send_msg(i);
  if (0 != ret) {
    Logger::ngap().error( "Could not send ITTI message %s to task TASK_AMF_N2", i->get_msg_name());
  } 
}
int ngap_amf_handle_uplink_nas_transport(const sctp_assoc_id_t             assoc_id,  const sctp_stream_id_t            stream,  struct Ngap_NGAP_PDU *message_p){
  Logger::ngap().debug("sending itti up link nas transport message to TASK_AMF_N2");
  asn_fprint(stderr, &asn_DEF_Ngap_NGAP_PDU, message_p);
  UplinkNASTransportMsg * uplinkNasT = new UplinkNASTransportMsg();
  if(!uplinkNasT->decodefrompdu(message_p)){
    Logger::ngap().error("decoding UplinkNasTransport message error");
    return -1;
  }
  itti_ul_nas_transport * itti_ul_nas = new itti_ul_nas_transport(TASK_NGAP, TASK_AMF_N2);
  itti_ul_nas->assoc_id = assoc_id;
  itti_ul_nas->stream = stream;
  itti_ul_nas->ulNas = uplinkNasT;
  std::shared_ptr<itti_ul_nas_transport> i = std::shared_ptr<itti_ul_nas_transport>(itti_ul_nas);
  int ret = itti_inst->send_msg(i);
  if (0 != ret) {
    Logger::ngap().error( "Could not send ITTI message %s to task TASK_AMF_N2", i->get_msg_name());
  } 
}




































ngap_message_decoded_callback   messages_callback[][3] = {
    {0,0,0}, /*0 AMFConfigurationUpdate*/
    {0,0,0}, /*1 AMFStatusIndication*/
    {0,0,0}, /*2 CellTrafficTrace*/
    {0,0,0}, /*3 DeactivateTrace*/
    {0,0,0}, /*4 DownlinkNASTransport*/
    {0,0,0}, /*5 DownlinkNonUEAssociatedNRPPaTransport*/
    {0,0,0}, /*6 DownlinkRANConfigurationTransfer*/
    {0,0,0}, /*7 DownlinkRANStatusTransfer*/
    {0,0,0}, /*8 DownlinkUEAssociatedNRPPaTransport*/
    {0,0,0},//9 {ngap_amf_handle_error_indication,0,0}, /*ErrorIndication*/
    {0,0,0}, /*10 HandoverCancel*/
    {0,0,0}, /*11 HandoverNotification*/
    {0,0,0}, /*12 HandoverPreparation*/
    {0,0,0}, /*13 HandoverResourceAllocation*/
    {0,0,0},//{14
     //0,ngap_amf_handle_initial_context_setup_response,
     //ngap_amf_handle_initial_context_setup_failure}, /*InitialContextSetup*/
    {ngap_amf_handle_initial_ue_message,0,0},//15 {ngap_amf_handle_initial_ue_message,0,0}, /*InitialUEMessage*/
    {0,0,0}, /*16 LocationReportingControl*/
    {0,0,0}, /*17 LocationReportingFailureIndication*/
    {0,0,0}, /*18 LocationReport*/
    {0,0,0}, /*19 NASNonDeliveryIndication*/
    {0,0,0}, /*20 NGReset*/
    {ngap_amf_handle_ng_setup_request,0,0}, /*21 NGSetup*/
    {0,0,0}, /*OverloadStart*/
    {0,0,0}, /*OverloadStop*/
    {0,0,0}, /*Paging*/
    {0,0,0},//{ngap_amf_handle_path_switch_request,0,0}, /*PathSwitchRequest*
    {0,0,0}, /*PDUSessionResourceModify*/
    {0,0,0}, /*PDUSessionResourceModifyIndication*/
    {0,0,0}, /*PDUSessionResourceRelease*/
    {0,0,0}, /*PDUSessionResourceSetup*/
    {0,0,0}, /*PDUSessionResourceNotify*/
    {0,0,0}, /*PrivateMessage*/
    {0,0,0}, /*PWSCancel*/
    {0,0,0}, /*PWSFailureIndication*/
    {0,0,0}, /*PWSRestartIndication*/
    {0,0,0}, /*RANConfigurationUpdate*/
    {0,0,0}, /*RerouteNASRequest*/
    {0,0,0}, /*RRCInactiveTransitionReport*/
    {0,0,0}, /*TraceFailureIndication*/
    {0,0,0}, /*TraceStart*/
    {0,0,0}, /*UEContextModification*/
    {0,0,0},//{0,ngap_amf_handle_ue_context_release_complete,0}, /*UEContextRelease*/
    {0,0,0},//{ngap_amf_handle_ue_context_release_request,0,0}, /*UEContextReleaseRequest*/
    {0,0,0}, /*UERadioCapabilityCheck*/
    {0,0,0},//{ngap_amf_handle_ue_radio_cap_indication,0,0}, /*UERadioCapabilityInfoIndication*/
    {0,0,0}, /*UETNLABindingRelease*/
    {ngap_amf_handle_uplink_nas_transport,0,0},//{ngap_amf_handle_uplink_nas_transport,0,0}, /*UplinkNASTransport*/
    {0,0,0}, /*UplinkNonUEAssociatedNRPPaTransport*/
    {0,0,0}, /*UplinkRANConfigurationTransfer*/
    {0,0,0}, /*UplinkRANStatusTransfer*/
    {0,0,0}, /*UplinkUEAssociatedNRPPaTransport*/
    {0,0,0}, /*WriteReplaceWarning*/
    {0,0,0}, /*WriteReplaceWarning*/
    {0,0,0}, /*WriteReplaceWarning*/
    {0,0,0}, /*WriteReplaceWarning*/
    {0,0,0}, /*WriteReplaceWarning*/
    {0,0,0}, /*WriteReplaceWarning*/
    {0,0,0}, /*WriteReplaceWarning*/
    {0,0,0}, /*WriteReplaceWarning*/
    {0,0,0} /*WriteReplaceWarning*/
};
