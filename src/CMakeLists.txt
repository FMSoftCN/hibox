# -----------------------------------------------------------------------------
# Add components directories
# -----------------------------------------------------------------------------
add_subdirectory(wtf)

add_subdirectory(hibox)

if (ENABLE_API_TESTS)
    add_subdirectory(tests)
endif ()

add_subdirectory(examples)

HIBOX_INCLUDE_CONFIG_FILES_IF_EXISTS()
