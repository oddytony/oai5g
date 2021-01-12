#ifndef _RANSTATUSTRANSFERTRANSPATENTCONTAINER_H_
#define _RANSTATUSTRANSFERTRANSPATENTCONTAINER_H_
#include "dRBsSubjectToStatusTransferList.hpp"
#include "dRBsSubjectToStatusTransferItem.hpp"
extern "C"
{
#include "Ngap_RANStatusTransfer-TransparentContainer.h"
}
namespace ngap
{
    class RANStatusTransferTransparentContainer
    {
    private:
        /* data */
        dRBSubjectList *drb_sub_list;

    public:
        RANStatusTransferTransparentContainer(/* args */);
        virtual ~RANStatusTransferTransparentContainer();
        void getdRBSubject_list(dRBSubjectList *&drblist);
        void setdRBSubject_list(dRBSubjectList *drblist);
        bool encoderanstatustransfer_transparentcontainer(Ngap_RANStatusTransfer_TransparentContainer_t *ranstatustransfer_transparentcontainer);
        bool decoderanstatustransfer_transparentcontainer(Ngap_RANStatusTransfer_TransparentContainer_t *ranstatustransfer_transparentcontainer);
    };

} // namespace ngap
#endif