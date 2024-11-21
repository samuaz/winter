#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##     EXTERNAL LIBS      ##
############################
find_package(mariadb-connector-cpp REQUIRED)
IF (WINTER_WITH_TEST)
find_package(GTest REQUIRED)
set(WINTER_LIBS_TEST gtest::gtest)
ENDIF()
set(WINTER_MARIADB_LIBS mariadb-connector-cpp::mariadb-connector-cpp)
