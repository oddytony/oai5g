#ifndef _AMF_NAS_CONTEXT_H_
#define _AMF_NAS_CONTEXT_H_

#include <stdint.h>
#include "security_def.hpp"
#include "authentication_algorithms_with_5gaka.hpp"
#include <string>
#include "nas_security_context.hpp"
#include "ies/NSSAI.hpp"

class nas_context{
public:
  nas_context();
  ~nas_context();
public:
  bool             ctx_avaliability_ind;
  long             amf_ue_ngap_id;
  uint32_t         ran_ue_ngap_id;

/************ parameters from Registration request *************/ 
  uint8_t          registration_type:3;
  bool             follow_on_req_pending_ind;
  uint8_t          ngKsi:4;
  //mobility identity: imsi, supi, 5g-guti, etc
  std::string           imsi;
  uint8_t          mmCapability;
  uint8_t          ueSecurityCapEnc;
  uint8_t          ueSecurityCapInt;
  std::vector<nas::SNSSAI_t>    requestedNssai;
  std::string           serving_network;
  uint8_t              *auts;
/************ NAS EP(s) ****************/ 
  bool             is_specific_procedure_for_registration_running;
  bool             is_specific_procedure_for_deregistration_running;
  bool             is_specific_procedure_for_eCell_inactivity_running;
  bool             is_common_procedure_for_authentication_running;
  bool             is_common_procedure_for_identification_running;
  bool             is_common_procedure_for_security_mode_control_running;
  bool             is_common_procedure_for_nas_transport_running;
/************ security related ***********/
#define MAX_5GS_AUTH_VECTORS          1
  auc_vector_t    _vector[MAX_5GS_AUTH_VECTORS];/* 5GS authentication vector */ 
  _5G_HE_AV_t     _5g_he_av[MAX_5GS_AUTH_VECTORS];//generated by UDM 
  _5G_AV_t        _5g_av[MAX_5GS_AUTH_VECTORS];//generated by ausf
  uint8_t         kamf[MAX_5GS_AUTH_VECTORS][32];
  security_context_t _security;

  nas_secu_ctx    *security_ctx;

  bool             is_current_security_avaliable;

  int              registration_attempt_counter;//used to limit the subsequently reject registration attempts(clause 5.5.1.2.7/5.5.1.3.7, 3gpp ts24.501) 
/**************** parameters present? ****************/
  bool             is_imsi_present;
  bool             is_5g_guti_present;
  bool             is_auth_vectors_present;

};















#endif
