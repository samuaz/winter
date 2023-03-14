#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##     EXTERNAL LIBS      ##
############################
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
#include(${PARENT_DIR}/cmake/dep_openssl.cmake)
#include(${PARENT_DIR}/cmake/dep_openssl_system.cmake)

option(USE_SYSTEM_GRPC "Use system installed gRPC" OFF)
if(USE_SYSTEM_GRPC)
  # Find system-installed gRPC
    find_package(Protobuf REQUIRED)
    #protoc 
    set(PROTO_BINARY "${Protobuf_PROTOC_EXECUTABLE}" CACHE INTERNAL "")
    find_library(PROTOBUF_LIBRARY NAMES protobuf)
    find_library(PROTOC_LIBRARY NAMES protoc)
    #GPRC
    find_program(grpc_cpp_plugin grpc_cpp_plugin)
    find_library(GRPC_LIBRARY NAMES grpc)
    find_library(GRPCPP_LIBRARY NAMES grpc++)
    find_library(GPR_LIBRARY NAMES gpr)
    set(GRPC_PLUGIN ${grpc_cpp_plugin} CACHE INTERNAL "")
    set(WINTER_GRPC_LIB ${GRPCPP_LIBRARY} ${GRPC_LIBRARY} ${GPR_LIBRARY})
    set(WINTER_PROTOBUF_LIB ${PROTOC_LIBRARY} ${PROTOBUF_LIBRARY})
    set(WINTER_GRPC_LIBS ${WINTER_PROTOBUF_LIB} ${WINTER_GRPC_LIB})
else()
    include(${PROJECT_SOURCE_DIR}/cmake/dep_protobuf.cmake)
    include(${PROJECT_SOURCE_DIR}/cmake/dep_grpc.cmake)
    include(${PROJECT_SOURCE_DIR}/cmake/util_grpc_proto.cmake)
    set(WINTER_GRPC_LIBS ${WINTER_PROTOBUF_LIB} ${WINTER_GRPC_LIB})
    set(PROTO_BINARY "${protobuf_compiler_SOURCE_DIR}/bin/protoc" CACHE INTERNAL "")
    set(GRPC_PLUGIN "${grpc_plugin_SOURCE_DIR}/grpc_cpp_plugin" CACHE INTERNAL "")
endif()
IF (WINTER_WITH_TEST)
include(${PARENT_DIR}/cmake/dep_gtest.cmake)
set(WINTER_LIBS_TEST ${WINTER_GTEST_LIB})
ENDIF(WINTER_WITH_TEST)

