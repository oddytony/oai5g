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

/*! \file amf_n11.hpp
 \brief
 \author Keliang DU (BUPT), Tien-Thinh NGUYEN (EURECOM)
 \date 2020
 \email: contact@openairinterface.org
 */

#ifndef _AMF_N11_H_
#define _AMF_N11_H_

#include <map>
#include <shared_mutex>
#include <string>

#include "itti_msg_n11.hpp"
#include "pdu_session_context.hpp"
#include "AuthenticationInfo.h"
#include "UEAuthenticationCtx.h"

namespace amf_application {

class amf_n11 {
 public:
  amf_n11();
  ~amf_n11();

  void handle_itti_message(itti_smf_services_consumer&);
  void handle_pdu_session_initial_request(
      std::string supi, std::shared_ptr<pdu_session_context> psc,
      std::string smf_addr, std::string smf_api_version, bstring sm_msg,
      std::string dnn);
  void handle_itti_message(itti_nsmf_pdusession_update_sm_context& itti_msg);
  void handle_itti_message(itti_nsmf_pdusession_release_sm_context& itti_msg);
  void handle_itti_message(itti_pdu_session_resource_setup_response& itti_msg);
  void send_pdu_session_update_sm_context_request(
      std::string supi, std::shared_ptr<pdu_session_context> psc,
      std::string smf_addr, bstring sm_msg, std::string dnn);

  std::map<std::string, std::shared_ptr<pdu_session_context>>
      supi2pdu;  // amf ue ngap id
  mutable std::shared_mutex m_supi2pdu;
  bool is_supi_to_pdu_ctx(const std::string& supi) const;
  std::shared_ptr<pdu_session_context> supi_to_pdu_ctx(
      const std::string& supi) const;
  void set_supi_to_pdu_ctx(
      const std::string& supi, std::shared_ptr<pdu_session_context> psc);
  std::map<uint8_t, std::string> pduid2supi;

  bool smf_selection_from_configuration(
      std::string& smf_addr, std::string& smf_api_version);
  // bool smf_selection_from_context(
  //    std::string& smf_addr, std::string& smf_api_version);
  void handle_post_sm_context_response_error_400();
  void handle_post_sm_context_response_error(
      long code, std::string cause, bstring n1sm, std::string supi,
      uint8_t pdu_session_id);

  void curl_http_client(
      std::string remoteUri, std::string jsonData, std::string n1SmMsg,
      std::string n2SmMsg, std::string supi, uint8_t pdu_session_id);

  bool discover_smf(
      std::string& smf_addr, std::string& smf_api_version,
      const snssai_t snssai, const plmn_t plmn, const std::string dnn);

  bool send_ue_authentication_request(
      oai::amf::model::AuthenticationInfo& auth_info,
      oai::amf::model::UEAuthenticationCtx& ue_auth_ctx, uint8_t http_version);
};

}  // namespace amf_application

#endif
