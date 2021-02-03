#include "COUNTValueForPDCP_SN18.hpp"
#include <iostream>
#include <vector>

using namespace std;
namespace ngap {
COUNTValueForPDCP_SN18::COUNTValueForPDCP_SN18() {
  pdcp     = 0;
  hfn_pdcp = 0;
}
COUNTValueForPDCP_SN18::~COUNTValueForPDCP_SN18() {}
void COUNTValueForPDCP_SN18::setvalue(long pDCP, long hfn_PDCP) {
  pdcp     = pDCP;
  hfn_pdcp = hfn_PDCP;
}
void COUNTValueForPDCP_SN18::getvalue(long& pDCP, long& hFN_PDCP) {
  pDCP     = pdcp;
  hFN_PDCP = hfn_pdcp;
}
bool COUNTValueForPDCP_SN18::encodedCOUNTValueForPDCP_SN18(
    Ngap_COUNTValueForPDCP_SN18_t* countvalue) {
  countvalue->pDCP_SN18     = pdcp;
  countvalue->hFN_PDCP_SN18 = hfn_pdcp;
  cout << "the encode pdcp_sn18 is" << countvalue->pDCP_SN18 << endl;
  cout << "the encode hfn_pdcp_sn18 is" << countvalue->hFN_PDCP_SN18 << endl;
  return true;
}
bool COUNTValueForPDCP_SN18::decodedCOUNTValueForPDCP_SN18(
    Ngap_COUNTValueForPDCP_SN18_t& countValue) {
  pdcp     = countValue.pDCP_SN18;
  hfn_pdcp = countValue.hFN_PDCP_SN18;
  cout << "the decode pdcp_sn18 is" << countValue.pDCP_SN18 << endl;
  cout << "the decode hfn_pdcp_sn18 is" << countValue.hFN_PDCP_SN18 << endl;
  return true;
}
}  // namespace ngap
