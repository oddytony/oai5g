#ifndef _PDUSessionResourceHandoverCommandTransfer_H_
#define _PDUSessionResourceHandoverCommandTransfer_H_

#include "UPTransportLayerInformation.hpp"
#include "QosFlowToBeForwardedList.hpp"
#include "NgapIEsStruct.hpp"
extern "C" {
#include "Ngap_ProtocolIE-Field.h"
#include "Ngap_HandoverCommandTransfer.h"
}
namespace ngap {
class PDUSessionResourceHandoverCommandTransfer {
 private:
  /* data */
  Ngap_HandoverCommandTransfer_t* handovercommandtransferIE;
  UpTransportLayerInformation* dLForwardingUP_TNLInformation;
  QosFlowToBeForwardedList* qosFlowToBeForwardedList;

 public:
  PDUSessionResourceHandoverCommandTransfer(/* args */);
  virtual ~PDUSessionResourceHandoverCommandTransfer();
  void setUPTransportLayerInformation(GtpTunnel_t uptlinfo);
  void setQosFlowToBeForwardedList(
      std::vector<QosFlowToBeForwardedItem_t> list);
  int encodePDUSessionResourceHandoverCommandTransfer(
      uint8_t* buf, int buf_size);
};

}  // namespace ngap
#endif