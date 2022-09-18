#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${CMAKE_CURRENT_LIST_DIR}/host_utils.cmake)
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

# for some reason the 3 steps together dont work so i split it

# create grpc_cpp_plugin build dir
execute_process(
        COMMAND bash "-c" "mkdir -p build"
        WORKING_DIRECTORY ${grpc_SOURCE_DIR}
        RESULT_VARIABLE grpc_plugin_build_dir_creation_result
        OUTPUT_VARIABLE grpc_plugin_build_dir_creation_result_output)
MESSAGE(STATUS "grpc_plugin_build_dir_creation_error:" ${grpc_plugin_build_dir_creation_result})
MESSAGE(STATUS "grpc_plugin_build_dir_creation_output:" ${grpc_plugin_build_dir_creation_result_output})


# create grpc_cpp_plugin cmake configuration
execute_process(
        COMMAND bash "-c" "cmake .."
        WORKING_DIRECTORY ${grpc_SOURCE_DIR}/build
        RESULT_VARIABLE grpc_plugin_cmake_result
        OUTPUT_VARIABLE grpc_plugin_cmake_result_output)
MESSAGE(STATUS "grpc_plugin_cmake_CMD_ERROR:" ${grpc_plugin_cmake_result})
MESSAGE(STATUS "grpc_plugin_cmake_CMD_OUTPUT:" ${grpc_plugin_cmake_result_output})

# create grpc_cpp_plugin build
execute_process(
        COMMAND bash "-c" "make grpc_cpp_plugin"
        WORKING_DIRECTORY ${grpc_SOURCE_DIR}/build
        RESULT_VARIABLE grpc_plugin_make_result
        OUTPUT_VARIABLE grpc_plugin_make_output)
MESSAGE(STATUS "grpc_plugin_make_CMD_ERROR:" ${grpc_plugin_make_result})
MESSAGE(STATUS "grpc_plugin_make_CMD_OUTPUT:" ${grpc_plugin_make_output})

# create grpc_cpp_plugin copy to thirparty dir
execute_process(
        COMMAND bash "-c" "mkdir -p ${THIRD_PARTY_DIR}/grpc_plugin"
        WORKING_DIRECTORY ${grpc_SOURCE_DIR}/build
        RESULT_VARIABLE grpc_plugin_mkdir_result
        OUTPUT_VARIABLE grpc_plugin_mkdir_out)
MESSAGE(STATUS "grpc_plugin_mkdir_ERROR:" ${grpc_plugin_mkdir_result})
MESSAGE(STATUS "grpc_plugin_mkdir_OUTPUT:" ${grpc_plugin_mkdir_out})
set(grpc_plugin_SOURCE_DIR ${THIRD_PARTY_DIR}/grpc_plugin)

# create grpc_cpp_plugin copy to thirparty dir
execute_process(
        COMMAND bash "-c" "cp ${grpc_SOURCE_DIR}/build/grpc_cpp_plugin ${THIRD_PARTY_DIR}/grpc_plugin/"
        COMMAND bash "-c" "cp ${grpc_SOURCE_DIR}/build/libgrpc_plugin_support.a ${THIRD_PARTY_DIR}/grpc_plugin/"
        WORKING_DIRECTORY ${grpc_SOURCE_DIR}/build
        RESULT_VARIABLE grpc_plugin_install_result
        OUTPUT_VARIABLE grpc_plugin_install_out)
MESSAGE(STATUS "grpc_plugin_install_ERROR:" ${grpc_plugin_install_result})
MESSAGE(STATUS "grpc_plugin_install_OUTPUT:" ${grpc_plugin_install_out})
set(grpc_plugin_SOURCE_DIR ${THIRD_PARTY_DIR}/grpc_plugin)


# protobuf compiler 
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
