#ifndef _HANDOVERREQUESTACK_H_
#define _HANDOVERREQUESTACK_H_

#include "NgapIEsStruct.hpp"
#include "PDUSessionResourceAdmittedItem.hpp"
#include "PDUSessionResourceAdmittedList.hpp"
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
#include "Ngap_PDUSessionResourceAdmittedItem.h"
#include "Ngap_HandoverRequestAcknowledgeTransfer.h"
#include <netinet/in.h>
#include <arpa/inet.h>
}

namespace ngap {

class HandoverRequestAck {
 public:
  HandoverRequestAck();
  virtual ~HandoverRequestAck();

  int encode2buffer(uint8_t* buf, int buf_size);
  bool decodefrompdu(Ngap_NGAP_PDU_t* ngap_msg_pdu);

  unsigned long getAmfUeNgapId();  // return -1;(不存在)
  uint32_t getRanUeNgapId();       // return -1;(不存在)

  void setMessageType();  // Initialize the PDU and populate the MessageType;
  OCTET_STRING_t getTargetToSource_TransparentContainer();
  bool getPDUSessionResourceAdmittedList(
      std::vector<PDUSessionResourceAdmittedItem_t>& list);

 private:
  Ngap_NGAP_PDU_t* handoverRequestAckPdu;
  Ngap_HandoverRequestAcknowledge_t* handoverRequestAckIEs;
  /***************** for decoding ****************/
  AMF_UE_NGAP_ID* amfUeNgapId;
  RAN_UE_NGAP_ID* ranUeNgapId;
  Ngap_HandoverType_t* handovertype;

  PDUSessionResourceAdmittedList* pduSessionResourceAdmittedList;
  Ngap_PDUSessionResourceFailedToSetupListHOAck_t*
      PDUSessionResourceFailedToSetupList;
  Ngap_TargetToSource_TransparentContainer_t*
      TargetToSource_TransparentContainer;
  Ngap_CriticalityDiagnostics_t* CriticalityDiagnostics;
};

}  // namespace ngap

#endif
