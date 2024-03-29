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
IF (WINTER_WITH_TEST)
include(${PARENT_DIR}/cmake/dep_gtest.cmake)
set(WINTER_LIBS_TEST ${WINTER_GTEST_LIB})
ENDIF(WINTER_WITH_TEST)
set(WINTER_REDIS_LIBS ${WINTER_REDIS_LIB})
