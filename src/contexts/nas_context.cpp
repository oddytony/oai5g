#include "nas_context.hpp"

nas_context::nas_context(){
  is_imsi_present = false;
  is_auth_vectors_present = false;
  auts = NULL;
}

nas_context::~nas_context(){}
