#ifndef _ITTI_MSG_N2_H_
#define _ITTI_MSG_N2_H_


#include "itti_msg.hpp"
#include "NGSetupRequest.hpp"
#include "InitialUEMessage.hpp"
#include "UplinkNASTransport.hpp"
#include "sctp_server.hpp"

using namespace ngap;
using namespace sctp;

class itti_msg_n2 : public itti_msg{
public:
  itti_msg_n2(const itti_msg_type_t  msg_type, const task_id_t origin, const task_id_t destination):itti_msg(msg_type,origin,destination){
  }
  itti_msg_n2(const itti_msg_n2& i) : itti_msg(i){
    assoc_id = i.assoc_id;
    stream = i.stream;
  }
  sctp_assoc_id_t assoc_id;
  sctp_stream_id_t stream;
};

class itti_new_sctp_association : public itti_msg_n2{
public:
  itti_new_sctp_association(const task_id_t origin, const task_id_t destination) : itti_msg_n2(NEW_SCTP_ASSOCIATION, origin, destination){}
};

class itti_ng_setup_request : public itti_msg_n2{
public:
  itti_ng_setup_request(const task_id_t origin, const task_id_t destination):itti_msg_n2(NG_SETUP_REQ,origin,destination){}
  itti_ng_setup_request(const itti_ng_setup_request &i) : itti_msg_n2(i){
  }
public:
  NGSetupRequestMsg * ngSetupReq;
};

class itti_initial_ue_message : public itti_msg_n2{
public:
  itti_initial_ue_message(const task_id_t origin, const task_id_t destination):itti_msg_n2(INITIAL_UE_MSG,origin,destination){}
  itti_initial_ue_message(const itti_initial_ue_message &i) : itti_msg_n2(i){}

  InitialUEMessageMsg * initUeMsg;
};

class itti_ul_nas_transport : public itti_msg_n2{
public:
  itti_ul_nas_transport(const task_id_t origin, const task_id_t destination):itti_msg_n2(ITTI_UL_NAS_TRANSPORT,origin,destination){}
  itti_ul_nas_transport(const itti_ul_nas_transport &i) : itti_msg_n2(i){}

  UplinkNASTransportMsg *ulNas;
};

class itti_dl_nas_transport : public itti_msg_n2{
public:
  itti_dl_nas_transport(const task_id_t origin, const task_id_t destination):itti_msg_n2(ITTI_DL_NAS_TRANSPORT,origin,destination){}
  itti_dl_nas_transport(const itti_dl_nas_transport &i) : itti_msg_n2(i){}
public:
  uint32_t ran_ue_ngap_id;
  long     amf_ue_ngap_id;
  bstring  nas;
};








#endif
