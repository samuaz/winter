#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${CMAKE_CURRENT_LIST_DIR}/host_utils.cmake)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

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

FetchContent_MakeAvailable(cpp_redis)
include_directories(${cpp_redis_SOURCE_DIR}/tacopie/includes)
include_directories(${cpp_redis_SOURCE_DIR}/includes)
set(WINTER_REDIS_LIB cpp_redis tacopie)
