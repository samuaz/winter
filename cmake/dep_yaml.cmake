#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${CMAKE_CURRENT_LIST_DIR}/host_utils.cmake)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

## yaml_cpp
FetchContent_Declare(
        yaml_cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG        master
        GIT_PROGRESS   TRUE
        SOURCE_DIR ${THIRD_PARTY_DIR}/yaml_cpp
)

FetchContent_GetProperties(yaml_cpp)
if(NOT yaml_cpp_POPULATED)
    FetchContent_Populate(yaml_cpp)
    add_subdirectory(${yaml_cpp_SOURCE_DIR} ${yaml_cpp_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
include_directories(${yaml_cpp_SOURCE_DIR}/include)
set(WINTER_YAML_LIB yaml-cpp)
