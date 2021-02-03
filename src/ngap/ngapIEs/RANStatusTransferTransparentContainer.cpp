#include "RANStatusTransferTransparentContainer.hpp"
#include <iostream>
#include <vector>
using namespace std;

namespace ngap {
RANStatusTransferTransparentContainer::RANStatusTransferTransparentContainer() {
  drb_sub_list = NULL;
}
RANStatusTransferTransparentContainer::
    ~RANStatusTransferTransparentContainer() {}
void RANStatusTransferTransparentContainer::getdRBSubject_list(
    dRBSubjectList*& drblist) {
  drblist = drb_sub_list;
}
void RANStatusTransferTransparentContainer::setdRBSubject_list(
    dRBSubjectList* drblist) {
  drb_sub_list = drblist;
}
bool RANStatusTransferTransparentContainer::
    encoderanstatustransfer_transparentcontainer(
        Ngap_RANStatusTransfer_TransparentContainer_t*
            ranstatustransfer_transparentcontainer) {
  if (!drb_sub_list->encodefromdRBSubjectlist(
          ranstatustransfer_transparentcontainer
              ->dRBsSubjectToStatusTransferList)) {
    cout << "encoderanstatustransfer_transparentcontainer error" << endl;
    return false;
  }
  return true;
}
bool RANStatusTransferTransparentContainer::
    decoderanstatustransfer_transparentcontainer(
        Ngap_RANStatusTransfer_TransparentContainer_t*
            ranstatustransfer_transparentcontainer) {
  drb_sub_list = new dRBSubjectList();
  if (!drb_sub_list->decodefromdRBSubjectlist(
          ranstatustransfer_transparentcontainer
              ->dRBsSubjectToStatusTransferList)) {
    cout << "decoderanstatustransfer_transparentcontainer error" << endl;
    return false;
  }
  return true;
}
}  // namespace ngap