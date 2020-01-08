#ifndef _AMF_CONFIG_H_
#define _AMF_CONFIG_H_

#include <arpa/inet.h>
#include <libconfig.h++>
#include <netinet/in.h>
#include <sys/socket.h>

#include <mutex>
#include <vector>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include "amf_config.hpp"
#include "thread_sched.hpp"

#define AMF_CONFIG_STRING_AMF_CONFIG                    "AMF"
#define AMF_CONFIG_STRING_PID_DIRECTORY                 "PID_DIRECTORY"
#define AMF_CONFIG_STRING_INSTANCE_ID                   "INSTANCE_ID"
#define AMF_CONFIG_STRING_STATISTICS_TIMER_INTERVAL     "STATISTICS_TIMER_INTERVAL"
#define AMF_CONFIG_STRING_INTERFACES                    "INTERFACES"
#define AMF_CONFIG_STRING_INTERFACE_NGAP_AMF            "NGAP_AMF"
#define AMF_CONFIG_STRING_INTERFACE_NAME                "INTERFACE_NAME"
#define AMF_CONFIG_STRING_IPV4_ADDRESS                  "IPV4_ADDRESS"
#define AMF_CONFIG_STRING_SCTP_PORT                     "SCTP_PORT"
#define AMF_CONFIG_STRING_PPID                          "PPID"

#define AMF_CONFIG_STRING_SCHED_PARAMS                  "SCHED_PARAMS"
#define AMF_CONFIG_STRING_THREAD_RD_CPU_ID              "CPU_ID"
#define AMF_CONFIG_STRING_THREAD_RD_SCHED_POLICY        "SCHED_POLICY"
#define AMF_CONFIG_STRING_THREAD_RD_SCHED_PRIORITY      "SCHED_PRIORITY"

#define AMF_CONFIG_STRING_AMF_NAME                      "AMF_NAME"
#define AMF_CONFIG_STRING_ServedGUAMIList               "ServedGUAMIList"
#define AMF_CONFIG_STRING_MCC                           "MCC"
#define AMF_CONFIG_STRING_MNC                           "MNC"
#define AMF_CONFIG_STRING_RegionID                      "RegionID"
#define AMF_CONFIG_STRING_AMFSetID                      "AMFSetID"
#define AMF_CONFIG_STRING_AMFPointer                    "AMFPointer"
#define AMF_CONFIG_STRING_RelativeAMFCapacity           "RelativeAMFCapacity"
#define AMF_CONFIG_STRING_PLMNSupportList               "PLMNSupportList"
#define AMF_CONFIG_STRING_SliceSupportList              "SliceSupportList"
#define AMF_CONFIG_STRING_SST                           "SST"
#define AMF_CONFIG_STRING_SD                            "SD"


using namespace libconfig;
using namespace std;

namespace config{

typedef struct interface_cfg_s {
  std::string     if_name;
  struct in_addr  addr4;
  struct in_addr  network4;
  struct in6_addr addr6;
  unsigned int    mtu;
  unsigned int    port;
  util::thread_sched_params thread_rd_sched_params;
} interface_cfg_t;

typedef struct itti_cfg_s {
  util::thread_sched_params itti_timer_sched_params;
  util::thread_sched_params sx_sched_params;
  util::thread_sched_params s5s8_sched_params;
  util::thread_sched_params pgw_app_sched_params;
  util::thread_sched_params async_cmd_sched_params;
} itti_cfg_t;

typedef struct guami_s{
  string mcc;
  string mnc;
  string regionID;
  string AmfSetID;
  string AmfPointer;
}guami_t;

typedef struct slice_s{
  string sST;
  string sD;
}slice_t;

typedef struct plmn_support_item_s{
  string mcc;
  string mnc;
  vector<slice_t> slice_list;
}plmn_item_t;

class amf_config{
public:
  amf_config();
  ~amf_config();
  int load(const std::string &config_file);
  int load_interface(const Setting& if_cfg, interface_cfg_t & cfg);
  int load_thread_sched_params(const libconfig::Setting& thread_sched_params_cfg, util::thread_sched_params& cfg);
  void display();
public:
  unsigned int                  instance;
  string                        pid_dir;
  interface_cfg_t               n2;
  itti_cfg_t                    itti;
  unsigned int                  statistics_interval;
  string                        AMF_Name;
  vector<guami_t>               guami_list;  
  unsigned int                  relativeAMFCapacity;
  vector<plmn_item_t>           plmn_list;

};






}







#endif
