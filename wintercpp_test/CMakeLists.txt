#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#
set(CMAKE_CXX_STANDARD 17)
set(BINARY wintercpp_test)
set(WINTER_MARIADB_DRIVER true CACHE INTERNAL "WINTER_MARIADB_DRIVER")
#set(OPENSSL_CRYPTO_LIBRARY "/lib/libcrypto.a" CACHE INTERNAL "OPENSSL_CRYPTO_LIBRARY")
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

target_link_libraries(${BINARY} PUBLIC ${WINTER_LIBS_TEST} ${EXTRA_LIBRARY} winter::core winter::mariadb winter::mysql winter::grpc winter::redis)

format_with_clang_by_sources(${TEST_SOURCES})

## to make the build finish if the tests fails
add_custom_command(
        TARGET ${BINARY}
        COMMENT "Run tests"
        POST_BUILD
        COMMAND ${BINARY} --output-on-failure
)

gtest_discover_tests(${BINARY})