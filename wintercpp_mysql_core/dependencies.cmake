#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##     EXTERNAL LIBS      ##
############################
find_package(wintercpp_core REQUIRED CONFIG)
if (WINTER_WITH_TEST)
    find_package(GTest REQUIRED)
    set(WINTER_LIBS_TEST gtest::gtest)
endif()
set(WINTER_LIBS wintercpp_core::wintercpp_core)
