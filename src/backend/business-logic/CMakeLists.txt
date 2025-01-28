cmake_minimum_required(VERSION 3.18)

project(SecVault VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)
include_directories(src)
include_directories(proto)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(fmt REQUIRED)
find_package(protobuf REQUIRED)
find_package(gRPC REQUIRED)

set(SOURCES
  src/main.cc

  src/core/token.cc
  src/core/server/bl_server.cc
  src/core/server/secret_management_service.cc

  proto/secret_management.grpc.pb.cc
  proto/secret_management.pb.cc
)

set(HEADERS
  src/core/token.h
  src/core/server/bl_server.h
  src/core/server/secret_management_service.h

  proto/secret_management.grpc.pb.h
  proto/secret_management.pb.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} fmt::fmt grpc::grpc protobuf::protobuf abseil::abseil)
