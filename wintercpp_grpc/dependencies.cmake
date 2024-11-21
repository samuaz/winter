#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##     EXTERNAL LIBS      ##
############################
find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
#protoc 
set(PROTO_BINARY "${Protobuf_PROTOC_EXECUTABLE}" CACHE INTERNAL "")
find_library(PROTOBUF_LIBRARY NAMES protobuf)
find_library(PROTOC_LIBRARY NAMES protoc)
#GPRC
find_program(grpc_cpp_plugin grpc_cpp_plugin)
find_library(GRPC_LIBRARY NAMES grpc)
find_library(GRPCPP_LIBRARY NAMES grpc++)
find_library(GPR_LIBRARY NAMES gpr)
set(GRPC_PLUGIN ${grpc_cpp_plugin} CACHE INTERNAL "")
set(WINTER_GRPC_LIB ${GRPCPP_LIBRARY} ${GRPC_LIBRARY} ${GPR_LIBRARY})
set(WINTER_PROTOBUF_LIB protobuf::libprotobuf)
set(WINTER_GRPC_LIBS ${WINTER_PROTOBUF_LIB} gRPC::grpc++)
IF (WINTER_WITH_TEST)
find_package(GTest REQUIRED)
set(WINTER_LIBS_TEST gtest::gtest)
ENDIF()

