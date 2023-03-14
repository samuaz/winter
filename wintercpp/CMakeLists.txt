#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##      CONFIG BUILD      ##
############################
project( wintercpp_core )
get_filename_component(PARENT_DIR ../ ABSOLUTE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
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

############################
##      DEPS              ##
############################
include(dependencies.cmake)
include(${PARENT_DIR}/cmake/ClangFormat.cmake)


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
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/generated)    
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

target_include_directories(${PROJECT_NAME} PUBLIC ${OPENSSL_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/json/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/jwt/include)

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

############################
##  TEST ##
############################

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false test/*.cpp)
IF (WINTER_WITH_TEST AND TEST_SOURCES)
set(wintercpp_core_binary ${PROJECT_NAME}_test)
include(GoogleTest)
enable_testing()
add_executable(${wintercpp_core_binary} ${TEST_SOURCES})
target_link_libraries(${wintercpp_core_binary} PUBLIC ${WINTER_LIBS_TEST} ${EXTRA_LIBRARY} winter::core)
format_with_clang_by_sources(${TEST_SOURCES})
## to make the build finish if the tests fails
add_custom_command(
        TARGET ${wintercpp_core_binary}
        COMMENT "Run wintercpp_core_binary tests"
        POST_BUILD
        COMMAND ${wintercpp_core_binary} --output-on-failure
)
gtest_discover_tests(${wintercpp_core_binary})
ENDIF()

############################
##  END TEST ##
############################