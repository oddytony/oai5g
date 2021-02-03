#ifndef _HANDOVERREQUIRED_H_
#define _HANDOVERREQUIRED_H_

#include "NgapIEsStruct.hpp"

#include "MessageType.hpp"
#include "GlobalRanNodeId.hpp"
#include "RanNodeName.hpp"
#include "DefaultPagingDRX.hpp"
#include "SupportedTAList.hpp"
#include "AMF-UE-NGAP-ID.hpp"
#include "RAN-UE-NGAP-ID.hpp"
#include "Cause.hpp"
extern "C" {
#include "Ngap_NGAP-PDU.h"
#include "Ngap_ProtocolIE-Field.h"
#include "Ngap_NGSetupRequest.h"
}
#include "TAI.hpp"
#include "NgapIEsStruct.hpp"
#include "PDUSessionResourceListHORqd.hpp"
namespace ngap {

class HandoverRequiredMsg {
 public:
  HandoverRequiredMsg();
  virtual ~HandoverRequiredMsg();

  int encode2buffer(uint8_t* buf, int buf_size);
  bool decodefrompdu(Ngap_NGAP_PDU_t* ngap_msg_pdu);
  unsigned long getAmfUeNgapId();  // return -1;(不存在)
  uint32_t getRanUeNgapId();       // return -1;(不存在)

  Ngap_HandoverType_t getHandoverType();
  Ngap_Cause_PR getChoiceOfCause();
  long getCauseValue();
  OCTET_STRING_t getSourceToTarget_TransparentContainer();
  void getGlobalRanNodeId(GlobalgNBId*& ptr);
  void getTAI(TAI*& ptr);
  bool getPDUSessionResourceList(std::vector<PDUSessionResourceItem_t>& list);
  long getDirectForwardingPathAvailability();

 private:
  Ngap_NGAP_PDU_t* handoverRequiredPdu;
  Ngap_HandoverRequired_t* handoverRequiredIEs;
  /***************** for decoding ****************/
  AMF_UE_NGAP_ID* amfUeNgapId;
  RAN_UE_NGAP_ID* ranUeNgapId;
  Ngap_HandoverType_t* handovertype;
  Cause* cause;
  Ngap_TargetID_t* targetid;
  Ngap_DirectForwardingPathAvailability_t* directforwardingPathAvailability;
  PDUSessionResourceListHORqd* PDUSessionResourceList;
  Ngap_SourceToTarget_TransparentContainer_t*
      SourceToTarget_TransparentContainer;
};

}  // namespace ngap

#endif
