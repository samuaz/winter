#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${CMAKE_CURRENT_LIST_DIR}/host_utils.cmake)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG master
        SOURCE_DIR ${THIRD_PARTY_DIR}/json
)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
include_directories(${json_SOURCE_DIR}/include/)