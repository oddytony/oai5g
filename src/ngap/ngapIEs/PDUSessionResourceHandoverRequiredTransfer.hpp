/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this
 * file except in compliance with the License. You may obtain a copy of the
 * License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

#ifndef _PDUSESSIONRESOURCEHANDOVERREQUIREDTRANSFER_H_
#define _PDUSESSIONRESOURCEHANDOVERREQUIREDTRANSFER_H_

#include "NgapIEsStruct.hpp"

#include "DLQoSFlowPerTNLInformation.hpp"
#include "SecurityResult.hpp"

extern "C" {
#include "Ngap_ProtocolIE-Field.h"
#include "Ngap_HandoverRequiredTransfer.h"
}

namespace ngap {

class PDUSessionResourceHandoverRequiredTransfer {
 public:
  PDUSessionResourceHandoverRequiredTransfer();
  virtual ~PDUSessionResourceHandoverRequiredTransfer();
  void setDirectForwardingPathAvailability(
      Ngap_DirectForwardingPathAvailability_t directForwardingPathAvailability);
  int encode2buffer(uint8_t* buf, int buf_size);
  // Decapsulation
  bool decodefromIE(uint8_t* buf, int buf_size);
  bool getDirectForwardingPathAvailability(
      long* directForwardingPathAvailability);

 private:
  Ngap_HandoverRequiredTransfer_t* handoverrquiredTransferIEs;
  Ngap_DirectForwardingPathAvailability_t* DirectForwardingPathAvailability;
};

}  // namespace ngap
#endif