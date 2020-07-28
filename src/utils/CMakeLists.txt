include_directories(${SRC_TOP_DIR}/../build/ext/spdlog/include)
include_directories(${SRC_TOP_DIR}/common)
include_directories(${SRC_TOP_DIR}/common/unicode)
include_directories(${SRC_TOP_DIR}/nas/common)
include_directories(${SRC_TOP_DIR}/utils)
include_directories(${SRC_TOP_DIR}/utils/bstr)

add_library (AMF_UTILS STATIC
 ${CMAKE_CURRENT_SOURCE_DIR}/backtrace.c
 ${CMAKE_CURRENT_SOURCE_DIR}/conversions.c
 ${CMAKE_CURRENT_SOURCE_DIR}/hex_string_convert.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/http_multi_parser.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/if.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/string.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/thread_sched.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/mime_parser.cpp
 )

