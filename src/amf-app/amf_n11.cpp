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

/*! \file amf_n11.cpp
 \brief
 \author  Keliang DU, BUPT, Tien-Thinh NGUYEN, EURECOM
 \date 2020
 \email: contact@openairinterface.org
 */

#include "amf_n11.hpp"

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "dynamic_memory_check.h"
#include "amf_n1.hpp"
#include "itti.hpp"
#include "itti_msg_amf_app.hpp"
#include "amf_config.hpp"
#include "nas_context.hpp"
#include "amf.hpp"
#include "3gpp_ts24501.hpp"
// For smf_client
#include "SmContextCreateData.h"
#include "SMContextsCollectionApi.h"
#include "ApiConfiguration.h"
#include "ApiClient.h"
#include "mime_parser.hpp"

using namespace oai::smf::model;
using namespace oai::smf::api;
using namespace web;
// Common features like URIs.
using namespace web::http;
// Common HTTP functionality
using namespace web::http::client;

using namespace config;
using namespace amf_application;
extern itti_mw *itti_inst;
extern amf_config amf_cfg;
extern amf_n11 *amf_n11_inst;

extern amf_n1 *amf_n1_inst;

extern void msg_str_2_msg_hex(std::string msg, bstring &b);
extern void convert_string_2_hex(std::string &input, std::string &output);
extern void print_buffer(const std::string app, const std::string commit, uint8_t *buf, int len);
extern bool multipart_parser(std::string input, std::string &jsonData, std::string &n1sm, std::string &n2sm);
extern unsigned char* format_string_as_hex(std::string str);
extern char* bstring2charString(bstring b);

//------------------------------------------------------------------------------
std::size_t callback(const char *in, std::size_t size, std::size_t num, std::string *out) {
  const std::size_t totalBytes(size * num);
  out->append(in, totalBytes);
  return totalBytes;
}

//------------------------------------------------------------------------------
void octet_stream_2_hex_stream(uint8_t *buf, int len, std::string &out) {
  out = "";
  char *tmp = (char*) calloc(1, 2 * len * sizeof(uint8_t) + 1);
  for (int i = 0; i < len; i++) {
    sprintf(tmp + 2 * i, "%02x", buf[i]);
  }
  tmp[2 * len] = '\0';
  out = tmp;
  printf("n1sm buffer: %s\n", out.c_str());
}

/****************************************************/
/**  used to run NF(s) consumer, like smf_client ****/
/***************************************************/

void amf_n11_task(void*);
//------------------------------------------------------------------------------
void amf_n11_task(void*) {
  const task_id_t task_id = TASK_AMF_N11;
  itti_inst->notify_task_ready(task_id);
  do {
    std::shared_ptr<itti_msg> shared_msg = itti_inst->receive_msg(task_id);
    auto *msg = shared_msg.get();
    switch (msg->msg_type) {
      case SMF_SERVICES_CONSUMER: {
        Logger::amf_n1().info("Running SMF_SERVICES_CONSUMER");
        itti_smf_services_consumer *m = dynamic_cast<itti_smf_services_consumer*>(msg);
        amf_n11_inst->handle_itti_message(ref(*m));
      }
        break;
      case NSMF_PDU_SESSION_UPDATE_SM_CTX: {
        Logger::amf_n1().info("Receive Nsmf_PDUSessionUpdateSMContext, handling ...");
        itti_nsmf_pdusession_update_sm_context *m = dynamic_cast<itti_nsmf_pdusession_update_sm_context*>(msg);
        amf_n11_inst->handle_itti_message(ref(*m));
      }
        break;
      case PDU_SESS_RES_SET_RESP: {
        Logger::amf_n1().info("Receive PDU Session Resource Setup Response, handling ...");
        itti_pdu_session_resource_setup_response *m = dynamic_cast<itti_pdu_session_resource_setup_response*>(msg);
        amf_n11_inst->handle_itti_message(ref(*m));
      }
        break;
    }
  } while (true);
}

//------------------------------------------------------------------------------
amf_n11::amf_n11() {
  if (itti_inst->create_task(TASK_AMF_N11, amf_n11_task, nullptr)) {
    Logger::amf_n11().error("Cannot create task TASK_AMF_N1");
    throw std::runtime_error("Cannot create task TASK_AMF_N1");
  }
  Logger::amf_n1().startup("Started");
  Logger::amf_n1().debug("Construct amf_n1 successfully");
}

//------------------------------------------------------------------------------
amf_n11::~amf_n11() {
}

// itti message handlers
//------------------------------------------------------------------------------
void amf_n11::handle_itti_message(itti_pdu_session_resource_setup_response &itti_msg) {
}

//------------------------------------------------------------------------------
void amf_n11::handle_itti_message(itti_nsmf_pdusession_update_sm_context &itti_msg) {
  std::string supi = pduid2supi.at(itti_msg.pdu_session_id);
  Logger::amf_n11().debug("Found SUPI %s with PDU Session ID %d", supi.c_str(), itti_msg.pdu_session_id);
  std::shared_ptr<pdu_session_context> psc;
  if (is_supi_to_pdu_ctx(supi)) {
    psc = supi_to_pdu_ctx(supi);
  } else {
    Logger::amf_n11().error("Could not find psu_session_context with SUPI %s, Failed", supi.c_str());
    return;
  }
  std::string smf_addr;
  if (!psc.get()->smf_available) {
    if (!smf_selection_from_configuration(smf_addr)) {
      Logger::amf_n11().error("No SMF candidate is available");
      return;
    }
  } else {
    smf_selection_from_context(smf_addr);
  }

  std::string smf_ip_addr, remote_uri;

  //remove http port from the URI if existed
  std::size_t found_port = smf_addr.find(":");
  if (found_port != std::string::npos)
    smf_ip_addr = smf_addr.substr(0, found_port - 1);
  else
    smf_ip_addr = smf_addr;

  std::size_t found = psc.get()->smf_context_location.find(smf_ip_addr);
  if (found != std::string::npos)
    remote_uri = psc.get()->smf_context_location + "/modify";
  else
    remote_uri = smf_addr + psc.get()->smf_context_location + "/modify";

  Logger::amf_n11().debug("SMF URI: %s", remote_uri.c_str());

  nlohmann::json pdu_session_update_request = {};
  pdu_session_update_request["n2SmInfoType"] = "PDU_RES_SETUP_RSP";
  pdu_session_update_request["n2SmInfo"]["contentId"] = "n2SmMsg";
  std::string json_part = pdu_session_update_request.dump();
  std::string n2SmMsg;
  octet_stream_2_hex_stream((uint8_t*) bdata(itti_msg.n2sm), blength(itti_msg.n2sm), n2SmMsg);
  curl_http_client(remote_uri, json_part, "", n2SmMsg, supi, itti_msg.pdu_session_id);
}

//------------------------------------------------------------------------------
void amf_n11::handle_itti_message(itti_smf_services_consumer &smf) {
  std::shared_ptr<nas_context> nc;
  nc = amf_n1_inst->amf_ue_id_2_nas_context(smf.amf_ue_ngap_id);
  std::string supi = "imsi-" + nc.get()->imsi;

  std::shared_ptr<pdu_session_context> psc;
  if (is_supi_to_pdu_ctx(supi)) {
    psc = supi_to_pdu_ctx(supi);
  } else {
    psc = std::shared_ptr < pdu_session_context > (new pdu_session_context());
    set_supi_to_pdu_ctx(supi, psc);
  }

  pduid2supi[smf.pdu_sess_id] = supi;

  psc.get()->amf_ue_ngap_id = nc.get()->amf_ue_ngap_id;
  psc.get()->ran_ue_ngap_id = nc.get()->ran_ue_ngap_id;
  psc.get()->req_type = smf.req_type;
  psc.get()->pdu_session_id = smf.pdu_sess_id;
  psc.get()->snssai.sST = smf.snssai.sST;
  psc.get()->snssai.sD = smf.snssai.sD;
  psc.get()->plmn.mcc = smf.plmn.mcc;
  psc.get()->plmn.mnc = smf.plmn.mnc;

  //parse binary dnn and store
  std::string dnn = "default";
  if ((smf.dnn != nullptr) && (blength(smf.dnn) > 0)) {
    char *tmp = bstring2charString(smf.dnn);
    dnn = tmp;
    free(tmp);
    tmp = nullptr;
  }

  Logger::amf_n11().debug("Requested DNN: %s", dnn.c_str());
  psc.get()->dnn = dnn;

  std::string smf_addr;
  if (!psc.get()->smf_available) {
    if (!smf_selection_from_configuration(smf_addr)) {
      Logger::amf_n11().error("No candidate for SMF is available");
      return;
    }
  } else {
    smf_selection_from_context(smf_addr);
  }

  switch (smf.req_type & 0x07) {
    case PDU_SESSION_INITIAL_REQUEST: {
      handle_pdu_session_initial_request(supi, psc, smf_addr, smf.sm_msg, dnn);
    }
      break;
    case EXISTING_PDU_SESSION: {
      //TODO:
    }
      break;
    case PDU_SESSION_MODIFICATION_REQUEST: {
      //TODO:
    }
      break;
  }
}

//------------------------------------------------------------------------------
void amf_n11::handle_pdu_session_initial_request(std::string supi, std::shared_ptr<pdu_session_context> psc, std::string smf_addr, bstring sm_msg, std::string dnn) {
  //TODO: Remove hardcoded values
  std::string remote_uri = smf_addr + "/nsmf-pdusession/v1/sm-contexts";  //TODO
  nlohmann::json pdu_session_establishment_request;
  pdu_session_establishment_request["supi"] = supi.c_str();
  pdu_session_establishment_request["pei"] = "imei-200000000000001";
  pdu_session_establishment_request["gpsi"] = "msisdn-200000000001";
  pdu_session_establishment_request["dnn"] = dnn.c_str();
  pdu_session_establishment_request["sNssai"]["sst"] = psc.get()->snssai.sST;
  pdu_session_establishment_request["sNssai"]["sd"] = psc.get()->snssai.sD;
  pdu_session_establishment_request["pduSessionId"] = psc.get()->pdu_session_id;
  pdu_session_establishment_request["requestType"] = "INITIAL_REQUEST";  //TODO: from SM_MSG
  pdu_session_establishment_request["servingNfId"] = "servingNfId";
  pdu_session_establishment_request["servingNetwork"]["mcc"] = psc.get()->plmn.mcc;
  pdu_session_establishment_request["servingNetwork"]["mnc"] = psc.get()->plmn.mnc;
  pdu_session_establishment_request["anType"] = "3GPP_ACCESS";  //TODO
  pdu_session_establishment_request["smContextStatusUri"] = "smContextStatusUri";

  pdu_session_establishment_request["n1MessageContainer"]["n1MessageClass"] = "SM";
  pdu_session_establishment_request["n1MessageContainer"]["n1MessageContent"]["contentId"] = "n1SmMsg";

  std::string json_part = pdu_session_establishment_request.dump();
  std::string n1SmMsg;
  octet_stream_2_hex_stream((uint8_t*) bdata(sm_msg), blength(sm_msg), n1SmMsg);
  curl_http_client(remote_uri, json_part, n1SmMsg, "", supi, psc.get()->pdu_session_id);
}

//Context management functions
//------------------------------------------------------------------------------
bool amf_n11::is_supi_to_pdu_ctx(const std::string &supi) const {
  std::shared_lock lock(m_supi2pdu);
  return bool { supi2pdu.count(supi) > 0 };
}

std::shared_ptr<pdu_session_context> amf_n11::supi_to_pdu_ctx(const std::string &supi) const {
  std::shared_lock lock(m_supi2pdu);
  return supi2pdu.at(supi);
}

//------------------------------------------------------------------------------
void amf_n11::set_supi_to_pdu_ctx(const string &supi, std::shared_ptr<pdu_session_context> psc) {
  std::shared_lock lock(m_supi2pdu);
  supi2pdu[supi] = psc;
}

//SMF selection
//------------------------------------------------------------------------------
bool amf_n11::smf_selection_from_configuration(std::string &smf_addr) {
  for (int i = 0; i < amf_cfg.smf_pool.size(); i++) {
    if (amf_cfg.smf_pool[i].selected) {
      //smf_addr = "http://" + amf_cfg.smf_pool[i].ipv4 + ":" + amf_cfg.smf_pool[i].port;
      smf_addr = amf_cfg.smf_pool[i].ipv4 + ":" + amf_cfg.smf_pool[i].port;
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------------------------
bool amf_n11::smf_selection_from_context(std::string &smf_addr) {
  //TODO:
}

// handlers for smf client response
//------------------------------------------------------------------------------
void amf_n11::handle_post_sm_context_response_error_400() {
}

//------------------------------------------------------------------------------
void amf_n11::handle_post_sm_context_response_error(long code, std::string cause, bstring n1sm, std::string supi, uint8_t pdu_session_id) {
  print_buffer("amf_n11", "n1 sm", (uint8_t*) bdata(n1sm), blength(n1sm));
  itti_n1n2_message_transfer_request *itti_msg = new itti_n1n2_message_transfer_request(TASK_AMF_N11, TASK_AMF_APP);
  itti_msg->n1sm = n1sm;
  itti_msg->is_n2sm_set = false;
  itti_msg->supi = supi;
  itti_msg->pdu_session_id = pdu_session_id;
  std::shared_ptr<itti_n1n2_message_transfer_request> i = std::shared_ptr < itti_n1n2_message_transfer_request > (itti_msg);
  int ret = itti_inst->send_msg(i);
  if (0 != ret) {
    Logger::amf_n1().error("Could not send ITTI message %s to task TASK_AMF_APP", i->get_msg_name());
  }
}

//------------------------------------------------------------------------------
void amf_n11::curl_http_client(std::string remoteUri, std::string jsonData, std::string n1SmMsg, std::string n2SmMsg, std::string supi, uint8_t pdu_session_id) {
  Logger::amf_n11().debug("Call SMF service: %s", remoteUri.c_str());

  std::shared_ptr<pdu_session_context> psc;
  if (is_supi_to_pdu_ctx(supi)) {
    psc = supi_to_pdu_ctx(supi);
  } else {
    Logger::amf_n11().warn("PDU Session context for SUPI %s doesn't exit!", supi.c_str());
    //TODO:
  }

  mime_parser parser = { };
  std::string body;

  if ((n1SmMsg.size() > 0) and (n2SmMsg.size() > 0)) {
    //prepare the body content for Curl
    parser.create_multipart_related_content(body, jsonData, CURL_MIME_BOUNDARY, n1SmMsg, n2SmMsg);
  } else if (n1SmMsg.size() > 0) {  //only N1 content
    //prepare the body content for Curl
    parser.create_multipart_related_content(body, jsonData, CURL_MIME_BOUNDARY, n1SmMsg, multipart_related_content_part_e::NAS);
  } else if (n2SmMsg.size() > 0) {  //only N2 content
    //prepare the body content for Curl
    parser.create_multipart_related_content(body, jsonData, CURL_MIME_BOUNDARY, n2SmMsg, multipart_related_content_part_e::NGAP);
  }

  Logger::amf_n11().debug("Send HTTP message to SMF with body %s", body.c_str());

  uint32_t str_len = body.length();
  char *body_data = (char*) malloc(str_len + 1);
  memset(body_data, 0, str_len + 1);
  memcpy((void*) body_data, (void*) body.c_str(), str_len);

  curl_global_init (CURL_GLOBAL_ALL);
  CURL *curl = curl_easy_init();

  if (curl) {
    CURLcode res = { };
    struct curl_slist *headers = nullptr;

    std::string content_type = "content-type: multipart/related; boundary=" + std::string(CURL_MIME_BOUNDARY);
    headers = curl_slist_append(headers, content_type.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, remoteUri.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, SMF_CURL_TIMEOUT_MS);
    curl_easy_setopt(curl, CURLOPT_INTERFACE, amf_cfg.n11.if_name.c_str());

    // Response information.
    long httpCode = { 0 };
    std::unique_ptr < std::string > httpData(new std::string());
    std::unique_ptr < std::string > httpHeaderData(new std::string());

    // Hook up data handling function.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, httpHeaderData.get());

    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.length());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body_data);

    res = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

    //get cause from the response
    std::string response = *httpData.get();
    std::string json_data_response = "";
    std::string n1sm = "";
    std::string n2sm = "";
    bool is_response_ok = true;
    Logger::amf_n11().debug("Get response with httpcode (%d)", httpCode);
    if (httpCode == 0) {
      Logger::amf_n11().error("Cannot get response when calling %s", remoteUri.c_str());
      //free curl before returning
      curl_slist_free_all(headers);
      curl_easy_cleanup(curl);
      return;
    }

    if (httpCode != 200 && httpCode != 201 && httpCode != 204) {
      is_response_ok = false;
      if (response.size() < 1) {
        Logger::amf_n11().error("There's no content in the response");
        //TODO: send context response error
        return;
      }
      if (!(multipart_parser(response, json_data_response, n1sm, n2sm))) {
        Logger::amf_n11().error("Could not get N1/N2 content from the response");
        //TODO:
      }
    } else {
      //store location of the created context
      std::string header_response = *httpHeaderData.get();
      std::string CRLF = "\r\n";
      std::size_t location_pos = header_response.find("Location");
      std::size_t crlf_pos = header_response.find(CRLF, location_pos);
      std::string location = header_response.substr(location_pos + 10, crlf_pos - (location_pos + 10));
      Logger::amf_n11().info("Location of the SMF context created: %s", location.c_str());
      psc.get()->smf_context_location = location;
    }

    nlohmann::json response_data = { };
    bstring n1sm_hex;

    if (!is_response_ok) {
      try {
        response_data = nlohmann::json::parse(json_data_response);
      } catch (nlohmann::json::exception &e) {
        Logger::amf_n11().warn("Could not get Json content from the response");
        //Set the default Cause
        response_data["error"]["cause"] = "504 Gateway Timeout";
      }

      Logger::amf_n11().debug("Get response with jsonData: %s", json_data_response.c_str());
      msg_str_2_msg_hex(n1sm.substr(0, n1sm.length() - 2), n1sm_hex);  //pdu session establishment reject bugs from SMF
      print_buffer("amf_n11", "Get response with n1sm:", (uint8_t*) bdata(n1sm_hex), blength(n1sm_hex));

      std::string cause = response_data["error"]["cause"];
      Logger::amf_n11().error("Call Network Function services failure");
      Logger::amf_n11().debug("Cause value: %s", cause.c_str());
      if (!cause.compare("DNN_DENIED"))
        handle_post_sm_context_response_error(httpCode, cause, n1sm_hex, supi, pdu_session_id);
    }
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();
  if (body_data != nullptr) {
    free(body_data);
    body_data = NULL;
  }

}
