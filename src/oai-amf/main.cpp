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
#include "itti.hpp"
#include "amf_app.hpp"
#include "amf_module_from_config.hpp"
#include "amf_statistics.hpp"

using namespace std;
using namespace config;
//using namespace ngap;
using namespace amf;

amf_config amf_cfg;
amf_modules modules;
//ngap_app * ngap_inst = NULL;
itti_mw *itti_inst = nullptr;
amf_app *amf_app_inst = nullptr;
statistics stacs;


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
  modules.load(Options::getlibconfigConfig());
  modules.display();
  
  itti_inst = new itti_mw();
  itti_inst->start(amf_cfg.itti.itti_timer_sched_params);
  //itti_inst->start();

  amf_app_inst = new amf_app(amf_cfg);
  amf_app_inst->allRegistredModulesInit(modules);

  Logger::amf_app().debug("Initiating Done!");
  pause();
  return 0;
}
