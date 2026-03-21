#pragma once

#include "expression.h"
#include "dialects.h"
#include <sstream>
#include <string>

namespace libsqlglot {

/// SQL generator - converts AST back to SQL text with dialect support
class Generator {
public:
    struct Options {
        bool pretty;                  ///< Enable pretty-printing with indentation
        int indent_width;             ///< Number of spaces per indent level
        bool trailing_comma;          ///< Put commas at end of lines (default: true)

        Options() : pretty(false), indent_width(2), trailing_comma(false) {}
    };

    /// Generate SQL from expression tree (default: ANSI SQL)
    static std::string generate(Expression* expr, Dialect dialect = Dialect::ANSI) {
        Generator gen(dialect);
        gen.visit(expr);
        return gen.sql_.str();
    }

    /// Generate SQL with options (pretty-printing, etc.)
    static std::string generate(Expression* expr, Dialect dialect, const Options& opts) {
        Generator gen(dialect, opts);
        gen.visit(expr);
        return gen.sql_.str();
    }

private:
    std::ostringstream sql_;
    Dialect dialect_;
    const DialectFeatures& features_;
    Options options_;
    int indent_level_ = 0;

    explicit Generator(Dialect d = Dialect::ANSI, const Options& opts = Options{})
        : dialect_(d), features_(DialectConfig::get_features(d)), options_(opts) {}

    /// Write text to output
    void write(const std::string& text) {
        sql_ << text;
    }

    /// Write newline and indent if pretty-printing
    void newline() {
        if (options_.pretty) {
            sql_ << "\n" << std::string(indent_level_ * options_.indent_width, ' ');
        }
    }

    /// Increase indent level
    void indent() {
        if (options_.pretty) {
            indent_level_++;
        }
    }

    /// Decrease indent level
    void dedent() {
        if (options_.pretty && indent_level_ > 0) {
            indent_level_--;
        }
    }

    /// Write space or newline based on pretty mode
    void space_or_newline() {
        if (options_.pretty) {
            newline();
        } else {
            write(" ");
        }
    }

    void visit(Expression* expr) {
        if (!expr) return;

        switch (expr->type) {
            case ExprType::LITERAL:
                visit_literal(static_cast<const Literal*>(expr));
                break;
            case ExprType::COLUMN:
                visit_column(static_cast<const Column*>(expr));
                break;
            case ExprType::STAR:
                visit_star(static_cast<const Star*>(expr));
                break;
            case ExprType::EQ:
            case ExprType::NEQ:
            case ExprType::LT:
            case ExprType::LTE:
            case ExprType::GT:
            case ExprType::GTE:
            case ExprType::LIKE:
            case ExprType::ILIKE:
            case ExprType::NOT_LIKE:
            case ExprType::NOT_ILIKE:
            case ExprType::PLUS:
            case ExprType::MINUS:
            case ExprType::MUL:
            case ExprType::DIV:
            case ExprType::MOD:
            case ExprType::AND:
            case ExprType::OR:
            case ExprType::CONCAT:
                visit_binary_op(static_cast<const BinaryOp*>(expr));
                break;
            case ExprType::NOT:
            case ExprType::IS_NULL:
            case ExprType::IS_NOT_NULL:
                visit_unary_op(static_cast<const UnaryOp*>(expr));
                break;
            case ExprType::FUNCTION_CALL:
                visit_function_call(static_cast<const FunctionCall*>(expr));
                break;
            case ExprType::AGG_COUNT:
            case ExprType::AGG_SUM:
            case ExprType::AGG_AVG:
            case ExprType::AGG_MIN:
            case ExprType::AGG_MAX:
                visit_aggregate(static_cast<const FunctionCall*>(expr));
                break;
            case ExprType::TABLE_REF:
                visit_table_ref(static_cast<const TableRef*>(expr));
                break;
            case ExprType::JOIN_CLAUSE:
                visit_join(static_cast<const JoinClause*>(expr));
                break;
            case ExprType::SELECT_STMT:
                visit_select(static_cast<const SelectStmt*>(expr));
                break;
            case ExprType::INSERT_STMT:
                visit_insert(static_cast<const InsertStmt*>(expr));
                break;
            case ExprType::UPDATE_STMT:
                visit_update(static_cast<const UpdateStmt*>(expr));
                break;
            case ExprType::DELETE_STMT:
                visit_delete(static_cast<const DeleteStmt*>(expr));
                break;
            case ExprType::CREATE_TABLE_STMT:
                visit_create_table(static_cast<const CreateTableStmt*>(expr));
                break;
            case ExprType::CTE:
                visit_cte(static_cast<const CTE*>(expr));
                break;
            case ExprType::WITH_CLAUSE:
                visit_with_clause(static_cast<const WithClause*>(expr));
                break;
            case ExprType::WINDOW_FUNCTION:
                visit_window_function(static_cast<const WindowFunction*>(expr));
                break;
            case ExprType::SUBQUERY:
                visit_subquery(static_cast<const Subquery*>(expr));
                break;
            case ExprType::ALIAS:
                visit_alias(static_cast<const Alias*>(expr));
                break;
            case ExprType::UNION_STMT:
            case ExprType::INTERSECT_STMT:
            case ExprType::EXCEPT_STMT:
                visit_set_operation(static_cast<const SetOperation*>(expr));
                break;
            case ExprType::CASE_EXPR:
                visit_case_expr(static_cast<const CaseExpr*>(expr));
                break;
            case ExprType::BETWEEN:
                visit_between(static_cast<const BetweenExpr*>(expr));
                break;
            case ExprType::IN:
                visit_in(static_cast<const InExpr*>(expr));
                break;
            case ExprType::EXISTS:
                visit_exists(static_cast<const ExistsExpr*>(expr));
                break;
            case ExprType::COALESCE:
            case ExprType::NULLIF:
                visit_function_call(static_cast<const FunctionCall*>(expr));
                break;
            case ExprType::CREATE_INDEX_STMT:
                visit_create_index(static_cast<const CreateIndexStmt*>(expr));
                break;
            case ExprType::CREATE_VIEW_STMT:
                visit_create_view(static_cast<const CreateViewStmt*>(expr));
                break;
            case ExprType::DROP_TABLE_STMT:
                visit_drop_table(static_cast<const DropTableStmt*>(expr));
                break;
            case ExprType::DROP_INDEX_STMT:
                visit_drop_index(static_cast<const DropIndexStmt*>(expr));
                break;
            case ExprType::DROP_VIEW_STMT:
                visit_drop_view(static_cast<const DropViewStmt*>(expr));
                break;
            case ExprType::ALTER_TABLE_STMT:
                visit_alter_table(static_cast<const AlterTableStmt*>(expr));
                break;
            case ExprType::TRUNCATE_STMT:
                visit_truncate(static_cast<const TruncateStmt*>(expr));
                break;
            case ExprType::BEGIN_STMT:
                visit_begin(static_cast<const BeginStmt*>(expr));
                break;
            case ExprType::COMMIT_STMT:
                visit_commit(static_cast<const CommitStmt*>(expr));
                break;
            case ExprType::ROLLBACK_STMT:
                visit_rollback(static_cast<const RollbackStmt*>(expr));
                break;
            case ExprType::SAVEPOINT_STMT:
                visit_savepoint(static_cast<const SavepointStmt*>(expr));
                break;
            case ExprType::SET_STMT:
                visit_set(static_cast<const SetStmt*>(expr));
                break;
            case ExprType::SHOW_STMT:
                visit_show(static_cast<const ShowStmt*>(expr));
                break;
            case ExprType::DESCRIBE_STMT:
                visit_describe(static_cast<const DescribeStmt*>(expr));
                break;
            case ExprType::EXPLAIN_STMT:
                visit_explain(static_cast<const ExplainStmt*>(expr));
                break;
            case ExprType::CAST:
                visit_function_call(static_cast<const FunctionCall*>(expr));
                break;
            case ExprType::ANY_EXPR:
            case ExprType::ALL_EXPR:
                visit_quantified(static_cast<const QuantifiedExpr*>(expr));
                break;
            case ExprType::VALUES_CLAUSE:
                visit_values(static_cast<const ValuesClause*>(expr));
                break;
            case ExprType::ARRAY_LITERAL:
                visit_array_literal(static_cast<const ArrayLiteral*>(expr));
                break;
            case ExprType::ARRAY_INDEX:
                visit_array_index(static_cast<const ArrayIndex*>(expr));
                break;
            case ExprType::REGEX_MATCH:
                visit_regex_match(static_cast<const RegexMatch*>(expr));
                break;
            case ExprType::PIVOT_CLAUSE:
                visit_pivot(static_cast<const PivotClause*>(expr));
                break;
            case ExprType::UNPIVOT_CLAUSE:
                visit_unpivot(static_cast<const UnpivotClause*>(expr));
                break;
            case ExprType::CALL_PROCEDURE:
                visit_call_procedure(static_cast<const CallProcedureStmt*>(expr));
                break;
            case ExprType::RETURN_STMT:
                visit_return_stmt(static_cast<const ReturnStmt*>(expr));
                break;
            case ExprType::DECLARE_VAR:
                visit_declare_stmt(static_cast<const DeclareStmt*>(expr));
                break;
            case ExprType::IF_STMT:
                visit_if_stmt(static_cast<const IfStmt*>(expr));
                break;
            case ExprType::WHILE_LOOP:
                visit_while_loop(static_cast<const WhileLoop*>(expr));
                break;
            case ExprType::FOR_LOOP:
                visit_for_loop(static_cast<const ForLoop*>(expr));
                break;
            case ExprType::BEGIN_END_BLOCK:
                visit_begin_end_block(static_cast<const BeginEndBlock*>(expr));
                break;
            case ExprType::CREATE_PROCEDURE:
                visit_create_procedure(static_cast<const CreateProcedureStmt*>(expr));
                break;
            case ExprType::DELIMITER_STMT:
                visit_delimiter(static_cast<const DelimiterStmt*>(expr));
                break;
            case ExprType::ASSIGNMENT_STMT:
                visit_assignment(static_cast<const AssignmentStmt*>(expr));
                break;
            case ExprType::EXCEPTION_BLOCK:
                visit_exception_block(static_cast<const ExceptionBlock*>(expr));
                break;
            case ExprType::DECLARE_CURSOR:
                visit_declare_cursor(static_cast<const DeclareCursorStmt*>(expr));
                break;
            case ExprType::OPEN_CURSOR:
                visit_open_cursor(static_cast<const OpenCursorStmt*>(expr));
                break;
            case ExprType::FETCH_CURSOR:
                visit_fetch_cursor(static_cast<const FetchCursorStmt*>(expr));
                break;
            case ExprType::CLOSE_CURSOR:
                visit_close_cursor(static_cast<const CloseCursorStmt*>(expr));
                break;
            case ExprType::RAISE_STMT:
                visit_raise(static_cast<const RaiseStmt*>(expr));
                break;
            default:
                // Unsupported node types are silently ignored to avoid breaking existing functionality
                break;
        }
    }

    void visit_literal(const Literal* lit) {
        // Handle special literals
        if (lit->value == "NULL") {
            sql_ << "NULL";
            return;
        }

        // Handle boolean keywords (dialect-specific)
        // NOTE: We only convert TRUE/FALSE keywords, not numeric 1/0
        // because numeric literals might be integers, not booleans
        if (lit->value == "TRUE" || lit->value == "true") {
            sql_ << features_.true_literal;
            return;
        }
        if (lit->value == "FALSE" || lit->value == "false") {
            sql_ << features_.false_literal;
            return;
        }

        // Already quoted string
        if (!lit->value.empty() && lit->value[0] == '\'') {
            sql_ << lit->value;
            return;
        }

        // Check if it's a number
        bool is_number = true;
        for (char c : lit->value) {
            if (!std::isdigit(c) && c != '.' && c != '-' && c != 'e' && c != 'E') {
                is_number = false;
                break;
            }
        }

        if (is_number) {
            sql_ << lit->value;
        } else {
            // String literal - use dialect-specific quote
            sql_ << features_.string_quote << lit->value << features_.string_quote;
        }
    }

    /// Quote identifier based on dialect
    void quote_identifier(const std::string& ident) {
        if (features_.identifier_quote == '[') {
            // SQL Server uses [identifier]
            sql_ << '[' << ident << ']';
        } else {
            sql_ << features_.identifier_quote << ident << features_.identifier_quote;
        }
    }

    void visit_column(const Column* col) {
        if (!col->table.empty()) {
            quote_identifier(col->table);
            sql_ << ".";
        }
        quote_identifier(col->column);
    }

    void visit_star(const Star* star) {
        if (!star->table.empty()) {
            sql_ << star->table << ".";
        }
        sql_ << "*";
    }

    void visit_binary_op(const BinaryOp* op) {
        // Handle ILIKE for dialects that don't support it
        if (op->type == ExprType::ILIKE && !features_.supports_ilike) {
            // Convert ILIKE to LOWER(x) LIKE LOWER(y)
            sql_ << "LOWER(";
            visit(op->left);
            sql_ << ") LIKE LOWER(";
            visit(op->right);
            sql_ << ")";
            return;
        }

        if (op->type == ExprType::NOT_ILIKE && !features_.supports_ilike) {
            // Convert NOT ILIKE to LOWER(x) NOT LIKE LOWER(y)
            sql_ << "LOWER(";
            visit(op->left);
            sql_ << ") NOT LIKE LOWER(";
            visit(op->right);
            sql_ << ")";
            return;
        }

        visit(op->left);
        sql_ << " " << operator_string(op->type) << " ";
        visit(op->right);
    }

    void visit_unary_op(const UnaryOp* op) {
        if (op->type == ExprType::NOT) {
            sql_ << "NOT ";
            visit(op->operand);
        } else if (op->type == ExprType::IS_NULL) {
            visit(op->operand);
            sql_ << " IS NULL";
        } else if (op->type == ExprType::IS_NOT_NULL) {
            visit(op->operand);
            sql_ << " IS NOT NULL";
        }
    }

    void visit_function_call(const FunctionCall* func) {
        sql_ << func->name << "(";
        if (func->distinct) sql_ << "DISTINCT ";
        for (size_t i = 0; i < func->args.size(); ++i) {
            if (i > 0) sql_ << ", ";
            visit(func->args[i]);
        }
        sql_ << ")";
    }

    void visit_aggregate(const FunctionCall* agg) {
        switch (agg->type) {
            case ExprType::AGG_COUNT: sql_ << "COUNT"; break;
            case ExprType::AGG_SUM: sql_ << "SUM"; break;
            case ExprType::AGG_AVG: sql_ << "AVG"; break;
            case ExprType::AGG_MIN: sql_ << "MIN"; break;
            case ExprType::AGG_MAX: sql_ << "MAX"; break;
            default: sql_ << "UNKNOWN"; break;
        }
        sql_ << "(";
        if (agg->distinct) sql_ << "DISTINCT ";
        for (size_t i = 0; i < agg->args.size(); ++i) {
            if (i > 0) sql_ << ", ";
            visit(agg->args[i]);
        }
        sql_ << ")";
    }

    void visit_table_ref(const TableRef* table) {
        if (!table->database.empty()) {
            quote_identifier(table->database);
            sql_ << ".";
        }
        if (!table->schema.empty()) {
            quote_identifier(table->schema);
            sql_ << ".";
        }
        quote_identifier(table->table);
        if (!table->alias.empty()) {
            sql_ << " AS ";
            quote_identifier(table->alias);
        }
    }

    void visit_join(const JoinClause* join) {
        visit(join->left_table);
        sql_ << " ";

        switch (join->join_type) {
            case JoinClause::JoinType::INNER: sql_ << "INNER JOIN"; break;
            case JoinClause::JoinType::LEFT: sql_ << "LEFT JOIN"; break;
            case JoinClause::JoinType::RIGHT: sql_ << "RIGHT JOIN"; break;
            case JoinClause::JoinType::FULL: sql_ << "FULL JOIN"; break;
            case JoinClause::JoinType::CROSS: sql_ << "CROSS JOIN"; break;
        }

        sql_ << " ";
        visit(join->right_table);

        if (join->condition) {
            sql_ << " ON ";
            visit(join->condition);
        }
    }

    void visit_select(const SelectStmt* stmt) {
        // WITH clause (CTEs)
        if (stmt->with) {
            visit_with_clause(stmt->with);
            space_or_newline();
        }

        write("SELECT ");

        // SQL Server: TOP N comes before DISTINCT
        if (stmt->limit && features_.limit_style == DialectFeatures::LimitStyle::TOP) {
            write("TOP ");
            visit(stmt->limit);
            write(" ");
        }

        if (stmt->distinct) write("DISTINCT ");

        // Columns
        if (stmt->columns.empty()) {
            write("*");
        } else {
            if (options_.pretty && stmt->columns.size() > 1) {
                indent();
                newline();
            }
            for (size_t i = 0; i < stmt->columns.size(); ++i) {
                if (i > 0) {
                    write(",");
                    if (options_.pretty) {
                        newline();
                    } else {
                        write(" ");
                    }
                }
                visit(stmt->columns[i]);
            }
            if (options_.pretty && stmt->columns.size() > 1) {
                dedent();
            }
        }

        if (stmt->from) {
            space_or_newline();
            write("FROM ");
            visit(stmt->from);
        }

        if (stmt->where) {
            space_or_newline();
            write("WHERE ");
            visit(stmt->where);
        }

        if (!stmt->group_by.empty()) {
            space_or_newline();
            write("GROUP BY ");
            for (size_t i = 0; i < stmt->group_by.size(); ++i) {
                if (i > 0) write(", ");
                visit(stmt->group_by[i]);
            }
        }

        if (stmt->having) {
            space_or_newline();
            write("HAVING ");
            visit(stmt->having);
        }

        if (stmt->qualify && features_.supports_qualify) {
            space_or_newline();
            write("QUALIFY ");
            visit(stmt->qualify);
        }

        if (!stmt->order_by.empty()) {
            space_or_newline();
            write("ORDER BY ");
            for (size_t i = 0; i < stmt->order_by.size(); ++i) {
                if (i > 0) write(", ");
                visit(stmt->order_by[i]);
            }
        }

        // Handle LIMIT/OFFSET based on dialect
        if (stmt->limit || stmt->offset) {
            switch (features_.limit_style) {
                case DialectFeatures::LimitStyle::LIMIT_OFFSET:
                    // PostgreSQL, MySQL: LIMIT n OFFSET m
                    if (stmt->limit) {
                        space_or_newline();
                        write("LIMIT ");
                        visit(stmt->limit);
                    }
                    if (stmt->offset) {
                        space_or_newline();
                        write("OFFSET ");
                        visit(stmt->offset);
                    }
                    break;

                case DialectFeatures::LimitStyle::TOP:
                    // SQL Server: TOP already handled above
                    // OFFSET/FETCH for pagination
                    if (stmt->offset) {
                        space_or_newline();
                        write("OFFSET ");
                        visit(stmt->offset);
                        write(" ROWS");
                    }
                    break;

                case DialectFeatures::LimitStyle::FETCH_FIRST:
                    // Oracle, ANSI SQL: OFFSET n ROWS FETCH FIRST m ROWS ONLY
                    if (stmt->offset) {
                        space_or_newline();
                        write("OFFSET ");
                        visit(stmt->offset);
                        write(" ROWS");
                    }
                    if (stmt->limit) {
                        space_or_newline();
                        write("FETCH FIRST ");
                        visit(stmt->limit);
                        write(" ROWS ONLY");
                    }
                    break;

                case DialectFeatures::LimitStyle::ROWNUM:
                    // Oracle legacy: WHERE ROWNUM <= n (handled in WHERE clause transformation)
                    break;
            }
        }
    }

    void visit_insert(const InsertStmt* stmt) {
        sql_ << "INSERT INTO ";
        visit_table_ref(stmt->table);

        // Column list
        if (!stmt->columns.empty()) {
            sql_ << " (";
            for (size_t i = 0; i < stmt->columns.size(); ++i) {
                if (i > 0) sql_ << ", ";
                sql_ << stmt->columns[i];
            }
            sql_ << ")";
        }

        // VALUES or SELECT
        if (stmt->select_stmt) {
            sql_ << " ";
            visit_select(stmt->select_stmt);
        } else if (!stmt->values.empty()) {
            sql_ << " VALUES ";
            for (size_t i = 0; i < stmt->values.size(); ++i) {
                if (i > 0) sql_ << ", ";
                sql_ << "(";
                for (size_t j = 0; j < stmt->values[i].size(); ++j) {
                    if (j > 0) sql_ << ", ";
                    visit(stmt->values[i][j]);
                }
                sql_ << ")";
            }
        }
    }

    void visit_update(const UpdateStmt* stmt) {
        sql_ << "UPDATE ";
        visit_table_ref(stmt->table);

        sql_ << " SET ";
        for (size_t i = 0; i < stmt->assignments.size(); ++i) {
            if (i > 0) sql_ << ", ";
            sql_ << stmt->assignments[i].first << " = ";
            visit(stmt->assignments[i].second);
        }

        if (stmt->from) {
            sql_ << " FROM ";
            visit(stmt->from);
        }

        if (stmt->where) {
            sql_ << " WHERE ";
            visit(stmt->where);
        }
    }

    void visit_delete(const DeleteStmt* stmt) {
        sql_ << "DELETE FROM ";
        visit_table_ref(stmt->table);

        if (stmt->using_clause) {
            sql_ << " USING ";
            visit(stmt->using_clause);
        }

        if (stmt->where) {
            sql_ << " WHERE ";
            visit(stmt->where);
        }
    }

    void visit_create_table(const CreateTableStmt* stmt) {
        sql_ << "CREATE TABLE ";
        if (stmt->if_not_exists) {
            sql_ << "IF NOT EXISTS ";
        }
        visit_table_ref(stmt->table);

        if (stmt->as_select) {
            sql_ << " AS ";
            visit_select(stmt->as_select);
        } else {
            sql_ << " (";
            for (size_t i = 0; i < stmt->columns.size(); ++i) {
                if (i > 0) sql_ << ", ";
                const auto& col = stmt->columns[i];
                sql_ << col.name << " " << col.type;
                if (col.not_null) sql_ << " NOT NULL";
                if (col.primary_key) sql_ << " PRIMARY KEY";
                if (col.unique) sql_ << " UNIQUE";
                if (col.default_value) {
                    sql_ << " DEFAULT ";
                    visit(col.default_value);
                }
            }
            sql_ << ")";
        }
    }

    void visit_with_clause(const WithClause* with) {
        sql_ << "WITH ";
        if (with->recursive) sql_ << "RECURSIVE ";

        for (size_t i = 0; i < with->ctes.size(); ++i) {
            if (i > 0) sql_ << ", ";
            visit_cte(with->ctes[i]);
        }
    }

    void visit_cte(const CTE* cte) {
        sql_ << cte->name;

        // Optional column list
        if (!cte->columns.empty()) {
            sql_ << " (";
            for (size_t i = 0; i < cte->columns.size(); ++i) {
                if (i > 0) sql_ << ", ";
                sql_ << cte->columns[i];
            }
            sql_ << ")";
        }

        sql_ << " AS (";
        if (cte->query) {
            visit(cte->query);  // Use general visit() to handle both SELECT and set operations
        }
        sql_ << ")";
    }

    void visit_window_function(const WindowFunction* win_func) {
        sql_ << win_func->function_name << "(";
        for (size_t i = 0; i < win_func->args.size(); ++i) {
            if (i > 0) sql_ << ", ";
            visit(win_func->args[i]);
        }
        sql_ << ") OVER (";

        const auto* spec = win_func->over;
        if (spec) {
            bool need_space = false;

            if (!spec->partition_by.empty()) {
                sql_ << "PARTITION BY ";
                for (size_t i = 0; i < spec->partition_by.size(); ++i) {
                    if (i > 0) sql_ << ", ";
                    visit(spec->partition_by[i]);
                }
                need_space = true;
            }

            if (!spec->order_by.empty()) {
                if (need_space) sql_ << " ";
                sql_ << "ORDER BY ";
                for (size_t i = 0; i < spec->order_by.size(); ++i) {
                    if (i > 0) sql_ << ", ";
                    visit(spec->order_by[i]);
                }
                need_space = true;
            }

            if (spec->frame) {
                if (need_space) sql_ << " ";
                visit_frame_clause(spec->frame);
            }
        }

        sql_ << ")";
    }

    void visit_subquery(const Subquery* subq) {
        sql_ << "(";
        visit_select(subq->query);
        sql_ << ")";
        if (!subq->alias.empty()) {
            sql_ << " AS " << subq->alias;
        }
    }

    void visit_alias(const Alias* alias) {
        visit(alias->expr);
        sql_ << " AS " << alias->alias;
    }

    void visit_set_operation(const SetOperation* set_op) {
        // Check if dialect supports the operation
        bool unsupported = false;
        if (set_op->op_type == SetOperation::OpType::INTERSECT && !features_.supports_intersect) {
            unsupported = true;
        }
        if (set_op->op_type == SetOperation::OpType::EXCEPT && !features_.supports_except) {
            unsupported = true;
        }

        if (unsupported) {
            // For dialects that don't support INTERSECT/EXCEPT, we could generate
            // equivalent SQL using JOINs and subqueries, but for now emit a comment
            sql_ << "/* Unsupported set operation in " << DialectConfig::get_name(dialect_) << " */ ";
        }

        visit(set_op->left);
        sql_ << " ";

        switch (set_op->op_type) {
            case SetOperation::OpType::UNION:
                sql_ << "UNION";
                break;
            case SetOperation::OpType::INTERSECT:
                sql_ << "INTERSECT";
                break;
            case SetOperation::OpType::EXCEPT:
                sql_ << "EXCEPT";
                break;
        }

        if (set_op->all) {
            sql_ << " ALL";
        }

        sql_ << " ";
        visit(set_op->right);
    }

    void visit_case_expr(const CaseExpr* case_expr) {
        sql_ << "CASE";

        if (case_expr->case_value) {
            sql_ << " ";
            visit(case_expr->case_value);
        }

        for (const auto& when_clause : case_expr->when_clauses) {
            sql_ << " WHEN ";
            visit(when_clause.condition);
            sql_ << " THEN ";
            visit(when_clause.result);
        }

        if (case_expr->else_expr) {
            sql_ << " ELSE ";
            visit(case_expr->else_expr);
        }

        sql_ << " END";
    }

    void visit_between(const BetweenExpr* between) {
        visit(between->expr);
        sql_ << " BETWEEN ";
        visit(between->lower);
        sql_ << " AND ";
        visit(between->upper);
    }

    void visit_in(const InExpr* in_expr) {
        visit(in_expr->expr);
        sql_ << " IN (";

        for (size_t i = 0; i < in_expr->values.size(); ++i) {
            if (i > 0) sql_ << ", ";
            visit(in_expr->values[i]);
        }

        sql_ << ")";
    }

    void visit_exists(const ExistsExpr* exists) {
        if (exists->not_exists) {
            sql_ << "NOT ";
        }
        sql_ << "EXISTS (";
        visit(exists->subquery);
        sql_ << ")";
    }

    void visit_create_index(const CreateIndexStmt* stmt) {
        sql_ << "CREATE ";
        if (stmt->unique) {
            sql_ << "UNIQUE ";
        }
        sql_ << "INDEX ";
        if (stmt->if_not_exists) {
            sql_ << "IF NOT EXISTS ";
        }
        sql_ << stmt->index_name << " ON ";
        visit_table_ref(stmt->table);
        sql_ << " (";
        for (size_t i = 0; i < stmt->columns.size(); ++i) {
            if (i > 0) sql_ << ", ";
            sql_ << stmt->columns[i];
        }
        sql_ << ")";
    }

    void visit_create_view(const CreateViewStmt* stmt) {
        sql_ << "CREATE ";
        if (stmt->or_replace) {
            sql_ << "OR REPLACE ";
        }
        sql_ << "VIEW ";
        if (stmt->if_not_exists) {
            sql_ << "IF NOT EXISTS ";
        }
        sql_ << stmt->name;

        if (!stmt->columns.empty()) {
            sql_ << " (";
            for (size_t i = 0; i < stmt->columns.size(); ++i) {
                if (i > 0) sql_ << ", ";
                sql_ << stmt->columns[i];
            }
            sql_ << ")";
        }

        sql_ << " AS ";
        visit_select(stmt->query);
    }

    void visit_drop_table(const DropTableStmt* stmt) {
        sql_ << "DROP TABLE ";
        if (stmt->if_exists) {
            sql_ << "IF EXISTS ";
        }
        visit_table_ref(stmt->table);
        if (stmt->cascade) {
            sql_ << " CASCADE";
        }
    }

    void visit_drop_index(const DropIndexStmt* stmt) {
        sql_ << "DROP INDEX ";
        if (stmt->if_exists) {
            sql_ << "IF EXISTS ";
        }
        sql_ << stmt->index_name;
        if (stmt->table) {
            sql_ << " ON ";
            visit_table_ref(stmt->table);
        }
    }

    void visit_drop_view(const DropViewStmt* stmt) {
        sql_ << "DROP VIEW ";
        if (stmt->if_exists) {
            sql_ << "IF EXISTS ";
        }
        sql_ << stmt->name;
        if (stmt->cascade) {
            sql_ << " CASCADE";
        }
    }

    void visit_alter_table(const AlterTableStmt* stmt) {
        sql_ << "ALTER TABLE ";
        visit_table_ref(stmt->table);
        sql_ << " ";

        switch (stmt->operation) {
            case AlterOperation::ADD_COLUMN:
                sql_ << "ADD COLUMN " << stmt->column_def.name << " " << stmt->column_def.type;
                if (stmt->column_def.not_null) sql_ << " NOT NULL";
                break;
            case AlterOperation::DROP_COLUMN:
                sql_ << "DROP COLUMN " << stmt->old_name;
                break;
            case AlterOperation::RENAME_COLUMN:
                sql_ << "RENAME COLUMN " << stmt->old_name << " TO " << stmt->new_name;
                break;
            case AlterOperation::RENAME_TABLE:
                sql_ << "RENAME TO " << stmt->new_name;
                break;
            default:
                break;
        }
    }

    void visit_truncate(const TruncateStmt* stmt) {
        sql_ << "TRUNCATE TABLE " << stmt->table;
        if (stmt->cascade) {
            sql_ << " CASCADE";
        }
    }

    void visit_begin(const BeginStmt* stmt) {
        if (stmt->start_transaction) {
            sql_ << "START TRANSACTION";
        } else {
            sql_ << "BEGIN";
        }
    }

    void visit_commit(const CommitStmt*) {
        sql_ << "COMMIT";
    }

    void visit_rollback(const RollbackStmt* stmt) {
        sql_ << "ROLLBACK";
        if (!stmt->savepoint_name.empty()) {
            sql_ << " TO SAVEPOINT " << stmt->savepoint_name;
        }
    }

    void visit_savepoint(const SavepointStmt* stmt) {
        sql_ << "SAVEPOINT " << stmt->name;
    }

    void visit_set(const SetStmt* stmt) {
        sql_ << "SET ";
        if (stmt->scope == SetStmt::Scope::GLOBAL) {
            sql_ << "GLOBAL ";
        } else if (stmt->scope == SetStmt::Scope::SESSION) {
            sql_ << "SESSION ";
        }

        for (size_t i = 0; i < stmt->assignments.size(); ++i) {
            if (i > 0) sql_ << ", ";
            sql_ << stmt->assignments[i].first << " = ";
            visit(stmt->assignments[i].second);
        }
    }

    void visit_show(const ShowStmt* stmt) {
        sql_ << "SHOW " << stmt->what;
        if (!stmt->target.empty()) {
            sql_ << " " << stmt->target;
        }
    }

    void visit_describe(const DescribeStmt* stmt) {
        sql_ << "DESCRIBE " << stmt->target;
    }

    void visit_explain(const ExplainStmt* stmt) {
        sql_ << "EXPLAIN ";
        if (stmt->analyze) {
            sql_ << "ANALYZE ";
        }
        visit(stmt->statement);
    }

    void visit_quantified(const QuantifiedExpr* expr) {
        visit(expr->left);
        sql_ << " " << operator_string(expr->comparison_op) << " ";

        switch (expr->quantifier) {
            case QuantifiedExpr::QuantifierType::ANY:
                sql_ << "ANY";
                break;
            case QuantifiedExpr::QuantifierType::ALL:
                sql_ << "ALL";
                break;
            case QuantifiedExpr::QuantifierType::SOME:
                sql_ << "SOME";
                break;
        }

        sql_ << " (";
        visit_select(expr->subquery);
        sql_ << ")";
    }

    void visit_values(const ValuesClause* values) {
        sql_ << "VALUES ";
        for (size_t i = 0; i < values->rows.size(); ++i) {
            if (i > 0) sql_ << ", ";
            sql_ << "(";
            for (size_t j = 0; j < values->rows[i].size(); ++j) {
                if (j > 0) sql_ << ", ";
                visit(values->rows[i][j]);
            }
            sql_ << ")";
        }
    }

    void visit_array_literal(const ArrayLiteral* arr) {
        sql_ << "[";
        for (size_t i = 0; i < arr->elements.size(); ++i) {
            if (i > 0) sql_ << ", ";
            visit(arr->elements[i]);
        }
        sql_ << "]";
    }

    void visit_array_index(const ArrayIndex* idx) {
        visit(idx->array);
        sql_ << "[";
        visit(idx->index);
        sql_ << "]";
    }

    void visit_regex_match(const RegexMatch* regex) {
        visit(regex->expr);
        if (regex->similar_to) {
            sql_ << " SIMILAR TO ";
        } else {
            sql_ << " REGEXP ";
        }
        visit(regex->pattern);
    }

    void visit_frame_clause(const FrameClause* frame) {
        // Frame type: ROWS or RANGE or GROUPS
        switch (frame->frame_type) {
            case FrameType::ROWS: sql_ << "ROWS"; break;
            case FrameType::RANGE: sql_ << "RANGE"; break;
            case FrameType::GROUPS: sql_ << "GROUPS"; break;
        }
        sql_ << " ";

        // Check if we need BETWEEN ... AND ...
        bool use_between = (frame->end_bound != FrameBound::CURRENT_ROW ||
                           frame->end_offset != nullptr);

        if (use_between) {
            sql_ << "BETWEEN ";
            visit_frame_bound(frame->start_bound, frame->start_offset);
            sql_ << " AND ";
            visit_frame_bound(frame->end_bound, frame->end_offset);
        } else {
            // Single boundary
            visit_frame_bound(frame->start_bound, frame->start_offset);
        }
    }

    void visit_frame_bound(FrameBound bound, Expression* offset) {
        switch (bound) {
            case FrameBound::UNBOUNDED_PRECEDING:
                sql_ << "UNBOUNDED PRECEDING";
                break;
            case FrameBound::UNBOUNDED_FOLLOWING:
                sql_ << "UNBOUNDED FOLLOWING";
                break;
            case FrameBound::CURRENT_ROW:
                sql_ << "CURRENT ROW";
                break;
            case FrameBound::PRECEDING:
                visit(offset);
                sql_ << " PRECEDING";
                break;
            case FrameBound::FOLLOWING:
                visit(offset);
                sql_ << " FOLLOWING";
                break;
        }
    }

    void visit_pivot(const PivotClause* pivot) {
        // Generate base table/subquery
        visit(pivot->table_expr);

        // Generate PIVOT clause
        sql_ << " PIVOT (";
        visit_function_call(pivot->aggregate);
        sql_ << " FOR ";
        visit(pivot->pivot_column);
        sql_ << " IN (";

        for (size_t i = 0; i < pivot->pivot_values.size(); ++i) {
            if (i > 0) sql_ << ", ";
            visit(pivot->pivot_values[i]);
        }

        sql_ << "))";

        // Optional alias
        if (!pivot->alias.empty()) {
            sql_ << " AS " << pivot->alias;
        }
    }

    void visit_unpivot(const UnpivotClause* unpivot) {
        // Generate base table/subquery
        visit(unpivot->table_expr);

        // Generate UNPIVOT clause
        sql_ << " UNPIVOT (";
        sql_ << unpivot->value_column;
        sql_ << " FOR ";
        sql_ << unpivot->name_column;
        sql_ << " IN (";

        for (size_t i = 0; i < unpivot->unpivot_columns.size(); ++i) {
            if (i > 0) sql_ << ", ";
            sql_ << unpivot->unpivot_columns[i];
        }

        sql_ << "))";

        // Optional alias
        if (!unpivot->alias.empty()) {
            sql_ << " AS " << unpivot->alias;
        }
    }

    void visit_call_procedure(const CallProcedureStmt* stmt) {
        sql_ << "CALL " << stmt->name;

        // Arguments (always include parentheses, even if empty)
        sql_ << "(";
        for (size_t i = 0; i < stmt->arguments.size(); ++i) {
            if (i > 0) sql_ << ", ";
            visit(stmt->arguments[i]);
        }
        sql_ << ")";
    }

    void visit_return_stmt(const ReturnStmt* stmt) {
        sql_ << "RETURN";
        if (stmt->return_value) {
            sql_ << " ";
            visit(stmt->return_value);
        }
    }

    void visit_declare_stmt(const DeclareStmt* stmt) {
        sql_ << "DECLARE " << stmt->variable_name << " " << stmt->type;
        if (stmt->default_value) {
            sql_ << " DEFAULT ";
            visit(stmt->default_value);
        }
    }

    void visit_if_stmt(const IfStmt* stmt) {
        sql_ << "IF ";
        visit(stmt->condition);
        sql_ << " THEN";

        // THEN statements
        for (auto* then_stmt : stmt->then_stmts) {
            sql_ << " ";
            visit(then_stmt);
        }

        // ELSEIF branches
        for (const auto& elseif : stmt->elseif_branches) {
            sql_ << " ELSEIF ";
            visit(elseif.condition);
            sql_ << " THEN";
            for (auto* stmt : elseif.statements) {
                sql_ << " ";
                visit(stmt);
            }
        }

        // ELSE clause
        if (!stmt->else_stmts.empty()) {
            sql_ << " ELSE";
            for (auto* else_stmt : stmt->else_stmts) {
                sql_ << " ";
                visit(else_stmt);
            }
        }

        sql_ << " END IF";
    }

    void visit_while_loop(const WhileLoop* stmt) {
        sql_ << "WHILE ";
        visit(stmt->condition);
        sql_ << " DO";

        // Loop body
        for (auto* body_stmt : stmt->body) {
            sql_ << " ";
            visit(body_stmt);
        }

        sql_ << " END WHILE";
    }

    void visit_for_loop(const ForLoop* stmt) {
        // Check if target dialect supports FOR loops
        if (!features_.supports_for_loops) {
            // Transpile FOR loop to WHILE loop for T-SQL
            visit_for_as_while(stmt);
            return;
        }

        sql_ << "FOR " << stmt->variable << " IN ";
        visit(stmt->start_value);
        sql_ << "..";
        visit(stmt->end_value);
        sql_ << " LOOP";

        // Loop body
        for (auto* body_stmt : stmt->body) {
            sql_ << " ";
            visit(body_stmt);
        }

        sql_ << " END LOOP";
    }

    /// Transpile FOR loop to WHILE loop (for T-SQL which doesn't support FOR)
    void visit_for_as_while(const ForLoop* stmt) {
        // DECLARE @variable INT = start_value
        sql_ << "DECLARE " << features_.variable_prefix << stmt->variable << " INT = ";
        visit(stmt->start_value);
        sql_ << "; ";

        // WHILE @variable <= end_value
        sql_ << "WHILE " << features_.variable_prefix << stmt->variable << " <= ";
        visit(stmt->end_value);
        sql_ << " BEGIN ";

        // Loop body
        for (auto* body_stmt : stmt->body) {
            visit(body_stmt);
            sql_ << "; ";
        }

        // SET @variable = @variable + 1
        sql_ << "SET " << features_.variable_prefix << stmt->variable << " = "
             << features_.variable_prefix << stmt->variable << " + 1; ";

        sql_ << "END";
    }

    /// Visit BEGIN...END procedural block (dialect-aware)
    void visit_begin_end_block(const BeginEndBlock* block) {
        // Only generate BEGIN...END if dialect supports it
        if (!features_.supports_begin_end_blocks) {
            // For dialects without BEGIN...END, just output statements sequentially
            for (size_t i = 0; i < block->statements.size(); ++i) {
                if (i > 0) sql_ << "; ";
                visit(block->statements[i]);
            }
            return;
        }

        sql_ << "BEGIN";

        if (options_.pretty) {
            indent();
        }

        // Generate statements inside the block
        for (auto* stmt : block->statements) {
            if (options_.pretty) {
                newline();
            } else {
                sql_ << " ";
            }
            visit(stmt);
            sql_ << ";";
        }

        if (options_.pretty) {
            dedent();
            newline();
        } else {
            sql_ << " ";
        }

        sql_ << "END";
    }
    /// Visit CREATE PROCEDURE or CREATE FUNCTION statement
    void visit_create_procedure(const CreateProcedureStmt* stmt) {
        sql_ << "CREATE ";
        if (stmt->or_replace) {
            sql_ << "OR REPLACE ";
        }
        
        if (stmt->is_function) {
            sql_ << "FUNCTION ";
        } else {
            sql_ << "PROCEDURE ";
        }
        
        sql_ << stmt->name;
        
        // Parameters
        sql_ << "(";
        for (size_t i = 0; i < stmt->parameters.size(); ++i) {
            if (i > 0) sql_ << ", ";
            
            const auto& param = stmt->parameters[i];
            
            // Parameter mode (IN, OUT, INOUT)
            switch (param.mode) {
                case ProcedureParam::Mode::IN: 
                    if (dialect_ == Dialect::Oracle || dialect_ == Dialect::PostgreSQL) {
                        sql_ << "IN ";
                    }
                    break;
                case ProcedureParam::Mode::OUT: sql_ << "OUT "; break;
                case ProcedureParam::Mode::INOUT: sql_ << "INOUT "; break;
            }
            
            sql_ << param.name << " " << param.type;
            
            if (param.default_value) {
                sql_ << " DEFAULT ";
                visit(param.default_value);
            }
        }
        sql_ << ")";
        
        // RETURNS clause (for functions)
        if (stmt->is_function && !stmt->return_type.empty()) {
            sql_ << " RETURNS " << stmt->return_type;
        }
        
        // LANGUAGE clause (PostgreSQL style)
        if (!stmt->language.empty()) {
            sql_ << " LANGUAGE " << stmt->language;
        }
        
        // AS clause
        if (!stmt->body.empty() || !stmt->declarations.empty()) {
            sql_ << " AS";
            
            if (options_.pretty) {
                newline();
            } else {
                sql_ << " ";
            }
            
            sql_ << "BEGIN";
            
            if (options_.pretty) {
                indent();
            }
            
            // Declarations
            for (auto* decl : stmt->declarations) {
                if (options_.pretty) {
                    newline();
                } else {
                    sql_ << " ";
                }
                visit(decl);
                sql_ << ";";
            }
            
            // Body statements
            for (auto* body_stmt : stmt->body) {
                if (options_.pretty) {
                    newline();
                } else {
                    sql_ << " ";
                }
                visit(body_stmt);
                sql_ << ";";
            }
            
            if (options_.pretty) {
                dedent();
                newline();
            } else {
                sql_ << " ";
            }
            
            sql_ << "END";
        }
    }

    void visit_delimiter(const DelimiterStmt* stmt) {
        sql_ << "DELIMITER " << stmt->delimiter;
    }

    void visit_assignment(const AssignmentStmt* stmt) {
        // Dialect-aware assignment
        if (dialect_ == Dialect::SQLServer || dialect_ == Dialect::MySQL) {
            sql_ << "SET " << stmt->variable_name << " = ";
        } else {
            // PostgreSQL, Oracle use :=
            sql_ << stmt->variable_name << " := ";
        }
        visit(stmt->value);
    }

    void visit_exception_block(const ExceptionBlock* block) {
        sql_ << "BEGIN";
        if (options_.pretty) {
            indent();
        }

        // Try statements
        for (auto* stmt : block->try_statements) {
            if (options_.pretty) {
                newline();
            } else {
                sql_ << " ";
            }
            visit(stmt);
            sql_ << ";";
        }

        // Exception handlers
        if (!block->handlers.empty()) {
            if (options_.pretty) {
                dedent();
                newline();
            } else {
                sql_ << " ";
            }
            sql_ << "EXCEPTION";
            if (options_.pretty) {
                indent();
            }

            for (const auto& handler : block->handlers) {
                if (options_.pretty) {
                    newline();
                } else {
                    sql_ << " ";
                }
                sql_ << "WHEN " << handler.exception_name << " THEN";
                if (options_.pretty) {
                    indent();
                }
                for (auto* stmt : handler.statements) {
                    if (options_.pretty) {
                        newline();
                    } else {
                        sql_ << " ";
                    }
                    visit(stmt);
                    sql_ << ";";
                }
                if (options_.pretty) {
                    dedent();
                }
            }
        }

        if (options_.pretty) {
            dedent();
            newline();
        } else {
            sql_ << " ";
        }
        sql_ << "END";
    }

    void visit_declare_cursor(const DeclareCursorStmt* stmt) {
        sql_ << "DECLARE " << stmt->cursor_name << " ";
        if (stmt->scroll) {
            sql_ << "SCROLL ";
        }
        sql_ << "CURSOR FOR ";
        visit(stmt->query);
    }

    void visit_open_cursor(const OpenCursorStmt* stmt) {
        sql_ << "OPEN " << stmt->cursor_name;
        if (!stmt->arguments.empty()) {
            sql_ << "(";
            for (size_t i = 0; i < stmt->arguments.size(); ++i) {
                if (i > 0) sql_ << ", ";
                visit(stmt->arguments[i]);
            }
            sql_ << ")";
        }
    }

    void visit_fetch_cursor(const FetchCursorStmt* stmt) {
        sql_ << "FETCH ";
        switch (stmt->direction) {
            case FetchCursorStmt::Direction::NEXT: sql_ << "NEXT "; break;
            case FetchCursorStmt::Direction::PRIOR: sql_ << "PRIOR "; break;
            case FetchCursorStmt::Direction::FIRST: sql_ << "FIRST "; break;
            case FetchCursorStmt::Direction::LAST: sql_ << "LAST "; break;
            default: break;
        }
        sql_ << "FROM " << stmt->cursor_name;

        if (!stmt->into_variables.empty()) {
            sql_ << " INTO ";
            for (size_t i = 0; i < stmt->into_variables.size(); ++i) {
                if (i > 0) sql_ << ", ";
                sql_ << stmt->into_variables[i];
            }
        }
    }

    void visit_close_cursor(const CloseCursorStmt* stmt) {
        sql_ << "CLOSE " << stmt->cursor_name;
    }

    void visit_raise(const RaiseStmt* stmt) {
        if (dialect_ == Dialect::MySQL) {
            sql_ << "SIGNAL SQLSTATE '" << stmt->error_code << "'";
            if (!stmt->message.empty()) {
                sql_ << " SET MESSAGE_TEXT = " << stmt->message;
            }
        } else {
            // PostgreSQL
            sql_ << "RAISE ";
            switch (stmt->level) {
                case RaiseStmt::Level::EXCEPTION: sql_ << "EXCEPTION"; break;
                case RaiseStmt::Level::NOTICE: sql_ << "NOTICE"; break;
                case RaiseStmt::Level::WARNING: sql_ << "WARNING"; break;
                case RaiseStmt::Level::INFO: sql_ << "INFO"; break;
                case RaiseStmt::Level::LOG: sql_ << "LOG"; break;
                case RaiseStmt::Level::DEBUG: sql_ << "DEBUG"; break;
            }
            if (!stmt->message.empty()) {
                sql_ << " " << stmt->message;
            }
        }
    }


    static std::string operator_string(ExprType type) {
        switch (type) {
            case ExprType::EQ: return "=";
            case ExprType::NEQ: return "<>";
            case ExprType::LT: return "<";
            case ExprType::LTE: return "<=";
            case ExprType::GT: return ">";
            case ExprType::GTE: return ">=";
            case ExprType::LIKE: return "LIKE";
            case ExprType::ILIKE: return "ILIKE";
            case ExprType::NOT_LIKE: return "NOT LIKE";
            case ExprType::NOT_ILIKE: return "NOT ILIKE";
            case ExprType::PLUS: return "+";
            case ExprType::MINUS: return "-";
            case ExprType::MUL: return "*";
            case ExprType::DIV: return "/";
            case ExprType::MOD: return "%";
            case ExprType::AND: return "AND";
            case ExprType::OR: return "OR";
            case ExprType::CONCAT: return "||";
            default: return "?";
        }
    }
};

} // namespace libsqlglot
