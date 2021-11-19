if (NOT TARGET HiBox::HiBox)
    if (NOT INTERNAL_BUILD)
        message(FATAL_ERROR "HiBox::HiBox target not found")
    endif ()

    # This should be moved to an if block if the Apple Mac/iOS build moves completely to CMake
    # Just assuming Windows for the moment
    add_library(HiBox::HiBox STATIC IMPORTED)
    set_target_properties(HiBox::HiBox PROPERTIES
        IMPORTED_LOCATION ${WEBKIT_LIBRARIES_LINK_DIR}/HiBox${DEBUG_SUFFIX}.lib
    )
    set(HiBox_PRIVATE_FRAMEWORK_HEADERS_DIR "${CMAKE_BINARY_DIR}/../include/private")
    target_include_directories(HiBox::HiBox INTERFACE
        ${HiBox_PRIVATE_FRAMEWORK_HEADERS_DIR}
    )
endif ()
