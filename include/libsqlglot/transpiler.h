#pragma once

#include "parser.h"
#include "generator.h"
#include "optimizer.h"
#include "dialects.h"
#include "arena.h"
#include <string>

namespace libsqlglot {

/// High-level transpiler API
class Transpiler {
public:
    /// Parse SQL in source dialect and generate in target dialect
    static std::string transpile(
        const std::string& sql,
        [[maybe_unused]] Dialect source_dialect = Dialect::ANSI,
        Dialect target_dialect = Dialect::ANSI,
        bool optimize = true)
    {
        // Create arena for AST
        Arena arena;

        // Parse SQL
        Parser parser(arena, sql);
        auto expr = parser.parse_select();
        auto stmt = static_cast<SelectStmt*>(expr);  // Assume it's a SELECT for now

        // Apply optimizations
        if (optimize && stmt) {
            Optimizer::qualify_columns(stmt);
            if (stmt->where) {
                stmt->where = Optimizer::normalize(stmt->where);
            }
        }

        // Generate SQL in target dialect
        std::string result = Generator::generate(expr, target_dialect);

        return result;
    }

    /// Parse SQL and return AST
    static Expression* parse(Arena& arena, const std::string& sql) {
        Parser parser(arena, sql);
        return parser.parse_select();
    }

    /// Generate SQL from AST
    static std::string generate(Expression* expr, Dialect dialect = Dialect::ANSI) {
        return Generator::generate(expr, dialect);
    }

    /// Optimize AST in-place
    static void optimize(Arena& arena, SelectStmt* stmt) {
        if (!stmt) return;

        Optimizer::qualify_columns(stmt);

        // Apply predicate pushdown optimization
        Optimizer::pushdown_predicates(stmt, arena);

        // Apply subquery elimination
        Optimizer::eliminate_subqueries(stmt, arena);

        if (stmt->where) {
            stmt->where = Optimizer::normalize(stmt->where);
            stmt->where = Optimizer::fold_constants(stmt->where, arena);
        }
    }

    /// Parse, optimize, and generate
    static std::string process(
        Arena& arena,
        const std::string& sql,
        Dialect dialect = Dialect::ANSI)
    {
        auto expr = parse(arena, sql);
        auto stmt = static_cast<SelectStmt*>(expr);  // Assume SELECT for optimization
        optimize(arena, stmt);
        return generate(expr, dialect);
    }
};

} // namespace libsqlglot
