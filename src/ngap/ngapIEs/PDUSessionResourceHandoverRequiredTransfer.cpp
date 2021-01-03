#include "PDUSessionResourceHandoverRequiredTransfer.hpp"

extern "C" {
#include "constr_TYPE.h"
#include "asn_codecs.h"
#include "per_encoder.h"
#include "per_decoder.h"
#include "constraints.h"
}

#include <iostream>
using namespace std;

namespace ngap {
PDUSessionResourceHandoverRequiredTransfer::PDUSessionResourceHandoverRequiredTransfer() {
  handoverrquiredTransferIEs = (Ngap_HandoverRequiredTransfer_t*) calloc(
      1, sizeof(Ngap_HandoverRequiredTransfer_t));
  DirectForwardingPathAvailability = NULL;
}
PDUSessionResourceHandoverRequiredTransfer::~PDUSessionResourceHandoverRequiredTransfer() {
}

void PDUSessionResourceHandoverRequiredTransfer::setDirectForwardingPathAvailability(
    Ngap_DirectForwardingPathAvailability_t directForwardingPathAvailability) {
  if (!DirectForwardingPathAvailability)
    DirectForwardingPathAvailability =
        new Ngap_DirectForwardingPathAvailability_t();
  *DirectForwardingPathAvailability = directForwardingPathAvailability;
}

int PDUSessionResourceHandoverRequiredTransfer::encode2buffer(uint8_t *buf,
                                                              int buf_size) {
  asn_fprint(stderr, &asn_DEF_Ngap_HandoverRequiredTransfer,
             handoverrquiredTransferIEs);
  asn_enc_rval_t er = aper_encode_to_buffer(
      &asn_DEF_Ngap_HandoverRequiredTransfer, NULL, handoverrquiredTransferIEs,
      buf, buf_size);
  cout << "er.encoded(" << er.encoded << ")" << endl;
  return er.encoded;
}
//Decapsulation
bool PDUSessionResourceHandoverRequiredTransfer::decodefromIE(uint8_t *buf,
                                                              int buf_size) {
  asn_dec_rval_t rc = asn_decode(NULL, ATS_ALIGNED_CANONICAL_PER,
                                 &asn_DEF_Ngap_HandoverRequiredTransfer,
                                 (void**) &handoverrquiredTransferIEs, buf,
                                 buf_size);
  if (rc.code == RC_OK) {
    cout << "Decoded successfully" << endl;
  } else if (rc.code == RC_WMORE) {
    cout << "More data expected, call again" << endl;
    return false;
  } else {
    cout << "Failure to decode data" << endl;
    return false;
  }
  cout << "rc.consumed to decode = " << rc.consumed << endl;
  cout << endl;
  //asn_fprint(stderr, &asn_DEF_Ngap_PDUSessionResourceSetupResponseTransfer, pduSessionResourceSetupResponseTransferIEs);
  if (handoverrquiredTransferIEs->directForwardingPathAvailability) {
    Ngap_DirectForwardingPathAvailability_t *directForwardingPathAvailability =
        new Ngap_DirectForwardingPathAvailability_t;
    directForwardingPathAvailability = handoverrquiredTransferIEs
        ->directForwardingPathAvailability;
  }

  return true;
}

bool PDUSessionResourceHandoverRequiredTransfer::getDirectForwardingPathAvailability(
    long *directForwardingPathAvailability) {
  directForwardingPathAvailability = DirectForwardingPathAvailability;
  return true;
}

}

