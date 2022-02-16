#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##      CONFIG BUILD      ##
############################
project( wintercpp_core )
get_filename_component(PARENT_DIR ../ ABSOLUTE)
set(CMAKE_CXX_STANDARD 20)
add_compile_definitions(STATIC_CONCPP)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
set(_LIBCPP_INLINE_VISIBILITY "")
set(CMAKE_OPTIMIZE_DEPENDENCIES TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


option(APP_ENV "APP_ENV" local)
message("***************************** ENVIRONMENT IS ${APP_ENV} **************************************")
if (APP_ENV)
else ()
    message("***************************** NOT ENV **************************************")
    message("local AS DEFAULT")
    set(APP_ENV local)
endif (APP_ENV)

execute_process(COMMAND rm -f ${CMAKE_BINARY_DIR}/generated)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/wintercpp/config/winter_env.h.in  ${CMAKE_BINARY_DIR}/generated/wintercpp/config/winter_env.h)
include_directories(${CMAKE_BINARY_DIR}/generated)

############################
##      DEPS              ##
############################
include(dependencies.cmake)
include(${PARENT_DIR}/cmake/ClangFormat.cmake)

############################2
##    CREATE EXECUTABLE   ##
############################

if (CMAKE_VERSION VERSION_LESS 3.12)
    #add_definitions(STATIC_CONCPP)
else ()
    add_compile_definitions(STATIC_CONCPP)
endif ()

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
set(DCMAKE_FIND_LIBRARY_SUFFIXES .a)

############################
##       FLAGS           ##
############################
if (UNIX AND NOT APPLE)
    set(EXTRA_LIBRARY "-pthread -lstdc++ -lrt -lresolv")
endif ()

if (APPLE)
    #set(EXTRA_LIBRARY "-pthread -lstdc++ -lresolv")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG=TRUE)
endif ()

message("***************************** LIBRARY ${WINTER_LIBS} **************************************")
file(GLOB_RECURSE HEADERS LIST_DIRECTORIES false include/wintercpp/*.h)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false src/*.cpp include/wintercpp/*.tpp)

foreach(file ${HEADERS})
    format_with_clang(${file})
endforeach()

foreach(file ${SOURCES})
    format_with_clang(${file})
endforeach()

#format_with_astyle_by_sources(${SOURCES})
#format_with_astyle_by_sources(${HEADERS})

add_library(${PROJECT_NAME} STATIC ${PROTOBUF_MODELS_INCLUDES} ${HEADERS} ${SOURCES})
add_library(winter::core ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} ${WINTER_LIBS} ${EXTRA_LIBRARY}) ## the test target is going to use this as definition source
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${APP_VERSION} SOVERSION ${APP_VERSION})

function(create_winter_header headerFiles)
    # Create empty output file
    set(output ${CMAKE_CURRENT_SOURCE_DIR}/include/wintercpp/winter.h)
    file(WRITE ${output} "")
    # Iterate through input files
    file(APPEND ${output} "//\n")
    file(APPEND ${output} "// Created by AZCONA VARGAS, SAMUEL EDUARDO\n")
    file(APPEND ${output} "//\n")
    file(APPEND ${output} "#ifndef WINTERC_WINTER_H\n")
    file(APPEND ${output} "#define WINTERC_WINTER_H\n")
    foreach(bin ${HEADERS})
        string(REGEX REPLACE "(.*)include/" "" filename ${bin})
        IF(NOT ${filename} MATCHES "winter.h")
        file(APPEND ${output} "#include <${filename}>\n")
        endif()
    endforeach()
    file(APPEND ${output} "#endif // WINTERC_WINTER_H;\n")
endfunction()

create_winter_header(${HEADERS})

set(WINTER_INSTALL_DIR "$ENV{HOME}/winter-release/winter")

# target_include_directories(${PROJECT_NAME} PUBLIC
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#         $<INSTALL_INTERFACE:include/${APP_NAME}>
#         )

# target_include_directories(${PROJECT_NAME} PUBLIC
#         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>
#         $<INSTALL_INTERFACE:include/${APP_NAME}>
#         )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/generated)        


       
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/openssl/include)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/jwt/include)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/json/include)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/grpc/include)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/protobuf/src)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/yaml_cpp/include)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/cpp_redis/includes)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/cpp_redis/tacopie/includes)


# target_include_directories(${PROJECT_NAME} PUBLIC
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/openssl/include>
#         $<INSTALL_INTERFACE:include/${APP_NAME}>
#         )

# target_include_directories(${PROJECT_NAME} PUBLIC
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/jwt/include>
#         $<INSTALL_INTERFACE:include/${APP_NAME}>
#         )

# target_include_directories(${PROJECT_NAME} PUBLIC
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/json/include>
#         $<INSTALL_INTERFACE:include/${APP_NAME}>
#         )

# target_include_directories(${PROJECT_NAME} PUBLIC
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/grpc/include>
#         $<INSTALL_INTERFACE:include/${APP_NAME}>
#         )

# target_include_directories(${PROJECT_NAME} PUBLIC
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/protobuf/src>
#         $<INSTALL_INTERFACE:include/${APP_NAME}>
#         )

# target_include_directories(${PROJECT_NAME} PUBLIC
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/yaml_cpp/include>
#         $<INSTALL_INTERFACE:include/${APP_NAME}>
#         )

# target_include_directories(${PROJECT_NAME} PUBLIC
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/cpp_redis/includes>
#         $<INSTALL_INTERFACE:include/${APP_NAME}>
#         )

# target_include_directories(${PROJECT_NAME} PUBLIC
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/cpp_redis/tacopie/includes>
#         $<INSTALL_INTERFACE:include/${APP_NAME}>
#         )

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" # source directory
        DESTINATION ${WINTER_INSTALL_DIR}/include/${APP_NAME} # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.h*" # select header files
        )
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" # source directory
        DESTINATION ${WINTER_INSTALL_DIR}/include/${APP_NAME} # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.tpp*" # select header files
        )

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cmake" # source directory
        DESTINATION ${WINTER_INSTALL_DIR}/include/${APP_NAME}/cmake # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.cmake*" # select header files
        )

install(TARGETS ${PROJECT_NAME} DESTINATION ${WINTER_INSTALL_DIR}/lib/)


############################
##  END CREATE EXECUTALBE ##
############################