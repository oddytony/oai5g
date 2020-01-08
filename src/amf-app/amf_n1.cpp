#include "amf_n1.hpp"
#include "itti.hpp"
#include "logger.hpp"

using namespace amf;

extern itti_mw * itti_inst;

void amf_n1_task(void*);
void amf_n1_task(void*){
  const task_id_t task_id = TASK_AMF_N1;
  itti_inst->notify_task_ready(task_id);
  do{
    std::shared_ptr<itti_msg> shared_msg = itti_inst->receive_msg(task_id);
    auto *msg = shared_msg.get();
    switch(msg->msg_type){
      default:
        Logger::task_amf_n1().error("no handler for msg type %d",msg->msg_type);
    }
  }while(true);
}



amf_n1::amf_n1(){
  if(itti_inst->create_task(TASK_AMF_N1, amf_n1_task, nullptr) ) {
    Logger::amf_n1().error( "Cannot create task TASK_AMF_N1" );
    throw std::runtime_error( "Cannot create task TASK_AMF_N1" );
  }
  Logger::task_amf_n1().startup( "Started" );
  Logger::task_amf_n1().debug("construct amf_n1 successfully");
}
amf_n1::~amf_n1(){}
