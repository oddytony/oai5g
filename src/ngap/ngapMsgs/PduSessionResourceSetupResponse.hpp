/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
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

/*! \file
 \brief
 \author  Keliang DU, BUPT
 \date 2020
 \email: contact@openairinterface.org
 */

#ifndef _PDUSESSIONRESOURCESETUPRESPONSE_H_
#define _PDUSESSIONRESOURCESETUPRESPONSE_H_

#include "NgapIEsStruct.hpp"

#include "MessageType.hpp"
#include "AMF-UE-NGAP-ID.hpp"
#include "RAN-UE-NGAP-ID.hpp"
#include "PDUSessionResourceSetupListSURes.hpp"
#include "PDUSessionResourceFailedToSetupListSURes.hpp"

extern "C" {
#include "Ngap_NGAP-PDU.h"
#include "Ngap_ProtocolIE-Field.h"
#include "Ngap_PDUSessionResourceSetupResponse.h"
}

namespace ngap {

class PduSessionResourceSetupResponseMsg {
 public:
  PduSessionResourceSetupResponseMsg();
  virtual ~PduSessionResourceSetupResponseMsg();

  void setMessageType();
  void setAmfUeNgapId(unsigned long id);  //40 bits
  void setRanUeNgapId(uint32_t id);  // 32 bits
  void setPduSessionResourceSetupResponseList(std::vector<PDUSessionResourceSetupResponseItem_t> list);
  void setPduSessionResourceFailedToSetupList(std::vector<PDUSessionResourceFailedToSetupItem_t> list);

  int encode2buffer(uint8_t *buf, int buf_size);
  //Decapsulation
  bool decodefrompdu(Ngap_NGAP_PDU_t *ngap_msg_pdu);
  unsigned long getAmfUeNgapId();
  uint32_t getRanUeNgapId();
  bool getPduSessionResourceSetupResponseList(std::vector<PDUSessionResourceSetupResponseItem_t> &list);
  bool getPduSessionResourceFailedToSetupList(std::vector<PDUSessionResourceFailedToSetupItem_t> &list);

 private:
  Ngap_NGAP_PDU_t *pduSessionResourceSetupResponsePdu;
  Ngap_PDUSessionResourceSetupResponse_t *pduSessionResourceSetupResponseIEs;

  AMF_UE_NGAP_ID *amfUeNgapId;
  RAN_UE_NGAP_ID *ranUeNgapId;
  PDUSessionResourceSetupListSURes *pduSessionResourceSetupResponseList;
  PDUSessionResourceFailedToSetupListSURes *pduSessionResourceFailedToSetupResponseList;
};

}
#endif

