#pragma once

#include "dialects.h"
#include <string_view>
#include <string>
#include <vector>
#include <stdexcept>
#include <meta>  // C++26 reflection

/**
 * C++26 Reflection-Based Dialect System
 *
 * This file uses C++26 compile-time reflection to automatically generate
 * dialect name mappings from the Dialect enum itself.
 *
 * ZERO RUNTIME COST: All reflection happens at compile time.
 * The generated code is identical to hand-written mappings.
 *
 * SINGLE SOURCE OF TRUTH: Only the Dialect enum in dialects.h needs maintenance.
 * Adding a new dialect means just adding one line to the enum.
 *
 * Benefits:
 * - Impossible to desync: Bindings are derived from enum automatically
 * - Maintenance-free: No manual lists to update
 * - Type-safe: Compile-time verification
 */

namespace libsqlglot::dialects {

/// Dialect name-value mapping
/// Using const char* instead of std::string_view for better ABI stability with nanobind
struct DialectMapping {
    const char* name;   // Dialect name (e.g., "ANSI", "MySQL", "PostgreSQL")
    Dialect value;      // Dialect enum value

    constexpr DialectMapping() noexcept : name(""), value(Dialect::ANSI) {}
    constexpr DialectMapping(const char* n, Dialect v) noexcept
        : name(n), value(v) {}
};

/// Generate dialect mappings from Dialect enum using C++26 reflection
/// This is 100% compile-time - ZERO runtime cost!
consteval auto generate_dialect_mappings() {
    using namespace std;
    using namespace std::meta;

    // Get all enum enumerators via C++26 reflection (^^Dialect gets reflection of Dialect)
    constexpr auto enumerators = enumerators_of(^^Dialect);
    constexpr size_t max_dialects = 64;  // Generous upper bound

    std::array<DialectMapping, max_dialects> result{};
    size_t idx = 0;

    // Iterate over enum enumerators at compile time
    template for (constexpr auto e : enumerators) {
        // Get the enumerator name as a string_view
        // identifier_of returns a std::string_view pointing to compiler-managed string storage
        // which has static storage duration and is safe to use via .data()
        constexpr auto name = identifier_of(e);

        // Skip the COUNT sentinel
        if constexpr (name != "COUNT") {
            // Get the enumerator value
            constexpr auto value = extract<Dialect>(e);

            // Store the mapping
            // The name.data() pointer is safe because it points to the compiler's
            // internal storage of the identifier name, which has static lifetime
            result[idx++] = DialectMapping{name.data(), value};
        }
    }

    return result;
}

// Generate the mappings at compile time
// Using a function that returns a static local to ensure single instantiation
// This provides better ABI stability across shared library boundaries
inline constexpr const auto& get_dialect_mappings_array() {
    static constexpr auto array = generate_dialect_mappings();
    return array;
}

// Access the mappings through the array
inline constexpr const DialectMapping* dialect_mappings = get_dialect_mappings_array().data();

/// Count of actual dialects (excluding COUNT sentinel)
consteval size_t count_dialects() {
    constexpr auto& arr = get_dialect_mappings_array();
    size_t count = 0;
    for (const auto& mapping : arr) {
        if (mapping.name != nullptr && mapping.name[0] != '\0') {
            count++;
        }
    }
    return count;
}

inline constexpr size_t DIALECT_COUNT = count_dialects();

// Compile-time verification
static_assert(DIALECT_COUNT > 0, "No dialects found - reflection failed");
static_assert(DIALECT_COUNT == static_cast<size_t>(Dialect::COUNT),
              "Dialect count mismatch - enum may have changed");

/// Compile-time validation: ensure no empty dialect names
consteval bool validate_dialects() {
    constexpr auto& arr = get_dialect_mappings_array();
    for (size_t i = 0; i < DIALECT_COUNT; ++i) {
        if (arr[i].name == nullptr || arr[i].name[0] == '\0') {
            return false;
        }
    }
    return true;
}
static_assert(validate_dialects(), "All dialects must have valid names");

/// Find dialect by name (case-insensitive) - runtime function
/// Uses compile-time generated mappings for zero-maintenance lookups
[[nodiscard]] inline Dialect from_name(std::string_view name) {
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

    throw std::runtime_error("Unknown dialect: " + std::string(name));
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
