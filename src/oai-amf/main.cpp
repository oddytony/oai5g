#include <iostream>
#include <thread>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h> 
#include <unistd.h>

#include "AMFApiServer.hpp"
#include "pistache/endpoint.h"
#include "pistache/http.h"
#include "pistache/router.h"

#include "logger.hpp"
#include "options.hpp"
#include "amf_config.hpp"
#include "ngap_app.hpp"
#include "itti.hpp"
#include "amf_app.hpp"
#include "amf_module_from_config.hpp"
#include "amf_statistics.hpp"

#include "SMFClientApi.hpp"
#include "test.hpp"
#include "smf-client.hpp"

#include <string>
#include <cstring>
#include "normalizer.hh"

extern void hexStr2Byte(const char *src, unsigned char *dest, int len);
extern void print_buffer(const std::string app, const std::string commit, uint8_t *buf, int len);
extern void ue_gnb_simulator();

using namespace std;
using namespace config;
//using namespace ngap;
using namespace amf_application;

amf_config amf_cfg;
amf_modules modules;
//ngap_app * ngap_inst = NULL;
itti_mw *itti_inst = nullptr;
amf_app *amf_app_inst = nullptr;
statistics stacs;

//------------------------------------------------------------------------------
int main(int argc, char **argv) {
  srand (time(NULL));

if  (!Options::parse(argc, argv)) {
    cout<<"Options::parse() failed"<<endl;
    return 1;
  }

  Logger::init( "AMF" , Options::getlogStdout() , Options::getlogRotFilelog());
  Logger::amf_app().startup("Options parsed!");

  amf_cfg.load(Options::getlibconfigConfig());
  amf_cfg.display();
  modules.load(Options::getlibconfigConfig());
  modules.display();

  itti_inst = new itti_mw();
  itti_inst->start(amf_cfg.itti.itti_timer_sched_params);
  //itti_inst->start();

  amf_app_inst = new amf_app(amf_cfg);
  amf_app_inst->allRegistredModulesInit(modules);

  Logger::amf_app().debug("Initiating AMF server endpoints");
  Pistache::Address addr(std::string(inet_ntoa (*((struct in_addr *)&amf_cfg.n2.addr4))) , Pistache::Port(8282));
  AMFApiServer amfApiServer(addr, amf_app_inst);
  amfApiServer.init(2);
  std::thread amf_api_manager(&AMFApiServer::start, amfApiServer);

  Logger::amf_app().debug("Initiating Done!");
  pause();
  return 0;
}
