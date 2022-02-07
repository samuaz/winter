#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${CMAKE_CURRENT_LIST_DIR}/host_utils.cmake)
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

## openssl

FetchContent_Declare(
        openssl
        GIT_REPOSITORY https://github.com/openssl/openssl.git
        GIT_TAG        OpenSSL-fips-2_0-stable
        GIT_PROGRESS   TRUE
        CONFIGURE_COMMAND config --prefix=${THIRD_PARTY_DIR}/openssl
        INSTALL_COMMAND make install_sw
        SOURCE_DIR ${THIRD_PARTY_DIR}/openssl
)
#FetchContent_MakeAvailable(openssl)

FetchContent_GetProperties(openssl)
if(NOT openssl_POPULATED)
    FetchContent_Populate(openssl)
    #add_subdirectory(${grpc_SOURCE_DIR} ${grpc_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
#set(OPENSSL_USE_STATIC_LIBS TRUE CACHE INTERNAL "")

set(OPENSSL_ROOT_DIR ${openssl_SOURCE_DIR} CACHE INTERNAL "")
set(OPENSSL_CRYPTO_LIBRARY ${openssl_SOURCE_DIR}/libcrypto.a CACHE INTERNAL "")
set(OPENSSL_SSL_LIBRARY ${openssl_SOURCE_DIR}/libssl.a CACHE INTERNAL "")
set(OPENSSL_INCLUDE_DIR ${openssl_SOURCE_DIR}/include CACHE INTERNAL "")
set(OPENSSL_LIBRARIES ${openssl_SOURCE_DIR} CACHE INTERNAL "")
link_directories("${openssl_SOURCE_DIR}/lib")
link_directories("${openssl_SOURCE_DIR}")

#[[

if (UNIX AND NOT APPLE)
    execute_process(
            COMMAND ./config --prefix=${openssl_SOURCE_DIR}
            WORKING_DIRECTORY ${openssl_SOURCE_DIR}
            RESULT_VARIABLE openssl_install_result
            OUTPUT_VARIABLE openssl_OUTPUT_VARIABLE)
endif ()
if (APPLE)
    execute_process(
            COMMAND ./Configure darwin-i386-cc -shared --prefix=${openssl_SOURCE_DIR}
            #COMMAND ./config --prefix=${openssl_SOURCE_DIR}
            WORKING_DIRECTORY ${openssl_SOURCE_DIR}
            RESULT_VARIABLE openssl_install_result
            OUTPUT_VARIABLE openssl_OUTPUT_VARIABLE)
endif ()
]]

execute_process(
        COMMAND ./config no-asm --prefix=${openssl_SOURCE_DIR}
        WORKING_DIRECTORY ${openssl_SOURCE_DIR}
        RESULT_VARIABLE openssl_install_result
        OUTPUT_VARIABLE openssl_OUTPUT_VARIABLE)
execute_process(
        COMMAND make install_sw
        WORKING_DIRECTORY ${openssl_SOURCE_DIR}
        RESULT_VARIABLE openssl_install_result
        OUTPUT_VARIABLE openssl_OUTPUT_VARIABLE)
MESSAGE(STATUS "OPENSSL_CMD_ERROR:" ${openssl_install_result})
MESSAGE(STATUS "OPENSSL_CMD_OUTPUT:" ${openssl_OUTPUT_VARIABLE})
include_directories(${openssl_SOURCE_DIR}/include)
set(WINTER_OPENSSL_LIB ${openssl_SOURCE_DIR}/libssl.a ${openssl_SOURCE_DIR}/libcrypto.a ${openssl_SOURCE_DIR}/libfips.a)