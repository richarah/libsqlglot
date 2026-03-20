cmake_minimum_required(VERSION 3.21)
project(libsqlglot VERSION 0.1.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(LIBSQLGLOT_BUILD_TESTS "Build tests" ON)
option(LIBSQLGLOT_BUILD_BENCHMARKS "Build benchmarks" OFF)
option(LIBSQLGLOT_BUILD_PYTHON "Build Python bindings" OFF)
option(LIBSQLGLOT_BUILD_SHARED "Build shared library" ON)
option(LIBSQLGLOT_ENABLE_SIMD "Enable SIMD optimisations" ON)
option(LIBSQLGLOT_FUZZ "Build fuzz targets" OFF)
option(LIBSQLGLOT_PGO_GENERATE "Generate PGO profile data" OFF)
option(LIBSQLGLOT_PGO_USE "Use PGO profile data for optimization" OFF)

# Compiler flags for our code (not dependencies)
set(LIBSQLGLOT_CXX_FLAGS -Wall -Wextra -Wpedantic -Werror -fno-rtti)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    list(APPEND LIBSQLGLOT_CXX_FLAGS -O3 -march=native -flto -ffast-math -fmerge-all-constants -fvisibility=hidden)
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

# Header-only interface target
add_library(libsqlglot INTERFACE)
target_include_directories(libsqlglot INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(libsqlglot INTERFACE cxx_std_23)

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
