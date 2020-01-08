#ifndef _AMF_N1_H_
#define _AMF_N1_H_

#include <map>
#include <shared_mutex>
#include "nas_context.hpp"

namespace amf{

class amf_n1{
public:
  amf_n1();
  ~amf_n1();
  //void handle_itti_message(itti_nas_signaling_establishment_req & nas_signaling_estb_req);
private:
  std::map<long, std::shared_ptr<nas_context>> amfueid2nas_context; // amf ue ngap id
  mutable std::shared_mutex m_amfueid2nas_context;

};
}










#endif
