#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${CMAKE_CURRENT_LIST_DIR}/host_utils.cmake)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

## googletest ##
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
        SOURCE_DIR ${THIRD_PARTY_DIR}/googletest
)

# FetchContent_GetProperties(googletest)
# if(NOT googletest_POPULATED)
#     FetchContent_Populate(googletest)
#     add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#include_directories(${googletest_SOURCE_DIR}/googlemock/include/)

set(WINTER_GTEST_LIB gtest gmock gtest_main)
## END googletest##
