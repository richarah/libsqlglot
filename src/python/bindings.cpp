#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/function.h>

#include <libsqlglot/parser.h>
#include <libsqlglot/generator.h>
#include <libsqlglot/transpiler.h>
#include <libsqlglot/optimizer.h>
#include <libsqlglot/arena.h>
#include <libsqlglot/dialects.h>
#include <libsqlglot/dialect_reflection.h>
#include <libsqlglot/version.h>

#include <functional>
#include <vector>
#include <string>
#include <stdexcept>

namespace nb = nanobind;
using namespace libsqlglot;

static Arena& get_arena() {
    thread_local Arena* arena = new Arena();
    return *arena;
}

static Expression* parse_expr(const std::string& sql) {
    Arena& arena = get_arena();
    Parser parser(arena, sql);
    return parser.parse_expression_public();
}

// Helper function to recursively traverse and collect matching expressions
static void find_all_recursive(Expression* expr, ExprType type_to_find, std::vector<Expression*>& results) {
    if (!expr) return;

    if (expr->type == type_to_find) {
        results.push_back(expr);
    }

    // Traverse based on expression type
    if (auto* select = dynamic_cast<SelectStmt*>(expr)) {
        for (auto* col : select->columns) find_all_recursive(col, type_to_find, results);
        find_all_recursive(select->from, type_to_find, results);
        find_all_recursive(select->where, type_to_find, results);
        for (auto* gb : select->group_by) find_all_recursive(gb, type_to_find, results);
        find_all_recursive(select->having, type_to_find, results);
        find_all_recursive(select->qualify, type_to_find, results);
        for (auto* ob : select->order_by) find_all_recursive(ob, type_to_find, results);
        find_all_recursive(select->limit, type_to_find, results);
        find_all_recursive(select->offset, type_to_find, results);
    } else if (auto* binop = dynamic_cast<BinaryOp*>(expr)) {
        find_all_recursive(binop->left, type_to_find, results);
        find_all_recursive(binop->right, type_to_find, results);
    } else if (auto* unop = dynamic_cast<UnaryOp*>(expr)) {
        find_all_recursive(unop->operand, type_to_find, results);
    } else if (auto* func = dynamic_cast<FunctionCall*>(expr)) {
        for (auto* arg : func->args) find_all_recursive(arg, type_to_find, results);
    } else if (auto* alias = dynamic_cast<Alias*>(expr)) {
        find_all_recursive(alias->expr, type_to_find, results);
    }
    // Add more types as needed
}

// Helper function to walk all nodes in the tree
static void walk_recursive(Expression* expr, const std::function<void(Expression*)>& callback) {
    if (!expr) return;

    callback(expr);  // Call the callback on this node

    // Traverse based on expression type
    if (auto* select = dynamic_cast<SelectStmt*>(expr)) {
        for (auto* col : select->columns) walk_recursive(col, callback);
        walk_recursive(select->from, callback);
        walk_recursive(select->where, callback);
        for (auto* gb : select->group_by) walk_recursive(gb, callback);
        walk_recursive(select->having, callback);
        walk_recursive(select->qualify, callback);
        for (auto* ob : select->order_by) walk_recursive(ob, callback);
        walk_recursive(select->limit, callback);
        walk_recursive(select->offset, callback);
    } else if (auto* binop = dynamic_cast<BinaryOp*>(expr)) {
        walk_recursive(binop->left, callback);
        walk_recursive(binop->right, callback);
    } else if (auto* unop = dynamic_cast<UnaryOp*>(expr)) {
        walk_recursive(unop->operand, callback);
    } else if (auto* func = dynamic_cast<FunctionCall*>(expr)) {
        for (auto* arg : func->args) walk_recursive(arg, callback);
    } else if (auto* alias = dynamic_cast<Alias*>(expr)) {
        walk_recursive(alias->expr, callback);
    }
    // Add more types as needed
}

NB_MODULE(_libsqlglot, m) {
    m.doc() = "High-performance C++ SQL parser, transpiler, and optimiser";

    // Arena
    nb::class_<Arena>(m, "Arena").def(nb::init<>());

    // Dialect enum – using reflection-generated mappings
    // The mappings are automatically derived from the Dialect enum via C++26 reflection
    auto dialect_enum = nb::enum_<Dialect>(m, "Dialect");
    for (size_t i = 0; i < dialects::DIALECT_COUNT; ++i) {
        dialect_enum.value(dialects::dialect_mappings[i].name,
                          dialects::dialect_mappings[i].value);
    }
    dialect_enum.export_values();

    // ExprType enum – auto-generated bindings
    // To regenerate: python3 scripts/generate_expr_type_bindings.py > src/python/expr_type_bindings_generated.h
#include "expr_type_bindings_generated.h"

    // Expression base
    nb::class_<Expression>(m, "Expression")
        .def_ro("type", &Expression::type)
        .def("sql", [](Expression* expr, nb::object dialect = nb::none(), bool pretty = false) {
            Dialect d = Dialect::ANSI;
            if (!dialect.is_none()) {
                if (nb::isinstance<nb::str>(dialect))
                    d = dialects::from_name(nb::cast<std::string>(dialect));
                else if (nb::isinstance<nb::int_>(dialect))
                    d = static_cast<Dialect>(nb::cast<int>(dialect));
                else
                    d = nb::cast<Dialect>(dialect);
            }
            Generator::Options opts;
            opts.pretty = pretty;
            return Generator::generate(expr, d, opts);
        }, nb::arg("dialect") = nb::none(), nb::arg("pretty") = false)
        .def("find_all", [](Expression* expr, ExprType type_to_find) -> nb::list {
            std::vector<Expression*> results;
            find_all_recursive(expr, type_to_find, results);
            nb::list py_results;
            for (auto* result : results) {
                py_results.append(result);
            }
            return py_results;
        }, nb::arg("expr_type"))
        .def("walk", [](Expression* expr, nb::object func) {
            auto callback = [&func](Expression* node) {
                func(node);
            };
            walk_recursive(expr, callback);
        }, nb::arg("callback"));

    // Column
    nb::class_<Column, Expression>(m, "Column")
        .def_prop_ro("table", [](Column& col) -> std::string { return col.table; })
        .def_prop_ro("name", [](Column& col) -> std::string { return col.column; });

    // Literal
    nb::class_<Literal, Expression>(m, "Literal")
        .def_prop_ro("value", [](Literal& lit) -> std::string { return lit.value; });

    // Star
    nb::class_<Star, Expression>(m, "Star")
        .def_prop_ro("table", [](Star& star) -> std::string { return star.table; });

    // TableRef
    nb::class_<TableRef, Expression>(m, "TableRef")
        .def_prop_ro("database", [](TableRef& tbl) -> std::string { return tbl.database; })
        .def_prop_ro("schema", [](TableRef& tbl) -> std::string { return tbl.schema; })
        .def_prop_ro("table", [](TableRef& tbl) -> std::string { return tbl.table; })
        .def_prop_ro("alias", [](TableRef& tbl) -> std::string { return tbl.alias; });

    // SelectStmt
    nb::class_<SelectStmt, Expression>(m, "SelectStmt")
        .def_ro("distinct", &SelectStmt::distinct)
        .def_ro("columns", &SelectStmt::columns)
        .def_prop_ro("from_table", [](SelectStmt* stmt) { return stmt->from; })
        .def_prop_ro("where_clause", [](SelectStmt* stmt) { return stmt->where; })
        .def_prop_ro("group_by_clause", [](SelectStmt* stmt) { return stmt->group_by; })
        .def_prop_ro("having_clause", [](SelectStmt* stmt) { return stmt->having; })
        .def_prop_ro("order_by_clause", [](SelectStmt* stmt) { return stmt->order_by; })
        .def_prop_ro("limit_value", [](SelectStmt* stmt) { return stmt->limit; })
        .def_prop_ro("offset_value", [](SelectStmt* stmt) { return stmt->offset; })
        .def_prop_ro("with_clause", [](SelectStmt* stmt) { return stmt->with; })

        // Fluent builder
        .def("from_", [](SelectStmt* self, const std::string& table) -> SelectStmt* {
            Arena& arena = get_arena();
            self->from = arena.create<TableRef>(table);
            return self;
        })
        .def("where", [](SelectStmt* self, const std::string& condition) -> SelectStmt* {
            try {
                self->where = parse_expr(condition);
            } catch (const std::exception& e) {
                throw nb::value_error(("Failed to parse WHERE condition: " + std::string(e.what())).c_str());
            }
            return self;
        })
        .def("limit", [](SelectStmt* self, int n) -> SelectStmt* {
            Arena& arena = get_arena();
            self->limit = arena.create<Literal>(std::to_string(n));
            return self;
        })
        .def("order_by", [](SelectStmt* self, const std::string& col) -> SelectStmt* {
            Arena& arena = get_arena();
            self->order_by.push_back(arena.create<Column>(col));
            return self;
        });

    // Parser
    nb::class_<Parser>(m, "Parser")
        .def(nb::init<Arena&, std::string_view>(), nb::arg("arena"), nb::arg("sql"))
        .def("parse", &Parser::parse)
        .def("parse_select", &Parser::parse_select)
        .def("parse_insert", &Parser::parse_insert)
        .def("parse_update", &Parser::parse_update)
        .def("parse_delete", &Parser::parse_delete)
        .def("parse_create_table", &Parser::parse_create_table);

    // Generator
    m.def("generate", [](Expression* expr, nb::object dialect = nb::none(), bool pretty = false) -> std::string {
        Dialect d = Dialect::ANSI;
        if (!dialect.is_none()) {
            if (nb::isinstance<nb::str>(dialect))
                d = dialects::from_name(nb::cast<std::string>(dialect));
            else if (nb::isinstance<nb::int_>(dialect))
                d = static_cast<Dialect>(nb::cast<int>(dialect));
            else
                d = nb::cast<Dialect>(dialect);
        }
        Generator::Options opts;
        opts.pretty = pretty;
        return Generator::generate(expr, d, opts);
    }, nb::arg("expr"), nb::arg("dialect") = nb::none(), nb::arg("pretty") = false);

    // High-level parse functions - convert all C++ exceptions to Python RuntimeError
    m.def("parse", [](const std::string& sql) -> Expression* {
        try {
            Parser parser(get_arena(), sql);
            return parser.parse();
        } catch (const std::exception& e) {
            throw std::runtime_error(e.what());
        }
    }, nb::arg("sql"), nb::rv_policy::reference);

    m.def("parse_one", [](const std::string& sql) -> Expression* {
        try {
            Parser parser(get_arena(), sql);
            return parser.parse();
        } catch (const std::exception& e) {
            throw std::runtime_error(e.what());
        }
    }, nb::arg("sql"), nb::rv_policy::reference);

    // Transpile - convert all C++ exceptions to Python RuntimeError
    m.def("transpile", [](const std::string& sql,
                          nb::object from_dialect = nb::none(),
                          nb::object to_dialect = nb::none(),
                          nb::object read = nb::none(),
                          nb::object write = nb::none()) -> std::string {
        try {
            Dialect from_d = Dialect::ANSI;
            Dialect to_d = Dialect::ANSI;

            if (!read.is_none()) {
                if (nb::isinstance<nb::str>(read))
                    from_d = dialects::from_name(nb::cast<std::string>(read));
                else if (nb::isinstance<nb::int_>(read))
                    from_d = static_cast<Dialect>(nb::cast<int>(read));
            } else if (!from_dialect.is_none()) {
                if (nb::isinstance<nb::str>(from_dialect))
                    from_d = dialects::from_name(nb::cast<std::string>(from_dialect));
                else if (nb::isinstance<nb::int_>(from_dialect))
                    from_d = static_cast<Dialect>(nb::cast<int>(from_dialect));
            }

            if (!write.is_none()) {
                if (nb::isinstance<nb::str>(write))
                    to_d = dialects::from_name(nb::cast<std::string>(write));
                else if (nb::isinstance<nb::int_>(write))
                    to_d = static_cast<Dialect>(nb::cast<int>(write));
            } else if (!to_dialect.is_none()) {
                if (nb::isinstance<nb::str>(to_dialect))
                    to_d = dialects::from_name(nb::cast<std::string>(to_dialect));
                else if (nb::isinstance<nb::int_>(to_dialect))
                    to_d = static_cast<Dialect>(nb::cast<int>(to_dialect));
            }

            return Transpiler::transpile(sql, from_d, to_d);
        } catch (const std::exception& e) {
            throw std::runtime_error(e.what());
        }
    }, nb::arg("sql"), nb::arg("from_dialect") = nb::none(), nb::arg("to_dialect") = nb::none(),
       nb::arg("read") = nb::none(), nb::arg("write") = nb::none());

    // Optimizer
    m.def("optimize", [](Expression* expr) -> Expression* {
        if (auto* select = dynamic_cast<SelectStmt*>(expr)) {
            Transpiler::optimize(get_arena(), select);
        }
        return expr;
    }, nb::arg("expr"), nb::rv_policy::reference);

    // Diff
    m.def("diff", [](const std::string& sql1, const std::string& sql2) -> std::string {
        thread_local Arena* arena1 = new Arena();
        thread_local Arena* arena2 = new Arena();
        Parser p1(*arena1, sql1);
        Parser p2(*arena2, sql2);
        Expression* expr1 = p1.parse();
        Expression* expr2 = p2.parse();
        if (expr1->type != expr2->type)
            return "Expression types differ: " + std::to_string(static_cast<int>(expr1->type)) + " vs " +
                   std::to_string(static_cast<int>(expr2->type));
        std::string gen1 = Generator::generate(expr1);
        std::string gen2 = Generator::generate(expr2);
        if (gen1 == gen2) return "No differences";
        return "SQL differs:\nLeft:  " + gen1 + "\nRight: " + gen2;
    }, nb::arg("sql1"), nb::arg("sql2"));

    // Fluent builder entry points
    m.def("select", [](const std::vector<std::string>& columns) -> SelectStmt* {
        Arena& arena = get_arena();
        auto* stmt = arena.create<SelectStmt>();
        for (const auto& col_name : columns) {
            auto* col = arena.create<Column>(col_name);
            stmt->columns.push_back(col);
        }
        return stmt;
    }, nb::arg("columns"), nb::rv_policy::reference);

    m.def("select", []() -> SelectStmt* {
        Arena& arena = get_arena();
        auto* stmt = arena.create<SelectStmt>();
        auto* star = arena.create<Star>();
        stmt->columns.push_back(star);
        return stmt;
    }, nb::rv_policy::reference);

    // Version and dialect count
    m.attr("__version__") = LIBSQLGLOT_VERSION;
    m.attr("__dialect_count__") = static_cast<int>(dialects::DIALECT_COUNT);
}