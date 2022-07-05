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
include(${PARENT_DIR}/cmake/dep_openssl_system.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/dep_mariadb_connector.cmake)
set(WINTER_MARIADB_LIBS ${WINTER_OPENSSL_LIB} ${WINTER_MARIADB_CONNECTOR_LIB})