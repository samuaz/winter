#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

cmake_minimum_required(VERSION 3.15)
set(CMAKE_POLICY_DEFAULT_CMP0079 NEW)
set(WINTER_PROJECT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(APP_NAME wintercpp)
set(APP_VERSION 0.1)
set(APP_DESCRIPTION "c++ framework to build microservices")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
project(${APP_NAME} VERSION ${APP_VERSION} DESCRIPTION ${APP_DESCRIPTION})
option(ALPINE_BUILD "Use ALPINE_BUILD" FALSE)
option(BUILD_LIB "Use BUILD_LIB" FALSE)
option(HOST_OS "HOST_OS")
option(WINTER_WITH_TEST "Enable building TESTS" OFF)
option(WINTER_WITH_GRPC "Enable building GRPC" OFF)
option(WINTER_WITH_MARIADB "Enable building MARIADB" OFF)
option(WINTER_WITH_MYSQL "Enable building MYSQL" OFF)
option(WINTER_WITH_REDIS "Enable building REDIS" OFF)


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

# assume built-in pthreads on MacOS
IF(APPLE)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
ENDIF()

##grpc fails to build generated_message_util.h:224:14: error: zero size arrays are an extension [-Werror,-Wzero-length-array]
## so workarround disable -pedantic-errors
#set(CMAKE_CXX_FLAGS_DEBUG "-O3 -g -pedantic-errors -Wall -Wextra ")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_C_FLAGS_DEBUG "-DEBUG -O0 -g2 -ggdb -Wall -Wextra -fsanitize=address -fdiagnostics-color=auto -fno-omit-frame-pointer -ftemplate-backtrace-limit=0 -Werror=return-type")
set(CMAKE_CXX_FLAGS_DEBUG "-DEBUG -O0 -g2 -ggdb -Wall -Wextra -fsanitize=address -fdiagnostics-color=auto -fno-omit-frame-pointer -ftemplate-backtrace-limit=0 -Werror=return-type")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -pipe -fno-unroll-loops -fmerge-all-constants -fno-ident -ffunction-sections -fdata-sections -Bsymbolic-functions -fpie -Wall -Werror=return-type")
set(CMAKE_C_FLAGS_RELEASE "-Ofast -pipe -fno-unroll-loops -fmerge-all-constants -fno-ident -ffunction-sections -fdata-sections -Bsymbolic-functions -fpie -Wall -Werror=return-type")
############################
##       END FLAGS        ##
############################
add_subdirectory(wintercpp)
add_subdirectory(wintercpp_mysql_core)

IF (WINTER_WITH_MARIADB)
add_subdirectory(wintercpp_mariadb)
ENDIF(WINTER_WITH_MARIADB)

IF (WINTER_WITH_MYSQL)
add_subdirectory(wintercpp_mysql)
ENDIF(WINTER_WITH_MYSQL)

IF (WINTER_WITH_GRPC)
add_subdirectory(wintercpp_grpc)
ENDIF(WINTER_WITH_GRPC)

IF (WINTER_WITH_REDIS)
add_subdirectory(wintercpp_redis)
ENDIF(WINTER_WITH_REDIS)

IF (WINTER_WITH_TEST)
add_subdirectory(wintercpp_mariadb)
add_subdirectory(wintercpp_mysql)
add_subdirectory(wintercpp_grpc)
add_subdirectory(wintercpp_redis)
add_subdirectory(wintercpp_test)
ENDIF(WINTER_WITH_TEST)


