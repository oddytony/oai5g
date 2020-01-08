#ifndef _ITTI_MSG_N2_H_
#define _ITTI_MSG_N2_H_


#include "itti_msg.hpp"

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
  //NGSetupRequestMsg * ngSetupReq;
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
private:
  //NGSetupRequestMsg * ngSetupReq;
};










#endif
