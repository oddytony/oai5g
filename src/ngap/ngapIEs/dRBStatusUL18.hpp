#ifndef _DRBSTATUSUL18_H_
#define _DRBSTATUSUL18_H_
#include "COUNTValueForPDCP_SN18.hpp"
extern "C"
{
#include "Ngap_DRBStatusUL18.h"
}
namespace ngap
{
    class dRBStatusUL18
    {
    private:
        /* data */
        COUNTValueForPDCP_SN18 *pdcp_value;

    public:
        dRBStatusUL18(/* args */);
        virtual ~dRBStatusUL18();
        void getcountvalue(COUNTValueForPDCP_SN18 *&count_value);
        void setcountvalue(COUNTValueForPDCP_SN18 *count_value);
        bool encodeddRBStatusUL18(Ngap_DRBStatusUL18_t *UL18);
        bool decodeddRBStatusUL18(Ngap_DRBStatusUL18_t *UL18);
    };

} // namespace ngap
#endif