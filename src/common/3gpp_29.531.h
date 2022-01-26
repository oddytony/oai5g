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

/*! \file 3gpp_29.531.h
 \brief
 \author Tien Thinh NGUYEN
 \company Eurecom
 \email: tien-thinh.nguyen@eurecom.fr
 */
#ifndef FILE_3GPP_29_531_SEEN
#define FILE_3GPP_29_531_SEEN

#include <stdint.h>

#include <string>
#include <vector>
#include "3gpp_23.003.h"

typedef struct subscribed_snssai_s {
  snssai_t subscribed_snssai;
} subscribed_snssai_t;

typedef struct nsi_information_s {
  std::string nrf_id;
  // TODO: nsiId
  // TODO: nrfNfMgtUri
  // TODO: nrfAccessTokenUri
} nsi_information_t;

typedef struct allowed_snssai_s {
  snssai_t allowed_snssai;
  std::vector<nsi_information_t> nsi_information_list;
  snssai_t mapped_home_snssai;
} allowed_snssai_t;

typedef struct allowed_nssai_s {
  std::vector<allowed_snssai_t> allowed_snssai_list;
  std::string access_type;
} allowed_nssai_t;

typedef struct mapping_of_snssai_s {
  snssai_t serving_snssai;
  snssai_t home_snssai;
} mapping_of_snssai_t;

typedef struct slice_info_for_registration_s {
  std::vector<subscribed_snssai_t> subscribed_nssai;
  std::vector<allowed_nssai_t> allowed_nssai_current_access;
  // allowed_nssai_other_access
  std::vector<snssai_t> sNssai_for_mapping;
  std::vector<snssai_t> requested_nssai;
  bool default_configured_snssai_ind;
  std::vector<mapping_of_snssai_t> mapping_of_nssai;
  bool request_mapping;
} slice_info_for_registration_t;

typedef struct configured_snssai_s {
  snssai_t configured_snssai;
  snssai_t mapped_home_snssai;
} configured_snssai_t;

typedef struct authorized_network_slice_info_s {
  std::vector<allowed_nssai_t> allowed_nssai_list;
  std::vector<configured_snssai_t> configured_nssai;
  std::string target_amf_set;
  std::vector<std::string> candidate_amf_list;
  std::vector<snssai_t> rejected_nssai_in_plmn;
  std::vector<snssai_t> rejected_nssai_in_ta;
  nsi_information_t nsi_information;
  // SupportedFeatures
  std::string nrf_amf_set;
  std::string nrf_amf_set_nf_mgt_uri;
  std::string nrf_amf_set_access_token_uri;

} authorized_network_slice_info_t;

#endif
