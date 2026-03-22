#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/transpiler.h>
#include <libsqlglot/parser.h>
#include <iostream>

using namespace libsqlglot;

TEST_CASE("Debug GRANT parsing", "[debug]") {
    Arena arena;
    std::string sql = "GRANT SELECT ON users TO alice";

    Parser parser(arena, sql);
    auto expr = parser.parse();

    REQUIRE(expr != nullptr);
    REQUIRE(expr->type == ExprType::GRANT_STMT);

    auto grant_stmt = static_cast<GrantStmt*>(expr);

    std::cout << "Number of privileges: " << grant_stmt->privileges.size() << std::endl;
    std::cout << "Object name: " << grant_stmt->object_name << std::endl;
    std::cout << "Number of grantees: " << grant_stmt->grantees.size() << std::endl;
    std::cout << "to_public: " << grant_stmt->to_public << std::endl;

    if (!grant_stmt->grantees.empty()) {
        std::cout << "First grantee: " << grant_stmt->grantees[0] << std::endl;
    }

    // Now try to generate
    std::string result = Transpiler::transpile(sql);
    std::cout << "Generated SQL: " << result << std::endl;

    REQUIRE(grant_stmt->grantees.size() == 1);
    REQUIRE(grant_stmt->grantees[0] == "alice");
}
