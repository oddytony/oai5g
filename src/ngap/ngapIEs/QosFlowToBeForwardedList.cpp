#include "QosFlowToBeForwardedList.hpp"
#include <iostream>
using namespace std;
namespace ngap
{
    QosFlowToBeForwardedList::QosFlowToBeForwardedList()
    {
        Qosflowtobeforwardeditem = NULL;
        numofqosflowtobeforwardeditem = 0;
    }
    QosFlowToBeForwardedList::~QosFlowToBeForwardedList() {}
    void QosFlowToBeForwardedList::setQosFlowToBeForwardedItem(QosFlowToBeForwardedItem *m_qosflowtobeforwardeditem, int num)
    {
        Qosflowtobeforwardeditem = m_qosflowtobeforwardeditem;
        numofqosflowtobeforwardeditem = num;
    }
    bool QosFlowToBeForwardedList::encodeQosFlowToBeForwardedList(Ngap_QosFlowToBeForwardedList *&m_ngap_qosflowtobeforwardedlist)
    {
        m_ngap_qosflowtobeforwardedlist = (Ngap_QosFlowToBeForwardedList_t *)calloc(1, sizeof(Ngap_QosFlowToBeForwardedList_t));
        for (int i = 0; i < numofqosflowtobeforwardeditem; i++)
        {
            cout << "encoding list..." << endl;
            Ngap_QosFlowToBeForwardedItem_t *response = (Ngap_QosFlowToBeForwardedItem_t *)calloc(1, sizeof(Ngap_QosFlowToBeForwardedItem_t));
            if (!response)
                return false;
            if (!Qosflowtobeforwardeditem[i].encodeQosFlowToBeForwardedItem(response))
            {
                cout << "encode QosFlowTowardedItem error" << endl;
                return false;
            }
            cout << "QFI is " << response->qosFlowIdentifier << endl;
            if (ASN_SEQUENCE_ADD(&m_ngap_qosflowtobeforwardedlist->list, response) != 0)
            {
                cout << "encode QosFlowTowardedList error" << endl;
                return false;
            }
        }
        return true;
    }
} // namespace ngap