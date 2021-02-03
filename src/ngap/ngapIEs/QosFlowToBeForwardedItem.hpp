#ifndef _QOSFLOWTOBEFORWARDEDITEM_H_
#define _QOSFLOWTOBEFORWARDEDITEM_H_
#include "QosFlowIdentifier.hpp"
extern "C" {
#include "Ngap_QosFlowToBeForwardedItem.h"
}
namespace ngap {
class QosFlowToBeForwardedItem {
 public:
  QosFlowToBeForwardedItem();
  virtual ~QosFlowToBeForwardedItem();
  void setQosFlowIdentifier(QosFlowIdentifier* m_qosflowidentifier);
  bool encodeQosFlowToBeForwardedItem(
      Ngap_QosFlowToBeForwardedItem_t* qosflowtobeforwardeditem);

 private:
  QosFlowIdentifier* qosflowidentifier;
};
}  // namespace ngap
#endif