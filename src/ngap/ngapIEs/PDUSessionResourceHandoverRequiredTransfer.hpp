#ifndef _PDUSESSIONRESOURCEHANDOVERREQUIREDTRANSFER_H_
#define _PDUSESSIONRESOURCEHANDOVERREQUIREDTRANSFER_H_

#include "NgapIEsStruct.hpp"

#include "DLQoSFlowPerTNLInformation.hpp"
#include "SecurityResult.hpp"

extern "C" {
#include "Ngap_ProtocolIE-Field.h"
#include "Ngap_HandoverRequiredTransfer.h"
}

namespace ngap {

class PDUSessionResourceHandoverRequiredTransfer {

 public:
  PDUSessionResourceHandoverRequiredTransfer();
  virtual ~PDUSessionResourceHandoverRequiredTransfer();
  void setDirectForwardingPathAvailability(
      Ngap_DirectForwardingPathAvailability_t directForwardingPathAvailability);
  int encode2buffer(uint8_t *buf, int buf_size);
  //Decapsulation
  bool decodefromIE(uint8_t *buf, int buf_size);
  bool getDirectForwardingPathAvailability(
      long *directForwardingPathAvailability);
 private:
  Ngap_HandoverRequiredTransfer_t *handoverrquiredTransferIEs;
  Ngap_DirectForwardingPathAvailability_t *DirectForwardingPathAvailability;
};

}
#endif

