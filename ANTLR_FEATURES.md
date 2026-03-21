# ANTLR Grammar Feature Discovery Report

**Generated from**: external/grammars-v4/antlr/antlr4/examples/grammars-v4
**Dialects analyzed**: 17

---

## Summary

| Dialect | Parser Rules | Keywords | Lexer Rules |
|---------|--------------|----------|-------------|
| athena | 125 | 150 | 174 |
| clickhouse | 120 | 0 | 230 |
| derby | 162 | 327 | 358 |
| drill | 83 | 120 | 154 |
| hive | 519 | 406 | 417 |
| informix-sql | 42 | 184 | 196 |
| mariadb | 363 | 1137 | 1186 |
| mysql | 1024 | 1122 | 2032 |
| phoenix | 129 | 163 | 197 |
| plsql | 1187 | 2330 | 2382 |
| postgresql | 720 | 529 | 554 |
| snowflake | 593 | 1089 | 921 |
| sqlite | 113 | 162 | 193 |
| starrocks | 437 | 457 | 505 |
| teradata | 642 | 1135 | 1233 |
| trino | 125 | 296 | 340 |
| tsql | 603 | 1133 | 1206 |

---

## ATHENA

**Parser rules**: 125  
**Keywords**: 150  
**Lexer rules**: 174

### DDL (16 rules)

- `alter_table_add_cols`
- `alter_table_add_part`
- `alter_table_drop_part`
- `alter_table_rename_part`
- `alter_table_replace_part`
- `alter_table_set_location`
- `alter_table_set_props`
- `create_database`
- `create_table`
- `create_table_as`
- `create_view`
- `drop_database`
- `drop_table`
- `drop_view`
- `show_create_table`
- `show_create_view`

### DML (9 rules)

- `delete_stmt`
- `insert_into`
- `merge_into`
- `select`
- `select_item`
- `select_list`
- `select_statement`
- `update`
- `update_delete`

### Queries (1 rules)

- `table_subquery`

### Other (99 rules)

- `alias`
- `all_distinct`
- `alter_database`
- `boolean_expression`
- `case_expression`
- `col_comment`
- `col_def_with_comment`
- `col_name`
- `column_list`
- `command`
- `comparison_operator`
- `condition`
- `count`
- `data_type`
- `database_name`
- `db_name`
- `db_schema`
- `ddl_command`
- `deallocate`
- `describe`
- `describe_view`
- `destination_table`
- `dml_command`
- `execute`
- `explain`
- `explain_option`
- `expression`
- `expression_list_`
- `field_name`
- `file_format`
- ... and 69 more

### Keywords (150 total)

Top 50:

- `A`
- `ADD`
- `ALL`
- `ALTER`
- `ANALYZE`
- `AND`
- `ANY`
- `ARRAY`
- `AS`
- `ASC`
- `AVRO`
- `BETWEEN`
- `BIGINT`
- `BINARY`
- `BIN_PACK`
- `BOOLEAN`
- `BUCKETS`
- `BY`
- `CASCADE`
- `CASE`
- `CAST`
- `CHAR`
- `CLUSTERED`
- `COLLECTION`
- `COLUMNS`
- `COMMENT`
- `CREATE`
- `DATA`
- `DATABASE`
- `DATABASES`
- `DATE`
- `DBPROPERTIES`
- `DEALLOCATE`
- `DECIMAL`
- `DEFINED`
- `DELETE`
- `DELIMITED`
- `DESC`
- `DESCRIBE`
- `DISTINCT`
- `DISTRIBUTED`
- `DOUBLE`
- `DROP`
- `E`
- `ELSE`
- `END`
- `ESCAPED`
- `EXCEPT`
- `EXECUTE`
- `EXISTS`
- ... and 100 more

---

## CLICKHOUSE

**Parser rules**: 120  
**Keywords**: 0  
**Lexer rules**: 230

### DDL (2 rules)

- `alterTableClause`
- `truncateStmt`

### DML (5 rules)

- `insertStmt`
- `projectionSelectStmt`
- `selectStmt`
- `selectStmtWithParens`
- `selectUnionStmt`

### Queries (15 rules)

- `arrayJoinClause`
- `ctes`
- `groupByClause`
- `havingClause`
- `joinConstraintClause`
- `joinExpr`
- `joinOp`
- `joinOpCross`
- `orderByClause`
- `prewhereClause`
- `projectionOrderByClause`
- `subqueryClause`
- `whereClause`
- `winOrderByClause`
- `withClause`

### Window Functions (4 rules)

- `partitionByClause`
- `winPartitionByClause`
- `windowClause`
- `windowExpr`

### Procedural (1 rules)

- `winFrameExtend`

### Constraints (2 rules)

- `dictionaryPrimaryKeyClause`
- `primaryKeyClause`

### Other (91 rules)

- `alias`
- `alterStmt`
- `assignmentExpr`
- `assignmentExprList`
- `assignmentValue`
- `assignmentValues`
- `attachStmt`
- `checkStmt`
- `clusterClause`
- `codecArgExpr`
- `codecExpr`
- `columnAliases`
- `columnArgExpr`
- `columnArgList`
- `columnExpr`
- `columnExprList`
- `columnIdentifier`
- `columnLambdaExpr`
- `columnTypeExpr`
- `columnsClause`
- `columnsExpr`
- `createStmt`
- `dataClause`
- `databaseIdentifier`
- `describeStmt`
- `destinationClause`
- `dictionaryArgExpr`
- `dictionaryAttrDfnt`
- `dictionaryEngineClause`
- `dictionarySchemaClause`
- ... and 61 more

---

## DERBY

**Parser rules**: 162  
**Keywords**: 327  
**Lexer rules**: 358

### DDL (11 rules)

- `alter_table`
- `create_function`
- `create_index`
- `create_procedure`
- `create_schema`
- `create_table`
- `create_view`
- `drop_index`
- `drop_table`
- `drop_view`
- `truncate_table`

### DML (13 rules)

- `delete_statement`
- `for_update_clause`
- `insert_statement`
- `merge_insert`
- `merge_statement`
- `merge_update`
- `merge_when_clause`
- `merge_when_matched`
- `merge_when_not_matched`
- `select_expression`
- `select_item`
- `select_statement`
- `update_statement`

### Queries (9 rules)

- `character_expression`
- `constraint_characteristics`
- `group_by_clause`
- `having_clause`
- `join_operation`
- `order_by_clause`
- `order_by_item`
- `table_subquery`
- `where_clause`

### Procedural (2 rules)

- `extended_case`
- `return_data_type`

### Constraints (4 rules)

- `always_by_default`
- `defaultValue`
- `default_constant_expression`
- `with_default`

### Other (123 rules)

- `aggreagate_built_in_function`
- `aggregate_name`
- `all_distinct`
- `alter_command`
- `asc_desc`
- `authorization_identifier`
- `batch`
- `boolean_expression`
- `cascade_restrict`
- `case_expression`
- `columnPosition`
- `column_alteration`
- `column_definition`
- `column_element`
- `column_identifier`
- `column_level_constraint`
- `column_list`
- `column_name`
- `comparison_operator`
- `constant_expression_null`
- `constraint_check_time`
- `constraint_clause`
- `constraint_name`
- `constraint_name_list`
- `correlation_clause`
- `correlation_name`
- `create_command`
- `create_derby_aggregate`
- `create_role`
- `create_sequence`
- ... and 93 more

### Keywords (327 total)

Top 50:

- `ABS`
- `ABSVAL`
- `ACOS`
- `ACTION`
- `ADD`
- `AGGREGATE`
- `ALL`
- `ALLOCATE`
- `ALTER`
- `ALWAYS`
- `AND`
- `ANY`
- `ARE`
- `AS`
- `ASC`
- `ASIN`
- `ASSERTION`
- `AT`
- `ATAN`
- `ATAN2`
- `AUTHORIZATION`
- `AVG`
- `BEGIN`
- `BETWEEN`
- `BIGINT`
- `BINARY`
- `BIT`
- `BLOB`
- `BOOLEAN`
- `BOTH`
- `BY`
- `CALL`
- `CALLED`
- `CASCADE`
- `CASCADED`
- `CASE`
- `CAST`
- `CEIL`
- `CEILING`
- `CHAR`
- `CHARACTER`
- `CHARACTER_LENGTH`
- `CHECK`
- `CLOB`
- `CLOSE`
- `COALESCE`
- `COLLATE`
- `COLLATION`
- `COLUMN`
- `COMMIT`
- ... and 277 more

---

## DRILL

**Parser rules**: 83  
**Keywords**: 120  
**Lexer rules**: 154

### DDL (7 rules)

- `create_function`
- `create_schema`
- `create_table`
- `create_temp_table`
- `create_view`
- `drop_table`
- `drop_view`

### DML (4 rules)

- `select_clause`
- `select_expression`
- `select_item`
- `select_stmt`

### Queries (10 rules)

- `group_by_clause`
- `having_clause`
- `join_clause`
- `join_type`
- `lateral_join_type`
- `lateral_subquery`
- `order_by_clause`
- `table_subquery`
- `where_clause`
- `with_clause`

### Window Functions (1 rules)

- `partition_by_clause`

### Constraints (1 rules)

- `default_clause`

### Other (60 rules)

- `alter_command`
- `alter_system`
- `analyze_command`
- `batch`
- `boolean_expression`
- `column_alias`
- `column_definition`
- `column_list`
- `column_list_paren`
- `column_name`
- `comparison_operator`
- `correlation_clause`
- `correlation_name`
- `create_command`
- `data_type`
- `ddl_command`
- `describe_command`
- `drill_file`
- `drop_command`
- `drop_function`
- `expr_list`
- `expression`
- `format_clause`
- `from_clause`
- `function_call`
- `function_name`
- `id_`
- `if_exists`
- `kv_list`
- `kv_pair`
- ... and 30 more

### Keywords (120 total)

Top 50:

- `ALL`
- `ALTER`
- `ANALYZE`
- `AND`
- `ANY`
- `AS`
- `ASC`
- `ASSIGN`
- `BETWEEN`
- `BIGINT`
- `BINARY`
- `BOOLEAN`
- `BY`
- `CAST`
- `CHAR`
- `CHARACTER`
- `COLUMNS`
- `COMPUTE`
- `CREATE`
- `CROSS`
- `DATABASE`
- `DATABASES`
- `DATE`
- `DAY`
- `DEC`
- `DECIMAL`
- `DEFAULT`
- `DESC`
- `DESCRIBE`
- `DISTINCT`
- `DOUBLE`
- `DROP`
- `E`
- `ESCAPE`
- `ESTIMATE`
- `EXISTS`
- `FALSE`
- `FETCH`
- `FILES`
- `FIRST`
- `FLOAT`
- `FOR`
- `FORMAT`
- `FROM`
- `FULL`
- `FUNCTION`
- `GROUP`
- `HAVING`
- `HOUR`
- `IF`
- ... and 70 more

---

## HIVE

**Parser rules**: 519  
**Keywords**: 406  
**Lexer rules**: 417

### DDL (16 rules)

- `alterTableStatementSuffix`
- `createDatabaseStatement`
- `createFunctionStatement`
- `createIndexStatement`
- `createMaterializedViewStatement`
- `createTablePartitionColumnSpec`
- `createTablePartitionColumnTypeSpec`
- `createTablePartitionSpec`
- `createTableStatement`
- `createViewStatement`
- `dropDatabaseStatement`
- `dropIndexStatement`
- `dropMaterializedViewStatement`
- `dropTableStatement`
- `dropViewStatement`
- `truncateTableStatement`

### DML (23 rules)

- `alterStatementSuffixMergeFiles`
- `alterStatementSuffixUpdateColumns`
- `alterStatementSuffixUpdateStats`
- `alterStatementSuffixUpdateStatsCol`
- `atomSelectStatement`
- `deleteStatement`
- `insertClause`
- `mergeStatement`
- `partitionSelectorOperator`
- `partitionSelectorSpec`
- `partitionSelectorVal`
- `selectClause`
- `selectExpression`
- `selectExpressionList`
- `selectItem`
- `selectList`
- `selectStatement`
- `selectStatementWithCTE`
- `selectTrfmClause`
- `setOpSelectStatement`
- `subQuerySelectorOperator`
- `updateOrDelete`
- `updateStatement`

### Queries (20 rules)

- `atomjoinSource`
- `cteStatement`
- `extractExpression`
- `groupByClause`
- `groupByEmpty`
- `groupby_expression`
- `havingClause`
- `joinSource`
- `joinSourcePart`
- `joinToken`
- `orderByClause`
- `subQueryExpression`
- `subQuerySource`
- `unionType`
- `uniqueJoinExpr`
- `uniqueJoinSource`
- `uniqueJoinTableSource`
- `uniqueJoinToken`
- `whereClause`
- `withClause`

### Window Functions (9 rules)

- `partitionByClause`
- `window_clause`
- `window_defn`
- `window_frame`
- `window_frame_boundary`
- `window_frame_start_boundary`
- `window_range_expression`
- `window_specification`
- `window_value_expression`

### Constraints (10 rules)

- `alterForeignKeyConstraint`
- `alterForeignKeyWithName`
- `checkConstraint`
- `createForeignKey`
- `defaultVal`
- `defaultValue`
- `expressionOrDefault`
- `foreignKeyConstraint`
- `precedencePlusExpressionOrDefault`
- `tableConstraintPrimaryKey`

### Advanced (6 rules)

- `alterMaterializedViewStatementSuffix`
- `alterMaterializedViewSuffixRebuild`
- `alterMaterializedViewSuffixRewrite`
- `lateralView`
- `qualifyClause`
- `tableSample`

### Other (435 rules)

- `abortCompactionStatement`
- `abortTransactionStatement`
- `activate`
- `adminOptionFor`
- `aliasList`
- `all_distinct`
- `alterColConstraint`
- `alterColumnConstraint`
- `alterConstraintWithName`
- `alterDataConnectorStatementSuffix`
- `alterDataConnectorSuffixProperties`
- `alterDataConnectorSuffixSetOwner`
- `alterDataConnectorSuffixSetUrl`
- `alterDatabaseStatementSuffix`
- `alterDatabaseSuffixProperties`
- `alterDatabaseSuffixSetLocation`
- `alterDatabaseSuffixSetManagedLocation`
- `alterDatabaseSuffixSetOwner`
- `alterIndexStatementSuffix`
- `alterMappingStatement`
- `alterPoolStatement`
- `alterResourcePlanStatement`
- `alterScheduledQueryChange`
- `alterScheduledQueryStatement`
- `alterStatement`
- `alterStatementChangeColPosition`
- `alterStatementPartitionKeyType`
- `alterStatementSuffixAddCol`
- `alterStatementSuffixAddConstraint`
- `alterStatementSuffixAddPartitions`
- ... and 405 more

### Keywords (406 total)

Top 50:

- `A`
- `ABORT`
- `ACTIVATE`
- `ACTIVE`
- `ADD`
- `ADMIN`
- `AFTER`
- `ALL`
- `ALLOC_FRACTION`
- `ALTER`
- `ANALYZE`
- `AND`
- `ANTI`
- `ANY`
- `APPLICATION`
- `ARCHIVE`
- `ARRAY`
- `AS`
- `ASC`
- `AST`
- `AT`
- `AUTHORIZATION`
- `AUTOCOMMIT`
- `B`
- `BEFORE`
- `BETWEEN`
- `BIGINT`
- `BINARY`
- `BOOLEAN`
- `BOTH`
- `BUCKET`
- `BUCKETS`
- `BY`
- `CACHE`
- `CASCADE`
- `CASE`
- `CAST`
- `CBO`
- `CHANGE`
- `CHAR`
- `CHECK`
- `CLUSTER`
- `CLUSTERED`
- `CLUSTERSTATUS`
- `COLLECTION`
- `COLUMN`
- `COLUMNS`
- `COMMENT`
- `COMMIT`
- `COMPACT`
- ... and 356 more

---

## INFORMIX-SQL

**Parser rules**: 42  
**Keywords**: 184  
**Lexer rules**: 196

### DDL (4 rules)

- `dropDatabase`
- `dropIndex`
- `dropTable`
- `dropView`

### Other (38 rules)

- `anyName`
- `closeDatabaseStmt`
- `closeStmt`
- `commitWorkStmt`
- `createRole`
- `databaseStmt`
- `dropAccessMethod`
- `dropAggregate`
- `dropRole`
- `dropSynonym`
- `dropTrigger`
- `dropTrustedContext`
- `dropType`
- `dropUser`
- `dropXadataTypeSource`
- `dropXadatasource`
- `identifier`
- `keyword`
- `quotedString`
- `releaseSavepoint`
- `renameColumn`
- `renameConstraint`
- `renameDatabase`
- `renameIndex`
- `renameSecurity`
- `renameSequence`
- `renameTable`
- `renameTrustedContext`
- `renameUser`
- `rollbackWork`
- `savepointStmt`
- `setAutofree`
- `setCollation`
- `setDataskip`
- `setDebugFile`
- `setDeferredPrepareStatement`
- `sqlScript`
- `unitStatement`

### Keywords (184 total)

Top 50:

- `ABORT`
- `ACCESS_METHOD`
- `ACTION`
- `ADD`
- `AFTER`
- `AGGREGATE`
- `ALL`
- `ALTER`
- `ALWAYS`
- `ANALYZE`
- `AND`
- `APPEND`
- `AS`
- `ASC`
- `ATTACH`
- `AUTOFREE`
- `AUTOINCREMENT`
- `BEFORE`
- `BEGIN`
- `BETWEEN`
- `BY`
- `CASCADE`
- `CASE`
- `CAST`
- `CHECK`
- `CLOSE`
- `COLLATE`
- `COLLATION`
- `COLUMN`
- `COMMIT`
- `COMPONENT`
- `CONFLICT`
- `CONSTRAINT`
- `CONTEXT`
- `CREATE`
- `CROSS`
- `CUME_DIST`
- `CURRENT`
- `CURRENT_DATE`
- `CURRENT_TIME`
- `CURRENT_TIMESTAMP`
- `DATABASE`
- `DATASKIP`
- `DEBUG`
- `DEFAULT`
- `DEFERRABLE`
- `DEFERRED`
- `DEFERRED_PREPARE`
- `DELETE`
- `DENSE_RANK`
- ... and 134 more

---

## MARIADB

**Parser rules**: 363  
**Keywords**: 1137  
**Lexer rules**: 1186

### DDL (18 rules)

- `alterTable`
- `alterTablespace`
- `createDatabase`
- `createDatabaseOption`
- `createFunction`
- `createIndex`
- `createProcedure`
- `createTable`
- `createTablespaceInnodb`
- `createTablespaceNdb`
- `createUdfunction`
- `createView`
- `dropDatabase`
- `dropIndex`
- `dropTable`
- `dropTablespace`
- `dropView`
- `truncateTable`

### DML (16 rules)

- `deleteStatement`
- `insertStatement`
- `insertStatementValue`
- `multipleDeleteStatement`
- `multipleUpdateStatement`
- `selectElement`
- `selectElements`
- `selectFieldsInto`
- `selectIntoExpression`
- `selectLinesInto`
- `selectSpec`
- `selectStatement`
- `singleDeleteStatement`
- `singleUpdateStatement`
- `updateStatement`
- `updatedElement`

### Queries (11 rules)

- `cteColumnName`
- `cteName`
- `groupByClause`
- `groupByItem`
- `havingClause`
- `joinPart`
- `orderByClause`
- `orderByExpression`
- `unionParenthesis`
- `unionStatement`
- `withClause`

### Window Functions (6 rules)

- `aggregateWindowedFunction`
- `nonAggregateWindowedFunction`
- `overClause`
- `windowClause`
- `windowName`
- `windowSpec`

### Procedural (10 rules)

- `beginWork`
- `caseStatement`
- `declareCondition`
- `declareCursor`
- `declareHandler`
- `declareVariable`
- `ifStatement`
- `loopStatement`
- `returnStatement`
- `xaEndTransaction`

### Constraints (4 rules)

- `defaultValue`
- `expressionOrDefault`
- `expressionsWithDefaults`
- `nullNotnull`

### Advanced (1 rules)

- `lateralStatement`

### Other (297 rules)

- `administrationStatement`
- `alterDatabase`
- `alterEvent`
- `alterFunction`
- `alterInstance`
- `alterLogfileGroup`
- `alterPartitionSpecification`
- `alterProcedure`
- `alterServer`
- `alterSpecification`
- `alterUser`
- `alterView`
- `analyzeTable`
- `assignmentField`
- `authPlugin`
- `authenticationRule`
- `binlogStatement`
- `bitOperator`
- `blockStatement`
- `boolMasterOption`
- `booleanLiteral`
- `cacheIndexStatement`
- `callStatement`
- `caseAlternative`
- `caseFuncAlternative`
- `changeMaster`
- `changeReplicationFilter`
- `channelOption`
- `charSet`
- `charsetName`
- ... and 267 more

### Keywords (1137 total)

Top 50:

- `ABS`
- `ACCOUNT`
- `ACOS`
- `ACTION`
- `ADD`
- `ADDDATE`
- `ADDTIME`
- `ADMIN`
- `AES_DECRYPT`
- `AES_ENCRYPT`
- `AFTER`
- `AGGREGATE`
- `ALGORITHM`
- `ALL`
- `ALTER`
- `ALWAYS`
- `ANALYZE`
- `AND`
- `ANY`
- `APPLICATION_PASSWORD_ADMIN`
- `ARCHIVE`
- `AREA`
- `ARMSCII8`
- `ARRAY`
- `AS`
- `ASBINARY`
- `ASC`
- `ASCII`
- `ASIN`
- `ASTEXT`
- `ASWKB`
- `ASWKT`
- `ASYMMETRIC_DECRYPT`
- `ASYMMETRIC_DERIVE`
- `ASYMMETRIC_ENCRYPT`
- `ASYMMETRIC_SIGN`
- `ASYMMETRIC_VERIFY`
- `AT`
- `ATAN`
- `ATAN2`
- `ATTRIBUTE`
- `AUDIT_ADMIN`
- `AUTHORS`
- `AUTO`
- `AUTOCOMMIT`
- `AUTOEXTEND_SIZE`
- `AUTO_INCREMENT`
- `AVG`
- `AVG_ROW_LENGTH`
- `B`
- ... and 1087 more

---

## MYSQL

**Parser rules**: 1024  
**Keywords**: 1122  
**Lexer rules**: 2032

### DDL (41 rules)

- `alterTable`
- `alterTableActions`
- `alterTablespace`
- `alterTablespaceOption`
- `alterTablespaceOptions`
- `alterUndoTablespace`
- `createDatabase`
- `createDatabaseOption`
- `createFunction`
- `createIndex`
- `createIndexTarget`
- `createProcedure`
- `createTable`
- `createTableOption`
- `createTableOptions`
- `createTableOptionsEtc`
- `createTableOptionsSpaceSeparated`
- `createTablespace`
- `createTablespaceInnodb`
- `createTablespaceNdb`
- `createUdfunction`
- `createUndoTablespace`
- `createView`
- `dropDatabase`
- `dropIndex`
- `dropTable`
- `dropTableSpace`
- `dropTablespace`
- `dropUndoTablespace`
- `dropView`
- `showCreateDatabaseStatement`
- `showCreateFunctionCodeStatement`
- `showCreateFunctionStatement`
- `showCreateFunctionStatusStatement`
- `showCreateProcedureCodeStatement`
- `showCreateProcedureStatement`
- `showCreateProcedureStatusStatement`
- `showCreateTableStatement`
- `showCreateViewStatement`
- `truncateTable`
- `truncateTableStatement`

### DML (35 rules)

- `deleteOption`
- `deleteStatement`
- `deleteStatementOption`
- `histogramAutoUpdate`
- `histogramUpdateParam`
- `insertFromConstructor`
- `insertIdentifier`
- `insertLockOption`
- `insertQueryExpression`
- `insertStatement`
- `insertStatementValue`
- `insertUpdateList`
- `insertValues`
- `multipleDeleteStatement`
- `multipleUpdateStatement`
- `partitionDelete`
- `returningType`
- `selectAlias`
- `selectElement`
- `selectElements`
- `selectFieldsInto`
- `selectIntoExpression`
- `selectItem`
- `selectItemList`
- `selectLinesInto`
- `selectOption`
- `selectSpec`
- `selectStatement`
- `selectStatementWithInto`
- `singleDeleteStatement`
- `singleUpdateStatement`
- `updateElement`
- `updateList`
- `updateStatement`
- `updatedElement`

### Queries (23 rules)

- `cteColumnName`
- `cteName`
- `exceptRoleList`
- `groupByClause`
- `groupByItem`
- `havingClause`
- `innerJoinType`
- `joinPart`
- `joinSpec`
- `joinedTable`
- `naturalJoinType`
- `orderByClause`
- `orderByExpression`
- `outerJoinType`
- `queryExpressionWithOptLockingClauses`
- `showCharacterSetStatement`
- `subquery`
- `transactionCharacteristics`
- `unionOption`
- `unionParenthesis`
- `unionStatement`
- `whereClause`
- `withClause`

### Window Functions (19 rules)

- `aggregateWindowedFunction`
- `leadLagInfo`
- `nonAggregateWindowedFunction`
- `overClause`
- `tableAdministrationStatement`
- `windowClause`
- `windowDefinition`
- `windowFrameBetween`
- `windowFrameBound`
- `windowFrameClause`
- `windowFrameExclusion`
- `windowFrameExtent`
- `windowFrameStart`
- `windowFrameUnits`
- `windowFunctionCall`
- `windowName`
- `windowSpec`
- `windowSpecDetails`
- `windowingClause`

### Procedural (13 rules)

- `beginEndBlock`
- `beginWork`
- `caseStatement`
- `declareCondition`
- `declareCursor`
- `declareHandler`
- `declareVariable`
- `ifStatement`
- `loopStatement`
- `returnStatement`
- `setSystemVariable`
- `tsOptionAutoextendSize`
- `xaEndTransaction`

### Constraints (12 rules)

- `checkConstraint`
- `defaultAuthOption`
- `defaultCharset`
- `defaultCollation`
- `defaultEncryption`
- `defaultRoleClause`
- `defaultValue`
- `expressionOrDefault`
- `expressionsWithDefaults`
- `nullNotnull`
- `setExprOrDefault`
- `tablePrimaryKeyCheckDef`

### Advanced (3 rules)

- `lateralStatement`
- `qualifyClause`
- `tablesampleClause`

### Other (878 rules)

- `accountLockPasswordExpireOptions`
- `accountManagementStatement`
- `aclType`
- `addOperator`
- `adminPartition`
- `administrationStatement`
- `allOrPartitionNameList`
- `alterAlgorithmOption`
- `alterCommandList`
- `alterCommandsModifier`
- `alterCommandsModifierList`
- `alterDatabase`
- `alterDatabaseOption`
- `alterEvent`
- `alterFunction`
- `alterInstance`
- `alterInstanceStatement`
- `alterList`
- `alterListItem`
- `alterLockOption`
- `alterLogfileGroup`
- `alterLogfileGroupOption`
- `alterLogfileGroupOptions`
- `alterOrderList`
- `alterPartition`
- `alterPartitionSpecification`
- `alterProcedure`
- `alterResourceGroup`
- `alterServer`
- `alterSpecification`
- ... and 848 more

### Keywords (1122 total)

Top 50:

- `ABS`
- `ACCOUNT`
- `ACOS`
- `ACTION`
- `ADD`
- `ADDDATE`
- `ADDTIME`
- `ADMIN`
- `AES_DECRYPT`
- `AES_ENCRYPT`
- `AFTER`
- `AGGREGATE`
- `ALGORITHM`
- `ALL`
- `ALTER`
- `ALWAYS`
- `ANALYZE`
- `AND`
- `ANY`
- `APPLICATION_PASSWORD_ADMIN`
- `ARCHIVE`
- `AREA`
- `ARMSCII8`
- `ARRAY`
- `AS`
- `ASBINARY`
- `ASC`
- `ASCII`
- `ASIN`
- `ASTEXT`
- `ASWKB`
- `ASWKT`
- `ASYMMETRIC_DECRYPT`
- `ASYMMETRIC_DERIVE`
- `ASYMMETRIC_ENCRYPT`
- `ASYMMETRIC_SIGN`
- `ASYMMETRIC_VERIFY`
- `AT`
- `ATAN`
- `ATAN2`
- `ATTRIBUTE`
- `AUDIT_ABORT_EXEMPT`
- `AUDIT_ADMIN`
- `AUTHENTICATION_POLICY_ADMIN`
- `AUTHORS`
- `AUTOCOMMIT`
- `AUTOEXTEND_SIZE`
- `AUTO_INCREMENT`
- `AVG`
- `AVG_ROW_LENGTH`
- ... and 1072 more

---

## PHOENIX

**Parser rules**: 129  
**Keywords**: 163  
**Lexer rules**: 197

### DDL (8 rules)

- `create_function_command`
- `create_index_command`
- `create_schema_command`
- `create_table_command`
- `create_view_command`
- `drop_index_command`
- `drop_table_command`
- `drop_view_command`

### DML (7 rules)

- `delete_command`
- `select_command`
- `select_expression`
- `select_statement`
- `update_statistics_command`
- `upsert_select_command`
- `upsert_values_command`

### Queries (8 rules)

- `join_hint`
- `join_item`
- `join_list`
- `join_type`
- `order_by_clause`
- `union`
- `union_list`
- `where_clause`

### Procedural (1 rules)

- `declare_cursor_command`

### Other (105 rules)

- `alias`
- `aliased_table_ref`
- `alter_command`
- `alter_index_command`
- `any_all`
- `array_constructor`
- `asc_desc`
- `batch`
- `bind_parameter`
- `bind_parameter_number`
- `cache_hint`
- `case`
- `case_when`
- `cast`
- `class_name`
- `close_command`
- `column_alias`
- `column_def`
- `column_def_list`
- `column_name`
- `column_ref`
- `column_ref_list`
- `comp_op`
- `constraint`
- `constraint_column`
- `constraint_column_list`
- `constraint_name`
- `create_sequence_command`
- `cursor_name`
- `data_type`
- ... and 75 more

### Keywords (163 total)

Top 50:

- `ADD`
- `ALL`
- `ALTER`
- `AND`
- `ANY`
- `APPROX_COUNT_DISTINCT`
- `ARRAY`
- `AS`
- `ASC`
- `ASYNC`
- `AVG`
- `BETWEEN`
- `BIGINT`
- `BINARY`
- `BY`
- `CACHE`
- `CASCADE`
- `CASE`
- `CAST`
- `CHAR`
- `CLOSE`
- `COLUMN`
- `CONSTANT`
- `CONSTRAINT`
- `COUNT`
- `CREATE`
- `CURRENT`
- `CURSOR`
- `CYCLE`
- `DATE`
- `DECIMAL`
- `DECLARE`
- `DEFAULT`
- `DEFAULTVALUE`
- `DELETE`
- `DESC`
- `DISABLE`
- `DISTINCT`
- `DOUBLE`
- `DROP`
- `DUPLICATE`
- `E`
- `ELSE`
- `END`
- `EXISTS`
- `EXPLAIN`
- `FALSE`
- `FETCH`
- `FIRST`
- `FIRST_VALUE`
- ... and 113 more

---

## PLSQL

**Parser rules**: 1187  
**Keywords**: 2330  
**Lexer rules**: 2382

### DDL (38 rules)

- `alter_mapping_table_clause`
- `alter_table`
- `alter_table_partitioning`
- `alter_table_properties`
- `alter_table_properties_1`
- `alter_tablespace`
- `alter_tablespace_attrs`
- `alter_tablespace_encryption`
- `alter_tablespace_set`
- `blockchain_drop_table_clause`
- `create_analytic_view`
- `create_database`
- `create_database_link`
- `create_function_body`
- `create_index`
- `create_materialized_view`
- `create_materialized_view_log`
- `create_procedure_body`
- `create_table`
- `create_tablespace`
- `create_tablespace_set`
- `create_view`
- `create_zonemap_on_table`
- `drop_analytic_view`
- `drop_database`
- `drop_database_link`
- `drop_index`
- `drop_index_partition`
- `drop_indextype`
- `drop_materialized_view`
- `drop_table`
- `drop_table_partition`
- `drop_tablespace`
- `drop_tablespace_set`
- `drop_view`
- `truncate_cluster`
- `truncate_table`
- `truncate_table_partition`

### DML (46 rules)

- `add_update_secret`
- `add_update_secret_seps`
- `column_based_update_set_clause`
- `conditional_insert_clause`
- `conditional_insert_else_part`
- `conditional_insert_when_part`
- `default_selectivity`
- `default_selectivity_clause`
- `delete_secret`
- `delete_secret_seps`
- `delete_statement`
- `dynamic_returning_clause`
- `for_update_clause`
- `for_update_of_part`
- `for_update_options`
- `immutable_table_no_delete_clause`
- `insert_into_clause`
- `insert_statement`
- `json_query_returning_clause`
- `merge_element`
- `merge_insert_clause`
- `merge_into_existing_keystore`
- `merge_into_new_keystore`
- `merge_statement`
- `merge_table_partition`
- `merge_update_clause`
- `merge_update_delete_part`
- `multi_table_insert`
- `on_delete_clause`
- `select_list_elements`
- `select_only_statement`
- `select_statement`
- `selected_list`
- `selected_tableview`
- `selection_directive`
- `selection_directive_body`
- `single_table_insert`
- `static_returning_clause`
- `update_all_indexes_clause`
- `update_all_indexes_index_clause`
- `update_global_index_clause`
- `update_index_clauses`
- `update_index_partition`
- `update_index_subpartition`
- `update_set_clause`
- `update_statement`

### Queries (39 rules)

- `alter_inmemory_join_group`
- `bitmap_join_index_clause`
- `character_set_clause`
- `clustering_join`
- `clustering_join_item`
- `collect_order_by_part`
- `create_inmemory_join_group`
- `create_zonemap_as_subquery`
- `dependent_exceptions_part`
- `dimension_join_clause`
- `drop_inmemory_join_group`
- `equijoin_condition`
- `exception_declaration`
- `exception_handler`
- `exception_name`
- `exceptions_clause`
- `group_by_clause`
- `group_by_elements`
- `having_clause`
- `join_clause`
- `join_condition`
- `join_condition_item`
- `join_on_part`
- `join_path_clause`
- `join_using_part`
- `order_by_clause`
- `order_by_elements`
- `outer_join_sign`
- `outer_join_type`
- `subquery`
- `subquery_basic_elements`
- `subquery_factoring_clause`
- `subquery_operation_part`
- `subquery_restriction_clause`
- `where_clause`
- `with_backup_clause`
- `with_clause`
- `with_factoring_clause`
- `within_or_over_clause_keyword`

### Window Functions (18 rules)

- `add_overflow_clause`
- `alter_overflow_clause`
- `commit_switchover_clause`
- `hash_partitions_by_quantity`
- `index_org_overflow_clause`
- `lead_cdb_clause`
- `lead_cdb_uri_clause`
- `listagg_overflow_clause`
- `over_clause`
- `over_clause_keyword`
- `partition_by_clause`
- `recovery_clauses`
- `subpartition_by_hash`
- `subpartition_by_list`
- `subpartition_by_range`
- `windowing_clause`
- `windowing_elements`
- `windowing_type`

### Procedural (22 rules)

- `autoextend_clause`
- `begin_or_end`
- `declare_spec`
- `dependent_handling_clause`
- `end_time_column`
- `extended_attribute_clause`
- `if_statement`
- `json_query_return_type`
- `json_return_clause`
- `json_value_return_clause`
- `json_value_return_type`
- `loop_statement`
- `multi_column_for_loop`
- `partition_extended_names`
- `raise_statement`
- `return_rows_clause`
- `return_statement`
- `searched_case_statement`
- `seq_of_declare_specs`
- `simple_case_statement`
- `single_column_for_loop`
- `subpartition_extended_names`

### Constraints (18 rules)

- `check_constraint`
- `default_aggregate_clause`
- `default_collation_clause`
- `default_cost_clause`
- `default_index_compression`
- `default_measure_clause`
- `default_settings_clause`
- `default_table_compression`
- `default_tablespace`
- `default_tablespace_params`
- `default_temp_tablespace`
- `default_value_part`
- `foreign_key_clause`
- `modify_index_default_attrs`
- `primary_key_clause`
- `unique_key_clause`
- `user_default_role_clause`
- `xml_general_default_part`

### Advanced (15 rules)

- `alter_materialized_view`
- `alter_materialized_view_log`
- `alter_materialized_zonemap`
- `comment_on_materialized`
- `create_materialized_zonemap`
- `drop_materialized_zonemap`
- `pivot_clause`
- `pivot_element`
- `pivot_for_clause`
- `pivot_in_clause`
- `pivot_in_clause_element`
- `pivot_in_clause_elements`
- `unpivot_clause`
- `unpivot_in_clause`
- `unpivot_in_elements`

### Other (991 rules)

- `access_driver_type`
- `accessible_by_clause`
- `accessor`
- `action_audit_clause`
- `actions_clause`
- `activate_standby_db_clause`
- `ad_attributes_clause`
- `ad_level_clause`
- `ad_using_clause`
- `add_binding_clause`
- `add_calc_meas_clause`
- `add_calcs_clause`
- `add_column_clause`
- `add_constraint`
- `add_constraint_clause`
- `add_disk_clause`
- `add_filegroup_clause`
- `add_hash_index_partition`
- `add_logfile_clauses`
- `add_modify_drop_column_clauses`
- `add_mv_log_column_clause`
- `add_or_drop`
- `add_rem_container_data`
- `add_table_partition`
- `add_volume_clause`
- `administer_key_management`
- `aggregate_clause`
- `aggregate_function_name`
- `all_clause`
- `allocate_extent_clause`
- ... and 961 more

### Keywords (2330 total)

Top 50:

- `A`
- `ABORT`
- `ABS`
- `ABSENT`
- `ACCESS`
- `ACCESSED`
- `ACCESSIBLE`
- `ACCOUNT`
- `ACL`
- `ACOS`
- `ACROSS`
- `ACTION`
- `ACTIONS`
- `ACTIVATE`
- `ACTIVE`
- `ACTIVE_COMPONENT`
- `ACTIVE_DATA`
- `ACTIVE_FUNCTION`
- `ACTIVE_TAG`
- `ACTIVITY`
- `ADAPTIVE_PLAN`
- `ADD`
- `ADD_COLUMN`
- `ADD_GROUP`
- `ADD_MONTHS`
- `ADJ_DATE`
- `ADMIN`
- `ADMINISTER`
- `ADMINISTRATOR`
- `ADVANCED`
- `ADVISE`
- `ADVISOR`
- `AFD_DISKSTRING`
- `AFTER`
- `AGENT`
- `AGGREGATE`
- `ALGORITHM`
- `ALIAS`
- `ALL`
- `ALLOCATE`
- `ALLOW`
- `ALL_ROWS`
- `ALTER`
- `ALTERNATE`
- `ALWAYS`
- `ANALYTIC`
- `ANALYZE`
- `ANCESTOR`
- `ANCILLARY`
- `AND`
- ... and 2280 more

---

## POSTGRESQL

**Parser rules**: 720  
**Keywords**: 529  
**Lexer rules**: 554

### DDL (10 rules)

- `alter_table_cmd`
- `alter_table_cmds`
- `altertablestmt`
- `createforeigntablestmt`
- `createfunctionstmt`
- `creatematviewstmt`
- `createschemastmt`
- `createtablespacestmt`
- `droptablespacestmt`
- `truncatestmt`

### DML (27 rules)

- `deletestmt`
- `insert_column_item`
- `insert_column_list`
- `insert_rest`
- `insert_target`
- `insertstmt`
- `json_returning_clause`
- `key_delete`
- `key_update`
- `merge_delete_clause`
- `merge_insert_clause`
- `merge_update_clause`
- `mergestmt`
- `on_conflict_`
- `returning_clause`
- `select_clause`
- `select_fetch_first_value`
- `select_limit`
- `select_limit_`
- `select_limit_value`
- `select_no_parens`
- `select_offset_value`
- `select_with_parens`
- `selectstmt`
- `simple_select_intersect`
- `simple_select_pramary`
- `updatestmt`

### Queries (17 rules)

- `character`
- `character_c`
- `constcharacter`
- `cte_list`
- `exclusionwhereclause`
- `group_by_item`
- `group_by_list`
- `having_clause`
- `join_qual`
- `join_type`
- `json_array_aggregate_order_by_clause`
- `subquery_Op`
- `where_clause`
- `where_or_current_clause`
- `with_clause`
- `with_clause_`
- `within_group_clause`

### Window Functions (8 rules)

- `existing_window_name_`
- `func_expr_windowless`
- `over_clause`
- `window_clause`
- `window_definition`
- `window_definition_list`
- `window_exclusion_clause_`
- `window_specification`

### Procedural (3 rules)

- `alterobjectdependsstmt`
- `declarecursorstmt`
- `func_return`

### Constraints (12 rules)

- `alter_column_default`
- `alterdefaultprivilegesstmt`
- `case_default`
- `default_`
- `func_arg_with_default`
- `func_args_with_defaults`
- `func_args_with_defaults_list`
- `json_key_uniqueness_constraint`
- `rowsecuritydefaultforcmd`
- `rowsecuritydefaultpermissive`
- `rowsecuritydefaulttorole`
- `unique_`

### Advanced (2 rules)

- `materialized_`
- `tablesample_clause`

### Other (641 rules)

- `a_expr`
- `a_expr_add`
- `a_expr_and`
- `a_expr_at_time_zone`
- `a_expr_between`
- `a_expr_caret`
- `a_expr_collate`
- `a_expr_compare`
- `a_expr_in`
- `a_expr_is_not`
- `a_expr_isnull`
- `a_expr_lessless`
- `a_expr_like`
- `a_expr_mul`
- `a_expr_or`
- `a_expr_qual`
- `a_expr_qual_op`
- `a_expr_typecast`
- `a_expr_unary_not`
- `a_expr_unary_qualop`
- `a_expr_unary_sign`
- `access_method_clause`
- `add_drop`
- `aexprconst`
- `aggr_arg`
- `aggr_args`
- `aggr_args_list`
- `aggregate_with_argtypes`
- `aggregate_with_argtypes_list`
- `alias_clause`
- ... and 611 more

### Keywords (529 total)

Top 50:

- `ABORT`
- `ABSENT`
- `ABSOLUTE`
- `ACCESS`
- `ACTION`
- `ADD`
- `ADMIN`
- `AFTER`
- `AGGREGATE`
- `ALL`
- `ALSO`
- `ALTER`
- `ALWAYS`
- `ANALYSE`
- `ANALYZE`
- `AND`
- `ANY`
- `ARRAY`
- `AS`
- `ASC`
- `ASENSITIVE`
- `ASSERT`
- `ASSERTION`
- `ASSIGNMENT`
- `ASYMMETRIC`
- `AT`
- `ATOMIC`
- `ATTACH`
- `ATTRIBUTE`
- `AUTHORIZATION`
- `B`
- `BACKWARD`
- `BEFORE`
- `BEGIN`
- `BETWEEN`
- `BIGINT`
- `BINARY`
- `BIT`
- `BOOLEAN`
- `BOTH`
- `BREATH`
- `BY`
- `CACHE`
- `CALL`
- `CALLED`
- `CASCADE`
- `CASCADED`
- `CASE`
- `CAST`
- `CATALOG`
- ... and 479 more

---

## SNOWFLAKE

**Parser rules**: 593  
**Keywords**: 1089  
**Lexer rules**: 921

### DDL (27 rules)

- `alter_dynamic_table`
- `alter_external_table`
- `alter_table`
- `alter_table_alter_column`
- `create_database`
- `create_dynamic_table`
- `create_event_table`
- `create_external_function`
- `create_function`
- `create_materialized_view`
- `create_procedure`
- `create_schema`
- `create_table`
- `create_table_as_select`
- `create_table_clause`
- `create_table_like`
- `create_view`
- `drop_database`
- `drop_dynamic_table`
- `drop_external_table`
- `drop_materialized_view`
- `drop_table`
- `drop_view`
- `truncate_materialized_view`
- `truncate_table`
- `undrop_database`
- `undrop_table`

### DML (21 rules)

- `delete_statement`
- `insert_multi_table_statement`
- `insert_only`
- `insert_statement`
- `merge_cond`
- `merge_insert`
- `merge_matches`
- `merge_statement`
- `merge_update_delete`
- `on_delete`
- `on_update`
- `select_clause`
- `select_list`
- `select_list_elem`
- `select_list_no_top`
- `select_list_top`
- `select_optional_clauses`
- `select_statement`
- `select_statement_in_parentheses`
- `select_top_clause`
- `update_statement`

### Queries (13 rules)

- `character`
- `group_by_clause`
- `group_by_elem`
- `group_by_list`
- `having_clause`
- `join_clause`
- `join_type`
- `order_by_clause`
- `order_by_expr`
- `outer_join`
- `subquery`
- `table_source_item_joined`
- `where_clause`

### Window Functions (3 rules)

- `over_clause`
- `partition_by`
- `ranking_windowed_function`

### Procedural (7 rules)

- `append_only`
- `begin_txn`
- `default_append_only`
- `end`
- `if_suspended`
- `resume_suspend`
- `task_suspend_after_failure_number`

### Constraints (9 rules)

- `arg_default_value_clause`
- `default_ddl_collation`
- `default_value`
- `foreign_key`
- `foreign_key_match`
- `not_null`
- `null_not_null`
- `primary_key`
- `show_primary_keys`

### Advanced (7 rules)

- `alter_materialized_view`
- `describe_materialized_view`
- `materialized_col_decl`
- `materialized_col_decl_list`
- `pivot_unpivot`
- `qualify_clause`
- `show_materialized_views`

### Other (506 rules)

- `account_id_list`
- `account_identifier`
- `account_object_privilege`
- `account_object_privileges`
- `account_params`
- `after_match`
- `aggregate_function`
- `alert_action`
- `alert_condition`
- `alert_set_clause`
- `alert_unset_clause`
- `alias`
- `all_distinct`
- `alter_account`
- `alter_account_opts`
- `alter_alert`
- `alter_api_integration`
- `alter_column_clause`
- `alter_column_decl`
- `alter_column_decl_list`
- `alter_column_opts`
- `alter_command`
- `alter_connection`
- `alter_connection_opts`
- `alter_database`
- `alter_file_format`
- `alter_function`
- `alter_function_signature`
- `alter_masking_policy`
- `alter_modify`
- ... and 476 more

### Keywords (1089 total)

Top 50:

- `ABORT`
- `ABORT_AFTER_WAIT`
- `ABORT_DETACHED_QUERY`
- `ABORT_STATEMENT`
- `ABSENT`
- `ABSOLUTE`
- `ACCESS`
- `ACCOUNT`
- `ACCOUNTADMIN`
- `ACCOUNTS`
- `ACTION`
- `ACTIVE`
- `ADD`
- `ADMINISTER`
- `ADMIN_NAME`
- `ADMIN_PASSWORD`
- `AES`
- `AFTER`
- `AGGREGATE`
- `ALERT`
- `ALERTS`
- `ALL`
- `ALLOWED`
- `ALLOWED_ACCOUNTS`
- `ALLOWED_DATABASES`
- `ALLOWED_INTEGRATION_TYPES`
- `ALLOWED_IP_LIST`
- `ALLOWED_SHARES`
- `ALLOWED_VALUES`
- `ALLOW_CLIENT_MFA_CACHING`
- `ALLOW_CONNECTIONS`
- `ALLOW_DUPLICATE`
- `ALLOW_ID_TOKEN`
- `ALLOW_MULTIPLE_EVENT_LOSS`
- `ALLOW_OVERLAPPING_EXECUTION`
- `ALLOW_SINGLE_EVENT_LOSS`
- `ALTER`
- `ALWAYS`
- `AND`
- `ANONYMOUS`
- `ANY`
- `ANY_VALUE`
- `API`
- `API_ALLOWED_PREFIXES`
- `API_AWS_ROLE_ARN`
- `API_BLOCKED_PREFIXES`
- `API_INTEGRATION`
- `API_KEY`
- `API_PROVIDER`
- `APPEND`
- ... and 1039 more

---

## SQLITE

**Parser rules**: 113  
**Keywords**: 162  
**Lexer rules**: 193

### DDL (5 rules)

- `alter_table_stmt`
- `create_index_stmt`
- `create_table_stmt`
- `create_view_stmt`
- `create_virtual_table_stmt`

### DML (14 rules)

- `compound_select_stmt`
- `delete_stmt`
- `delete_stmt_limited`
- `factored_select_stmt`
- `initial_select`
- `insert_stmt`
- `recursive_select`
- `returning_clause`
- `select_core`
- `select_stmt`
- `simple_select_stmt`
- `update_stmt`
- `update_stmt_limited`
- `upsert_clause`

### Queries (10 rules)

- `cte_table_name`
- `join_clause`
- `join_constraint`
- `join_operator`
- `order_by_expr`
- `order_by_expr_asc_desc`
- `order_by_stmt`
- `recursive_cte`
- `table_or_subquery`
- `with_clause`

### Window Functions (7 rules)

- `base_window_name`
- `over_clause`
- `partition_by`
- `window_defn`
- `window_function`
- `window_function_invocation`
- `window_name`

### Procedural (2 rules)

- `begin_stmt`
- `raise_function`

### Constraints (2 rules)

- `default_value`
- `foreign_key_clause`

### Other (73 rules)

- `aggregate_func`
- `aggregate_function_invocation`
- `alias`
- `analyze_stmt`
- `any_name`
- `asc_desc`
- `attach_stmt`
- `collation_name`
- `column_alias`
- `column_constraint`
- `column_def`
- `column_name`
- `column_name_list`
- `commit_stmt`
- `common_table_expression`
- `common_table_stmt`
- `compound_operator`
- `conflict_clause`
- `create_trigger_stmt`
- `detach_stmt`
- `drop_stmt`
- `error_message`
- `expr`
- `expr_asc_desc`
- `filename`
- `filter_clause`
- `foreign_table`
- `frame_clause`
- `frame_left`
- `frame_right`
- ... and 43 more

### Keywords (162 total)

Top 50:

- `ABORT`
- `ACTION`
- `ADD`
- `AFTER`
- `ALL`
- `ALTER`
- `ALWAYS`
- `ANALYZE`
- `AND`
- `AS`
- `ASC`
- `ATTACH`
- `AUTOINCREMENT`
- `BEFORE`
- `BEGIN`
- `BETWEEN`
- `BY`
- `CASCADE`
- `CASE`
- `CAST`
- `CHECK`
- `COLLATE`
- `COLUMN`
- `COMMIT`
- `CONFLICT`
- `CONSTRAINT`
- `CREATE`
- `CROSS`
- `CUME_DIST`
- `CURRENT`
- `CURRENT_DATE`
- `CURRENT_TIME`
- `CURRENT_TIMESTAMP`
- `DATABASE`
- `DEFAULT`
- `DEFERRABLE`
- `DEFERRED`
- `DELETE`
- `DENSE_RANK`
- `DESC`
- `DETACH`
- `DISTINCT`
- `DO`
- `DROP`
- `E`
- `EACH`
- `ELSE`
- `END`
- `ESCAPE`
- `EXCEPT`
- ... and 112 more

---

## STARROCKS

**Parser rules**: 437  
**Keywords**: 457  
**Lexer rules**: 505

### DDL (18 rules)

- `alterTableStatement`
- `cancelAlterTableStatement`
- `createFunctionStatement`
- `createIndexClause`
- `createIndexStatement`
- `createMaterializedViewStatement`
- `createTableAsSelectStatement`
- `createTableLikeStatement`
- `createTableStatement`
- `createViewStatement`
- `dropIndexClause`
- `dropIndexStatement`
- `dropMaterializedViewStatement`
- `dropTableStatement`
- `dropViewStatement`
- `showCreateTableStatement`
- `truncatePartitionClause`
- `truncateTableStatement`

### DML (7 rules)

- `dataCacheSelectStatement`
- `deleteStatement`
- `insertStatement`
- `selectItem`
- `showDeleteStatement`
- `updateFailPointStatusStatement`
- `updateStatement`

### Queries (9 rules)

- `crossOrInnerJoinType`
- `joinCriteria`
- `joinRelation`
- `orderByDesc`
- `outerAndSemiJoinType`
- `subquery`
- `transaction_characteristics`
- `tupleInSubquery`
- `withClause`

### Window Functions (2 rules)

- `windowFrame`
- `windowFunction`

### Procedural (12 rules)

- `addBackendBlackListStatement`
- `addBackendClause`
- `addFrontendClause`
- `decommissionBackendClause`
- `delBackendBlackListStatement`
- `dropBackendClause`
- `dropFrontendClause`
- `modifyBackendClause`
- `modifyFrontendHostClause`
- `showBackendBlackListStatement`
- `showBackendsStatement`
- `showFrontendsStatement`

### Constraints (6 rules)

- `defaultDesc`
- `expressionOrDefault`
- `expressionsWithDefault`
- `setDefaultRoleStatement`
- `setDefaultStorageVolumeStatement`
- `setExprOrDefault`

### Advanced (8 rules)

- `alterMaterializedViewStatement`
- `cancelRefreshMaterializedViewStatement`
- `materializedViewDesc`
- `pivotAggregationExpression`
- `pivotClause`
- `pivotValue`
- `refreshMaterializedViewStatement`
- `showMaterializedViewsStatement`

### Other (375 rules)

- `addColumnClause`
- `addColumnsClause`
- `addComputeNodeClause`
- `addFieldClause`
- `addPartitionClause`
- `addSqlBlackListStatement`
- `adminCancelRepairTableStatement`
- `adminCheckTabletsStatement`
- `adminRepairTableStatement`
- `adminSetConfigStatement`
- `adminSetPartitionVersion`
- `adminSetReplicaStatusStatement`
- `adminShowConfigStatement`
- `adminShowReplicaDistributionStatement`
- `adminShowReplicaStatusStatement`
- `aggDesc`
- `aggregationFunction`
- `alterCatalogStatement`
- `alterDatabaseRenameStatement`
- `alterDbQuotaStatement`
- `alterLoadErrorUrlClause`
- `alterLoadStatement`
- `alterPipeClause`
- `alterPipeStatement`
- `alterResourceGroupStatement`
- `alterResourceStatement`
- `alterRoleStatement`
- `alterRoutineLoadStatement`
- `alterStorageVolumeClause`
- `alterStorageVolumeStatement`
- ... and 345 more

### Keywords (457 total)

Top 50:

- `ACCESS`
- `ACTIVE`
- `ADD`
- `ADMIN`
- `AFTER`
- `AGGREGATE`
- `ALL`
- `ALTER`
- `ANALYZE`
- `AND`
- `ANTI`
- `APPLY`
- `ARRAY`
- `ARRAY_AGG`
- `ARRAY_AGG_DISTINCT`
- `AS`
- `ASC`
- `ASYNC`
- `AUTHENTICATION`
- `AUTHORS`
- `AUTO_INCREMENT`
- `AVG`
- `BACKEND`
- `BACKENDS`
- `BACKUP`
- `BASE`
- `BEGIN`
- `BETWEEN`
- `BIGINT`
- `BINARY`
- `BITMAP`
- `BITMAP_UNION`
- `BITSHIFTLEFT`
- `BITSHIFTRIGHT`
- `BITSHIFTRIGHTLOGICAL`
- `BLACKHOLE`
- `BLACKLIST`
- `BODY`
- `BOOLEAN`
- `BOTH`
- `BROKER`
- `BUCKETS`
- `BUILTIN`
- `BY`
- `CACHE`
- `CANCEL`
- `CASE`
- `CAST`
- `CATALOG`
- `CATALOGS`
- ... and 407 more

---

## TERADATA

**Parser rules**: 642  
**Keywords**: 1135  
**Lexer rules**: 1233

### DDL (34 rules)

- `alter_foreign_table_stat`
- `alter_table_basic_stat`
- `alter_table_join_index_stat`
- `alter_table_map_and_collocation_form_stat`
- `alter_table_release_rows_stat`
- `alter_table_revalidation_stat`
- `alter_table_stat`
- `alter_table_to_current_stat`
- `create_database_stat`
- `create_error_table_stat`
- `create_foreign_table_stat`
- `create_global_temporary_trace_table_stat`
- `create_hash_index_stat`
- `create_index_stat`
- `create_join_index_stat`
- `create_queue_table_stat`
- `create_replace_external_function_stat`
- `create_replace_function_stat`
- `create_replace_procedure_sql_form_stat`
- `create_replace_procedure_stat`
- `create_replace_sql_function_stat`
- `create_replace_table_function_stat`
- `create_replace_view_stat`
- `create_table_as_stat`
- `create_table_primary_form_stat`
- `create_table_stat`
- `drop_database_stat`
- `drop_default_journal_table`
- `drop_error_table_stat`
- `drop_hash_index_stat`
- `drop_index_stat`
- `drop_join_index_stat`
- `drop_table_stat`
- `drop_view_stat`

### DML (24 rules)

- `delete_database_stat`
- `delete_stat`
- `delete_table_spec`
- `delete_user_stat`
- `insert_explain_stat`
- `insert_stat`
- `ji_selection`
- `join_index_select_clause`
- `merge_stat`
- `mergeblockratio`
- `positioned_delete_stat`
- `positioned_update_stat`
- `select_and_consume_stat`
- `select_list`
- `select_stat`
- `selected_column`
- `selected_columns`
- `update_basic_form_stat`
- `update_stat`
- `update_table_spec`
- `update_upsert_form_stat`
- `update_with_from_stat`
- `with_deleted_rows`
- `xml_returning_spec`

### Queries (29 rules)

- `alter_join_index_stat`
- `character_set_phrase`
- `character_set_prefix`
- `cte_spec`
- `foreign_server_with_clause`
- `group_by_clause`
- `group_by_spec`
- `having_clause`
- `ji_joined_table`
- `join_clause`
- `join_index_add_option`
- `join_joined_spec`
- `join_on_clause`
- `join_source_spec`
- `latin_unicode_character_set_phrase`
- `local_order_by`
- `order_by_clause`
- `order_by_spec_asc_desc_only`
- `order_by_spec_full`
- `recursive_cte_spec`
- `regular_cte_spec`
- `subquery`
- `subquery_reference`
- `table_function_local_order_by_clause`
- `where_clause`
- `window_order_by`
- `with_clause`
- `with_clause_by_phrase`
- `with_clause_title_phrase`

### Window Functions (6 rules)

- `hash_or_partition_by`
- `window_partition_by`
- `window_rows`
- `window_spec`
- `window_spec_with_ties`
- `window_spec_without_rows`

### Procedural (18 rules)

- `begin_isolated_loading_stat`
- `begin_logging_stat`
- `begin_query_capture_stat`
- `begin_query_logging_stat`
- `begin_transaction_stat`
- `calendar_function`
- `end_isolated_loading_stat`
- `end_logging_stat`
- `end_query_capture_stat`
- `end_query_logging_all_rules`
- `end_query_logging_on_items`
- `end_query_logging_stat`
- `end_transaction_stat`
- `foreign_returns_clause`
- `interval_expr_start_end_phrase`
- `returns_clause`
- `returns_parameter_spec`
- `table_function_returns_clause`

### Constraints (4 rules)

- `database_default_map`
- `default_journal_table`
- `default_value`
- `default_value_control_phrase`

### Advanced (16 rules)

- `from_pivot_spec`
- `from_unpivot_spec`
- `pivot`
- `pivot_agg_func_spec`
- `pivot_expr_spec_list`
- `pivot_expr_spec_scalar`
- `pivot_for_phrase`
- `pivot_spec`
- `pivot_with_phrase`
- `pivot_with_spec`
- `qualify_clause`
- `td_unpivot_table_operator`
- `unpivot`
- `unpivot_column_name_spec_list`
- `unpivot_column_name_spec_single`
- `unpivot_spec`

### Other (511 rules)

- `abort_stat`
- `account_spec`
- `add_attribute_clause`
- `add_drop_range_option`
- `add_method_clause`
- `add_method_spec`
- `add_option`
- `add_specific_method_clause`
- `add_specific_method_spec`
- `after_journal`
- `aggregate_function`
- `aggregation_clause`
- `alias_name`
- `all_operator`
- `allocate_stat`
- `alter_column_spec`
- `alter_foreign_column_option`
- `alter_foreign_server_stat`
- `alter_function_stat`
- `alter_hash_index_stat`
- `alter_option`
- `alter_partitioning`
- `alter_range_expr`
- `alter_type_stat`
- `analysis_time_limit_clause`
- `analytic_function`
- `anchor_name`
- `argument`
- `arithmetic_function`
- `array_bounds`
- ... and 481 more

### Keywords (1135 total)

Top 50:

- `ABORT`
- `ABORTSESSION`
- `ABS`
- `ABSENT`
- `ACCESS`
- `ACCESS_LOCK`
- `ACCORDING`
- `ACCOUNT`
- `ACCUMULATE`
- `ACOS`
- `ACOSH`
- `ADD`
- `ADD_MONTHS`
- `ADMIN`
- `AFTER`
- `AG`
- `AGGREGATE`
- `ALIAS`
- `ALL`
- `ALLDBQL`
- `ALLOCATE`
- `ALLOCATION`
- `ALLOW`
- `ALLPARAMS`
- `ALLTDWM`
- `ALTER`
- `ALWAYS`
- `AMP`
- `AMPCOUNT`
- `ANALYSIS`
- `ANCHOR`
- `ANCHOR_HOUR`
- `ANCHOR_MILLISECOND`
- `ANCHOR_MINUTE`
- `ANCHOR_SECOND`
- `AND`
- `ANSIDATE`
- `ANY`
- `APPLNAME`
- `ARCHIVE`
- `ARGLPAREN`
- `ARRAY`
- `ARRAY_ADD`
- `ARRAY_AGG`
- `ARRAY_AVG`
- `ARRAY_COMPARE`
- `ARRAY_CONCAT`
- `ARRAY_COUNT_DISTINCT`
- `ARRAY_DIV`
- `ARRAY_EQ`
- ... and 1085 more

---

## TRINO

**Parser rules**: 125  
**Keywords**: 296  
**Lexer rules**: 340

### DML (3 rules)

- `mergeCase`
- `selectItem`
- `updateAssignment`

### Queries (4 rules)

- `groupBy`
- `joinCriteria`
- `joinType`
- `routineCharacteristic`

### Window Functions (3 rules)

- `windowDefinition`
- `windowFrame`
- `windowSpecification`

### Procedural (2 rules)

- `caseStatementWhenClause`
- `returnsClause`

### Other (113 rules)

- `aliasedRelation`
- `authorizationUser`
- `booleanExpression`
- `booleanValue`
- `callArgument`
- `columnAliases`
- `columnDefinition`
- `comparisonOperator`
- `comparisonQuantifier`
- `controlStatement`
- `copartitionTables`
- `descriptorArgument`
- `descriptorField`
- `elseClause`
- `elseIfClause`
- `emptyMatchHandling`
- `explainOption`
- `expression`
- `filter`
- `frameBound`
- `frameExtent`
- `functionDeclaration`
- `functionSpecification`
- `grantor`
- `groupingElement`
- `groupingSet`
- `identifier`
- `interval`
- `intervalField`
- `jsonArgument`
- ... and 83 more

### Keywords (296 total)

Top 50:

- `ABSENT`
- `ADD`
- `ADMIN`
- `AFTER`
- `ALL`
- `ALTER`
- `ANALYZE`
- `AND`
- `ANY`
- `ARRAY`
- `AS`
- `ASC`
- `AT`
- `AUTHORIZATION`
- `BEGIN`
- `BERNOULLI`
- `BETWEEN`
- `BOTH`
- `BY`
- `CALL`
- `CALLED`
- `CASCADE`
- `CASE`
- `CAST`
- `CATALOG`
- `CATALOGS`
- `COLUMN`
- `COLUMNS`
- `COMMENT`
- `COMMIT`
- `COMMITTED`
- `CONDITIONAL`
- `CONSTRAINT`
- `COPARTITION`
- `COUNT`
- `CREATE`
- `CROSS`
- `CUBE`
- `CURRENT`
- `CURRENT_CATALOG`
- `CURRENT_DATE`
- `CURRENT_PATH`
- `CURRENT_ROLE`
- `CURRENT_SCHEMA`
- `CURRENT_TIME`
- `CURRENT_TIMESTAMP`
- `CURRENT_USER`
- `DATA`
- `DATE`
- `DAY`
- ... and 246 more

---

## TSQL

**Parser rules**: 603  
**Keywords**: 1133  
**Lexer rules**: 1206

### DDL (34 rules)

- `alter_table`
- `alter_table_index_option`
- `alter_table_index_options`
- `create_columnstore_index`
- `create_columnstore_index_options`
- `create_database`
- `create_database_audit_specification`
- `create_database_option`
- `create_index`
- `create_index_options`
- `create_nonclustered_columnstore_index`
- `create_or_alter_function`
- `create_or_alter_procedure`
- `create_partition_function`
- `create_schema`
- `create_schema_azure_sql_dw_and_pdw`
- `create_table`
- `create_table_index_option`
- `create_table_index_options`
- `create_view`
- `create_xml_index`
- `create_xml_schema_collection`
- `drop_backward_compatible_index`
- `drop_database`
- `drop_database_audit_specification`
- `drop_database_encryption_key`
- `drop_database_scoped_credential`
- `drop_external_table`
- `drop_fulltext_index`
- `drop_index`
- `drop_relational_or_xml_or_spatial_index`
- `drop_table`
- `drop_view`
- `truncate_table`

### DML (24 rules)

- `db_update_option`
- `delete_statement`
- `delete_statement_from`
- `func_body_returns_select`
- `insert_column_id`
- `insert_column_name_list`
- `insert_statement`
- `insert_statement_value`
- `merge_matched`
- `merge_not_matched`
- `merge_statement`
- `on_delete`
- `on_update`
- `select_list`
- `select_list_elem`
- `select_order_by_clause`
- `select_statement`
- `select_statement_standalone`
- `update_elem`
- `update_elem_merge`
- `update_statement`
- `update_statistics`
- `update_statistics_option`
- `update_statistics_options`

### Queries (9 rules)

- `alter_assembly_with_clause`
- `cross_join`
- `group_by_item`
- `join_on`
- `non_ansi_join`
- `order_by_clause`
- `order_by_expression`
- `sql_union`
- `subquery`

### Window Functions (8 rules)

- `aggregate_windowed_function`
- `analytic_windowed_function`
- `over_clause`
- `ranking_windowed_function`
- `window_frame_bound`
- `window_frame_extent`
- `window_frame_following`
- `window_frame_preceding`

### Procedural (22 rules)

- `alter_endpoint`
- `begin_conversation_dialog`
- `begin_conversation_timer`
- `create_endpoint`
- `declare_cursor`
- `declare_local`
- `declare_set_cursor_common`
- `declare_set_cursor_common_partial`
- `declare_statement`
- `drop_endpoint`
- `end_conversation`
- `endpoint_authentication_clause`
- `endpoint_encryption_alogorithm_clause`
- `endpoint_listener_clause`
- `func_body_returns_scalar`
- `func_body_returns_table`
- `if_statement`
- `opendatasource`
- `raiseerror_statement`
- `return_statement`
- `send_conversation`
- `try_catch_statement`

### Constraints (8 rules)

- `check_constraint`
- `dbcc_checkconstraints`
- `dbcc_checkconstraints_option`
- `drop_default`
- `foreign_key_options`
- `null_notnull`
- `primary_key_options`
- `procedure_param_default_value`

### Advanced (5 rules)

- `materialized_column_definition`
- `pivot`
- `pivot_clause`
- `unpivot`
- `unpivot_clause`

### Other (493 rules)

- `action_specification`
- `add_or_modify_filegroups`
- `add_or_modify_files`
- `algorithm`
- `all_distinct_expression`
- `alter_application_role`
- `alter_assembly`
- `alter_assembly_add_clause`
- `alter_assembly_as`
- `alter_assembly_clause`
- `alter_assembly_client_file_clause`
- `alter_assembly_drop`
- `alter_assembly_drop_clause`
- `alter_assembly_drop_multiple_files`
- `alter_assembly_file_bits`
- `alter_assembly_file_name`
- `alter_assembly_from_clause`
- `alter_assembly_from_clause_start`
- `alter_assembly_start`
- `alter_assembly_with`
- `alter_asssembly_add_clause_start`
- `alter_asymmetric_key`
- `alter_asymmetric_key_start`
- `alter_authorization`
- `alter_authorization_for_azure_dw`
- `alter_authorization_for_parallel_dw`
- `alter_authorization_for_sql_database`
- `alter_authorization_start`
- `alter_availability_group`
- `alter_availability_group_options`
- ... and 463 more

### Keywords (1133 total)

Top 50:

- `ABORT`
- `ABORT_AFTER_WAIT`
- `ABS`
- `ABSENT`
- `ABSOLUTE`
- `ACCELERATED_DATABASE_RECOVERY`
- `ACCENT_SENSITIVITY`
- `ACCESS`
- `ACOS`
- `ACTION`
- `ACTIVATION`
- `ACTIVE`
- `ADD`
- `ADDRESS`
- `ADMINISTER`
- `AES`
- `AES_128`
- `AES_192`
- `AES_256`
- `AFFINITY`
- `AFTER`
- `AGGREGATE`
- `ALGORITHM`
- `ALL`
- `ALLOWED`
- `ALLOW_CONNECTIONS`
- `ALLOW_ENCRYPTED_VALUE_MODIFICATIONS`
- `ALLOW_MULTIPLE_EVENT_LOSS`
- `ALLOW_PAGE_LOCKS`
- `ALLOW_ROW_LOCKS`
- `ALLOW_SINGLE_EVENT_LOSS`
- `ALLOW_SNAPSHOT_ISOLATION`
- `ALL_CONSTRAINTS`
- `ALL_ERRORMSGS`
- `ALL_INDEXES`
- `ALL_LEVELS`
- `ALTER`
- `ALWAYS`
- `AND`
- `ANONYMOUS`
- `ANSI_DEFAULTS`
- `ANSI_NULLS`
- `ANSI_NULL_DEFAULT`
- `ANSI_NULL_DFLT_OFF`
- `ANSI_NULL_DFLT_ON`
- `ANSI_PADDING`
- `ANSI_WARNINGS`
- `ANY`
- `APPEND`
- `APPLICATION`
- ... and 1083 more

---
