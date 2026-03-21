# Complexity Analysis: MySQLParser

## Summary

| Complexity | Count | Percentage | Generation Strategy |
|------------|-------|------------|---------------------|
| ✅ SIMPLE   | 253 | 33.5% | Fully auto-generated |
| ⚠️ MEDIUM  | 300 | 39.7% | Template-assisted |
| ❌ COMPLEX | 202 | 26.8% | Manual implementation |
| **Total**  | 755 | 100% | |

---

## ✅ SIMPLE Rules (Auto-generatable)

**Count**: 253

- `alterServer`: Simple keyword sequence with few rule calls
- `restrict`: Token-only rule
- `withValidation`: Simple keyword sequence with few rule calls
- `removePartitioning`: Simple keyword sequence with few rule calls
- `undoTableSpaceOption`: Simple keyword sequence with few rule calls
- `viewCheckOption`: Token-only rule
- `createServer`: Simple keyword sequence with few rule calls
- `tsDataFile`: Simple keyword sequence with few rule calls
- `tsOptionWait`: Simple keyword sequence with few rule calls
- `viewAlgorithm`: Simple keyword sequence with few rule calls
- `viewSuid`: Simple keyword sequence with few rule calls
- `triggerFollowsPrecedesClause`: Simple keyword sequence with few rule calls
- `renamePair`: Simple keyword sequence with few rule calls
- `importStatement`: Simple keyword sequence with few rule calls
- `partitionDelete`: Simple keyword sequence with few rule calls
- `deleteStatementOption`: Token-only rule
- `insertLockOption`: Token-only rule
- `dataOrXml`: Token-only rule
- `loadDataLock`: Token-only rule
- `loadFrom`: Simple keyword sequence with few rule calls
- ... and 233 more

---

## ⚠️ MEDIUM Rules (Template-assisted)

**Count**: 300

- `alterDatabase`: 1 quantifiers
- `alterDatabaseOption`: 2 alternatives, 1 quantifiers
- `alterLogfileGroup`: 1 quantifiers
- `alterLogfileGroupOptions`: 2 quantifiers
- `alterLogfileGroupOption`: 3 alternatives
- `alterCommandsModifierList`: 1 quantifiers
- `alterCommandsModifier`: 3 alternatives
- `place`: 2 alternatives
- `alterOrderList`: 3 quantifiers, 4 rule calls
- `alterAlgorithmOption`: 1 quantifiers
- `alterLockOption`: 1 quantifiers
- `indexLockAndAlgorithm`: 2 alternatives, 2 quantifiers, 4 rule calls
- `allOrPartitionNameList`: 2 alternatives
- `alterTablespace`: 1 quantifiers, 7 rule calls
- `alterUndoTablespace`: 1 quantifiers
- `undoTableSpaceOptions`: 2 quantifiers
- `alterTablespaceOptions`: 2 quantifiers
- `alterTablespaceOption`: 7 alternatives, 1 quantifiers, 9 rule calls
- `changeTablespaceOption`: 3 alternatives, 1 quantifiers
- `alterInstanceStatement`: 2 alternatives, 1 quantifiers, 6 rule calls
- `createDatabase`: 2 quantifiers
- `createDatabaseOption`: 3 alternatives, 5 rule calls
- `routineString`: 2 alternatives
- `createUdf`: 2 quantifiers, 4 rule calls
- `routineCreateOption`: 2 alternatives, 1 quantifiers
- `routineAlterOptions`: 1 quantifiers
- `routineOption`: 7 alternatives, 12 rule calls
- `indexNameAndType`: 3 alternatives, 1 quantifiers, 5 rule calls
- `createLogfileGroup`: 1 quantifiers
- `logfileGroupOptions`: 2 quantifiers
- ... and 270 more

---

## ❌ COMPLEX Rules (Manual implementation)

**Count**: 202

These rules require manual implementation:

### `queries`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `query`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `simpleStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `alterStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `alterEvent`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `alterTable`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `alterTableActions`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `alterCommandList`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `standaloneAlterCommands`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `alterPartition`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `alterList`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `alterListItem`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `alterView`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `viewTail`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `viewQueryBlock`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `createStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `createTable`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `tableElementList`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `tableElement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `duplicateAsQe`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `asCreateQueryExpression`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `queryExpressionOrParens`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `queryExpressionWithOptLockingClauses`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `createRoutine`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `createProcedure`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `storedRoutineBody`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `createFunction`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `createIndex`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `createIndexTarget`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `createView`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `createTrigger`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `createEvent`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `callStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `deleteStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `doStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `handlerStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `handlerReadOrScan`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `insertStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `insertFromConstructor`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `insertValues`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `insertQueryExpression`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `valueList`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `values`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `insertUpdateList`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `loadStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `loadDataFileTail`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `replaceStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `selectStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `selectStatementWithInto`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `queryExpression`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `queryExpressionBody`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `queryExpressionParens`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `queryPrimary`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `querySpecification`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `subquery`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `havingClause`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `qualifyClause`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `windowClause`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `windowDefinition`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `windowSpec`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `windowSpecDetails`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `windowFrameClause`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `windowFrameExtent`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `windowFrameStart`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `windowFrameBetween`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `windowFrameBound`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `withClause`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `commonTableExpression`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `groupByClause`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `orderClause`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `fromClause`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `tableReferenceList`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `tableValueConstructor`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `rowValueExplicit`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `selectItemList`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `selectItem`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `whereClause`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `tableReference`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `escapedTableReference`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `joinedTable`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `tableFactor`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `derivedTable`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `tableReferenceListParens`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `tableFunction`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `columnsClause`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `jtColumn`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `updateStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `replicationStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `purgeOptions`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `sourceDefinition`
- **Reason**: Too many alternatives (34)
- **Approach**: Consider using dispatch table or redesigning rule structure

### `roleOrPrivilege`
- **Reason**: Too many alternatives (11)
- **Approach**: Consider using dispatch table or redesigning rule structure

### `installStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `installSetRvalue`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `installSetValue`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `installSetValueList`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `setStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `startOptionValueList`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `optionValueListContinued`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `optionValueNoOptionType`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `optionValue`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `startOptionValueListFollowingOptionType`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `optionValueFollowingOptionType`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `setExprOrDefault`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `showDatabasesStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `showTablesStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `showTriggersStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `showEventsStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `showTableStatusStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `showOpenTablesStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `showParseTreeStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `showColumnsStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `showKeysStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `showStatusStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `showVariablesStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `showCharacterSetStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `showCollationStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `showCreateProcedureStatusStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `showCreateFunctionStatusStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `otherAdministrativeStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `utilityStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `explainStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `explainableStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `expr`
- **Reason**: Has left-recursion
- **Approach**: Implement using precedence climbing or Pratt parser

### `boolPri`
- **Reason**: Has left-recursion
- **Approach**: Implement using precedence climbing or Pratt parser

### `predicate`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `predicateOperations`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `bitExpr`
- **Reason**: Has left-recursion
- **Approach**: Implement using precedence climbing or Pratt parser

### `simpleExpr`
- **Reason**: Has left-recursion
- **Approach**: Implement using precedence climbing or Pratt parser

### `sumExpr`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `groupingOperation`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `windowFunctionCall`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `windowingClause`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `leadLagInfo`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `jsonFunction`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `inSumExpr`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `runtimeFunctionCall`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `geometryFunction`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `trimFunction`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `substringFunction`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `functionCall`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `udfExprList`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `udfExpr`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `inExpressionUserVariableAssignment`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `whenExpression`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `thenExpression`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `elseExpression`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `castType`
- **Reason**: Too many alternatives (14)
- **Approach**: Consider using dispatch table or redesigning rule structure

### `exprList`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `exprListWithParentheses`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `exprWithParentheses`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `simpleExprWithParentheses`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `orderList`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `orderExpression`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `groupList`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `groupingExpression`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `compoundStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `returnStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `ifStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `ifBody`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `thenStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `compoundStatementList`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `caseStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `elseStatement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `labeledBlock`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `unlabeledBlock`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `beginEndBlock`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `labeledControl`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `unlabeledControl`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `loopBlock`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `whileDoBlock`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `repeatUntilBlock`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `spDeclarations`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `spDeclaration`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `variableDeclaration`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `handlerDeclaration`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `cursorDeclaration`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `signalInformationItemName`
- **Reason**: Too many alternatives (12)
- **Approach**: Consider using dispatch table or redesigning rule structure

### `schedule`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `columnDefinition`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `checkOrReferences`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `checkConstraint`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `tableConstraintDef`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `fieldDefinition`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `columnAttribute`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `keyListWithExpression`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `keyPartOrExpression`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `dataType`
- **Reason**: Too many alternatives (30)
- **Approach**: Consider using dispatch table or redesigning rule structure

### `createTableOptionsEtc`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `createPartitioningEtc`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `createTableOption`
- **Reason**: Too many alternatives (29)
- **Approach**: Consider using dispatch table or redesigning rule structure

### `partitionClause`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `partitionTypeDef`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `subPartitions`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `partitionDefinitions`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `partitionDefinition`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `partitionValuesIn`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `partitionValueItemListParen`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `partitionValueItem`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `updateList`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `updateElement`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `likeOrWhere`
- **Reason**: Has indirect recursion
- **Approach**: Requires careful handling to avoid infinite loops

### `identifierKeywordsAmbiguous2Labels`
- **Reason**: Too many alternatives (35)
- **Approach**: Consider using dispatch table or redesigning rule structure

---
