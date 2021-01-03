#ifndef _PDUSESSIONRESOURCESETUPITEMHOREQ_H_
#define _PDUSESSIONRESOURCESETUPITEMHOREQ_H_

#include "PDUSessionID.hpp"
#include "NAS-PDU.hpp"
#include "S-NSSAI.hpp"
#include "PDUSessionResourceSetupRequestTransfer.hpp"

extern "C" {
#include "Ngap_PDUSessionResourceSetupItemHOReq.h"
}

namespace ngap {

class PDUSessionResourceSetupItemHOReq {
 public:
  PDUSessionResourceSetupItemHOReq();
  virtual ~PDUSessionResourceSetupItemHOReq();

  void setPDUSessionResourceSetupItemHOReq(
      PDUSessionID *m_pDUSessionID, S_NSSAI *m_s_NSSAI,
      OCTET_STRING_t m_pDUSessionResourceSetupRequestTransfer);
  void getPDUSessionResourceSetupItemHOReq(
      PDUSessionID *&m_pDUSessionID, S_NSSAI *&m_s_NSSAI,
      OCTET_STRING_t &m_pDUSessionResourceSetupRequestTransfer);

  bool encode2PDUSessionResourceSetupItemHOReq(
      Ngap_PDUSessionResourceSetupItemHOReq_t *pduSessionResourceSetupItemHOReq);
  bool decodefromPDUSessionResourceSetupItemHOReq(
      Ngap_PDUSessionResourceSetupItemHOReq_t *pduSessionResourceSetupItemHOReq);
 private:
  PDUSessionID *pDUSessionID;
  S_NSSAI *s_NSSAI;
  OCTET_STRING_t pDUSessionResourceSetupRequestTransfer;
};

}

#endif

