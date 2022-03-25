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
        GIT_TAG        OpenSSL_1_1_1-stable
        GIT_PROGRESS   TRUE
        CONFIGURE_COMMAND config --prefix=${THIRD_PARTY_DIR}/openssl/install
        INSTALL_COMMAND make install_sw
        SOURCE_DIR ${THIRD_PARTY_DIR}/openssl
)
#FetchContent_MakeAvailable(openssl)

FetchContent_GetProperties(openssl)
if(NOT openssl_POPULATED)
    FetchContent_Populate(openssl)
    #add_subdirectory(${grpc_SOURCE_DIR} ${grpc_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


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
        COMMAND ./config no-asm no-shared --prefix=${openssl_SOURCE_DIR}/install
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

set(OPENSSL_ROOT_DIR ${openssl_SOURCE_DIR}/install CACHE INTERNAL "")
set(OPENSSL_LIBRARIES ${OPENSSL_ROOT_DIR}/lib CACHE INTERNAL "")
set(OPENSSL_INCLUDE_DIR ${OPENSSL_ROOT_DIR}/include CACHE INTERNAL "")
set(OPENSSL_CRYPTO_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libcrypto.a CACHE INTERNAL "")
set(OPENSSL_SSL_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libssl.a CACHE INTERNAL "")
set(OPENSSL_USE_STATIC_LIBS TRUE CACHE INTERNAL "")
set(USE_WINTER_OPENSSL TRUE)
set(gRPC_SSL_PROVIDER package CACHE INTERNAL "")

link_directories("${OPENSSL_ROOT_DIR}/lib")
include_directories(${OPENSSL_ROOT_DIR}/include)
set(WINTER_OPENSSL_LIB ${OPENSSL_ROOT_DIR}/lib/libssl.a ${OPENSSL_ROOT_DIR}/lib/libcrypto.a)