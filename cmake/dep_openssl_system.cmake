#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${CMAKE_CURRENT_LIST_DIR}/host_utils.cmake)
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

set(OPENSSL_USE_STATIC_LIBS TRUE)
include(FindPkgConfig)
find_package(OpenSSL REQUIRED) 
if( OpenSSL_FOUND )
    message("OPENSSL FOUND")
    include_directories(${OPENSSL_INCLUDE_DIRS})
    link_directories(${OPENSSL_LIBRARIES})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
endif ()
set(gRPC_SSL_PROVIDER package CACHE INTERNAL "")
#set(WINTER_OPENSSL_LIB -lssl -lcrypto)
