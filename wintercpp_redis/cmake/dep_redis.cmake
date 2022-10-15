#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${PARENT_DIR}/cmake//host_utils.cmake)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

## cpp_redis
FetchContent_Declare(
        cpp_redis
        GIT_REPOSITORY https://github.com/cpp-redis/cpp_redis.git
        GIT_TAG        master
        GIT_PROGRESS   TRUE
        SOURCE_DIR ${THIRD_PARTY_DIR}/cpp_redis
)

FetchContent_GetProperties(cpp_redis)
if(NOT cpp_redis_POPULATED)
    FetchContent_Populate(cpp_redis)
endif()

execute_process(
        COMMAND bash "-c" "git submodule init && git submodule update; mkdir build; cd build && cmake .. -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DINSTALL_LIB_SUFFIX=${ssh2_SOURCE_DIR}/install -DCMAKE_INSTALL_PREFIX=${ssh2_SOURCE_DIR}/install && make -j 4 && make install"
        WORKING_DIRECTORY ${cpp_redis_SOURCE_DIR}
        RESULT_VARIABLE cpp_redis_result
        OUTPUT_VARIABLE cpp_redis_VARIABLE)
MESSAGE(STATUS "ssh2_cmake_CMD_ERROR:" ${cpp_redis_result})
MESSAGE(STATUS "ssh2_cmake_CMD_OUTPUT:" ${cpp_redis_VARIABLE})
set(cpp_redis_lib ${cpp_redis_SOURCE_DIR}/install/lib/libcpp_redis.a)
set(tacopie_lib ${cpp_redis_SOURCE_DIR}/install/lib/libtacopie.a)
include_directories(${cpp_redis_SOURCE_DIR}/install/include)
set(WINTER_REDIS_LIB ${tacopie_lib} ${cpp_redis_lib})
## END cpp_redis
