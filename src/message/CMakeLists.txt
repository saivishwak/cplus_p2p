get_filename_component(PROJ_DIR ../../ ABSOLUTE)
set(Protobuf_USE_STATIC_LIBS ON)
list(APPEND CMAKE_PREFIX_PATH ${PROJ_DIR}/vendor/protobuf/.build)
find_package(Protobuf REQUIRED)
#include_directories(${Protobuf_INCLUDE_DIRS})
#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ../proto/Block.proto)

set(PROTOBUFF_INCLUDE ${PROJ_DIR}/vendor/protobuf/.build/include)
set(PROTOBUFF_LIB ${PROJ_DIR}/vendor/protobuf/.build/lib/libprotobuf.a)
include_directories(${PROJ_DIR}/vendor/jsoncpp/include ${PROJ_DIR}/vendor/spdlog/include ${PROTOBUFF_INCLUDE} ../proto/models)
add_library(message Message.cpp Message.hpp)
target_include_directories(message PUBLIC .)

target_link_libraries(message ${PROTOBUFF_LIB} "${PROJ_DIR}/vendor/jsoncpp/build/lib/libjsoncpp.a" "${PROJ_DIR}/vendor/spdlog/build/libspdlog.a")