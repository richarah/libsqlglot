# Google Benchmark benchmarks for libsqlglot

# Tokenizer benchmarks
add_executable(bench_tokenizer bench_tokenizer.cpp)
target_link_libraries(bench_tokenizer PRIVATE libsqlglot benchmark::benchmark)
target_compile_options(bench_tokenizer PRIVATE ${LIBSQLGLOT_CXX_FLAGS})

# Parser benchmarks
add_executable(bench_parser bench_parser.cpp)
target_link_libraries(bench_parser PRIVATE libsqlglot benchmark::benchmark)
target_compile_options(bench_parser PRIVATE ${LIBSQLGLOT_CXX_FLAGS})

# Transpiler benchmarks
add_executable(bench_transpiler bench_transpiler.cpp)
target_link_libraries(bench_transpiler PRIVATE libsqlglot benchmark::benchmark)
target_compile_options(bench_transpiler PRIVATE ${LIBSQLGLOT_CXX_FLAGS})

# Copy mad_queries directory to build directory for tests
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/mad_queries)
file(GLOB MAD_QUERY_FILES ${CMAKE_CURRENT_SOURCE_DIR}/mad_queries/*.sql)
file(COPY ${MAD_QUERY_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/mad_queries)

# All benchmarks target
add_custom_target(run_benchmarks
    COMMAND bench_tokenizer --benchmark_format=console
    COMMAND bench_parser --benchmark_format=console
    COMMAND bench_transpiler --benchmark_format=console
    DEPENDS bench_tokenizer bench_parser bench_transpiler
    COMMENT "Running all benchmarks"
)
