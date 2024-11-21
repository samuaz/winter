#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##     EXTERNAL LIBS      ##
############################
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(cpp-jwt REQUIRED)
if (WINTER_WITH_TEST)
    find_package(GTest REQUIRED)
    set(WINTER_LIBS_TEST gtest::gtest)
endif()
set(WINTER_LIBS OpenSSL::SSL nlohmann_json::nlohmann_json cpp-jwt::cpp-jwt)
