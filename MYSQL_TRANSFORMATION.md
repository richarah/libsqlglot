# Grammar Transformation Report: MySQLParser

## Transformations Applied

1. **Left Recursion Elimination**: Processed 759 rules
2. **Deterministic Alternatives**: Analyzed FIRST/FOLLOW sets
3. **Quantifier Normalization**: Flattened nested quantifiers

## Transformed Rules

### New Helper Rules (4)

Created to eliminate left recursion:

- `expr_tail`
- `boolPri_tail`
- `bitExpr_tail`
- `simpleExpr_tail`

---

## FIRST Sets (Sample)

- `queries`: {ALTER_SYMBOL, BEGIN_SYMBOL, CALL_SYMBOL, CHANGE_SYMBOL, CLONE_SYMBOL, ... (+42 more)}
- `query`: {ALTER_SYMBOL, BEGIN_SYMBOL, CALL_SYMBOL, CHANGE_SYMBOL, CLONE_SYMBOL, ... (+41 more)}
- `simpleStatement`: {ALTER_SYMBOL, CALL_SYMBOL, CHANGE_SYMBOL, CLONE_SYMBOL, COMMIT_SYMBOL, ... (+40 more)}
- `alterStatement`: {ALTER_SYMBOL}
- `alterDatabase`: {DATABASE_SYMBOL}
- `alterDatabaseOption`: {CHARSET_SYMBOL, CHAR_SYMBOL, COLLATE_SYMBOL, DEFAULT_SYMBOL, READ_SYMBOL}
- `alterEvent`: {DEFINER_SYMBOL, EVENT_SYMBOL}
- `alterLogfileGroup`: {LOGFILE_SYMBOL}
- `alterLogfileGroupOptions`: {ENGINE_SYMBOL, INITIAL_SIZE_SYMBOL, NO_WAIT_SYMBOL, STORAGE_SYMBOL, WAIT_SYMBOL}
- `alterLogfileGroupOption`: {ENGINE_SYMBOL, INITIAL_SIZE_SYMBOL, NO_WAIT_SYMBOL, STORAGE_SYMBOL, WAIT_SYMBOL}
- `alterServer`: {SERVER_SYMBOL}
- `alterTable`: {OFFLINE_SYMBOL, ONLINE_SYMBOL, TABLE_SYMBOL}
- `alterTableActions`: {ADD_SYMBOL, ALGORITHM_SYMBOL, ALTER_SYMBOL, ANALYZE_SYMBOL, CHANGE_SYMBOL, ... (+27 more)}
- `alterCommandList`: {ADD_SYMBOL, ALGORITHM_SYMBOL, ALTER_SYMBOL, CHANGE_SYMBOL, CHARSET_SYMBOL, ... (+14 more)}
- `alterCommandsModifierList`: {ALGORITHM_SYMBOL, LOCK_SYMBOL, WITHOUT_SYMBOL, WITH_SYMBOL}
- `standaloneAlterCommands`: {ADD_SYMBOL, ANALYZE_SYMBOL, CHECK_SYMBOL, COALESCE_SYMBOL, DISCARD_SYMBOL, ... (+8 more)}
- `alterPartition`: {ADD_SYMBOL, ANALYZE_SYMBOL, CHECK_SYMBOL, COALESCE_SYMBOL, DISCARD_SYMBOL, ... (+8 more)}
- `alterList`: {ADD_SYMBOL, ALTER_SYMBOL, CHANGE_SYMBOL, CHARSET_SYMBOL, CHAR_SYMBOL, ... (+10 more)}
- `alterCommandsModifier`: {ALGORITHM_SYMBOL, LOCK_SYMBOL, WITHOUT_SYMBOL, WITH_SYMBOL}
- `alterListItem`: {ADD_SYMBOL, ALTER_SYMBOL, CHANGE_SYMBOL, CONVERT_SYMBOL, DISABLE_SYMBOL, ... (+6 more)}