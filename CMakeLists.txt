cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_COMPILER "g++")
set (CMAKE_CXX_STANDARD 17)

project(bitfab LANGUAGES CXX VERSION 1.0)

include(CTest)
enable_testing()

add_subdirectory(./src/net)
add_subdirectory(./src/db)
add_subdirectory(./src/message)
add_subdirectory(./src/utils)
add_subdirectory(./src/http)
add_subdirectory(./vendor/jsoncpp)
add_subdirectory(./vendor/spdlog)

set(CMAKE_CXX_FLAGS "-pthread -DBUILD_STATIC_LIBS=ON")
set(Protobuf_USE_STATIC_LIBS ON)
list(APPEND CMAKE_PREFIX_PATH ./vendor/protobuf/.build)
set(PROTOBUFF_INCLUDE ./vendor/protobuf/.build/include)
find_package(Protobuf REQUIRED)
#include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${PROTOBUFF_INCLUDE})

file(GLOB PROTO_CC "./src/proto/models/*.cc")
file(GLOB PROTO_H "./src/proto/models/*.h")

#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ./src/proto/Block.proto PROTOC_OUT_DIR /Users/saivishwak.korimerla/Desktop/blazeCoinC++/src/proto/models)
# foreach(file ${PROTO_DEF})    
#     if(EXISTS ${file})
#         MESSAGE("**** GENERATING PROTOBUFF ******")
#         protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS "${file}" PROTOC_OUT_DIR /Users/saivishwak.korimerla/Desktop/blazeCoinC++/src/proto/models)
#     else()
#         MESSAGE("**** PROTOBUFF DOES NOT EXIST ****")
#     endif()
# endforeach()

# ${PROTO_SRCS} ${PROTO_HDRS}
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)
add_executable(bitfab ./src/main.cpp ${PROTO_CC} ${PROTO_H})

include_directories(./vendor/jsoncpp/include ./vendor/spdlog/include)
target_link_libraries(${PROJECT_NAME} net db message http)
#target_include_directories(db PUBLIC
                        #   "${PROJECT_BINARY_DIR}"
                        #   "${PROJECT_SOURCE_DIR}/db"
                        #   )

include(CPack)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})