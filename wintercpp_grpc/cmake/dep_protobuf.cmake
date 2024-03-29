#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#
include(${PARENT_DIR}/cmake/host_utils.cmake)
set(WINTER_PROTOBUF_VERSION 21.6 CACHE INTERNAL "default winter protobuf version")
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
FetchContent_Declare(
        protobuf
        GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
        GIT_TAG        v${WINTER_PROTOBUF_VERSION}
        SOURCE_DIR ${THIRD_PARTY_DIR}/protobuf
)
set(Protobuf_USE_STATIC_LIBS ON CACHE INTERNAL "use static protobuf")
set(protobuf_BUILD_TESTS OFF CACHE INTERNAL "turn off proto tests")
set(gRPC_PROTOBUF_PROVIDER package CACHE INTERNAL "not use internal protobuf")
# FetchContent_GetProperties(protobuf)
# if(NOT protobuf_POPULATED)
#     FetchContent_Populate(protobuf)
#     if (TARGET libprotobuf)
#         RETURN()
#     endif()
#     add_subdirectory(${protobuf_SOURCE_DIR}/cmake ${protobuf_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()

if(NOT protobuf_POPULATED)
    FetchContent_Populate(protobuf)
endif()

#FetchContent_MakeAvailable(protobuf)

execute_process(
        COMMAND bash "-c" "git submodule update --init --recursive"
        WORKING_DIRECTORY ${protobuf_SOURCE_DIR}
        RESULT_VARIABLE protobuf_init_result
        OUTPUT_VARIABLE protobuf_init_VARIABLE)
MESSAGE(STATUS "protobuf_init_CMD_ERROR:" ${protobuf_init_result})
MESSAGE(STATUS "protobuf_init_CMD_OUTPUT:" ${protobuf_init_VARIABLE})

execute_process(
        COMMAND bash "-c" "mkdir -p build; cd build && cmake -DCMAKE_BUILD_TYPE=Release -Dprotobuf_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=${protobuf_SOURCE_DIR}/install ../cmake && make -j$(nproc) && make install "
        WORKING_DIRECTORY ${protobuf_SOURCE_DIR}
        RESULT_VARIABLE protobuf_install_result
        OUTPUT_VARIABLE protobuf_install_VARIABLE)
MESSAGE(STATUS "protobuf_install_CMD_ERROR:" ${protobuf_install_result})
MESSAGE(STATUS "protobuf_install_CMD_OUTPUT:" ${protobuf_install_VARIABLE})

set(protobuf_SOURCE_DIR ${protobuf_SOURCE_DIR} CACHE STRING "" FORCE)
set(Protobuf_ROOT_DIR ${protobuf_SOURCE_DIR}/install CACHE STRING "" FORCE)
set(Protobuf_LIBRARIES ${protobuf_SOURCE_DIR}/install/lib CACHE STRING "" FORCE)
set(Protobuf_INCLUDE_DIR ${protobuf_SOURCE_DIR}/install/include CACHE STRING "" FORCE)
set(Protobuf_PROTOC_LIBRARY ${protobuf_SOURCE_DIR}/install/lib/libprotoc.a CACHE STRING "" FORCE)
set(Protobuf_LIBRARY ${protobuf_SOURCE_DIR}/install/lib/libprotobuf.a CACHE STRING "" FORCE)
set(Protobuf_PROTOC_EXECUTABLE ${protobuf_SOURCE_DIR}/install/bin/protoc CACHE STRING "" FORCE)
link_directories(${Protobuf_LIBRARIES})
include_directories(Protobuf_INCLUDE_DIR)
set(WINTER_PROTOBUF_LIB ${Protobuf_LIBRARIES}/libprotobuf.a ${Protobuf_LIBRARIES}/libprotoc.a)
#set(WINTER_PROTOBUF_LIB protobuf::libprotobuf)