#include "PDUSessionResourceListHORqd.hpp"

#include <iostream>
using namespace std;

namespace ngap {
PDUSessionResourceListHORqd::PDUSessionResourceListHORqd() {
  pduSessionResourceItemHORqd      = NULL;
  numofpduSessionResourceItemHORqd = 0;
}
PDUSessionResourceListHORqd::~PDUSessionResourceListHORqd() {}

void PDUSessionResourceListHORqd::setPDUSessionResourceListHORqd(
    PDUSessionResourceItemHORqd* m_pduSessionResourceItemHORqd, int num) {
  pduSessionResourceItemHORqd      = m_pduSessionResourceItemHORqd;
  numofpduSessionResourceItemHORqd = num;
}
bool PDUSessionResourceListHORqd::encode2PDUSessionResourceListHORqd(
    Ngap_PDUSessionResourceListHORqd_t* pduSessionResourceListHORQqd) {
  for (int i = 0; i < numofpduSessionResourceItemHORqd; i++) {
    Ngap_PDUSessionResourceItemHORqd_t* response =
        (Ngap_PDUSessionResourceItemHORqd_t*) calloc(
            1, sizeof(Ngap_PDUSessionResourceItemHORqd_t));
    if (!response) return false;
    if (!pduSessionResourceItemHORqd[i].encode2PDUSessionResourceItemHORqd(
            response))
      return false;
    if (ASN_SEQUENCE_ADD(&pduSessionResourceListHORQqd->list, response) != 0)
      return false;
  }

  return true;
}
bool PDUSessionResourceListHORqd::decodefromPDUSessionResourceListHORqd(
    Ngap_PDUSessionResourceListHORqd_t* pduSessionResourceListHORQqd) {
  numofpduSessionResourceItemHORqd = pduSessionResourceListHORQqd->list.count;
  pduSessionResourceItemHORqd =
      new PDUSessionResourceItemHORqd[numofpduSessionResourceItemHORqd]();
  for (int i = 0; i < numofpduSessionResourceItemHORqd; i++) {
    if (!pduSessionResourceItemHORqd[i].decodefromPDUSessionResourceItemHORqd(
            pduSessionResourceListHORQqd->list.array[i]))
      return false;
  }

  return true;
}
void PDUSessionResourceListHORqd::getPDUSessionResourceListHORqd(
    PDUSessionResourceItemHORqd*& m_pduSessionResourceItemHORqd, int& num) {
  m_pduSessionResourceItemHORqd = pduSessionResourceItemHORqd;
  num                           = numofpduSessionResourceItemHORqd;
}

}  // namespace ngap
