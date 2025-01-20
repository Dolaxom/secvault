cmake_minimum_required(VERSION 3.18)

project(SecVault VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
include_directories(src)
include_directories(proto)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(fmt REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cc" "${CMAKE_SOURCE_DIR}/src/**/*.cc")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} fmt::fmt gRPC::grpc++ protobuf::libprotobuf)
