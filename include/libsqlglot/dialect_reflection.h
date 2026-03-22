#pragma once

#include "dialects.h"
#include <string_view>
#include <string>
#include <vector>
#include <stdexcept>

/**
 * Automated Dialect Reflection System
 *
 * This file provides compile-time dialect name mappings automatically generated
 * from the Dialect enum in dialects.h.
 *
 * ZERO RUNTIME COST: All mappings are constexpr and compile-time generated.
 *
 * SINGLE SOURCE OF TRUTH: Only the Dialect enum in dialects.h needs maintenance.
 * Adding a new dialect means just adding one line to the enum.
 *
 * IMPLEMENTATION: Due to GCC 16 bug where enumerators_of() allocates memory
 * and cannot be used in constexpr contexts, we use build-time code generation:
 * - CMake runs scripts/generate_dialect_reflection.py
 * - Parses dialects.h and generates dialect_reflection_generated.h
 * - Generated file contains the constexpr mapping array
 *
 * When GCC fixes the reflection bug, this can be replaced with pure C++26 reflection.
 */

// Include the auto-generated mappings from the build directory
#include <libsqlglot/dialect_reflection_generated.h>

namespace libsqlglot::dialects {

/// Find dialect by name (case-insensitive) - runtime function
/// Uses compile-time generated mappings for zero-maintenance lookups
/// Returns ANSI dialect if name is unknown (fail-safe, not fail-fast)
[[nodiscard]] inline Dialect from_name(std::string_view name) noexcept {
    // Convert to lowercase for comparison
    auto to_lower = [](char c) { return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c; };

    for (size_t i = 0; i < DIALECT_COUNT; ++i) {
        std::string_view mapping_name(dialect_mappings[i].name);

        // Case-insensitive comparison
        if (mapping_name.size() == name.size()) {
            bool match = true;
            for (size_t j = 0; j < name.size(); ++j) {
                if (to_lower(mapping_name[j]) != to_lower(name[j])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return dialect_mappings[i].value;
            }
        }
    }

    // Handle common aliases
    std::string lower_name(name);
    for (char& c : lower_name) {
        if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
    }

    // Common aliases
    if (lower_name == "postgres" || lower_name == "postgresql") return Dialect::PostgreSQL;
    if (lower_name == "tsql" || lower_name == "sqlserver") return Dialect::SQLServer;
    if (lower_name == "cockroach" || lower_name == "cockroachdb") return Dialect::CockroachDB;

    // Unknown dialect - return ANSI as safe default (fail-safe)
    return Dialect::ANSI;
}

/// Get dialect name as string
[[nodiscard]] inline std::string to_string(Dialect dialect) {
    for (size_t i = 0; i < DIALECT_COUNT; ++i) {
        if (dialect_mappings[i].value == dialect) {
            return std::string(dialect_mappings[i].name);
        }
    }
    return "Unknown";
}

/// Get all dialect names (for iteration/debugging)
[[nodiscard]] inline std::vector<std::string> all_dialect_names() {
    std::vector<std::string> names;
    names.reserve(DIALECT_COUNT);
    for (size_t i = 0; i < DIALECT_COUNT; ++i) {
        names.emplace_back(dialect_mappings[i].name);
    }
    return names;
}

} // namespace libsqlglot::dialects
