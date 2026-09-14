cmake_minimum_required(VERSION 3.16)

project(learning_arduino_q1 LANGUAGES C CXX)

set(CMAKE_IGNORE_PATH 
    "/usr/local/lib" 
    "/usr/local/include"
    "/usr/lib/x86_64-linux-gnu"
    "/usr/lib/x86_64-linux-gnu/cmake"
    "/usr/include/x86_64-linux-gnu"
)
set(CMAKE_PREFIX_PATH "/usr/lib/aarch64-linux-gnu/cmake" ${CMAKE_PREFIX_PATH})

# Add this exact line here:
link_directories("/usr/lib/aarch64-linux-gnu")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(findGRPC)
include(generate_proto)
include(arduino_cli_targets)
include(format)

add_arduino_cli_compile_target(src_mcu/bridge)
add_arduino_cli_compile_target(src_mcu/hello)
add_arduino_cli_compile_target(src_mcu/rtos)

find_package(msgpack-cxx REQUIRED)

generate_proto(${CMAKE_CURRENT_SOURCE_DIR}/proto/mcu.proto)

add_library(mcu_rpc 
    ${CMAKE_CURRENT_BINARY_DIR}/mcu.pb.cc
    ${CMAKE_CURRENT_BINARY_DIR}/mcu.grpc.pb.cc)
target_include_directories(mcu_rpc PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(mcu_rpc PUBLIC ${_PROTOBUF_LIBPROTOBUF} ${_GRPC_GRPCPP})

add_executable(hello
    src/hello/main.cc
)
install(TARGETS hello DESTINATION "${CMAKE_INSTALL_BINDIR}")

add_executable(bridge
    src/bridge/main.cc
    src/bridge/bridge.cc
    src/bridge/mcu_service_simulator.cc
)
target_link_libraries(bridge mcu_rpc msgpack-cxx)
install(TARGETS bridge DESTINATION "${CMAKE_INSTALL_BINDIR}")