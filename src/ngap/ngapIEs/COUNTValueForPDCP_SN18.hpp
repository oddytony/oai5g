#ifndef _COUNTVALUEFORPDCP_SN18_H_
#define _COUNTVALUEFORPDCP_SN18_H_
extern "C" {
#include "Ngap_COUNTValueForPDCP-SN18.h"
}
namespace ngap {
class COUNTValueForPDCP_SN18 {
 private:
  /* data */
  long pdcp;
  long hfn_pdcp;

 public:
  COUNTValueForPDCP_SN18(/* args */);
  virtual ~COUNTValueForPDCP_SN18();
  void getvalue(long& pDCP, long& hFN_PDCP);
  void setvalue(long pDCP, long hfn_PDCP);
  bool encodedCOUNTValueForPDCP_SN18(Ngap_COUNTValueForPDCP_SN18_t* countvalue);
  bool decodedCOUNTValueForPDCP_SN18(Ngap_COUNTValueForPDCP_SN18_t& countValue);
};

}  // namespace ngap
#endif
