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

/*! \file
 \brief
 \author  Keliang DU, BUPT
 \date 2020
 \email: contact@openairinterface.org
 */

#include "UESecurityCapability.hpp"

#include "logger.hpp"
using namespace nas;

//------------------------------------------------------------------------------
UESecurityCapability::UESecurityCapability(uint8_t iei) {
  _iei      = iei;
  _5g_EASel = 0;
  _5g_IASel = 0;
  length    = 0;
}

//------------------------------------------------------------------------------
UESecurityCapability::UESecurityCapability() {
  _iei      = 0;
  _5g_EASel = 0;
  _5g_IASel = 0;
  length    = 0;
}

//------------------------------------------------------------------------------
UESecurityCapability::~UESecurityCapability() {}

//------------------------------------------------------------------------------
UESecurityCapability::UESecurityCapability(
    const uint8_t iei, uint8_t _5gg_EASel, uint8_t _5gg_IASel) {
  _iei      = iei;
  _5g_EASel = _5gg_EASel;
  _5g_IASel = _5gg_IASel;
  length    = 2;
}

//------------------------------------------------------------------------------
void UESecurityCapability::setEASel(uint8_t sel) {
  _5g_EASel = sel;
}

//------------------------------------------------------------------------------
void UESecurityCapability::setIASel(uint8_t sel) {
  _5g_IASel = sel;
}

//------------------------------------------------------------------------------
uint8_t UESecurityCapability::getEASel() {
  return _5g_EASel;
}

//------------------------------------------------------------------------------
uint8_t UESecurityCapability::getIASel() {
  return _5g_IASel;
}

//------------------------------------------------------------------------------
void UESecurityCapability::setLenght(uint8_t len) {
  if ((len > 0) && (len <= 4)) {
    length = len;
  } else {
    Logger::nas_mm().debug("Set UESecurityCapability Lenght faile %d", len);
    Logger::nas_mm().debug(
        "UESecurityCapability Lenght is set to the default value %d", length);
  }
}

//------------------------------------------------------------------------------
uint8_t UESecurityCapability::getLenght() {
  return length;
}

//------------------------------------------------------------------------------
int UESecurityCapability::encode2buffer(uint8_t* buf, int len) {
  Logger::nas_mm().debug("Encoding UESecurityCapability IEI 0x%x", _iei);
  if (len < length) {
    Logger::nas_mm().error("len is less than %d", length);
    return 0;
  }
  int encoded_size = 0;
  if (_iei) {
    *(buf + encoded_size) = _iei;
    encoded_size++;
    *(buf + encoded_size) = length;
    encoded_size++;
    *(buf + encoded_size) = _5g_EASel;
    encoded_size++;
    *(buf + encoded_size) = _5g_IASel;
    encoded_size++;
    if (length == 4) {
      *(buf + encoded_size) = 0xf0;
      encoded_size++;
      *(buf + encoded_size) = 0xf0;
      encoded_size++;
    }

  } else {
    *(buf + encoded_size) = length;
    encoded_size++;
    *(buf + encoded_size) = _5g_EASel;
    encoded_size++;
    *(buf + encoded_size) = _5g_IASel;
    encoded_size++;
    if (length == 4) {
      *(buf + encoded_size) = 0xf0;
      encoded_size++;
      *(buf + encoded_size) = 0xf0;
      encoded_size++;
    }
  }
  Logger::nas_mm().debug("encoded UESecurityCapability (len %d)", encoded_size);
  return encoded_size;
}

//------------------------------------------------------------------------------
int UESecurityCapability::decodefrombuffer(
    uint8_t* buf, int len, bool is_option) {
  Logger::nas_mm().debug("Decoding UESecurityCapability IEI 0x%x", *buf);
  int decoded_size = 0;
  if (is_option) {
    decoded_size++;
  }
  length = *(buf + decoded_size);
  decoded_size++;
  _5g_EASel = *(buf + decoded_size);
  decoded_size++;
  _5g_IASel = *(buf + decoded_size);
  decoded_size++;
  if (length >= 4) decoded_size += (length - 2);  // TODO: decoding EEA EIA
  Logger::nas_mm().debug(
      "UESecurityCapability (length %d) EA 0x%x,IA 0x%x", length, _5g_EASel,
      _5g_IASel);
  return decoded_size;
}
