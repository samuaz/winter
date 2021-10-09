#
# Created by AZCONA VARGAS, SAMUEL EDUARDO
#

option(ALPINE_BUILD "Use ALPINE_BUILD" FALSE)
option(HOST_OS "HOST_OS")

############################
##         FLAGS          ##
############################
if (ALPINE_BUILD)
    message("ALPINE FLAGS")
    set(EXTRA_LIBRARY "-pthread -lstdc++ -lrt -lssl -lcrypto")
else ()
    if (LINUX)
        message("LINUX FLAGS")
        set(EXTRA_LIBRARY "-pthread -lstdc++ -lrt -lz -ldl")
    endif ()
    if (APPLE)
        message("MAC FLAGS")
        set(EXTRA_LIBRARY "-pthread -lstdc++ -pthread")
    endif ()
endif ()


##grpc fails to build generated_message_util.h:224:14: error: zero size arrays are an extension [-Werror,-Wzero-length-array]
## so workarround disable -pedantic-errors
#set(CMAKE_CXX_FLAGS_DEBUG "-O3 -g -pedantic-errors -Wall -Wextra ")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_C_FLAGS_DEBUG "-DEBUG -O0 -g -ggdb -Wall -Wextra -fsanitize=address -fdiagnostics-color=auto -ftemplate-backtrace-limit=0 -fpie -fPIE")
set(CMAKE_CXX_FLAGS_DEBUG "-DEBUG -O0 -g -ggdb -Wall -Wextra -fsanitize=address -fdiagnostics-color=auto -ftemplate-backtrace-limit=0 -fpie -fPIE")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -march=native -pipe -fno-unroll-loops -fmerge-all-constants -fno-ident -ffunction-sections -fdata-sections -Bsymbolic-functions -fpie -fPIE -s")
set(CMAKE_C_FLAGS_RELEASE "-Ofast -march=native -pipe -fno-unroll-loops -fmerge-all-constants -fno-ident -ffunction-sections -fdata-sections -Bsymbolic-functions -fpie -fPIE -s")
link_libraries(${WINTER_LIBS} wintercpp ${EXTRA_LIBRARY})
############################
##       END FLAGS        ##
############################
