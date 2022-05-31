#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##     EXTERNAL LIBS      ##
############################
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

include(${PARENT_DIR}/cmake/dep_openssl_system.cmake)
#include(${PARENT_DIR}/cmake/dep_openssl.cmake)
include(${PARENT_DIR}/cmake/dep_protobuf.cmake)
include(${PARENT_DIR}/cmake/dep_grpc.cmake)
include(${PARENT_DIR}/cmake/dep_json.cmake)
include(${PARENT_DIR}/cmake/dep_jwt.cmake)
include(${PARENT_DIR}/cmake/dep_redis.cmake)
#include(${PROJECT_SOURCE_DIR}/cmake/util_grpc_proto.cmake)

set(WINTER_LIBS
        ${WINTER_PROTOBUF_LIB}
        ${WINTER_GRPC_LIB}
        ${WINTER_REDIS_LIB}
        ${WINTER_OPENSSL_LIB}
        )