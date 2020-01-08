#include "amf_statistics.hpp"
#include "logger.hpp"
#include <iostream>
using namespace std;


void statistics::display(){
  cout<<endl;
  Logger::amf_app().info("--------------------------------------------------");
  Logger::amf_app().info("| connected gNBs | connected UEs | registred UEs |");
  Logger::amf_app().info("--------------------------------------------------");
  Logger::amf_app().info("|       %d       |       %d      |        %d     |",gNB_connected,UE_connected,UE_registred);
  Logger::amf_app().info("--------------------------------------------------");
}

statistics::statistics(){
  gNB_connected = 0;
  UE_connected = 0;
  UE_registred = 0;
}

statistics::~statistics(){}
