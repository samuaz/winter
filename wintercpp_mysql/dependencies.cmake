#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##     EXTERNAL LIBS      ##
############################
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
include(${PARENT_DIR}/cmake/dep_openssl.cmake)
if(true)
include(${PROJECT_SOURCE_DIR}/cmake/dep_mysql.cmake)
endif ()
if(false)
include(${PROJECT_SOURCE_DIR}/cmake/dep_mariadb_connector.cmake)
endif ()

if(WINTER_MYSQL_DRIVER)
set(WINTER_MYSQL_LIBS
        ${WINTER_LIBS}
        ${WINTER_MYSQL_LIB}
        )
endif ()
if(WINTER_MARIADB_DRIVER)
set(WINTER_MYSQL_LIBS
        ${WINTER_LIBS}
        ${WINTER_MARIADB_CONNECTOR_LIB}
        )
endif ()

set(WINTER_MYSQL_LIBS
        ${WINTER_LIBS}
        ${WINTER_OPENSSL_LIB}
        )