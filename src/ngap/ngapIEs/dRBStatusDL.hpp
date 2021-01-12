#ifndef _DRBSTATUSDL_H_
#define _DRBSTATUSDL_H_
#include "dRBStatusDL18.hpp"
extern "C"
{
#include "Ngap_DRBStatusDL.h"
#include "Ngap_DRBStatusDL18.h"
}
namespace ngap
{
    class dRBStatusDL
    {
    private:
        /* data */
        DRBStatusDL18 *dl18;

    public:
        dRBStatusDL();
        virtual ~dRBStatusDL();
        void getDRBStatusDL18(DRBStatusDL18 *&dL18);
        void setDRBStatusDL18(DRBStatusDL18 *dL18);
        bool encodedRBStatusDL(Ngap_DRBStatusDL_t *dL);
        bool decodedRBStatusDL(Ngap_DRBStatusDL_t *dL);
    };

} // namespace ngap
#endif
