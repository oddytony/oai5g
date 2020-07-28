include_directories(${SRC_TOP_DIR}/../build/ext/spdlog/include)
include_directories(${SRC_TOP_DIR}/common)
include_directories(${SRC_TOP_DIR}/common/unicode)
include_directories(${SRC_TOP_DIR}/nas/common)
include_directories(${SRC_TOP_DIR}/sctp)
include_directories(${SRC_TOP_DIR}/utils)
include_directories(${SRC_TOP_DIR}/utils/bstr)

add_library (AMF_SCTP STATIC
${CMAKE_CURRENT_SOURCE_DIR}/sctp_server.cpp
 )

