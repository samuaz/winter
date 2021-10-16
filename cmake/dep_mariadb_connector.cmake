#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${CMAKE_CURRENT_LIST_DIR}/host_utils.cmake)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
set(MARIADB_LINK_DYNAMIC OFF CACHE INTERNAL "")

FetchContent_Declare(
        mariadb_connector
        GIT_REPOSITORY https://github.com/samuaz/mariadb-connector-cpp.git
        GIT_TAG        master
        SOURCE_SUBDIR  cmake
        SOURCE_DIR ${THIRD_PARTY_DIR}/mariadb_connector
)

#FetchContent_MakeAvailable(mariadb_connector)

#set(WINTER_MARIADB_CONNECTOR_LIB mariadb)


FetchContent_GetProperties(mariadb_connector)
if(NOT mariadb_connector_POPULATED)
    FetchContent_Populate(mariadb_connector)
    #add_subdirectory(${mysql_connector_cpp_SOURCE_DIR} ${mysql_connector_cpp_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

execute_process(
        COMMAND cmake -DBUILD_SHARED_LIBS=OFF -DMARIADB_LINK_DYNAMIC=OFF -DINSTALL_LIB_SUFFIX=${mariadb_connector_SOURCE_DIR}/install -DCMAKE_INSTALL_PREFIX=${mariadb_connector_SOURCE_DIR}/install
        WORKING_DIRECTORY ${mariadb_connector_SOURCE_DIR}
        RESULT_VARIABLE mariadb_cmake_result
        OUTPUT_VARIABLE mariadb_cmake_VARIABLE)
MESSAGE(STATUS "mariadb_cmake_CMD_ERROR:" ${mariadb_cmake_result})
MESSAGE(STATUS "mariadb_cmake_CMD_OUTPUT:" ${mariadb_cmake_VARIABLE})
execute_process(
        COMMAND make install
        WORKING_DIRECTORY ${mariadb_connector_SOURCE_DIR}
        RESULT_VARIABLE mariadb_install_result
        OUTPUT_VARIABLE mariadb_OUTPUT_VARIABLE)
MESSAGE(STATUS "mariadb_INSTALL_CMD_ERROR:" ${mariadb_install_result})
MESSAGE(STATUS "mariadb_INSTALL_CMD_OUTPUT:" ${mariadb_OUTPUT_VARIABLE})

include_directories(${mariadb_connector_cpp_SOURCE_DIR}/install/include)
link_directories(${mariadb_connector_cpp_SOURCE_DIR}/install/lib)

set(WINTER_MARIADB_CONNECTOR_LIB ${mariadb_connector_cpp_SOURCE_DIR}/install/lib/libmariadbcpp.a)