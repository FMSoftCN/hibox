include(GNUInstallDirs)

CALCULATE_LIBRARY_VERSIONS_FROM_LIBTOOL_TRIPLE(HIBOX 1 0 0)

# These are shared variables, but we special case their definition so that we can use the
# CMAKE_INSTALL_* variables that are populated by the GNUInstallDirs macro.
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_FULL_LIBDIR}" CACHE PATH "Absolute path to library installation directory")
set(EXEC_INSTALL_DIR "${CMAKE_INSTALL_FULL_BINDIR}" CACHE PATH "Absolute path to executable installation directory")
set(LIBEXEC_INSTALL_DIR "${CMAKE_INSTALL_FULL_LIBEXECDIR}/hibox" CACHE PATH "Absolute path to install executables executed by the library")
set(HEADER_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}" CACHE PATH "Absolute path to header installation directory")
set(HIBOX_HEADER_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/hibox" CACHE PATH "Absolute path to HiBox header installation directory")

add_definitions(-DBUILDING_LINUX__=1)
add_definitions(-DHIBOX_API_VERSION_STRING="${HIBOX_API_VERSION}")

HIBOX_OPTION_BEGIN()

# Public options specific to the HybridOS port. Do not add any options here unless
# there is a strong reason we should support changing the value of the option,
# and the option is not relevant to any other HiBox ports.
#HIBOX_OPTION_DEFINE(USE_SYSTEMD "Whether to enable journald logging" PUBLIC ON)

# Private options specific to the HybridOS port. Changing these options is
# completely unsupported. They are intended for use only by HiBox developers.
#HIBOX_OPTION_DEFINE(USE_ANGLE_WEBGL "Whether to use ANGLE as WebGL backend." PRIVATE OFF)
#HIBOX_OPTION_DEPEND(ENABLE_WEBGL ENABLE_GRAPHICS_CONTEXT_GL)

#HIBOX_OPTION_DEFAULT_PORT_VALUE(ENABLE_XXX PUBLIC ${ENABLE_XXX_DEFAULT})

# Finalize the value for all options. Do not attempt to use an option before
# this point, and do not attempt to change any option after this point.
HIBOX_OPTION_END()

set(HiBox_PKGCONFIG_FILE ${CMAKE_BINARY_DIR}/src/hibox/hibox.pc)

# CMake does not automatically add --whole-archive when building shared objects from
# a list of convenience libraries. This can lead to missing symbols in the final output.
# We add --whole-archive to all libraries manually to prevent the linker from trimming
# symbols that we actually need later. With ld64 on darwin, we use -all_load instead.
macro(ADD_WHOLE_ARCHIVE_TO_LIBRARIES _list_name)
    if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
        list(APPEND ${_list_name} -Wl,-all_load)
    else ()
        set(_tmp)
        foreach (item IN LISTS ${_list_name})
            if ("${item}" STREQUAL "PRIVATE" OR "${item}" STREQUAL "PUBLIC")
                list(APPEND _tmp "${item}")
            else ()
                list(APPEND _tmp -Wl,--whole-archive "${item}" -Wl,--no-whole-archive)
            endif ()
        endforeach ()
        set(${_list_name} ${_tmp})
    endif ()
endmacro()

#include(BubblewrapSandboxChecks)
