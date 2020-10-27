INCLUDE(CheckLibraryExists)
INCLUDE(CheckFunctionExists)

ADD_DEFINITIONS(-Wall -Werror)
IF(CMAKE_C_COMPILER_VERSION VERSION_GREATER 6)
	ADD_DEFINITIONS(-Wextra -Werror=implicit-function-declaration)
	ADD_DEFINITIONS(-Wformat -Werror=format-security -Werror=format-nonliteral)
ENDIF()
ADD_DEFINITIONS(-Os -std=gnu99 -g3 -Wmissing-declarations -Wno-unused-parameter)

INCLUDE(FindPkgConfig)

SET(SOURCES avl.c avl-cmp.c blob.c blobmsg.c vlist.c kvlist.c utils.c safe_list.c runqueue.c
        md5.c base64.c
        uloop.c usock.c ustream.c ustream-fd.c ulog.c
        cjson.c blobmsg_json.c json_script.c)

ADD_LIBRARY(hibox SHARED ${SOURCES})
ADD_LIBRARY(hibox-static STATIC ${SOURCES})
SET_TARGET_PROPERTIES(hibox-static PROPERTIES OUTPUT_NAME hibox)

SET(LIBS)
CHECK_FUNCTION_EXISTS(clock_gettime HAVE_GETTIME)
IF(NOT HAVE_GETTIME)
	CHECK_LIBRARY_EXISTS(rt clock_gettime "" NEED_GETTIME)
	IF(NEED_GETTIME)
		TARGET_LINK_LIBRARIES(hibox rt)
	ENDIF()
ENDIF()

FILE(GLOB headers *.h)
INSTALL(FILES ${headers}
	DESTINATION include/libhibox
)
INSTALL(TARGETS hibox hibox-static
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
)

ADD_SUBDIRECTORY(lua)
ADD_SUBDIRECTORY(examples)

MACRO(ADD_UNIT_TEST_SAN name)
  ADD_EXECUTABLE(${name}-san ${name}.c)
  TARGET_COMPILE_OPTIONS(${name}-san PRIVATE -g -fno-omit-frame-pointer -fsanitize=undefined,address,leak -fno-sanitize-recover=all)
  TARGET_LINK_OPTIONS(${name}-san PRIVATE -fsanitize=undefined,address,leak)
  TARGET_LINK_LIBRARIES(${name}-san hibox)
  TARGET_INCLUDE_DIRECTORIES(${name}-san PRIVATE ${PROJECT_SOURCE_DIR})
ENDMACRO(ADD_UNIT_TEST_SAN)

IF(UNIT_TESTING)
  ENABLE_TESTING()
  ADD_SUBDIRECTORY(tests)
ENDIF()

IF(ABIVERSION)
	SET_TARGET_PROPERTIES(hibox PROPERTIES VERSION ${ABIVERSION})
ENDIF()
