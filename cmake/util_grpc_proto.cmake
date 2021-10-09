#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${CMAKE_CURRENT_LIST_DIR}/host_utils.cmake)
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

FetchContent_Declare(
        protobuf_compiler
        URL https://github.com/protocolbuffers/protobuf/releases/download/v3.18.0/protoc-3.18.0-${HOST_OS}-x86_64.zip
        SOURCE_DIR ${THIRD_PARTY_DIR}/protobuf_compiler
)
set(protobuf_BUILD_TESTS OFF)

FetchContent_Declare(
        grpc_plugin
        URL https://packages.grpc.io/archive/2021/09/253d7076fc19c7380b3f58b598eaca1b076bec74-e2a3a12f-5674-4798-9ea6-61228b2acbdc/protoc/grpc-protoc_${HOST_OS_2}_x64-1.42.0-dev.tar.gz
        SOURCE_DIR ${THIRD_PARTY_DIR}/grpc_plugin
)
FetchContent_MakeAvailable(protobuf_compiler grpc_plugin)
