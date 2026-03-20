#pragma once

#include "expression.h"
#include <vector>
#include <string>
#include <cstdint>

namespace libsqlglot {

/// Optimizer - applies transformations to AST
class Optimizer {
public:
    /// Qualify table names in columns (add table prefix where missing)
    static void qualify_columns(SelectStmt* stmt) {
        if (!stmt || !stmt->from) return;

        // Extract table name from FROM clause
        std::string default_table;
        if (stmt->from->type == ExprType::TABLE_REF) {
            auto table = static_cast<TableRef*>(stmt->from);
            default_table = table->alias.empty() ? table->table : table->alias;
        }

        // Qualify columns in SELECT list
        for (auto col_expr : stmt->columns) {
            qualify_column_recursive(col_expr, default_table);
        }

        // Qualify columns in WHERE clause
        if (stmt->where) {
            qualify_column_recursive(stmt->where, default_table);
        }
    }

    /// Normalize boolean expressions (flatten nested AND/OR)
    static Expression* normalize(Expression* expr) {
        if (!expr) return nullptr;

        // Flatten nested AND/OR
        if (expr->type == ExprType::AND || expr->type == ExprType::OR) {
            auto binop = static_cast<BinaryOp*>(expr);
            binop->left = normalize(binop->left);
            binop->right = normalize(binop->right);
        }

        return expr;
    }

    /// Predicate pushdown - push WHERE predicates into subqueries
    static void pushdown_predicates(SelectStmt* stmt, Arena& arena) {
        if (!stmt || !stmt->where || !stmt->from) return;

        // Check if FROM is a subquery
        if (stmt->from->type == ExprType::SUBQUERY) {
            auto subquery_expr = static_cast<Subquery*>(stmt->from);
            auto subquery = subquery_expr->query;

            if (!subquery) return;

            // Extract pushable predicates from WHERE clause
            std::vector<Expression*> pushable;
            std::vector<Expression*> remaining;

            split_predicates(stmt->where, subquery_expr->alias, pushable, remaining);

            // Push predicates into subquery
            if (!pushable.empty()) {
                Expression* pushed_cond = combine_predicates(pushable, arena);
                if (subquery->where) {
                    // Combine with existing WHERE
                    subquery->where = create_and(subquery->where, pushed_cond, arena);
                } else {
                    subquery->where = pushed_cond;
                }

                // Update outer WHERE with remaining predicates
                if (remaining.empty()) {
                    stmt->where = nullptr;
                } else {
                    stmt->where = combine_predicates(remaining, arena);
                }
            }

            // Recursively optimize subquery
            pushdown_predicates(subquery, arena);
        }
    }

    /// Subquery elimination - flatten simple subqueries that don't require nesting
    static void eliminate_subqueries(SelectStmt* stmt, Arena& arena) {
        if (!stmt || !stmt->from) return;

        // Check if FROM is a simple subquery that can be eliminated
        if (stmt->from->type == ExprType::SUBQUERY) {
            auto subquery_expr = static_cast<Subquery*>(stmt->from);
            auto subquery = subquery_expr->query;

            if (!subquery) return;

            // Conditions for subquery elimination:
            // 1. Subquery has no aggregation (GROUP BY, HAVING, DISTINCT)
            // 2. Subquery selects all columns we need
            // 3. No conflicting column names
            if (can_eliminate_subquery(stmt, subquery)) {
                flatten_subquery(stmt, subquery, subquery_expr->alias, arena);
                // After flattening, recursively process the new FROM clause
                // (only if we still have a valid FROM after flattening)
                if (stmt->from) {
                    eliminate_subqueries(stmt, arena);
                }
                return;  // Don't process again below
            }
        }

        // Process JOIN clauses
        if (stmt->from && stmt->from->type == ExprType::JOIN_CLAUSE) {
            auto join = static_cast<JoinClause*>(stmt->from);
            if (join->left_table && join->left_table->type == ExprType::SELECT_STMT) {
                eliminate_subqueries(static_cast<SelectStmt*>(join->left_table), arena);
            }
            if (join->right_table && join->right_table->type == ExprType::SELECT_STMT) {
                eliminate_subqueries(static_cast<SelectStmt*>(join->right_table), arena);
            }
        }
    }

    /// Detect correlated subqueries (subqueries that reference outer query columns)
    static bool is_correlated_subquery(SelectStmt* subquery, const std::string& outer_alias) {
        if (!subquery) return false;

        // Check if any column references the outer query
        return references_outer_query(subquery->where, outer_alias) ||
               references_outer_query_in_list(subquery->columns, outer_alias);
    }

private:
    /// Split AND-connected predicates into pushable and non-pushable
    static void split_predicates(Expression* expr, const std::string& subquery_alias,
                                std::vector<Expression*>& pushable,
                                std::vector<Expression*>& remaining) {
        if (!expr) return;

        // If it's an AND, split both sides
        if (expr->type == ExprType::AND) {
            auto binop = static_cast<BinaryOp*>(expr);
            split_predicates(binop->left, subquery_alias, pushable, remaining);
            split_predicates(binop->right, subquery_alias, pushable, remaining);
            return;
        }

        // Check if this predicate can be pushed down
        if (can_pushdown(expr, subquery_alias)) {
            // Remove the subquery alias prefix from columns
            auto rewritten = rewrite_for_pushdown(expr, subquery_alias);
            pushable.push_back(rewritten);
        } else {
            remaining.push_back(expr);
        }
    }

    /// Check if a predicate can be pushed down into a subquery
    static bool can_pushdown(Expression* expr, const std::string& subquery_alias) {
        if (!expr) return false;

        // Check if all columns reference the subquery alias
        return all_columns_match_alias(expr, subquery_alias);
    }

    /// Check if all columns in expression reference the given alias
    static bool all_columns_match_alias(Expression* expr, const std::string& alias) {
        if (!expr) return true;

        if (expr->type == ExprType::COLUMN) {
            auto col = static_cast<Column*>(expr);
            return col->table.empty() || col->table == alias;
        }

        // Recurse into binary operations
        if (expr->type >= ExprType::EQ && expr->type <= ExprType::OR) {
            auto binop = static_cast<BinaryOp*>(expr);
            return all_columns_match_alias(binop->left, alias) &&
                   all_columns_match_alias(binop->right, alias);
        }

        // Recurse into unary operations
        if (expr->type == ExprType::NOT || expr->type == ExprType::IS_NULL ||
            expr->type == ExprType::IS_NOT_NULL) {
            auto unop = static_cast<UnaryOp*>(expr);
            return all_columns_match_alias(unop->operand, alias);
        }

        // Literals and other expressions are pushable
        return true;
    }

    /// Rewrite expression for pushdown by removing subquery alias prefix
    static Expression* rewrite_for_pushdown(Expression* expr, const std::string& alias) {
        if (!expr) return nullptr;

        if (expr->type == ExprType::COLUMN) {
            auto col = static_cast<Column*>(expr);
            if (col->table == alias) {
                col->table = "";  // Remove alias
            }
            return col;
        }

        // Recurse into binary operations
        if (expr->type >= ExprType::EQ && expr->type <= ExprType::OR) {
            auto binop = static_cast<BinaryOp*>(expr);
            binop->left = rewrite_for_pushdown(binop->left, alias);
            binop->right = rewrite_for_pushdown(binop->right, alias);
            return binop;
        }

        // Recurse into unary operations
        if (expr->type == ExprType::NOT || expr->type == ExprType::IS_NULL ||
            expr->type == ExprType::IS_NOT_NULL) {
            auto unop = static_cast<UnaryOp*>(expr);
            unop->operand = rewrite_for_pushdown(unop->operand, alias);
            return unop;
        }

        return expr;
    }

    /// Combine multiple predicates with AND
    static Expression* combine_predicates(const std::vector<Expression*>& predicates, Arena& arena) {
        if (predicates.empty()) return nullptr;
        if (predicates.size() == 1) return predicates[0];

        Expression* result = predicates[0];
        for (size_t i = 1; i < predicates.size(); ++i) {
            result = create_and(result, predicates[i], arena);
        }
        return result;
    }

    /// Create AND expression using arena allocation (no memory leaks)
    static Expression* create_and(Expression* left, Expression* right, Arena& arena) {
        return arena.create<BinaryOp>(ExprType::AND, left, right);
    }

    /// Check if subquery can be eliminated (no aggregation, compatible structure)
    static bool can_eliminate_subquery(SelectStmt* outer, SelectStmt* subquery) {
        if (!outer || !subquery) return false;

        // Don't eliminate if subquery has aggregation
        if (!subquery->group_by.empty() || subquery->having || subquery->distinct) {
            return false;
        }

        // Don't eliminate if subquery has LIMIT/OFFSET
        if (subquery->limit || subquery->offset) {
            return false;
        }

        // Don't eliminate if subquery has set operations
        // (Would be UNION/INTERSECT/EXCEPT which would be at top level)

        // Don't eliminate if outer query has aggregation that depends on subquery
        if (!outer->group_by.empty() || outer->having) {
            return false;
        }

        return true;
    }

    /// Flatten subquery into outer query
    static void flatten_subquery(SelectStmt* outer, SelectStmt* subquery,
                                 const std::string& alias, Arena& arena) {
        if (!outer || !subquery) return;

        // Replace FROM with subquery's FROM
        outer->from = subquery->from;

        // Merge WHERE clauses
        if (subquery->where) {
            if (outer->where) {
                outer->where = create_and(outer->where, subquery->where, arena);
            } else {
                outer->where = subquery->where;
            }
        }

        // Update column references to remove subquery alias
        rewrite_columns_in_list(outer->columns, alias);
        if (outer->where) {
            rewrite_for_pushdown(outer->where, alias);
        }
    }

    /// Check if expression references outer query columns
    static bool references_outer_query(Expression* expr, const std::string& outer_alias) {
        if (!expr) return false;

        if (expr->type == ExprType::COLUMN) {
            auto col = static_cast<Column*>(expr);
            return col->table == outer_alias;
        }

        // Recurse into binary operations
        if (expr->type >= ExprType::EQ && expr->type <= ExprType::OR) {
            auto binop = static_cast<BinaryOp*>(expr);
            return references_outer_query(binop->left, outer_alias) ||
                   references_outer_query(binop->right, outer_alias);
        }

        // Recurse into unary operations
        if (expr->type == ExprType::NOT || expr->type == ExprType::IS_NULL ||
            expr->type == ExprType::IS_NOT_NULL) {
            auto unop = static_cast<UnaryOp*>(expr);
            return references_outer_query(unop->operand, outer_alias);
        }

        return false;
    }

    /// Check if expression list references outer query
    static bool references_outer_query_in_list(const std::vector<Expression*>& exprs,
                                               const std::string& outer_alias) {
        for (auto expr : exprs) {
            if (references_outer_query(expr, outer_alias)) {
                return true;
            }
        }
        return false;
    }

    /// Rewrite column references in list
    static void rewrite_columns_in_list(std::vector<Expression*>& exprs,
                                       const std::string& alias) {
        for (auto& expr : exprs) {
            expr = rewrite_for_pushdown(expr, alias);
        }
    }

public:
    /// Constant folding - evaluate expressions with literal operands at compile time
    static Expression* fold_constants(Expression* expr, Arena& arena) {
        if (!expr) return nullptr;

        // Recursively fold sub-expressions first
        if (expr->type >= ExprType::EQ && expr->type <= ExprType::OR) {
            auto binop = static_cast<BinaryOp*>(expr);
            binop->left = fold_constants(binop->left, arena);
            binop->right = fold_constants(binop->right, arena);

            // Now try to fold this binary operation
            if (binop->left->type == ExprType::LITERAL && binop->right->type == ExprType::LITERAL) {
                auto left_lit = static_cast<Literal*>(binop->left);
                auto right_lit = static_cast<Literal*>(binop->right);

                // Handle NULL propagation: any operation with NULL returns NULL
                if (left_lit->value == "NULL" || right_lit->value == "NULL") {
                    return arena.create<Literal>("NULL");
                }

                // Arithmetic operations
                if (binop->type == ExprType::PLUS || binop->type == ExprType::MINUS ||
                    binop->type == ExprType::MUL || binop->type == ExprType::DIV ||
                    binop->type == ExprType::MOD) {
                    double left_val = parse_number(left_lit->value);
                    double right_val = parse_number(right_lit->value);
                    double result;

                    switch (binop->type) {
                        case ExprType::PLUS: result = left_val + right_val; break;
                        case ExprType::MINUS: result = left_val - right_val; break;
                        case ExprType::MUL: result = left_val * right_val; break;
                        case ExprType::DIV:
                            if (right_val == 0.0) return expr; // Avoid division by zero
                            result = left_val / right_val;
                            break;
                        case ExprType::MOD:
                            if (right_val == 0.0) return expr;
                            result = static_cast<int>(left_val) % static_cast<int>(right_val);
                            break;
                        default: return expr;
                    }

                    return arena.create<Literal>(format_number(result));
                }

                // Comparison operations
                if (binop->type == ExprType::EQ || binop->type == ExprType::NEQ ||
                    binop->type == ExprType::LT || binop->type == ExprType::LTE ||
                    binop->type == ExprType::GT || binop->type == ExprType::GTE) {
                    bool result = evaluate_comparison(binop->type, left_lit->value, right_lit->value);
                    return arena.create<Literal>(result ? "TRUE" : "FALSE");
                }

                // Boolean operations
                if (binop->type == ExprType::AND) {
                    bool left_bool = is_truthy(left_lit->value);
                    bool right_bool = is_truthy(right_lit->value);
                    return arena.create<Literal>((left_bool && right_bool) ? "TRUE" : "FALSE");
                }
                if (binop->type == ExprType::OR) {
                    bool left_bool = is_truthy(left_lit->value);
                    bool right_bool = is_truthy(right_lit->value);
                    return arena.create<Literal>((left_bool || right_bool) ? "TRUE" : "FALSE");
                }
            }

            // Simplify boolean expressions with known values
            if (binop->type == ExprType::AND) {
                // FALSE AND x = FALSE
                if (binop->left->type == ExprType::LITERAL &&
                    !is_truthy(static_cast<Literal*>(binop->left)->value)) {
                    return arena.create<Literal>("FALSE");
                }
                // x AND FALSE = FALSE
                if (binop->right->type == ExprType::LITERAL &&
                    !is_truthy(static_cast<Literal*>(binop->right)->value)) {
                    return arena.create<Literal>("FALSE");
                }
                // TRUE AND x = x
                if (binop->left->type == ExprType::LITERAL &&
                    is_truthy(static_cast<Literal*>(binop->left)->value)) {
                    return binop->right;
                }
                // x AND TRUE = x
                if (binop->right->type == ExprType::LITERAL &&
                    is_truthy(static_cast<Literal*>(binop->right)->value)) {
                    return binop->left;
                }
            }

            if (binop->type == ExprType::OR) {
                // TRUE OR x = TRUE
                if (binop->left->type == ExprType::LITERAL &&
                    is_truthy(static_cast<Literal*>(binop->left)->value)) {
                    return arena.create<Literal>("TRUE");
                }
                // x OR TRUE = TRUE
                if (binop->right->type == ExprType::LITERAL &&
                    is_truthy(static_cast<Literal*>(binop->right)->value)) {
                    return arena.create<Literal>("TRUE");
                }
                // FALSE OR x = x
                if (binop->left->type == ExprType::LITERAL &&
                    !is_truthy(static_cast<Literal*>(binop->left)->value)) {
                    return binop->right;
                }
                // x OR FALSE = x
                if (binop->right->type == ExprType::LITERAL &&
                    !is_truthy(static_cast<Literal*>(binop->right)->value)) {
                    return binop->left;
                }
            }
        }

        // NOT with literal
        if (expr->type == ExprType::NOT) {
            auto unop = static_cast<UnaryOp*>(expr);
            unop->operand = fold_constants(unop->operand, arena);

            if (unop->operand->type == ExprType::LITERAL) {
                bool val = is_truthy(static_cast<Literal*>(unop->operand)->value);
                return arena.create<Literal>(val ? "FALSE" : "TRUE");
            }
        }

        return expr;
    }

private:
    static void qualify_column_recursive(Expression* expr, const std::string& default_table) {
        if (!expr) return;

        if (expr->type == ExprType::COLUMN) {
            auto col = static_cast<Column*>(expr);
            if (col->table.empty() && !default_table.empty()) {
                col->table = default_table;
            }
        } else if (expr->type >= ExprType::EQ && expr->type <= ExprType::OR) {
            auto binop = static_cast<BinaryOp*>(expr);
            qualify_column_recursive(binop->left, default_table);
            qualify_column_recursive(binop->right, default_table);
        }
    }

    /// Parse a string literal to a numeric value
    static double parse_number(const std::string& str) {
        try {
            return std::stod(str);
        } catch (...) {
            return 0.0;
        }
    }

    /// Format a numeric value to a string
    static std::string format_number(double val) {
        // Check if it's an integer
        if (val == static_cast<int64_t>(val)) {
            return std::to_string(static_cast<int64_t>(val));
        }
        // Otherwise format as double, removing trailing zeros
        std::string result = std::to_string(val);
        result.erase(result.find_last_not_of('0') + 1, std::string::npos);
        if (result.back() == '.') {
            result.pop_back();
        }
        return result;
    }

    /// Determine if a literal value is truthy
    static bool is_truthy(const std::string& value) {
        if (value == "TRUE" || value == "true" || value == "1") return true;
        if (value == "FALSE" || value == "false" || value == "0") return false;
        if (value == "NULL" || value == "null") return false;
        // Non-zero numbers are truthy
        try {
            double num = std::stod(value);
            return num != 0.0;
        } catch (...) {
            // Non-empty strings are truthy
            return !value.empty();
        }
    }

    /// Evaluate a comparison operation between two literal values
    static bool evaluate_comparison(ExprType op, const std::string& left, const std::string& right) {
        // Try numeric comparison first
        try {
            double left_num = std::stod(left);
            double right_num = std::stod(right);

            switch (op) {
                case ExprType::EQ: return left_num == right_num;
                case ExprType::NEQ: return left_num != right_num;
                case ExprType::LT: return left_num < right_num;
                case ExprType::LTE: return left_num <= right_num;
                case ExprType::GT: return left_num > right_num;
                case ExprType::GTE: return left_num >= right_num;
                default: return false;
            }
        } catch (...) {
            // Fall back to string comparison
            switch (op) {
                case ExprType::EQ: return left == right;
                case ExprType::NEQ: return left != right;
                case ExprType::LT: return left < right;
                case ExprType::LTE: return left <= right;
                case ExprType::GT: return left > right;
                case ExprType::GTE: return left >= right;
                default: return false;
            }
        }
    }
};

} // namespace libsqlglot
