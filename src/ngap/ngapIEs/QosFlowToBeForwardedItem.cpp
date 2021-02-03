#include "QosFlowToBeForwardedItem.hpp"
extern "C" {}
#include <iostream>
using namespace std;
namespace ngap {
QosFlowToBeForwardedItem::QosFlowToBeForwardedItem() {
  qosflowidentifier = NULL;
}
QosFlowToBeForwardedItem::~QosFlowToBeForwardedItem() {}
void QosFlowToBeForwardedItem::setQosFlowIdentifier(
    QosFlowIdentifier* m_qosflowidentifier) {
  qosflowidentifier = m_qosflowidentifier;
}
bool QosFlowToBeForwardedItem::encodeQosFlowToBeForwardedItem(
    Ngap_QosFlowToBeForwardedItem_t* qosflowtobeforwardeditem) {
  if (!qosflowidentifier) return false;
  if (!qosflowidentifier->encode2QosFlowIdentifier(
          &qosflowtobeforwardeditem->qosFlowIdentifier)) {
    cout << "encode QFI error" << endl;
    return false;
  }
  return true;
}
}  // namespace ngap