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
    #find_package(gRPC REQUIRED)
    set(PROTO_BINARY "${Protobuf_PROTOC_EXECUTABLE}" CACHE INTERNAL "")
    find_program(grpc_cpp_plugin grpc_cpp_plugin)
    set(GRPC_PLUGIN ${grpc_cpp_plugin} CACHE INTERNAL "")
    set(WINTER_GRPC_LIB grpc grpc++)
    set(WINTER_PROTOBUF_LIB ${Protobuf_LIBRARIES})
else()
    include(${PROJECT_SOURCE_DIR}/cmake/dep_protobuf.cmake)
    include(${PROJECT_SOURCE_DIR}/cmake/dep_grpc.cmake)
    include(${PROJECT_SOURCE_DIR}/cmake/util_grpc_proto.cmake)
    set(WINTER_GRPC_LIBS ${WINTER_PROTOBUF_LIB} ${WINTER_GRPC_LIB})
    set(PROTO_BINARY "${protobuf_compiler_SOURCE_DIR}/bin/protoc" CACHE INTERNAL "")
    set(GRPC_PLUGIN "${grpc_plugin_SOURCE_DIR}/grpc_cpp_plugin" CACHE INTERNAL "")
endif()


