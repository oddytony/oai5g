#ifndef _DRBSTATUSDL18_H_
#define _DRBSTATUSDL18_H_
#include "COUNTValueForPDCP_SN18.hpp"
extern "C" {
#include "Ngap_DRBStatusDL18.h"
}
namespace ngap {
class DRBStatusDL18 {
 private:
  /* data */
  COUNTValueForPDCP_SN18* pdcp_value;

 public:
  DRBStatusDL18(/* args */);
  virtual ~DRBStatusDL18();
  void getcountvalue(COUNTValueForPDCP_SN18*& count_value);
  void setcountvalue(COUNTValueForPDCP_SN18* count_value);
  bool encodeddRBStatusDL18(Ngap_DRBStatusDL18_t* DL18);
  bool decodeddRBStatusDL18(Ngap_DRBStatusDL18_t* DL18);
};
}  // namespace ngap
#endif