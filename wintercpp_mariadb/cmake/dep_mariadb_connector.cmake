#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${PARENT_DIR}/cmake/host_utils.cmake)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
#set(WINTER_MYSQL_DRIVER false CACHE INTERNAL "WINTER_MYSQL_DRIVER")
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
set(MARIADB_LINK_DYNAMIC OFF CACHE INTERNAL "")

FetchContent_Declare(
        mariadb_connector
        GIT_REPOSITORY https://github.com/mariadb-corporation/mariadb-connector-cpp.git
        GIT_TAG        1.1.1
        SOURCE_SUBDIR  cmake
        SOURCE_DIR ${THIRD_PARTY_DIR}/mariadb_connector
)

#FetchContent_MakeAvailable(mariadb_connector)

FetchContent_GetProperties(mariadb_connector)
if(NOT mariadb_connector_POPULATED)
    FetchContent_Populate(mariadb_connector)
    #add_subdirectory(${mysql_connector_cpp_SOURCE_DIR} ${mysql_connector_cpp_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

execute_process(
        COMMAND bash "-c" "git submodule update --init --recursive"
        WORKING_DIRECTORY ${mariadb_connector_SOURCE_DIR}
        RESULT_VARIABLE mariadb_init_result
        OUTPUT_VARIABLE mariadb_init_VARIABLE)
MESSAGE(STATUS "mariadb_init_CMD_ERROR:" ${mariadb_patches_result})
MESSAGE(STATUS "mariadb_init_CMD_OUTPUT:" ${mariadb_patches_VARIABLE})

execute_process(
        COMMAND bash "-c" "patch -p1 < ${CMAKE_CURRENT_SOURCE_DIR}/cmake/patches/mariadb_cpp_cmake_static_build.patch"
        WORKING_DIRECTORY ${mariadb_connector_SOURCE_DIR}
        RESULT_VARIABLE mariadb_patches_result
        OUTPUT_VARIABLE mariadb_patches_VARIABLE)
MESSAGE(STATUS "mariadb_patches_CMD_ERROR:" ${mariadb_patches_result})
MESSAGE(STATUS "mariadb_patches_CMD_OUTPUT:" ${mariadb_patches_VARIABLE})

execute_process(
        COMMAND bash "-c" "patch -p1 < ${CMAKE_CURRENT_SOURCE_DIR}/cmake/patches/mariadb_c_fix_osx_and_static_build.patch"
        WORKING_DIRECTORY ${mariadb_connector_SOURCE_DIR}/libmariadb/
        RESULT_VARIABLE mariadb_c_patches_result
        OUTPUT_VARIABLE mariadb_c_patches_VARIABLE)
MESSAGE(STATUS "mariadb_c_patches_CMD_ERROR:" ${mariadb_c_patches_result})
MESSAGE(STATUS "mariadb_c_patches_CMD_OUTPUT:" ${mariadb_c_patches_VARIABLE})

execute_process(
        COMMAND bash "-c" "patch -p1 < ${CMAKE_CURRENT_SOURCE_DIR}/cmake/patches/mariadb_fix_missing_cstring_test_asserts.patch"
        WORKING_DIRECTORY ${mariadb_connector_SOURCE_DIR}
        RESULT_VARIABLE mariadb_c_patches_result
        OUTPUT_VARIABLE mariadb_c_patches_VARIABLE)
MESSAGE(STATUS "mariadb_c_patches_CMD_ERROR:" ${mariadb_c_patches_result})
MESSAGE(STATUS "mariadb_c_patches_CMD_OUTPUT:" ${mariadb_c_patches_VARIABLE})

execute_process(
        COMMAND bash "-c" "patch -p1 < ${CMAKE_CURRENT_SOURCE_DIR}/cmake/patches/mariadb_fix_missing_cstring.patch"
        WORKING_DIRECTORY ${mariadb_connector_SOURCE_DIR}
        RESULT_VARIABLE mariadb_c_patches_result
        OUTPUT_VARIABLE mariadb_c_patches_VARIABLE)
MESSAGE(STATUS "mariadb_c_patches_CMD_ERROR:" ${mariadb_c_patches_result})
MESSAGE(STATUS "mariadb_c_patches_CMD_OUTPUT:" ${mariadb_c_patches_VARIABLE})

execute_process(
        COMMAND bash "-c" "rm -rf test"
        WORKING_DIRECTORY ${mariadb_connector_SOURCE_DIR}
        RESULT_VARIABLE mariadb_remove_test_result
        OUTPUT_VARIABLE mariadb_remove_test_VARIABLE)
MESSAGE(STATUS "mariadb_remove_test_CMD_ERROR:" ${mariadb_remove_test_result})
MESSAGE(STATUS "mariadb_remove_test_CMD_OUTPUT:" ${mariadb_remove_test_VARIABLE})

execute_process(
        COMMAND bash "-c" "mkdir build"
        WORKING_DIRECTORY ${mariadb_connector_SOURCE_DIR}
        RESULT_VARIABLE mariadb_build_dir_result
        OUTPUT_VARIABLE mariadb_build_dir_VARIABLE)
MESSAGE(STATUS "mariadb_build_dir_CMD_ERROR:" ${mariadb_build_dir_result})
MESSAGE(STATUS "mariadb_build_dir_CMD_OUTPUT:" ${mariadb_build_dir_CMD_OUTPUT})

execute_process(
        COMMAND bash "-c" "cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DMARIADB_LINK_DYNAMIC=ON -DINSTALL_LIB_SUFFIX=${mariadb_connector_SOURCE_DIR}/install -DCMAKE_INSTALL_PREFIX=${mariadb_connector_SOURCE_DIR}/install"
        WORKING_DIRECTORY ${mariadb_connector_SOURCE_DIR}/build
        RESULT_VARIABLE mariadb_cmake_result
        OUTPUT_VARIABLE mariadb_cmake_VARIABLE)
MESSAGE(STATUS "mariadb_cmake_CMD_ERROR:" ${mariadb_cmake_result})
MESSAGE(STATUS "mariadb_cmake_CMD_OUTPUT:" ${mariadb_cmake_VARIABLE})

execute_process(
        COMMAND bash "-c" "make -j$(nproc)"
        COMMAND bash "-c" "make install"
        WORKING_DIRECTORY ${mariadb_connector_SOURCE_DIR}/build
        RESULT_VARIABLE mariadb_install_result
        OUTPUT_VARIABLE mariadb_install_VARIABLE)
MESSAGE(STATUS "mariadb_install_CMD_ERROR:" ${mariadb_install_result})
MESSAGE(STATUS "mariadb_install_CMD_OUTPUT:" ${mariadb_install_VARIABLE})

include_directories(${mariadb_connector_SOURCE_DIR}/install/include)
link_directories(${mariadb_connector_SOURCE_DIR}/install/lib)

set(WINTER_MARIADB_CONNECTOR_LIB ${mariadb_connector_SOURCE_DIR}/install/lib/libmariadbcpp.a ${mariadb_connector_SOURCE_DIR}/install/mariadb/libmariadb.a)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/wintercpp/data/sql/mysql/winter_sql_mysql_driver.h.in ${CMAKE_BINARY_DIR}/generated/wintercpp/data/sql/mysql/winter_sql_mysql_driver.h)