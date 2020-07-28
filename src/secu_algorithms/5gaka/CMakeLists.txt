include_directories(${SRC_TOP_DIR}/../build/ext/spdlog/include)
include_directories(${SRC_TOP_DIR}/common)
include_directories(${SRC_TOP_DIR}/common/unicode)
include_directories(${SRC_TOP_DIR}/nas/ies)
include_directories(${SRC_TOP_DIR}/nas/common)
include_directories(${SRC_TOP_DIR}/ngap/libngap)
include_directories(${SRC_TOP_DIR}/secu_algorithms/5gaka)
include_directories(${SRC_TOP_DIR}/utils)
include_directories(${SRC_TOP_DIR}/utils/bstr)


add_library (AMF_SECU_5GAKA STATIC
  authentication_algorithms_with_5gaka.cpp
  rijndael.cpp
  sha256.cpp
 )

