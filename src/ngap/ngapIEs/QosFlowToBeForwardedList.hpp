#ifndef _QOSFLOWTOBEFORWARDEDLIST_H_
#define _QOSFLOWTOBEFORWARDEDLIST_H_

#include "QosFlowToBeForwardedItem.hpp"
extern "C"
{
#include "Ngap_QosFlowToBeForwardedList.h"
}
namespace ngap
{
    class QosFlowToBeForwardedList
    {
    public:
        QosFlowToBeForwardedList();
        virtual ~QosFlowToBeForwardedList();
        void setQosFlowToBeForwardedItem(QosFlowToBeForwardedItem *m_qosflowtobeforwardeditem, int num);
        bool encodeQosFlowToBeForwardedList(Ngap_QosFlowToBeForwardedList *&m_ngap_qosflowtobeforwardedlist);

    private:
        QosFlowToBeForwardedItem *Qosflowtobeforwardeditem;
        int numofqosflowtobeforwardeditem;
    };
} // namespace ngap
#endif