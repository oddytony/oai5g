#include "dRBsSubjectToStatusTransferItem.hpp"

#include <iostream>
#include <vector>

using namespace std;
namespace ngap
{
    dRBSubjectItem::dRBSubjectItem()
    {
        drb_id = NULL;
        drb_ul = NULL;
        drb_dl = NULL;
    }
    dRBSubjectItem::~dRBSubjectItem() {}
    void dRBSubjectItem::setdRBSubjectItem(Ngap_DRB_ID_t *dRB_ID, dRBStatusUL *dRB_UL, dRBStatusDL *dRB_DL)
    {
        drb_id = dRB_ID;
        drb_ul = dRB_UL;
        drb_dl = dRB_DL;
    }
    void dRBSubjectItem::getdRBSubjectItem(Ngap_DRB_ID_t *&dRB_ID, dRBStatusUL *&dRB_UL, dRBStatusDL *&dRB_DL)
    {
        dRB_ID = drb_id;
        dRB_UL = drb_ul;
        dRB_DL = drb_dl;
    }
    bool dRBSubjectItem::decodefromdRBSubjectItem(Ngap_DRBsSubjectToStatusTransferItem_t *dRB_item)
    {
        if (dRB_item->dRB_ID)
        {
            drb_id = &dRB_item->dRB_ID;
            cout << "the decode drb_id is" << *drb_id << endl;
        }
        drb_ul = new dRBStatusUL();
        if (!drb_ul->decodedRBStatusUL(&dRB_item->dRBStatusUL))
        {
            cout << "decode from dRBSubjectItem  dRBStatusUL error" << endl;
            return false;
        }
        drb_dl = new dRBStatusDL();
        if (!drb_dl->decodedRBStatusDL(&dRB_item->dRBStatusDL))
        {
            cout << "decode from dRBSubjectItem  dRBStatusDL error" << endl;
            return false;
        }
        cout << "decode from dRBSubjectItem  successfully" << endl;
        return true;
    }
    bool dRBSubjectItem::encodedRBSubjectItem(Ngap_DRBsSubjectToStatusTransferItem_t *dRB_item)
    {
        if (drb_id)
        {
            dRB_item->dRB_ID = *drb_id;
            cout << "the encode drb_id is" << *drb_id << endl;
        }
        if (!drb_ul->encodedRBStatusUL(&dRB_item->dRBStatusUL))
        {
            cout << "encode from dRBSubjectItem  dRBStatusUL error" << endl;
            return false;
        }
        if (!drb_dl->encodedRBStatusDL(&dRB_item->dRBStatusDL))
        {
            cout << "encode from dRBSubjectItem  dRBStatusDL error" << endl;
            return false;
        }
        cout << "encode from dRBSubjectItem  successfully" << endl;
        return true;
    }
} // namespace ngap