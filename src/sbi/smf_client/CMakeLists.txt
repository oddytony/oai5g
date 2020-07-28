include_directories(${SRC_TOP_DIR}/../build/ext/spdlog/include)
include_directories(${SRC_TOP_DIR}/common)
include_directories(${SRC_TOP_DIR}/common/unicode)
include_directories(${SRC_TOP_DIR}/contexts)
include_directories(${SRC_TOP_DIR}/nas/common)
include_directories(${SRC_TOP_DIR}/utils)
include_directories(${SRC_TOP_DIR}/utils/bstr)
include_directories(${SRC_TOP_DIR}/sbi/smf_client)
include_directories(${SRC_TOP_DIR}/sbi/smf_client/api)
include_directories(${SRC_TOP_DIR}/sbi/smf_client/inputs)
include_directories(${SRC_TOP_DIR}/sbi/smf_client/model)

add_library (AMF_SBI_CLIENT STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/ApiClient.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ApiConfiguration.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ApiException.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/HttpContent.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/JsonBody.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ModelBase.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MultipartFormData.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Object.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/SMFClientApi.cpp
 )

