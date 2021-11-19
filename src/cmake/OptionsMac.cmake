include(GNUInstallDirs)

# FIXME: These should line up with versions in Version.xcconfig
set(HIBOX_MAC_VERSION 1.0.0)
set(MACOSX_FRAMEWORK_BUNDLE_VERSION 1.0.0)

# These are shared variables, but we special case their definition so that we can use the
# CMAKE_INSTALL_* variables that are populated by the GNUInstallDirs macro.
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_FULL_LIBDIR}" CACHE PATH "Absolute path to library installation directory")
set(EXEC_INSTALL_DIR "${CMAKE_INSTALL_FULL_BINDIR}" CACHE PATH "Absolute path to executable installation directory")
set(LIBEXEC_INSTALL_DIR "${CMAKE_INSTALL_FULL_LIBEXECDIR}/hibox" CACHE PATH "Absolute path to install executables executed by the library")
set(HEADER_INSTALL_DIR "${CMAKE_INSTALL_FULL_INCLUDEDIR}" CACHE PATH "Absolute path to header installation directory")
set(HIBOX_HEADER_INSTALL_DIR "${CMAKE_INSTALL_FULL_INCLUDEDIR}/hibox" CACHE PATH "Absolute path to HiBox header installation directory")

add_definitions(-DBUILDING_MAC__=1)
add_definitions(-DHIBOX_API_VERSION_STRING="${HIBOX_API_VERSION}")

HIBOX_OPTION_BEGIN()

# Private options shared with other HiBox ports. Add options here only if
# we need a value different from the default defined in GlobalFeatures.cmake.

# HIBOX_OPTION_DEFAULT_PORT_VALUE(ENABLE_XXX PUBLIC OFF)

HIBOX_OPTION_END()

set(HiBox_PKGCONFIG_FILE ${CMAKE_BINARY_DIR}/src/hibox/hibox.pc)

set(HiBox_LIBRARY_TYPE SHARED)
set(HiBoxTestSupport_LIBRARY_TYPE SHARED)

