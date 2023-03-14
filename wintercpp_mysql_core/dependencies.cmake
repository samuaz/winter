#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##     EXTERNAL LIBS      ##
############################
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
IF (WINTER_WITH_TEST)
include(${PARENT_DIR}/cmake/dep_gtest.cmake)
set(WINTER_LIBS_TEST ${WINTER_GTEST_LIB})
ENDIF(WINTER_WITH_TEST)
