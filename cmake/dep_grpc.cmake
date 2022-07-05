#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${CMAKE_CURRENT_LIST_DIR}/host_utils.cmake)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

## HOT FIX FOR GRPC AND GCC 11 & CLAND 12
## re2 ##
FetchContent_Declare(
        re2
        GIT_REPOSITORY https://github.com/google/re2.git
        GIT_TAG        2021-09-01
        GIT_PROGRESS   TRUE
        SOURCE_DIR ${THIRD_PARTY_DIR}/re2
)

## grpc ##
FetchContent_Declare(
        grpc
        GIT_REPOSITORY https://github.com/grpc/grpc.git
        GIT_TAG        v1.41.0
        GIT_PROGRESS   TRUE 
        SOURCE_DIR ${THIRD_PARTY_DIR}/grpc
)

set(BUILD_TESTING OFF CACHE INTERNAL "")
set(gRPC_BUILD_TESTS OFF CACHE INTERNAL "")
set(gRPC_RE2_PROVIDER package CACHE INTERNAL "")
set(gRPC_BUILD_GRPC_CPP_PLUGIN ON CACHE INTERNAL "")
set(gRPC_BUILD_GRPC_CSHARP_PLUGIN OFF CACHE INTERNAL "")
set(gRPC_BUILD_GRPC_NODE_PLUGIN OFF CACHE INTERNAL "")
set(gRPC_BUILD_GRPC_OBJECTIVE_C_PLUGIN OFF CACHE INTERNAL "")
set(gRPC_BUILD_GRPC_PHP_PLUGIN OFF CACHE INTERNAL "")
set(gRPC_BUILD_GRPC_PYTHON_PLUGIN OFF CACHE INTERNAL "")
set(gRPC_BUILD_GRPC_RUBY_PLUGIN OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(re2 grpc)

# FetchContent_GetProperties(re2)
# if(NOT re2_POPULATED)
#     FetchContent_Populate(re2)
#     add_subdirectory(${re2_SOURCE_DIR} ${re2_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()

# FetchContent_GetProperties(grpc)
# if(NOT grpc_POPULATED)
#     FetchContent_Populate(grpc)
#     add_subdirectory(${grpc_SOURCE_DIR} ${grpc_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()
set(WINTER_GRPC_LIB re2 grpc++)

