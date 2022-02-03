#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##     EXTERNAL LIBS      ##
############################
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
include(${PROJECT_SOURCE_DIR}/cmake/dep_gtest.cmake)
set(WINTER_LIBS_TEST ${WINTER_GTEST_LIB})