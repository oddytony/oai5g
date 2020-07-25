include_directories(${SRC_TOP_DIR}/itti)
include_directories(${SRC_TOP_DIR}/itti/msgs)
file(GLOB ITTI_SRC 
  ${SRC_TOP_DIR}/itti/itti.cpp
  ${SRC_TOP_DIR}/itti/itti_msg.cpp
)
