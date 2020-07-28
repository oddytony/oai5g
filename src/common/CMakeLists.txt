include_directories(${SRC_TOP_DIR}/common)
include_directories(${SRC_TOP_DIR}/../build/ext/spdlog/include)
include_directories(${SRC_TOP_DIR}/common/unicode)
file(GLOB COMMON_SRC ${SRC_TOP_DIR}/common/conversions.cpp)

add_library(3GPP_COMMON_TYPES STATIC
  ${SRC_TOP_DIR}/common/logger.cpp
  ${SRC_TOP_DIR}/common/conversions.cpp
)
