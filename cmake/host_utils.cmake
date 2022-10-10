#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

###############################
## CONFIG BUILD SYSTEM HOST ##
###############################

# Store in CMAKE_DEB_HOST_ARCH var the current build architecture
execute_process(
     COMMAND bash "-c" "uname -m"
     OUTPUT_VARIABLE CMAKE_HOST_ARCH
     OUTPUT_STRIP_TRAILING_WHITESPACE
)
MESSAGE(STATUS "ARCHITECTURE IS" ${CMAKE_HOST_ARCH})

if (UNIX AND NOT APPLE)
set(HOST_OS "linux" CACHE INTERNAL "")
set(HOST_OS_2 "linux" CACHE INTERNAL "")
set(MYSQL_PLATFORM linux-glibc2.12)
if(${CMAKE_HOST_ARCH} MATCHES "^(x86_64|X64)$")
     set(HOST_ARCHITECTURE "x86_64" CACHE INTERNAL "")
     set(HOST_ARCHITECTURE_2 "x64" CACHE INTERNAL "")
elseif(${CMAKE_HOST_ARCH} MATCHES "^(i386|i686|X32)$")
     set(HOST_ARCHITECTURE "x86_32" CACHE INTERNAL "")
     set(HOST_ARCHITECTURE_2 "i386" CACHE INTERNAL "")
elseif(${CMAKE_HOST_ARCH} MATCHES "^(aarch64|arm64|aarch64_be|armv8b|armv8l)$")
    set(HOST_ARCHITECTURE "aarch_64" CACHE INTERNAL "")
    set(HOST_ARCHITECTURE_2 "aarch64" CACHE INTERNAL "")
endif()
endif()

if (APPLE)
    if(${CMAKE_HOST_ARCH} MATCHES "^(x86_64|X64)$" OR ${CMAKE_OSX_ARCHITECTURES} EQUALS "^(x86_64|X64)$")
    #if(${CMAKE_HOST_ARCH} MATCHES "^(x86_64|X64)$")
     set(HOST_ARCHITECTURE "x86_64" CACHE INTERNAL "")
     set(HOST_ARCHITECTURE_2 "x64" CACHE INTERNAL "")
elseif(${CMAKE_HOST_ARCH} MATCHES "^(i386|i686|X32)$")
     set(HOST_ARCHITECTURE "x86_32" CACHE INTERNAL "")
     set(HOST_ARCHITECTURE_2 "i386" CACHE INTERNAL "")
elseif(${CMAKE_HOST_ARCH} MATCHES "^(aarch64|aarch_64|arm64|aarch64_be|armv8b|armv8l)$")
    set(HOST_ARCHITECTURE "aarch_64" CACHE INTERNAL "")
    set(HOST_ARCHITECTURE_2 "aarch64" CACHE INTERNAL "")
endif()
    set(CMAKE_MACOSX_RPATH 1)
    set(HOST_OS "osx" CACHE INTERNAL "")
    set(HOST_OS_2 "macos" CACHE INTERNAL "")
    set(MYSQL_PLATFORM macos10.14 CACHE INTERNAL "")
endif ()

MESSAGE("Building for ${HOST_OS} and architecture ${HOST_ARCHITECTURE} original architecture is ${CMAKE_HOST_ARCH}")