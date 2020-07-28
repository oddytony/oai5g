set(AMF_API_SERVER_DIR "${SRC_TOP_DIR}/sbi/amf_server")

include_directories(${SRC_TOP_DIR}/../build/ext/spdlog/include)
include_directories(${SRC_TOP_DIR}/amf-app)
include_directories(${SRC_TOP_DIR}/itti)
include_directories(${SRC_TOP_DIR}/itti/msgs)
include_directories(${SRC_TOP_DIR}/common)
include_directories(${SRC_TOP_DIR}/common/unicode)
include_directories(${SRC_TOP_DIR}/contexts)
include_directories(${SRC_TOP_DIR}/nas/common)
include_directories(${SRC_TOP_DIR}/ngap/libngap)
include_directories(${SRC_TOP_DIR}/ngap/ngapIEs)
include_directories(${SRC_TOP_DIR}/secu_algorithms/5gaka)
include_directories(${SRC_TOP_DIR}/secu_algorithms/nas_enc_int)
include_directories(${SRC_TOP_DIR}/utils)
include_directories(${SRC_TOP_DIR}/utils/bstr)
include_directories(${SRC_TOP_DIR}/sbi/amf_server)
include_directories(${SRC_TOP_DIR}/sbi/amf_server/api)
include_directories(${SRC_TOP_DIR}/sbi/amf_server/impl)
include_directories(${SRC_TOP_DIR}/sbi/amf_server/model)

file(GLOB AMF_API_SERVER_src_files
    ${AMF_API_SERVER_DIR}/AMFApiServer.cpp
    ${AMF_API_SERVER_DIR}/model/*.cpp
    ${AMF_API_SERVER_DIR}/api/*.cpp
    ${AMF_API_SERVER_DIR}/impl/*.cpp
)
 
add_library(AMF_SBI_SERVER STATIC
           ${AMF_API_SERVER_src_files})
                      

