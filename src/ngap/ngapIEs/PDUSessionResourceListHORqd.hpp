#ifndef _PDUSESSIONRESOURCELISTHORqd_H_
#define _PDUSESSIONRESOURCELISTHORqd_H_

#include "PDUSessionResourceItemHORqd.hpp"

extern "C" {
#include "Ngap_PDUSessionResourceListHORqd.h"
}

namespace ngap {

class PDUSessionResourceListHORqd {
 public:
  PDUSessionResourceListHORqd();
  virtual ~PDUSessionResourceListHORqd();

  void setPDUSessionResourceListHORqd(
      PDUSessionResourceItemHORqd *m_pduSessionResourceItemHORqd, int num);
  void getPDUSessionResourceListHORqd(
      PDUSessionResourceItemHORqd *&m_pduSessionResourceItemHORqd, int &num);

  bool encode2PDUSessionResourceListHORqd(
      Ngap_PDUSessionResourceListHORqd_t *pduSessionResourceListHORQqd);
  bool decodefromPDUSessionResourceListHORqd(
      Ngap_PDUSessionResourceListHORqd_t *pduSessionResourceListHORQqd);
 private:
  PDUSessionResourceItemHORqd *pduSessionResourceItemHORqd;
  int numofpduSessionResourceItemHORqd;
};

}

#endif

