#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

###############################
## CONFIG BUILD SYSTEM HOST ##
###############################

if (UNIX AND NOT APPLE)

# Store in CMAKE_DEB_HOST_ARCH var the current build architecture
execute_process(COMMAND
  uname -m
  OUTPUT_VARIABLE CMAKE_HOST_ARCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(HOST_OS "linux")
set(HOST_OS_2 "linux")
set(MYSQL_PLATFORM linux-glibc2.12)
if(${CMAKE_HOST_ARCH} MATCHES "^(x86_64|X64)$")
     set(HOST_ARCHITECTURE "x86_64")
     set(HOST_ARCHITECTURE_2 "X64")
elseif(${CMAKE_HOST_ARCH} MATCHES "^(i386|i686|X32)$")
     set(HOST_ARCHITECTURE "x86_32")
     set(HOST_ARCHITECTURE_2 "i386")
elseif(${CMAKE_HOST_ARCH} MATCHES "^(aarch64|arm64|aarch64_be|armv8b|armv8l)$")
    set(HOST_ARCHITECTURE "aarch_64")
    set(HOST_ARCHITECTURE_2 "aarch64")
endif()
endif()

if (APPLE)
if(${CMAKE_HOST_ARCH} MATCHES "^(x86_64|X64)$")
     set(HOST_ARCHITECTURE "x86_64")
     set(HOST_ARCHITECTURE_2 "X64")
elseif(${CMAKE_HOST_ARCH} MATCHES "^(i386|i686|X32)$")
     set(HOST_ARCHITECTURE "x86_32")
     set(HOST_ARCHITECTURE_2 "i386")
elseif(${CMAKE_HOST_ARCH} MATCHES "^(aarch64|arm64|aarch64_be|armv8b|armv8l)$")
    set(HOST_ARCHITECTURE "aarch_64")
    set(HOST_ARCHITECTURE_2 "aarch64")
endif()

    set(CMAKE_MACOSX_RPATH 1)
    set(HOST_OS "osx")
    set(HOST_OS_2 "macos")
    set(MYSQL_PLATFORM macos10.14)
endif ()

MESSAGE("Building for ${HOST_OS} ${HOST_ARCHITECTURE}")