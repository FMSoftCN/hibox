# FIXME: These should line up with versions in Version.xcconfig
set(HIBOX_MAC_VERSION 1.0.0)
set(MACOSX_FRAMEWORK_BUNDLE_VERSION 1.0.0)

HIBOX_OPTION_BEGIN()
# Private options shared with other HiBox ports. Add options here only if
# we need a value different from the default defined in GlobalFeatures.cmake.

# HIBOX_OPTION_DEFAULT_PORT_VALUE(ENABLE_XXX PUBLIC OFF)

HIBOX_OPTION_END()

set(HiBox_PKGCONFIG_FILE ${CMAKE_BINARY_DIR}/src/hibox/hibox.pc)

set(HiBox_LIBRARY_TYPE SHARED)
set(HiBoxTestSupport_LIBRARY_TYPE SHARED)

