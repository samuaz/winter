#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${PARENT_DIR}/cmake/host_utils.cmake)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
#set(WINTER_MARIADB_DRIVER false CACHE INTERNAL "WINTER_MARIADB_DRIVER")

set(MYSQL_VERSION 8.0.29)
set(MYSQL_CONNECTOR_EXTENSION tar.gz)
if (UNIX AND NOT APPLE)
    set(MYSQL_PLATFORM linux-glibc2.12)
    set(MYSQL_EXTENSION tar.xz)
endif ()
if (APPLE)
    set(MYSQL_PLATFORM macos11)
    set(MYSQL_EXTENSION tar.gz)
endif ()

## BOOST
FetchContent_Declare(
        boost
        URL https://boostorg.jfrog.io/artifactory/main/release/1.77.0/source/boost_1_77_0.tar.gz
        SOURCE_DIR ${THIRD_PARTY_DIR}/boost
)
FetchContent_GetProperties(boost)
if(NOT boost_POPULATED)
    FetchContent_Populate(boost)
endif()
set(WITH_BOOST ${THIRD_PARTY_DIR}/boost CACHE INTERNAL "boost directory")

##### CLIENT
FetchContent_Declare(
        mysql_client
        GIT_REPOSITORY https://github.com/mysql/mysql-server.git
        GIT_TAG        mysql-${MYSQL_VERSION}
        GIT_PROGRESS   TRUE
        SOURCE_DIR ${THIRD_PARTY_DIR}/mysql_client
)

FetchContent_GetProperties(mysql_client)
if(NOT mysql_client_POPULATED)
    FetchContent_Populate(mysql_client)
    set(CMAKE_INSTALL_PREFIX_OLD ${CMAKE_INSTALL_PREFIX})
    set(DOWNLOAD_BOOST ON CACHE INTERNAL "MYSQL CLIENT DOWNLOAD BOOST")
    set(WITHOUT_SERVER ON CACHE INTERNAL "MYSQL CLIENT WITHOUT SERVER")
    set(BUILD_CONFIG mysql_release CACHE INTERNAL "MYSQL CLIENT BUILD_CONFIG")
    set(INSTALL_STATIC_LIBRARIES ON CACHE INTERNAL "MYSQL CLIENT INSTALL_STATIC_LIBRARIES")
    set(WITH_UNIT_TESTS OFF CACHE INTERNAL "MYSQL CLIENT WITH_UNIT_TESTS")
    set(RUN_ABI_CHECK OFF CACHE INTERNAL "MYSQL CLIENT WITH_UNIT_TESTS")
    set(CMAKE_INSTALL_PREFIX ${mysql_client_SOURCE_DIR}/build/install CACHE INTERNAL "DOWNLOAD BOOST")


execute_process(
        COMMAND bash "-c" "mkdir -p build/install"
        WORKING_DIRECTORY ${mysql_client_SOURCE_DIR}
        RESULT_VARIABLE mysql_client_build_dir_result
        OUTPUT_VARIABLE mysql_client_build_dir_VARIABLE)
MESSAGE(STATUS "MYSQL_client_build_dir_CMD_ERROR:" ${mysql_client_build_dir_result})
MESSAGE(STATUS "MYSQL_client_build_dir_CMD_OUTPUT:" ${mysql_client_build_dir_VARIABLE})

execute_process(
         COMMAND bash "-c" "sed -e '/SET(RUN_ABI_CHECK 1)/ s/^#*/#/' -i abi_check.cmake"
         WORKING_DIRECTORY ${mysql_client_SOURCE_DIR}/cmake
         RESULT_VARIABLE mysql_client_RUN_ABI_CHECK_result
         OUTPUT_VARIABLE mysql_client_RUN_ABI_CHECK_VARIABLE)
MESSAGE(STATUS "MYSQL_client_RUN_ABI_CHECK_CMD_ERROR:" ${mysql_client_RUN_ABI_CHECK_result})
MESSAGE(STATUS "MYSQL_client_RUN_ABI_CHECK_CMD_OUTPUT:" ${mysql_client_RUN_ABI_CHECK_VARIABLE})


if(USE_WINTER_OPENSSL)
        set(MYSQL_CLIENT_COMMAND "cmake .. -DDOWNLOAD_BOOST=1 -DWITH_SSL=${openssl_SOURCE_DIR}/install -DOPENSSL_INCLUDE_DIR=${openssl_SOURCE_DIR}/install/include -DOPENSSL_LIBRARY=${openssl_SOURCE_DIR}/install/lib/libssl.a -DCRYPTO_LIBRARY=${openssl_SOURCE_DIR}/install/lib/libcrypto.a -DWITH_BOOST=${THIRD_PARTY_DIR}/boost -DWITHOUT_SERVER=ON -DBUILD_CONFIG=mysql_release -DINSTALL_STATIC_LIBRARIES=ON -DCMAKE_INSTALL_PREFIX=${mysql_client_SOURCE_DIR}/build/install -DWITH_UNIT_TESTS=OFF && make install")
else()
        set(MYSQL_CLIENT_COMMAND "cmake .. -DWITH_BOOST=${THIRD_PARTY_DIR}/boost -DWITH_SSL=system -DWITHOUT_SERVER=ON -DBUILD_CONFIG=mysql_release -DINSTALL_STATIC_LIBRARIES=ON -DCMAKE_INSTALL_PREFIX=${mysql_client_SOURCE_DIR}/build/install -DWITH_UNIT_TESTS=OFF && make -j4 && make install")
endif()      

execute_process(
        COMMAND bash "-c" ${MYSQL_CLIENT_COMMAND}
        WORKING_DIRECTORY ${mysql_client_SOURCE_DIR}/build
        RESULT_VARIABLE mysql_client_cmake_result)
MESSAGE(STATUS "MYSQL_client_cmake_CMD_ERROR:" ${mysql_client_cmake_result})
MESSAGE(STATUS "MYSQL_client_cmake_CMD_OUTPUT:" ${mysql_client_cmake_VARIABLE})

#add_subdirectory(${mysql_client_SOURCE_DIR} ${mysql_client_BINARY_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX_OLD} CACHE BOOL "install prefix" FORCE)
endif()

FetchContent_Declare(
        mysql_connector_cpp
        GIT_REPOSITORY https://github.com/mysql/mysql-connector-cpp.git
        GIT_TAG        ${MYSQL_VERSION}
        GIT_PROGRESS   TRUE
        SOURCE_DIR ${THIRD_PARTY_DIR}/mysql_connector_cpp
)

FetchContent_GetProperties(mysql_connector_cpp)
if(NOT mysql_connector_cpp_POPULATED)
    FetchContent_Populate(mysql_connector_cpp)
endif()

if(USE_WINTER_OPENSSL)
        set(MYSQL_CONNECTOR_COMMAND "cmake -DWITH_BOOST=${THIRD_PARTY_DIR}/boost -DCMAKE_INSTALL_LIBDIR=${mysql_connector_cpp_SOURCE_DIR}/install -DOPENSSL_INCLUDE_DIR=${openssl_SOURCE_DIR}/install/include -DWITH_SSL=${openssl_SOURCE_DIR}/install -DOPENSSL_LIBRARY=${openssl_SOURCE_DIR}/install/lib/libssl.a -DCRYPTO_LIBRARY=${openssl_SOURCE_DIR}/install/lib/libcrypto.a -DMYSQL_LIB_DIR=${THIRD_PARTY_DIR}/mysql_client/build/install/lib -DMYSQL_INCLUDE_DIR=${THIRD_PARTY_DIR}/mysql_client/build/install/include -DCMAKE_BUILD_TYPE=Release -DWITH_JDBC=TRUE -DBUILD_STATIC=ON -DMYSQLCLIENT_STATIC_LINKING=ON -DCMAKE_INSTALL_PREFIX=${mysql_connector_cpp_SOURCE_DIR}/install && make install")
else()
        set(MYSQL_CONNECTOR_COMMAND "cmake -DWITH_BOOST=${THIRD_PARTY_DIR}/boost -DCMAKE_INSTALL_LIBDIR=${mysql_connector_cpp_SOURCE_DIR}/install -DMYSQL_LIB_DIR=${THIRD_PARTY_DIR}/mysql_client/build/install/lib -DMYSQL_INCLUDE_DIR=${THIRD_PARTY_DIR}/mysql_client/build/install/include -DCMAKE_BUILD_TYPE=Release -DWITH_JDBC=TRUE -DBUILD_STATIC=ON -DMYSQLCLIENT_STATIC_LINKING=ON -DCMAKE_INSTALL_PREFIX=${mysql_connector_cpp_SOURCE_DIR}/install && make install")
endif()      

execute_process(
        COMMAND bash "-c" ${MYSQL_CONNECTOR_COMMAND}
        WORKING_DIRECTORY ${mysql_connector_cpp_SOURCE_DIR}
        RESULT_VARIABLE mysql_cmake_result
        OUTPUT_VARIABLE mysql_cmake_VARIABLE)
MESSAGE(STATUS "MYSQL_cmake_CMD_ERROR:" ${mysql_cmake_result})
MESSAGE(STATUS "MYSQL_cmake_CMD_OUTPUT:" ${mysql_cmake_VARIABLE})

include_directories(${mysql_connector_cpp_SOURCE_DIR}/install/include)
include_directories(${THIRD_PARTY_DIR}/boost/)
link_directories(${mysql_connector_cpp_SOURCE_DIR}/install)
set(WINTER_MYSQL_CONNECTOR_LIB ${mysql_connector_cpp_SOURCE_DIR}/install/libmysqlcppconn-static.a)