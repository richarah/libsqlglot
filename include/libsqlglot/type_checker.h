#pragma once

#include "expression.h"
#include "schema.h"
#include <stdexcept>
#include <string>
#include <sstream>

namespace libsqlglot {

/// Type checking error
class TypeCheckError : public std::runtime_error {
public:
    explicit TypeCheckError(const std::string& msg) : std::runtime_error(msg) {}
};

/// Type inference and validation
class TypeChecker {
public:
    explicit TypeChecker(const SchemaCatalog& catalog) : catalog_(catalog) {}

    /// Infer the data type of an expression
    DataType infer_type(Expression* expr) {
        if (!expr) return DataType::NULL_TYPE;

        switch (expr->type) {
            case ExprType::LITERAL:
                return infer_literal_type(static_cast<Literal*>(expr));

            case ExprType::COLUMN:
                return infer_column_type(static_cast<Column*>(expr));

            case ExprType::PLUS:
            case ExprType::MINUS:
            case ExprType::MUL:
            case ExprType::DIV:
            case ExprType::MOD:
                return infer_arithmetic_type(static_cast<BinaryOp*>(expr));

            case ExprType::EQ:
            case ExprType::NEQ:
            case ExprType::LT:
            case ExprType::LTE:
            case ExprType::GT:
            case ExprType::GTE:
            case ExprType::AND:
            case ExprType::OR:
                return DataType::BOOLEAN;

            case ExprType::NOT:
            case ExprType::IS_NULL:
            case ExprType::IS_NOT_NULL:
                return DataType::BOOLEAN;

            case ExprType::AGG_COUNT:
                return DataType::BIGINT;

            case ExprType::AGG_SUM:
            case ExprType::AGG_AVG:
                return infer_aggregate_type(static_cast<FunctionCall*>(expr));

            case ExprType::AGG_MIN:
            case ExprType::AGG_MAX:
                // MIN/MAX preserve input type
                return infer_aggregate_type(static_cast<FunctionCall*>(expr));

            case ExprType::FUNCTION_CALL:
                return infer_function_type(static_cast<FunctionCall*>(expr));

            default:
                return DataType::UNKNOWN;
        }
    }

    /// Validate type compatibility for an expression
    void validate_expression(Expression* expr) {
        if (!expr) return;

        switch (expr->type) {
            case ExprType::PLUS:
            case ExprType::MINUS:
            case ExprType::MUL:
            case ExprType::DIV:
            case ExprType::MOD:
                validate_arithmetic(static_cast<BinaryOp*>(expr));
                break;

            case ExprType::EQ:
            case ExprType::NEQ:
            case ExprType::LT:
            case ExprType::LTE:
            case ExprType::GT:
            case ExprType::GTE:
                validate_comparison(static_cast<BinaryOp*>(expr));
                break;

            case ExprType::AND:
            case ExprType::OR:
                validate_boolean_logic(static_cast<BinaryOp*>(expr));
                break;

            default:
                break;
        }
    }

    /// Validate SELECT statement
    void validate_select(SelectStmt* stmt) {
        if (!stmt) return;

        // Validate all column expressions
        for (auto expr : stmt->columns) {
            validate_expression(expr);
        }

        // Validate WHERE clause
        if (stmt->where) {
            validate_expression(stmt->where);
            DataType where_type = infer_type(stmt->where);
            if (where_type != DataType::BOOLEAN && where_type != DataType::UNKNOWN) {
                throw TypeCheckError("WHERE clause must have boolean type");
            }
        }

        // Validate HAVING clause
        if (stmt->having) {
            validate_expression(stmt->having);
            DataType having_type = infer_type(stmt->having);
            if (having_type != DataType::BOOLEAN && having_type != DataType::UNKNOWN) {
                throw TypeCheckError("HAVING clause must have boolean type");
            }
        }

        // Validate GROUP BY expressions
        for (auto expr : stmt->group_by) {
            validate_expression(expr);
        }

        // Validate ORDER BY expressions
        for (auto expr : stmt->order_by) {
            validate_expression(expr);
        }
    }

private:
    const SchemaCatalog& catalog_;

    /// Infer type of literal
    DataType infer_literal_type(Literal* lit) {
        const std::string& value = lit->value;

        if (value.empty()) return DataType::NULL_TYPE;

        if (value == "NULL") return DataType::NULL_TYPE;
        if (value == "TRUE" || value == "FALSE" || value == "true" || value == "false") {
            return DataType::BOOLEAN;
        }

        // String literal (starts with ' or ")
        if (value[0] == '\'' || value[0] == '"') return DataType::VARCHAR;

        // Check if it's a number
        bool has_dot = false;
        bool has_e = false;
        bool is_number = true;

        for (size_t i = 0; i < value.size(); ++i) {
            char c = value[i];

            // Allow leading +/- sign
            if (i == 0 && (c == '+' || c == '-')) continue;

            // Check for decimal point
            if (c == '.') {
                if (has_dot) {  // Multiple dots = not a number
                    is_number = false;
                    break;
                }
                has_dot = true;
                continue;
            }

            // Check for scientific notation
            if (c == 'e' || c == 'E') {
                if (has_e) {  // Multiple e's = not a number
                    is_number = false;
                    break;
                }
                has_e = true;
                continue;
            }

            // Must be a digit
            if (c < '0' || c > '9') {
                is_number = false;
                break;
            }
        }

        if (!is_number) return DataType::VARCHAR;

        // Determine numeric type
        if (has_dot || has_e) return DataType::DOUBLE;
        return DataType::INTEGER;
    }

    /// Infer type of column reference
    DataType infer_column_type(Column* col) {
        if (col->table.empty()) {
            // No table qualifier - can't infer without schema context
            return DataType::UNKNOWN;
        }

        return catalog_.get_column_type(col->table, col->column);
    }

    /// Infer type of arithmetic operation
    DataType infer_arithmetic_type(BinaryOp* op) {
        DataType left_type = infer_type(op->left);
        DataType right_type = infer_type(op->right);

        // NULL propagation
        if (left_type == DataType::NULL_TYPE || right_type == DataType::NULL_TYPE) {
            return DataType::NULL_TYPE;
        }

        // Promote to highest precision type
        if (left_type == DataType::DOUBLE || right_type == DataType::DOUBLE) {
            return DataType::DOUBLE;
        }
        if (left_type == DataType::FLOAT || right_type == DataType::FLOAT) {
            return DataType::FLOAT;
        }
        if (left_type == DataType::DECIMAL || right_type == DataType::DECIMAL) {
            return DataType::DECIMAL;
        }
        if (left_type == DataType::BIGINT || right_type == DataType::BIGINT) {
            return DataType::BIGINT;
        }
        if (left_type == DataType::INTEGER || right_type == DataType::INTEGER) {
            return DataType::INTEGER;
        }

        return DataType::UNKNOWN;
    }

    /// Infer type of aggregate function
    DataType infer_aggregate_type(FunctionCall* func) {
        if (func->args.empty()) return DataType::UNKNOWN;

        DataType arg_type = infer_type(func->args[0]);

        if (func->type == ExprType::AGG_COUNT) {
            return DataType::BIGINT;
        }

        if (func->type == ExprType::AGG_AVG) {
            // AVG always returns floating point
            return DataType::DOUBLE;
        }

        if (func->type == ExprType::AGG_SUM) {
            // SUM preserves or promotes type
            if (arg_type == DataType::INTEGER) return DataType::BIGINT;
            if (arg_type == DataType::FLOAT) return DataType::DOUBLE;
            return arg_type;
        }

        // MIN/MAX preserve input type
        return arg_type;
    }

    /// Infer type of function call
    DataType infer_function_type(FunctionCall* func) {
        std::string name = func->name;
        // Convert to uppercase for comparison
        for (char& c : name) {
            if (c >= 'a' && c <= 'z') c = c - 32;
        }

        if (name == "UPPER" || name == "LOWER" || name == "TRIM" ||
            name == "SUBSTRING" || name == "CONCAT") {
            return DataType::VARCHAR;
        }

        if (name == "LENGTH" || name == "CHAR_LENGTH") {
            return DataType::INTEGER;
        }

        if (name == "COALESCE") {
            // Return type of first non-null argument
            for (auto arg : func->args) {
                DataType t = infer_type(arg);
                if (t != DataType::NULL_TYPE) return t;
            }
            return DataType::NULL_TYPE;
        }

        if (name == "CAST") {
            // Would need to parse type argument
            return DataType::UNKNOWN;
        }

        return DataType::UNKNOWN;
    }

    /// Validate arithmetic operation
    void validate_arithmetic(BinaryOp* op) {
        validate_expression(op->left);
        validate_expression(op->right);

        DataType left_type = infer_type(op->left);
        DataType right_type = infer_type(op->right);

        // Check that operands are numeric
        if (!is_numeric(left_type) && left_type != DataType::NULL_TYPE &&
            left_type != DataType::UNKNOWN) {
            throw TypeCheckError("Left operand of arithmetic operation must be numeric");
        }

        if (!is_numeric(right_type) && right_type != DataType::NULL_TYPE &&
            right_type != DataType::UNKNOWN) {
            throw TypeCheckError("Right operand of arithmetic operation must be numeric");
        }
    }

    /// Validate comparison operation
    void validate_comparison(BinaryOp* op) {
        validate_expression(op->left);
        validate_expression(op->right);

        DataType left_type = infer_type(op->left);
        DataType right_type = infer_type(op->right);

        // Allow comparisons between compatible types
        if (!types_compatible(left_type, right_type)) {
            std::ostringstream oss;
            oss << "Cannot compare incompatible types: "
                << type_name(left_type) << " and " << type_name(right_type);
            throw TypeCheckError(oss.str());
        }
    }

    /// Validate boolean logic operation
    void validate_boolean_logic(BinaryOp* op) {
        validate_expression(op->left);
        validate_expression(op->right);

        DataType left_type = infer_type(op->left);
        DataType right_type = infer_type(op->right);

        if (left_type != DataType::BOOLEAN && left_type != DataType::UNKNOWN) {
            throw TypeCheckError("Left operand of boolean operation must be boolean");
        }

        if (right_type != DataType::BOOLEAN && right_type != DataType::UNKNOWN) {
            throw TypeCheckError("Right operand of boolean operation must be boolean");
        }
    }

    /// Check if type is numeric
    static bool is_numeric(DataType type) {
        return type == DataType::INTEGER || type == DataType::BIGINT ||
               type == DataType::SMALLINT || type == DataType::TINYINT ||
               type == DataType::FLOAT || type == DataType::DOUBLE ||
               type == DataType::DECIMAL || type == DataType::NUMERIC;
    }

    /// Check if two types are compatible for comparison
    static bool types_compatible(DataType left, DataType right) {
        if (left == DataType::UNKNOWN || right == DataType::UNKNOWN) return true;
        if (left == DataType::NULL_TYPE || right == DataType::NULL_TYPE) return true;

        // Numeric types are compatible with each other
        if (is_numeric(left) && is_numeric(right)) return true;

        // String types are compatible with each other
        if ((left == DataType::VARCHAR || left == DataType::CHAR || left == DataType::TEXT) &&
            (right == DataType::VARCHAR || right == DataType::CHAR || right == DataType::TEXT)) {
            return true;
        }

        // Same type is always compatible
        return left == right;
    }

    /// Get type name for error messages
    static const char* type_name(DataType type) {
        switch (type) {
            case DataType::INTEGER: return "INTEGER";
            case DataType::BIGINT: return "BIGINT";
            case DataType::FLOAT: return "FLOAT";
            case DataType::DOUBLE: return "DOUBLE";
            case DataType::VARCHAR: return "VARCHAR";
            case DataType::BOOLEAN: return "BOOLEAN";
            case DataType::DATE: return "DATE";
            case DataType::TIMESTAMP: return "TIMESTAMP";
            case DataType::NULL_TYPE: return "NULL";
            case DataType::UNKNOWN: return "UNKNOWN";
            default: return "UNKNOWN";
        }
    }
};

} // namespace libsqlglot
