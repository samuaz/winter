#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#
include(${PARENT_DIR}/cmake/host_utils.cmake)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
FetchContent_Declare(
        protobuf
        GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
        GIT_TAG        v3.18.0
        SOURCE_SUBDIR  cmake
        SOURCE_DIR ${THIRD_PARTY_DIR}/protobuf
)

 set(protobuf_BUILD_TESTS OFF CACHE INTERNAL "")
 set(gRPC_PROTOBUF_PROVIDER package CACHE INTERNAL "")
# FetchContent_GetProperties(protobuf)
# if(NOT protobuf_POPULATED)
#     FetchContent_Populate(protobuf)
#     if (TARGET libprotobuf)
#         RETURN()
#     endif()
#     add_subdirectory(${protobuf_SOURCE_DIR}/cmake ${protobuf_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()


FetchContent_MakeAvailable(protobuf)
set(PROTOBUF_ROOT_DIR ${protobuf_SOURCE_DIR} INTERNAL "")
set(WINTER_PROTOBUF_LIB protobuf::libprotobuf)