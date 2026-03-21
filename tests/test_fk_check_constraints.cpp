#include <catch2/catch_test_macros.hpp>
#include <libsqlglot/transpiler.h>

using namespace libsqlglot;

TEST_CASE("Column-level FOREIGN KEY constraints", "[fk][ddl]") {
    SECTION("Simple FK with table reference") {
        std::string sql = "CREATE TABLE orders (customer_id INT REFERENCES customers)";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        REQUIRE(expr->type == ExprType::CREATE_TABLE_STMT);

        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns.size() == 1);
        REQUIRE(stmt->columns[0].name == "customer_id");
        REQUIRE(stmt->columns[0].fk_constraint != nullptr);
        REQUIRE(stmt->columns[0].fk_constraint->ref_table == "customers");
    }

    SECTION("FK with explicit column reference") {
        std::string sql = "CREATE TABLE orders (customer_id INT REFERENCES customers(id))";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns[0].fk_constraint != nullptr);
        REQUIRE(stmt->columns[0].fk_constraint->ref_table == "customers");
        REQUIRE(stmt->columns[0].fk_constraint->ref_column == "id");
    }

    SECTION("FK with ON DELETE CASCADE") {
        std::string sql = "CREATE TABLE orders (customer_id INT REFERENCES customers(id) ON DELETE CASCADE)";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns[0].fk_constraint != nullptr);
        REQUIRE(stmt->columns[0].fk_constraint->on_delete_action == "CASCADE");
    }

    SECTION("FK with ON UPDATE SET NULL") {
        std::string sql = "CREATE TABLE orders (customer_id INT REFERENCES customers(id) ON UPDATE SET NULL)";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns[0].fk_constraint != nullptr);
        REQUIRE(stmt->columns[0].fk_constraint->on_update_action == "SET NULL");
    }

    SECTION("FK with both ON DELETE and ON UPDATE") {
        std::string sql = "CREATE TABLE orders (customer_id INT REFERENCES customers(id) ON DELETE CASCADE ON UPDATE RESTRICT)";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns[0].fk_constraint != nullptr);
        REQUIRE(stmt->columns[0].fk_constraint->on_delete_action == "CASCADE");
        REQUIRE(stmt->columns[0].fk_constraint->on_update_action == "RESTRICT");
    }

    SECTION("FK with NO ACTION") {
        std::string sql = "CREATE TABLE orders (customer_id INT REFERENCES customers(id) ON DELETE NO ACTION)";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns[0].fk_constraint != nullptr);
        REQUIRE(stmt->columns[0].fk_constraint->on_delete_action == "NO ACTION");
    }
}

TEST_CASE("Table-level FOREIGN KEY constraints", "[fk][ddl]") {
    SECTION("Single column FK") {
        std::string sql = "CREATE TABLE orders (order_id INT, customer_id INT, FOREIGN KEY (customer_id) REFERENCES customers(id))";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        REQUIRE(expr->type == ExprType::CREATE_TABLE_STMT);

        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns.size() == 2);
        REQUIRE(stmt->foreign_keys.size() == 1);
        REQUIRE(stmt->foreign_keys[0].first.size() == 1);
        REQUIRE(stmt->foreign_keys[0].first[0] == "customer_id");
        REQUIRE(stmt->foreign_keys[0].second->table == "customers");
    }

    SECTION("Composite FK") {
        std::string sql = "CREATE TABLE order_items (order_id INT, item_id INT, FOREIGN KEY (order_id, item_id) REFERENCES orders(id, item))";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->foreign_keys.size() == 1);
        REQUIRE(stmt->foreign_keys[0].first.size() == 2);
        REQUIRE(stmt->foreign_keys[0].first[0] == "order_id");
        REQUIRE(stmt->foreign_keys[0].first[1] == "item_id");
    }
}

TEST_CASE("Column-level CHECK constraints", "[check][ddl]") {
    SECTION("Simple CHECK constraint") {
        std::string sql = "CREATE TABLE products (price DECIMAL CHECK (price > 0))";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        REQUIRE(expr->type == ExprType::CREATE_TABLE_STMT);

        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns.size() == 1);
        REQUIRE(stmt->columns[0].name == "price");
        REQUIRE(stmt->columns[0].check_constraint == "price > 0");
    }

    SECTION("CHECK with complex expression") {
        std::string sql = "CREATE TABLE employees (salary INT CHECK (salary >= 0 AND salary <= 1000000))";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns[0].check_constraint == "salary >= 0 AND salary <= 1000000");
    }
}

TEST_CASE("Table-level PRIMARY KEY constraints", "[pk][ddl]") {
    SECTION("Single column PK") {
        std::string sql = "CREATE TABLE users (id INT, name VARCHAR, PRIMARY KEY (id))";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns.size() == 2);
        REQUIRE(stmt->primary_keys.size() == 1);
        REQUIRE(stmt->primary_keys[0] == "id");
    }

    SECTION("Composite PK") {
        std::string sql = "CREATE TABLE order_items (order_id INT, item_id INT, PRIMARY KEY (order_id, item_id))";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->primary_keys.size() == 2);
        REQUIRE(stmt->primary_keys[0] == "order_id");
        REQUIRE(stmt->primary_keys[1] == "item_id");
    }
}

TEST_CASE("Combined constraints", "[constraints][ddl]") {
    SECTION("Column with multiple constraints") {
        std::string sql = "CREATE TABLE products (id INT PRIMARY KEY, price DECIMAL NOT NULL CHECK (price > 0))";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns.size() == 2);
        REQUIRE(stmt->columns[0].primary_key == true);
        REQUIRE(stmt->columns[1].not_null == true);
        REQUIRE(stmt->columns[1].check_constraint == "price > 0");
    }

    SECTION("Table with mixed column and table constraints") {
        std::string sql = R"(
            CREATE TABLE orders (
                id INT PRIMARY KEY,
                customer_id INT NOT NULL REFERENCES customers(id),
                total DECIMAL CHECK (total >= 0),
                FOREIGN KEY (customer_id) REFERENCES customers(id)
            )
        )";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns.size() == 3);
        REQUIRE(stmt->columns[0].primary_key == true);
        REQUIRE(stmt->columns[1].not_null == true);
        REQUIRE(stmt->columns[1].fk_constraint != nullptr);
        REQUIRE(stmt->columns[2].check_constraint == "total >= 0");
        REQUIRE(stmt->foreign_keys.size() == 1);
    }
}

TEST_CASE("UNIQUE constraints", "[unique][ddl]") {
    SECTION("Column-level UNIQUE") {
        std::string sql = "CREATE TABLE users (email VARCHAR UNIQUE)";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns[0].unique == true);
    }

    SECTION("Table-level UNIQUE") {
        std::string sql = "CREATE TABLE users (first_name VARCHAR, last_name VARCHAR, UNIQUE (first_name, last_name))";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        // Table-level UNIQUE is parsed but not stored yet (TODO item)
        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns.size() == 2);
    }
}

TEST_CASE("Real-world DDL examples", "[constraints][integration]") {
    SECTION("E-commerce database schema") {
        std::string sql = R"(
            CREATE TABLE customers (
                id INT PRIMARY KEY,
                email VARCHAR UNIQUE NOT NULL,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            )
        )";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns.size() == 3);
        REQUIRE(stmt->columns[0].primary_key == true);
        REQUIRE(stmt->columns[1].unique == true);
        REQUIRE(stmt->columns[1].not_null == true);
    }

    SECTION("Order system with FK") {
        std::string sql = R"(
            CREATE TABLE orders (
                id INT PRIMARY KEY,
                customer_id INT NOT NULL REFERENCES customers(id) ON DELETE CASCADE,
                total DECIMAL CHECK (total > 0),
                status VARCHAR CHECK (status IN ('pending', 'shipped', 'delivered'))
            )
        )";
        Arena arena;
        Parser parser(arena, sql);
        auto expr = parser.parse();

        REQUIRE(expr != nullptr);
        auto* stmt = static_cast<CreateTableStmt*>(expr);
        REQUIRE(stmt->columns.size() == 4);
        REQUIRE(stmt->columns[1].fk_constraint != nullptr);
        REQUIRE(stmt->columns[1].fk_constraint->on_delete_action == "CASCADE");
    }
}
