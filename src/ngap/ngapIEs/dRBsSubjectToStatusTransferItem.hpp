#ifndef _DRBSSUBJECTTOSTATUSTRANSFERITEM_H_
#define _DRBSSUBJECTTOSTATUSTRANSFERITEM_H_
#include "dRBStatusUL.hpp"
#include "dRBStatusDL.hpp"
extern "C" {
#include "Ngap_DRBsSubjectToStatusTransferItem.h"
}
namespace ngap {
class dRBSubjectItem {
 public:
  dRBSubjectItem();
  virtual ~dRBSubjectItem();
  void getdRBSubjectItem(
      Ngap_DRB_ID_t*& dRB_ID, dRBStatusUL*& dRB_UL, dRBStatusDL*& dRB_DL);
  void setdRBSubjectItem(
      Ngap_DRB_ID_t* dRB_ID, dRBStatusUL* dRB_UL, dRBStatusDL* dRB_DL);
  bool decodefromdRBSubjectItem(
      Ngap_DRBsSubjectToStatusTransferItem_t* dRB_item);
  bool encodedRBSubjectItem(Ngap_DRBsSubjectToStatusTransferItem_t* dRB_item);

 private:
  Ngap_DRB_ID_t* drb_id;
  dRBStatusUL* drb_ul;
  dRBStatusDL* drb_dl;
};
}  // namespace ngap
#endif