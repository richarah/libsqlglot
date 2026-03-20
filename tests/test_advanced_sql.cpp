#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/parser.h>
#include <libsqlglot/generator.h>
#include <libsqlglot/keywords.h>

using namespace libsqlglot;

// ============================================================================
// SET OPERATIONS - Tests for UNION/INTERSECT/EXCEPT
// ============================================================================

TEST_CASE("Keyword lookup - INTERSECT and EXCEPT", "[advanced][keywords]") {
    // Test that INTERSECT and EXCEPT are recognized as keywords
    auto intersect_token = KeywordLookup::lookup("INTERSECT");
    auto except_token = KeywordLookup::lookup("EXCEPT");
    auto set_token = KeywordLookup::lookup("SET");
    auto or_token = KeywordLookup::lookup("OR");

    REQUIRE(intersect_token == TokenType::INTERSECT);
    REQUIRE(except_token == TokenType::EXCEPT);
    REQUIRE(set_token == TokenType::SET);
    REQUIRE(or_token == TokenType::OR);
}

TEST_CASE("Set operations - UNION", "[advanced][set_operations]") {
    Arena arena;
    Parser parser(arena, "SELECT id FROM users UNION SELECT id FROM admins");

    auto expr = parser.parse_select();

    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::UNION_STMT);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("UNION") != std::string::npos);
}

TEST_CASE("Set operations - UNION ALL", "[advanced][set_operations]") {
    Arena arena;
    Parser parser(arena, "SELECT id FROM users UNION ALL SELECT id FROM admins");

    auto expr = parser.parse_select();

    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::UNION_STMT);
    auto* set_op = static_cast<SetOperation*>(expr);
    REQUIRE(set_op->all == true);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("UNION ALL") != std::string::npos);
}

TEST_CASE("Set operations - INTERSECT", "[advanced][set_operations]") {
    Arena arena;
    Parser parser(arena, "SELECT id FROM users INTERSECT SELECT id FROM admins");

    auto expr = parser.parse_select();

    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::INTERSECT_STMT);
    auto* set_op = static_cast<SetOperation*>(expr);
    REQUIRE(set_op->op_type == SetOperation::OpType::INTERSECT);
    REQUIRE(set_op->all == false);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("INTERSECT") != std::string::npos);
}

TEST_CASE("Set operations - INTERSECT ALL", "[advanced][set_operations]") {
    Arena arena;
    Parser parser(arena, "SELECT id FROM users INTERSECT ALL SELECT id FROM admins");

    auto expr = parser.parse_select();

    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::INTERSECT_STMT);
    auto* set_op = static_cast<SetOperation*>(expr);
    REQUIRE(set_op->op_type == SetOperation::OpType::INTERSECT);
    REQUIRE(set_op->all == true);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("INTERSECT ALL") != std::string::npos);
}

TEST_CASE("Set operations - EXCEPT", "[advanced][set_operations]") {
    Arena arena;
    Parser parser(arena, "SELECT id FROM users EXCEPT SELECT id FROM admins");

    auto expr = parser.parse_select();

    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::EXCEPT_STMT);
    auto* set_op = static_cast<SetOperation*>(expr);
    REQUIRE(set_op->op_type == SetOperation::OpType::EXCEPT);
    REQUIRE(set_op->all == false);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("EXCEPT") != std::string::npos);
}

TEST_CASE("Set operations - EXCEPT ALL", "[advanced][set_operations]") {
    Arena arena;
    Parser parser(arena, "SELECT id FROM users EXCEPT ALL SELECT id FROM admins");

    auto expr = parser.parse_select();

    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::EXCEPT_STMT);
    auto* set_op = static_cast<SetOperation*>(expr);
    REQUIRE(set_op->op_type == SetOperation::OpType::EXCEPT);
    REQUIRE(set_op->all == true);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("EXCEPT ALL") != std::string::npos);
}

// ============================================================================
// CASE EXPRESSIONS
// ============================================================================

TEST_CASE("CASE - Simple CASE expression", "[advanced][case]") {
    Arena arena;
    Parser parser(arena,
        "SELECT CASE status WHEN 1 THEN 'active' WHEN 2 THEN 'inactive' ELSE 'unknown' END FROM users");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->columns.size() == 1);
    REQUIRE(stmt->columns[0]->type == ExprType::CASE_EXPR);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("CASE") != std::string::npos);
    REQUIRE(sql.find("WHEN") != std::string::npos);
    REQUIRE(sql.find("THEN") != std::string::npos);
    REQUIRE(sql.find("ELSE") != std::string::npos);
    REQUIRE(sql.find("END") != std::string::npos);
}

TEST_CASE("CASE - Searched CASE expression", "[advanced][case]") {
    Arena arena;
    Parser parser(arena,
        "SELECT CASE WHEN age < 18 THEN 'minor' WHEN age < 65 THEN 'adult' ELSE 'senior' END FROM users");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->columns.size() == 1);
    REQUIRE(stmt->columns[0]->type == ExprType::CASE_EXPR);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("CASE WHEN") != std::string::npos);
}

TEST_CASE("CASE - Without ELSE clause", "[advanced][case]") {
    Arena arena;
    Parser parser(arena,
        "SELECT CASE WHEN premium = 1 THEN 'Premium' END FROM users");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->columns[0]->type == ExprType::CASE_EXPR);

    std::string sql = Generator::generate(expr);
    REQUIRE(!sql.empty());
}

// ============================================================================
// PREDICATES - BETWEEN, IN, EXISTS
// ============================================================================

TEST_CASE("Predicates - BETWEEN", "[advanced][predicates]") {
    Arena arena;
    Parser parser(arena, "SELECT * FROM users WHERE age BETWEEN 18 AND 65");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->where != nullptr);
    REQUIRE(stmt->where->type == ExprType::BETWEEN);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("BETWEEN") != std::string::npos);
}

TEST_CASE("Predicates - IN with values", "[advanced][predicates]") {
    Arena arena;
    Parser parser(arena, "SELECT * FROM users WHERE status IN (1, 2, 3)");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->where != nullptr);
    REQUIRE(stmt->where->type == ExprType::IN);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("IN (") != std::string::npos);
}

TEST_CASE("Predicates - IN with subquery", "[advanced][predicates]") {
    Arena arena;
    Parser parser(arena, "SELECT * FROM users WHERE id IN (SELECT user_id FROM premium)");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->where != nullptr);
    REQUIRE(stmt->where->type == ExprType::IN);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("IN (") != std::string::npos);
}

TEST_CASE("Predicates - EXISTS", "[advanced][predicates]") {
    Arena arena;
    Parser parser(arena, "SELECT * FROM users WHERE EXISTS (SELECT 1 FROM orders WHERE user_id = users.id)");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->where != nullptr);
    REQUIRE(stmt->where->type == ExprType::EXISTS);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("EXISTS (") != std::string::npos);
}

TEST_CASE("Predicates - NOT EXISTS", "[advanced][predicates]") {
    Arena arena;
    Parser parser(arena, "SELECT * FROM users WHERE NOT EXISTS (SELECT 1 FROM orders WHERE user_id = users.id)");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->where != nullptr);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("NOT") != std::string::npos);
    REQUIRE(sql.find("EXISTS") != std::string::npos);
}

// ============================================================================
// TRANSACTION STATEMENTS
// ============================================================================

TEST_CASE("Transaction - BEGIN", "[advanced][transaction]") {
    Arena arena;
    Parser parser(arena, "BEGIN");

    auto stmt = parser.parse_begin();

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->type == ExprType::BEGIN_STMT);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql == "BEGIN");
}

// ============================================================================
// UTILITY STATEMENTS
// ============================================================================

TEST_CASE("Utility - SET variable", "[advanced][utility]") {
    Arena arena;
    Parser parser(arena, "SET autocommit = 1");

    auto stmt = parser.parse_set_statement();

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->type == ExprType::SET_STMT);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql.find("SET") != std::string::npos);
}

TEST_CASE("Utility - SET SESSION variable", "[advanced][utility]") {
    Arena arena;
    Parser parser(arena, "SET SESSION autocommit = 1");

    auto stmt = parser.parse_set_statement();
    auto* set = static_cast<SetStmt*>(stmt);

    REQUIRE(set->scope == SetStmt::Scope::SESSION);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql.find("SET SESSION") != std::string::npos);
}

TEST_CASE("Utility - DESCRIBE table", "[advanced][utility]") {
    Arena arena;
    Parser parser(arena, "DESCRIBE users");

    auto stmt = parser.parse_describe();

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->type == ExprType::DESCRIBE_STMT);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql.find("DESCRIBE") != std::string::npos);
}

// ============================================================================
// ADVANCED FEATURES
// ============================================================================

TEST_CASE("Advanced - VALUES clause", "[advanced][values]") {
    Arena arena;
    Parser parser(arena, "VALUES (1, 'a'), (2, 'b'), (3, 'c')");

    auto stmt = parser.parse_values_clause();

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->type == ExprType::VALUES_CLAUSE);

    std::string sql = Generator::generate(stmt);
    REQUIRE(sql.find("VALUES") != std::string::npos);
}

TEST_CASE("Advanced - Array literal", "[advanced][array]") {
    Arena arena;
    Parser parser(arena, "SELECT [1, 2, 3, 4, 5]");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->columns.size() == 1);
    REQUIRE(stmt->columns[0]->type == ExprType::ARRAY_LITERAL);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("[") != std::string::npos);
    REQUIRE(sql.find("]") != std::string::npos);
}

TEST_CASE("Advanced - Array indexing", "[advanced][array]") {
    Arena arena;
    Parser parser(arena, "SELECT data[1] FROM arrays");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->columns.size() == 1);
    REQUIRE(stmt->columns[0]->type == ExprType::ARRAY_INDEX);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("[") != std::string::npos);
}

// ============================================================================
// COMPLEX COMBINED TESTS
// ============================================================================

TEST_CASE("Complex - CTE with CASE and BETWEEN", "[advanced][complex]") {
    Arena arena;
    Parser parser(arena,
        "WITH categorized AS ("
        "  SELECT id, "
        "    CASE WHEN age BETWEEN 0 AND 17 THEN 'minor' "
        "         WHEN age BETWEEN 18 AND 64 THEN 'adult' "
        "         ELSE 'senior' END AS category "
        "  FROM users"
        ") "
        "SELECT * FROM categorized WHERE category IN ('adult', 'senior')");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->with != nullptr);
    REQUIRE(stmt->where != nullptr);

    std::string sql = Generator::generate(expr);
    REQUIRE(!sql.empty());
}

TEST_CASE("Complex - Set operation with window functions", "[advanced][complex]") {
    Arena arena;
    Parser parser(arena,
        "SELECT id, ROW_NUMBER() OVER (ORDER BY score) FROM users "
        "UNION "
        "SELECT id, ROW_NUMBER() OVER (ORDER BY score) FROM admins");

    auto expr = parser.parse_select();

    REQUIRE(expr->type == ExprType::UNION_STMT);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("UNION") != std::string::npos);
    REQUIRE(sql.find("ROW_NUMBER()") != std::string::npos);
}

// ============================================================================
// PIVOT/UNPIVOT - Advanced row-to-column transformations
// ============================================================================

TEST_CASE("PIVOT - Keyword lookup", "[pivot][keywords]") {
    // Test that PIVOT/UNPIVOT keywords are recognized
    auto pivot_token = KeywordLookup::lookup("PIVOT");
    auto unpivot_token = KeywordLookup::lookup("UNPIVOT");

    REQUIRE(pivot_token == TokenType::PIVOT);
    REQUIRE(unpivot_token == TokenType::UNPIVOT);
}

TEST_CASE("PIVOT - Simple PIVOT with one aggregate", "[pivot][basic]") {
    Arena arena;
    Parser parser(arena,
        "SELECT * FROM sales PIVOT (SUM(amount) FOR quarter IN ('Q1', 'Q2', 'Q3', 'Q4'))");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->from != nullptr);
    REQUIRE(stmt->from->type == ExprType::PIVOT_CLAUSE);

    auto* pivot = static_cast<PivotClause*>(stmt->from);
    REQUIRE(pivot->aggregate != nullptr);
    REQUIRE(pivot->pivot_column != nullptr);
    REQUIRE(pivot->pivot_values.size() == 4);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("PIVOT") != std::string::npos);
    REQUIRE(sql.find("SUM(amount)") != std::string::npos);
    REQUIRE(sql.find("FOR") != std::string::npos);
    REQUIRE(sql.find("IN") != std::string::npos);
}

TEST_CASE("PIVOT - PIVOT with COUNT aggregate", "[pivot][aggregate]") {
    Arena arena;
    Parser parser(arena,
        "SELECT * FROM orders PIVOT (COUNT(*) FOR status IN ('pending', 'shipped', 'delivered'))");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->from->type == ExprType::PIVOT_CLAUSE);
    auto* pivot = static_cast<PivotClause*>(stmt->from);
    REQUIRE(pivot->aggregate != nullptr);
    REQUIRE(pivot->pivot_values.size() == 3);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("PIVOT") != std::string::npos);
    REQUIRE(sql.find("COUNT(*)") != std::string::npos);
}

TEST_CASE("PIVOT - PIVOT with AVG aggregate", "[pivot][aggregate]") {
    Arena arena;
    Parser parser(arena,
        "SELECT * FROM scores PIVOT (AVG(score) FOR subject IN ('math', 'science', 'english'))");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->from->type == ExprType::PIVOT_CLAUSE);
    auto* pivot = static_cast<PivotClause*>(stmt->from);
    REQUIRE(pivot->aggregate != nullptr);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("PIVOT") != std::string::npos);
    REQUIRE(sql.find("AVG(score)") != std::string::npos);
}

TEST_CASE("PIVOT - PIVOT with alias", "[pivot][alias]") {
    Arena arena;
    Parser parser(arena,
        "SELECT * FROM sales PIVOT (SUM(amount) FOR quarter IN ('Q1', 'Q2')) AS quarterly_sales");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->from->type == ExprType::PIVOT_CLAUSE);
    auto* pivot = static_cast<PivotClause*>(stmt->from);
    REQUIRE(pivot->alias == "quarterly_sales");

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("AS quarterly_sales") != std::string::npos);
}

TEST_CASE("PIVOT - PIVOT with numeric values", "[pivot][numeric]") {
    Arena arena;
    Parser parser(arena,
        "SELECT * FROM data PIVOT (MAX(value) FOR month IN (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12))");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->from->type == ExprType::PIVOT_CLAUSE);
    auto* pivot = static_cast<PivotClause*>(stmt->from);
    REQUIRE(pivot->pivot_values.size() == 12);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("PIVOT") != std::string::npos);
    REQUIRE(sql.find("MAX(value)") != std::string::npos);
}

TEST_CASE("UNPIVOT - Simple UNPIVOT", "[unpivot][basic]") {
    Arena arena;
    Parser parser(arena,
        "SELECT * FROM quarterly_sales UNPIVOT (amount FOR quarter IN (Q1, Q2, Q3, Q4))");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt != nullptr);
    REQUIRE(stmt->from != nullptr);
    REQUIRE(stmt->from->type == ExprType::UNPIVOT_CLAUSE);

    auto* unpivot = static_cast<UnpivotClause*>(stmt->from);
    REQUIRE(unpivot->value_column == "amount");
    REQUIRE(unpivot->name_column == "quarter");
    REQUIRE(unpivot->unpivot_columns.size() == 4);
    REQUIRE(unpivot->unpivot_columns[0] == "Q1");
    REQUIRE(unpivot->unpivot_columns[1] == "Q2");
    REQUIRE(unpivot->unpivot_columns[2] == "Q3");
    REQUIRE(unpivot->unpivot_columns[3] == "Q4");

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("UNPIVOT") != std::string::npos);
    REQUIRE(sql.find("amount") != std::string::npos);
    REQUIRE(sql.find("FOR quarter") != std::string::npos);
    REQUIRE(sql.find("IN") != std::string::npos);
}

TEST_CASE("UNPIVOT - UNPIVOT with alias", "[unpivot][alias]") {
    Arena arena;
    Parser parser(arena,
        "SELECT * FROM quarterly_sales UNPIVOT (amount FOR quarter IN (Q1, Q2)) AS normalized");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->from->type == ExprType::UNPIVOT_CLAUSE);
    auto* unpivot = static_cast<UnpivotClause*>(stmt->from);
    REQUIRE(unpivot->alias == "normalized");

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("AS normalized") != std::string::npos);
}

TEST_CASE("UNPIVOT - UNPIVOT with many columns", "[unpivot][columns]") {
    Arena arena;
    Parser parser(arena,
        "SELECT * FROM monthly_data UNPIVOT (value FOR month IN (jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec))");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->from->type == ExprType::UNPIVOT_CLAUSE);
    auto* unpivot = static_cast<UnpivotClause*>(stmt->from);
    REQUIRE(unpivot->unpivot_columns.size() == 12);
    REQUIRE(unpivot->value_column == "value");
    REQUIRE(unpivot->name_column == "month");

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("UNPIVOT") != std::string::npos);
}

TEST_CASE("PIVOT - Round-trip parse and generate", "[pivot][roundtrip]") {
    Arena arena;
    const char* original_sql = "SELECT * FROM sales PIVOT (SUM(amount) FOR quarter IN ('Q1', 'Q2', 'Q3'))";
    Parser parser(arena, original_sql);

    auto expr = parser.parse_select();
    REQUIRE(expr != nullptr);

    std::string generated_sql = Generator::generate(expr);
    REQUIRE(!generated_sql.empty());

    // Parse the generated SQL again to verify it's valid
    Arena arena2;
    Parser parser2(arena2, generated_sql.c_str());
    auto expr2 = parser2.parse_select();
    REQUIRE(expr2 != nullptr);
    REQUIRE(expr2->type == expr->type);
}

TEST_CASE("UNPIVOT - Round-trip parse and generate", "[unpivot][roundtrip]") {
    Arena arena;
    const char* original_sql = "SELECT * FROM quarterly_sales UNPIVOT (amount FOR quarter IN (Q1, Q2, Q3, Q4))";
    Parser parser(arena, original_sql);

    auto expr = parser.parse_select();
    REQUIRE(expr != nullptr);

    std::string generated_sql = Generator::generate(expr);
    REQUIRE(!generated_sql.empty());

    // Parse the generated SQL again to verify it's valid
    Arena arena2;
    Parser parser2(arena2, generated_sql.c_str());
    auto expr2 = parser2.parse_select();
    REQUIRE(expr2 != nullptr);
    REQUIRE(expr2->type == expr->type);
}

TEST_CASE("PIVOT - Complex query with WHERE and GROUP BY", "[pivot][complex]") {
    Arena arena;
    Parser parser(arena,
        "SELECT region, * FROM sales PIVOT (SUM(amount) FOR quarter IN ('Q1', 'Q2', 'Q3', 'Q4')) WHERE year = 2024");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->from->type == ExprType::PIVOT_CLAUSE);
    REQUIRE(stmt->where != nullptr);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("PIVOT") != std::string::npos);
    REQUIRE(sql.find("WHERE") != std::string::npos);
}

TEST_CASE("PIVOT - Multiple IN values with expressions", "[pivot][expressions]") {
    Arena arena;
    Parser parser(arena,
        "SELECT * FROM data PIVOT (SUM(value) FOR category IN ('A', 'B', 'C', 'D', 'E'))");

    auto expr = parser.parse_select();
    auto stmt = static_cast<SelectStmt*>(expr);

    REQUIRE(stmt->from->type == ExprType::PIVOT_CLAUSE);
    auto* pivot = static_cast<PivotClause*>(stmt->from);
    REQUIRE(pivot->pivot_values.size() == 5);

    std::string sql = Generator::generate(expr);
    REQUIRE(sql.find("'A'") != std::string::npos);
    REQUIRE(sql.find("'E'") != std::string::npos);
}
