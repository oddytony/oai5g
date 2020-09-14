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

/*! \file amf_statistics.cpp
 \brief
 \author  Keliang DU, BUPT
 \date 2020
 \email: contact@openairinterface.org
 */

#include "amf_statistics.hpp"

#include <iostream>

#include "logger.hpp"

//------------------------------------------------------------------------------
void statistics::display() {
  Logger::amf_app().info("");
  //Logger::amf_app().info("--------------------------------------------------");
  //Logger::amf_app().info("| connected gNBs | connected UEs | registered UEs |");
  //Logger::amf_app().info("--------------------------------------------------");
  //Logger::amf_app().info("|       %d       |       %d      |        %d     |",gNB_connected,UE_connected,UE_registred);
  //Logger::amf_app().info("--------------------------------------------------");
  Logger::amf_app().info(
      "|----------------------------------------------------------------------------------------------------------------|");
  Logger::amf_app().info(
      "|----------------------------------------------------gNBs' information-------------------------------------------|");
  Logger::amf_app().info(
      "|    Index    |      Status      |       Global ID       |       gNB Name       |    Tracking Area (PLMN, TAC)   |");
  if (gnbs.size() == 0) {
    Logger::amf_app().info(
        "|      -      |          -       |           -           |           -          |                -               |");
  }

  //TODO: Show the list of common PLMNs
  for (int i = 0; i < gnbs.size(); i++) {
    Logger::amf_app().info(
        "|      %d      |    Connected     |         0x%x       |         %s        |          %s, %d          | ",
        i + 1, gnbs[i].gnb_id, gnbs[i].gnb_name.c_str(),
        (gnbs[i].mcc + gnbs[i].mnc).c_str(), gnbs[i].tac);
  }
  Logger::amf_app().info(
      "|----------------------------------------------------------------------------------------------------------------|");
  Logger::amf_app().info("");

  Logger::amf_app().info(
      "|----------------------------------------------------------------------------------------------------------------|");
  Logger::amf_app().info(
      "|----------------------------------------------------UEs' information--------------------------------------------|");
  Logger::amf_app().info(
      "|  Index | Connection state | Registration state |      IMSI        |     GUTI      | RAN UE NGAP ID | AMF UE ID |");
  for (int i = 0; i < ues.size(); i++) {
    Logger::amf_app().info(
        "|    %d   |  %s    |    %s    | %s  |  %s  |       %d        |     %d     | ",
        i + 1, ues[i].connStatus.c_str(), ues[i].registerStatus.c_str(),
        ues[i].imsi.c_str(), ues[i].guti.c_str(), ues[i].ranid, ues[i].amfid);
    //Logger::amf_app().info("Current ran_ue_ngap_id[%d]; Current amf_ue_ngap_id[%d]", ues[i].ranid, ues[i].amfid);
    Logger::amf_app().info("Location [NrCgi][PLMN(%s), cellID(%d)]",
                           (ues[i].mcc + ues[i].mnc).c_str(), ues[i].cellId);
    Logger::amf_app().info("");
  }
  Logger::amf_app().info(
      "|----------------------------------------------------------------------------------------------------------------|");
  Logger::amf_app().info("");
}

//------------------------------------------------------------------------------
statistics::statistics() {
  gNB_connected = 0;
  UE_connected = 0;
  UE_registred = 0;
}

//------------------------------------------------------------------------------
statistics::~statistics() {
}
