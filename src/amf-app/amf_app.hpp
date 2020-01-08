#ifndef _AMF_APP_H_
#define _AMF_APP_H_

#include <map>
#include <set>
#include <shared_mutex>
#include <string>
#include <thread>
#include "amf_config.hpp"
#include "amf_module_from_config.hpp"

using namespace config;

namespace amf{

#define TASK_AMF_APP_PERIODIC_STATISTICS (0)

class amf_app{
public:
  explicit amf_app(const amf_config &amf_cfg);
  amf_app(amf_app const&) = delete;
  void operator=(amf_app const&)     = delete;
  void allRegistredModulesInit(const amf_modules & modules);
private:
};



}













#endif
