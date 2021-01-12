#ifndef _DRBSSUBJECTTOSTATUSTRANSFERLIST_H_
#define _DRBSSUBJECTTOSTATUSTRANSFERLIST_H_
#include "dRBsSubjectToStatusTransferItem.hpp"
extern "C"
{
#include "Ngap_DRBsSubjectToStatusTransferList.h"
#include "asn_SEQUENCE_OF.h"
}
namespace ngap
{
    class dRBSubjectList
    {
    public:
        dRBSubjectList();
        virtual ~dRBSubjectList();
        void setdRBSubjectItem(dRBSubjectItem *m_item, int num);
        void getdRBSubjectItem(dRBSubjectItem *&m_item, int &num);
        bool decodefromdRBSubjectlist(Ngap_DRBsSubjectToStatusTransferList_t &DRBsSubjectToStatusTransferList);
        bool encodefromdRBSubjectlist(Ngap_DRBsSubjectToStatusTransferList_t &DRBsSubjectToStatusTransferList);

    private:
        dRBSubjectItem *drbsubjectitem;
        int numofitem;
    };
} // namespace ngap
#endif