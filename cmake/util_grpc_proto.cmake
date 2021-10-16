#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${CMAKE_CURRENT_LIST_DIR}/host_utils.cmake)
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

execute_process(
        COMMAND "mkdir -p build && cd build && cmake .. && make grpc_cpp_plugin"
        WORKING_DIRECTORY ${grpc_SOURCE_DIR}
        RESULT_VARIABLE grpc_plugin_cmake_result
        OUTPUT_VARIABLE grpc_plugin_cmake_VARIABLE)
MESSAGE(STATUS "grpc_plugin_build_CMD_ERROR:" ${grpc_plugin_cmake_result})
MESSAGE(STATUS "grpc_plugin_build_CMD_OUTPUT:" ${grpc_plugin_cmake_VARIABLE})
execute_process(
        COMMAND mkdir -p ${THIRD_PARTY_DIR}/grpc_plugin
        COMMAND cp ${grpc_SOURCE_DIR}/build/grpc_cpp_plugin ${THIRD_PARTY_DIR}/grpc_plugin
        COMMAND cp ${grpc_SOURCE_DIR}/build/libgrpc_plugin_support.a ${THIRD_PARTY_DIR}/grpc_plugin
        WORKING_DIRECTORY ${grpc_SOURCE_DIR}/build
        RESULT_VARIABLE grpc_plugin_install_result
        OUTPUT_VARIABLE grpc_plugin_OUTPUT_VARIABLE)
MESSAGE(STATUS "grpc_plugin_CMD_ERROR:" ${grpc_plugin_install_result})
MESSAGE(STATUS "grpc_plugin_CMD_OUTPUT:" ${grpc_plugin_OUTPUT_VARIABLE})
set(grpc_plugin_SOURCE_DIR ${THIRD_PARTY_DIR}/grpc_plugin)

FetchContent_Declare(
        protobuf_compiler
        URL https://github.com/protocolbuffers/protobuf/releases/download/v3.18.0/protoc-3.18.0-${HOST_OS}-${HOST_ARCHITECTURE}.zip
        SOURCE_DIR ${THIRD_PARTY_DIR}/protobuf_compiler
)
set(protobuf_BUILD_TESTS OFF)

# FetchContent_Declare(
#         grpc_plugin
#         URL https://packages.grpc.io/archive/2021/09/253d7076fc19c7380b3f58b598eaca1b076bec74-e2a3a12f-5674-4798-9ea6-61228b2acbdc/protoc/grpc-protoc_${HOST_OS_2}_${HOST_ARCHITECTURE_2}-1.42.0-dev.tar.gz
#         SOURCE_DIR ${THIRD_PARTY_DIR}/grpc_plugin
# )
FetchContent_MakeAvailable(protobuf_compiler)
