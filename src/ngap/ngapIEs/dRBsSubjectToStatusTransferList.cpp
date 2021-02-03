#include "dRBsSubjectToStatusTransferList.hpp"
#include <iostream>
#include <vector>
using namespace std;
namespace ngap {
dRBSubjectList::dRBSubjectList() {
  drbsubjectitem = NULL;
  numofitem      = 0;
}
dRBSubjectList::~dRBSubjectList() {}
void dRBSubjectList::setdRBSubjectItem(dRBSubjectItem* m_item, int num) {
  drbsubjectitem = m_item;
  numofitem      = num;
}
void dRBSubjectList::getdRBSubjectItem(dRBSubjectItem*& m_item, int& num) {
  m_item = drbsubjectitem;
  num    = numofitem;
}
bool dRBSubjectList::encodefromdRBSubjectlist(
    Ngap_DRBsSubjectToStatusTransferList_t& DRBsSubjectToStatusTransferList) {
  for (int i = 0; i < numofitem; i++) {
    Ngap_DRBsSubjectToStatusTransferItem_t* ie =
        (Ngap_DRBsSubjectToStatusTransferItem_t*) calloc(
            1, sizeof(Ngap_DRBsSubjectToStatusTransferItem_t));
    if (!ie) return false;
    if (!drbsubjectitem[i].encodedRBSubjectItem(ie)) {
      cout << "encodefromdRBSubjectlist error" << endl;
      return false;
    }
    if (ASN_SEQUENCE_ADD(&DRBsSubjectToStatusTransferList.list, ie) != 0) {
      cout
          << "ASN_SEQUENCE_ADD(&DRBsSubjectToStatusTransferList.list, ie) error"
          << endl;
      return false;
    }
  }
  cout << "encodefromdRBSubjectlist successfully" << endl;
  return true;
}
bool dRBSubjectList::decodefromdRBSubjectlist(
    Ngap_DRBsSubjectToStatusTransferList_t& DRBsSubjectToStatusTransferList) {
  numofitem      = DRBsSubjectToStatusTransferList.list.count;
  drbsubjectitem = new dRBSubjectItem[numofitem]();
  for (int i = 0; i < numofitem; i++) {
    if (!drbsubjectitem[i].decodefromdRBSubjectItem(
            DRBsSubjectToStatusTransferList.list.array[i])) {
      cout << "decodefromdRBSubjectlist error" << endl;
      return false;
    }
  }
  cout << "decodefromdRBSubjectlist successfully" << endl;
  return true;
}
}  // namespace ngap