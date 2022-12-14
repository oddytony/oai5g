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

#include "PDUSessionResourceFailedToSetupItemCxtFail.hpp"

namespace ngap {

//------------------------------------------------------------------------------
PDUSessionResourceFailedToSetupItemCxtFail::
    PDUSessionResourceFailedToSetupItemCxtFail() {}

//------------------------------------------------------------------------------
PDUSessionResourceFailedToSetupItemCxtFail::
    ~PDUSessionResourceFailedToSetupItemCxtFail() {}

//------------------------------------------------------------------------------
void PDUSessionResourceFailedToSetupItemCxtFail::
    setPDUSessionResourceFailedToSetupItemCxtFail(
        const PDUSessionID& m_pDUSessionID,
        const OCTET_STRING_t& m_pDUSessionResourceSetupUnsuccessfulTransfer) {
  pDUSessionID = m_pDUSessionID;
  pDUSessionResourceSetupUnsuccessfulTransfer =
      m_pDUSessionResourceSetupUnsuccessfulTransfer;
}

//------------------------------------------------------------------------------
void PDUSessionResourceFailedToSetupItemCxtFail::
    getPDUSessionResourceFailedToSetupItemCxtFail(
        PDUSessionID& m_pDUSessionID,
        OCTET_STRING_t& m_pDUSessionResourceSetupUnsuccessfulTransfer) {
  m_pDUSessionID = pDUSessionID;
  pDUSessionResourceSetupUnsuccessfulTransfer =
      pDUSessionResourceSetupUnsuccessfulTransfer;
}

//------------------------------------------------------------------------------
bool PDUSessionResourceFailedToSetupItemCxtFail::
    encode2PDUSessionResourceFailedToSetupItemCxtFail(
        Ngap_PDUSessionResourceFailedToSetupItemCxtFail_t*
            pduSessionResourceFailedToSetupItemCxtFail) {
  if (!pDUSessionID.encode2PDUSessionID(
          pduSessionResourceFailedToSetupItemCxtFail->pDUSessionID))
    return false;
  pduSessionResourceFailedToSetupItemCxtFail
      ->pDUSessionResourceSetupUnsuccessfulTransfer =
      pDUSessionResourceSetupUnsuccessfulTransfer;

  return true;
}

//------------------------------------------------------------------------------
bool PDUSessionResourceFailedToSetupItemCxtFail::
    decodefromPDUSessionResourceFailedToSetupItemCxtFail(
        Ngap_PDUSessionResourceFailedToSetupItemCxtFail_t*
            pduSessionResourceFailedToSetupItemCxtFail) {
  if (!pDUSessionID.decodefromPDUSessionID(
          pduSessionResourceFailedToSetupItemCxtFail->pDUSessionID))
    return false;
  pDUSessionResourceSetupUnsuccessfulTransfer =
      pduSessionResourceFailedToSetupItemCxtFail
          ->pDUSessionResourceSetupUnsuccessfulTransfer;

  return true;
}

}  // namespace ngap
