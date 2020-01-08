#ifndef _AMF_N2_H_
#define _AMF_N2_H_

#include "ngap_app.hpp"
#include "itti_msg_n2.hpp"
#include "ue_ngap_context.hpp"

namespace amf{

class amf_n2 : public ngap::ngap_app{
public:
  amf_n2(const string &address, const uint16_t port_num);
  ~amf_n2();
  //void handle_receive(bstring payload, sctp_assoc_id_t assoc_id, sctp_stream_id_t stream, sctp_stream_id_t instreams, sctp_stream_id_t outstreams);
  void handle_itti_message(itti_new_sctp_association &new_assoc);
  void handle_itti_message(itti_ng_setup_request &ngsetupreq);
  //void handle_itti_message(itti_initial_ue_message &init_ue_msg);
private:
  std::map<uint32_t, std::shared_ptr<ue_ngap_context>> ranid2uecontext;// ran ue ngap id
  mutable std::shared_mutex m_ranid2uecontext;
}; 








}
















#endif
