#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

include(${PARENT_DIR}/cmake/host_utils.cmake)
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

## grpc ##
FetchContent_Declare(
        grpc
        GIT_REPOSITORY https://github.com/grpc/grpc.git
        GIT_TAG        v1.49.0
        GIT_PROGRESS   TRUE 
        SOURCE_DIR ${THIRD_PARTY_DIR}/grpc
)

set(BUILD_TESTING OFF CACHE INTERNAL "")
set(gRPC_BUILD_TESTS OFF CACHE INTERNAL "")
set(gRPC_RE2_PROVIDER package CACHE INTERNAL "")
set(gRPC_BUILD_GRPC_CPP_PLUGIN ON CACHE INTERNAL "")
set(gRPC_BUILD_GRPC_CSHARP_PLUGIN OFF CACHE INTERNAL "")
set(gRPC_BUILD_GRPC_NODE_PLUGIN OFF CACHE INTERNAL "")
set(gRPC_BUILD_GRPC_OBJECTIVE_C_PLUGIN OFF CACHE INTERNAL "")
set(gRPC_BUILD_GRPC_PHP_PLUGIN OFF CACHE INTERNAL "")
set(gRPC_BUILD_GRPC_PYTHON_PLUGIN OFF CACHE INTERNAL "")
set(gRPC_BUILD_GRPC_RUBY_PLUGIN OFF CACHE INTERNAL "")
set(gRPC_SSL_PROVIDER package CACHE INTERNAL "")

#FetchContent_MakeAvailable(re2 grpc)

if(NOT grpc_POPULATED)
    FetchContent_Populate(grpc)
endif()

execute_process(
        COMMAND bash "-c" "patch -p1 < ${CMAKE_CURRENT_SOURCE_DIR}/cmake/patches/grpc_gzlib.patch"
        WORKING_DIRECTORY ${grpc_SOURCE_DIR}
        RESULT_VARIABLE grpc_gzlib_patches_result
        OUTPUT_VARIABLE grpc_gzlib_patches_VARIABLE)
MESSAGE(STATUS "grpc_gzlib_patches_CMD_ERROR:" ${grpc_gzlib_patches_result})
MESSAGE(STATUS "grpc_gzlib_patches_CMD_OUTPUT:" ${grpc_gzlib_patches_VARIABLE})

execute_process(
        COMMAND bash "-c" "patch -p1 < ${CMAKE_CURRENT_SOURCE_DIR}/cmake/patches/grpc_gzread.patch"
        WORKING_DIRECTORY ${grpc_SOURCE_DIR}
        RESULT_VARIABLE grpc_gzread_patches_result
        OUTPUT_VARIABLE grpc_gzread_patches_VARIABLE)
MESSAGE(STATUS "grpc_gzread_patches_CMD_ERROR:" ${grpc_gzread_patches_result})
MESSAGE(STATUS "grpc_gzread_patches_CMD_OUTPUT:" ${grpc_gzread_patches_VARIABLE})

execute_process(
        COMMAND bash "-c" "patch -p1 < ${CMAKE_CURRENT_SOURCE_DIR}/cmake/patches/grpc_gzwrite.patch"
        WORKING_DIRECTORY ${grpc_SOURCE_DIR}
        RESULT_VARIABLE grpc_gzwrite_patches_result
        OUTPUT_VARIABLE grpc_gzwrite_patches_VARIABLE)
MESSAGE(STATUS "grpc_gzwrite_patches_CMD_ERROR:" ${grpc_gzwrite_patches_result})
MESSAGE(STATUS "grpc_gzwrite_patches_CMD_OUTPUT:" ${grpc_gzwrite_patches_VARIABLE})

# FetchContent_GetProperties(re2)
# if(NOT re2_POPULATED)
#     FetchContent_Populate(re2)
#     add_subdirectory(${re2_SOURCE_DIR} ${re2_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()

# FetchContent_GetProperties(grpc)
# if(NOT grpc_POPULATED)
#     FetchContent_Populate(grpc)
#     add_subdirectory(${grpc_SOURCE_DIR} ${grpc_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()

execute_process(
        COMMAND bash "-c" "git submodule update --init --recursive"
        WORKING_DIRECTORY ${grpc_SOURCE_DIR}
        RESULT_VARIABLE grpc_init_result
        OUTPUT_VARIABLE grpc_init_VARIABLE)
MESSAGE(STATUS "grpc_init_CMD_ERROR:" ${grpc_init_result})
MESSAGE(STATUS "grpc_init_CMD_OUTPUT:" ${grpc_init_VARIABLE})
MESSAGE("USING Protobuf_LIBRARIES ${Protobuf_LIBRARIES}")
MESSAGE("USING gRPC_PROTOBUF_PROVIDER ${gRPC_PROTOBUF_PROVIDER}")
MESSAGE("USING Protobuf_INCLUDE_DIR ${Protobuf_INCLUDE_DIR}")
MESSAGE("USING Protobuf_PROTOC_LIBRARY ${Protobuf_PROTOC_LIBRARY}")

execute_process(
        COMMAND bash "-c" "mkdir -p build_grpc; cd build_grpc && \
        cmake .. -DCMAKE_BUILD_TYPE=Release \
        -DgRPC_BUILD_TESTS=OFF  \
        -DgRPC_BUILD_GRPC_CPP_PLUGIN=ON \
        -DgRPC_BUILD_GRPC_CSHARP_PLUGIN=OFF \
        -DgRPC_BUILD_GRPC_NODE_PLUGIN=OFF \
        -DgRPC_BUILD_GRPC_OBJECTIVE_C_PLUGIN=OFF \
        -DgRPC_BUILD_GRPC_PYTHON_PLUGIN=OFF \
        -DgRPC_BUILD_GRPC_RUBY_PLUGIN=OFF \
        -DgRPC_BUILD_GRPC_PHP_PLUGIN=OFF \
        -DgRPC_BUILD_GRPC_JAVA_PLUGIN=OFF \
        -DgRPC_SSL_PROVIDER=package \
        -DgRPC_PROTOBUF_PROVIDER=${gRPC_PROTOBUF_PROVIDER} \
        -DProtobuf_LIBRARIES=${Protobuf_LIBRARIES} \
        -DProtobuf_INCLUDE_DIR=${Protobuf_INCLUDE_DIR} \
        -DProtobuf_PROTOC_LIBRARY={Protobuf_PROTOC_LIBRARY} \
        -DCMAKE_INSTALL_PREFIX=${grpc_SOURCE_DIR}/install && make && make install "
        WORKING_DIRECTORY ${grpc_SOURCE_DIR}
        RESULT_VARIABLE grpc_install_result
        OUTPUT_VARIABLE grpc_install_VARIABLE)
MESSAGE(STATUS "grpc_install_CMD_ERROR:" ${grpc_install_result})
MESSAGE(STATUS "grpc_install_CMD_OUTPUT:" ${grpc_install_VARIABLE})
link_directories(${grpc_SOURCE_DIR}/install/lib)
set(grpc_SOURCE_DIR ${grpc_SOURCE_DIR} CACHE INTERNAL "")
set(grpc_INCLUDE_DIR ${grpc_SOURCE_DIR}/install/include CACHE INTERNAL "")
include_directories(grpc_INCLUDE_DIR)
set(WINTER_GRPC_LIB ${grpc_SOURCE_DIR}/install/lib/libgrpc++.a CACHE INTERNAL "")

