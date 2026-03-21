cmake_minimum_required(VERSION 3.21)
project(libsqlglot VERSION 0.2.0 LANGUAGES CXX)

# Require C++26 for reflection and advanced constexpr features
# Note: CMake 3.28 doesn't recognize CMAKE_CXX_STANDARD=26, so we use manual flags
# DO NOT set CMAKE_CXX_STANDARD here - it will cause "CXX26 dialect unknown" errors

# Manually add C++26 flag (CMake 3.28 doesn't have cxx_std_26 support yet)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-std=c++2b -freflection)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-std=c++26 -freflection)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/std:c++26)
endif()

# Require C++26 for reflection support - NO FALLBACK
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "14.0")
        message(FATAL_ERROR "GCC 14.0+ required for C++26 reflection (found ${CMAKE_CXX_COMPILER_VERSION}). Please upgrade compiler.")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "18.0")
        message(FATAL_ERROR "Clang 18.0+ required for C++26 reflection (found ${CMAKE_CXX_COMPILER_VERSION}). Please upgrade compiler.")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "19.40")
        message(FATAL_ERROR "MSVC 19.40+ required for C++26 reflection (found ${CMAKE_CXX_COMPILER_VERSION}). Please upgrade compiler.")
    endif()
else()
    message(FATAL_ERROR "Unknown compiler ${CMAKE_CXX_COMPILER_ID}. Supported: GCC 14+, Clang 18+, MSVC 19.40+")
endif()

message(STATUS "C++26 reflection enabled - keywords auto-generated from TokenType enum")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

# Options
option(LIBSQLGLOT_BUILD_TESTS "Build tests" ON)
option(LIBSQLGLOT_BUILD_BENCHMARKS "Build benchmarks" OFF)
option(LIBSQLGLOT_BUILD_PYTHON "Build Python bindings" OFF)
option(LIBSQLGLOT_BUILD_SHARED "Build shared library" ON)
option(LIBSQLGLOT_ENABLE_SIMD "Enable SIMD optimisations" ON)
option(LIBSQLGLOT_ENABLE_NATIVE "Enable native CPU optimizations (-march=native)" OFF)
option(LIBSQLGLOT_FUZZ "Build fuzz targets" OFF)
option(LIBSQLGLOT_PGO_GENERATE "Generate PGO profile data" OFF)
option(LIBSQLGLOT_PGO_USE "Use PGO profile data for optimization" OFF)

# Compiler flags for our code (not dependencies)
set(LIBSQLGLOT_CXX_FLAGS -Wall -Wextra -Wpedantic -Werror -fno-rtti)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Portable optimization flags (no -march=native for wheels)
    # Use LIBSQLGLOT_ENABLE_NATIVE for local builds with machine-specific optimizations
    if(LIBSQLGLOT_ENABLE_NATIVE)
        list(APPEND LIBSQLGLOT_CXX_FLAGS -O3 -march=native -mtune=native -flto -fmerge-all-constants -fvisibility=hidden)
        message(STATUS "Native optimizations enabled (-march=native -mtune=native)")
    else()
        # Portable: x86-64 baseline without AVX/AVX2/AVX512
        list(APPEND LIBSQLGLOT_CXX_FLAGS -O3 -march=x86-64 -mtune=generic -flto -fmerge-all-constants -fvisibility=hidden)
        message(STATUS "Portable optimizations enabled (-march=x86-64 -mtune=generic)")
    endif()
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)  # Enable LTO

    # Profile-Guided Optimization (PGO)
    if(LIBSQLGLOT_PGO_GENERATE)
        list(APPEND LIBSQLGLOT_CXX_FLAGS -fprofile-generate)
        message(STATUS "PGO: Generating profile data (step 1/3)")
    elseif(LIBSQLGLOT_PGO_USE)
        list(APPEND LIBSQLGLOT_CXX_FLAGS -fprofile-use -fprofile-correction)
        message(STATUS "PGO: Using profile data for optimization (step 3/3)")
    endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    list(APPEND LIBSQLGLOT_CXX_FLAGS -O0 -g)
endif()

# Generate merged dialect grammars from patches
find_package(Python3 COMPONENTS Interpreter REQUIRED)

# Find all dialect patches
file(GLOB DIALECT_PATCHES "${CMAKE_SOURCE_DIR}/dialects/patches/*.json")

# Map patch names to base grammars
set(PATCH_BASE_MAP
    "redshift:postgresql"
    "duckdb:postgresql"
    "cockroachdb:postgresql"
    "materialize:postgresql"
    "vertica:postgresql"
    "greenplum:postgresql"
    "risingwave:postgresql"
    "timescaledb:postgresql"
    "yugabytedb:postgresql"
    "dune:postgresql"
    "bigquery:postgresql"
    "spark:hive"
    "databricks:hive"
    "impala:hive"
    "spark2:hive"
    "singlestore:mysql"
    "doris:mysql"
    "tidb:mysql"
    "presto:trino"
    "dremio:trino"
    "oracle:plsql"
    "fabric:tsql"
    "druid:mysql"
    "db2:derby"
    "netezza:postgresql"
    "tableau:postgresql"
    "exasol:postgresql"
    "solr:derby"
    "calcite:derby"
)

set(MERGED_GRAMMARS "")
foreach(PATCH_FILE ${DIALECT_PATCHES})
    get_filename_component(PATCH_NAME ${PATCH_FILE} NAME_WE)

    # Find base grammar for this patch
    set(BASE_GRAMMAR "")
    foreach(MAPPING ${PATCH_BASE_MAP})
        string(REGEX MATCH "^${PATCH_NAME}:(.+)$" MATCHED "${MAPPING}")
        if(MATCHED)
            set(BASE_GRAMMAR "${CMAKE_MATCH_1}")
            break()
        endif()
    endforeach()

    if(BASE_GRAMMAR)
        set(BASE_GRAMMAR_FILE "${CMAKE_SOURCE_DIR}/generated/grammar_data/${BASE_GRAMMAR}_grammar_data.json")
        set(OUTPUT_FILE "${CMAKE_BINARY_DIR}/generated/grammar_data/${PATCH_NAME}_grammar_data.json")

        # Create output directory
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/generated/grammar_data")

        # Add custom command to merge grammar
        add_custom_command(
            OUTPUT ${OUTPUT_FILE}
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/merge_grammar.py
                    ${BASE_GRAMMAR_FILE} ${PATCH_FILE} ${OUTPUT_FILE}
            DEPENDS ${BASE_GRAMMAR_FILE} ${PATCH_FILE} ${CMAKE_SOURCE_DIR}/scripts/merge_grammar.py
            COMMENT "Merging ${PATCH_NAME} dialect grammar (base: ${BASE_GRAMMAR})"
            VERBATIM
        )

        list(APPEND MERGED_GRAMMARS ${OUTPUT_FILE})
    else()
        message(WARNING "No base grammar mapping found for patch: ${PATCH_NAME}")
    endif()
endforeach()

# Create custom target for all merged grammars
add_custom_target(merge_dialects ALL DEPENDS ${MERGED_GRAMMARS})

# Header-only interface target
add_library(libsqlglot INTERFACE)
target_include_directories(libsqlglot INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
# Note: CMake 3.28 doesn't support cxx_std_26, using manual flag above
# target_compile_features(libsqlglot INTERFACE cxx_std_26)
add_dependencies(libsqlglot merge_dialects)

# Optional compiled shared library
if(LIBSQLGLOT_BUILD_SHARED)
    add_library(libsqlglot_shared SHARED src/libsqlglot.cpp)
    target_link_libraries(libsqlglot_shared PUBLIC libsqlglot)
    target_compile_options(libsqlglot_shared PRIVATE ${LIBSQLGLOT_CXX_FLAGS})
    set_target_properties(libsqlglot_shared PROPERTIES
        OUTPUT_NAME sqlglot
        VERSION ${PROJECT_VERSION}
        SOVERSION 0
    )
endif()

# FetchContent for downloading dependencies
include(FetchContent)

# Tests (Catch2)
if(LIBSQLGLOT_BUILD_TESTS)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
    )
    FetchContent_MakeAvailable(Catch2)
    enable_testing()
    add_subdirectory(tests)
endif()

# Benchmarks (Google Benchmark)
if(LIBSQLGLOT_BUILD_BENCHMARKS)
    FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.8.3
    )
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark tests" FORCE)
    FetchContent_MakeAvailable(benchmark)
    add_subdirectory(benchmarks)
endif()

# Python bindings (nanobind)
if(LIBSQLGLOT_BUILD_PYTHON)
    find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)
    FetchContent_Declare(
        nanobind
        GIT_REPOSITORY https://github.com/wjakob/nanobind.git
        GIT_TAG v2.2.0
    )
    FetchContent_MakeAvailable(nanobind)
    add_subdirectory(src/python)
endif()

# Fuzz targets
if(LIBSQLGLOT_FUZZ)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message(FATAL_ERROR "Fuzzing requires Clang compiler")
    endif()
    add_subdirectory(tests/fuzz)
endif()

# Installation
include(GNUInstallDirs)
install(TARGETS libsqlglot
    EXPORT libsqlglotTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY include/libsqlglot
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

if(LIBSQLGLOT_BUILD_SHARED)
    install(TARGETS libsqlglot_shared
        EXPORT libsqlglotTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()
