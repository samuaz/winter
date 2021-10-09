#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

cmake_minimum_required(VERSION 3.15)
set(CMAKE_POLICY_DEFAULT_CMP0079 NEW)
set(APP_NAME wintercpp)
set(APP_VERSION 0.1)
set(APP_DESCRIPTION "c++ framework to build microservices")
set(CMAKE_CXX_STANDARD 17)
project(${APP_NAME} VERSION ${APP_VERSION} DESCRIPTION ${APP_DESCRIPTION})
option(ALPINE_BUILD "Use ALPINE_BUILD" FALSE)
option(BUILD_LIB "Use BUILD_LIB" FALSE)
option(HOST_OS "HOST_OS")

# Set a default build type if none was specified
set(default_build_type "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
            STRING "Choose the type of build." FORCE)
    # Set the possible set_values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

##grpc fails to build generated_message_util.h:224:14: error: zero size arrays are an extension [-Werror,-Wzero-length-array]
## so workarround disable -pedantic-errors
#set(CMAKE_CXX_FLAGS_DEBUG "-O3 -g -pedantic-errors -Wall -Wextra ")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_C_FLAGS_DEBUG "-DEBUG -O2 -g -ggdb -Wall -Wextra -fsanitize=address -fdiagnostics-color=auto -fno-omit-frame-pointer -ftemplate-backtrace-limit=0")
set(CMAKE_CXX_FLAGS_DEBUG "-DEBUG -O2 -g -ggdb -Wall -Wextra -fsanitize=address -fdiagnostics-color=auto -fno-omit-frame-pointer -ftemplate-backtrace-limit=0")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -march=native -pipe -fno-unroll-loops -fmerge-all-constants -fno-ident -ffunction-sections -fdata-sections -Bsymbolic-functions -fpie")
set(CMAKE_C_FLAGS_RELEASE "-Ofast -march=native -pipe -fno-unroll-loops -fmerge-all-constants -fno-ident -ffunction-sections -fdata-sections -Bsymbolic-functions -fpie")
############################
##       END FLAGS        ##
############################
add_subdirectory(wintercpp_test)
add_subdirectory(wintercpp)
