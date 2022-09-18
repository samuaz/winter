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
include(${PROJECT_SOURCE_DIR}/cmake/dep_protobuf.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dep_grpc.cmake)
set(WINTER_GRPC_LIBS ${WINTER_GRPC_LIB} ${WINTER_PROTOBUF_LIB})
