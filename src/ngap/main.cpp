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

/*! \file main.cpp
 \brief
 \author  Keliang DU, BUPT
 \date 2020
 \email: contact@openairinterface.org
 */

#include <iostream>
#include <thread>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h> 
#include <unistd.h>

#include "logger.hpp"
#include "options.hpp"
#include "amf_config.hpp"
#include "ngap_app.hpp"

using namespace std;
using namespace config;
using namespace ngap;

amf_config amf_cfg;
ngap_app * ngap_inst = NULL;

int main(int argc, char **argv){
  srand (time(NULL));

  if(!Options::parse(argc, argv)){
    cout<<"Options::parse() failed"<<endl;
    return 1;
  }

  Logger::init( "amf" , Options::getlogStdout() , Options::getlogRotFilelog());
  Logger::amf_app().startup("Options parsed!");

  amf_cfg.load(Options::getlibconfigConfig());
  amf_cfg.display();

  ngap_inst = new ngap_app("10.103.238.20",38412);

  Logger::amf_app().debug("Initiating Done!");
  pause();
  return 0;
}
