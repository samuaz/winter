#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##      CONFIG BUILD      ##
############################
project( wintercpp_mysql )

get_filename_component(PARENT_DIR ../ ABSOLUTE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
add_compile_definitions(STATIC_CONCPP)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
set(_LIBCPP_INLINE_VISIBILITY "")
set(CMAKE_OPTIMIZE_DEPENDENCIES TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(${CMAKE_BINARY_DIR}/generated)

############################
##      DEPS              ##
############################
include(${PARENT_DIR}/cmake/ClangFormat.cmake)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
set(DCMAKE_FIND_LIBRARY_SUFFIXES .a)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG=TRUE)
endif ()

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

add_library(${PROJECT_NAME} INTERFACE ${HEADERS} ${SOURCES})
add_library(winter::mysql ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries(${PROJECT_NAME} INTERFACE winter::core)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${APP_VERSION} SOVERSION ${APP_VERSION})

function(create_winter_header headerFiles)
    # Create empty output file
    set(output ${CMAKE_CURRENT_SOURCE_DIR}/include/wintercpp/winter_mysql.h)
    file(WRITE ${output} "")
    # Iterate through input files
    file(APPEND ${output} "//\n")
    file(APPEND ${output} "// Created by AZCONA VARGAS, SAMUEL EDUARDO\n")
    file(APPEND ${output} "//\n")
    file(APPEND ${output} "#ifndef WINTERC_WINTER_MYSQL_H\n")
    file(APPEND ${output} "#define WINTERC_WINTER_MYSQL_H\n")
    foreach(bin ${HEADERS})
        string(REGEX REPLACE "(.*)include/" "" filename ${bin})
        IF(NOT ${filename} MATCHES "winter_mysql.h")
        file(APPEND ${output} "#include <${filename}>\n")
        endif()
    endforeach()
    file(APPEND ${output} "#endif // WINTERC_WINTER_MYSQL_H;\n")
endfunction()

create_winter_header(${HEADERS})

set(WINTER_INSTALL_DIR "$ENV{HOME}/winter-release/winter")


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