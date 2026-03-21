#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

#include <libsqlglot/parser.h>
#include <libsqlglot/generator.h>
#include <libsqlglot/transpiler.h>
#include <libsqlglot/optimizer.h>
#include <libsqlglot/arena.h>
#include <libsqlglot/dialects.h>

#include <functional>
#include <vector>
#include <string>

namespace nb = nanobind;
using namespace libsqlglot;

// Thread-local arena accessor - intentionally never freed for maximum performance
// OS will reclaim memory at process exit. This is a common high-performance pattern
// in C++ Python extensions and avoids exit-time cleanup order issues.
static Arena& get_arena() {
    thread_local Arena* arena = new Arena();
    return *arena;
}

// Helper function to convert string dialect names to Dialect enum
static Dialect parse_dialect(const std::string& name) {
    std::string lower_name = name;
    for (char& c : lower_name) {
        if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
    }

    if (lower_name == "ansi") return Dialect::ANSI;
    if (lower_name == "mysql") return Dialect::MySQL;
    if (lower_name == "postgresql" || lower_name == "postgres") return Dialect::PostgreSQL;
    if (lower_name == "sqlite") return Dialect::SQLite;
    if (lower_name == "bigquery") return Dialect::BigQuery;
    if (lower_name == "snowflake") return Dialect::Snowflake;
    if (lower_name == "redshift") return Dialect::Redshift;
    if (lower_name == "oracle") return Dialect::Oracle;
    if (lower_name == "sqlserver" || lower_name == "tsql") return Dialect::SQLServer;
    if (lower_name == "duckdb") return Dialect::DuckDB;
    if (lower_name == "clickhouse") return Dialect::ClickHouse;
    if (lower_name == "presto") return Dialect::Presto;
    if (lower_name == "trino") return Dialect::Trino;
    if (lower_name == "hive") return Dialect::Hive;
    if (lower_name == "spark") return Dialect::Spark;
    if (lower_name == "athena") return Dialect::Athena;
    if (lower_name == "databricks") return Dialect::Databricks;

    throw std::runtime_error("Unknown dialect: " + name);
}

NB_MODULE(_libsqlglot, m) {
    m.doc() = "High-performance C++ SQL parser, transpiler, and optimiser";

    // Arena - memory management
    nb::class_<Arena>(m, "Arena")
        .def(nb::init<>(), "Create a new memory arena for SQL AST nodes");

    // Dialect enum
    nb::enum_<Dialect>(m, "Dialect")
        .value("ANSI", Dialect::ANSI)
        .value("MySQL", Dialect::MySQL)
        .value("PostgreSQL", Dialect::PostgreSQL)
        .value("SQLite", Dialect::SQLite)
        .value("BigQuery", Dialect::BigQuery)
        .value("Snowflake", Dialect::Snowflake)
        .value("Redshift", Dialect::Redshift)
        .value("Oracle", Dialect::Oracle)
        .value("SQLServer", Dialect::SQLServer)
        .value("DuckDB", Dialect::DuckDB)
        .value("ClickHouse", Dialect::ClickHouse)
        .value("Presto", Dialect::Presto)
        .value("Trino", Dialect::Trino)
        .value("Hive", Dialect::Hive)
        .value("Spark", Dialect::Spark)
        .value("Athena", Dialect::Athena)
        .value("Databricks", Dialect::Databricks)
        .export_values();

    // Expression type enum
    nb::enum_<ExprType>(m, "ExprType")
        .value("LITERAL", ExprType::LITERAL)
        .value("COLUMN", ExprType::COLUMN)
        .value("STAR", ExprType::STAR)
        .value("EQ", ExprType::EQ)
        .value("NEQ", ExprType::NEQ)
        .value("LT", ExprType::LT)
        .value("LTE", ExprType::LTE)
        .value("GT", ExprType::GT)
        .value("GTE", ExprType::GTE)
        .value("LIKE", ExprType::LIKE)
        .value("ILIKE", ExprType::ILIKE)
        .value("NOT_LIKE", ExprType::NOT_LIKE)
        .value("NOT_ILIKE", ExprType::NOT_ILIKE)
        .value("FUNCTION_CALL", ExprType::FUNCTION_CALL)
        .value("SELECT_STMT", ExprType::SELECT_STMT)
        .value("INSERT_STMT", ExprType::INSERT_STMT)
        .value("UPDATE_STMT", ExprType::UPDATE_STMT)
        .value("DELETE_STMT", ExprType::DELETE_STMT)
        .value("CREATE_TABLE_STMT", ExprType::CREATE_TABLE_STMT)
        .value("TABLE_REF", ExprType::TABLE_REF)
        .value("JOIN_CLAUSE", ExprType::JOIN_CLAUSE)
        .value("SUBQUERY", ExprType::SUBQUERY)
        .value("WINDOW_FUNCTION", ExprType::WINDOW_FUNCTION)
        .value("WITH_CLAUSE", ExprType::WITH_CLAUSE)
        .value("CTE", ExprType::CTE)
        .value("AGG_COUNT", ExprType::AGG_COUNT)
        .value("AGG_SUM", ExprType::AGG_SUM)
        .value("AGG_AVG", ExprType::AGG_AVG)
        .value("AGG_MIN", ExprType::AGG_MIN)
        .value("AGG_MAX", ExprType::AGG_MAX)
        .export_values();

    // Expression base class with AST traversal and convenience methods
    nb::class_<Expression>(m, "Expression")
        .def_ro("type", &Expression::type, "Expression type")
        .def("sql", [](Expression* expr, Dialect dialect = Dialect::ANSI, bool pretty = false) {
            Generator::Options opts;
            opts.pretty = pretty;
            return Generator::generate(expr, dialect, opts);
        },
        nb::arg("dialect") = Dialect::ANSI,
        nb::arg("pretty") = false,
        "Generate SQL from this expression (sqlglot-compatible API)")

        .def("find_all", [](Expression* expr, ExprType type_to_find) -> std::vector<Expression*> {
            std::vector<Expression*> results;
            std::function<void(Expression*)> traverse = [&](Expression* e) {
                if (!e) return;
                if (e->type == type_to_find) {
                    results.push_back(e);
                }
                // Traverse common expression structures
                if (auto* select = dynamic_cast<SelectStmt*>(e)) {
                    for (auto* col : select->columns) traverse(col);
                    traverse(select->from);
                    traverse(select->where);
                    for (auto* g : select->group_by) traverse(g);
                    traverse(select->having);
                    for (auto* o : select->order_by) traverse(o);
                } else if (auto* binop = dynamic_cast<BinaryOp*>(e)) {
                    traverse(binop->left);
                    traverse(binop->right);
                } else if (auto* unop = dynamic_cast<UnaryOp*>(e)) {
                    traverse(unop->operand);
                }
                // Add more expression types as needed
            };
            traverse(expr);
            return results;
        }, nb::arg("expr_type"), "Find all expressions of given type in AST")

        .def("walk", [](Expression* expr, nb::object func) {
            std::function<void(Expression*)> traverse = [&](Expression* e) {
                if (!e) return;
                func(e);  // Call Python callback
                // Traverse children
                if (auto* select = dynamic_cast<SelectStmt*>(e)) {
                    for (auto* col : select->columns) traverse(col);
                    traverse(select->from);
                    traverse(select->where);
                    for (auto* g : select->group_by) traverse(g);
                    traverse(select->having);
                    for (auto* o : select->order_by) traverse(o);
                } else if (auto* binop = dynamic_cast<BinaryOp*>(e)) {
                    traverse(binop->left);
                    traverse(binop->right);
                } else if (auto* unop = dynamic_cast<UnaryOp*>(e)) {
                    traverse(unop->operand);
                }
            };
            traverse(expr);
        }, nb::arg("callback"), "Walk the AST and call callback for each node");

    // SelectStmt
    nb::class_<SelectStmt, Expression>(m, "SelectStmt")
        .def_ro("distinct", &SelectStmt::distinct)
        .def_ro("columns", &SelectStmt::columns)
        .def_ro("from", &SelectStmt::from)
        .def_ro("where", &SelectStmt::where)
        .def_ro("group_by", &SelectStmt::group_by)
        .def_ro("having", &SelectStmt::having)
        .def_ro("order_by", &SelectStmt::order_by)
        .def_ro("limit", &SelectStmt::limit)
        .def_ro("offset", &SelectStmt::offset)
        .def_ro("with", &SelectStmt::with);

    // Parser
    nb::class_<Parser>(m, "Parser")
        .def(nb::init<Arena&, std::string_view>(),
             nb::arg("arena"), nb::arg("sql"),
             "Create a parser for the given SQL string")
        .def("parse", &Parser::parse,
             "Parse any SQL statement")
        .def("parse_select", &Parser::parse_select,
             "Parse a SELECT statement")
        .def("parse_insert", &Parser::parse_insert,
             "Parse an INSERT statement")
        .def("parse_update", &Parser::parse_update,
             "Parse an UPDATE statement")
        .def("parse_delete", &Parser::parse_delete,
             "Parse a DELETE statement")
        .def("parse_create_table", &Parser::parse_create_table,
             "Parse a CREATE TABLE statement");

    // Generator - static methods with pretty-printing support
    m.def("generate",
          [](Expression* expr, Dialect dialect = Dialect::ANSI, bool pretty = false) -> std::string {
              Generator::Options opts;
              opts.pretty = pretty;
              return Generator::generate(expr, dialect, opts);
          },
          nb::arg("expr"),
          nb::arg("dialect") = Dialect::ANSI,
          nb::arg("pretty") = false,
          "Generate SQL from an AST expression with optional pretty-printing");

    // Transpiler - high-level API
    m.def("parse",
          [](const std::string& sql) -> Expression* {
              Parser parser(get_arena(), sql);
              return parser.parse();
          },
          nb::arg("sql"),
          nb::rv_policy::reference,
          "Parse SQL and return AST (convenience function)");

    // Alias for sqlglot compatibility
    m.def("parse_one",
          [](const std::string& sql) -> Expression* {
              Parser parser(get_arena(), sql);
              return parser.parse();
          },
          nb::arg("sql"),
          nb::rv_policy::reference,
          "Parse SQL and return AST (sqlglot-compatible alias for parse())");

    // Transpile with improved API: supports both Dialect enum and string names
    // Also supports keyword arguments: read="mysql", write="spark"
    m.def("transpile",
          [](const std::string& sql,
             nb::object from_dialect = nb::none(),
             nb::object to_dialect = nb::none(),
             nb::object read = nb::none(),
             nb::object write = nb::none()) -> std::string {

              Dialect from_d = Dialect::ANSI;
              Dialect to_d = Dialect::ANSI;

              // Handle "read" keyword argument (source dialect)
              if (!read.is_none()) {
                  if (nb::isinstance<nb::str>(read)) {
                      from_d = parse_dialect(nb::cast<std::string>(read));
                  } else if (nb::isinstance<nb::int_>(read)) {
                      from_d = static_cast<Dialect>(nb::cast<int>(read));
                  }
              }
              // "from_dialect" positional arg overrides "read"
              else if (!from_dialect.is_none()) {
                  if (nb::isinstance<nb::str>(from_dialect)) {
                      from_d = parse_dialect(nb::cast<std::string>(from_dialect));
                  } else if (nb::isinstance<nb::int_>(from_dialect)) {
                      from_d = static_cast<Dialect>(nb::cast<int>(from_dialect));
                  }
              }

              // Handle "write" keyword argument (target dialect)
              if (!write.is_none()) {
                  if (nb::isinstance<nb::str>(write)) {
                      to_d = parse_dialect(nb::cast<std::string>(write));
                  } else if (nb::isinstance<nb::int_>(write)) {
                      to_d = static_cast<Dialect>(nb::cast<int>(write));
                  }
              }
              // "to_dialect" positional arg overrides "write"
              else if (!to_dialect.is_none()) {
                  if (nb::isinstance<nb::str>(to_dialect)) {
                      to_d = parse_dialect(nb::cast<std::string>(to_dialect));
                  } else if (nb::isinstance<nb::int_>(to_dialect)) {
                      to_d = static_cast<Dialect>(nb::cast<int>(to_dialect));
                  }
              }

              return Transpiler::transpile(sql, from_d, to_d);
          },
          nb::arg("sql"),
          nb::arg("from_dialect") = nb::none(),
          nb::arg("to_dialect") = nb::none(),
          nb::arg("read") = nb::none(),
          nb::arg("write") = nb::none(),
          "Transpile SQL from one dialect to another. "
          "Supports both Dialect enum and string names (case-insensitive). "
          "Use read= for source dialect, write= for target dialect.");

    // Optimizer API
    m.def("optimize",
          [](Expression* expr) -> Expression* {
              // Optimizer only works on SELECT statements
              if (auto* select = dynamic_cast<SelectStmt*>(expr)) {
                  Transpiler::optimize(get_arena(), select);
              }
              return expr;
          },
          nb::arg("expr"),
          nb::rv_policy::reference,
          "Optimize SQL expression (column qualification, predicate pushdown, constant folding)");

    // SQL diff/comparison
    m.def("diff",
          [](const std::string& sql1, const std::string& sql2) -> std::string {
              // Use separate arenas for independent SQL statements
              thread_local Arena* arena1 = new Arena();
              thread_local Arena* arena2 = new Arena();

              Parser p1(*arena1, sql1);
              Parser p2(*arena2, sql2);
              Expression* expr1 = p1.parse();
              Expression* expr2 = p2.parse();

              // Simple structural comparison
              if (expr1->type != expr2->type) {
                  return "Expression types differ: " +
                         std::to_string(static_cast<int>(expr1->type)) + " vs " +
                         std::to_string(static_cast<int>(expr2->type));
              }

              std::string gen1 = Generator::generate(expr1);
              std::string gen2 = Generator::generate(expr2);

              if (gen1 == gen2) {
                  return "No differences";
              }

              return "SQL differs:\nLeft:  " + gen1 + "\nRight: " + gen2;
          },
          nb::arg("sql1"),
          nb::arg("sql2"),
          "Compare two SQL expressions and show differences");

    // Fluent expression builders (using SelectStmt class already defined above)
    m.def("select",
          [](const std::vector<std::string>& columns) -> SelectStmt* {
              Arena& arena = get_arena();
              auto* stmt = arena.create<SelectStmt>();
              for (const auto& col_name : columns) {
                  auto* col = arena.create<Column>(col_name);
                  stmt->columns.push_back(col);
              }
              return stmt;
          },
          nb::arg("columns"),
          nb::rv_policy::reference,
          "Create SELECT statement with columns (fluent builder start)");

    m.def("select",
          []() -> SelectStmt* {
              Arena& arena = get_arena();
              auto* stmt = arena.create<SelectStmt>();
              auto* star = arena.create<Star>();
              stmt->columns.push_back(star);
              return stmt;
          },
          nb::rv_policy::reference,
          "Create SELECT * statement (fluent builder start)");

    // Version info
    m.attr("__version__") = "0.1.0";
    m.attr("__dialect_count__") = 31;  // Number of supported dialects
}
