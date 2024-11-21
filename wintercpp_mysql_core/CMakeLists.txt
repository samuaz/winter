cmake_minimum_required(VERSION 3.15)
set(APP_NAME wintercpp_mysql_core)
set(APP_VERSION 0.1)
set(APP_DESCRIPTION "winterc++ core framework to build microservices using cpp")
project(${APP_NAME} VERSION ${APP_VERSION} DESCRIPTION ${APP_DESCRIPTION})

set(WINTER_WITH_TEST ON)
include(dependencies.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(default_build_type "Release")
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if(APPLE)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
endif()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DEBUG -O0 -g2 -ggdb -Wall -Wextra -fsanitize=address -fdiagnostics-color=auto -fno-omit-frame-pointer -ftemplate-backtrace-limit=0 -Werror=return-type")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DEBUG -O0 -g2 -ggdb -Wall -Wextra -fsanitize=address -fdiagnostics-color=auto -fno-omit-frame-pointer -ftemplate-backtrace-limit=0 -Werror=return-type")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -pipe -fno-unroll-loops -fmerge-all-constants -fno-ident -ffunction-sections -fdata-sections -Bsymbolic-functions -fpie -Wall -Werror=return-type")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -pipe -fno-unroll-loops -fmerge-all-constants -fno-ident -ffunction-sections -fdata-sections -Bsymbolic-functions -fpie -Wall -Werror=return-type")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG=TRUE)
endif()

file(GLOB_RECURSE HEADERS LIST_DIRECTORIES false include/wintercpp/*.h)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false src/*.cpp include/wintercpp/*.tpp)

add_library(${APP_NAME} INTERFACE)
add_library(winter::mysql_core ALIAS ${APP_NAME})

target_include_directories(${APP_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(${APP_NAME} INTERFACE winter::core)

set_target_properties(${APP_NAME} PROPERTIES VERSION ${APP_VERSION} SOVERSION ${APP_VERSION})

include(GNUInstallDirs)
install(TARGETS ${APP_NAME}
        EXPORT ${APP_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/wintercpp/"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/wintercpp)

install(EXPORT ${APP_NAME}Targets
        FILE ${APP_NAME}Targets.cmake
        NAMESPACE winter::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${APP_NAME})

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}ConfigVersion.cmake
        VERSION ${APP_VERSION}
        COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}Config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${APP_NAME}
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${APP_NAME})

export(EXPORT ${APP_NAME}Targets
        FILE ${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}Targets.cmake
        NAMESPACE winter::)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false test/*.cpp)
if (WINTER_WITH_TEST AND TEST_SOURCES)
    set(wintercpp_mysql_core_binary ${APP_NAME}_test)
    include(GoogleTest)
    enable_testing()
    add_executable(${wintercpp_mysql_core_binary} ${TEST_SOURCES})
    target_include_directories(${wintercpp_mysql_core_binary} PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_BINARY_DIR}/generated
    )
    target_link_libraries(${wintercpp_mysql_core_binary} PUBLIC ${WINTER_LIBS_TEST} ${EXTRA_LIBRARY} winter::core ${APP_NAME})
    add_custom_command(
            TARGET ${wintercpp_mysql_core_binary}
            COMMENT "Run wintercpp_mysql_core_binary tests"
            POST_BUILD
            COMMAND ${wintercpp_mysql_core_binary} --output-on-failure
    )
    gtest_discover_tests(${wintercpp_mysql_core_binary})
endif()
