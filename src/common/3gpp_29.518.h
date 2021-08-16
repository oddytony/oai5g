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

#ifndef FILE_3GPP_29_518_SEEN
#define FILE_3GPP_29_518_SEEN

#include "amf.hpp"
#include <vector>

typedef enum amf_event_e {
  LOCATION_REPORT              = 1,
  PRESENCE_IN_AOI_REPORT       = 2,
  TIMEZONE_REPORT              = 3,
  ACCESS_TYPE_REPORT           = 4,
  REGISTRATION_STATE_REPORT    = 5,
  CONNECTIVITY_STATE_REPORT    = 6,
  REACHABILITY_REPORT          = 7,
  COMMUNICATION_FAILURE_REPORT = 8,
  UES_IN_AREA_REPORT           = 9,
  SUBSCRIPTION_ID_CHANGE       = 10,
  SUBSCRIPTION_ID_ADDITION     = 11,
  LOSS_OF_CONNECTIVITY         = 12
} amf_event_t;

static const std::vector<std::string> amf_event_e2str = {
    "AMF_EVENT_UNKNOWN",
    "LOCATION_REPORT",
    "PRESENCE_IN_AOI_REPORT",
    "TIMEZONE_REPORT",
    "ACCESS_TYPE_REPORT",
    "REGISTRATION_STATE_REPORT",
    "CONNECTIVITY_STATE_REPORT",
    "REACHABILITY_REPORT",
    "COMMUNICATION_FAILURE_REPORT",
    "UES_IN_AREA_REPORT",
    "SUBSCRIPTION_ID_CHANGE",
    "SUBSCRIPTION_ID_ADDITION",
    "LOSS_OF_CONNECTIVITY"};

enum class notification_method_e {
  PERIODIC           = 1,
  ONE_TIME           = 2,
  ON_EVENT_DETECTION = 3
};

static const std::vector<std::string> notification_method_e2str = {
    "NOTIFICATION_METHOD_UNKNOWN", "PERIODIC", "ONE_TIME",
    "ON_EVENT_DETECTION"};

typedef struct event_subscription_s {
  amf_event_t amf_event;
  // immediateFlag:
  // areaList:
  // locationFilterList:
  // refId:

} event_subscription_t;
#endif
