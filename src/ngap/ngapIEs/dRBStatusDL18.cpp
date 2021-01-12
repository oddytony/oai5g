#include "dRBStatusDL18.hpp"

#include <iostream>
using namespace std;
namespace ngap
{
    DRBStatusDL18::DRBStatusDL18()
    {
        pdcp_value = NULL;
    }
    DRBStatusDL18::~DRBStatusDL18() {}
    void DRBStatusDL18::getcountvalue(COUNTValueForPDCP_SN18 *&count_value)
    {
        count_value = pdcp_value;
    }
    void DRBStatusDL18::setcountvalue(COUNTValueForPDCP_SN18 *count_value)
    {
        pdcp_value = count_value;
    }
    bool DRBStatusDL18::encodeddRBStatusDL18(Ngap_DRBStatusDL18_t *DL18)
    {
        if (!pdcp_value->encodedCOUNTValueForPDCP_SN18(&DL18->dL_COUNTValue))
        {
            cout << "encodeddRBStatusDL18 error" << endl;
            return false;
        }
        return true;
    }
    bool DRBStatusDL18::decodeddRBStatusDL18(Ngap_DRBStatusDL18_t *DL18)
    {
        pdcp_value = new COUNTValueForPDCP_SN18();
        if (!pdcp_value->decodedCOUNTValueForPDCP_SN18(DL18->dL_COUNTValue))
        {
            cout << "decodeddRBStatusDL18 error" << endl;
            return false;
        }
        return true;
    }
} // namespace ngap
