#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${PARENT_DIR}/cmake//host_utils.cmake)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

FetchContent_Declare(
        tacopie
        GIT_REPOSITORY https://github.com/cpp-redis/tacopie.git
        GIT_TAG        master
        GIT_PROGRESS   TRUE
        SOURCE_DIR ${THIRD_PARTY_DIR}/tacopie
)

## cpp_redis
FetchContent_Declare(
        cpp_redis
        GIT_REPOSITORY https://github.com/cpp-redis/cpp_redis.git
        GIT_TAG        master
        GIT_PROGRESS   TRUE
        SOURCE_DIR ${THIRD_PARTY_DIR}/cpp_redis
)


## END cpp_redis

# FetchContent_GetProperties(cpp_redis)
# if(NOT cpp_redis_POPULATED)
#     FetchContent_Populate(cpp_redis)
#     add_subdirectory(${cpp_redis_SOURCE_DIR} ${cpp_redis_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()

FetchContent_MakeAvailable(tacopie cpp_redis)
include_directories(${tacopie_SOURCE_DIR}/includes)
include_directories(${cpp_redis_SOURCE_DIR}/includes)
set(WINTER_REDIS_LIB tacopie cpp_redis )
