#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

###############################
## CONFIG BUILD SYSTEM HOST ##
###############################
if (UNIX AND NOT APPLE)
    set(HOST_OS "linux")
    set(HOST_OS_2 "linux")
    set(MYSQL_PLATFORM linux-glibc2.12)
endif ()

if (APPLE)
    set(CMAKE_MACOSX_RPATH 1)
    set(HOST_OS "osx")
    set(HOST_OS_2 "macos")
    set(MYSQL_PLATFORM macos10.14)
endif ()
