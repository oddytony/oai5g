#ifndef _GNB_CONTEXT_H_
#define _GNB_CONTEXT_H_

#include <stdint.h>
#include <string>
#include <vector>
#include "sctp_server.hpp"

extern "C"{
  #include "Ngap_PagingDRX.h"
}

using namespace sctp;
using namespace std;

enum amf_ng_gnb_state_s{
    NGAP_INIT,
    NGAP_RESETING,
    NGAP_READY,
    NGAP_SHUTDOWN
};

typedef struct SliceSupport_s{
  string sst;
  string sd;
}SliceSupport_t;

typedef struct BroadcastPlmn_s{
  string mcc;
  string mnc;
  vector<SliceSupport_t> slice_list; 
}BroadcastPlmn_t;

typedef struct SupportedTA_s{
  uint32_t tac;
  vector<BroadcastPlmn_t> b_plmn_list; 
}SupportedTA_t;

class gnb_context{
public:
  enum amf_ng_gnb_state_s ng_state;
  
  string                  gnb_name;
  long                    globalRanNodeId;
  e_Ngap_PagingDRX        default_paging_drx;  //v32, v64, v128, v256
  vector<SupportedTA_t>   s_ta_list;
  
  sctp_assoc_id_t         sctp_assoc_id;
  sctp_stream_id_t        next_sctp_stream;
  sctp_stream_id_t        instreams;
  sctp_stream_id_t        outstreams;
  
};















#endif
