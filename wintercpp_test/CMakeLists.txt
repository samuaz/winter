#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

set(BINARY wintercpp_test)

############################
##      DEPS              ##
############################
#include(../dependencies.cmake)
#include(../cmake/protobuf.cmake)
include(dependencies.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/ClangFormat.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/astyle_format.cmake)
include(GoogleTest)


enable_testing()
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp *.tpp)

add_executable(${BINARY} ${TEST_SOURCES})

#add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${WINTER_LIBS_TEST} ${EXTRA_LIBRARY} winter::core winter::mysql)

format_with_clang_by_sources(${TEST_SOURCES})

## to make the build finish if the tests fails
add_custom_command(
        TARGET ${BINARY}
        COMMENT "Run tests"
        POST_BUILD
        COMMAND ${BINARY} --output-on-failure
)

gtest_discover_tests(${BINARY})


#[[
target_include_directories(${CMAKE_PROJECT_NAME}_test PUBLIC
        $<BUILD_INTERFACE:/home/samuaz/projects/toc/winter/wintercpp/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}_test>
        )
target_include_directories(${CMAKE_PROJECT_NAME}_test PUBLIC
        $<BUILD_INTERFACE:/home/samuaz/projects/toc/winter/wintercpp/third_party/mysql_connector_cpp_include/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}_test>
        )

target_include_directories(${CMAKE_PROJECT_NAME}_test PUBLIC
        $<BUILD_INTERFACE:/home/samuaz/projects/toc/winter/wintercpp/third_party/boost>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}_test>
        )

target_include_directories(${CMAKE_PROJECT_NAME}_test PUBLIC
        $<BUILD_INTERFACE:/home/samuaz/projects/toc/winter/wintercpp/third_party/mysql_client/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}_test>
        )

target_include_directories(${CMAKE_PROJECT_NAME}_test PUBLIC
        $<BUILD_INTERFACE:/home/samuaz/projects/toc/winter/wintercpp/third_party/openssl/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}_test>
        )

target_include_directories(${CMAKE_PROJECT_NAME}_test PUBLIC
        $<BUILD_INTERFACE:/home/samuaz/projects/toc/winter/wintercpp/third_party/jwt/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}_test>
        )

target_include_directories(${CMAKE_PROJECT_NAME}_test PUBLIC
        $<BUILD_INTERFACE:/home/samuaz/projects/toc/winter/wintercpp/third_party/json/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}_test>
        )

target_include_directories(${CMAKE_PROJECT_NAME}_test PUBLIC
        $<BUILD_INTERFACE:/home/samuaz/projects/toc/winter/wintercpp/third_party/grpc/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}_test>
        )

target_include_directories(${CMAKE_PROJECT_NAME}_test PUBLIC
        $<BUILD_INTERFACE:/home/samuaz/projects/toc/winter/wintercpp/third_party/protobuf/src>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}_test>
        )

target_include_directories(${CMAKE_PROJECT_NAME}_test PUBLIC
        $<BUILD_INTERFACE:/home/samuaz/projects/toc/winter/wintercpp/third_party/yaml_cpp/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}_test>
        )

target_include_directories(${CMAKE_PROJECT_NAME}_test PUBLIC
        $<BUILD_INTERFACE:/home/samuaz/projects/toc/winter/wintercpp/third_party/cpp_redis/includes>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}_test>
        )


target_include_directories(${CMAKE_PROJECT_NAME}_test PUBLIC
        $<BUILD_INTERFACE:/home/samuaz/projects/toc/winter/wintercpp/third_party/cpp_redis/tacopie/includes>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        )]]
