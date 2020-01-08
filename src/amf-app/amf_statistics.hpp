#ifndef _STATISTICS_H_
#define _STATISTICS_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

class statistics{
public:
  void display();
  statistics();
  ~statistics();
private:
  uint32_t        gNB_connected;
  uint32_t        UE_connected;
  uint32_t        UE_registred;
  //uint32_t        system_pdu_sessions;


};








#endif
