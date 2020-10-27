CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(hibox-1.0 C)

OPTION(BUILD_LUA "build Lua plugin" OFF)
OPTION(BUILD_EXAMPLES "build examples" ON)

if (UNIX OR MINGW OR CYGWIN)
    list(APPEND CMAKE_REQUIRED_DEFINITIONS -D_GNU_SOURCE)
endif()

if (UNIX)
    list(APPEND CMAKE_REQUIRED_LIBRARIES   m)
endif()

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
	if ("${DISABLE_WERROR}" STREQUAL "OFF")
	    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -Werror")
	endif()
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -Wall")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -Wno-error=deprecated-declarations")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -Wextra")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -Wwrite-strings")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -Wno-unused-parameter")
    if (NOT WIN32)
        set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} -Wstrict-prototypes")
    endif()

    add_definitions(-D_GNU_SOURCE)
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} /DEBUG")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} /wd4100")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} /wd4996")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} /wd4244")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} /wd4706")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} /wd4702")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} /wd4127")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} /wd4701")
endif()

ADD_SUBDIRECTORY(src)

# Packing stuff
SET(CPACK_PACKAGE_VENDOR "FMSoft")
SET(CPACK_PACKAGE_NAME ${PROJECT_NAME})
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The C utilities library for HybridOS")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}")
SET(CPACK_SOURCE_GENERATOR "TGZ")
SET(CPACK_SOURCE_IGNORE_FILES
      "/auto/;/cmake/;/.svn/;/.git/;/.bzr/;/CMakeFiles/;/_CPack_Packages/;CMakeCache.txt$;
      ~$;.swp$;.cmake$;
      ${CPACK_SOURCE_IGNORE_FILES}")

INCLUDE(CPack)
