#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##     EXTERNAL LIBS      ##
############################
find_package(mysql-connector-cpp REQUIRED CONFIG)
find_package(wintercpp_mysql_core REQUIRED CONFIG)
find_package(cpp-jwt REQUIRED)
IF (WINTER_WITH_TEST)
find_package(GTest REQUIRED)
set(WINTER_LIBS_TEST gtest::gtest)
ENDIF()
set(WINTER_MYSQL_LIBS cpp-jwt::cpp-jwt wintercpp_mysql_core::wintercpp_mysql_core mysql-connector-cpp::mysql-connector-cpp)
