#include "PDUSessionResourceAdmittedList.hpp"

#include <iostream>
using namespace std;

namespace ngap {
PDUSessionResourceAdmittedList::PDUSessionResourceAdmittedList() {
  pduSessionResourceAdmittedItem = NULL;
  numofSessionResourceAdmittedItem = 0;
}
PDUSessionResourceAdmittedList::~PDUSessionResourceAdmittedList() {
}

void PDUSessionResourceAdmittedList::setPDUSessionResourceAdmittedList(
    PDUSessionResourceAdmittedItem *m_pduSessionResourceAdmittedItem, int num) {
  pduSessionResourceAdmittedItem = m_pduSessionResourceAdmittedItem;
  numofSessionResourceAdmittedItem = num;
}
bool PDUSessionResourceAdmittedList::encode2PDUSessionResourceAdmittedList(
    Ngap_PDUSessionResourceAdmittedList_t *pduSessionResourceAdmittedList) {
  for (int i = 0; i < numofSessionResourceAdmittedItem; i++) {
    Ngap_PDUSessionResourceAdmittedItem_t *response =
        (Ngap_PDUSessionResourceAdmittedItem_t*) calloc(
            1, sizeof(Ngap_PDUSessionResourceAdmittedItem_t));
    if (!response)
      return false;
    if (!pduSessionResourceAdmittedItem[i].encode2PDUSessionResourceAdmittedItem(
        response))
      return false;
    if (ASN_SEQUENCE_ADD(&pduSessionResourceAdmittedList->list, response) != 0)
      return false;
  }

  return true;
}
bool PDUSessionResourceAdmittedList::decodefromPDUSessionResourceAdmittedList(
    Ngap_PDUSessionResourceAdmittedList_t *pduSessionResourceAdmittedList) {
  numofSessionResourceAdmittedItem = pduSessionResourceAdmittedList->list.count;
  pduSessionResourceAdmittedItem =
      new PDUSessionResourceAdmittedItem[numofSessionResourceAdmittedItem]();
  for (int i = 0; i < numofSessionResourceAdmittedItem; i++) {
    if (!pduSessionResourceAdmittedItem[i]
        .decodefromPDUSessionResourceAdmittedItem(
        pduSessionResourceAdmittedList->list.array[i]))
      return false;
  }

  return true;
}
void PDUSessionResourceAdmittedList::getPDUSessionResourceAdmittedList(
    PDUSessionResourceAdmittedItem *&m_pduSessionResourceAdmittedItem,
    int &num) {
  m_pduSessionResourceAdmittedItem = pduSessionResourceAdmittedItem;
  num = numofSessionResourceAdmittedItem;
}

}

