#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#
#set(PROTOBUF_INPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/proto")
#set(PROTOBUF_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/src/proto")
#set(PROTOBUF_EXTRA_INPUT_DIRECTORY "")
MESSAGE(STATUS "PROTOBUF_INPUT_DIRECTORY:" ${PROTOBUF_INPUT_DIRECTORY})
MESSAGE(STATUS "PROTOBUF_OUTPUT_DIRECTORY:" ${PROTOBUF_OUTPUT_DIRECTORY})

############################
##    PERMISSIONS         ##
############################
execute_process(COMMAND chmod +x ${protobuf_compiler_SOURCE_DIR}/bin/protoc
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE PROTOBUF_PERMISSION_RESULT
        OUTPUT_VARIABLE PROTOBUF_PERMISSION_OUTPUT_VARIABLE)
MESSAGE(STATUS "PROTO_PERMISSION_CMD_ERROR:" ${PROTOBUF_PERMISSION_RESULT})
MESSAGE(STATUS "PROTO_PERMISSION_CMD_OUTPUT:" ${PROTOBUF_PERMISSION_OUTPUT_VARIABLE})

execute_process(COMMAND chmod +x ${grpc_plugin_SOURCE_DIR}/grpc_cpp_plugin
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE GRPC_PERMISSION_RESULT
        OUTPUT_VARIABLE GRPC_PERMISSION_OUTPUT_VARIABLE)
MESSAGE(STATUS "GRPC_PERMISSION_CMD_ERROR:" ${GRPC_PERMISSION_RESULT})
MESSAGE(STATUS "GRPC_PERMISSION_CMD_OUTPUT:" ${GRPC_PERMISSION_OUTPUT_VARIABLE})
############################
##    END PERMISSIONS     ##
############################

############################
##    PROTOBUF FILES      ##
############################
message("***************************** CREATING PROTOBUF **************************************")
# this do:
# - search al .proto files in the PROTOBUF_INPUT_DIRECTORY
# - we do a foreach in the list of all proto files
# - because services use grpc so we need to build services with grpc plugin so we search for files that contains service word to create the grpc files
# - we build all our proto models and services
# - we add all our generated clases and headers to the include sources
execute_process(COMMAND rm -r ${PROTOBUF_OUTPUT_DIRECTORY})
execute_process(COMMAND mkdir -p ${PROTOBUF_OUTPUT_DIRECTORY})
execute_process(COMMAND touch ${PROTOBUF_OUTPUT_DIRECTORY}/generated_protos_are_here)
file(GLOB PROTOBUF_DEFINITION_FILES "${PROTOBUF_INPUT_DIRECTORY}/*.proto")

foreach (file ${PROTOBUF_DEFINITION_FILES})
    message("***************************** CREATING ${file} IN ${PROTOBUF_OUTPUT_DIRECTORY}  **************************************")
    if (file MATCHES "service" OR file MATCHES "controller")
        MESSAGE(${file})
        execute_process(COMMAND ${PROTO_BINARY} -I ${PROTOBUF_INPUT_DIRECTORY}  --grpc_out=${PROTOBUF_OUTPUT_DIRECTORY} --plugin=protoc-gen-grpc=${GRPC_PLUGIN} ${file}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                RESULT_VARIABLE PROTOBUF_GRPC_RESULT
                OUTPUT_VARIABLE PROTOBUF_GRPC_OUTPUT_VARIABLE)
        MESSAGE(STATUS "PROTO_GRPC_CMD_ERROR:" ${PROTOBUF_GRPC_RESULT})
        MESSAGE(STATUS "PROTO_GRPC_CMD_OUTPUT:" ${PROTOBUF_GRPC_OUTPUT_VARIABLE})
        execute_process(COMMAND ${PROTO_BINARY} -I ${PROTOBUF_INPUT_DIRECTORY}  --cpp_out=${PROTOBUF_OUTPUT_DIRECTORY} ${file}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                RESULT_VARIABLE PROTOBUF_RESULT
                OUTPUT_VARIABLE PROTOBUF_OUTPUT_VARIABLE)
        MESSAGE(STATUS "PROTO_CMD_ERROR:" ${PROTOBUF_RESULT})
        MESSAGE(STATUS "PROTO_CMD_OUTPUT:" ${PROTOBUF_OUTPUT_VARIABLE})
    else ()
        MESSAGE(${file})
        execute_process(COMMAND ${PROTO_BINARY} -I ${PROTOBUF_INPUT_DIRECTORY}  --cpp_out=${PROTOBUF_OUTPUT_DIRECTORY} ${file}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                RESULT_VARIABLE PROTOBUF_RESULT
                OUTPUT_VARIABLE PROTOBUF_OUTPUT_VARIABLE)
        MESSAGE(STATUS "PROTO_CMD_ERROR:" ${PROTOBUF_RESULT})
        MESSAGE(STATUS "PROTO_CMD_OUTPUT:" ${PROTOBUF_OUTPUT_VARIABLE})
    endif ()
endforeach ()

file(GLOB PROTOBUF_MODELS_INCLUDES "${PROTOBUF_OUTPUT_DIRECTORY}/*.cc" "${PROTOBUF_OUTPUT_DIRECTORY}/*.h")

############################
##    END PROTOBUF FILES  ##
############################
