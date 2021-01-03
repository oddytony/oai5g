#include "PDUSessionResourceSetupListHOReq.hpp"

#include <iostream>
using namespace std;

namespace ngap {
PDUSessionResourceSetupListHOReq::PDUSessionResourceSetupListHOReq() {
  pduSessionResourceSetupItemHOReq = NULL;
  numofpduSessionResourceSetupItemHOReq = 0;
}
PDUSessionResourceSetupListHOReq::~PDUSessionResourceSetupListHOReq() {
}

void PDUSessionResourceSetupListHOReq::setPDUSessionResourceSetupListHOReq(
    PDUSessionResourceSetupItemHOReq *m_pduSessionResourceSetupItemHOReq,
    int num) {
  pduSessionResourceSetupItemHOReq = m_pduSessionResourceSetupItemHOReq;
  numofpduSessionResourceSetupItemHOReq = num;
}
bool PDUSessionResourceSetupListHOReq::encode2PDUSessionResourceSetupListHOReq(
    Ngap_PDUSessionResourceSetupListHOReq_t *pduSessionResourceSetupListHOReq) {
  for (int i = 0; i < numofpduSessionResourceSetupItemHOReq; i++) {
    Ngap_PDUSessionResourceSetupItemHOReq_t *request =
        (Ngap_PDUSessionResourceSetupItemHOReq_t*) calloc(
            1, sizeof(Ngap_PDUSessionResourceSetupItemHOReq_t));
    if (!request)
      return false;
    if (!pduSessionResourceSetupItemHOReq[i]
        .encode2PDUSessionResourceSetupItemHOReq(request))
      return false;
    if (ASN_SEQUENCE_ADD(&pduSessionResourceSetupListHOReq->list, request) != 0)
      return false;
  }

  return true;
}
bool PDUSessionResourceSetupListHOReq::decodefromPDUSessionResourceSetupListHOReq(
    Ngap_PDUSessionResourceSetupListHOReq_t *pduSessionResourceSetupListHOReq) {
  numofpduSessionResourceSetupItemHOReq = pduSessionResourceSetupListHOReq->list
      .count;
  pduSessionResourceSetupItemHOReq =
      new PDUSessionResourceSetupItemHOReq[numofpduSessionResourceSetupItemHOReq]();
  for (int i = 0; i < numofpduSessionResourceSetupItemHOReq; i++) {
    if (!pduSessionResourceSetupItemHOReq[i]
        .decodefromPDUSessionResourceSetupItemHOReq(
        pduSessionResourceSetupListHOReq->list.array[i]))
      return false;
  }

  return true;
}
void PDUSessionResourceSetupListHOReq::getPDUSessionResourceSetupListHOReq(
    PDUSessionResourceSetupItemHOReq *&m_pduSessionResourceSetupItemHOReq,
    int &num) {
  m_pduSessionResourceSetupItemHOReq = pduSessionResourceSetupItemHOReq;
  num = numofpduSessionResourceSetupItemHOReq;
}

}

