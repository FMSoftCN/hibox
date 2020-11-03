INCLUDE(CheckLibraryExists)
INCLUDE(CheckFunctionExists)

ADD_DEFINITIONS(-Wall -Werror)
IF(CMAKE_C_COMPILER_VERSION VERSION_GREATER 6)
	ADD_DEFINITIONS(-Wextra -Werror=implicit-function-declaration)
	ADD_DEFINITIONS(-Wformat -Werror=format-security)
ENDIF()
ADD_DEFINITIONS(-Os -std=gnu99 -g3 -Wmissing-declarations -Wno-unused-parameter)

INCLUDE(FindPkgConfig)

SET(SOURCES gslist.c avl.c avl-cmp.c blob.c blobmsg.c vlist.c kvlist.c utils.c safe_list.c runqueue.c
        md5.c base64.c sha1.c
        uloop.c usock.c ustream.c ustream-fd.c ulog.c
        json-c/arraylist.c json-c/json_c_version.c json-c/json_object_iterator.c json-c/json_tokener.c
        json-c/json_visit.c json-c/printbuf.c json-c/strerror_override.c json-c/debug.c json-c/json_object.c
        json-c/json_pointer.c json-c/json_util.c json-c/linkhash.c json-c/random_seed.c
        blobmsg_json.c json_script.c)

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
	DESTINATION include/hibox
)

FILE(GLOB jsonc_headers
    json-c/json_config.h json-c/debug.h json-c/json_c_version.h json-c/json_inttypes.h json-c/json_types.h
    json-c/linkhash.h json-c/printbuf.h json-c/arraylist.h json-c/json_object.h
    json-c/json_object_iterator.h json-c/json_pointer.h json-c/json_tokener.h json-c/json_util.h)
INSTALL(FILES ${jsonc_headers}
	DESTINATION include/hibox/json-c)

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
