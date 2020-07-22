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

/*! \file pdu_session_context.hpp
 \brief
 \author  Keliang DU, BUPT
 \date 2020
 \email: contact@openairinterface.org
 */

#ifndef _PDU_SESSION_CONTEXT_H_
#define _PDU_SESSION_CONTEXT_H_

#include <string>
#include "bstrlib.h"
using namespace std;

class pdu_session_context{
public:
  pdu_session_context();
  ~pdu_session_context();
public:
  uint32_t ran_ue_ngap_id;
  long     amf_ue_ngap_id;
  uint8_t req_type;
  uint8_t pdu_session_id;
  bstring n2sm;
  string dnn;
  string remote_smf_addr[0];//"192.168.12.10:8080"
  bool smf_avaliable;
};
#endif
