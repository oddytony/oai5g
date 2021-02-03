#include "dRBStatusUL18.hpp"

#include <iostream>
using namespace std;
namespace ngap {
dRBStatusUL18::dRBStatusUL18() {
  pdcp_value = NULL;
}
dRBStatusUL18::~dRBStatusUL18() {}
void dRBStatusUL18::getcountvalue(COUNTValueForPDCP_SN18*& count_value) {
  count_value = pdcp_value;
}
void dRBStatusUL18::setcountvalue(COUNTValueForPDCP_SN18* count_value) {
  pdcp_value = count_value;
}
bool dRBStatusUL18::encodeddRBStatusUL18(Ngap_DRBStatusUL18_t* UL18) {
  if (!pdcp_value->encodedCOUNTValueForPDCP_SN18(&UL18->uL_COUNTValue)) {
    cout << "encodeddRBStatusUL18 error" << endl;
    return false;
  }
  return true;
}
bool dRBStatusUL18::decodeddRBStatusUL18(Ngap_DRBStatusUL18_t* UL18) {
  pdcp_value = new COUNTValueForPDCP_SN18();
  if (!pdcp_value->decodedCOUNTValueForPDCP_SN18(UL18->uL_COUNTValue)) {
    cout << "decodeddRBStatusUL18 error" << endl;
    return false;
  }
  return true;
}
}  // namespace ngap
