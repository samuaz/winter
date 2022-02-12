#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${PARENT_DIR}/cmake/host_utils.cmake)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

set(MYSQL_VERSION 8.0.27)
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
        URL https://boostorg.jfrog.io/artifactory/main/release/1.73.0/source/boost_1_73_0.tar.gz
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

execute_process(
        COMMAND bash "-c" "cmake .. -DDOWNLOAD_BOOST=1 -DWITH_SSL=${openssl_SOURCE_DIR} -DOPENSSL_INCLUDE_DIR=${openssl_SOURCE_DIR}/include -DWITH_SSL=${openssl_SOURCE_DIR} -DOPENSSL_LIBRARY=${openssl_SOURCE_DIR}/libssl.a -DCRYPTO_LIBRARY=${openssl_SOURCE_DIR}/libcrypto.a -DWITH_BOOST=${THIRD_PARTY_DIR}/boost -DWITHOUT_SERVER=ON -DBUILD_CONFIG=mysql_release -DINSTALL_STATIC_LIBRARIES=ON -DCMAKE_INSTALL_PREFIX=${mysql_client_SOURCE_DIR}/build/install -DWITH_UNIT_TESTS=OFF && make install"
        WORKING_DIRECTORY ${mysql_client_SOURCE_DIR}/build
        RESULT_VARIABLE mysql_client_cmake_result
        OUTPUT_VARIABLE mysql_client_cmake_VARIABLE)
MESSAGE(STATUS "MYSQL_client_cmake_CMD_ERROR:" ${mysql_client_cmake_result})
MESSAGE(STATUS "MYSQL_client_cmake_CMD_OUTPUT:" ${mysql_client_cmake_VARIABLE})

#add_subdirectory(${mysql_client_SOURCE_DIR} ${mysql_client_BINARY_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX_OLD} CACHE BOOL "install prefix" FORCE)
endif()


##### CONNECTOR

## SOME CONFIGS
# set(MYSQL_CXXFLAGS -stdlib=libc++ CACHE INTERNAL "")
# set(WITH_BOOST ${THIRD_PARTY_DIR}/boost CACHE INTERNAL "")
# set(WITH_JDBC ON CACHE INTERNAL "")
# set(BUILD_STATIC ON CACHE INTERNAL "")
# set(WITH_SSL=${openssl_SOURCE_DIR} CACHE INTERNAL "")
# set(INSTALL_INCLUDE_DIR ${mysql_connector_cpp_SOURCE_DIR}/install CACHE INTERNAL "")  # Forces the value
# set(INSTALL_LIB_DIR ${mysql_connector_cpp_SOURCE_DIR}/install CACHE INTERNAL "")  # Forces the value
# set(INSTALL_DOC_DIR ${mysql_connector_cpp_SOURCE_DIR}/install CACHE INTERNAL "")  # Forces the value
# set(MYSQL_LIB_DIR ${THIRD_PARTY_DIR}/mysql_client/build/install/lib CACHE INTERNAL "")
# set(MYSQL_INCLUDE_DIR ${THIRD_PARTY_DIR}/mysql_client/build/install/include CACHE INTERNAL "")

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

execute_process(
        COMMAND bash "-c" "cmake -DMYSQL_CXXFLAGS=-stdlib=libc++ -DWITH_BOOST=${THIRD_PARTY_DIR}/boost -DCMAKE_INSTALL_LIBDIR=${mysql_connector_cpp_SOURCE_DIR}/install -DOPENSSL_INCLUDE_DIR=${openssl_SOURCE_DIR}/include -DWITH_SSL=${openssl_SOURCE_DIR} -DOPENSSL_LIBRARY=${openssl_SOURCE_DIR}/libssl.a -DCRYPTO_LIBRARY=${openssl_SOURCE_DIR}/libcrypto.a -DMYSQL_LIB_DIR=${THIRD_PARTY_DIR}/mysql_client/build/install/lib -DMYSQL_INCLUDE_DIR=${THIRD_PARTY_DIR}/mysql_client/build/install/include -DCMAKE_BUILD_TYPE=Release -DWITH_JDBC=TRUE -DBUILD_STATIC=ON -DCMAKE_INSTALL_PREFIX=${mysql_connector_cpp_SOURCE_DIR}/install && make install"
        WORKING_DIRECTORY ${mysql_connector_cpp_SOURCE_DIR}
        RESULT_VARIABLE mysql_cmake_result
        OUTPUT_VARIABLE mysql_cmake_VARIABLE)
MESSAGE(STATUS "MYSQL_cmake_CMD_ERROR:" ${mysql_cmake_result})
MESSAGE(STATUS "MYSQL_cmake_CMD_OUTPUT:" ${mysql_cmake_VARIABLE})

include_directories(${mysql_connector_cpp_SOURCE_DIR}/install/include)
include_directories(${THIRD_PARTY_DIR}/boost/)
link_directories(${mysql_connector_cpp_SOURCE_DIR}/install)
set(WINTER_MYSQL_CONNECTOR_LIB ${mysql_connector_cpp_SOURCE_DIR}/install/libmysqlcppconn-static.a)
set(WINTER_MYSQL_DRIVER true CACHE INTERNAL "")
set(WINTER_MARIADB_DRIVER false CACHE INTERNAL "")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/wintercpp/data/sql/mysql/winter_sql_mysql_driver.h.in ${CMAKE_BINARY_DIR}/generated/wintercpp/data/sql/mysql/winter_sql_mysql_driver.h)


#cmake -DMYSQL_CXXFLAGS=-stdlib=libc++ -DWITH_BOOST=/home/samuaz/Projects/toc/mediamanager/third_party/winter/wintercpp_mysql/third_party/boost -DCMAKE_INSTALL_LIBDIR=/home/samuaz/Projects/toc/mediamanager/third_party/winter/wintercpp_mysql/third_party/mysql_connector_cpp/install -DWITH_SSL=/home/samuaz/Projects/toc/mediamanager/third_party/winter/wintercpp/third_party/openssl -DMYSQL_LIB_DIR=/home/samuaz/Projects/toc/mediamanager/third_party/winter/wintercpp_mysql/third_party/mysql_client/build/install/lib -DMYSQL_INCLUDE_DIR=/home/samuaz/Projects/toc/mediamanager/third_party/winter/wintercpp_mysql/third_party/mysql_client/build/install/include -DCMAKE_BUILD_TYPE=Release -DWITH_JDBC=TRUE -DBUILD_STATIC=ON -DCMAKE_INSTALL_PREFIX=/home/samuaz/Projects/toc/mediamanager/third_party/winter/wintercpp_mysql/third_party/mysql_connector_cpp/install && make install

#cmake .. -DDOWNLOAD_BOOST=1 -DOPENSSL_INCLUDE_DIR=/home/samuaz/Projects/toc/mediamanager/third_party/winter/wintercpp/third_party/openssl/include  -DCRYPTO_LIBRARY=/home/samuaz/Projects/toc/mediamanager/third_party/winter/wintercpp/third_party/openssl/libcrypto.a -DOPENSSL_LIBRARY=/home/samuaz/Projects/toc/mediamanager/third_party/winter/wintercpp/third_party/openssl/libssl.a -DWITH_SSL=/home/samuaz/Projects/toc/mediamanager/third_party/winter/wintercpp/third_party/openssl -DWITH_BOOST=/home/samuaz/Projects/toc/mediamanager/third_party/winter/wintercpp_mysql/third_party/boost -DWITHOUT_SERVER=ON -DBUILD_CONFIG=mysql_release -DINSTALL_STATIC_LIBRARIES=ON -DCMAKE_INSTALL_PREFIX=/home/samuaz/Projects/toc/mediamanager/third_party/winter/wintercpp_mysql/third_party/mysql_client/build/install -DWITH_UNIT_TESTS=OFF && make install
