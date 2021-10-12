#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${CMAKE_CURRENT_LIST_DIR}/host_utils.cmake)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

set(MYSQL_VERSION 8.0.25)
set(MYSQL_CONNECTOR_EXTENSION tar.gz)
if (UNIX AND NOT APPLE)
    set(MYSQL_PLATFORM linux-glibc2.12)
    set(MYSQL_EXTENSION tar.xz)
endif ()
if (APPLE)
    set(MYSQL_PLATFORM macos11)
    set(MYSQL_EXTENSION tar.gz)
endif ()

FetchContent_Declare(
        mysql_client
        URL https://dev.mysql.com/get/Downloads/MySQL-8.0/mysql-${MYSQL_VERSION}-${MYSQL_PLATFORM}-x86_64.${MYSQL_EXTENSION}
        SOURCE_DIR ${THIRD_PARTY_DIR}/mysql_client
)
FetchContent_MakeAvailable(mysql_client)
FetchContent_Declare(
        boost
        URL https://boostorg.jfrog.io/artifactory/main/release/1.75.0/source/boost_1_75_0.tar.gz
        SOURCE_DIR ${THIRD_PARTY_DIR}/boost
)
FetchContent_GetProperties(boost)
if(NOT boost_POPULATED)
    FetchContent_Populate(boost)
endif()

FetchContent_Declare(
        mysql_connector_cpp
        GIT_REPOSITORY https://github.com/mysql/mysql-connector-cpp.git
        GIT_TAG        ${MYSQL_VERSION}
        GIT_PROGRESS   TRUE
        SOURCE_DIR ${THIRD_PARTY_DIR}/mysql_connector_cpp
)
FetchContent_Declare(
        mysql_connector_cpp_include
        URL https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-${MYSQL_VERSION}-${MYSQL_PLATFORM}-x86-64bit.${MYSQL_CONNECTOR_EXTENSION}
        SOURCE_DIR ${THIRD_PARTY_DIR}/mysql_connector_cpp_include
)

set(MYSQL_CXXFLAGS -stdlib=libc++ CACHE INTERNAL "")
set(WITH_BOOST ${THIRD_PARTY_DIR}/boost CACHE INTERNAL "")
set(WITH_JDBC ON CACHE INTERNAL "")
set(BUILD_STATIC ON CACHE INTERNAL "")
set(WITH_SSL=${openssl_SOURCE_DIR} CACHE INTERNAL "")
set(INSTALL_INCLUDE_DIR ${mysql_connector_cpp_SOURCE_DIR}/install CACHE INTERNAL "")  # Forces the value
set(INSTALL_LIB_DIR ${mysql_connector_cpp_SOURCE_DIR}/install CACHE INTERNAL "")  # Forces the value
set(INSTALL_DOC_DIR ${mysql_connector_cpp_SOURCE_DIR}/install CACHE INTERNAL "")  # Forces the value
set(MYSQL_LIB_DIR ${THIRD_PARTY_DIR}/mysql_client/lib CACHE INTERNAL "")
set(MYSQL_INCLUDE_DIR ${THIRD_PARTY_DIR}/mysql_client/include CACHE INTERNAL "")

FetchContent_MakeAvailable(mysql_connector_cpp_include)

FetchContent_GetProperties(mysql_connector_cpp)
if(NOT mysql_connector_cpp_POPULATED)
    FetchContent_Populate(mysql_connector_cpp)
    #add_subdirectory(${mysql_connector_cpp_SOURCE_DIR} ${mysql_connector_cpp_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

execute_process(
        COMMAND cmake -DMYSQL_CXXFLAGS=-stdlib=libc++ -DWITH_BOOST=${THIRD_PARTY_DIR}/boost -DCMAKE_INSTALL_LIBDIR=${mysql_connector_cpp_SOURCE_DIR}/install -DWITH_SSL=${openssl_SOURCE_DIR} -DMYSQL_LIB_DIR=${THIRD_PARTY_DIR}/mysql_client/lib -DMYSQL_INCLUDE_DIR=${THIRD_PARTY_DIR}/mysql_client/include -DCMAKE_BUILD_TYPE=Release -DWITH_JDBC=TRUE -DBUILD_STATIC=ON -DCMAKE_INSTALL_PREFIX=${mysql_connector_cpp_SOURCE_DIR}/install
        WORKING_DIRECTORY ${mysql_connector_cpp_SOURCE_DIR}
        RESULT_VARIABLE mysql_cmake_result
        OUTPUT_VARIABLE mysql_cmake_VARIABLE)
MESSAGE(STATUS "MYSQL_cmake_CMD_ERROR:" ${mysql_cmake_result})
MESSAGE(STATUS "MYSQL_cmake_CMD_OUTPUT:" ${mysql_cmake_VARIABLE})
execute_process(
        COMMAND make install
        WORKING_DIRECTORY ${mysql_connector_cpp_SOURCE_DIR}
        RESULT_VARIABLE mysql_install_result
        OUTPUT_VARIABLE mysql_OUTPUT_VARIABLE)
MESSAGE(STATUS "MYSQL_INSTALL_CMD_ERROR:" ${mysql_install_result})
MESSAGE(STATUS "MYSQL_INSTALL_CMD_OUTPUT:" ${mysql_OUTPUT_VARIABLE})

include_directories(${mysql_connector_cpp_SOURCE_DIR}/install/include)
include_directories(${THIRD_PARTY_DIR}/boost/)
link_directories(${mysql_connector_cpp_SOURCE_DIR}/install)

set(WINTER_MYSQL_LIB ${mysql_connector_cpp_SOURCE_DIR}/install/libmysqlcppconn-static.a)