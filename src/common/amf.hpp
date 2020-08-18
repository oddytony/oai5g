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

/*! \file amf.hpp
 \brief
 \date 2020
 \email: contact@openairinterface.org
 */

#ifndef __AMF_HPP
#define __AMF_HPP

typedef struct {
  std::string mcc;
  std::string mnc;
  uint32_t tac;
} plmn_t;


typedef struct s_nssai  // section 28.4, TS23.003
{
  uint8_t sST;
  //uint32_t sD:24;
  std::string sD;
  s_nssai(const uint8_t &sst, const std::string sd)
      :
      sST(sst),
      sD(sd) {
  }
  s_nssai()
      :
      sST(),
      sD() {
  }
  s_nssai(const s_nssai &p)
      :
      sST(p.sST),
      sD(p.sD) {
  }
  bool operator==(const struct s_nssai &s) const {
    if ((s.sST == this->sST) && (s.sD.compare(this->sD) == 0)) {
      return true;
    } else {
      return false;
    }
  }

} snssai_t;




#endif

