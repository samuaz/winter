#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##     EXTERNAL LIBS      ##
############################
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

include(${PROJECT_SOURCE_DIR}/cmake/dep_openssl.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dep_protobuf.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dep_grpc.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dep_json.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dep_jwt.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dep_mysql.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dep_redis.cmake)
#include(${PROJECT_SOURCE_DIR}/cmake/util_grpc_proto.cmake)

set(WINTER_LIBS
        ${WINTER_PROTOBUF_LIB}
        ${WINTER_GRPC_LIB}
        ${WINTER_MYSQL_LIB}
        ${WINTER_REDIS_LIB}
        ${WINTER_OPENSSL_LIB}
        )