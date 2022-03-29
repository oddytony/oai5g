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

/*! \file amf_n1.hpp
 \brief
 \author Keliang DU (BUPT), Tien-Thinh NGUYEN (EURECOM)
 \date 2020
 \email: contact@openairinterface.org
 */

#ifndef _AMF_N1_H_
#define _AMF_N1_H_

#include <mysql/mysql.h>
#include <stdlib.h>
#include <string.h>

#include <map>
#include <shared_mutex>

#include "3gpp_ts24501.hpp"
#include "3gpp_29.503.h"
#include "amf.hpp"
#include "amf_statistics.hpp"
#include "bstrlib.h"
#include "itti_msg_n1.hpp"
#include "mysql_db.hpp"
#include "nas_context.hpp"
#include "pdu_session_context.hpp"
#include "amf_event.hpp"
#include "RegistrationAccept.hpp"
#include "ue_context.hpp"
#include "itti.hpp"
#include "SliceInfoForRegistration.h"
#include "AuthorizedNetworkSliceInfo.h"
#include "Nssai.h"

namespace amf_application {

#define NAS_MESSAGE_DOWNLINK 1
#define NAS_MESSAGE_UPLINK 0

typedef enum {
  PlainNasMsg                                              = 0x0,
  IntegrityProtected                                       = 0x1,
  IntegrityProtectedAndCiphered                            = 0x2,
  IntegrityProtectedWithNew5GNASSecurityContext            = 0x3,
  IntegrityProtectedAndCipheredWithNew5GNASSecurityContext = 0x4,
} SecurityHeaderType;

class amf_n1 {
 public:
  std::map<long, std::shared_ptr<nas_context>>
      amfueid2nas_context;  // amf ue ngap id
  mutable std::shared_mutex m_amfueid2nas_context;

  std::map<std::string, std::shared_ptr<nas_context>> imsi2nas_context;
  std::map<std::string, long> supi2amfId;
  std::map<std::string, uint32_t> supi2ranId;
  mutable std::shared_mutex m_nas_context;

  std::map<std::string, std::shared_ptr<nas_context>> guti2nas_context;
  mutable std::shared_mutex m_guti2nas_context;

  static std::map<std::string, std::string> rand_record;
  static uint8_t no_random_delta;
  random_state_t random_state;
  database_t* db_desc;

  amf_n1();
  ~amf_n1();

  /*
   * Handle ITTI message
   * @param [itti_uplink_nas_data_ind&]: ITTI message
   * @return void
   */
  void handle_itti_message(itti_uplink_nas_data_ind&);

  /*
   * Handle ITTI message
   * @param [itti_downlink_nas_transfer&]: ITTI message
   * @return void
   */
  void handle_itti_message(itti_downlink_nas_transfer& itti_msg);

  /*
   * Handle NAS Establishment Request (Registration Request, Service Request)
   * @param [SecurityHeaderType] type: Security Header Type
   * @param [std::shared_ptr<nas_context>] nc: Shared pointer to the NAS context
   * @param [uint32_t] ran_ue_ngap_id: RAN UE NGAP Id
   * @param [long] amf_ue_ngap_id: AMF UE NGAP Id
   * @param [bstring] plain_msg: NAS message in plain text
   * @param [std::string] snn: Serving Network
   * @param [uint8_t] ulCount: UL Sequence number
   * @return void
   */
  void nas_signalling_establishment_request_handle(
      SecurityHeaderType type, std::shared_ptr<nas_context> nc,
      uint32_t ran_ue_ngap_id, long amf_ue_ngap_id, bstring plain_msg,
      std::string snn, uint8_t ulCount);

  // TODO
  void uplink_nas_msg_handle(
      uint32_t ran_ue_ngap_id, long amf_ue_ngap_id, bstring plain_msg,
      plmn_t plmn);

  // TODO
  bool check_security_header_type(SecurityHeaderType& type, uint8_t* buffer);

  // TODO
  bool is_guti_2_nas_context(const std::string& guti) const;

  // TODO
  std::shared_ptr<nas_context> guti_2_nas_context(
      const std::string& guti) const;

  // TODO
  void set_guti_2_nas_context(
      const std::string& guti, std::shared_ptr<nas_context> nc);

  // TODO
  bool is_amf_ue_id_2_nas_context(const long& amf_ue_ngap_id) const;

  // TODO
  std::shared_ptr<nas_context> amf_ue_id_2_nas_context(
      const long& amf_ue_ngap_id) const;

  // TODO
  void set_amf_ue_ngap_id_2_nas_context(
      const long& amf_ue_ngap_id, std::shared_ptr<nas_context> nc);

  // TODO
  void run_registration_procedure(std::shared_ptr<nas_context>& nc);

  // TODO
  void run_mobility_registration_update_procedure(
      std::shared_ptr<nas_context> nc, uint16_t uplink_data_status,
      uint16_t pdu_session_status);

  // TODO
  void run_periodic_registration_update_procedure(
      std::shared_ptr<nas_context> nc, uint16_t);

  // TODO
  void run_periodic_registration_update_procedure(
      std::shared_ptr<nas_context> nc, bstring& nas_msg);

  // TODO
  bool auth_vectors_generator(std::shared_ptr<nas_context>& nc);

  // TODO
  bool get_authentication_vectors_from_ausf(std::shared_ptr<nas_context>& nc);

  // TODO
  bool _5g_aka_confirmation_from_ausf(
      std::shared_ptr<nas_context>& nc, bstring resStar);

  // TODO
  bool authentication_vectors_generator_in_ausf(
      std::shared_ptr<nas_context>& nc);

  // TODO
  bool authentication_vectors_generator_in_udm(
      std::shared_ptr<nas_context>& nc);

  // TODO
  bool get_mysql_auth_info(std::string imsi, mysql_auth_info_t& resp);

  // TODO
  void mysql_push_rand_sqn(std::string imsi, uint8_t* rand_p, uint8_t* sqn);

  // TODO
  void mysql_increment_sqn(std::string imsi);

  // TODO
  bool connect_to_mysql();

  // TODO
  void generate_random(uint8_t* random_p, ssize_t length);

  // TODO
  void generate_5g_he_av_in_udm(
      const uint8_t opc[16], std::string imsi, uint8_t key[16], uint8_t sqn[6],
      std::string serving_network, _5G_HE_AV_t& vector);

  // TODO
  void test_generate_5g_he_av_in_udm(
      const uint8_t opc[16], uint8_t key[16], uint8_t sqnak[6],
      std::string serving_network, _5G_HE_AV_t& vector);

  // TODO
  void handle_auth_vector_successful_result(std::shared_ptr<nas_context> nc);

  // TODO
  bool start_authentication_procedure(
      std::shared_ptr<nas_context> nc, int vindex, uint8_t ngksi);

  // TODO
  bool check_nas_common_procedure_on_going(std::shared_ptr<nas_context> nc);

  // TODO
  int security_select_algorithms(
      uint8_t nea, uint8_t nia, uint8_t& amf_nea, uint8_t& amf_nia);

  // TODO
  bool start_security_mode_control_procedure(std::shared_ptr<nas_context> nc);

  // TODO
  void encode_nas_message_protected(
      nas_secu_ctx* nsc, bool is_secu_ctx_new, uint8_t security_header_type,
      uint8_t direction, uint8_t* input_nas_buf, int input_nas_len,
      bstring& encrypted_nas);

  // TODO
  bool nas_message_integrity_protected(
      nas_secu_ctx* nsc, uint8_t direction, uint8_t* input_nas,
      int input_nas_len, uint32_t& mac);

  // TODO
  bool nas_message_cipher_protected(
      nas_secu_ctx* nsc, uint8_t direction, bstring input_nas,
      bstring& output_nas);

  // TODO
  void dump_nas_message(uint8_t* buf, int len);

  // TODO
  void ue_authentication_simulator(uint8_t* rand, uint8_t* autn);

  // TODO
  void annex_a_4_33501(
      uint8_t ck[16], uint8_t ik[16], uint8_t* input, uint8_t rand[16],
      std::string serving_network, uint8_t* output);

  // TODO
  void set_5gmm_state(std::shared_ptr<nas_context> nc, _5gmm_state_t state);

  // TODO
  void get_5gmm_state(std::shared_ptr<nas_context> nc, _5gmm_state_t& state);

  // TODO
  void set_5gcm_state(
      std::shared_ptr<nas_context>& nc, const cm_state_t& state);

  // TODO
  void get_5gcm_state(
      const std::shared_ptr<nas_context>& nc, cm_state_t& state) const;

  // TODO
  void handle_ue_location_change(
      std::string supi, oai::amf::model::UserLocation, uint8_t http_version);

  // TODO
  void handle_ue_reachability_status_change(
      std::string supi, uint8_t status, uint8_t http_version);

  // TODO
  void handle_ue_registration_state_change(
      std::string supi, uint8_t status, uint8_t http_version);

  // TODO
  void handle_ue_connectivity_state_change(
      std::string supi, uint8_t status, uint8_t http_version);

  // TODO
  void get_pdu_session_to_be_activated(
      uint16_t pdu_session_status,
      std::vector<uint8_t>& pdu_session_to_be_activated);

  // TODO
  void initialize_registration_accept(
      std::unique_ptr<nas::RegistrationAccept>& registration_accept);

  // TODO
  void initialize_registration_accept(
      std::unique_ptr<nas::RegistrationAccept>& registration_accept,
      std::shared_ptr<nas_context>& nc);

  // TODO
  bool find_ue_context(
      const std::shared_ptr<nas_context>& nc, std::shared_ptr<ue_context>& uc);

  // TODO
  bool find_ue_context(
      uint32_t ran_ue_ngap_id, long amf_ue_ngap_id,
      std::shared_ptr<ue_context>& uc);

  // TODO
  void mobile_reachable_timer_timeout(
      timer_id_t timer_id, uint64_t amf_ue_ngap_id);

  // TODO
  void set_mobile_reachable_timer_timeout(
      std::shared_ptr<nas_context>& nc, const bool& b);

  // TODO
  void get_mobile_reachable_timer_timeout(
      const std::shared_ptr<nas_context>& nc, bool& b) const;

  // TODO
  bool get_mobile_reachable_timer_timeout(
      const std::shared_ptr<nas_context>& nc) const;

  // TODO
  void set_mobile_reachable_timer(
      std::shared_ptr<nas_context>& nc, const timer_id_t& t);
  // TODO
  void set_implicit_deregistration_timer(
      std::shared_ptr<nas_context>& nc, const timer_id_t& t);
  // TODO
  void implicit_deregistration_timer_timeout(
      timer_id_t timer_id, uint64_t amf_ue_ngap_id);
  // TODO
  bool reroute_registration_request(
      std::shared_ptr<nas_context>& nc, bool& reroute_result);
  // TODO
  bool get_slice_selection_subscription_data(
      const std::shared_ptr<nas_context>& nc, oai::amf::model::Nssai& nssai);
  // TODO
  bool get_slice_selection_subscription_data_from_conf_file(
      const std::shared_ptr<nas_context>& nc, oai::amf::model::Nssai& nssai);
  // TODO
  bool check_subscribed_nssai(
      const std::shared_ptr<nas_context>& nc, oai::amf::model::Nssai& nssai);
  // TODO
  bool check_requested_nssai(const std::shared_ptr<nas_context>& nc);
  // TODO
  bool get_network_slice_selection(
      const std::shared_ptr<nas_context>& nc, const std::string& nf_instance_id,
      const oai::amf::model::SliceInfoForRegistration& slice_info,
      oai::amf::model::AuthorizedNetworkSliceInfo&
          authorized_network_slice_info);
  // TODO
  bool get_network_slice_selection_from_conf_file(
      const std::string& nf_instance_id,
      const oai::amf::model::SliceInfoForRegistration& slice_info,
      oai::amf::model::AuthorizedNetworkSliceInfo&
          authorized_network_slice_info) const;
  // TODO
  bool get_target_amf(
      const std::shared_ptr<nas_context>& nc, std::string& target_amf,
      const oai::amf::model::AuthorizedNetworkSliceInfo&
          authorized_network_slice_info);
  // TODO
  bool select_target_amf(
      const std::shared_ptr<nas_context>& nc, std::string& target_amf,
      const nlohmann::json& amf_candidate_list);
  // TODO
  void send_n1_message_notity(
      const std::shared_ptr<nas_context>& nc,
      const std::string& target_amf) const;
  // TODO
  bool reroute_nas_via_an(
      const std::shared_ptr<nas_context>& nc,
      const std::string& target_amf_set);
  // TODO
  bool get_amf_set_id(const std::string& target_amf_set, uint16_t& amf_set_id);

 private:
  void ue_initiate_de_registration_handle(
      uint32_t ran_ue_ngap_id, long amf_ue_ngap_id, bstring nas);
  void registration_request_handle(
      bool isNasSig, std::shared_ptr<nas_context>& nc, uint32_t ran_ue_ngap_id,
      long amf_ue_ngap_id, std::string snn, bstring reg);
  void authentication_response_handle(
      uint32_t ran_ue_ngap_id, long amf_ue_ngap_id, bstring plain_msg);
  void authentication_failure_handle(
      uint32_t ran_ue_ngap_id, long amf_ue_ngap_id, bstring plain_msg);
  void security_mode_complete_handle(
      uint32_t ran_ue_ngap_id, long amf_ue_ngap_id, bstring nas_msg);
  void security_mode_reject_handle(
      uint32_t ran_ue_ngap_id, long amf_ue_ngap_id, bstring nas_msg);
  void ul_nas_transport_handle(
      uint32_t ran_ue_ngap_id, long amf_ue_ngap_id, bstring nas, plmn_t plmn);
  void registration_complete_handle(
      uint32_t ran_ue_ngap_id, long amf_ue_ngap_id, bstring nas_msg);
  void sha256(unsigned char* message, int msg_len, unsigned char* output);
  void service_request_handle(
      bool isNasSig, std::shared_ptr<nas_context> nc, uint32_t ran_ue_ngap_id,
      long amf_ue_ngap_id, bstring nas);
  void identity_response_handle(
      uint32_t ran_ue_ngap_id, long amf_ue_ngap_id, bstring plain_msg);

  // authentication vector
  bool generate_authentication_vector();
  void itti_send_dl_nas_buffer_to_task_n2(
      bstring& b, uint32_t ran_ue_ngap_id, long amf_ue_ngap_id);
  // response message
  void response_registration_reject_msg(
      uint8_t cause_value, uint32_t ran_ue_ngap_id, long amf_ue_ngap_id);

  // for Event Handling
  amf_event event_sub;
  bs2::connection ee_ue_location_report_connection;
  bs2::connection ee_ue_reachability_status_connection;
  bs2::connection ee_ue_registration_state_connection;
  bs2::connection ee_ue_connectivity_state_connection;
};
}  // namespace amf_application

#endif
