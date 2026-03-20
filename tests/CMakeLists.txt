include(CTest)
include(Catch)

# Test executable
add_executable(libsqlglot_tests
    test_arena.cpp
    test_intern.cpp
    test_tokenizer.cpp
    test_parser.cpp
    test_transpiler.cpp
    test_end_to_end.cpp
    test_dml_statements.cpp
    test_cte_windows_subqueries.cpp
    test_advanced_sql.cpp
    test_stored_procedures.cpp
    test_dialect_transforms.cpp
    test_optimizer.cpp
    test_schema_type.cpp
    test_performance.cpp
    test_error_recovery.cpp
    test_error_messages.cpp
    test_security.cpp
    test_debug_pivot.cpp
    test_tokenizer_pivot.cpp
    test_for_keyword.cpp
    test_call_keyword.cpp
    test_return_keyword.cpp
    test_declare_keyword.cpp
    test_if_statement.cpp
    test_while_loop.cpp
    test_for_loop.cpp
    test_do_debug.cpp
    test_extract.cpp
    test_mad_queries.cpp
    test_unbounded_following.cpp
    test_dialect_transpilation.cpp
    test_all_dialects_comprehensive.cpp
    test_procedure_dialects.cpp
    test_begin_end_blocks.cpp
    test_for_while_transpile.cpp
    test_create_procedure.cpp
    test_delimiter.cpp
    test_assignments.cpp
    test_exceptions.cpp
    test_cursors.cpp
    test_raise.cpp
    test_main.cpp
)

target_link_libraries(libsqlglot_tests PRIVATE
    libsqlglot
    Catch2::Catch2WithMain
)

target_compile_features(libsqlglot_tests PRIVATE cxx_std_23)
target_compile_options(libsqlglot_tests PRIVATE ${LIBSQLGLOT_CXX_FLAGS})

# Discover tests
catch_discover_tests(libsqlglot_tests)
