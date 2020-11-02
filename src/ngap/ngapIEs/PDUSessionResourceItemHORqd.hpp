#ifndef _PDUSESSIONRESOURCEITEMHORQD_H_
#define _PDUSESSIONRESOURCEITEMHQRQD_H_

#include "PDUSessionID.hpp"
#include "PDUSessionResourceHandoverRequestAckTransfer.hpp"
extern "C" {
#include "Ngap_PDUSessionResourceItemHORqd.h"
}

namespace ngap {

class PDUSessionResourceItemHORqd {
public:
  PDUSessionResourceItemHORqd();
  virtual ~PDUSessionResourceItemHORqd();

  void
  setPDUSessionResourceItemHORqd(PDUSessionID *m_pDUSessionID,
                                 OCTET_STRING_t m_handoverrequiredtransfer);
  void
  getPDUSessionResourceItemHORqd(PDUSessionID *&m_pDUSessionID,
                                 OCTET_STRING_t &m_handoverrequiredtransfer);

  bool encode2PDUSessionResourceItemHORqd(
      Ngap_PDUSessionResourceItemHORqd_t *pdUSessionResourceItemHORqd);
  bool decodefromPDUSessionResourceItemHORqd(
      Ngap_PDUSessionResourceItemHORqd_t *pdUSessionResourceItemHORqd);

private:
  PDUSessionID *pDUSessionID;
  OCTET_STRING_t handoverrequiredtransfer;
};

} // namespace ngap

#endif
