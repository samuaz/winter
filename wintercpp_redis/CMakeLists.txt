#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

############################
##      CONFIG BUILD      ##
############################
cmake_minimum_required(VERSION 3.15)
set(APP_NAME wintercpp_redis)
set(APP_VERSION 0.1)
set(APP_DESCRIPTION "winterc++ core framework to build microservices using cpp")
project(${APP_NAME} VERSION ${APP_VERSION} DESCRIPTION ${APP_DESCRIPTION})

############################
##      COMMONS           ##
############################
get_filename_component(PARENT_DIR ../ ABSOLUTE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(_LIBCPP_INLINE_VISIBILITY "")
set(CMAKE_OPTIMIZE_DEPENDENCIES TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_BINARY_DIR}/generated)

include(${PARENT_DIR}/cmake/ClangFormat.cmake)

# Set a default build type if none was specified
set(default_build_type "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
            STRING "Choose the type of build." FORCE)
    # Set the possible set_values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# assume built-in pthreads on MacOS
IF(APPLE)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
ENDIF()

##grpc fails to build generated_message_util.h:224:14: error: zero size arrays are an extension [-Werror,-Wzero-length-array]
## so workarround disable -pedantic-errors
#set(CMAKE_CXX_FLAGS_DEBUG "-O3 -g -pedantic-errors -Wall -Wextra ")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DEBUG -O0 -g2 -ggdb -Wall -Wextra -fsanitize=address -fdiagnostics-color=auto -fno-omit-frame-pointer -ftemplate-backtrace-limit=0 -Werror=return-type")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DEBUG -O0 -g2 -ggdb -Wall -Wextra -fsanitize=address -fdiagnostics-color=auto -fno-omit-frame-pointer -ftemplate-backtrace-limit=0 -Werror=return-type")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -pipe -fno-unroll-loops -fmerge-all-constants -fno-ident -ffunction-sections -fdata-sections -Bsymbolic-functions -fpie -Wall -Werror=return-type")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -pipe -fno-unroll-loops -fmerge-all-constants -fno-ident -ffunction-sections -fdata-sections -Bsymbolic-functions -fpie -Wall -Werror=return-type")

############################
##     END COMMONS        ##
############################

############################
##      DEPS              ##
############################
include(dependencies.cmake)

############################
##    CREATE EXECUTABLE   ##
############################

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

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
add_library(winter::redis ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} winter::core ${WINTER_REDIS_LIBS} ${EXTRA_LIBRARY}) ## the test target is going to use this as definition source
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${APP_VERSION} SOVERSION ${APP_VERSION})

function(create_winter_header headerFiles)
    # Create empty output file
    set(output ${CMAKE_CURRENT_SOURCE_DIR}/include/wintercpp/winter_redis.h)
    file(WRITE ${output} "")
    # Iterate through input files
    file(APPEND ${output} "//\n")
    file(APPEND ${output} "// Created by AZCONA VARGAS, SAMUEL EDUARDO\n")
    file(APPEND ${output} "//\n")
    file(APPEND ${output} "#ifndef WINTERC_WINTER_REDIS_H\n")
    file(APPEND ${output} "#define WINTERC_WINTER_REDIS_H\n")
    foreach(bin ${HEADERS})
        string(REGEX REPLACE "(.*)include/" "" filename ${bin})
        IF(NOT ${filename} MATCHES "winter_redis.h")
        file(APPEND ${output} "#include <${filename}>\n")
        endif()
    endforeach()
    file(APPEND ${output} "#endif // WINTERC_WINTER_REDIS_H;\n")
endfunction()

create_winter_header(${HEADERS})

set(WINTER_INSTALL_DIR "$ENV{HOME}/winter-release/winter")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/generated)   
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/cpp_redis/includes)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/cpp_redis/tacopie/includes)

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
set(wintercpp_redis_test_binary ${PROJECT_NAME}_test)
include(GoogleTest)
enable_testing()
add_executable(${wintercpp_redis_test_binary} ${TEST_SOURCES})
target_link_libraries(${wintercpp_redis_test_binary} PUBLIC ${WINTER_LIBS_TEST} ${EXTRA_LIBRARY} winter::core winter::redis)
format_with_clang_by_sources(${TEST_SOURCES})
## to make the build finish if the tests fails
add_custom_command(
        TARGET ${wintercpp_redis_test_binary}
        COMMENT "Run wintercpp_redis_test_binary tests"
        POST_BUILD
        COMMAND ${wintercpp_redis_test_binary} --output-on-failure
)
gtest_discover_tests(${wintercpp_redis_test_binary})
ENDIF()
############################
##  END TEST ##
############################