#include "amf_app.hpp"
#include "itti.hpp"
#include "ngap_app.hpp"
#include "amf_config.hpp"
#include "amf_n2.hpp"
#include "amf_n1.hpp"
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include "amf_statistics.hpp"

using namespace ngap;
using namespace amf;
using namespace config;

extern amf_app * amf_app_inst;
extern itti_mw * itti_inst;
amf_n2 * amf_n2_inst = nullptr;
amf_n1 * amf_n1_inst = nullptr;
extern amf_config amf_cfg;
extern statistics stacs;

void amf_app_task(void*);

amf_app::amf_app(const amf_config &amf_cfg){
  Logger::amf_app().startup("Creating amf application functionality layer");
  if(itti_inst->create_task(TASK_AMF_APP, amf_app_task, nullptr)){
    Logger::amf_app().error( "Cannot create task TASK_AMF_APP" );
    throw std::runtime_error( "Cannot create task TASK_AMF_APP" );
  }
  try{
    amf_n2_inst = new amf_n2(std::string(inet_ntoa(amf_cfg.n2.addr4)),amf_cfg.n2.port); 
  }catch(std::exception& e){
    Logger::amf_app().error( "Cannot create amf n2 interface: %s", e.what() );
    throw;
  }
  try{
    amf_n1_inst = new amf_n1();
  }catch(std::exception& e){
    Logger::amf_app().error( "Cannot create amf n1 interface: %s", e.what() );
  }
  timer_id_t tid = itti_inst->timer_setup(amf_cfg.statistics_interval,0,TASK_AMF_APP,TASK_AMF_APP_PERIODIC_STATISTICS,0);
  Logger::amf_app().startup( "Started timer(%d)", tid);
}

void amf_app::allRegistredModulesInit(const amf_modules & modules){
  Logger::amf_app().info("Initiating all registred modules");
}

void amf_app_task(void*){
  const task_id_t task_id = TASK_AMF_APP;
  itti_inst->notify_task_ready(task_id);
  do {
    std::shared_ptr<itti_msg> shared_msg = itti_inst->receive_msg(task_id);
    auto *msg = shared_msg.get();
    timer_id_t tid;
    switch(msg->msg_type){
      case TIME_OUT:
        if (itti_msg_timeout* to = dynamic_cast<itti_msg_timeout*>(msg)) {
          switch(to->arg1_user){
            case TASK_AMF_APP_PERIODIC_STATISTICS:
              tid = itti_inst->timer_setup(amf_cfg.statistics_interval,0,TASK_AMF_APP,TASK_AMF_APP_PERIODIC_STATISTICS,0);
              //Logger::amf_app().info("statistics(ready to be implemented)");
              stacs.display();
              break;
            default:
              Logger::amf_app().info( "no handler for timer(%d) with arg1_user(%d) ", to->timer_id, to->arg1_user);
          }
      }
      break;
      default:
        Logger::amf_app().info( "no handler for msg type %d", msg->msg_type);
    }
  }while(true);
}
