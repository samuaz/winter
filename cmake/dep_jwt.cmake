#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${CMAKE_CURRENT_LIST_DIR}/host_utils.cmake)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

## JWT
set(CPP_JWT_USE_VENDORED_NLOHMANN_JSON ON CACHE INTERNAL "")
set(CPP_JWT_BUILD_TESTS FALSE CACHE INTERNAL "")
set(CPP_JWT_BUILD_EXAMPLES FALSE CACHE INTERNAL "")
FetchContent_Declare(
        jwt
        GIT_REPOSITORY https://github.com/arun11299/cpp-jwt.git
        GIT_TAG master
        SOURCE_DIR ${THIRD_PARTY_DIR}/jwt
)

FetchContent_GetProperties(jwt)
if(NOT jwt_POPULATED)
     FetchContent_Populate(jwt)
     #add_subdirectory(${jwt_SOURCE_DIR} ${jwt_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

#FetchContent_MakeAvailable(jwt)
include_directories(${jwt_SOURCE_DIR}/include/)
