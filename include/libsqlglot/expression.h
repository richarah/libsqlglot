#pragma once

#include "fwd.h"
#include "arena.h"
#include <string>
#include <vector>
#include <cstdint>

namespace libsqlglot {

// Forward declarations
struct WithClause;
struct SelectStmt;

/// Expression node type
enum class ExprType : uint16_t {
    // Literals
    LITERAL,
    COLUMN,
    STAR,

    // Binary operations
    EQ, NEQ, LT, LTE, GT, GTE,
    LIKE, ILIKE, NOT_LIKE, NOT_ILIKE,
    PLUS, MINUS, MUL, DIV, MOD,
    CONCAT,                 // String concatenation ||
    AND, OR,
    BETWEEN,            // BETWEEN x AND y
    IN,                 // IN (values)

    // Unary operations
    NOT, IS_NULL, IS_NOT_NULL,
    EXISTS,             // EXISTS (subquery)

    // Functions
    FUNCTION_CALL,
    AGG_COUNT, AGG_SUM, AGG_AVG, AGG_MIN, AGG_MAX,

    // Conditional expressions
    CASE_EXPR,          // CASE WHEN ... THEN ... ELSE ... END
    COALESCE,           // COALESCE(expr1, expr2, ...)
    NULLIF,             // NULLIF(expr1, expr2)

    // Query components
    SELECT_STMT,
    FROM_CLAUSE,
    WHERE_CLAUSE,
    JOIN_CLAUSE,
    GROUP_BY,
    ORDER_BY,
    LIMIT_CLAUSE,

    // Set operations
    UNION_STMT,         // UNION / UNION ALL
    INTERSECT_STMT,     // INTERSECT
    EXCEPT_STMT,        // EXCEPT / MINUS

    // DML Statements
    INSERT_STMT,
    UPDATE_STMT,
    DELETE_STMT,

    // DDL Statements
    CREATE_TABLE_STMT,
    CREATE_INDEX_STMT,
    CREATE_VIEW_STMT,
    CREATE_SCHEMA_STMT,
    CREATE_DATABASE_STMT,
    DROP_TABLE_STMT,
    DROP_INDEX_STMT,
    DROP_VIEW_STMT,
    DROP_SCHEMA_STMT,
    DROP_DATABASE_STMT,
    ALTER_TABLE_STMT,
    TRUNCATE_STMT,
    MERGE_STMT,

    // Transaction statements
    BEGIN_STMT,
    COMMIT_STMT,
    ROLLBACK_STMT,
    SAVEPOINT_STMT,

    // Utility statements
    SET_STMT,
    SHOW_STMT,
    DESCRIBE_STMT,
    EXPLAIN_STMT,

    // Advanced SELECT features
    CTE,                // Common Table Expression (WITH clause)
    WITH_CLAUSE,
    WINDOW_FUNCTION,    // Window function with OVER clause
    WINDOW_SPEC,        // OVER (PARTITION BY ... ORDER BY ... ROWS/RANGE ...)
    PARTITION_BY,
    FRAME_CLAUSE,       // ROWS/RANGE frame specification

    // Tables
    TABLE_REF,
    SUBQUERY,
    VALUES_CLAUSE,      // VALUES (row1), (row2), ...
    LATERAL_JOIN,       // LATERAL subquery

    // Advanced features
    ARRAY_LITERAL,      // [1, 2, 3]
    ARRAY_INDEX,        // array[index]
    JSON_EXTRACT,       // JSON operations
    REGEX_MATCH,        // REGEXP / RLIKE
    PIVOT_CLAUSE,       // PIVOT
    UNPIVOT_CLAUSE,     // UNPIVOT
    TABLESAMPLE,        // TABLESAMPLE (percent)
    QUALIFY_CLAUSE,     // QUALIFY (window function filter)

    // Stored Procedures & Functions
    CREATE_PROCEDURE,   // CREATE PROCEDURE
    CREATE_FUNCTION,    // CREATE FUNCTION
    DROP_PROCEDURE,     // DROP PROCEDURE
    DROP_FUNCTION,      // DROP FUNCTION
    CALL_PROCEDURE,     // CALL procedure_name
    DECLARE_VAR,        // DECLARE variable
    DECLARE_CURSOR,     // DECLARE CURSOR
    IF_STMT,            // IF condition THEN ... END IF
    WHILE_LOOP,         // WHILE condition DO ... END WHILE
    FOR_LOOP,           // FOR var IN ... LOOP ... END LOOP
    RETURN_STMT,        // RETURN expression
    BEGIN_END_BLOCK,    // BEGIN ... END block (T-SQL, MySQL, PL/SQL)
    EXCEPTION_BLOCK,    // EXCEPTION block (PL/pgSQL, PL/SQL)
    ASSIGNMENT_STMT,    // Variable assignment (SET var = val, var := val)
    DELIMITER_STMT,     // DELIMITER command (MySQL)
    RAISE_STMT,         // RAISE/SIGNAL statement (error handling)
    OPEN_CURSOR,        // OPEN cursor
    FETCH_CURSOR,       // FETCH cursor
    CLOSE_CURSOR,       // CLOSE cursor

    // Triggers
    CREATE_TRIGGER,     // CREATE TRIGGER
    DROP_TRIGGER,       // DROP TRIGGER

    // Advanced DDL
    PARTITION_SPEC,     // Table partitioning specification
    CREATE_TABLESPACE,  // CREATE TABLESPACE
    CREATE_INDEX_ADV,   // Advanced CREATE INDEX (partial, expression, concurrent)

    // Other
    ALIAS,
    CAST,
    ANY_EXPR,           // ANY(subquery)
    ALL_EXPR,           // ALL(subquery)
};

/// Base expression node (use arena allocation)
struct Expression {
    ExprType type;

    explicit Expression(ExprType t) : type(t) {}
    virtual ~Expression() = default;

    // Factory methods (use arena)
    template<typename T, typename... Args>
    static T* create(Arena& arena, Args&&... args) {
        return arena.create<T>(std::forward<Args>(args)...);
    }
};

/// Literal value (string, number, null)
struct Literal : Expression {
    std::string value;

    explicit Literal(std::string v)
        : Expression(ExprType::LITERAL), value(std::move(v)) {}
};

/// Column reference (table.column or just column)
struct Column : Expression {
    std::string table;   // Optional table qualifier
    std::string column;

    Column(std::string t, std::string c)
        : Expression(ExprType::COLUMN), table(std::move(t)), column(std::move(c)) {}

    explicit Column(std::string c)
        : Expression(ExprType::COLUMN), column(std::move(c)) {}
};

/// SELECT * or table.*
struct Star : Expression {
    std::string table;  // Optional table qualifier

    Star() : Expression(ExprType::STAR) {}
    explicit Star(std::string t) : Expression(ExprType::STAR), table(std::move(t)) {}
};

/// Binary operation
struct BinaryOp : Expression {
    Expression* left;
    Expression* right;

    BinaryOp(ExprType op, Expression* l, Expression* r)
        : Expression(op), left(l), right(r) {}
};

/// Unary operation
struct UnaryOp : Expression {
    Expression* operand;

    UnaryOp(ExprType op, Expression* expr)
        : Expression(op), operand(expr) {}
};

/// Function call
struct FunctionCall : Expression {
    std::string name;
    std::vector<Expression*> args;
    bool distinct;

    FunctionCall(std::string n, std::vector<Expression*> a, bool d = false)
        : Expression(ExprType::FUNCTION_CALL), name(std::move(n)), args(std::move(a)), distinct(d) {}
};

/// Table reference
struct TableRef : Expression {
    std::string database;  // Optional
    std::string schema;    // Optional
    std::string table;
    std::string alias;     // Optional

    explicit TableRef(std::string t)
        : Expression(ExprType::TABLE_REF), table(std::move(t)) {}

    TableRef(std::string t, std::string a)
        : Expression(ExprType::TABLE_REF), table(std::move(t)), alias(std::move(a)) {}
};

/// JOIN clause
struct JoinClause : Expression {
    enum class JoinType { INNER, LEFT, RIGHT, FULL, CROSS };

    JoinType join_type;
    Expression* left_table;
    Expression* right_table;
    Expression* condition;  // ON condition

    JoinClause(JoinType jt, Expression* l, Expression* r, Expression* cond = nullptr)
        : Expression(ExprType::JOIN_CLAUSE), join_type(jt),
          left_table(l), right_table(r), condition(cond) {}
};

/// SELECT statement
struct SelectStmt : Expression {
    WithClause* with;                      // WITH clause (CTEs)
    std::vector<Expression*> columns;     // SELECT columns
    Expression* from;                      // FROM clause (table or join)
    Expression* where;                     // WHERE condition
    std::vector<Expression*> group_by;    // GROUP BY columns
    Expression* having;                    // HAVING condition
    Expression* qualify;                   // QUALIFY condition (window function filter)
    std::vector<Expression*> order_by;    // ORDER BY columns
    Expression* limit;                     // LIMIT expression
    Expression* offset;                    // OFFSET expression
    bool distinct;

    SelectStmt()
        : Expression(ExprType::SELECT_STMT), with(nullptr), from(nullptr), where(nullptr),
          having(nullptr), qualify(nullptr), limit(nullptr), offset(nullptr), distinct(false) {}
};

/// Aliased expression
struct Alias : Expression {
    Expression* expr;
    std::string alias;

    Alias(Expression* e, std::string a)
        : Expression(ExprType::ALIAS), expr(e), alias(std::move(a)) {}
};

/// Subquery expression
struct Subquery : Expression {
    SelectStmt* query;
    std::string alias;

    Subquery(SelectStmt* q, std::string a = "")
        : Expression(ExprType::SUBQUERY), query(q), alias(std::move(a)) {}
};

/// INSERT statement
struct InsertStmt : Expression {
    TableRef* table;                          // Target table
    std::vector<std::string> columns;         // Optional column list
    std::vector<std::vector<Expression*>> values;  // VALUES rows
    SelectStmt* select_stmt;                  // INSERT ... SELECT

    InsertStmt()
        : Expression(ExprType::INSERT_STMT), table(nullptr), select_stmt(nullptr) {}
};

/// UPDATE statement
struct UpdateStmt : Expression {
    TableRef* table;                          // Target table
    std::vector<std::pair<std::string, Expression*>> assignments;  // SET column = value
    Expression* where;                        // WHERE condition
    Expression* from;                         // FROM clause (for joins)

    UpdateStmt()
        : Expression(ExprType::UPDATE_STMT), table(nullptr), where(nullptr), from(nullptr) {}
};

/// DELETE statement
struct DeleteStmt : Expression {
    TableRef* table;                          // Target table
    Expression* where;                        // WHERE condition
    Expression* using_clause;                 // USING clause (for joins)

    DeleteStmt()
        : Expression(ExprType::DELETE_STMT), table(nullptr), where(nullptr), using_clause(nullptr) {}
};

/// Column definition (for CREATE TABLE)
struct ColumnDef {
    std::string name;
    std::string type;                         // Data type (VARCHAR, INTEGER, etc.)
    bool not_null = false;
    bool primary_key = false;
    bool unique = false;
    bool auto_increment = false;
    Expression* default_value = nullptr;
    std::string check_constraint;             // CHECK constraint expression
};

/// CREATE TABLE statement
struct CreateTableStmt : Expression {
    TableRef* table;                          // Target table
    std::vector<ColumnDef> columns;           // Column definitions
    std::vector<std::string> primary_keys;    // Primary key column(s)
    std::vector<std::pair<std::vector<std::string>, TableRef*>> foreign_keys;  // FK: (columns, ref_table)
    bool if_not_exists = false;
    SelectStmt* as_select = nullptr;          // CREATE TABLE AS SELECT

    CreateTableStmt()
        : Expression(ExprType::CREATE_TABLE_STMT), table(nullptr) {}
};

/// CREATE INDEX statement
struct CreateIndexStmt : Expression {
    std::string index_name;
    TableRef* table;                          // Target table
    std::vector<std::string> columns;         // Indexed columns
    bool unique = false;
    bool if_not_exists = false;

    CreateIndexStmt()
        : Expression(ExprType::CREATE_INDEX_STMT), table(nullptr) {}
};

/// DROP TABLE statement
struct DropTableStmt : Expression {
    TableRef* table;                          // Target table
    bool if_exists = false;
    bool cascade = false;

    DropTableStmt()
        : Expression(ExprType::DROP_TABLE_STMT), table(nullptr) {}
};

/// DROP INDEX statement
struct DropIndexStmt : Expression {
    std::string index_name;
    TableRef* table;                          // Optional table (dialect-specific)
    bool if_exists = false;

    DropIndexStmt()
        : Expression(ExprType::DROP_INDEX_STMT), table(nullptr) {}
};

/// ALTER TABLE operation type
enum class AlterOperation {
    ADD_COLUMN,
    DROP_COLUMN,
    MODIFY_COLUMN,
    RENAME_COLUMN,
    RENAME_TABLE,
    ADD_CONSTRAINT,
    DROP_CONSTRAINT
};

/// ALTER TABLE statement
struct AlterTableStmt : Expression {
    TableRef* table;                          // Target table
    AlterOperation operation;
    ColumnDef column_def;                     // For ADD/MODIFY COLUMN
    std::string old_name;                     // For RENAME
    std::string new_name;                     // For RENAME

    AlterTableStmt()
        : Expression(ExprType::ALTER_TABLE_STMT), table(nullptr) {}
};

/// Common Table Expression (CTE)
struct CTE : Expression {
    std::string name;
    std::vector<std::string> columns;         // Optional column list
    SelectStmt* query;

    CTE(std::string n, SelectStmt* q)
        : Expression(ExprType::CTE), name(std::move(n)), query(q) {}
};

/// WITH clause (contains multiple CTEs)
struct WithClause : Expression {
    std::vector<CTE*> ctes;
    bool recursive = false;

    WithClause()
        : Expression(ExprType::WITH_CLAUSE) {}
};

/// Window frame type
enum class FrameType {
    ROWS,
    RANGE,
    GROUPS
};

/// Window frame boundary
enum class FrameBound {
    UNBOUNDED_PRECEDING,
    UNBOUNDED_FOLLOWING,
    CURRENT_ROW,
    PRECEDING,              // N PRECEDING
    FOLLOWING               // N FOLLOWING
};

/// Window frame specification
struct FrameClause : Expression {
    FrameType frame_type;
    FrameBound start_bound;
    Expression* start_offset;                 // NULL for UNBOUNDED/CURRENT
    FrameBound end_bound;                     // Optional (single boundary means BETWEEN start AND CURRENT ROW)
    Expression* end_offset;

    FrameClause(FrameType ft, FrameBound sb)
        : Expression(ExprType::FRAME_CLAUSE), frame_type(ft), start_bound(sb),
          start_offset(nullptr), end_bound(FrameBound::CURRENT_ROW), end_offset(nullptr) {}
};

/// Window specification (OVER clause)
struct WindowSpec : Expression {
    std::vector<Expression*> partition_by;    // PARTITION BY columns
    std::vector<Expression*> order_by;        // ORDER BY columns
    FrameClause* frame;                       // ROWS/RANGE frame (optional)

    WindowSpec()
        : Expression(ExprType::WINDOW_SPEC), frame(nullptr) {}
};

/// Window function
struct WindowFunction : Expression {
    std::string function_name;                // ROW_NUMBER, RANK, LEAD, LAG, etc.
    std::vector<Expression*> args;            // Function arguments
    WindowSpec* over;                         // OVER clause

    WindowFunction(std::string fn, WindowSpec* w)
        : Expression(ExprType::WINDOW_FUNCTION), function_name(std::move(fn)), over(w) {}
};

// ============================================================================
// NEW FEATURES - Set Operations, Conditional Expressions, Predicates
// ============================================================================

/// Set operation (UNION, INTERSECT, EXCEPT)
struct SetOperation : Expression {
    enum class OpType { UNION, INTERSECT, EXCEPT };

    SelectStmt* left;
    SelectStmt* right;
    OpType op_type;
    bool all;

    SetOperation(SelectStmt* l, SelectStmt* r, OpType op, bool is_all = false)
        : Expression(op == OpType::UNION ? ExprType::UNION_STMT :
                     op == OpType::INTERSECT ? ExprType::INTERSECT_STMT :
                     ExprType::EXCEPT_STMT),
          left(l), right(r), op_type(op), all(is_all) {}
};

/// CASE expression
struct CaseExpr : Expression {
    struct WhenClause {
        Expression* condition;
        Expression* result;
    };

    Expression* case_value;                   // Optional CASE <expr> (for simple CASE)
    std::vector<WhenClause> when_clauses;     // WHEN conditions
    Expression* else_expr;                    // ELSE clause (optional)

    CaseExpr()
        : Expression(ExprType::CASE_EXPR), case_value(nullptr), else_expr(nullptr) {}
};

/// BETWEEN expression
struct BetweenExpr : Expression {
    Expression* expr;
    Expression* lower;
    Expression* upper;
    bool not_between = false;                 // NOT BETWEEN

    BetweenExpr(Expression* e, Expression* l, Expression* u, bool neg = false)
        : Expression(ExprType::BETWEEN), expr(e), lower(l), upper(u), not_between(neg) {}
};

/// IN expression
struct InExpr : Expression {
    Expression* expr;
    std::vector<Expression*> values;          // IN (val1, val2, ...) or subquery

    InExpr(Expression* e, std::vector<Expression*> vals)
        : Expression(ExprType::IN), expr(e), values(std::move(vals)) {}
};

/// EXISTS expression
struct ExistsExpr : Expression {
    SelectStmt* subquery;
    bool not_exists = false;

    ExistsExpr(SelectStmt* sq, bool neg = false)
        : Expression(ExprType::EXISTS), subquery(sq), not_exists(neg) {}
};

/// ANY/ALL expression
struct QuantifiedExpr : Expression {
    enum class QuantifierType { ANY, ALL, SOME };

    Expression* left;
    ExprType comparison_op;                   // <, >, =, etc.
    QuantifierType quantifier;
    SelectStmt* subquery;

    QuantifiedExpr(ExprType expr_type, Expression* l, ExprType op, QuantifierType q, SelectStmt* sq)
        : Expression(expr_type), left(l), comparison_op(op), quantifier(q), subquery(sq) {}
};

// ============================================================================
// NEW DDL STATEMENTS
// ============================================================================

/// CREATE VIEW statement
struct CreateViewStmt : Expression {
    std::string name;
    std::vector<std::string> columns;         // Optional column list
    SelectStmt* query;
    bool or_replace = false;
    bool if_not_exists = false;

    CreateViewStmt()
        : Expression(ExprType::CREATE_VIEW_STMT), query(nullptr) {}
};

/// DROP VIEW statement
struct DropViewStmt : Expression {
    std::string name;
    bool if_exists = false;
    bool cascade = false;

    DropViewStmt()
        : Expression(ExprType::DROP_VIEW_STMT) {}
};

/// CREATE SCHEMA/DATABASE statement
struct CreateSchemaStmt : Expression {
    std::string name;
    bool if_not_exists = false;

    CreateSchemaStmt()
        : Expression(ExprType::CREATE_SCHEMA_STMT) {}
};

/// CREATE DATABASE is an alias for CREATE SCHEMA
using CreateDatabaseStmt = CreateSchemaStmt;

/// DROP SCHEMA/DATABASE statement
struct DropSchemaStmt : Expression {
    std::string name;
    bool if_exists = false;
    bool cascade = false;

    DropSchemaStmt()
        : Expression(ExprType::DROP_SCHEMA_STMT) {}
};

/// TRUNCATE statement
struct TruncateStmt : Expression {
    std::string table;
    bool cascade = false;

    TruncateStmt()
        : Expression(ExprType::TRUNCATE_STMT) {}
};

/// MERGE statement (UPSERT)
struct MergeStmt : Expression {
    TableRef* target;
    Expression* source;
    Expression* on_condition;
    std::vector<std::pair<std::string, Expression*>> update_assignments;  // WHEN MATCHED UPDATE
    std::vector<std::string> insert_columns;                              // WHEN NOT MATCHED INSERT
    std::vector<Expression*> insert_values;

    MergeStmt()
        : Expression(ExprType::MERGE_STMT), target(nullptr),
          source(nullptr), on_condition(nullptr) {}
};

// ============================================================================
// TRANSACTION & UTILITY STATEMENTS
// ============================================================================

/// BEGIN/START TRANSACTION statement
struct BeginStmt : Expression {
    bool start_transaction = false;           // START TRANSACTION vs BEGIN

    BeginStmt()
        : Expression(ExprType::BEGIN_STMT) {}
};

/// COMMIT statement
struct CommitStmt : Expression {
    CommitStmt()
        : Expression(ExprType::COMMIT_STMT) {}
};

/// ROLLBACK statement
struct RollbackStmt : Expression {
    std::string savepoint_name;               // Optional ROLLBACK TO savepoint

    RollbackStmt()
        : Expression(ExprType::ROLLBACK_STMT) {}
};

/// SAVEPOINT statement
struct SavepointStmt : Expression {
    std::string name;

    SavepointStmt()
        : Expression(ExprType::SAVEPOINT_STMT) {}
};

/// SET statement
struct SetStmt : Expression {
    std::vector<std::pair<std::string, Expression*>> assignments;  // Variable assignments
    enum class Scope { SESSION, GLOBAL, LOCAL } scope = Scope::SESSION;

    SetStmt()
        : Expression(ExprType::SET_STMT) {}
};

/// SHOW statement
struct ShowStmt : Expression {
    std::string what;                         // What to show (TABLES, DATABASES, etc.)
    std::string target;                       // Optional target

    ShowStmt()
        : Expression(ExprType::SHOW_STMT) {}
};

/// DESCRIBE/DESC statement
struct DescribeStmt : Expression {
    std::string target;                       // Table name

    DescribeStmt()
        : Expression(ExprType::DESCRIBE_STMT) {}
};

/// EXPLAIN statement
struct ExplainStmt : Expression {
    enum class ExplainFormat { TRADITIONAL, JSON, TREE };

    ExplainFormat format = ExplainFormat::TRADITIONAL;
    bool analyze = false;
    Expression* statement;                    // The statement to explain

    ExplainStmt()
        : Expression(ExprType::EXPLAIN_STMT), statement(nullptr) {}
};

// ============================================================================
// ADVANCED FEATURES
// ============================================================================

/// VALUES clause (standalone table constructor)
struct ValuesClause : Expression {
    std::vector<std::vector<Expression*>> rows;

    ValuesClause()
        : Expression(ExprType::VALUES_CLAUSE) {}
};

/// LATERAL join
struct LateralJoin : Expression {
    Expression* table_expr;                   // Can be subquery or table function

    LateralJoin(Expression* expr)
        : Expression(ExprType::LATERAL_JOIN), table_expr(expr) {}
};

/// Array literal [1, 2, 3]
struct ArrayLiteral : Expression {
    std::vector<Expression*> elements;

    ArrayLiteral(std::vector<Expression*> elems = {})
        : Expression(ExprType::ARRAY_LITERAL), elements(std::move(elems)) {}
};

/// Array indexing array[index]
struct ArrayIndex : Expression {
    Expression* array;
    Expression* index;

    ArrayIndex(Expression* arr, Expression* idx)
        : Expression(ExprType::ARRAY_INDEX), array(arr), index(idx) {}
};

/// JSON operations (JSON_EXTRACT, etc.)
struct JsonExpr : Expression {
    enum class OpType { ARROW, LONG_ARROW, HASH_ARROW, HASH_LONG_ARROW };

    Expression* json_expr;
    Expression* key;
    OpType op_type;

    JsonExpr(Expression* expr, Expression* k, OpType op)
        : Expression(ExprType::JSON_EXTRACT), json_expr(expr), key(k), op_type(op) {}
};

/// Regex match (REGEXP, RLIKE)
struct RegexMatch : Expression {
    Expression* expr;
    Expression* pattern;
    bool similar_to = false;                  // SIMILAR TO vs REGEXP/RLIKE

    RegexMatch(Expression* e, Expression* pat, bool sim = false)
        : Expression(ExprType::REGEX_MATCH), expr(e), pattern(pat), similar_to(sim) {}
};

/// PIVOT clause
struct PivotClause : Expression {
    Expression* table_expr;                   // Base table or subquery
    FunctionCall* aggregate;                  // Aggregate function (e.g., SUM(amount))
    Expression* pivot_column;                 // Column to pivot on (e.g., quarter)
    std::vector<Expression*> pivot_values;    // Values to pivot (e.g., 'Q1', 'Q2', 'Q3')
    std::string alias;                        // Optional alias

    PivotClause()
        : Expression(ExprType::PIVOT_CLAUSE), table_expr(nullptr), aggregate(nullptr), pivot_column(nullptr) {}
};

/// UNPIVOT clause
struct UnpivotClause : Expression {
    Expression* table_expr;                   // Base table or subquery
    std::string value_column;                 // Column to hold unpivoted values
    std::string name_column;                  // Column to hold column names
    std::vector<std::string> unpivot_columns; // Columns to unpivot
    std::string alias;                        // Optional alias

    UnpivotClause()
        : Expression(ExprType::UNPIVOT_CLAUSE), table_expr(nullptr) {}
};

/// TABLESAMPLE clause
struct Tablesample : Expression {
    enum class SampleMethod { BERNOULLI, SYSTEM };

    SampleMethod method;
    Expression* percent;                      // Sample percentage
    Expression* seed;                         // Optional random seed

    Tablesample(SampleMethod m, Expression* p)
        : Expression(ExprType::TABLESAMPLE), method(m), percent(p), seed(nullptr) {}
};

/// QUALIFY clause (filter window functions)
struct QualifyClause : Expression {
    Expression* condition;

    QualifyClause(Expression* cond)
        : Expression(ExprType::QUALIFY_CLAUSE), condition(cond) {}
};

// ============================================================================
// STORED PROCEDURES & FUNCTIONS
// ============================================================================

/// Procedure/Function parameter
struct ProcedureParam {
    enum class Mode { IN, OUT, INOUT } mode = Mode::IN;
    std::string name;
    std::string type;
    Expression* default_value = nullptr;
};

/// CREATE PROCEDURE/FUNCTION statement
struct CreateProcedureStmt : Expression {
    bool is_function = false;           // true for CREATE FUNCTION
    std::string name;
    std::vector<ProcedureParam> parameters;
    std::string return_type;            // For functions
    std::string language;               // plpgsql, tsql, sql, etc.
    std::vector<Expression*> declarations;  // DECLARE statements
    std::vector<Expression*> body;      // Procedure body statements
    bool or_replace = false;

    CreateProcedureStmt()
        : Expression(ExprType::CREATE_PROCEDURE) {}
};

/// DROP PROCEDURE/FUNCTION statement
struct DropProcedureStmt : Expression {
    bool is_function = false;
    std::string name;
    bool if_exists = false;
    bool cascade = false;

    DropProcedureStmt()
        : Expression(ExprType::DROP_PROCEDURE) {}
};

/// CALL procedure statement
struct CallProcedureStmt : Expression {
    std::string name;
    std::vector<Expression*> arguments;

    CallProcedureStmt()
        : Expression(ExprType::CALL_PROCEDURE) {}
};

/// DECLARE variable statement
struct DeclareStmt : Expression {
    std::string variable_name;
    std::string type;
    Expression* default_value = nullptr;

    DeclareStmt()
        : Expression(ExprType::DECLARE_VAR), default_value(nullptr) {}
};

/// IF statement
struct IfStmt : Expression {
    struct ElseIfBranch {
        Expression* condition;
        std::vector<Expression*> statements;
    };

    Expression* condition;                    // IF condition
    std::vector<Expression*> then_stmts;      // THEN statements
    std::vector<ElseIfBranch> elseif_branches; // ELSEIF branches
    std::vector<Expression*> else_stmts;      // ELSE statements

    IfStmt()
        : Expression(ExprType::IF_STMT), condition(nullptr) {}
};

/// WHILE loop
struct WhileLoop : Expression {
    Expression* condition;
    std::vector<Expression*> body;

    WhileLoop()
        : Expression(ExprType::WHILE_LOOP), condition(nullptr) {}
};

/// FOR loop
struct ForLoop : Expression {
    std::string variable;
    Expression* start_value;
    Expression* end_value;
    std::vector<Expression*> body;

    ForLoop()
        : Expression(ExprType::FOR_LOOP), start_value(nullptr), end_value(nullptr) {}
};

/// RETURN statement
struct ReturnStmt : Expression {
    Expression* return_value;

    ReturnStmt(Expression* val = nullptr)
        : Expression(ExprType::RETURN_STMT), return_value(val) {}
};

/// BEGIN...END block (T-SQL, MySQL, PL/SQL style)
struct BeginEndBlock : Expression {
    std::vector<Expression*> statements;

    BeginEndBlock()
        : Expression(ExprType::BEGIN_END_BLOCK) {}
};

/// EXCEPTION block (PL/pgSQL, PL/SQL)
struct ExceptionBlock : Expression {
    struct ExceptionHandler {
        std::string exception_name;               // Exception name (e.g., "no_data_found")
        std::vector<Expression*> statements;      // Handler statements
    };

    std::vector<Expression*> try_statements;      // Statements in try block
    std::vector<ExceptionHandler> handlers;       // Exception handlers

    ExceptionBlock()
        : Expression(ExprType::EXCEPTION_BLOCK) {}
};

/// Assignment statement (SET var = val, var := val)
struct AssignmentStmt : Expression {
    std::string variable_name;
    Expression* value;
    bool use_colon_equals = false;                // true for :=, false for SET ... =

    AssignmentStmt()
        : Expression(ExprType::ASSIGNMENT_STMT), value(nullptr) {}
};

/// DELIMITER statement (MySQL)
struct DelimiterStmt : Expression {
    std::string delimiter;                        // New delimiter (e.g., "$$", "//")

    DelimiterStmt()
        : Expression(ExprType::DELIMITER_STMT) {}
};

/// RAISE/SIGNAL statement (error handling)
struct RaiseStmt : Expression {
    enum class Level { EXCEPTION, NOTICE, WARNING, INFO, LOG, DEBUG } level = Level::EXCEPTION;
    std::string error_code;                       // SQL state code (e.g., "23505")
    std::string message;                          // Error message
    std::vector<Expression*> arguments;           // Message arguments

    RaiseStmt()
        : Expression(ExprType::RAISE_STMT) {}
};

/// DECLARE CURSOR statement
struct DeclareCursorStmt : Expression {
    std::string cursor_name;
    SelectStmt* query;                            // Cursor query
    bool scroll = false;                          // SCROLL cursor

    DeclareCursorStmt()
        : Expression(ExprType::DECLARE_CURSOR), query(nullptr) {}
};

/// OPEN cursor statement
struct OpenCursorStmt : Expression {
    std::string cursor_name;
    std::vector<Expression*> arguments;           // For parameterized cursors

    OpenCursorStmt()
        : Expression(ExprType::OPEN_CURSOR) {}
};

/// FETCH cursor statement
struct FetchCursorStmt : Expression {
    enum class Direction { NEXT, PRIOR, FIRST, LAST, ABSOLUTE, RELATIVE } direction = Direction::NEXT;
    Expression* count = nullptr;                  // For ABSOLUTE/RELATIVE
    std::string cursor_name;
    std::vector<std::string> into_variables;      // INTO variable list

    FetchCursorStmt()
        : Expression(ExprType::FETCH_CURSOR) {}
};

/// CLOSE cursor statement
struct CloseCursorStmt : Expression {
    std::string cursor_name;

    CloseCursorStmt()
        : Expression(ExprType::CLOSE_CURSOR) {}
};

// ============================================================================
// TRIGGERS
// ============================================================================

/// CREATE TRIGGER statement
struct CreateTriggerStmt : Expression {
    enum class Timing { BEFORE, AFTER, INSTEAD_OF };
    enum class Event { INSERT, UPDATE, DELETE };

    std::string name;
    std::string table;
    Timing timing;
    Event event;
    bool for_each_row = false;
    std::vector<std::string> update_columns;  // For UPDATE OF col1, col2, ...
    Expression* when_condition = nullptr;     // WHEN (condition)
    std::vector<Expression*> body;            // Trigger body or function name

    CreateTriggerStmt()
        : Expression(ExprType::CREATE_TRIGGER) {}
};

/// DROP TRIGGER statement
struct DropTriggerStmt : Expression {
    std::string name;
    std::string table;  // Optional in some dialects
    bool if_exists = false;
    bool cascade = false;

    DropTriggerStmt()
        : Expression(ExprType::DROP_TRIGGER) {}
};

// ============================================================================
// ADVANCED DDL
// ============================================================================

/// Partition type
enum class PartitionType {
    RANGE,      // PARTITION BY RANGE (column)
    LIST,       // PARTITION BY LIST (column)
    HASH        // PARTITION BY HASH (column)
};

/// Partition definition
struct PartitionDef {
    std::string name;
    std::string tablespace;
    Expression* values;  // Range or list values
};

/// Partition specification
struct PartitionSpec : Expression {
    PartitionType type;
    std::vector<std::string> columns;
    std::vector<PartitionDef> partitions;

    PartitionSpec()
        : Expression(ExprType::PARTITION_SPEC) {}
};

/// CREATE TABLESPACE statement
struct CreateTablespaceStmt : Expression {
    std::string name;
    std::string location;

    CreateTablespaceStmt()
        : Expression(ExprType::CREATE_TABLESPACE) {}
};

/// Advanced CREATE INDEX statement
struct CreateIndexAdvStmt : Expression {
    std::string index_name;
    std::string table;
    std::vector<Expression*> columns;  // Can be expressions, not just column names
    bool unique = false;
    bool concurrently = false;
    bool if_not_exists = false;
    Expression* where_clause = nullptr;  // Partial index: WHERE condition
    std::string using_method;            // btree, hash, gist, gin, etc.
    std::string tablespace;

    CreateIndexAdvStmt()
        : Expression(ExprType::CREATE_INDEX_ADV), where_clause(nullptr) {}
};

} // namespace libsqlglot
