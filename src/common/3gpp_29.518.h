/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this
 *file except in compliance with the License. You may obtain a copy of the
 *License at
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

#ifndef FILE_3GPP_29_518_SEEN
#define FILE_3GPP_29_518_SEEN

#include <vector>

enum n1_n2_message_transfer_cause_e {
  ATTEMPTING_TO_REACH_UE            = 1,
  N1_N2_TRANSFER_INITIATED          = 2,
  WAITING_FOR_ASYNCHRONOUS_TRANSFER = 3,
  UE_NOT_RESPONDING                 = 4,
  N1_MSG_NOT_TRANSFERRED            = 5,
  UE_NOT_REACHABLE_FOR_SESSION      = 6
};

static const std::vector<std::string> n1_n2_message_transfer_cause_e2str = {
    "UNKNOWN ERROR",
    "ATTEMPTING_TO_REACH_UE",
    "N1_N2_TRANSFER_INITIATED",
    "WAITING_FOR_ASYNCHRONOUS_TRANSFER",
    "UE_NOT_RESPONDING",
    "N1_MSG_NOT_TRANSFERRED",
    "UE_NOT_REACHABLE_FOR_SESSION"};

#endif
