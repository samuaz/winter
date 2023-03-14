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
include(${PARENT_DIR}/cmake/dep_json.cmake)
include(${PARENT_DIR}/cmake/dep_jwt.cmake)
IF (WINTER_WITH_TEST)
include(${PARENT_DIR}/cmake/dep_gtest.cmake)
set(WINTER_LIBS_TEST ${WINTER_GTEST_LIB})
ENDIF(WINTER_WITH_TEST)
set(WINTER_LIBS ${WINTER_OPENSSL_LIB})