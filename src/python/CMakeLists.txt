# Python bindings with nanobind
nanobind_add_module(_libsqlglot bindings.cpp)

# Link against the header-only library
target_link_libraries(_libsqlglot PRIVATE libsqlglot)

# Static link libstdc++ and libgcc for portability (wheel distribution)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_options(_libsqlglot PRIVATE -static-libstdc++ -static-libgcc)
endif()

# Set output directory
set_target_properties(_libsqlglot PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/libsqlglot"
)

# Install the extension module
install(TARGETS _libsqlglot
    LIBRARY DESTINATION libsqlglot
)
