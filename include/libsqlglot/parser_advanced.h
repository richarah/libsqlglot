#pragma once

#include "parser.h"

namespace libsqlglot {

/// Advanced SQL parsing extensions for Parser class
/// Add these methods to Parser class:

/*
   /// Parse PIVOT clause
   /// Syntax: PIVOT (aggregate_function FOR pivot_column IN (value_list))
   PivotClause* parse_pivot_clause() {
       auto pivot = arena_.create<PivotClause>();
       expect(TokenType::PIVOT);
       expect(TokenType::LPAREN);

       // Aggregate function: SUM(amount), COUNT(*), etc.
       if (current().type == TokenType::IDENTIFIER) {
           std::string func_name(current().text);
           advance();
           expect(TokenType::LPAREN);

           std::vector<Expression*> args;
           if (match(TokenType::STAR)) {
               args.push_back(arena_.create<Star>());
           } else if (!check(TokenType::RPAREN)) {
               do {
                   args.push_back(parse_expression());
               } while (match(TokenType::COMMA));
           }
           expect(TokenType::RPAREN);

           pivot->aggregate = arena_.create<FunctionCall>(func_name, args);
       }

       // FOR column
       if (current().type == TokenType::IDENTIFIER && std::string(current().text) == "FOR") {
           advance();  // consume FOR
           pivot->pivot_column = parse_expression();
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

   /// Parse UNPIVOT clause
   /// Syntax: UNPIVOT (value_column FOR name_column IN (column_list))
   UnpivotClause* parse_unpivot_clause() {
       auto unpivot = arena_.create<UnpivotClause>();
       expect(TokenType::UNPIVOT);
       expect(TokenType::LPAREN);

       // Value column name
       if (current().type == TokenType::IDENTIFIER) {
           unpivot->value_column = std::string(current().text);
           advance();
       }

       // FOR name column
       if (current().type == TokenType::IDENTIFIER && std::string(current().text) == "FOR") {
           advance();  // consume FOR
           if (current().type == TokenType::IDENTIFIER) {
               unpivot->name_column = std::string(current().text);
               advance();
           }
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

   /// Modified parse_table_reference to handle PIVOT/UNPIVOT
   Expression* parse_table_reference_with_pivot() {
       Expression* table = nullptr;

       // Subquery: (SELECT ...) AS alias
       if (match(TokenType::LPAREN)) {
           if (check(TokenType::SELECT) || check(TokenType::WITH)) {
               auto select_expr = parse_select();
               auto select_stmt = static_cast<SelectStmt*>(select_expr);
               expect(TokenType::RPAREN);

               std::string alias;
               if (match(TokenType::AS)) {
                   if (!is_at_end() && current().text) {
                       alias = std::string(current().text);
                       advance();
                   }
               } else if (current().type == TokenType::IDENTIFIER) {
                   alias = std::string(current().text);
                   advance();
               }

               table = arena_.create<Subquery>(select_stmt, alias);
           } else {
               throw ParseError("Expected subquery after '('");
           }
       } else {
           // Regular table
           if (current().type != TokenType::IDENTIFIER) {
               throw ParseError("Expected table name or subquery");
           }

           std::string table_name(current().text);
           advance();

           std::string alias;
           if (match(TokenType::AS)) {
               if (!is_at_end() && current().text) {
                   alias = std::string(current().text);
                   advance();
               }
           } else if (current().type == TokenType::IDENTIFIER &&
                      !check(TokenType::PIVOT) && !check(TokenType::UNPIVOT)) {
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
           auto pivot = parse_pivot_clause();
           pivot->table_expr = table;
           return pivot;
       } else if (check(TokenType::UNPIVOT)) {
           auto unpivot = parse_unpivot_clause();
           unpivot->table_expr = table;
           return unpivot;
       }

       return table;
   }

   /// Parse CREATE PROCEDURE statement
   Expression* parse_create_procedure() {
       expect(TokenType::PROCEDURE);
       // Would implement full CREATE PROCEDURE parsing here
       // This is a stub for now
       throw ParseError("CREATE PROCEDURE not yet fully implemented");
   }

   /// Parse CREATE TRIGGER statement
   Expression* parse_create_trigger() {
       expect(TokenType::TRIGGER);
       // Would implement full CREATE TRIGGER parsing here
       // This is a stub for now
       throw ParseError("CREATE TRIGGER not yet fully implemented");
   }
*/

} // namespace libsqlglot
