# Per-File Optimization Level Configuration
# ===========================================
# Different parts of the codebase benefit from different optimization strategies:
# - Hot paths (parser, tokenizer): -O3 with aggressive inlining
# - Code size sensitive (bindings): -Os to reduce binary bloat
# - Debug/error paths: -O2 to balance size and speed
# - Template-heavy code: -O2 to reduce compile time without sacrificing runtime

# Performance-critical hot paths - Maximum optimization (-O3)
# These are called millions of times in typical workloads
set(HOTPATH_FILES
    # Empty for now - will be populated after profiling
)

# Code size sensitive - Optimize for size (-Os)
# These contribute significantly to binary size but aren't performance critical
set(SIZE_OPTIMIZED_FILES
    # Python bindings - large due to nanobind templates
    src/python/bindings.cpp
    src/python/expr_type_bindings_generated.h
)

# Template-heavy code - Moderate optimization (-O2)
# Heavy template instantiation causes long compile times with -O3
set(TEMPLATE_HEAVY_FILES
    # Will be identified during profiling
)

# Error handling - Optimize for size (-Os)
# Error paths are cold, prioritize binary size
set(ERROR_PATH_FILES
    # Will be identified during profiling
)

function(apply_per_file_optimizations target)
    # Hot path files - Maximum performance
    foreach(file ${HOTPATH_FILES})
        set_source_files_properties(${file} PROPERTIES
            COMPILE_FLAGS "-O3 -finline-limit=2000 -ffast-math"
        )
    endforeach()

    # Size-optimized files
    foreach(file ${SIZE_OPTIMIZED_FILES})
        set_source_files_properties(${file} PROPERTIES
            COMPILE_FLAGS "-Os -ffunction-sections -fdata-sections"
        )
    endforeach()

    # Template-heavy files
    foreach(file ${TEMPLATE_HEAVY_FILES})
        set_source_files_properties(${file} PROPERTIES
            COMPILE_FLAGS "-O2"
        )
    endforeach()

    # Error path files
    foreach(file ${ERROR_PATH_FILES})
        set_source_files_properties(${file} PROPERTIES
            COMPILE_FLAGS "-Os"
        )
    endforeach()
endfunction()

# Profile-Guided Optimization (PGO) Support
# ==========================================
# Three-phase process:
# 1. Build with -fprofile-generate, run training workload
# 2. Analyze profile data
# 3. Build with -fprofile-use for optimized binary

if(LIBSQLGLOT_PGO_GENERATE)
    message(STATUS "PGO Phase 1/3: Building with profiling instrumentation")
    add_compile_options(-fprofile-generate=${CMAKE_BINARY_DIR}/pgo-data)
    add_link_options(-fprofile-generate=${CMAKE_BINARY_DIR}/pgo-data)

    # Create directory for profile data
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/pgo-data)

    message(STATUS "After building, run training workload then rebuild with LIBSQLGLOT_PGO_USE=ON")
endif()

if(LIBSQLGLOT_PGO_USE)
    message(STATUS "PGO Phase 3/3: Building with profile-guided optimizations")

    # Check if profile data exists
    if(NOT EXISTS ${CMAKE_BINARY_DIR}/pgo-data)
        message(FATAL_ERROR "PGO profile data not found at ${CMAKE_BINARY_DIR}/pgo-data")
    endif()

    add_compile_options(
        -fprofile-use=${CMAKE_BINARY_DIR}/pgo-data
        -fprofile-correction  # Handle inconsistencies
        -Wno-missing-profile  # Don't warn about missing profiles
    )
    add_link_options(-fprofile-use=${CMAKE_BINARY_DIR}/pgo-data)

    message(STATUS "Using profile data from: ${CMAKE_BINARY_DIR}/pgo-data")
endif()

# Optimization Analysis Helper
# =============================
# Generate optimization report showing which optimizations were applied

function(generate_optimization_report)
    set(report_file ${CMAKE_BINARY_DIR}/optimization_report.txt)

    file(WRITE ${report_file} "libsqlglot Optimization Report\n")
    file(APPEND ${report_file} "================================\n\n")
    file(APPEND ${report_file} "Build Type: ${CMAKE_BUILD_TYPE}\n")
    file(APPEND ${report_file} "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}\n\n")

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        file(APPEND ${report_file} "Base Optimization: -O3\n")
        file(APPEND ${report_file} "LTO: ${CMAKE_INTERPROCEDURAL_OPTIMIZATION}\n")

        if(LIBSQLGLOT_ENABLE_NATIVE)
            file(APPEND ${report_file} "Native optimizations: -march=native -mtune=native\n")
        else()
            file(APPEND ${report_file} "Portable optimizations: -march=x86-64 -mtune=generic\n")
        endif()

        if(LIBSQLGLOT_PGO_GENERATE)
            file(APPEND ${report_file} "PGO: Generating profile data\n")
        elseif(LIBSQLGLOT_PGO_USE)
            file(APPEND ${report_file} "PGO: Using profile data\n")
        else()
            file(APPEND ${report_file} "PGO: Not enabled\n")
        endif()
    endif()

    file(APPEND ${report_file} "\nPer-File Optimization Levels:\n")
    file(APPEND ${report_file} "-----------------------------\n")

    file(APPEND ${report_file} "\nHot Paths (-O3):\n")
    foreach(file ${HOTPATH_FILES})
        file(APPEND ${report_file} "  ${file}\n")
    endforeach()

    file(APPEND ${report_file} "\nSize-Optimized (-Os):\n")
    foreach(file ${SIZE_OPTIMIZED_FILES})
        file(APPEND ${report_file} "  ${file}\n")
    endforeach()

    file(APPEND ${report_file} "\nTemplate-Heavy (-O2):\n")
    foreach(file ${TEMPLATE_HEAVY_FILES})
        file(APPEND ${report_file} "  ${file}\n")
    endforeach()

    message(STATUS "Optimization report written to: ${report_file}")
endfunction()
