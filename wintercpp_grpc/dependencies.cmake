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
    find_package(gRPC CONFIG REQUIRED)
else()
    include(${PROJECT_SOURCE_DIR}/cmake/dep_protobuf.cmake)
    include(${PROJECT_SOURCE_DIR}/cmake/dep_grpc.cmake)
    include(${PROJECT_SOURCE_DIR}/cmake/util_grpc_proto.cmake)
    set(WINTER_GRPC_LIBS ${WINTER_PROTOBUF_LIB} ${WINTER_GRPC_LIB})
endif()


