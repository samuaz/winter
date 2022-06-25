#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##     EXTERNAL LIBS      ##
############################
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
include(${PROJECT_SOURCE_DIR}/cmake/dep_redis.cmake)
set(WINTER_REDIS_LIBS ${WINTER_REDIS_LIB})
