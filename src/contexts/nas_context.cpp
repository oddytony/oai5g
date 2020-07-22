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

/*! \file nas_context.cpp
 \brief
 \author  Keliang DU, BUPT
 \date 2020
 \email: contact@openairinterface.org
 */

#include "nas_context.hpp"

nas_context::nas_context(){
  security_ctx = NULL;
  is_imsi_present = false;
  is_stacs_available = false;
  is_auth_vectors_present = false;
  is_specific_procedure_for_registration_running = false;
  is_specific_procedure_for_deregistration_running = false;
  is_specific_procedure_for_eCell_inactivity_running = false;
  is_common_procedure_for_authentication_running = false;
  is_common_procedure_for_identification_running = false;
  is_common_procedure_for_security_mode_control_running = false;
  is_common_procedure_for_nas_transport_running = false;
  auts = NULL;
}

nas_context::~nas_context(){}
