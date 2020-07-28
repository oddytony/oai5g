include_directories(${SRC_TOP_DIR}/../build/ext/spdlog/include)
include_directories(${SRC_TOP_DIR}/itti)
include_directories(${SRC_TOP_DIR}/itti/msgs)
include_directories(${SRC_TOP_DIR}/common)
include_directories(${SRC_TOP_DIR}/common/unicode)
include_directories(${SRC_TOP_DIR}/contexts)
include_directories(${SRC_TOP_DIR}/nas/ies)
include_directories(${SRC_TOP_DIR}/nas/common)
include_directories(${SRC_TOP_DIR}/nas/utils)
include_directories(${SRC_TOP_DIR}/ngap/libngap)
include_directories(${SRC_TOP_DIR}/ngap/ngapIEs)
include_directories(${SRC_TOP_DIR}/sctp)
include_directories(${SRC_TOP_DIR}/secu_algorithms/5gaka)
include_directories(${SRC_TOP_DIR}/secu_algorithms/nas_enc_int)
include_directories(${SRC_TOP_DIR}/utils)
include_directories(${SRC_TOP_DIR}/utils/bstr)

add_library (CONTEXTS STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/gNB_context.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/nas_context.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/pdu_session_context.cpp
)

