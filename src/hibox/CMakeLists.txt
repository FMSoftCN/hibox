set_property(DIRECTORY . PROPERTY FOLDER "HiBox")

include(GlobalCommon)
include(MyMacros.cmake)

configure_file(hibox_version.h.in ${HiBox_DERIVED_SOURCES_DIR}/hibox_version.h @ONLY)
configure_file(hibox_features.h.in ${HiBox_DERIVED_SOURCES_DIR}/hibox_features.h @ONLY)
configure_file(hibox.pc.in ${HiBox_PKGCONFIG_FILE} @ONLY)

set(HiBox_PRIVATE_INCLUDE_DIRECTORIES
    "${CMAKE_BINARY_DIR}"
    "${HIBOX_DIR}"
    "${HIBOX_DIR}/include"
    "${HIBOX_DIR}/include/private"
    "${HiBox_DERIVED_SOURCES_DIR}"
    "${FORWARDING_HEADERS_DIR}"
)

# TODO: List the headers should be installed to system `hibox/` here.
set(HiBox_INSTALLED_HEADERS
    "${HiBox_DERIVED_SOURCES_DIR}/hibox_version.h"
    "${HiBox_DERIVED_SOURCES_DIR}/hibox_features.h"
    "${HIBOX_DIR}/include/arraylist.h"
    "${HIBOX_DIR}/include/list.h"
    "${HIBOX_DIR}/include/kvlist.h"
    "${HIBOX_DIR}/include/avl-cmp.h"
    "${HIBOX_DIR}/include/avl.h"
    "${HIBOX_DIR}/include/gslist.h"
    "${HIBOX_DIR}/include/safe_list.h"
    "${HIBOX_DIR}/include/sorted-array.h"
    "${HIBOX_DIR}/include/vlist.h"
    "${HIBOX_DIR}/include/hmac.h"
    "${HIBOX_DIR}/include/md5.h"
    "${HIBOX_DIR}/include/sha1.h"
    "${HIBOX_DIR}/include/sha256.h"
    "${HIBOX_DIR}/include/sha512.h"
    "${HIBOX_DIR}/include/utils.h"
    "${HIBOX_DIR}/include/json.h"
    "${HIBOX_DIR}/include/blob.h"
    "${HIBOX_DIR}/include/blobmsg.h"
    "${HIBOX_DIR}/include/blobmsg_json.h"
    "${HIBOX_DIR}/include/json_script.h"
    "${HIBOX_DIR}/include/runqueue.h"
    "${HIBOX_DIR}/include/ulog.h"
    "${HIBOX_DIR}/include/uloop.h"
    "${HIBOX_DIR}/include/usock.h"
    "${HIBOX_DIR}/include/ustream.h"
)

# TODO: List the headers should be installed to system `hibox/` here.
set(HiBox_JSONC_INSTALLED_HEADERS
    "${HIBOX_DIR}/include/json-c/json_c_version.h"
    "${HIBOX_DIR}/include/json-c/json_object.h"
    "${HIBOX_DIR}/include/json-c/json_object_iterator.h"
    "${HIBOX_DIR}/include/json-c/json_pointer.h"
    "${HIBOX_DIR}/include/json-c/json_tokener.h"
    "${HIBOX_DIR}/include/json-c/json_types.h"
    "${HIBOX_DIR}/include/json-c/json_util.h"
    "${HIBOX_DIR}/include/json-c/linkhash.h"
)

# TODO: List the directorires which do not contain any platform-dependent C source files
set(HiBox_PLATFORM_INDEPENDENT_DIRS
    "algorithm"
    "blob"
    "datastructure"
    "infrastructure"
    "json-c"
    "misc"
)

# This macro will append all C/CXX source files in ${HiBox_PLATFORM_INDEPENDENT_DIRS}
# to ${HiBox_SOURCES}
APPEND_ALL_SOURCE_FILES_IN_DIRLIST(HiBox_SOURCES "${HiBox_PLATFORM_INDEPENDENT_DIRS}")

# TODO: List the source files individually.
list(APPEND HiBox_SOURCES
)

# Put the CXX source files which can be unified in `Sources.txt`
list(APPEND HiBox_UNIFIED_SOURCE_LIST_FILES
    "Sources.txt"
)

set(HiBox_LIBRARIES)

set(HiBox_INTERFACE_LIBRARIES HiBox)
set(HiBox_INTERFACE_INCLUDE_DIRECTORIES ${HiBox_PRIVATE_FRAMEWORK_HEADERS_DIR})

HIBOX_FRAMEWORK_DECLARE(HiBox)
HIBOX_INCLUDE_CONFIG_FILES_IF_EXISTS()

HIBOX_WRAP_SOURCELIST(${HiBox_SOURCES})

HIBOX_COPY_FILES(HiBox_CopyPrivateHeaders
    DESTINATION ${HiBox_PRIVATE_FRAMEWORK_HEADERS_DIR}/hibox
    FILES ${HiBox_PRIVATE_FRAMEWORK_HEADERS}
    FLATTENED
)
list(APPEND HiBox_INTERFACE_DEPENDENCIES HiBox_CopyPrivateHeaders)
# HiBox_CopyPrivateHeaders needs to have a direct or indirect
# dependency of HiBox target for CMake Visual Studio generator to
# eliminate duplicated custom commands. Otherwise, CSSPropertyNames.h
# will be generated in both projects.
if (NOT INTERNAL_BUILD)
    add_dependencies(HiBox_CopyPrivateHeaders HiBox)
endif ()

HIBOX_COMPUTE_SOURCES(HiBox)
HIBOX_FRAMEWORK(HiBox)
HIBOX_FRAMEWORK_TARGET(HiBox)

# The -ftree-sra optimization (implicit with -O2) causes crashes when
# allocating large chunks of memory using bmalloc on Intel 32bit.
# See https://bugs.webkit.org/show_bug.cgi?id=146440
string(TOLOWER ${CMAKE_HOST_SYSTEM_PROCESSOR} LOWERCASE_CMAKE_HOST_SYSTEM_PROCESSOR)
if (CMAKE_COMPILER_IS_GNUCXX AND "${LOWERCASE_CMAKE_HOST_SYSTEM_PROCESSOR}" MATCHES "(i[3-6]86|x86)$")
    HIBOX_ADD_TARGET_CXX_FLAGS(HiBox -fno-tree-sra)
endif ()

if (${HiBox_LIBRARY_TYPE} MATCHES "SHARED")
    set_target_properties(HiBox PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})
    install(TARGETS HiBox DESTINATION "${LIB_INSTALL_DIR}")
endif ()

if (MSVC)
    set_target_properties(HiBox PROPERTIES
        COMPILE_PDB_NAME ${HiBox_OUTPUT_NAME}
    )
endif ()

# add_subdirectory(res)

install(TARGETS HiBox
        DESTINATION "${LIB_INSTALL_DIR}/"
)

install(FILES ${HiBox_INSTALLED_HEADERS}
        DESTINATION "${HEADER_INSTALL_DIR}/hibox"
)

install(FILES ${HiBox_JSONC_INSTALLED_HEADERS}
        DESTINATION "${HEADER_INSTALL_DIR}/hibox/json-c"
)

install(FILES "${HiBox_PKGCONFIG_FILE}"
        DESTINATION "${LIB_INSTALL_DIR}/pkgconfig"
)

