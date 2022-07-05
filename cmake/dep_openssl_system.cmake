#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${CMAKE_CURRENT_LIST_DIR}/host_utils.cmake)
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

# set(OPENSSL_USE_STATIC_LIBS TRUE)
# include(FindPkgConfig)
# find_package(OpenSSL REQUIRED) 
# if( OpenSSL_FOUND )
#     message("OPENSSL FOUND")
#     include_directories(${OPENSSL_INCLUDE_DIRS})
#     link_directories(${OPENSSL_LIBRARIES})
#     message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
# endif ()
# set(gRPC_SSL_PROVIDER package CACHE INTERNAL "")
#set(WINTER_OPENSSL_LIB -lssl -lcrypto)
# Search OpenSSL
find_package(PkgConfig REQUIRED)
pkg_search_module(OPENSSL REQUIRED openssl)

if( OPENSSL_FOUND )
    include_directories(${OPENSSL_INCLUDE_DIRS})
    link_directories(${OPENSSL_LIBRARIES})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
else()
    # Error; with REQUIRED, pkg_search_module() will throw an error by it's own
endif()

#target_link_libraries(${YOUR_TARGET_HERE} ${OPENSSL_LIBRARIES})
set(WINTER_OPENSSL_LIB -lssl -lcrypto)
