#ifndef _DRBSTATUSUL_H_
#define _DRBSTATUSUL_H_
#include "dRBStatusUL18.hpp"
extern "C"
{
#include "Ngap_DRBStatusUL.h"
}
namespace ngap
{
    class dRBStatusUL
    {
    private:
        /* data */
        dRBStatusUL18 *ul18;

    public:
        dRBStatusUL(/* args */);
        virtual ~dRBStatusUL();
        void setdRBStatusUL(dRBStatusUL18 *uL18);
        void getdRBStatusUL(dRBStatusUL18 *&uL18);
        bool encodedRBStatusUL(Ngap_DRBStatusUL_t *uL);
        bool decodedRBStatusUL(Ngap_DRBStatusUL_t *uL);
    };
} // namespace ngap
#endif