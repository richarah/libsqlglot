#pragma once

#include "fwd.h"
#include "tokens.h"
#include "tokenizer.h"
#include "expression.h"
#include "arena.h"
#include <vector>
#include <string_view>
#include <stdexcept>

namespace libsqlglot {

/// Parse error exception with precise location tracking
class ParseError : public std::runtime_error {
public:
    uint16_t line;
    uint16_t column;
    std::string context;

    explicit ParseError(const std::string& msg, uint16_t l = 0, uint16_t c = 0, const std::string& ctx = "")
        : std::runtime_error(format_message(msg, l, c, ctx))
        , line(l)
        , column(c)
        , context(ctx)
    {}

private:
    static std::string format_message(const std::string& msg, uint16_t line, uint16_t col, const std::string& ctx) {
        std::string formatted;
        if (line > 0) {
            formatted += "Line " + std::to_string(line);
            if (col > 0) {
                formatted += ", column " + std::to_string(col);
            }
            formatted += ": ";
        }
        formatted += msg;
        if (!ctx.empty()) {
            formatted += " (found: '" + ctx + "')";
        }
        return formatted;
    }
};

/// Recursive descent parser for SQL
class Parser {
public:
    static constexpr size_t kMaxRecursionDepth = 256;

    Parser(Arena& arena, std::string_view source)
        : arena_(arena)
        , source_(source)
        , recursion_depth_(0)
        , string_pool_()  // Initialize string pool first
    {
        Tokenizer tokenizer(source, &string_pool_);  // Pass pool to tokenizer
        tokens_ = tokenizer.tokenize_all();
        pos_ = 0;
    }

    /// Parse a SELECT statement (may return SetOperation for UNION/INTERSECT/EXCEPT)
    Expression* parse_select() {
        auto stmt = arena_.create<SelectStmt>();

        // WITH clause (CTEs)
        if (check(TokenType::WITH)) {
            stmt->with = parse_with_clause();
        }

        expect(TokenType::SELECT);

        // DISTINCT?
        if (match(TokenType::DISTINCT)) {
            stmt->distinct = true;
        }

        // SELECT columns
        stmt->columns = parse_select_list();

        // FROM clause
        if (match(TokenType::FROM)) {
            stmt->from = parse_from_clause();
        }

        // WHERE clause
        if (match(TokenType::WHERE)) {
            stmt->where = parse_expression();
        }

        // GROUP BY
        if (match(TokenType::GROUP)) {
            expect(TokenType::BY);
            stmt->group_by = parse_expression_list();
        }

        // HAVING
        if (match(TokenType::HAVING)) {
            stmt->having = parse_expression();
        }

        // QUALIFY clause (Snowflake, BigQuery)
        if (match(TokenType::QUALIFY)) {
            stmt->qualify = parse_expression();
        }

        // ORDER BY
        if (match(TokenType::ORDER)) {
            expect(TokenType::BY);
            stmt->order_by = parse_order_by_list();
        }

        // LIMIT
        if (match(TokenType::LIMIT)) {
            stmt->limit = parse_expression();
        }

        // OFFSET
        if (match(TokenType::OFFSET)) {
            stmt->offset = parse_expression();
        }

        // Set operations: UNION, INTERSECT, EXCEPT
        if (check(TokenType::UNION) || check(TokenType::INTERSECT) || check(TokenType::EXCEPT)) {
            return parse_set_operation(stmt);
        }

        return stmt;
    }

    /// Parse set operations (UNION, INTERSECT, EXCEPT)
    Expression* parse_set_operation(SelectStmt* left) {
        SetOperation::OpType op_type;
        bool all = false;

        if (match(TokenType::UNION)) {
            op_type = SetOperation::OpType::UNION;
            all = match(TokenType::ALL);
        } else if (match(TokenType::INTERSECT)) {
            op_type = SetOperation::OpType::INTERSECT;
            all = match(TokenType::ALL);
        } else if (match(TokenType::EXCEPT)) {
            op_type = SetOperation::OpType::EXCEPT;
            all = match(TokenType::ALL);
        } else {
            error("Expected UNION, INTERSECT, or EXCEPT for set operation");
        }

        // Parse right side (another SELECT - may be nested set operation)
        auto right_expr = parse_select();
        auto right = static_cast<SelectStmt*>(right_expr);  // Simplified - would need better type checking

        return arena_.create<SetOperation>(left, right, op_type, all);
    }

    /// Parse INSERT statement
    InsertStmt* parse_insert() {
        auto stmt = arena_.create<InsertStmt>();
        expect(TokenType::INSERT);
        expect(TokenType::INTO);

        // Table name
        stmt->table = static_cast<TableRef*>(parse_table_reference());

        // Optional column list: (col1, col2, ...)
        if (match(TokenType::LPAREN)) {
            do {
                if (current().type == TokenType::IDENTIFIER) {
                    stmt->columns.push_back(std::string(current().text));
                    advance();
                }
            } while (match(TokenType::COMMA));
            expect(TokenType::RPAREN);
        }

        // VALUES or SELECT
        if (check(TokenType::SELECT) || check(TokenType::WITH)) {
            stmt->select_stmt = static_cast<SelectStmt*>(parse_select());
        } else {
            expect(TokenType::VALUES);
            // Parse value rows: VALUES (val1, val2), (val3, val4), ...
            do {
                expect(TokenType::LPAREN);
                std::vector<Expression*> row;
                do {
                    row.push_back(parse_expression());
                } while (match(TokenType::COMMA));
                expect(TokenType::RPAREN);
                stmt->values.push_back(row);
            } while (match(TokenType::COMMA));
        }

        return stmt;
    }

    /// Parse UPDATE statement
    UpdateStmt* parse_update() {
        auto stmt = arena_.create<UpdateStmt>();
        expect(TokenType::UPDATE);

        stmt->table = static_cast<TableRef*>(parse_table_reference());

        // SET clause
        expect(TokenType::SET);
        do {
            if (current().type == TokenType::IDENTIFIER) {
                std::string column(current().text);
                advance();
                expect(TokenType::EQ);
                Expression* value = parse_expression();
                stmt->assignments.emplace_back(column, value);
            }
        } while (match(TokenType::COMMA));

        // FROM clause (PostgreSQL extension)
        if (match(TokenType::FROM)) {
            stmt->from = parse_from_clause();
        }

        // WHERE clause
        if (match(TokenType::WHERE)) {
            stmt->where = parse_expression();
        }

        return stmt;
    }

    /// Parse DELETE statement
    DeleteStmt* parse_delete() {
        auto stmt = arena_.create<DeleteStmt>();
        expect(TokenType::DELETE);
        expect(TokenType::FROM);

        stmt->table = static_cast<TableRef*>(parse_table_reference());

        // USING clause (PostgreSQL extension)
        if (match(TokenType::USING)) {
            stmt->using_clause = parse_from_clause();
        }

        // WHERE clause
        if (match(TokenType::WHERE)) {
            stmt->where = parse_expression();
        }

        return stmt;
    }

    /// Parse CREATE statement (dispatches to TABLE, VIEW, SCHEMA, DATABASE)
    Expression* parse_create_statement() {
        expect(TokenType::CREATE);

        if (match(TokenType::OR)) {
            expect(TokenType::REPLACE);
            if (check(TokenType::VIEW)) {
                return parse_create_view_impl(true);
            }
            error("CREATE OR REPLACE is only supported for VIEW (found after OR REPLACE)");
        }

        if (check(TokenType::TABLE)) {
            return parse_create_table();
        } else if (check(TokenType::VIEW)) {
            return parse_create_view_impl(false);
        } else if (check(TokenType::SCHEMA)) {
            return parse_create_schema();
        } else if (check(TokenType::DATABASE)) {
            return parse_create_database();
        }

        error_expected_after("TABLE, VIEW, SCHEMA, or DATABASE", "CREATE");
    }

    /// Parse CREATE TABLE statement
    CreateTableStmt* parse_create_table() {
        auto stmt = arena_.create<CreateTableStmt>();

        // Consume CREATE if not already consumed (for direct calls)
        if (check(TokenType::CREATE)) {
            advance();
        }

        expect(TokenType::TABLE);

        // IF NOT EXISTS
        if (match(TokenType::IF_KW)) {
            expect(TokenType::NOT);
            expect(TokenType::EXISTS);  // EXISTS in keywords.h, not EXISTS_KW
            stmt->if_not_exists = true;
        }

        // Table name (without alias - AS might be part of "AS SELECT")
        if (current().type != TokenType::IDENTIFIER) {
            error_expected_after("table name", "CREATE TABLE");
        }
        std::string table_name(current().text);
        advance();
        stmt->table = arena_.create<TableRef>(table_name);

        // CREATE TABLE AS SELECT
        if (match(TokenType::AS)) {
            stmt->as_select = static_cast<SelectStmt*>(parse_select());
            return stmt;
        }

        // Column definitions
        expect(TokenType::LPAREN);
        do {
            if (current().type == TokenType::IDENTIFIER) {
                ColumnDef col;
                col.name = std::string(current().text);
                advance();

                // Data type
                if (current().type == TokenType::IDENTIFIER) {
                    col.type = std::string(current().text);
                    advance();

                    // Type parameters: VARCHAR(255), DECIMAL(10,2), etc.
                    if (match(TokenType::LPAREN)) {
                        while (!check(TokenType::RPAREN) && !is_at_end()) {
                            advance();
                        }
                        expect(TokenType::RPAREN);
                    }
                }

                // Column constraints
                while (true) {
                    if (match(TokenType::NOT)) {
                        expect(TokenType::NULL_KW);
                        col.not_null = true;
                    } else if (match(TokenType::PRIMARY)) {
                        expect(TokenType::KEY);
                        col.primary_key = true;
                    } else if (match(TokenType::UNIQUE)) {
                        col.unique = true;
                    } else if (match(TokenType::DEFAULT)) {
                        col.default_value = parse_expression();
                    } else {
                        break;
                    }
                }

                stmt->columns.push_back(col);
            }
        } while (match(TokenType::COMMA));
        expect(TokenType::RPAREN);

        return stmt;
    }

    /// Parse CREATE VIEW statement
    CreateViewStmt* parse_create_view_impl(bool or_replace) {
        auto stmt = arena_.create<CreateViewStmt>();
        stmt->or_replace = or_replace;
        expect(TokenType::VIEW);

        // IF NOT EXISTS
        if (match(TokenType::IF_KW)) {
            expect(TokenType::NOT);
            expect(TokenType::EXISTS);
            stmt->if_not_exists = true;
        }

        // View name
        if (current().type != TokenType::IDENTIFIER) {
            error_expected_after("view name", "DROP VIEW");
        }
        stmt->name = std::string(current().text);
        advance();

        // Optional column list
        if (match(TokenType::LPAREN)) {
            do {
                if (current().type == TokenType::IDENTIFIER) {
                    stmt->columns.push_back(std::string(current().text));
                    advance();
                }
            } while (match(TokenType::COMMA));
            expect(TokenType::RPAREN);
        }

        // AS SELECT ...
        expect(TokenType::AS);
        stmt->query = static_cast<SelectStmt*>(parse_select());

        return stmt;
    }

    /// Parse CREATE SCHEMA statement
    CreateSchemaStmt* parse_create_schema() {
        auto stmt = arena_.create<CreateSchemaStmt>();
        expect(TokenType::SCHEMA);

        // IF NOT EXISTS
        if (match(TokenType::IF_KW)) {
            expect(TokenType::NOT);
            expect(TokenType::EXISTS);
            stmt->if_not_exists = true;
        }

        // Schema name
        if (current().type != TokenType::IDENTIFIER) {
            error_expected_after("schema name", "DROP SCHEMA");
        }
        stmt->name = std::string(current().text);
        advance();

        return stmt;
    }

    /// Parse CREATE DATABASE statement
    CreateDatabaseStmt* parse_create_database() {
        auto stmt = arena_.create<CreateDatabaseStmt>();
        expect(TokenType::DATABASE);

        // IF NOT EXISTS
        if (match(TokenType::IF_KW)) {
            expect(TokenType::NOT);
            expect(TokenType::EXISTS);
            stmt->if_not_exists = true;
        }

        // Database name
        if (current().type != TokenType::IDENTIFIER) {
            error_expected_after("database name", "CREATE DATABASE");
        }
        stmt->name = std::string(current().text);
        advance();

        return stmt;
    }

    /// Parse DROP statement (dispatches to TABLE, VIEW, SCHEMA, DATABASE)
    Expression* parse_drop_statement() {
        expect(TokenType::DROP);

        if (check(TokenType::TABLE)) {
            // Existing DROP TABLE would go here (not implemented yet)
            error("DROP TABLE statement is not yet implemented");
        } else if (check(TokenType::VIEW)) {
            return parse_drop_view();
        } else if (check(TokenType::SCHEMA)) {
            return parse_drop_schema();
        } else if (check(TokenType::DATABASE)) {
            return parse_drop_database();
        }

        error_expected_after("TABLE, VIEW, SCHEMA, or DATABASE", "DROP");
    }

    /// Parse DROP VIEW statement
    DropViewStmt* parse_drop_view() {
        auto stmt = arena_.create<DropViewStmt>();
        expect(TokenType::VIEW);

        // IF EXISTS
        if (match(TokenType::IF_KW)) {
            expect(TokenType::EXISTS);
            stmt->if_exists = true;
        }

        // View name
        if (current().type != TokenType::IDENTIFIER) {
            error_expected_after("view name", "DROP VIEW");
        }
        stmt->name = std::string(current().text);
        advance();

        // CASCADE/RESTRICT (simplified - just skip keywords that might appear)
        // These keywords are not in TokenType yet, so we check identifier
        if (current().type == TokenType::IDENTIFIER) {
            std::string kw(current().text);
            if (kw == "CASCADE" || kw == "RESTRICT") {
                advance();
            }
        }

        return stmt;
    }

    /// Parse DROP SCHEMA statement
    DropSchemaStmt* parse_drop_schema() {
        auto stmt = arena_.create<DropSchemaStmt>();
        expect(TokenType::SCHEMA);

        // IF EXISTS
        if (match(TokenType::IF_KW)) {
            expect(TokenType::EXISTS);
            stmt->if_exists = true;
        }

        // Schema name
        if (current().type != TokenType::IDENTIFIER) {
            error_expected_after("schema name", "DROP SCHEMA");
        }
        stmt->name = std::string(current().text);
        advance();

        return stmt;
    }

    /// Parse DROP DATABASE statement (same as DROP SCHEMA in most dialects)
    DropSchemaStmt* parse_drop_database() {
        auto stmt = arena_.create<DropSchemaStmt>();
        expect(TokenType::DATABASE);

        // IF EXISTS
        if (match(TokenType::IF_KW)) {
            expect(TokenType::EXISTS);
            stmt->if_exists = true;
        }

        // Database name
        if (current().type != TokenType::IDENTIFIER) {
            error_expected_after("database name", "DROP DATABASE");
        }
        stmt->name = std::string(current().text);
        advance();

        return stmt;
    }

    /// Parse TRUNCATE statement
    TruncateStmt* parse_truncate() {
        auto stmt = arena_.create<TruncateStmt>();
        expect(TokenType::TRUNCATE);
        match(TokenType::TABLE);  // TABLE is optional

        // Table name
        if (current().type != TokenType::IDENTIFIER) {
            error_expected_after("table name", "TRUNCATE");
        }
        stmt->table = std::string(current().text);
        advance();

        return stmt;
    }

    /// Parse MERGE statement
    MergeStmt* parse_merge() {
        auto stmt = arena_.create<MergeStmt>();
        expect(TokenType::MERGE);
        expect(TokenType::INTO);

        // Target table
        stmt->target = static_cast<TableRef*>(parse_table_reference());

        // USING clause
        expect(TokenType::USING);
        stmt->source = parse_table_reference();

        // ON condition
        expect(TokenType::ON);
        stmt->on_condition = parse_expression();

        // WHEN MATCHED / NOT MATCHED clauses (simplified)
        while (match(TokenType::WHEN)) {
            bool not_matched = match(TokenType::NOT);
            expect(TokenType::MATCHED);

            if (not_matched) {
                expect(TokenType::THEN);
                expect(TokenType::INSERT);
                // Simplified: would parse full INSERT clause here
            } else {
                expect(TokenType::THEN);
                if (match(TokenType::UPDATE)) {
                    expect(TokenType::SET);
                    // Simplified: would parse SET assignments here
                } else if (match(TokenType::DELETE)) {
                    // DELETE action
                }
            }
        }

        return stmt;
    }

    /// Parse BEGIN statement
    BeginStmt* parse_begin() {
        auto stmt = arena_.create<BeginStmt>();
        expect(TokenType::BEGIN);
        match(TokenType::TRANSACTION) || match(TokenType::WORK);  // Optional
        return stmt;
    }

    /// Parse COMMIT statement
    CommitStmt* parse_commit() {
        auto stmt = arena_.create<CommitStmt>();
        expect(TokenType::COMMIT);
        match(TokenType::TRANSACTION) || match(TokenType::WORK);  // Optional
        return stmt;
    }

    /// Parse ROLLBACK statement
    RollbackStmt* parse_rollback() {
        auto stmt = arena_.create<RollbackStmt>();
        expect(TokenType::ROLLBACK);
        match(TokenType::TRANSACTION) || match(TokenType::WORK);  // Optional

        // ROLLBACK TO SAVEPOINT name
        if (current().type == TokenType::IDENTIFIER && std::string(current().text) == "TO") {
            advance();  // consume TO
            expect(TokenType::SAVEPOINT);
            if (current().type == TokenType::IDENTIFIER) {
                stmt->savepoint_name = std::string(current().text);
                advance();
            }
        }

        return stmt;
    }

    /// Parse SAVEPOINT statement
    SavepointStmt* parse_savepoint() {
        auto stmt = arena_.create<SavepointStmt>();
        expect(TokenType::SAVEPOINT);

        if (current().type == TokenType::IDENTIFIER) {
            stmt->name = std::string(current().text);
            advance();
        }

        return stmt;
    }

    /// Parse SET statement
    SetStmt* parse_set_statement() {
        auto stmt = arena_.create<SetStmt>();
        expect(TokenType::SET);

        // Parse variable assignments
        do {
            if (current().type == TokenType::IDENTIFIER) {
                std::string var_name(current().text);
                advance();

                // = or TO
                if (!match(TokenType::EQ)) {
                    // Some dialects use TO instead of =
                    if (current().type == TokenType::IDENTIFIER &&
                        std::string(current().text) == "TO") {
                        advance();
                    }
                }

                Expression* value = parse_expression();
                stmt->assignments.emplace_back(var_name, value);
            }
        } while (match(TokenType::COMMA));

        return stmt;
    }

    /// Parse SHOW statement
    ShowStmt* parse_show() {
        auto stmt = arena_.create<ShowStmt>();
        expect(TokenType::SHOW);

        // What to show (TABLES, DATABASES, etc.)
        if (current().type == TokenType::IDENTIFIER) {
            stmt->what = std::string(current().text);
            advance();
        }

        return stmt;
    }

    /// Parse DESCRIBE statement
    DescribeStmt* parse_describe() {
        auto stmt = arena_.create<DescribeStmt>();
        match(TokenType::DESCRIBE) || match(TokenType::DESC_KW);

        // Table name
        if (current().type == TokenType::IDENTIFIER) {
            stmt->target = std::string(current().text);
            advance();
        }

        return stmt;
    }

    /// Parse EXPLAIN statement
    ExplainStmt* parse_explain() {
        auto stmt = arena_.create<ExplainStmt>();
        expect(TokenType::EXPLAIN);

        // Optional ANALYZE
        if (match(TokenType::ANALYZE)) {
            stmt->analyze = true;
        }

        // The statement being explained
        stmt->statement = parse();

        return stmt;
    }

    /// Parse VALUES clause (can be standalone or part of INSERT)
    ValuesClause* parse_values_clause() {
        auto stmt = arena_.create<ValuesClause>();
        expect(TokenType::VALUES);

        // Parse value rows: VALUES (val1, val2), (val3, val4), ...
        do {
            expect(TokenType::LPAREN);
            std::vector<Expression*> row;
            do {
                row.push_back(parse_expression());
            } while (match(TokenType::COMMA));
            expect(TokenType::RPAREN);
            stmt->rows.push_back(row);
        } while (match(TokenType::COMMA));

        return stmt;
    }

    /// Parse CALL statement: CALL proc_name(arg1, arg2, ...)
    CallProcedureStmt* parse_call() {
        auto stmt = arena_.create<CallProcedureStmt>();
        expect(TokenType::CALL);

        // Procedure name
        if (current().type != TokenType::IDENTIFIER) {
            error_expected_after("procedure name", "CALL");
        }
        stmt->name = std::string(current().text);
        advance();

        // Optional arguments: (arg1, arg2, ...)
        if (match(TokenType::LPAREN)) {
            if (!check(TokenType::RPAREN)) {
                do {
                    stmt->arguments.push_back(parse_expression());
                } while (match(TokenType::COMMA));
            }
            expect(TokenType::RPAREN);
        }

        return stmt;
    }

    /// Parse RETURN statement: RETURN expression
    ReturnStmt* parse_return() {
        expect(TokenType::RETURN_KW);  // RETURN_KW keyword from tokens.h

        // Optional return value
        Expression* return_value = nullptr;
        if (!check(TokenType::SEMICOLON) && !is_at_end()) {
            return_value = parse_expression();
        }

        return arena_.create<ReturnStmt>(return_value);
    }

    /// Parse DECLARE statement: DECLARE variable_name type [DEFAULT value]
    DeclareStmt* parse_declare() {
        expect(TokenType::DECLARE);

        // Variable name
        if (current().type != TokenType::IDENTIFIER) {
            error_expected_after("variable name", "DECLARE");
        }
        std::string var_name(current().text);
        advance();

        // Data type
        if (current().type != TokenType::IDENTIFIER) {
            error_expected_after("data type", "variable name in DECLARE");
        }
        std::string type_str(current().text);
        advance();

        // Type parameters: VARCHAR(255), DECIMAL(10,2), etc.
        if (match(TokenType::LPAREN)) {
            type_str += "(";
            while (!check(TokenType::RPAREN) && !is_at_end()) {
                if (current().text) {
                    type_str += std::string(current().text);
                } else if (current().type == TokenType::COMMA) {
                    type_str += ",";
                }
                advance();
            }
            expect(TokenType::RPAREN);
            type_str += ")";
        }

        // Optional DEFAULT value
        Expression* default_value = nullptr;
        if (match(TokenType::DEFAULT)) {
            default_value = parse_expression();
        }

        auto stmt = arena_.create<DeclareStmt>();
        stmt->variable_name = var_name;
        stmt->type = type_str;
        stmt->default_value = default_value;
        return stmt;
    }

    /// Parse IF statement: IF condition THEN statements [ELSEIF ...] [ELSE ...] END IF
    IfStmt* parse_if() {
        auto stmt = arena_.create<IfStmt>();
        expect(TokenType::IF_KW);

        // IF condition
        stmt->condition = parse_expression();
        expect(TokenType::THEN);

        // THEN statements (parse until ELSEIF, ELSE, END, or ENDIF)
        while (!check(TokenType::ELSEIF) && !check(TokenType::ELSE) &&
               !check(TokenType::END) && !check(TokenType::ENDIF) && !is_at_end()) {
            stmt->then_stmts.push_back(parse());
            match(TokenType::SEMICOLON);  // Optional semicolon
        }

        // ELSEIF branches
        while (match(TokenType::ELSEIF)) {
            IfStmt::ElseIfBranch branch;
            branch.condition = parse_expression();
            expect(TokenType::THEN);

            // ELSEIF body
            while (!check(TokenType::ELSEIF) && !check(TokenType::ELSE) &&
                   !check(TokenType::END) && !check(TokenType::ENDIF) && !is_at_end()) {
                branch.statements.push_back(parse());
                match(TokenType::SEMICOLON);  // Optional semicolon
            }
            stmt->elseif_branches.push_back(branch);
        }

        // ELSE clause
        if (match(TokenType::ELSE)) {
            while (!check(TokenType::END) && !check(TokenType::ENDIF) && !is_at_end()) {
                stmt->else_stmts.push_back(parse());
                match(TokenType::SEMICOLON);  // Optional semicolon
            }
        }

        // END IF or ENDIF
        if (match(TokenType::ENDIF)) {
            // Single token ENDIF
        } else {
            expect(TokenType::END);
            expect(TokenType::IF_KW);  // END IF (two tokens)
        }

        return stmt;
    }

    /// Parse WHILE loop: WHILE condition DO statements END WHILE
    WhileLoop* parse_while() {
        auto stmt = arena_.create<WhileLoop>();
        expect(TokenType::WHILE);

        // WHILE condition
        stmt->condition = parse_expression();
        expect(TokenType::DO);

        // Loop body (parse until END or ENDWHILE)
        while (!check(TokenType::END) && !check(TokenType::ENDWHILE) && !is_at_end()) {
            stmt->body.push_back(parse());
            match(TokenType::SEMICOLON);  // Optional semicolon
        }

        // END WHILE or ENDWHILE
        if (match(TokenType::ENDWHILE)) {
            // Single token ENDWHILE
        } else {
            expect(TokenType::END);
            expect(TokenType::WHILE);  // END WHILE (two tokens)
        }

        return stmt;
    }

    /// Parse FOR loop: FOR variable IN start..end LOOP statements END LOOP
    ForLoop* parse_for() {
        auto stmt = arena_.create<ForLoop>();
        expect(TokenType::FOR);

        // Variable name
        if (current().type != TokenType::IDENTIFIER) {
            error_expected_after("variable name", "FOR");
        }
        stmt->variable = std::string(current().text);
        advance();

        // IN keyword
        expect(TokenType::IN);

        // Start value
        stmt->start_value = parse_expression();

        // Range operator: ..
        expect(TokenType::DOUBLE_DOT);

        // End value
        stmt->end_value = parse_expression();

        // LOOP keyword
        expect(TokenType::LOOP);

        // Loop body (parse until END or ENDLOOP)
        while (!check(TokenType::END) && !check(TokenType::ENDLOOP) && !is_at_end()) {
            stmt->body.push_back(parse());
            match(TokenType::SEMICOLON);  // Optional semicolon
        }

        // END LOOP or ENDLOOP
        if (match(TokenType::ENDLOOP)) {
            // Single token ENDLOOP
        } else {
            expect(TokenType::END);
            expect(TokenType::LOOP);  // END LOOP (two tokens)
        }

        return stmt;
    }

    /// Parse CASE expression
    CaseExpr* parse_case_expression() {
        auto case_expr = arena_.create<CaseExpr>();

        // CASE value WHEN ... or CASE WHEN ...
        if (!check(TokenType::WHEN)) {
            case_expr->case_value = parse_expression();
        }

        // WHEN clauses
        while (match(TokenType::WHEN)) {
            auto when_expr = parse_expression();
            expect(TokenType::THEN);
            auto then_expr = parse_expression();
            case_expr->when_clauses.push_back({when_expr, then_expr});
        }

        // ELSE clause
        if (match(TokenType::ELSE)) {
            case_expr->else_expr = parse_expression();
        }

        expect(TokenType::END);
        return case_expr;
    }

    /// Parse WITH clause (CTEs)
    WithClause* parse_with_clause() {
        auto with = arena_.create<WithClause>();
        expect(TokenType::WITH);

        // RECURSIVE?
        if (match(TokenType::RECURSIVE)) {
            with->recursive = true;
        }

        // Parse CTEs
        do {
            auto cte = arena_.create<CTE>("", nullptr);

            if (current().type == TokenType::IDENTIFIER) {
                cte->name = std::string(current().text);
                advance();
            }

            // Optional column list
            if (match(TokenType::LPAREN)) {
                do {
                    if (current().type == TokenType::IDENTIFIER) {
                        cte->columns.push_back(std::string(current().text));
                        advance();
                    }
                } while (match(TokenType::COMMA));
                expect(TokenType::RPAREN);
            }

            expect(TokenType::AS);
            expect(TokenType::LPAREN);
            cte->query = static_cast<SelectStmt*>(parse_select());
            expect(TokenType::RPAREN);

            with->ctes.push_back(cte);
        } while (match(TokenType::COMMA));

        return with;
    }

    /// Parse window function
    WindowFunction* parse_window_function(std::string func_name, std::vector<Expression*> args) {
        expect(TokenType::OVER);
        expect(TokenType::LPAREN);

        auto window_spec = arena_.create<WindowSpec>();

        // PARTITION BY
        if (match(TokenType::PARTITION)) {
            expect(TokenType::BY);
            window_spec->partition_by = parse_expression_list();
        }

        // ORDER BY
        if (match(TokenType::ORDER)) {
            expect(TokenType::BY);
            window_spec->order_by = parse_order_by_list();
        }

        // Frame clause: ROWS/RANGE/GROUPS
        if (check(TokenType::ROWS) || check(TokenType::RANGE)) {
            window_spec->frame = parse_frame_clause();
        }

        expect(TokenType::RPAREN);

        auto window_func = arena_.create<WindowFunction>(func_name, window_spec);
        window_func->args = args;
        return window_func;
    }

    /// Parse window frame clause: ROWS/RANGE [BETWEEN] ...
    FrameClause* parse_frame_clause() {
        // Frame type: ROWS or RANGE or GROUPS
        FrameType frame_type;
        if (match(TokenType::ROWS)) {
            frame_type = FrameType::ROWS;
        } else if (match(TokenType::RANGE)) {
            frame_type = FrameType::RANGE;
        } else {
            error("Expected ROWS or RANGE for window frame");
        }

        // Check for BETWEEN syntax
        if (match(TokenType::BETWEEN)) {
            // BETWEEN start AND end
            auto [start_bound, start_offset] = parse_frame_bound();
            expect(TokenType::AND);
            auto [end_bound, end_offset] = parse_frame_bound();

            auto frame = arena_.create<FrameClause>(frame_type, start_bound);
            frame->start_offset = start_offset;
            frame->end_bound = end_bound;
            frame->end_offset = end_offset;
            return frame;
        } else {
            // Single boundary (implies BETWEEN start AND CURRENT ROW)
            auto [bound, offset] = parse_frame_bound();
            auto frame = arena_.create<FrameClause>(frame_type, bound);
            frame->start_offset = offset;
            return frame;
        }
    }

    /// Parse frame boundary: UNBOUNDED PRECEDING | N PRECEDING | CURRENT ROW | N FOLLOWING | UNBOUNDED FOLLOWING
    std::pair<FrameBound, Expression*> parse_frame_bound() {
        if (match(TokenType::UNBOUNDED)) {
            if (match(TokenType::PRECEDING)) {
                return {FrameBound::UNBOUNDED_PRECEDING, nullptr};
            } else if (match(TokenType::FOLLOWING)) {
                return {FrameBound::UNBOUNDED_FOLLOWING, nullptr};
            } else {
                error_expected_after("PRECEDING or FOLLOWING", "UNBOUNDED");
            }
        } else if (match(TokenType::CURRENT)) {
            expect(TokenType::ROW);
            return {FrameBound::CURRENT_ROW, nullptr};
        } else {
            // N PRECEDING or N FOLLOWING
            auto offset = parse_expression();
            if (match(TokenType::PRECEDING)) {
                return {FrameBound::PRECEDING, offset};
            } else if (match(TokenType::FOLLOWING)) {
                return {FrameBound::FOLLOWING, offset};
            } else {
                error_expected_after("PRECEDING or FOLLOWING", "frame offset");
            }
        }
    }

    /// Parse any statement (returns Expression* for polymorphism)
    Expression* parse() {
        if (check(TokenType::WITH) || check(TokenType::SELECT)) {
            return parse_select();
        } else if (check(TokenType::INSERT)) {
            return parse_insert();
        } else if (check(TokenType::UPDATE)) {
            return parse_update();
        } else if (check(TokenType::DELETE)) {
            return parse_delete();
        } else if (check(TokenType::CREATE)) {
            return parse_create_statement();
        } else if (check(TokenType::DROP)) {
            return parse_drop_statement();
        } else if (check(TokenType::TRUNCATE)) {
            return parse_truncate();
        } else if (check(TokenType::MERGE)) {
            return parse_merge();
        } else if (check(TokenType::BEGIN)) {
            return parse_begin();
        } else if (check(TokenType::COMMIT)) {
            return parse_commit();
        } else if (check(TokenType::ROLLBACK)) {
            return parse_rollback();
        } else if (check(TokenType::SAVEPOINT)) {
            return parse_savepoint();
        } else if (check(TokenType::SET)) {
            return parse_set_statement();
        } else if (check(TokenType::SHOW)) {
            return parse_show();
        } else if (check(TokenType::DESCRIBE) || check(TokenType::DESC_KW)) {
            return parse_describe();
        } else if (check(TokenType::EXPLAIN)) {
            return parse_explain();
        } else if (check(TokenType::VALUES)) {
            return parse_values_clause();
        } else if (check(TokenType::CALL)) {
            return parse_call();
        } else if (check(TokenType::RETURN_KW)) {
            return parse_return();
        } else if (check(TokenType::DECLARE)) {
            return parse_declare();
        } else if (check(TokenType::IF_KW)) {
            return parse_if();
        } else if (check(TokenType::WHILE)) {
            return parse_while();
        } else if (check(TokenType::FOR)) {
            return parse_for();
        }
        error("Unexpected token - expected SQL statement (SELECT, INSERT, UPDATE, DELETE, CREATE, etc.)");
    }

private:
    /// RAII guard for recursion depth tracking
    struct RecursionGuard {
        size_t& depth;
        Parser* parser;
        RecursionGuard(size_t& d, size_t max_depth, Parser* p) : depth(d), parser(p) {
            if (++depth > max_depth) {
                parser->error("Maximum recursion depth exceeded - query is too deeply nested (stack overflow protection)");
            }
        }
        ~RecursionGuard() { --depth; }
    };

    Arena& arena_;
    std::string_view source_;
    std::vector<Token> tokens_;
    size_t pos_;
    size_t recursion_depth_;
    LocalStringPool string_pool_;  // Owns interned strings for tokens

    // Token navigation
    const Token& current() const {
        if (pos_ >= tokens_.size()) return tokens_.back(); // EOF
        return tokens_[pos_];
    }

    const Token& peek(size_t offset = 1) const {
        size_t p = pos_ + offset;
        if (p >= tokens_.size()) return tokens_.back();
        return tokens_[p];
    }

    bool is_at_end() const {
        return current().type == TokenType::EOF_TOKEN;
    }

    bool check(TokenType type) const {
        return !is_at_end() && current().type == type;
    }

    bool match(TokenType type) {
        if (check(type)) {
            advance();
            return true;
        }
        return false;
    }

    void advance() {
        if (!is_at_end()) pos_++;
    }

    void expect(TokenType type) {
        if (!match(type)) {
            error_expected(std::string(token_type_name(type)));
        }
    }

    /// Throw parse error with current token location
    [[noreturn]] void error(const std::string& msg) {
        const Token& tok = current();
        std::string context = tok.text ? std::string(tok.text) : "";
        throw ParseError(msg, tok.line, tok.col, context);
    }

    /// Throw error for expected token
    [[noreturn]] void error_expected(const std::string& expected) {
        const Token& tok = current();
        std::string context = tok.text ? std::string(tok.text) : token_type_name(tok.type).data();
        std::string msg = "Expected " + expected;
        throw ParseError(msg, tok.line, tok.col, context);
    }

    /// Throw error for expected token with additional context
    [[noreturn]] void error_expected_after(const std::string& expected, const std::string& after) {
        const Token& tok = current();
        std::string context = tok.text ? std::string(tok.text) : "";
        std::string msg = "Expected " + expected + " after " + after;
        throw ParseError(msg, tok.line, tok.col, context);
    }

    // Expression parsing
    std::vector<Expression*> parse_select_list() {
        std::vector<Expression*> columns;

        // SELECT col1, col2, ... (or *, col1, col2, ...)
        do {
            // Check for * (can appear in list like SELECT *, col1, col2)
            if (match(TokenType::STAR)) {
                columns.push_back(arena_.create<Star>());
                continue;  // Skip to next iteration (check for comma)
            }

            auto expr = parse_expression();

            // AS alias?
            if (match(TokenType::AS)) {
                // Allow any token (including keywords) as alias
                if (!is_at_end() && current().text) {
                    std::string alias(current().text);
                    advance();
                    expr = arena_.create<Alias>(expr, alias);
                }
            }

            columns.push_back(expr);
        } while (match(TokenType::COMMA));

        return columns;
    }

    std::vector<Expression*> parse_expression_list() {
        std::vector<Expression*> exprs;

        do {
            exprs.push_back(parse_expression());
        } while (match(TokenType::COMMA));

        return exprs;
    }

    /// Parse ORDER BY clause (consumes ASC/DESC but doesn't store them yet)
    std::vector<Expression*> parse_order_by_list() {
        std::vector<Expression*> exprs;

        do {
            exprs.push_back(parse_expression());
            // Consume optional ASC/DESC (not stored in current implementation)
            match(TokenType::ASC) || match(TokenType::DESC);
        } while (match(TokenType::COMMA));

        return exprs;
    }

    Expression* parse_from_clause() {
        auto table = parse_table_reference();

        // JOIN?
        while (check(TokenType::JOIN) || check(TokenType::INNER) ||
               check(TokenType::LEFT) || check(TokenType::RIGHT) ||
               check(TokenType::FULL) || check(TokenType::CROSS)) {

            JoinClause::JoinType join_type = JoinClause::JoinType::INNER;

            if (match(TokenType::INNER)) {
                expect(TokenType::JOIN);
            } else if (match(TokenType::LEFT)) {
                join_type = JoinClause::JoinType::LEFT;
                expect(TokenType::JOIN);
            } else if (match(TokenType::RIGHT)) {
                join_type = JoinClause::JoinType::RIGHT;
                expect(TokenType::JOIN);
            } else if (match(TokenType::FULL)) {
                join_type = JoinClause::JoinType::FULL;
                expect(TokenType::JOIN);
            } else if (match(TokenType::CROSS)) {
                join_type = JoinClause::JoinType::CROSS;
                expect(TokenType::JOIN);
            } else {
                match(TokenType::JOIN);
            }

            auto right_table = parse_table_reference();

            Expression* condition = nullptr;
            if (match(TokenType::ON)) {
                condition = parse_expression();
            }

            table = arena_.create<JoinClause>(join_type, table, right_table, condition);
        }

        return table;
    }

    Expression* parse_table_reference() {
        Expression* table = nullptr;

        // Subquery: (SELECT ...) AS alias
        if (match(TokenType::LPAREN)) {
            if (check(TokenType::SELECT) || check(TokenType::WITH)) {
                auto select_expr = parse_select();
                auto select_stmt = static_cast<SelectStmt*>(select_expr);
                expect(TokenType::RPAREN);

                std::string alias;
                if (match(TokenType::AS)) {
                    // Allow any token (including keywords) as alias
                    if (!is_at_end() && current().text) {
                        alias = std::string(current().text);
                        advance();
                    }
                } else if (current().type == TokenType::IDENTIFIER) {
                    // Implicit alias (only identifiers, not keywords)
                    alias = std::string(current().text);
                    advance();
                }

                table = arena_.create<Subquery>(select_stmt, alias);
            } else {
                error_expected_after("SELECT subquery", "opening parenthesis");
            }
        } else {
            if (current().type != TokenType::IDENTIFIER) {
                error("Expected table name or (SELECT ...) subquery in FROM clause");
            }

            std::string table_name(current().text);
            advance();

            // Alias?
            std::string alias;
            if (match(TokenType::AS)) {
                // Allow any token (including keywords) as alias
                if (!is_at_end() && current().text) {
                    alias = std::string(current().text);
                    advance();
                }
            } else if (current().type == TokenType::IDENTIFIER &&
                       !check(TokenType::PIVOT) && !check(TokenType::UNPIVOT)) {
                // Implicit alias (only identifiers, not keywords, not PIVOT/UNPIVOT)
                alias = std::string(current().text);
                advance();
            }

            if (alias.empty()) {
                table = arena_.create<TableRef>(table_name);
            } else {
                table = arena_.create<TableRef>(table_name, alias);
            }
        }

        // Check for PIVOT/UNPIVOT after table
        if (check(TokenType::PIVOT)) {
            return parse_pivot_clause(table);
        } else if (check(TokenType::UNPIVOT)) {
            return parse_unpivot_clause(table);
        }

        return table;
    }

    /// Parse PIVOT clause: PIVOT (aggregate FOR column IN (value_list))
    PivotClause* parse_pivot_clause(Expression* table_expr) {
        auto pivot = arena_.create<PivotClause>();
        pivot->table_expr = table_expr;

        expect(TokenType::PIVOT);
        expect(TokenType::LPAREN);

        // Parse aggregate function: SUM(sales), COUNT(*), AVG(amount)
        pivot->aggregate = static_cast<FunctionCall*>(parse_expression());

        // FOR column (just an identifier, not a full expression to avoid consuming IN)
        expect(TokenType::FOR);
        if (current().type == TokenType::IDENTIFIER) {
            std::string col_name(current().text);
            advance();
            pivot->pivot_column = arena_.create<Column>(col_name);
        } else {
            error_expected_after("column name", "FOR in PIVOT");
        }

        // IN (value_list)
        expect(TokenType::IN);
        expect(TokenType::LPAREN);

        // Parse pivot values: ('Q1', 'Q2', 'Q3') or (Q1, Q2, Q3)
        do {
            pivot->pivot_values.push_back(parse_expression());
        } while (match(TokenType::COMMA));

        expect(TokenType::RPAREN);
        expect(TokenType::RPAREN);  // Close PIVOT clause

        // Optional alias
        if (match(TokenType::AS)) {
            if (current().type == TokenType::IDENTIFIER) {
                pivot->alias = std::string(current().text);
                advance();
            }
        } else if (current().type == TokenType::IDENTIFIER) {
            // Implicit alias
            pivot->alias = std::string(current().text);
            advance();
        }

        return pivot;
    }

    /// Parse UNPIVOT clause: UNPIVOT (value_column FOR name_column IN (column_list))
    UnpivotClause* parse_unpivot_clause(Expression* table_expr) {
        auto unpivot = arena_.create<UnpivotClause>();
        unpivot->table_expr = table_expr;

        expect(TokenType::UNPIVOT);
        expect(TokenType::LPAREN);

        // Value column name
        if (current().type == TokenType::IDENTIFIER) {
            unpivot->value_column = std::string(current().text);
            advance();
        } else {
            error_expected_after("value column name", "UNPIVOT");
        }

        // FOR name column
        if (match(TokenType::FOR)) {
            if (current().type == TokenType::IDENTIFIER) {
                unpivot->name_column = std::string(current().text);
                advance();
            } else {
                error_expected_after("name column", "FOR in UNPIVOT");
            }
        } else {
            error_expected_after("FOR keyword", "value column in UNPIVOT");
        }

        // IN (column_list)
        expect(TokenType::IN);
        expect(TokenType::LPAREN);

        // Parse column names to unpivot
        do {
            if (current().type == TokenType::IDENTIFIER) {
                unpivot->unpivot_columns.push_back(std::string(current().text));
                advance();
            }
        } while (match(TokenType::COMMA));

        expect(TokenType::RPAREN);
        expect(TokenType::RPAREN);  // Close UNPIVOT clause

        // Optional alias
        if (match(TokenType::AS)) {
            if (current().type == TokenType::IDENTIFIER) {
                unpivot->alias = std::string(current().text);
                advance();
            }
        } else if (current().type == TokenType::IDENTIFIER) {
            // Implicit alias
            unpivot->alias = std::string(current().text);
            advance();
        }

        return unpivot;
    }

    Expression* parse_expression() {
        RecursionGuard guard(recursion_depth_, kMaxRecursionDepth, this);
        return parse_or_expression();
    }

    Expression* parse_or_expression() {
        RecursionGuard guard(recursion_depth_, kMaxRecursionDepth, this);
        auto left = parse_and_expression();

        while (match(TokenType::OR)) {
            auto right = parse_and_expression();
            left = arena_.create<BinaryOp>(ExprType::OR, left, right);
        }

        return left;
    }

    Expression* parse_and_expression() {
        auto left = parse_not_expression();

        while (match(TokenType::AND)) {
            auto right = parse_not_expression();
            left = arena_.create<BinaryOp>(ExprType::AND, left, right);
        }

        return left;
    }

    Expression* parse_not_expression() {
        RecursionGuard guard(recursion_depth_, kMaxRecursionDepth, this);
        if (match(TokenType::NOT)) {
            auto operand = parse_not_expression();
            return arena_.create<UnaryOp>(ExprType::NOT, operand);
        }

        return parse_comparison_expression();
    }

    Expression* parse_comparison_expression() {
        auto left = parse_additive_expression();

        while (true) {
            ExprType op;

            if (match(TokenType::EQ)) {
                op = ExprType::EQ;
            } else if (match(TokenType::NEQ)) {
                op = ExprType::NEQ;
            } else if (match(TokenType::LT)) {
                op = ExprType::LT;
            } else if (match(TokenType::LTE)) {
                op = ExprType::LTE;
            } else if (match(TokenType::GT)) {
                op = ExprType::GT;
            } else if (match(TokenType::GTE)) {
                op = ExprType::GTE;
            } else if (match(TokenType::IS)) {
                if (match(TokenType::NOT)) {
                    expect(TokenType::NULL_KW);
                    return arena_.create<UnaryOp>(ExprType::IS_NOT_NULL, left);
                } else {
                    expect(TokenType::NULL_KW);
                    return arena_.create<UnaryOp>(ExprType::IS_NULL, left);
                }
            } else if (match(TokenType::BETWEEN)) {
                // BETWEEN low AND high
                auto low = parse_additive_expression();
                expect(TokenType::AND);
                auto high = parse_additive_expression();
                return arena_.create<BetweenExpr>(left, low, high);
            } else if (match(TokenType::IN)) {
                // IN (list) or IN (subquery)
                expect(TokenType::LPAREN);
                std::vector<Expression*> values;

                if (check(TokenType::SELECT) || check(TokenType::WITH)) {
                    // Subquery
                    auto subquery = static_cast<SelectStmt*>(parse_select());
                    expect(TokenType::RPAREN);
                    return arena_.create<InExpr>(left, std::vector<Expression*>{subquery});
                }

                // Value list
                do {
                    values.push_back(parse_expression());
                } while (match(TokenType::COMMA));
                expect(TokenType::RPAREN);
                return arena_.create<InExpr>(left, values);
            } else if (match(TokenType::NOT)) {
                // NOT LIKE, NOT ILIKE, NOT BETWEEN, NOT IN
                if (match(TokenType::LIKE)) {
                    op = ExprType::NOT_LIKE;
                } else if (match(TokenType::ILIKE)) {
                    op = ExprType::NOT_ILIKE;
                } else if (match(TokenType::BETWEEN)) {
                    auto low = parse_additive_expression();
                    expect(TokenType::AND);
                    auto high = parse_additive_expression();
                    auto between = arena_.create<BetweenExpr>(left, low, high);
                    return arena_.create<UnaryOp>(ExprType::NOT, between);
                } else if (match(TokenType::IN)) {
                    expect(TokenType::LPAREN);
                    std::vector<Expression*> values;
                    if (check(TokenType::SELECT) || check(TokenType::WITH)) {
                        auto subquery = static_cast<SelectStmt*>(parse_select());
                        expect(TokenType::RPAREN);
                        auto in_expr = arena_.create<InExpr>(left, std::vector<Expression*>{subquery});
                        return arena_.create<UnaryOp>(ExprType::NOT, in_expr);
                    }
                    do {
                        values.push_back(parse_expression());
                    } while (match(TokenType::COMMA));
                    expect(TokenType::RPAREN);
                    auto in_expr = arena_.create<InExpr>(left, values);
                    return arena_.create<UnaryOp>(ExprType::NOT, in_expr);
                } else {
                    // Put back NOT token
                    pos_--;
                    break;
                }
            } else if (match(TokenType::LIKE)) {
                op = ExprType::LIKE;
            } else if (match(TokenType::ILIKE)) {
                op = ExprType::ILIKE;
            } else if (match(TokenType::REGEXP) || match(TokenType::RLIKE)) {
                // REGEXP/RLIKE pattern
                auto pattern = parse_additive_expression();
                return arena_.create<RegexMatch>(left, pattern, false);
            } else if (match(TokenType::SIMILAR)) {
                // SIMILAR TO pattern (SQL standard)
                // TO is not a token, check as identifier
                if (current().type == TokenType::IDENTIFIER && std::string(current().text) == "TO") {
                    advance();
                }
                auto pattern = parse_additive_expression();
                return arena_.create<RegexMatch>(left, pattern, true);
            } else {
                break;
            }

            auto right = parse_additive_expression();
            left = arena_.create<BinaryOp>(op, left, right);
        }

        return left;
    }

    Expression* parse_additive_expression() {
        auto left = parse_multiplicative_expression();

        while (true) {
            ExprType op;

            if (match(TokenType::PLUS)) {
                op = ExprType::PLUS;
            } else if (match(TokenType::MINUS)) {
                op = ExprType::MINUS;
            } else if (match(TokenType::CONCAT)) {
                op = ExprType::CONCAT;
            } else {
                break;
            }

            auto right = parse_multiplicative_expression();
            left = arena_.create<BinaryOp>(op, left, right);
        }

        return left;
    }

    Expression* parse_multiplicative_expression() {
        auto left = parse_unary_expression();

        while (true) {
            ExprType op;

            if (match(TokenType::STAR)) {
                op = ExprType::MUL;
            } else if (match(TokenType::SLASH)) {
                op = ExprType::DIV;
            } else if (match(TokenType::PERCENT)) {
                op = ExprType::MOD;
            } else {
                break;
            }

            auto right = parse_unary_expression();
            left = arena_.create<BinaryOp>(op, left, right);
        }

        return left;
    }

    Expression* parse_unary_expression() {
        RecursionGuard guard(recursion_depth_, kMaxRecursionDepth, this);
        if (match(TokenType::MINUS)) {
            auto operand = parse_unary_expression();
            auto zero = arena_.create<Literal>("0");
            return arena_.create<BinaryOp>(ExprType::MINUS, zero, operand);
        }

        if (match(TokenType::PLUS)) {
            return parse_unary_expression();
        }

        return parse_primary_expression();
    }

    Expression* parse_primary_expression() {
        // CASE expression
        if (match(TokenType::CASE)) {
            return parse_case_expression();
        }

        // EXISTS (subquery)
        if (match(TokenType::EXISTS)) {
            expect(TokenType::LPAREN);
            auto subquery = static_cast<SelectStmt*>(parse_select());
            expect(TokenType::RPAREN);
            return arena_.create<ExistsExpr>(subquery);
        }

        // Array literal: ARRAY[1, 2, 3] or [1, 2, 3]
        if (match(TokenType::ARRAY)) {
            expect(TokenType::LBRACKET);
            std::vector<Expression*> elements;
            if (!check(TokenType::RBRACKET)) {
                do {
                    elements.push_back(parse_expression());
                } while (match(TokenType::COMMA));
            }
            expect(TokenType::RBRACKET);
            return arena_.create<ArrayLiteral>(elements);
        }

        // Bracket array literal: [1, 2, 3] (BigQuery, DuckDB)
        if (match(TokenType::LBRACKET)) {
            std::vector<Expression*> elements;
            if (!check(TokenType::RBRACKET)) {
                do {
                    elements.push_back(parse_expression());
                } while (match(TokenType::COMMA));
            }
            expect(TokenType::RBRACKET);
            return arena_.create<ArrayLiteral>(elements);
        }

        // Parenthesized expression or subquery
        if (match(TokenType::LPAREN)) {
            // Check if it's a subquery
            if (check(TokenType::SELECT) || check(TokenType::WITH)) {
                auto subquery = static_cast<SelectStmt*>(parse_select());
                expect(TokenType::RPAREN);
                return arena_.create<Subquery>(subquery, "");
            }
            auto expr = parse_expression();
            expect(TokenType::RPAREN);
            return expr;
        }

        // NULL
        if (match(TokenType::NULL_KW)) {
            return arena_.create<Literal>("NULL");
        }

        // TRUE/FALSE
        if (match(TokenType::TRUE)) {
            return arena_.create<Literal>("TRUE");
        }
        if (match(TokenType::FALSE)) {
            return arena_.create<Literal>("FALSE");
        }

        // Number
        if (current().type == TokenType::NUMBER) {
            auto lit = arena_.create<Literal>(std::string(current().text));
            advance();
            return lit;
        }

        // String
        if (current().type == TokenType::STRING) {
            auto lit = arena_.create<Literal>(std::string(current().text));
            advance();
            return lit;
        }

        // Special keyword functions
        if (match(TokenType::COALESCE)) {
            expect(TokenType::LPAREN);
            std::vector<Expression*> args;
            do {
                args.push_back(parse_expression());
            } while (match(TokenType::COMMA));
            expect(TokenType::RPAREN);
            auto func = arena_.create<FunctionCall>("COALESCE", args);
            func->type = ExprType::COALESCE;
            return func;
        }

        if (match(TokenType::NULLIF)) {
            expect(TokenType::LPAREN);
            auto arg1 = parse_expression();
            expect(TokenType::COMMA);
            auto arg2 = parse_expression();
            expect(TokenType::RPAREN);
            auto func = arena_.create<FunctionCall>("NULLIF", std::vector<Expression*>{arg1, arg2});
            func->type = ExprType::NULLIF;
            return func;
        }

        if (match(TokenType::CAST)) {
            expect(TokenType::LPAREN);
            auto expr = parse_expression();
            expect(TokenType::AS);
            // Parse type - track paren depth for types like VARCHAR(100)
            std::string type_str;
            int paren_depth = 0;
            while ((!check(TokenType::RPAREN) || paren_depth > 0) && !is_at_end()) {
                if (current().type == TokenType::LPAREN) {
                    paren_depth++;
                } else if (current().type == TokenType::RPAREN) {
                    paren_depth--;
                }
                if (current().text) {
                    type_str += std::string(current().text);
                    // Add space except before closing paren
                    if (current().type != TokenType::RPAREN) {
                        type_str += " ";
                    }
                }
                advance();
            }
            expect(TokenType::RPAREN);
            auto func = arena_.create<FunctionCall>("CAST", std::vector<Expression*>{expr});
            return func;
        }

        if (match(TokenType::EXTRACT)) {
            expect(TokenType::LPAREN);
            // Parse field name (YEAR, MONTH, DAY, etc.)
            if (current().type != TokenType::IDENTIFIER) {
                error_expected_after("date/time field name (YEAR, MONTH, DAY, etc.)", "EXTRACT(");
            }
            std::string field(current().text);
            advance();
            // Expect FROM keyword
            expect(TokenType::FROM);
            // Parse the expression to extract from
            auto expr = parse_expression();
            expect(TokenType::RPAREN);
            // Return as a function call with field as first argument (as literal)
            auto field_lit = arena_.create<Literal>(field);
            return arena_.create<FunctionCall>("EXTRACT", std::vector<Expression*>{field_lit, expr});
        }

        // Type keyword functions (DATE, TIME, TIMESTAMP can be functions)
        if (match(TokenType::DATE) || match(TokenType::TIME) || match(TokenType::TIMESTAMP)) {
            std::string name(tokens_[pos_ - 1].text);  // Get text of just-consumed token

            // Must be followed by LPAREN to be a function
            if (match(TokenType::LPAREN)) {
                std::vector<Expression*> args;
                if (!check(TokenType::RPAREN)) {
                    do {
                        args.push_back(parse_expression());
                    } while (match(TokenType::COMMA));
                }
                expect(TokenType::RPAREN);
                return arena_.create<FunctionCall>(name, args);
            } else {
                // Not a function - error
                error("DATE/TIME/TIMESTAMP keyword must be followed by ( for function call");
            }
        }

        // Function call or column
        if (current().type == TokenType::IDENTIFIER) {
            std::string name(current().text);
            advance();

            // Function call: func(...)
            if (match(TokenType::LPAREN)) {
                std::vector<Expression*> args;

                // Check for DISTINCT in aggregates: COUNT(DISTINCT col)
                // (consume but don't store for now)
                match(TokenType::DISTINCT);

                // Special handling for COUNT(*), SUM(*), etc.
                if (match(TokenType::STAR)) {
                    args.push_back(arena_.create<Star>());
                } else if (!check(TokenType::RPAREN)) {
                    do {
                        args.push_back(parse_expression());
                    } while (match(TokenType::COMMA));
                }

                expect(TokenType::RPAREN);

                // Window function: func(...) OVER (...)
                if (check(TokenType::OVER)) {
                    return parse_window_function(name, args);
                }

                // Check if it's an aggregate function
                auto func = arena_.create<FunctionCall>(name, args);

                // Convert to aggregate type if recognized
                std::string upper_name = name;
                for (char& c : upper_name) {
                    if (c >= 'a' && c <= 'z') c = c - 32;
                }

                if (upper_name == "COUNT") func->type = ExprType::AGG_COUNT;
                else if (upper_name == "SUM") func->type = ExprType::AGG_SUM;
                else if (upper_name == "AVG") func->type = ExprType::AGG_AVG;
                else if (upper_name == "MIN") func->type = ExprType::AGG_MIN;
                else if (upper_name == "MAX") func->type = ExprType::AGG_MAX;

                // Check for array index or JSON operators after function
                Expression* result = func;
                while (true) {
                    if (match(TokenType::LBRACKET)) {
                        auto index = parse_expression();
                        expect(TokenType::RBRACKET);
                        result = arena_.create<ArrayIndex>(result, index);
                    } else if (match(TokenType::ARROW)) {
                        // -> JSON operator
                        auto key = parse_expression();
                        result = arena_.create<JsonExpr>(result, key, JsonExpr::OpType::ARROW);
                    } else if (match(TokenType::LONG_ARROW)) {
                        // ->> JSON operator
                        auto key = parse_expression();
                        result = arena_.create<JsonExpr>(result, key, JsonExpr::OpType::LONG_ARROW);
                    } else {
                        break;
                    }
                }

                return result;
            }

            // table.column?
            if (match(TokenType::DOT)) {
                if (current().type == TokenType::IDENTIFIER) {
                    std::string column(current().text);
                    advance();

                    // Check for array index or JSON operators on column
                    Expression* result = arena_.create<Column>(name, column);
                    while (true) {
                        if (match(TokenType::LBRACKET)) {
                            auto index = parse_expression();
                            expect(TokenType::RBRACKET);
                            result = arena_.create<ArrayIndex>(result, index);
                        } else if (match(TokenType::ARROW)) {
                            auto key = parse_expression();
                            result = arena_.create<JsonExpr>(result, key, JsonExpr::OpType::ARROW);
                        } else if (match(TokenType::LONG_ARROW)) {
                            auto key = parse_expression();
                            result = arena_.create<JsonExpr>(result, key, JsonExpr::OpType::LONG_ARROW);
                        } else {
                            break;
                        }
                    }
                    return result;
                } else if (match(TokenType::STAR)) {
                    return arena_.create<Star>(name);
                }
            }

            // Array index or JSON operators on simple column
            Expression* result = arena_.create<Column>(name);
            while (true) {
                if (match(TokenType::LBRACKET)) {
                    auto index = parse_expression();
                    expect(TokenType::RBRACKET);
                    result = arena_.create<ArrayIndex>(result, index);
                } else if (match(TokenType::ARROW)) {
                    auto key = parse_expression();
                    result = arena_.create<JsonExpr>(result, key, JsonExpr::OpType::ARROW);
                } else if (match(TokenType::LONG_ARROW)) {
                    auto key = parse_expression();
                    result = arena_.create<JsonExpr>(result, key, JsonExpr::OpType::LONG_ARROW);
                } else {
                    break;
                }
            }

            return result;
        }

        // If we get here, unhandled token
        error("Unexpected token in expression - expected literal, identifier, function, or subquery");
    }
    // Note: is_keyword() is provided by tokens.h
};

} // namespace libsqlglot
