#pragma once

// Auto-generated grammar patterns from ANTLR grammars
// DO NOT EDIT MANUALLY
//
// This file contains token sequence patterns extracted from SQL dialect grammars.
// These patterns are used by libsqlglot's hand-written parser for validation
// and syntax checking.

#include "tokens.h"
#include "dialects.h"
#include <array>
#include <cstdint>

namespace libsqlglot {
namespace grammar {

/// Grammar pattern: a sequence of tokens representing a valid construct
struct Pattern {
    const char* name;
    Dialect dialect;
    const TokenType* tokens;
    uint8_t length;
    const char* pattern_type;
};

// CREATE_STATEMENT patterns

constexpr TokenType mysql_createStatement_tokens_0[] = {
    TokenType::CREATE,
    TokenType::createDatabase
};

constexpr TokenType mysql_createStatement_tokens_1[] = {
    TokenType::CREATE,
    TokenType::createTable
};

constexpr TokenType mysql_createStatement_tokens_2[] = {
    TokenType::CREATE,
    TokenType::createFunction
};

constexpr TokenType mysql_createStatement_tokens_3[] = {
    TokenType::CREATE,
    TokenType::createProcedure
};

constexpr TokenType mysql_createStatement_tokens_4[] = {
    TokenType::CREATE,
    TokenType::createUdf
};

constexpr TokenType mysql_createStatement_tokens_5[] = {
    TokenType::CREATE,
    TokenType::createLogfileGroup
};

constexpr TokenType mysql_createStatement_tokens_6[] = {
    TokenType::CREATE,
    TokenType::createView
};

constexpr TokenType mysql_createStatement_tokens_7[] = {
    TokenType::CREATE,
    TokenType::createTrigger
};

constexpr TokenType mysql_createStatement_tokens_8[] = {
    TokenType::CREATE,
    TokenType::createIndex
};

constexpr TokenType mysql_createStatement_tokens_9[] = {
    TokenType::CREATE,
    TokenType::createServer
};

constexpr TokenType mysql_createStatement_tokens_10[] = {
    TokenType::CREATE,
    TokenType::createTablespace
};

constexpr TokenType mysql_createStatement_tokens_11[] = {
    TokenType::CREATE,
    TokenType::createEvent
};

constexpr TokenType mysql_createStatement_tokens_12[] = {
    TokenType::CREATE,
    TokenType::createRole
};

constexpr TokenType mysql_createStatement_tokens_13[] = {
    TokenType::CREATE,
    TokenType::this,
    TokenType::isServerVersionGe80011,
    TokenType::createSpatialReference
};

constexpr TokenType mysql_createStatement_tokens_14[] = {
    TokenType::CREATE,
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::createUndoTablespace
};

constexpr TokenType mysql_createDatabase_tokens_15[] = {
    TokenType::DATABASE,
    TokenType::ifNotExists,
    TokenType::schemaName,
    TokenType::createDatabaseOption
};

constexpr TokenType mysql_createDatabaseOption_tokens_16[] = {
    TokenType::defaultCharset
};

constexpr TokenType mysql_createDatabaseOption_tokens_17[] = {
    TokenType::defaultCollation
};

constexpr TokenType mysql_createDatabaseOption_tokens_18[] = {
    TokenType::this,
    TokenType::isServerVersionGe80016,
    TokenType::defaultEncryption
};

constexpr TokenType mysql_createTable_tokens_19[] = {
    TokenType::TEMPORARY,
    TokenType::TABLE,
    TokenType::ifNotExists,
    TokenType::tableName,
    TokenType::LPAREN,
    TokenType::tableElementList,
    TokenType::RPAREN,
    TokenType::createTableOptionsEtc
};

constexpr TokenType mysql_createTable_tokens_20[] = {
    TokenType::TEMPORARY,
    TokenType::TABLE,
    TokenType::ifNotExists,
    TokenType::tableName,
    TokenType::LIKE,
    TokenType::tableRef
};

constexpr TokenType mysql_createTable_tokens_21[] = {
    TokenType::TEMPORARY,
    TokenType::TABLE,
    TokenType::ifNotExists,
    TokenType::tableName,
    TokenType::LPAREN,
    TokenType::LIKE,
    TokenType::tableRef,
    TokenType::RPAREN
};

constexpr TokenType mysql_asCreateQueryExpression_tokens_22[] = {
    TokenType::AS,
    TokenType::queryExpressionWithOptLockingClauses
};

constexpr TokenType mysql_createRoutine_tokens_23[] = {
    TokenType::CREATE,
    TokenType::createProcedure,
    TokenType::SEMICOLON,
    TokenType::EOF_TOKEN
};

constexpr TokenType mysql_createRoutine_tokens_24[] = {
    TokenType::CREATE,
    TokenType::createFunction,
    TokenType::SEMICOLON,
    TokenType::EOF_TOKEN
};

constexpr TokenType mysql_createRoutine_tokens_25[] = {
    TokenType::CREATE,
    TokenType::createUdf,
    TokenType::SEMICOLON,
    TokenType::EOF_TOKEN
};

constexpr TokenType mysql_createProcedure_tokens_26[] = {
    TokenType::definerClause,
    TokenType::PROCEDURE,
    TokenType::ifNotExists,
    TokenType::procedureName,
    TokenType::LPAREN,
    TokenType::procedureParameter,
    TokenType::COMMA,
    TokenType::procedureParameter,
    TokenType::RPAREN,
    TokenType::routineCreateOption,
    TokenType::storedRoutineBody
};

constexpr TokenType mysql_createFunction_tokens_27[] = {
    TokenType::definerClause,
    TokenType::FUNCTION,
    TokenType::ifNotExists,
    TokenType::functionName,
    TokenType::LPAREN,
    TokenType::functionParameter,
    TokenType::COMMA,
    TokenType::functionParameter,
    TokenType::RPAREN,
    TokenType::RETURNS,
    TokenType::typeWithOptCollate,
    TokenType::routineCreateOption,
    TokenType::storedRoutineBody
};

constexpr TokenType mysql_createUdf_tokens_28[] = {
    TokenType::AGGREGATE,
    TokenType::FUNCTION,
    TokenType::ifNotExists,
    TokenType::udfName,
    TokenType::RETURNS,
    TokenType::type,
    TokenType::STRING,
    TokenType::SONAME,
    TokenType::textLiteral
};

constexpr TokenType mysql_createUdf_tokens_29[] = {
    TokenType::AGGREGATE,
    TokenType::FUNCTION,
    TokenType::ifNotExists,
    TokenType::udfName,
    TokenType::RETURNS,
    TokenType::type,
    TokenType::INT,
    TokenType::SONAME,
    TokenType::textLiteral
};

constexpr TokenType mysql_createUdf_tokens_30[] = {
    TokenType::AGGREGATE,
    TokenType::FUNCTION,
    TokenType::ifNotExists,
    TokenType::udfName,
    TokenType::RETURNS,
    TokenType::type,
    TokenType::REAL,
    TokenType::SONAME,
    TokenType::textLiteral
};

constexpr TokenType mysql_createUdf_tokens_31[] = {
    TokenType::AGGREGATE,
    TokenType::FUNCTION,
    TokenType::ifNotExists,
    TokenType::udfName,
    TokenType::RETURNS,
    TokenType::type,
    TokenType::DECIMAL,
    TokenType::SONAME,
    TokenType::textLiteral
};

constexpr TokenType mysql_routineCreateOption_tokens_32[] = {
    TokenType::routineOption
};

constexpr TokenType mysql_routineCreateOption_tokens_33[] = {
    TokenType::NOT,
    TokenType::DETERMINISTIC
};

constexpr TokenType mysql_createIndex_tokens_34[] = {
    TokenType::onlineOption,
    TokenType::UNIQUE,
    TokenType::type,
    TokenType::INDEX,
    TokenType::indexName,
    TokenType::indexTypeClause,
    TokenType::createIndexTarget,
    TokenType::indexOption,
    TokenType::indexLockAndAlgorithm
};

constexpr TokenType mysql_createIndex_tokens_35[] = {
    TokenType::onlineOption,
    TokenType::type,
    TokenType::FULLTEXT,
    TokenType::INDEX,
    TokenType::indexName,
    TokenType::createIndexTarget,
    TokenType::fulltextIndexOption,
    TokenType::indexLockAndAlgorithm
};

constexpr TokenType mysql_createIndex_tokens_36[] = {
    TokenType::onlineOption,
    TokenType::type,
    TokenType::SPATIAL,
    TokenType::INDEX,
    TokenType::indexName,
    TokenType::createIndexTarget,
    TokenType::spatialIndexOption,
    TokenType::indexLockAndAlgorithm
};

constexpr TokenType mysql_createIndexTarget_tokens_37[] = {
    TokenType::ON,
    TokenType::tableRef,
    TokenType::keyListWithExpression
};

constexpr TokenType mysql_createLogfileGroup_tokens_38[] = {
    TokenType::LOGFILE,
    TokenType::GROUP,
    TokenType::logfileGroupName,
    TokenType::ADD,
    TokenType::UNDOFILE,
    TokenType::textLiteral,
    TokenType::logfileGroupOptions
};

constexpr TokenType mysql_createServer_tokens_39[] = {
    TokenType::SERVER,
    TokenType::serverName,
    TokenType::FOREIGN,
    TokenType::DATA,
    TokenType::WRAPPER,
    TokenType::textOrIdentifier,
    TokenType::serverOptions
};

constexpr TokenType mysql_createTablespace_tokens_40[] = {
    TokenType::TABLESPACE,
    TokenType::tablespaceName,
    TokenType::tsDataFileName,
    TokenType::USE,
    TokenType::LOGFILE,
    TokenType::GROUP,
    TokenType::logfileGroupRef,
    TokenType::tablespaceOptions
};

constexpr TokenType mysql_createUndoTablespace_tokens_41[] = {
    TokenType::UNDO,
    TokenType::TABLESPACE,
    TokenType::tablespaceName,
    TokenType::ADD,
    TokenType::tsDataFile,
    TokenType::undoTableSpaceOptions
};

constexpr TokenType mysql_createView_tokens_42[] = {
    TokenType::viewReplaceOrAlgorithm,
    TokenType::definerClause,
    TokenType::viewSuid,
    TokenType::VIEW,
    TokenType::viewName,
    TokenType::viewTail
};

constexpr TokenType mysql_createTrigger_tokens_43[] = {
    TokenType::definerClause,
    TokenType::TRIGGER,
    TokenType::ifNotExists,
    TokenType::triggerName,
    TokenType::timing,
    TokenType::BEFORE,
    TokenType::event,
    TokenType::INSERT,
    TokenType::ON,
    TokenType::tableRef,
    TokenType::FOR,
    TokenType::EACH,
    TokenType::ROW,
    TokenType::triggerFollowsPrecedesClause,
    TokenType::compoundStatement
};

constexpr TokenType mysql_createTrigger_tokens_44[] = {
    TokenType::definerClause,
    TokenType::TRIGGER,
    TokenType::ifNotExists,
    TokenType::triggerName,
    TokenType::timing,
    TokenType::BEFORE,
    TokenType::event,
    TokenType::UPDATE,
    TokenType::ON,
    TokenType::tableRef,
    TokenType::FOR,
    TokenType::EACH,
    TokenType::ROW,
    TokenType::triggerFollowsPrecedesClause,
    TokenType::compoundStatement
};

constexpr TokenType mysql_createTrigger_tokens_45[] = {
    TokenType::definerClause,
    TokenType::TRIGGER,
    TokenType::ifNotExists,
    TokenType::triggerName,
    TokenType::timing,
    TokenType::BEFORE,
    TokenType::event,
    TokenType::DELETE,
    TokenType::ON,
    TokenType::tableRef,
    TokenType::FOR,
    TokenType::EACH,
    TokenType::ROW,
    TokenType::triggerFollowsPrecedesClause,
    TokenType::compoundStatement
};

constexpr TokenType mysql_createTrigger_tokens_46[] = {
    TokenType::definerClause,
    TokenType::TRIGGER,
    TokenType::ifNotExists,
    TokenType::triggerName,
    TokenType::timing,
    TokenType::AFTER,
    TokenType::event,
    TokenType::INSERT,
    TokenType::ON,
    TokenType::tableRef,
    TokenType::FOR,
    TokenType::EACH,
    TokenType::ROW,
    TokenType::triggerFollowsPrecedesClause,
    TokenType::compoundStatement
};

constexpr TokenType mysql_createTrigger_tokens_47[] = {
    TokenType::definerClause,
    TokenType::TRIGGER,
    TokenType::ifNotExists,
    TokenType::triggerName,
    TokenType::timing,
    TokenType::AFTER,
    TokenType::event,
    TokenType::UPDATE,
    TokenType::ON,
    TokenType::tableRef,
    TokenType::FOR,
    TokenType::EACH,
    TokenType::ROW,
    TokenType::triggerFollowsPrecedesClause,
    TokenType::compoundStatement
};

constexpr TokenType mysql_createTrigger_tokens_48[] = {
    TokenType::definerClause,
    TokenType::TRIGGER,
    TokenType::ifNotExists,
    TokenType::triggerName,
    TokenType::timing,
    TokenType::AFTER,
    TokenType::event,
    TokenType::DELETE,
    TokenType::ON,
    TokenType::tableRef,
    TokenType::FOR,
    TokenType::EACH,
    TokenType::ROW,
    TokenType::triggerFollowsPrecedesClause,
    TokenType::compoundStatement
};

constexpr TokenType mysql_createEvent_tokens_49[] = {
    TokenType::definerClause,
    TokenType::EVENT,
    TokenType::ifNotExists,
    TokenType::eventName,
    TokenType::ON,
    TokenType::SCHEDULE,
    TokenType::schedule,
    TokenType::ON,
    TokenType::COMPLETION,
    TokenType::NOT,
    TokenType::PRESERVE,
    TokenType::ENABLE,
    TokenType::COMMENT,
    TokenType::textLiteral,
    TokenType::DO,
    TokenType::compoundStatement
};

constexpr TokenType mysql_createEvent_tokens_50[] = {
    TokenType::definerClause,
    TokenType::EVENT,
    TokenType::ifNotExists,
    TokenType::eventName,
    TokenType::ON,
    TokenType::SCHEDULE,
    TokenType::schedule,
    TokenType::ON,
    TokenType::COMPLETION,
    TokenType::NOT,
    TokenType::PRESERVE,
    TokenType::DISABLE,
    TokenType::ON,
    TokenType::replica,
    TokenType::COMMENT,
    TokenType::textLiteral,
    TokenType::DO,
    TokenType::compoundStatement
};

constexpr TokenType mysql_createRole_tokens_51[] = {
    TokenType::ROLE,
    TokenType::ifNotExists,
    TokenType::roleList
};

constexpr TokenType mysql_createSpatialReference_tokens_52[] = {
    TokenType::OR,
    TokenType::REPLACE,
    TokenType::SPATIAL,
    TokenType::REFERENCE,
    TokenType::SYSTEM,
    TokenType::real_ulonglong_number,
    TokenType::srsAttribute
};

constexpr TokenType mysql_createSpatialReference_tokens_53[] = {
    TokenType::SPATIAL,
    TokenType::REFERENCE,
    TokenType::SYSTEM,
    TokenType::ifNotExists,
    TokenType::real_ulonglong_number,
    TokenType::srsAttribute
};

constexpr TokenType mysql_createUserStatement_tokens_54[] = {
    TokenType::CREATE,
    TokenType::USER,
    TokenType::ifNotExists,
    TokenType::createUserList,
    TokenType::defaultRoleClause,
    TokenType::createUserTail
};

constexpr TokenType mysql_createUserTail_tokens_55[] = {
    TokenType::requireClause,
    TokenType::connectOptions,
    TokenType::accountLockPasswordExpireOptions,
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::userAttributes
};

constexpr TokenType mysql_showCreateDatabaseStatement_tokens_56[] = {
    TokenType::SHOW,
    TokenType::CREATE,
    TokenType::DATABASE,
    TokenType::ifNotExists,
    TokenType::schemaRef
};

constexpr TokenType mysql_showCreateTableStatement_tokens_57[] = {
    TokenType::SHOW,
    TokenType::CREATE,
    TokenType::TABLE,
    TokenType::tableRef
};

constexpr TokenType mysql_showCreateViewStatement_tokens_58[] = {
    TokenType::SHOW,
    TokenType::CREATE,
    TokenType::VIEW,
    TokenType::viewRef
};

constexpr TokenType mysql_showCreateProcedureStatement_tokens_59[] = {
    TokenType::SHOW,
    TokenType::CREATE,
    TokenType::PROCEDURE,
    TokenType::procedureRef
};

constexpr TokenType mysql_showCreateFunctionStatement_tokens_60[] = {
    TokenType::SHOW,
    TokenType::CREATE,
    TokenType::FUNCTION,
    TokenType::functionRef
};

constexpr TokenType mysql_showCreateTriggerStatement_tokens_61[] = {
    TokenType::SHOW,
    TokenType::CREATE,
    TokenType::TRIGGER,
    TokenType::triggerRef
};

constexpr TokenType mysql_showCreateProcedureStatusStatement_tokens_62[] = {
    TokenType::SHOW,
    TokenType::CREATE,
    TokenType::PROCEDURE,
    TokenType::STATUS,
    TokenType::likeOrWhere
};

constexpr TokenType mysql_showCreateFunctionStatusStatement_tokens_63[] = {
    TokenType::SHOW,
    TokenType::CREATE,
    TokenType::FUNCTION,
    TokenType::STATUS,
    TokenType::likeOrWhere
};

constexpr TokenType mysql_showCreateProcedureCodeStatement_tokens_64[] = {
    TokenType::SHOW,
    TokenType::CREATE,
    TokenType::PROCEDURE,
    TokenType::CODE,
    TokenType::procedureRef
};

constexpr TokenType mysql_showCreateFunctionCodeStatement_tokens_65[] = {
    TokenType::SHOW,
    TokenType::CREATE,
    TokenType::FUNCTION,
    TokenType::CODE,
    TokenType::functionRef
};

constexpr TokenType mysql_showCreateEventStatement_tokens_66[] = {
    TokenType::SHOW,
    TokenType::CREATE,
    TokenType::EVENT,
    TokenType::eventRef
};

constexpr TokenType mysql_showCreateUserStatement_tokens_67[] = {
    TokenType::SHOW,
    TokenType::CREATE,
    TokenType::USER,
    TokenType::user
};

constexpr TokenType mysql_createResourceGroup_tokens_68[] = {
    TokenType::CREATE,
    TokenType::RESOURCE,
    TokenType::GROUP,
    TokenType::identifier,
    TokenType::TYPE,
    TokenType::equal,
    TokenType::USER,
    TokenType::resourceGroupVcpuList,
    TokenType::resourceGroupPriority,
    TokenType::resourceGroupEnableDisable
};

constexpr TokenType mysql_createResourceGroup_tokens_69[] = {
    TokenType::CREATE,
    TokenType::RESOURCE,
    TokenType::GROUP,
    TokenType::identifier,
    TokenType::TYPE,
    TokenType::equal,
    TokenType::SYSTEM,
    TokenType::resourceGroupVcpuList,
    TokenType::resourceGroupPriority,
    TokenType::resourceGroupEnableDisable
};

constexpr TokenType mysql_createTableOptions_tokens_70[] = {
    TokenType::createTableOption,
    TokenType::COMMA,
    TokenType::createTableOption
};

constexpr TokenType mysql_createTableOptionsEtc_tokens_71[] = {
    TokenType::createTableOptions,
    TokenType::createPartitioningEtc
};

constexpr TokenType mysql_createTableOptionsEtc_tokens_72[] = {
    TokenType::createPartitioningEtc
};

constexpr TokenType mysql_createPartitioningEtc_tokens_73[] = {
    TokenType::partitionClause,
    TokenType::duplicateAsQe
};

constexpr TokenType mysql_createPartitioningEtc_tokens_74[] = {
    TokenType::duplicateAsQe
};

constexpr TokenType mysql_createTableOptionsSpaceSeparated_tokens_75[] = {
    TokenType::createTableOption
};

constexpr TokenType mysql_createTableOption_tokens_76[] = {
    TokenType::option,
    TokenType::ENGINE,
    TokenType::EQ,
    TokenType::engineRef
};

constexpr TokenType mysql_createTableOption_tokens_77[] = {
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::option,
    TokenType::SECONDARY_ENGINE,
    TokenType::equal,
    TokenType::NULL_KW
};

constexpr TokenType mysql_createTableOption_tokens_78[] = {
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::option,
    TokenType::SECONDARY_ENGINE,
    TokenType::equal,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_createTableOption_tokens_79[] = {
    TokenType::option,
    TokenType::MAX_ROWS,
    TokenType::EQ,
    TokenType::ulonglongNumber
};

constexpr TokenType mysql_createTableOption_tokens_80[] = {
    TokenType::option,
    TokenType::MIN_ROWS,
    TokenType::EQ,
    TokenType::ulonglongNumber
};

constexpr TokenType mysql_createTableOption_tokens_81[] = {
    TokenType::option,
    TokenType::AVG_ROW_LENGTH,
    TokenType::EQ,
    TokenType::ulonglongNumber
};

constexpr TokenType mysql_createTableOption_tokens_82[] = {
    TokenType::option,
    TokenType::PASSWORD,
    TokenType::EQ,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_createTableOption_tokens_83[] = {
    TokenType::option,
    TokenType::COMMENT,
    TokenType::EQ,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_createTableOption_tokens_84[] = {
    TokenType::option,
    TokenType::COMPRESSION,
    TokenType::EQ,
    TokenType::textString
};

constexpr TokenType mysql_createTableOption_tokens_85[] = {
    TokenType::option,
    TokenType::ENCRYPTION,
    TokenType::EQ,
    TokenType::textString
};

constexpr TokenType mysql_createTableOption_tokens_86[] = {
    TokenType::option,
    TokenType::AUTO_INCREMENT,
    TokenType::EQ,
    TokenType::ulonglongNumber
};

constexpr TokenType mysql_createTableOption_tokens_87[] = {
    TokenType::option,
    TokenType::PACK_KEYS,
    TokenType::EQ,
    TokenType::ternaryOption
};

constexpr TokenType mysql_createTableOption_tokens_88[] = {
    TokenType::option,
    TokenType::STATS_AUTO_RECALC,
    TokenType::EQ,
    TokenType::ternaryOption
};

constexpr TokenType mysql_createTableOption_tokens_89[] = {
    TokenType::option,
    TokenType::STATS_PERSISTENT,
    TokenType::EQ,
    TokenType::ternaryOption
};

constexpr TokenType mysql_createTableOption_tokens_90[] = {
    TokenType::option,
    TokenType::STATS_SAMPLE_PAGES,
    TokenType::EQ,
    TokenType::ternaryOption
};

constexpr TokenType mysql_createTableOption_tokens_91[] = {
    TokenType::option,
    TokenType::CHECKSUM,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_createTableOption_tokens_92[] = {
    TokenType::option,
    TokenType::TABLE_CHECKSUM,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_createTableOption_tokens_93[] = {
    TokenType::option,
    TokenType::DELAY_KEY_WRITE,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_createTableOption_tokens_94[] = {
    TokenType::option,
    TokenType::ROW_FORMAT,
    TokenType::EQ,
    TokenType::format,
    TokenType::DEFAULT
};

constexpr TokenType mysql_createTableOption_tokens_95[] = {
    TokenType::option,
    TokenType::ROW_FORMAT,
    TokenType::EQ,
    TokenType::format,
    TokenType::DYNAMIC
};

constexpr TokenType mysql_createTableOption_tokens_96[] = {
    TokenType::option,
    TokenType::ROW_FORMAT,
    TokenType::EQ,
    TokenType::format,
    TokenType::FIXED
};

constexpr TokenType mysql_createTableOption_tokens_97[] = {
    TokenType::option,
    TokenType::ROW_FORMAT,
    TokenType::EQ,
    TokenType::format,
    TokenType::COMPRESSED
};

constexpr TokenType mysql_createTableOption_tokens_98[] = {
    TokenType::option,
    TokenType::ROW_FORMAT,
    TokenType::EQ,
    TokenType::format,
    TokenType::REDUNDANT
};

constexpr TokenType mysql_createTableOption_tokens_99[] = {
    TokenType::option,
    TokenType::ROW_FORMAT,
    TokenType::EQ,
    TokenType::format,
    TokenType::COMPACT
};

constexpr TokenType mysql_createTableOption_tokens_100[] = {
    TokenType::option,
    TokenType::UNION,
    TokenType::EQ,
    TokenType::LPAREN,
    TokenType::tableRefList,
    TokenType::RPAREN
};

constexpr TokenType mysql_createTableOption_tokens_101[] = {
    TokenType::defaultCharset
};

constexpr TokenType mysql_createTableOption_tokens_102[] = {
    TokenType::defaultCollation
};

constexpr TokenType mysql_createTableOption_tokens_103[] = {
    TokenType::option,
    TokenType::INSERT_METHOD,
    TokenType::EQ,
    TokenType::method,
    TokenType::NO
};

constexpr TokenType mysql_createTableOption_tokens_104[] = {
    TokenType::option,
    TokenType::INSERT_METHOD,
    TokenType::EQ,
    TokenType::method,
    TokenType::FIRST
};

constexpr TokenType mysql_createTableOption_tokens_105[] = {
    TokenType::option,
    TokenType::INSERT_METHOD,
    TokenType::EQ,
    TokenType::method,
    TokenType::LAST
};

constexpr TokenType mysql_createTableOption_tokens_106[] = {
    TokenType::option,
    TokenType::DATA,
    TokenType::DIRECTORY,
    TokenType::EQ,
    TokenType::textString
};

constexpr TokenType mysql_createTableOption_tokens_107[] = {
    TokenType::option,
    TokenType::INDEX,
    TokenType::DIRECTORY,
    TokenType::EQ,
    TokenType::textString
};

constexpr TokenType mysql_createTableOption_tokens_108[] = {
    TokenType::option,
    TokenType::TABLESPACE,
    TokenType::EQ,
    TokenType::identifier
};

constexpr TokenType mysql_createTableOption_tokens_109[] = {
    TokenType::option,
    TokenType::STORAGE,
    TokenType::DISK
};

constexpr TokenType mysql_createTableOption_tokens_110[] = {
    TokenType::option,
    TokenType::STORAGE,
    TokenType::MEMORY
};

constexpr TokenType mysql_createTableOption_tokens_111[] = {
    TokenType::option,
    TokenType::CONNECTION,
    TokenType::EQ,
    TokenType::textString
};

constexpr TokenType mysql_createTableOption_tokens_112[] = {
    TokenType::option,
    TokenType::KEY_BLOCK_SIZE,
    TokenType::EQ,
    TokenType::ulonglongNumber
};

constexpr TokenType mysql_createTableOption_tokens_113[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::option,
    TokenType::STAR,
    TokenType::TRANSACTION
};

constexpr TokenType mysql_createTableOption_tokens_114[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::option,
    TokenType::ENGINE_ATTRIBUTE,
    TokenType::EQ,
    TokenType::jsonAttribute
};

constexpr TokenType mysql_createTableOption_tokens_115[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::option,
    TokenType::SECONDARY_ENGINE_ATTRIBUTE,
    TokenType::EQ,
    TokenType::jsonAttribute
};

constexpr TokenType mysql_createTableOption_tokens_116[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::tsOptionAutoextendSize
};

constexpr TokenType mysql_createUserList_tokens_117[] = {
    TokenType::createUser,
    TokenType::COMMA,
    TokenType::createUser
};

constexpr TokenType mysql_createUser_tokens_118[] = {
    TokenType::user,
    TokenType::identification,
    TokenType::createUserWithMfa
};

constexpr TokenType mysql_createUser_tokens_119[] = {
    TokenType::user,
    TokenType::identifiedWithPlugin,
    TokenType::initialAuth
};

constexpr TokenType mysql_createUser_tokens_120[] = {
    TokenType::user,
    TokenType::createUserWithMfa
};

constexpr TokenType mysql_createUserWithMfa_tokens_121[] = {
    TokenType::AND,
    TokenType::identification,
    TokenType::AND,
    TokenType::identification
};

// DELETE_STATEMENT patterns

constexpr TokenType mysql_deleteStatement_tokens_0[] = {
    TokenType::withClause,
    TokenType::DELETE,
    TokenType::deleteStatementOption,
    TokenType::FROM,
    TokenType::tableAliasRefList,
    TokenType::USING,
    TokenType::tableReferenceList,
    TokenType::whereClause
};

constexpr TokenType mysql_deleteStatement_tokens_1[] = {
    TokenType::withClause,
    TokenType::DELETE,
    TokenType::deleteStatementOption,
    TokenType::FROM,
    TokenType::tableRef,
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::tableAlias,
    TokenType::partitionDelete,
    TokenType::whereClause,
    TokenType::orderClause,
    TokenType::simpleLimitClause
};

constexpr TokenType mysql_deleteStatement_tokens_2[] = {
    TokenType::withClause,
    TokenType::DELETE,
    TokenType::deleteStatementOption,
    TokenType::tableAliasRefList,
    TokenType::FROM,
    TokenType::tableReferenceList,
    TokenType::whereClause
};

constexpr TokenType mysql_partitionDelete_tokens_3[] = {
    TokenType::PARTITION,
    TokenType::LPAREN,
    TokenType::identifierList,
    TokenType::RPAREN
};

constexpr TokenType mysql_deleteStatementOption_tokens_4[] = {
    TokenType::QUICK
};

constexpr TokenType mysql_deleteStatementOption_tokens_5[] = {
    TokenType::LOW_PRIORITY
};

constexpr TokenType mysql_deleteStatementOption_tokens_6[] = {
    TokenType::QUICK
};

constexpr TokenType mysql_deleteStatementOption_tokens_7[] = {
    TokenType::IGNORE
};

constexpr TokenType mysql_deleteOption_tokens_8[] = {
    TokenType::RESTRICT
};

constexpr TokenType mysql_deleteOption_tokens_9[] = {
    TokenType::CASCADE
};

constexpr TokenType mysql_deleteOption_tokens_10[] = {
    TokenType::SET,
    TokenType::nullLiteral
};

constexpr TokenType mysql_deleteOption_tokens_11[] = {
    TokenType::SET,
    TokenType::DEFAULT
};

constexpr TokenType mysql_deleteOption_tokens_12[] = {
    TokenType::NO,
    TokenType::ACTION
};

// DROP_STATEMENT patterns

constexpr TokenType mysql_dropStatement_tokens_0[] = {
    TokenType::DROP,
    TokenType::dropDatabase
};

constexpr TokenType mysql_dropStatement_tokens_1[] = {
    TokenType::DROP,
    TokenType::dropEvent
};

constexpr TokenType mysql_dropStatement_tokens_2[] = {
    TokenType::DROP,
    TokenType::dropFunction
};

constexpr TokenType mysql_dropStatement_tokens_3[] = {
    TokenType::DROP,
    TokenType::dropProcedure
};

constexpr TokenType mysql_dropStatement_tokens_4[] = {
    TokenType::DROP,
    TokenType::dropIndex
};

constexpr TokenType mysql_dropStatement_tokens_5[] = {
    TokenType::DROP,
    TokenType::dropLogfileGroup
};

constexpr TokenType mysql_dropStatement_tokens_6[] = {
    TokenType::DROP,
    TokenType::dropServer
};

constexpr TokenType mysql_dropStatement_tokens_7[] = {
    TokenType::DROP,
    TokenType::dropTable
};

constexpr TokenType mysql_dropStatement_tokens_8[] = {
    TokenType::DROP,
    TokenType::dropTableSpace
};

constexpr TokenType mysql_dropStatement_tokens_9[] = {
    TokenType::DROP,
    TokenType::dropTrigger
};

constexpr TokenType mysql_dropStatement_tokens_10[] = {
    TokenType::DROP,
    TokenType::dropView
};

constexpr TokenType mysql_dropStatement_tokens_11[] = {
    TokenType::DROP,
    TokenType::dropRole
};

constexpr TokenType mysql_dropStatement_tokens_12[] = {
    TokenType::DROP,
    TokenType::this,
    TokenType::isServerVersionGe80011,
    TokenType::dropSpatialReference
};

constexpr TokenType mysql_dropStatement_tokens_13[] = {
    TokenType::DROP,
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::dropUndoTablespace
};

constexpr TokenType mysql_dropDatabase_tokens_14[] = {
    TokenType::DATABASE,
    TokenType::ifExists,
    TokenType::schemaRef
};

constexpr TokenType mysql_dropEvent_tokens_15[] = {
    TokenType::EVENT,
    TokenType::ifExists,
    TokenType::eventRef
};

constexpr TokenType mysql_dropFunction_tokens_16[] = {
    TokenType::FUNCTION,
    TokenType::ifExists,
    TokenType::functionRef
};

constexpr TokenType mysql_dropProcedure_tokens_17[] = {
    TokenType::PROCEDURE,
    TokenType::ifExists,
    TokenType::procedureRef
};

constexpr TokenType mysql_dropIndex_tokens_18[] = {
    TokenType::onlineOption,
    TokenType::type,
    TokenType::INDEX,
    TokenType::indexRef,
    TokenType::ON,
    TokenType::tableRef,
    TokenType::indexLockAndAlgorithm
};

constexpr TokenType mysql_dropLogfileGroup_tokens_19[] = {
    TokenType::LOGFILE,
    TokenType::GROUP,
    TokenType::logfileGroupRef,
    TokenType::dropLogfileGroupOption,
    TokenType::COMMA,
    TokenType::dropLogfileGroupOption
};

constexpr TokenType mysql_dropLogfileGroupOption_tokens_20[] = {
    TokenType::tsOptionWait
};

constexpr TokenType mysql_dropLogfileGroupOption_tokens_21[] = {
    TokenType::tsOptionEngine
};

constexpr TokenType mysql_dropServer_tokens_22[] = {
    TokenType::SERVER,
    TokenType::ifExists,
    TokenType::serverRef
};

constexpr TokenType mysql_dropTable_tokens_23[] = {
    TokenType::TEMPORARY,
    TokenType::type,
    TokenType::TABLE,
    TokenType::ifExists,
    TokenType::tableRefList,
    TokenType::RESTRICT
};

constexpr TokenType mysql_dropTable_tokens_24[] = {
    TokenType::TEMPORARY,
    TokenType::type,
    TokenType::TABLE,
    TokenType::ifExists,
    TokenType::tableRefList,
    TokenType::CASCADE
};

constexpr TokenType mysql_dropTable_tokens_25[] = {
    TokenType::TEMPORARY,
    TokenType::type,
    TokenType::TABLES,
    TokenType::ifExists,
    TokenType::tableRefList,
    TokenType::RESTRICT
};

constexpr TokenType mysql_dropTable_tokens_26[] = {
    TokenType::TEMPORARY,
    TokenType::type,
    TokenType::TABLES,
    TokenType::ifExists,
    TokenType::tableRefList,
    TokenType::CASCADE
};

constexpr TokenType mysql_dropTableSpace_tokens_27[] = {
    TokenType::TABLESPACE,
    TokenType::tablespaceRef,
    TokenType::dropLogfileGroupOption,
    TokenType::COMMA,
    TokenType::dropLogfileGroupOption
};

constexpr TokenType mysql_dropTrigger_tokens_28[] = {
    TokenType::TRIGGER,
    TokenType::ifExists,
    TokenType::triggerRef
};

constexpr TokenType mysql_dropView_tokens_29[] = {
    TokenType::VIEW,
    TokenType::ifExists,
    TokenType::viewRefList,
    TokenType::RESTRICT
};

constexpr TokenType mysql_dropView_tokens_30[] = {
    TokenType::VIEW,
    TokenType::ifExists,
    TokenType::viewRefList,
    TokenType::CASCADE
};

constexpr TokenType mysql_dropRole_tokens_31[] = {
    TokenType::ROLE,
    TokenType::ifExists,
    TokenType::roleList
};

constexpr TokenType mysql_dropSpatialReference_tokens_32[] = {
    TokenType::SPATIAL,
    TokenType::REFERENCE,
    TokenType::SYSTEM,
    TokenType::ifExists,
    TokenType::real_ulonglong_number
};

constexpr TokenType mysql_dropUndoTablespace_tokens_33[] = {
    TokenType::UNDO,
    TokenType::TABLESPACE,
    TokenType::tablespaceRef,
    TokenType::undoTableSpaceOptions
};

constexpr TokenType mysql_dropUserStatement_tokens_34[] = {
    TokenType::DROP,
    TokenType::USER,
    TokenType::ifExists,
    TokenType::userList
};

constexpr TokenType mysql_dropResourceGroup_tokens_35[] = {
    TokenType::DROP,
    TokenType::RESOURCE,
    TokenType::GROUP,
    TokenType::resourceGroupRef,
    TokenType::FORCE
};

// EXPRESSION patterns

constexpr TokenType mysql_queryExpressionOrParens_tokens_0[] = {
    TokenType::queryExpression,
    TokenType::lockingClauseList
};

constexpr TokenType mysql_queryExpressionOrParens_tokens_1[] = {
    TokenType::queryExpressionParens
};

constexpr TokenType mysql_queryExpressionWithOptLockingClauses_tokens_2[] = {
    TokenType::queryExpression,
    TokenType::lockingClauseList
};

constexpr TokenType mysql_queryExpression_tokens_3[] = {
    TokenType::withClause,
    TokenType::queryExpressionBody,
    TokenType::orderClause,
    TokenType::limitClause
};

constexpr TokenType mysql_queryExpressionBody_tokens_4[] = {
    TokenType::queryPrimary,
    TokenType::UNION,
    TokenType::unionOption,
    TokenType::queryExpressionBody
};

constexpr TokenType mysql_queryExpressionBody_tokens_5[] = {
    TokenType::queryPrimary,
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::EXCEPT,
    TokenType::unionOption,
    TokenType::queryExpressionBody
};

constexpr TokenType mysql_queryExpressionBody_tokens_6[] = {
    TokenType::queryPrimary,
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::INTERSECT,
    TokenType::unionOption,
    TokenType::queryExpressionBody
};

constexpr TokenType mysql_queryExpressionBody_tokens_7[] = {
    TokenType::queryExpressionParens,
    TokenType::UNION,
    TokenType::unionOption,
    TokenType::queryExpressionBody
};

constexpr TokenType mysql_queryExpressionBody_tokens_8[] = {
    TokenType::queryExpressionParens,
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::EXCEPT,
    TokenType::unionOption,
    TokenType::queryExpressionBody
};

constexpr TokenType mysql_queryExpressionBody_tokens_9[] = {
    TokenType::queryExpressionParens,
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::INTERSECT,
    TokenType::unionOption,
    TokenType::queryExpressionBody
};

constexpr TokenType mysql_queryExpressionParens_tokens_10[] = {
    TokenType::LPAREN,
    TokenType::queryExpressionParens,
    TokenType::RPAREN
};

constexpr TokenType mysql_queryExpressionParens_tokens_11[] = {
    TokenType::LPAREN,
    TokenType::queryExpressionWithOptLockingClauses,
    TokenType::RPAREN
};

constexpr TokenType mysql_commonTableExpression_tokens_12[] = {
    TokenType::identifier,
    TokenType::columnInternalRefList,
    TokenType::AS,
    TokenType::subquery
};

constexpr TokenType mysql_setExprOrDefault_tokens_13[] = {
    TokenType::expr
};

constexpr TokenType mysql_setExprOrDefault_tokens_14[] = {
    TokenType::DEFAULT
};

constexpr TokenType mysql_setExprOrDefault_tokens_15[] = {
    TokenType::ON
};

constexpr TokenType mysql_setExprOrDefault_tokens_16[] = {
    TokenType::ALL
};

constexpr TokenType mysql_setExprOrDefault_tokens_17[] = {
    TokenType::BINARY
};

constexpr TokenType mysql_setExprOrDefault_tokens_18[] = {
    TokenType::ROW
};

constexpr TokenType mysql_setExprOrDefault_tokens_19[] = {
    TokenType::SYSTEM
};

constexpr TokenType mysql_expr_tokens_20[] = {
    TokenType::boolPri,
    TokenType::IS,
    TokenType::notRule,
    TokenType::type,
    TokenType::TRUE,
    TokenType::exprIs
};

constexpr TokenType mysql_expr_tokens_21[] = {
    TokenType::boolPri,
    TokenType::IS,
    TokenType::notRule,
    TokenType::type,
    TokenType::FALSE,
    TokenType::exprIs
};

constexpr TokenType mysql_expr_tokens_22[] = {
    TokenType::boolPri,
    TokenType::IS,
    TokenType::notRule,
    TokenType::type,
    TokenType::UNKNOWN,
    TokenType::exprIs
};

constexpr TokenType mysql_expr_tokens_23[] = {
    TokenType::NOT,
    TokenType::expr,
    TokenType::exprNot
};

constexpr TokenType mysql_expr_tokens_24[] = {
    TokenType::expr,
    TokenType::op,
    TokenType::AND,
    TokenType::expr,
    TokenType::exprAnd
};

constexpr TokenType mysql_expr_tokens_25[] = {
    TokenType::expr,
    TokenType::op,
    TokenType::AND,
    TokenType::expr,
    TokenType::exprAnd
};

constexpr TokenType mysql_expr_tokens_26[] = {
    TokenType::expr,
    TokenType::XOR,
    TokenType::expr,
    TokenType::exprXor
};

constexpr TokenType mysql_expr_tokens_27[] = {
    TokenType::expr,
    TokenType::op,
    TokenType::OR,
    TokenType::expr,
    TokenType::exprOr
};

constexpr TokenType mysql_expr_tokens_28[] = {
    TokenType::expr,
    TokenType::op,
    TokenType::OR,
    TokenType::expr,
    TokenType::exprOr
};

constexpr TokenType mysql_bitExpr_tokens_29[] = {
    TokenType::simpleExpr
};

constexpr TokenType mysql_bitExpr_tokens_30[] = {
    TokenType::bitExpr,
    TokenType::op,
    TokenType::CARET,
    TokenType::bitExpr
};

constexpr TokenType mysql_bitExpr_tokens_31[] = {
    TokenType::bitExpr,
    TokenType::op,
    TokenType::STAR,
    TokenType::bitExpr
};

constexpr TokenType mysql_bitExpr_tokens_32[] = {
    TokenType::bitExpr,
    TokenType::op,
    TokenType::SLASH,
    TokenType::bitExpr
};

constexpr TokenType mysql_bitExpr_tokens_33[] = {
    TokenType::bitExpr,
    TokenType::op,
    TokenType::PERCENT,
    TokenType::bitExpr
};

constexpr TokenType mysql_bitExpr_tokens_34[] = {
    TokenType::bitExpr,
    TokenType::op,
    TokenType::SLASH,
    TokenType::bitExpr
};

constexpr TokenType mysql_bitExpr_tokens_35[] = {
    TokenType::bitExpr,
    TokenType::op,
    TokenType::MOD,
    TokenType::bitExpr
};

constexpr TokenType mysql_bitExpr_tokens_36[] = {
    TokenType::bitExpr,
    TokenType::op,
    TokenType::PLUS,
    TokenType::bitExpr
};

constexpr TokenType mysql_bitExpr_tokens_37[] = {
    TokenType::bitExpr,
    TokenType::op,
    TokenType::MINUS,
    TokenType::bitExpr
};

constexpr TokenType mysql_bitExpr_tokens_38[] = {
    TokenType::bitExpr,
    TokenType::op,
    TokenType::PLUS,
    TokenType::INTERVAL,
    TokenType::expr,
    TokenType::interval
};

constexpr TokenType mysql_bitExpr_tokens_39[] = {
    TokenType::bitExpr,
    TokenType::op,
    TokenType::MINUS,
    TokenType::INTERVAL,
    TokenType::expr,
    TokenType::interval
};

constexpr TokenType mysql_bitExpr_tokens_40[] = {
    TokenType::bitExpr,
    TokenType::op,
    TokenType::SHIFT_LEFT,
    TokenType::bitExpr
};

constexpr TokenType mysql_bitExpr_tokens_41[] = {
    TokenType::bitExpr,
    TokenType::op,
    TokenType::SHIFT_RIGHT,
    TokenType::bitExpr
};

constexpr TokenType mysql_bitExpr_tokens_42[] = {
    TokenType::bitExpr,
    TokenType::op,
    TokenType::AMPERSAND,
    TokenType::bitExpr
};

constexpr TokenType mysql_bitExpr_tokens_43[] = {
    TokenType::bitExpr,
    TokenType::op,
    TokenType::PIPE,
    TokenType::bitExpr
};

constexpr TokenType mysql_simpleExpr_tokens_44[] = {
    TokenType::columnRef,
    TokenType::jsonOperator,
    TokenType::simpleExprColumnRef
};

constexpr TokenType mysql_simpleExpr_tokens_45[] = {
    TokenType::runtimeFunctionCall,
    TokenType::simpleExprRuntimeFunction
};

constexpr TokenType mysql_simpleExpr_tokens_46[] = {
    TokenType::functionCall,
    TokenType::simpleExprFunction
};

constexpr TokenType mysql_simpleExpr_tokens_47[] = {
    TokenType::simpleExpr,
    TokenType::COLLATE,
    TokenType::textOrIdentifier,
    TokenType::simpleExprCollate
};

constexpr TokenType mysql_simpleExpr_tokens_48[] = {
    TokenType::literalOrNull,
    TokenType::simpleExprLiteral
};

constexpr TokenType mysql_simpleExpr_tokens_49[] = {
    TokenType::PARAM_MARKER,
    TokenType::simpleExprParamMarker
};

constexpr TokenType mysql_simpleExpr_tokens_50[] = {
    TokenType::rvalueSystemOrUserVariable,
    TokenType::simpleExpressionRValue
};

constexpr TokenType mysql_simpleExpr_tokens_51[] = {
    TokenType::inExpressionUserVariableAssignment,
    TokenType::simpleExprUserVariableAssignment
};

constexpr TokenType mysql_simpleExpr_tokens_52[] = {
    TokenType::sumExpr,
    TokenType::simpleExprSum
};

constexpr TokenType mysql_simpleExpr_tokens_53[] = {
    TokenType::groupingOperation,
    TokenType::simpleExprGroupingOperation
};

constexpr TokenType mysql_simpleExpr_tokens_54[] = {
    TokenType::windowFunctionCall,
    TokenType::simpleExprWindowingFunction
};

constexpr TokenType mysql_simpleExpr_tokens_55[] = {
    TokenType::simpleExpr,
    TokenType::CONCAT_PIPES,
    TokenType::simpleExpr,
    TokenType::simpleExprConcat
};

constexpr TokenType mysql_simpleExpr_tokens_56[] = {
    TokenType::op,
    TokenType::PLUS,
    TokenType::simpleExpr,
    TokenType::simpleExprUnary
};

constexpr TokenType mysql_simpleExpr_tokens_57[] = {
    TokenType::op,
    TokenType::MINUS,
    TokenType::simpleExpr,
    TokenType::simpleExprUnary
};

constexpr TokenType mysql_simpleExpr_tokens_58[] = {
    TokenType::op,
    TokenType::TILDE,
    TokenType::simpleExpr,
    TokenType::simpleExprUnary
};

constexpr TokenType mysql_simpleExpr_tokens_59[] = {
    TokenType::not2Rule,
    TokenType::simpleExpr,
    TokenType::simpleExprNot
};

constexpr TokenType mysql_simpleExpr_tokens_60[] = {
    TokenType::ROW,
    TokenType::LPAREN,
    TokenType::exprList,
    TokenType::RPAREN,
    TokenType::simpleExprList
};

constexpr TokenType mysql_simpleExpr_tokens_61[] = {
    TokenType::EXISTS,
    TokenType::subquery,
    TokenType::simpleExprSubQuery
};

constexpr TokenType mysql_simpleExpr_tokens_62[] = {
    TokenType::LBRACE,
    TokenType::identifier,
    TokenType::expr,
    TokenType::RBRACE,
    TokenType::simpleExprOdbc
};

constexpr TokenType mysql_simpleExpr_tokens_63[] = {
    TokenType::MATCH,
    TokenType::identListArg,
    TokenType::AGAINST,
    TokenType::LPAREN,
    TokenType::bitExpr,
    TokenType::fulltextOptions,
    TokenType::RPAREN,
    TokenType::simpleExprMatch
};

constexpr TokenType mysql_simpleExpr_tokens_64[] = {
    TokenType::BINARY,
    TokenType::simpleExpr,
    TokenType::simpleExprBinary
};

constexpr TokenType mysql_simpleExpr_tokens_65[] = {
    TokenType::CAST,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::AT,
    TokenType::LOCAL,
    TokenType::AS,
    TokenType::castType,
    TokenType::arrayCast,
    TokenType::RPAREN,
    TokenType::simpleExprCast
};

constexpr TokenType mysql_simpleExpr_tokens_66[] = {
    TokenType::CAST,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::AT,
    TokenType::TIME,
    TokenType::ZONE,
    TokenType::INTERVAL,
    TokenType::textStringLiteral,
    TokenType::AS,
    TokenType::DATETIME,
    TokenType::typeDatetimePrecision,
    TokenType::RPAREN,
    TokenType::simpleExprCastTime
};

constexpr TokenType mysql_simpleExpr_tokens_67[] = {
    TokenType::CASE,
    TokenType::expr,
    TokenType::whenExpression,
    TokenType::thenExpression,
    TokenType::elseExpression,
    TokenType::END,
    TokenType::simpleExprCase
};

constexpr TokenType mysql_simpleExpr_tokens_68[] = {
    TokenType::CONVERT,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::castType,
    TokenType::RPAREN,
    TokenType::simpleExprConvert
};

constexpr TokenType mysql_simpleExpr_tokens_69[] = {
    TokenType::CONVERT,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::USING,
    TokenType::charsetName,
    TokenType::RPAREN,
    TokenType::simpleExprConvertUsing
};

constexpr TokenType mysql_simpleExpr_tokens_70[] = {
    TokenType::DEFAULT,
    TokenType::LPAREN,
    TokenType::simpleIdentifier,
    TokenType::RPAREN,
    TokenType::simpleExprDefault
};

constexpr TokenType mysql_simpleExpr_tokens_71[] = {
    TokenType::VALUES,
    TokenType::LPAREN,
    TokenType::simpleIdentifier,
    TokenType::RPAREN,
    TokenType::simpleExprValues
};

constexpr TokenType mysql_simpleExpr_tokens_72[] = {
    TokenType::INTERVAL,
    TokenType::expr,
    TokenType::interval,
    TokenType::PLUS,
    TokenType::expr,
    TokenType::simpleExprInterval
};

constexpr TokenType mysql_sumExpr_tokens_73[] = {
    TokenType::name,
    TokenType::AVG,
    TokenType::LPAREN,
    TokenType::DISTINCT,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_74[] = {
    TokenType::name,
    TokenType::BIT_AND,
    TokenType::LPAREN,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_75[] = {
    TokenType::name,
    TokenType::BIT_OR,
    TokenType::LPAREN,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_76[] = {
    TokenType::name,
    TokenType::BIT_XOR,
    TokenType::LPAREN,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_77[] = {
    TokenType::jsonFunction
};

constexpr TokenType mysql_sumExpr_tokens_78[] = {
    TokenType::name,
    TokenType::ST_COLLECT,
    TokenType::LPAREN,
    TokenType::DISTINCT,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_79[] = {
    TokenType::name,
    TokenType::COUNT,
    TokenType::LPAREN,
    TokenType::ALL,
    TokenType::STAR,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_80[] = {
    TokenType::name,
    TokenType::COUNT,
    TokenType::LPAREN,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_81[] = {
    TokenType::name,
    TokenType::COUNT,
    TokenType::LPAREN,
    TokenType::DISTINCT,
    TokenType::exprList,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_82[] = {
    TokenType::name,
    TokenType::MIN,
    TokenType::LPAREN,
    TokenType::DISTINCT,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_83[] = {
    TokenType::name,
    TokenType::MAX,
    TokenType::LPAREN,
    TokenType::DISTINCT,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_84[] = {
    TokenType::name,
    TokenType::STD,
    TokenType::LPAREN,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_85[] = {
    TokenType::name,
    TokenType::VARIANCE,
    TokenType::LPAREN,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_86[] = {
    TokenType::name,
    TokenType::STDDEV_SAMP,
    TokenType::LPAREN,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_87[] = {
    TokenType::name,
    TokenType::VAR_SAMP,
    TokenType::LPAREN,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_88[] = {
    TokenType::name,
    TokenType::SUM,
    TokenType::LPAREN,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_89[] = {
    TokenType::name,
    TokenType::SUM,
    TokenType::LPAREN,
    TokenType::DISTINCT,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_sumExpr_tokens_90[] = {
    TokenType::name,
    TokenType::GROUP_CONCAT,
    TokenType::LPAREN,
    TokenType::DISTINCT,
    TokenType::exprList,
    TokenType::orderClause,
    TokenType::SEPARATOR,
    TokenType::textString,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_inSumExpr_tokens_91[] = {
    TokenType::ALL,
    TokenType::expr
};

constexpr TokenType mysql_udfExprList_tokens_92[] = {
    TokenType::udfExpr,
    TokenType::COMMA,
    TokenType::udfExpr
};

constexpr TokenType mysql_udfExpr_tokens_93[] = {
    TokenType::expr,
    TokenType::selectAlias
};

constexpr TokenType mysql_inExpressionUserVariableAssignment_tokens_94[] = {
    TokenType::userVariable,
    TokenType::EQ,
    TokenType::expr
};

constexpr TokenType mysql_whenExpression_tokens_95[] = {
    TokenType::WHEN,
    TokenType::expr
};

constexpr TokenType mysql_thenExpression_tokens_96[] = {
    TokenType::THEN,
    TokenType::expr
};

constexpr TokenType mysql_elseExpression_tokens_97[] = {
    TokenType::ELSE,
    TokenType::expr
};

constexpr TokenType mysql_exprList_tokens_98[] = {
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr
};

constexpr TokenType mysql_exprListWithParentheses_tokens_99[] = {
    TokenType::LPAREN,
    TokenType::exprList,
    TokenType::RPAREN
};

constexpr TokenType mysql_exprWithParentheses_tokens_100[] = {
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_simpleExprWithParentheses_tokens_101[] = {
    TokenType::LPAREN,
    TokenType::simpleExpr,
    TokenType::RPAREN
};

constexpr TokenType mysql_orderExpression_tokens_102[] = {
    TokenType::expr,
    TokenType::direction
};

constexpr TokenType mysql_groupingExpression_tokens_103[] = {
    TokenType::expr
};

constexpr TokenType mysql_signalAllowedExpr_tokens_104[] = {
    TokenType::literal
};

constexpr TokenType mysql_signalAllowedExpr_tokens_105[] = {
    TokenType::rvalueSystemOrUserVariable
};

constexpr TokenType mysql_signalAllowedExpr_tokens_106[] = {
    TokenType::qualifiedIdentifier
};

constexpr TokenType mysql_keyListWithExpression_tokens_107[] = {
    TokenType::LPAREN,
    TokenType::keyPartOrExpression,
    TokenType::COMMA,
    TokenType::keyPartOrExpression,
    TokenType::RPAREN
};

constexpr TokenType mysql_keyPartOrExpression_tokens_108[] = {
    TokenType::keyPart
};

constexpr TokenType mysql_keyPartOrExpression_tokens_109[] = {
    TokenType::this,
    TokenType::isServerVersionGe80013,
    TokenType::exprWithParentheses,
    TokenType::direction
};

// INSERT_STATEMENT patterns

constexpr TokenType mysql_insertStatement_tokens_0[] = {
    TokenType::INSERT,
    TokenType::insertLockOption,
    TokenType::IGNORE,
    TokenType::INTO,
    TokenType::tableRef,
    TokenType::usePartition,
    TokenType::insertFromConstructor,
    TokenType::valuesReference,
    TokenType::insertUpdateList
};

constexpr TokenType mysql_insertStatement_tokens_1[] = {
    TokenType::INSERT,
    TokenType::insertLockOption,
    TokenType::IGNORE,
    TokenType::INTO,
    TokenType::tableRef,
    TokenType::usePartition,
    TokenType::SET,
    TokenType::updateList,
    TokenType::valuesReference,
    TokenType::insertUpdateList
};

constexpr TokenType mysql_insertStatement_tokens_2[] = {
    TokenType::INSERT,
    TokenType::insertLockOption,
    TokenType::IGNORE,
    TokenType::INTO,
    TokenType::tableRef,
    TokenType::usePartition,
    TokenType::insertQueryExpression,
    TokenType::insertUpdateList
};

constexpr TokenType mysql_insertLockOption_tokens_3[] = {
    TokenType::LOW_PRIORITY
};

constexpr TokenType mysql_insertLockOption_tokens_4[] = {
    TokenType::DELAYED
};

constexpr TokenType mysql_insertLockOption_tokens_5[] = {
    TokenType::HIGH_PRIORITY
};

constexpr TokenType mysql_insertFromConstructor_tokens_6[] = {
    TokenType::LPAREN,
    TokenType::fields,
    TokenType::RPAREN,
    TokenType::insertValues
};

constexpr TokenType mysql_insertValues_tokens_7[] = {
    TokenType::VALUES,
    TokenType::valueList
};

constexpr TokenType mysql_insertValues_tokens_8[] = {
    TokenType::VALUE,
    TokenType::valueList
};

constexpr TokenType mysql_insertQueryExpression_tokens_9[] = {
    TokenType::queryExpression
};

constexpr TokenType mysql_insertQueryExpression_tokens_10[] = {
    TokenType::queryExpressionParens
};

constexpr TokenType mysql_insertQueryExpression_tokens_11[] = {
    TokenType::LPAREN,
    TokenType::fields,
    TokenType::RPAREN,
    TokenType::queryExpressionWithOptLockingClauses
};

constexpr TokenType mysql_insertUpdateList_tokens_12[] = {
    TokenType::ON,
    TokenType::DUPLICATE,
    TokenType::KEY,
    TokenType::UPDATE,
    TokenType::updateList
};

constexpr TokenType mysql_insertIdentifier_tokens_13[] = {
    TokenType::columnRef
};

constexpr TokenType mysql_insertIdentifier_tokens_14[] = {
    TokenType::tableWild
};

// OTHER patterns

constexpr TokenType mysql_queries_tokens_0[] = {
    TokenType::query,
    TokenType::EOF_TOKEN
};

constexpr TokenType mysql_query_tokens_1[] = {
    TokenType::simpleStatement,
    TokenType::SEMICOLON
};

constexpr TokenType mysql_query_tokens_2[] = {
    TokenType::beginWork,
    TokenType::SEMICOLON
};

constexpr TokenType mysql_simpleStatement_tokens_3[] = {
    TokenType::alterStatement
};

constexpr TokenType mysql_simpleStatement_tokens_4[] = {
    TokenType::createStatement
};

constexpr TokenType mysql_simpleStatement_tokens_5[] = {
    TokenType::dropStatement
};

constexpr TokenType mysql_simpleStatement_tokens_6[] = {
    TokenType::renameTableStatement
};

constexpr TokenType mysql_simpleStatement_tokens_7[] = {
    TokenType::truncateTableStatement
};

constexpr TokenType mysql_simpleStatement_tokens_8[] = {
    TokenType::importStatement
};

constexpr TokenType mysql_simpleStatement_tokens_9[] = {
    TokenType::callStatement
};

constexpr TokenType mysql_simpleStatement_tokens_10[] = {
    TokenType::deleteStatement
};

constexpr TokenType mysql_simpleStatement_tokens_11[] = {
    TokenType::doStatement
};

constexpr TokenType mysql_simpleStatement_tokens_12[] = {
    TokenType::handlerStatement
};

constexpr TokenType mysql_simpleStatement_tokens_13[] = {
    TokenType::insertStatement
};

constexpr TokenType mysql_simpleStatement_tokens_14[] = {
    TokenType::loadStatement
};

constexpr TokenType mysql_simpleStatement_tokens_15[] = {
    TokenType::replaceStatement
};

constexpr TokenType mysql_simpleStatement_tokens_16[] = {
    TokenType::selectStatement
};

constexpr TokenType mysql_simpleStatement_tokens_17[] = {
    TokenType::updateStatement
};

constexpr TokenType mysql_simpleStatement_tokens_18[] = {
    TokenType::transactionOrLockingStatement
};

constexpr TokenType mysql_simpleStatement_tokens_19[] = {
    TokenType::replicationStatement
};

constexpr TokenType mysql_simpleStatement_tokens_20[] = {
    TokenType::preparedStatement
};

constexpr TokenType mysql_simpleStatement_tokens_21[] = {
    TokenType::cloneStatement
};

constexpr TokenType mysql_simpleStatement_tokens_22[] = {
    TokenType::accountManagementStatement
};

constexpr TokenType mysql_simpleStatement_tokens_23[] = {
    TokenType::tableAdministrationStatement
};

constexpr TokenType mysql_simpleStatement_tokens_24[] = {
    TokenType::uninstallStatement
};

constexpr TokenType mysql_simpleStatement_tokens_25[] = {
    TokenType::installStatement
};

constexpr TokenType mysql_simpleStatement_tokens_26[] = {
    TokenType::setStatement
};

constexpr TokenType mysql_simpleStatement_tokens_27[] = {
    TokenType::showDatabasesStatement
};

constexpr TokenType mysql_simpleStatement_tokens_28[] = {
    TokenType::showTablesStatement
};

constexpr TokenType mysql_simpleStatement_tokens_29[] = {
    TokenType::showTriggersStatement
};

constexpr TokenType mysql_simpleStatement_tokens_30[] = {
    TokenType::showEventsStatement
};

constexpr TokenType mysql_simpleStatement_tokens_31[] = {
    TokenType::showTableStatusStatement
};

constexpr TokenType mysql_simpleStatement_tokens_32[] = {
    TokenType::showOpenTablesStatement
};

constexpr TokenType mysql_simpleStatement_tokens_33[] = {
    TokenType::showParseTreeStatement
};

constexpr TokenType mysql_simpleStatement_tokens_34[] = {
    TokenType::showPluginsStatement
};

constexpr TokenType mysql_simpleStatement_tokens_35[] = {
    TokenType::showEngineLogsStatement
};

constexpr TokenType mysql_simpleStatement_tokens_36[] = {
    TokenType::showEngineMutexStatement
};

constexpr TokenType mysql_simpleStatement_tokens_37[] = {
    TokenType::showEngineStatusStatement
};

constexpr TokenType mysql_simpleStatement_tokens_38[] = {
    TokenType::showColumnsStatement
};

constexpr TokenType mysql_simpleStatement_tokens_39[] = {
    TokenType::showBinaryLogsStatement
};

constexpr TokenType mysql_simpleStatement_tokens_40[] = {
    TokenType::showBinaryLogStatusStatement
};

constexpr TokenType mysql_simpleStatement_tokens_41[] = {
    TokenType::showReplicasStatement
};

constexpr TokenType mysql_simpleStatement_tokens_42[] = {
    TokenType::showBinlogEventsStatement
};

constexpr TokenType mysql_simpleStatement_tokens_43[] = {
    TokenType::showRelaylogEventsStatement
};

constexpr TokenType mysql_simpleStatement_tokens_44[] = {
    TokenType::showKeysStatement
};

constexpr TokenType mysql_simpleStatement_tokens_45[] = {
    TokenType::showEnginesStatement
};

constexpr TokenType mysql_simpleStatement_tokens_46[] = {
    TokenType::showCountWarningsStatement
};

constexpr TokenType mysql_simpleStatement_tokens_47[] = {
    TokenType::showCountErrorsStatement
};

constexpr TokenType mysql_simpleStatement_tokens_48[] = {
    TokenType::showWarningsStatement
};

constexpr TokenType mysql_simpleStatement_tokens_49[] = {
    TokenType::showErrorsStatement
};

constexpr TokenType mysql_simpleStatement_tokens_50[] = {
    TokenType::showProfilesStatement
};

constexpr TokenType mysql_simpleStatement_tokens_51[] = {
    TokenType::showProfileStatement
};

constexpr TokenType mysql_simpleStatement_tokens_52[] = {
    TokenType::showStatusStatement
};

constexpr TokenType mysql_simpleStatement_tokens_53[] = {
    TokenType::showProcessListStatement
};

constexpr TokenType mysql_simpleStatement_tokens_54[] = {
    TokenType::showVariablesStatement
};

constexpr TokenType mysql_simpleStatement_tokens_55[] = {
    TokenType::showCharacterSetStatement
};

constexpr TokenType mysql_simpleStatement_tokens_56[] = {
    TokenType::showCollationStatement
};

constexpr TokenType mysql_simpleStatement_tokens_57[] = {
    TokenType::showPrivilegesStatement
};

constexpr TokenType mysql_simpleStatement_tokens_58[] = {
    TokenType::showGrantsStatement
};

constexpr TokenType mysql_simpleStatement_tokens_59[] = {
    TokenType::showCreateDatabaseStatement
};

constexpr TokenType mysql_simpleStatement_tokens_60[] = {
    TokenType::showCreateTableStatement
};

constexpr TokenType mysql_simpleStatement_tokens_61[] = {
    TokenType::showCreateViewStatement
};

constexpr TokenType mysql_simpleStatement_tokens_62[] = {
    TokenType::showMasterStatusStatement
};

constexpr TokenType mysql_simpleStatement_tokens_63[] = {
    TokenType::showReplicaStatusStatement
};

constexpr TokenType mysql_simpleStatement_tokens_64[] = {
    TokenType::showCreateProcedureStatement
};

constexpr TokenType mysql_simpleStatement_tokens_65[] = {
    TokenType::showCreateFunctionStatement
};

constexpr TokenType mysql_simpleStatement_tokens_66[] = {
    TokenType::showCreateTriggerStatement
};

constexpr TokenType mysql_simpleStatement_tokens_67[] = {
    TokenType::showCreateProcedureStatusStatement
};

constexpr TokenType mysql_simpleStatement_tokens_68[] = {
    TokenType::showCreateFunctionStatusStatement
};

constexpr TokenType mysql_simpleStatement_tokens_69[] = {
    TokenType::showCreateProcedureCodeStatement
};

constexpr TokenType mysql_simpleStatement_tokens_70[] = {
    TokenType::showCreateFunctionCodeStatement
};

constexpr TokenType mysql_simpleStatement_tokens_71[] = {
    TokenType::showCreateEventStatement
};

constexpr TokenType mysql_simpleStatement_tokens_72[] = {
    TokenType::showCreateUserStatement
};

constexpr TokenType mysql_simpleStatement_tokens_73[] = {
    TokenType::resourceGroupManagement
};

constexpr TokenType mysql_simpleStatement_tokens_74[] = {
    TokenType::otherAdministrativeStatement
};

constexpr TokenType mysql_simpleStatement_tokens_75[] = {
    TokenType::utilityStatement
};

constexpr TokenType mysql_simpleStatement_tokens_76[] = {
    TokenType::getDiagnosticsStatement
};

constexpr TokenType mysql_simpleStatement_tokens_77[] = {
    TokenType::signalStatement
};

constexpr TokenType mysql_simpleStatement_tokens_78[] = {
    TokenType::resignalStatement
};

constexpr TokenType mysql_alterStatement_tokens_79[] = {
    TokenType::ALTER,
    TokenType::alterTable
};

constexpr TokenType mysql_alterStatement_tokens_80[] = {
    TokenType::ALTER,
    TokenType::alterDatabase
};

constexpr TokenType mysql_alterStatement_tokens_81[] = {
    TokenType::ALTER,
    TokenType::PROCEDURE,
    TokenType::procedureRef,
    TokenType::routineAlterOptions
};

constexpr TokenType mysql_alterStatement_tokens_82[] = {
    TokenType::ALTER,
    TokenType::FUNCTION,
    TokenType::functionRef,
    TokenType::routineAlterOptions
};

constexpr TokenType mysql_alterStatement_tokens_83[] = {
    TokenType::ALTER,
    TokenType::alterView
};

constexpr TokenType mysql_alterStatement_tokens_84[] = {
    TokenType::ALTER,
    TokenType::alterEvent
};

constexpr TokenType mysql_alterStatement_tokens_85[] = {
    TokenType::ALTER,
    TokenType::alterTablespace
};

constexpr TokenType mysql_alterStatement_tokens_86[] = {
    TokenType::ALTER,
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::alterUndoTablespace
};

constexpr TokenType mysql_alterStatement_tokens_87[] = {
    TokenType::ALTER,
    TokenType::alterLogfileGroup
};

constexpr TokenType mysql_alterStatement_tokens_88[] = {
    TokenType::ALTER,
    TokenType::alterServer
};

constexpr TokenType mysql_alterStatement_tokens_89[] = {
    TokenType::ALTER,
    TokenType::alterInstanceStatement
};

constexpr TokenType mysql_alterDatabase_tokens_90[] = {
    TokenType::DATABASE,
    TokenType::schemaRef,
    TokenType::alterDatabaseOption
};

constexpr TokenType mysql_alterDatabaseOption_tokens_91[] = {
    TokenType::createDatabaseOption
};

constexpr TokenType mysql_alterDatabaseOption_tokens_92[] = {
    TokenType::READ,
    TokenType::ONLY,
    TokenType::EQ,
    TokenType::ternaryOption
};

constexpr TokenType mysql_alterEvent_tokens_93[] = {
    TokenType::definerClause,
    TokenType::EVENT,
    TokenType::eventRef,
    TokenType::ON,
    TokenType::SCHEDULE,
    TokenType::schedule,
    TokenType::ON,
    TokenType::COMPLETION,
    TokenType::NOT,
    TokenType::PRESERVE,
    TokenType::RENAME,
    TokenType::TO,
    TokenType::identifier,
    TokenType::ENABLE,
    TokenType::COMMENT,
    TokenType::textLiteral,
    TokenType::DO,
    TokenType::compoundStatement
};

constexpr TokenType mysql_alterEvent_tokens_94[] = {
    TokenType::definerClause,
    TokenType::EVENT,
    TokenType::eventRef,
    TokenType::ON,
    TokenType::SCHEDULE,
    TokenType::schedule,
    TokenType::ON,
    TokenType::COMPLETION,
    TokenType::NOT,
    TokenType::PRESERVE,
    TokenType::RENAME,
    TokenType::TO,
    TokenType::identifier,
    TokenType::DISABLE,
    TokenType::ON,
    TokenType::replica,
    TokenType::COMMENT,
    TokenType::textLiteral,
    TokenType::DO,
    TokenType::compoundStatement
};

constexpr TokenType mysql_alterLogfileGroup_tokens_95[] = {
    TokenType::LOGFILE,
    TokenType::GROUP,
    TokenType::logfileGroupRef,
    TokenType::ADD,
    TokenType::UNDOFILE,
    TokenType::textLiteral,
    TokenType::alterLogfileGroupOptions
};

constexpr TokenType mysql_alterLogfileGroupOptions_tokens_96[] = {
    TokenType::alterLogfileGroupOption,
    TokenType::COMMA,
    TokenType::alterLogfileGroupOption
};

constexpr TokenType mysql_alterLogfileGroupOption_tokens_97[] = {
    TokenType::tsOptionInitialSize
};

constexpr TokenType mysql_alterLogfileGroupOption_tokens_98[] = {
    TokenType::tsOptionEngine
};

constexpr TokenType mysql_alterLogfileGroupOption_tokens_99[] = {
    TokenType::tsOptionWait
};

constexpr TokenType mysql_alterServer_tokens_100[] = {
    TokenType::SERVER,
    TokenType::serverRef,
    TokenType::serverOptions
};

constexpr TokenType mysql_alterTable_tokens_101[] = {
    TokenType::onlineOption,
    TokenType::TABLE,
    TokenType::tableRef,
    TokenType::alterTableActions
};

constexpr TokenType mysql_alterTableActions_tokens_102[] = {
    TokenType::alterCommandList,
    TokenType::partitionClause
};

constexpr TokenType mysql_alterTableActions_tokens_103[] = {
    TokenType::alterCommandList,
    TokenType::removePartitioning
};

constexpr TokenType mysql_alterTableActions_tokens_104[] = {
    TokenType::partitionClause
};

constexpr TokenType mysql_alterTableActions_tokens_105[] = {
    TokenType::removePartitioning
};

constexpr TokenType mysql_alterTableActions_tokens_106[] = {
    TokenType::alterCommandsModifierList,
    TokenType::COMMA,
    TokenType::standaloneAlterCommands
};

constexpr TokenType mysql_alterCommandList_tokens_107[] = {
    TokenType::alterCommandsModifierList
};

constexpr TokenType mysql_alterCommandList_tokens_108[] = {
    TokenType::alterCommandsModifierList,
    TokenType::COMMA,
    TokenType::alterList
};

constexpr TokenType mysql_alterCommandsModifierList_tokens_109[] = {
    TokenType::alterCommandsModifier,
    TokenType::COMMA,
    TokenType::alterCommandsModifier
};

constexpr TokenType mysql_standaloneAlterCommands_tokens_110[] = {
    TokenType::DISCARD,
    TokenType::TABLESPACE
};

constexpr TokenType mysql_standaloneAlterCommands_tokens_111[] = {
    TokenType::IMPORT,
    TokenType::TABLESPACE
};

constexpr TokenType mysql_standaloneAlterCommands_tokens_112[] = {
    TokenType::alterPartition
};

constexpr TokenType mysql_standaloneAlterCommands_tokens_113[] = {
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::SECONDARY_LOAD
};

constexpr TokenType mysql_standaloneAlterCommands_tokens_114[] = {
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::SECONDARY_UNLOAD
};

constexpr TokenType mysql_alterPartition_tokens_115[] = {
    TokenType::ADD,
    TokenType::PARTITION,
    TokenType::noWriteToBinLog,
    TokenType::partitionDefinitions
};

constexpr TokenType mysql_alterPartition_tokens_116[] = {
    TokenType::ADD,
    TokenType::PARTITION,
    TokenType::noWriteToBinLog,
    TokenType::PARTITIONS,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_alterPartition_tokens_117[] = {
    TokenType::DROP,
    TokenType::PARTITION,
    TokenType::identifierList
};

constexpr TokenType mysql_alterPartition_tokens_118[] = {
    TokenType::REBUILD,
    TokenType::PARTITION,
    TokenType::noWriteToBinLog,
    TokenType::allOrPartitionNameList
};

constexpr TokenType mysql_alterPartition_tokens_119[] = {
    TokenType::OPTIMIZE,
    TokenType::PARTITION,
    TokenType::noWriteToBinLog,
    TokenType::allOrPartitionNameList,
    TokenType::noWriteToBinLog
};

constexpr TokenType mysql_alterPartition_tokens_120[] = {
    TokenType::ANALYZE,
    TokenType::PARTITION,
    TokenType::noWriteToBinLog,
    TokenType::allOrPartitionNameList
};

constexpr TokenType mysql_alterPartition_tokens_121[] = {
    TokenType::CHECK,
    TokenType::PARTITION,
    TokenType::allOrPartitionNameList,
    TokenType::checkOption
};

constexpr TokenType mysql_alterPartition_tokens_122[] = {
    TokenType::REPAIR,
    TokenType::PARTITION,
    TokenType::noWriteToBinLog,
    TokenType::allOrPartitionNameList,
    TokenType::repairType
};

constexpr TokenType mysql_alterPartition_tokens_123[] = {
    TokenType::COALESCE,
    TokenType::PARTITION,
    TokenType::noWriteToBinLog,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_alterPartition_tokens_124[] = {
    TokenType::TRUNCATE,
    TokenType::PARTITION,
    TokenType::allOrPartitionNameList
};

constexpr TokenType mysql_alterPartition_tokens_125[] = {
    TokenType::REORGANIZE,
    TokenType::PARTITION,
    TokenType::noWriteToBinLog,
    TokenType::identifierList,
    TokenType::INTO,
    TokenType::partitionDefinitions
};

constexpr TokenType mysql_alterPartition_tokens_126[] = {
    TokenType::EXCHANGE,
    TokenType::PARTITION,
    TokenType::identifier,
    TokenType::WITH,
    TokenType::TABLE,
    TokenType::tableRef,
    TokenType::withValidation
};

constexpr TokenType mysql_alterPartition_tokens_127[] = {
    TokenType::DISCARD,
    TokenType::PARTITION,
    TokenType::allOrPartitionNameList,
    TokenType::TABLESPACE
};

constexpr TokenType mysql_alterPartition_tokens_128[] = {
    TokenType::IMPORT,
    TokenType::PARTITION,
    TokenType::allOrPartitionNameList,
    TokenType::TABLESPACE
};

constexpr TokenType mysql_alterList_tokens_129[] = {
    TokenType::alterListItem,
    TokenType::COMMA,
    TokenType::alterListItem
};

constexpr TokenType mysql_alterList_tokens_130[] = {
    TokenType::alterListItem,
    TokenType::COMMA,
    TokenType::alterCommandsModifier
};

constexpr TokenType mysql_alterList_tokens_131[] = {
    TokenType::alterListItem,
    TokenType::COMMA,
    TokenType::createTableOptionsSpaceSeparated
};

constexpr TokenType mysql_alterList_tokens_132[] = {
    TokenType::createTableOptionsSpaceSeparated,
    TokenType::COMMA,
    TokenType::alterListItem
};

constexpr TokenType mysql_alterList_tokens_133[] = {
    TokenType::createTableOptionsSpaceSeparated,
    TokenType::COMMA,
    TokenType::alterCommandsModifier
};

constexpr TokenType mysql_alterList_tokens_134[] = {
    TokenType::createTableOptionsSpaceSeparated,
    TokenType::COMMA,
    TokenType::createTableOptionsSpaceSeparated
};

constexpr TokenType mysql_alterCommandsModifier_tokens_135[] = {
    TokenType::alterAlgorithmOption
};

constexpr TokenType mysql_alterCommandsModifier_tokens_136[] = {
    TokenType::alterLockOption
};

constexpr TokenType mysql_alterCommandsModifier_tokens_137[] = {
    TokenType::withValidation
};

constexpr TokenType mysql_alterListItem_tokens_138[] = {
    TokenType::ADD,
    TokenType::COLUMN,
    TokenType::identifier,
    TokenType::fieldDefinition,
    TokenType::checkOrReferences,
    TokenType::place
};

constexpr TokenType mysql_alterListItem_tokens_139[] = {
    TokenType::ADD,
    TokenType::COLUMN,
    TokenType::LPAREN,
    TokenType::tableElementList,
    TokenType::RPAREN
};

constexpr TokenType mysql_alterListItem_tokens_140[] = {
    TokenType::ADD,
    TokenType::tableConstraintDef
};

constexpr TokenType mysql_alterListItem_tokens_141[] = {
    TokenType::CHANGE,
    TokenType::COLUMN,
    TokenType::columnInternalRef,
    TokenType::identifier,
    TokenType::fieldDefinition,
    TokenType::place
};

constexpr TokenType mysql_alterListItem_tokens_142[] = {
    TokenType::MODIFY,
    TokenType::COLUMN,
    TokenType::columnInternalRef,
    TokenType::fieldDefinition,
    TokenType::place
};

constexpr TokenType mysql_alterListItem_tokens_143[] = {
    TokenType::DROP,
    TokenType::COLUMN,
    TokenType::columnInternalRef,
    TokenType::restrict
};

constexpr TokenType mysql_alterListItem_tokens_144[] = {
    TokenType::DROP,
    TokenType::FOREIGN,
    TokenType::KEY,
    TokenType::columnInternalRef
};

constexpr TokenType mysql_alterListItem_tokens_145[] = {
    TokenType::DROP,
    TokenType::PRIMARY,
    TokenType::KEY
};

constexpr TokenType mysql_alterListItem_tokens_146[] = {
    TokenType::DROP,
    TokenType::keyOrIndex,
    TokenType::indexRef
};

constexpr TokenType mysql_alterListItem_tokens_147[] = {
    TokenType::DROP,
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::CHECK,
    TokenType::identifier
};

constexpr TokenType mysql_alterListItem_tokens_148[] = {
    TokenType::DROP,
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::CONSTRAINT,
    TokenType::identifier
};

constexpr TokenType mysql_alterListItem_tokens_149[] = {
    TokenType::DISABLE,
    TokenType::KEYS
};

constexpr TokenType mysql_alterListItem_tokens_150[] = {
    TokenType::ENABLE,
    TokenType::KEYS
};

constexpr TokenType mysql_alterListItem_tokens_151[] = {
    TokenType::ALTER,
    TokenType::COLUMN,
    TokenType::columnInternalRef,
    TokenType::SET,
    TokenType::DEFAULT,
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_alterListItem_tokens_152[] = {
    TokenType::ALTER,
    TokenType::COLUMN,
    TokenType::columnInternalRef,
    TokenType::SET,
    TokenType::DEFAULT,
    TokenType::signedLiteralOrNull
};

constexpr TokenType mysql_alterListItem_tokens_153[] = {
    TokenType::ALTER,
    TokenType::COLUMN,
    TokenType::columnInternalRef,
    TokenType::DROP,
    TokenType::DEFAULT
};

constexpr TokenType mysql_alterListItem_tokens_154[] = {
    TokenType::ALTER,
    TokenType::COLUMN,
    TokenType::columnInternalRef,
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::SET,
    TokenType::visibility
};

constexpr TokenType mysql_alterListItem_tokens_155[] = {
    TokenType::ALTER,
    TokenType::INDEX,
    TokenType::indexRef,
    TokenType::visibility
};

constexpr TokenType mysql_alterListItem_tokens_156[] = {
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::ALTER,
    TokenType::CHECK,
    TokenType::identifier,
    TokenType::constraintEnforcement
};

constexpr TokenType mysql_alterListItem_tokens_157[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::ALTER,
    TokenType::CONSTRAINT,
    TokenType::identifier,
    TokenType::constraintEnforcement
};

constexpr TokenType mysql_alterListItem_tokens_158[] = {
    TokenType::RENAME,
    TokenType::COLUMN,
    TokenType::columnInternalRef,
    TokenType::TO,
    TokenType::identifier
};

constexpr TokenType mysql_alterListItem_tokens_159[] = {
    TokenType::RENAME,
    TokenType::TO,
    TokenType::tableName
};

constexpr TokenType mysql_alterListItem_tokens_160[] = {
    TokenType::RENAME,
    TokenType::AS,
    TokenType::tableName
};

constexpr TokenType mysql_alterListItem_tokens_161[] = {
    TokenType::RENAME,
    TokenType::keyOrIndex,
    TokenType::indexRef,
    TokenType::TO,
    TokenType::indexName
};

constexpr TokenType mysql_alterListItem_tokens_162[] = {
    TokenType::CONVERT,
    TokenType::TO,
    TokenType::charset,
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::DEFAULT,
    TokenType::collate
};

constexpr TokenType mysql_alterListItem_tokens_163[] = {
    TokenType::CONVERT,
    TokenType::TO,
    TokenType::charset,
    TokenType::charsetName,
    TokenType::collate
};

constexpr TokenType mysql_alterListItem_tokens_164[] = {
    TokenType::FORCE
};

constexpr TokenType mysql_alterListItem_tokens_165[] = {
    TokenType::ORDER,
    TokenType::BY,
    TokenType::alterOrderList
};

constexpr TokenType mysql_place_tokens_166[] = {
    TokenType::AFTER,
    TokenType::identifier
};

constexpr TokenType mysql_place_tokens_167[] = {
    TokenType::FIRST
};

constexpr TokenType mysql_restrict_tokens_168[] = {
    TokenType::RESTRICT
};

constexpr TokenType mysql_restrict_tokens_169[] = {
    TokenType::CASCADE
};

constexpr TokenType mysql_alterOrderList_tokens_170[] = {
    TokenType::identifier,
    TokenType::direction,
    TokenType::COMMA,
    TokenType::identifier,
    TokenType::direction
};

constexpr TokenType mysql_alterAlgorithmOption_tokens_171[] = {
    TokenType::ALGORITHM,
    TokenType::EQ,
    TokenType::DEFAULT
};

constexpr TokenType mysql_alterAlgorithmOption_tokens_172[] = {
    TokenType::ALGORITHM,
    TokenType::EQ,
    TokenType::identifier
};

constexpr TokenType mysql_alterLockOption_tokens_173[] = {
    TokenType::LOCK,
    TokenType::EQ,
    TokenType::DEFAULT
};

constexpr TokenType mysql_alterLockOption_tokens_174[] = {
    TokenType::LOCK,
    TokenType::EQ,
    TokenType::identifier
};

constexpr TokenType mysql_indexLockAndAlgorithm_tokens_175[] = {
    TokenType::alterAlgorithmOption,
    TokenType::alterLockOption
};

constexpr TokenType mysql_indexLockAndAlgorithm_tokens_176[] = {
    TokenType::alterLockOption,
    TokenType::alterAlgorithmOption
};

constexpr TokenType mysql_withValidation_tokens_177[] = {
    TokenType::WITH,
    TokenType::VALIDATION
};

constexpr TokenType mysql_withValidation_tokens_178[] = {
    TokenType::WITHOUT,
    TokenType::VALIDATION
};

constexpr TokenType mysql_removePartitioning_tokens_179[] = {
    TokenType::REMOVE,
    TokenType::PARTITIONING
};

constexpr TokenType mysql_allOrPartitionNameList_tokens_180[] = {
    TokenType::ALL
};

constexpr TokenType mysql_allOrPartitionNameList_tokens_181[] = {
    TokenType::identifierList
};

constexpr TokenType mysql_alterTablespace_tokens_182[] = {
    TokenType::TABLESPACE,
    TokenType::tablespaceRef,
    TokenType::ADD,
    TokenType::DATAFILE,
    TokenType::textLiteral,
    TokenType::alterTablespaceOptions
};

constexpr TokenType mysql_alterTablespace_tokens_183[] = {
    TokenType::TABLESPACE,
    TokenType::tablespaceRef,
    TokenType::DROP,
    TokenType::DATAFILE,
    TokenType::textLiteral,
    TokenType::alterTablespaceOptions
};

constexpr TokenType mysql_alterTablespace_tokens_184[] = {
    TokenType::TABLESPACE,
    TokenType::tablespaceRef,
    TokenType::RENAME,
    TokenType::TO,
    TokenType::identifier
};

constexpr TokenType mysql_alterTablespace_tokens_185[] = {
    TokenType::TABLESPACE,
    TokenType::tablespaceRef,
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::alterTablespaceOptions
};

constexpr TokenType mysql_alterUndoTablespace_tokens_186[] = {
    TokenType::UNDO,
    TokenType::TABLESPACE,
    TokenType::tablespaceRef,
    TokenType::SET,
    TokenType::ACTIVE,
    TokenType::undoTableSpaceOptions
};

constexpr TokenType mysql_alterUndoTablespace_tokens_187[] = {
    TokenType::UNDO,
    TokenType::TABLESPACE,
    TokenType::tablespaceRef,
    TokenType::SET,
    TokenType::INACTIVE,
    TokenType::undoTableSpaceOptions
};

constexpr TokenType mysql_undoTableSpaceOptions_tokens_188[] = {
    TokenType::undoTableSpaceOption,
    TokenType::COMMA,
    TokenType::undoTableSpaceOption
};

constexpr TokenType mysql_undoTableSpaceOption_tokens_189[] = {
    TokenType::tsOptionEngine
};

constexpr TokenType mysql_alterTablespaceOptions_tokens_190[] = {
    TokenType::alterTablespaceOption,
    TokenType::COMMA,
    TokenType::alterTablespaceOption
};

constexpr TokenType mysql_alterTablespaceOption_tokens_191[] = {
    TokenType::INITIAL_SIZE,
    TokenType::EQ,
    TokenType::sizeNumber
};

constexpr TokenType mysql_alterTablespaceOption_tokens_192[] = {
    TokenType::tsOptionAutoextendSize
};

constexpr TokenType mysql_alterTablespaceOption_tokens_193[] = {
    TokenType::tsOptionMaxSize
};

constexpr TokenType mysql_alterTablespaceOption_tokens_194[] = {
    TokenType::tsOptionEngine
};

constexpr TokenType mysql_alterTablespaceOption_tokens_195[] = {
    TokenType::tsOptionWait
};

constexpr TokenType mysql_alterTablespaceOption_tokens_196[] = {
    TokenType::tsOptionEncryption
};

constexpr TokenType mysql_alterTablespaceOption_tokens_197[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::tsOptionEngineAttribute
};

constexpr TokenType mysql_changeTablespaceOption_tokens_198[] = {
    TokenType::INITIAL_SIZE,
    TokenType::EQ,
    TokenType::sizeNumber
};

constexpr TokenType mysql_changeTablespaceOption_tokens_199[] = {
    TokenType::tsOptionAutoextendSize
};

constexpr TokenType mysql_changeTablespaceOption_tokens_200[] = {
    TokenType::tsOptionMaxSize
};

constexpr TokenType mysql_alterView_tokens_201[] = {
    TokenType::viewAlgorithm,
    TokenType::definerClause,
    TokenType::viewSuid,
    TokenType::VIEW,
    TokenType::viewRef,
    TokenType::viewTail
};

constexpr TokenType mysql_viewTail_tokens_202[] = {
    TokenType::columnInternalRefList,
    TokenType::AS,
    TokenType::viewQueryBlock
};

constexpr TokenType mysql_viewQueryBlock_tokens_203[] = {
    TokenType::queryExpressionWithOptLockingClauses,
    TokenType::viewCheckOption
};

constexpr TokenType mysql_viewCheckOption_tokens_204[] = {
    TokenType::WITH,
    TokenType::CASCADED,
    TokenType::CHECK,
    TokenType::OPTION
};

constexpr TokenType mysql_viewCheckOption_tokens_205[] = {
    TokenType::WITH,
    TokenType::LOCAL,
    TokenType::CHECK,
    TokenType::OPTION
};

constexpr TokenType mysql_alterInstanceStatement_tokens_206[] = {
    TokenType::INSTANCE,
    TokenType::ROTATE,
    TokenType::textOrIdentifier,
    TokenType::MASTER,
    TokenType::KEY
};

constexpr TokenType mysql_alterInstanceStatement_tokens_207[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::RELOAD,
    TokenType::TLS,
    TokenType::NO,
    TokenType::ROLLBACK,
    TokenType::ON,
    TokenType::ERROR
};

constexpr TokenType mysql_alterInstanceStatement_tokens_208[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::RELOAD,
    TokenType::TLS,
    TokenType::FOR,
    TokenType::CHANNEL,
    TokenType::identifier,
    TokenType::NO,
    TokenType::ROLLBACK,
    TokenType::ON,
    TokenType::ERROR
};

constexpr TokenType mysql_alterInstanceStatement_tokens_209[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::ENABLE,
    TokenType::identifier,
    TokenType::identifier
};

constexpr TokenType mysql_alterInstanceStatement_tokens_210[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::DISABLE,
    TokenType::identifier,
    TokenType::identifier
};

constexpr TokenType mysql_alterInstanceStatement_tokens_211[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::RELOAD,
    TokenType::KEYRING
};

constexpr TokenType mysql_tableElementList_tokens_212[] = {
    TokenType::tableElement,
    TokenType::COMMA,
    TokenType::tableElement
};

constexpr TokenType mysql_tableElement_tokens_213[] = {
    TokenType::columnDefinition
};

constexpr TokenType mysql_tableElement_tokens_214[] = {
    TokenType::tableConstraintDef
};

constexpr TokenType mysql_duplicateAsQe_tokens_215[] = {
    TokenType::REPLACE,
    TokenType::asCreateQueryExpression
};

constexpr TokenType mysql_duplicateAsQe_tokens_216[] = {
    TokenType::IGNORE,
    TokenType::asCreateQueryExpression
};

constexpr TokenType mysql_routineString_tokens_217[] = {
    TokenType::textStringLiteral
};

constexpr TokenType mysql_routineString_tokens_218[] = {
    TokenType::DOLLAR_QUOTED_STRING_TEXT
};

constexpr TokenType mysql_storedRoutineBody_tokens_219[] = {
    TokenType::compoundStatement
};

constexpr TokenType mysql_storedRoutineBody_tokens_220[] = {
    TokenType::this,
    TokenType::isStoredRoutineBody,
    TokenType::AS,
    TokenType::routineString
};

constexpr TokenType mysql_routineAlterOptions_tokens_221[] = {
    TokenType::routineCreateOption
};

constexpr TokenType mysql_routineOption_tokens_222[] = {
    TokenType::option,
    TokenType::COMMENT,
    TokenType::textLiteral
};

constexpr TokenType mysql_routineOption_tokens_223[] = {
    TokenType::option,
    TokenType::LANGUAGE,
    TokenType::SQL
};

constexpr TokenType mysql_routineOption_tokens_224[] = {
    TokenType::option,
    TokenType::LANGUAGE,
    TokenType::this,
    TokenType::isServerVersionGe80032,
    TokenType::identifier
};

constexpr TokenType mysql_routineOption_tokens_225[] = {
    TokenType::option,
    TokenType::NO,
    TokenType::SQL
};

constexpr TokenType mysql_routineOption_tokens_226[] = {
    TokenType::option,
    TokenType::CONTAINS,
    TokenType::SQL
};

constexpr TokenType mysql_routineOption_tokens_227[] = {
    TokenType::option,
    TokenType::READS,
    TokenType::SQL,
    TokenType::DATA
};

constexpr TokenType mysql_routineOption_tokens_228[] = {
    TokenType::option,
    TokenType::MODIFIES,
    TokenType::SQL,
    TokenType::DATA
};

constexpr TokenType mysql_routineOption_tokens_229[] = {
    TokenType::option,
    TokenType::SQL,
    TokenType::SECURITY,
    TokenType::security,
    TokenType::DEFINER
};

constexpr TokenType mysql_routineOption_tokens_230[] = {
    TokenType::option,
    TokenType::SQL,
    TokenType::SECURITY,
    TokenType::security,
    TokenType::INVOKER
};

constexpr TokenType mysql_indexNameAndType_tokens_231[] = {
    TokenType::indexName
};

constexpr TokenType mysql_indexNameAndType_tokens_232[] = {
    TokenType::indexName,
    TokenType::USING,
    TokenType::indexType
};

constexpr TokenType mysql_indexNameAndType_tokens_233[] = {
    TokenType::indexName,
    TokenType::TYPE,
    TokenType::indexType
};

constexpr TokenType mysql_logfileGroupOptions_tokens_234[] = {
    TokenType::logfileGroupOption,
    TokenType::COMMA,
    TokenType::logfileGroupOption
};

constexpr TokenType mysql_logfileGroupOption_tokens_235[] = {
    TokenType::tsOptionInitialSize
};

constexpr TokenType mysql_logfileGroupOption_tokens_236[] = {
    TokenType::tsOptionUndoRedoBufferSize
};

constexpr TokenType mysql_logfileGroupOption_tokens_237[] = {
    TokenType::tsOptionNodegroup
};

constexpr TokenType mysql_logfileGroupOption_tokens_238[] = {
    TokenType::tsOptionEngine
};

constexpr TokenType mysql_logfileGroupOption_tokens_239[] = {
    TokenType::tsOptionWait
};

constexpr TokenType mysql_logfileGroupOption_tokens_240[] = {
    TokenType::tsOptionComment
};

constexpr TokenType mysql_serverOptions_tokens_241[] = {
    TokenType::OPTIONS,
    TokenType::LPAREN,
    TokenType::serverOption,
    TokenType::COMMA,
    TokenType::serverOption,
    TokenType::RPAREN
};

constexpr TokenType mysql_serverOption_tokens_242[] = {
    TokenType::option,
    TokenType::HOST,
    TokenType::textLiteral
};

constexpr TokenType mysql_serverOption_tokens_243[] = {
    TokenType::option,
    TokenType::DATABASE,
    TokenType::textLiteral
};

constexpr TokenType mysql_serverOption_tokens_244[] = {
    TokenType::option,
    TokenType::USER,
    TokenType::textLiteral
};

constexpr TokenType mysql_serverOption_tokens_245[] = {
    TokenType::option,
    TokenType::PASSWORD,
    TokenType::textLiteral
};

constexpr TokenType mysql_serverOption_tokens_246[] = {
    TokenType::option,
    TokenType::SOCKET,
    TokenType::textLiteral
};

constexpr TokenType mysql_serverOption_tokens_247[] = {
    TokenType::option,
    TokenType::OWNER,
    TokenType::textLiteral
};

constexpr TokenType mysql_serverOption_tokens_248[] = {
    TokenType::option,
    TokenType::PORT,
    TokenType::ulong_number
};

constexpr TokenType mysql_tsDataFileName_tokens_249[] = {
    TokenType::ADD,
    TokenType::tsDataFile
};

constexpr TokenType mysql_tsDataFileName_tokens_250[] = {
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::ADD,
    TokenType::tsDataFile
};

constexpr TokenType mysql_tsDataFile_tokens_251[] = {
    TokenType::DATAFILE,
    TokenType::textLiteral
};

constexpr TokenType mysql_tablespaceOptions_tokens_252[] = {
    TokenType::tablespaceOption,
    TokenType::COMMA,
    TokenType::tablespaceOption
};

constexpr TokenType mysql_tablespaceOption_tokens_253[] = {
    TokenType::tsOptionInitialSize
};

constexpr TokenType mysql_tablespaceOption_tokens_254[] = {
    TokenType::tsOptionAutoextendSize
};

constexpr TokenType mysql_tablespaceOption_tokens_255[] = {
    TokenType::tsOptionMaxSize
};

constexpr TokenType mysql_tablespaceOption_tokens_256[] = {
    TokenType::tsOptionExtentSize
};

constexpr TokenType mysql_tablespaceOption_tokens_257[] = {
    TokenType::tsOptionNodegroup
};

constexpr TokenType mysql_tablespaceOption_tokens_258[] = {
    TokenType::tsOptionEngine
};

constexpr TokenType mysql_tablespaceOption_tokens_259[] = {
    TokenType::tsOptionWait
};

constexpr TokenType mysql_tablespaceOption_tokens_260[] = {
    TokenType::tsOptionComment
};

constexpr TokenType mysql_tablespaceOption_tokens_261[] = {
    TokenType::tsOptionFileblockSize
};

constexpr TokenType mysql_tablespaceOption_tokens_262[] = {
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::tsOptionEncryption
};

constexpr TokenType mysql_tsOptionInitialSize_tokens_263[] = {
    TokenType::INITIAL_SIZE,
    TokenType::EQ,
    TokenType::sizeNumber
};

constexpr TokenType mysql_tsOptionUndoRedoBufferSize_tokens_264[] = {
    TokenType::UNDO_BUFFER_SIZE,
    TokenType::EQ,
    TokenType::sizeNumber
};

constexpr TokenType mysql_tsOptionUndoRedoBufferSize_tokens_265[] = {
    TokenType::REDO_BUFFER_SIZE,
    TokenType::EQ,
    TokenType::sizeNumber
};

constexpr TokenType mysql_tsOptionAutoextendSize_tokens_266[] = {
    TokenType::AUTOEXTEND_SIZE,
    TokenType::EQ,
    TokenType::sizeNumber
};

constexpr TokenType mysql_tsOptionMaxSize_tokens_267[] = {
    TokenType::MAX_SIZE,
    TokenType::EQ,
    TokenType::sizeNumber
};

constexpr TokenType mysql_tsOptionExtentSize_tokens_268[] = {
    TokenType::EXTENT_SIZE,
    TokenType::EQ,
    TokenType::sizeNumber
};

constexpr TokenType mysql_tsOptionNodegroup_tokens_269[] = {
    TokenType::NODEGROUP,
    TokenType::EQ,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_tsOptionEngine_tokens_270[] = {
    TokenType::STORAGE,
    TokenType::ENGINE,
    TokenType::EQ,
    TokenType::engineRef
};

constexpr TokenType mysql_tsOptionWait_tokens_271[] = {
    TokenType::WAIT
};

constexpr TokenType mysql_tsOptionWait_tokens_272[] = {
    TokenType::NO_WAIT
};

constexpr TokenType mysql_tsOptionComment_tokens_273[] = {
    TokenType::COMMENT,
    TokenType::EQ,
    TokenType::textLiteral
};

constexpr TokenType mysql_tsOptionFileblockSize_tokens_274[] = {
    TokenType::FILE_BLOCK_SIZE,
    TokenType::EQ,
    TokenType::sizeNumber
};

constexpr TokenType mysql_tsOptionEncryption_tokens_275[] = {
    TokenType::ENCRYPTION,
    TokenType::EQ,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_tsOptionEngineAttribute_tokens_276[] = {
    TokenType::ENGINE,
    TokenType::EQ,
    TokenType::jsonAttribute
};

constexpr TokenType mysql_viewReplaceOrAlgorithm_tokens_277[] = {
    TokenType::OR,
    TokenType::REPLACE,
    TokenType::viewAlgorithm
};

constexpr TokenType mysql_viewReplaceOrAlgorithm_tokens_278[] = {
    TokenType::viewAlgorithm
};

constexpr TokenType mysql_viewAlgorithm_tokens_279[] = {
    TokenType::ALGORITHM,
    TokenType::EQ,
    TokenType::algorithm,
    TokenType::UNDEFINED
};

constexpr TokenType mysql_viewAlgorithm_tokens_280[] = {
    TokenType::ALGORITHM,
    TokenType::EQ,
    TokenType::algorithm,
    TokenType::MERGE
};

constexpr TokenType mysql_viewAlgorithm_tokens_281[] = {
    TokenType::ALGORITHM,
    TokenType::EQ,
    TokenType::algorithm,
    TokenType::TEMPTABLE
};

constexpr TokenType mysql_viewSuid_tokens_282[] = {
    TokenType::SQL,
    TokenType::SECURITY,
    TokenType::DEFINER
};

constexpr TokenType mysql_viewSuid_tokens_283[] = {
    TokenType::SQL,
    TokenType::SECURITY,
    TokenType::INVOKER
};

constexpr TokenType mysql_triggerFollowsPrecedesClause_tokens_284[] = {
    TokenType::ordering,
    TokenType::FOLLOWS,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_triggerFollowsPrecedesClause_tokens_285[] = {
    TokenType::ordering,
    TokenType::PRECEDES,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_srsAttribute_tokens_286[] = {
    TokenType::NAME,
    TokenType::TEXT,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_srsAttribute_tokens_287[] = {
    TokenType::DEFINITION,
    TokenType::TEXT,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_srsAttribute_tokens_288[] = {
    TokenType::ORGANIZATION,
    TokenType::textStringNoLinebreak,
    TokenType::IDENTIFIED,
    TokenType::BY,
    TokenType::real_ulonglong_number
};

constexpr TokenType mysql_srsAttribute_tokens_289[] = {
    TokenType::DESCRIPTION,
    TokenType::TEXT,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_renameTableStatement_tokens_290[] = {
    TokenType::RENAME,
    TokenType::TABLE,
    TokenType::renamePair,
    TokenType::COMMA,
    TokenType::renamePair
};

constexpr TokenType mysql_renameTableStatement_tokens_291[] = {
    TokenType::RENAME,
    TokenType::TABLES,
    TokenType::renamePair,
    TokenType::COMMA,
    TokenType::renamePair
};

constexpr TokenType mysql_renamePair_tokens_292[] = {
    TokenType::tableRef,
    TokenType::TO,
    TokenType::tableName
};

constexpr TokenType mysql_truncateTableStatement_tokens_293[] = {
    TokenType::TRUNCATE,
    TokenType::TABLE,
    TokenType::tableRef
};

constexpr TokenType mysql_importStatement_tokens_294[] = {
    TokenType::IMPORT,
    TokenType::TABLE,
    TokenType::FROM,
    TokenType::textStringLiteralList
};

constexpr TokenType mysql_callStatement_tokens_295[] = {
    TokenType::CALL,
    TokenType::procedureRef,
    TokenType::LPAREN,
    TokenType::exprList,
    TokenType::RPAREN
};

constexpr TokenType mysql_doStatement_tokens_296[] = {
    TokenType::DO,
    TokenType::selectItemList
};

constexpr TokenType mysql_handlerStatement_tokens_297[] = {
    TokenType::HANDLER,
    TokenType::tableRef,
    TokenType::OPEN,
    TokenType::tableAlias
};

constexpr TokenType mysql_handlerStatement_tokens_298[] = {
    TokenType::HANDLER,
    TokenType::identifier,
    TokenType::CLOSE
};

constexpr TokenType mysql_handlerStatement_tokens_299[] = {
    TokenType::HANDLER,
    TokenType::identifier,
    TokenType::READ,
    TokenType::handlerReadOrScan,
    TokenType::whereClause,
    TokenType::limitClause
};

constexpr TokenType mysql_handlerReadOrScan_tokens_300[] = {
    TokenType::FIRST
};

constexpr TokenType mysql_handlerReadOrScan_tokens_301[] = {
    TokenType::NEXT
};

constexpr TokenType mysql_handlerReadOrScan_tokens_302[] = {
    TokenType::identifier,
    TokenType::FIRST
};

constexpr TokenType mysql_handlerReadOrScan_tokens_303[] = {
    TokenType::identifier,
    TokenType::NEXT
};

constexpr TokenType mysql_handlerReadOrScan_tokens_304[] = {
    TokenType::identifier,
    TokenType::PREV
};

constexpr TokenType mysql_handlerReadOrScan_tokens_305[] = {
    TokenType::identifier,
    TokenType::LAST
};

constexpr TokenType mysql_handlerReadOrScan_tokens_306[] = {
    TokenType::identifier,
    TokenType::EQ,
    TokenType::LPAREN,
    TokenType::values,
    TokenType::RPAREN
};

constexpr TokenType mysql_handlerReadOrScan_tokens_307[] = {
    TokenType::identifier,
    TokenType::LT,
    TokenType::LPAREN,
    TokenType::values,
    TokenType::RPAREN
};

constexpr TokenType mysql_handlerReadOrScan_tokens_308[] = {
    TokenType::identifier,
    TokenType::GT,
    TokenType::LPAREN,
    TokenType::values,
    TokenType::RPAREN
};

constexpr TokenType mysql_handlerReadOrScan_tokens_309[] = {
    TokenType::identifier,
    TokenType::LTE,
    TokenType::LPAREN,
    TokenType::values,
    TokenType::RPAREN
};

constexpr TokenType mysql_handlerReadOrScan_tokens_310[] = {
    TokenType::identifier,
    TokenType::GTE,
    TokenType::LPAREN,
    TokenType::values,
    TokenType::RPAREN
};

constexpr TokenType mysql_fields_tokens_311[] = {
    TokenType::insertIdentifier,
    TokenType::COMMA,
    TokenType::insertIdentifier
};

constexpr TokenType mysql_valueList_tokens_312[] = {
    TokenType::LPAREN,
    TokenType::values,
    TokenType::RPAREN,
    TokenType::COMMA,
    TokenType::LPAREN,
    TokenType::values,
    TokenType::RPAREN
};

constexpr TokenType mysql_values_tokens_313[] = {
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr
};

constexpr TokenType mysql_values_tokens_314[] = {
    TokenType::expr,
    TokenType::COMMA,
    TokenType::DEFAULT
};

constexpr TokenType mysql_values_tokens_315[] = {
    TokenType::DEFAULT,
    TokenType::COMMA,
    TokenType::expr
};

constexpr TokenType mysql_values_tokens_316[] = {
    TokenType::DEFAULT,
    TokenType::COMMA,
    TokenType::DEFAULT
};

constexpr TokenType mysql_valuesReference_tokens_317[] = {
    TokenType::this,
    TokenType::isServerVersionGe80018,
    TokenType::AS,
    TokenType::identifier,
    TokenType::columnInternalRefList
};

constexpr TokenType mysql_loadStatement_tokens_318[] = {
    TokenType::LOAD,
    TokenType::dataOrXml,
    TokenType::loadDataLock,
    TokenType::loadFrom,
    TokenType::LOCAL,
    TokenType::loadSourceType,
    TokenType::textStringLiteral,
    TokenType::sourceCount,
    TokenType::sourceOrder,
    TokenType::REPLACE,
    TokenType::INTO,
    TokenType::TABLE,
    TokenType::tableRef,
    TokenType::usePartition,
    TokenType::charsetClause,
    TokenType::xmlRowsIdentifiedBy,
    TokenType::fieldsClause,
    TokenType::linesClause,
    TokenType::loadDataFileTail,
    TokenType::loadParallel,
    TokenType::loadMemory,
    TokenType::loadAlgorithm
};

constexpr TokenType mysql_loadStatement_tokens_319[] = {
    TokenType::LOAD,
    TokenType::dataOrXml,
    TokenType::loadDataLock,
    TokenType::loadFrom,
    TokenType::LOCAL,
    TokenType::loadSourceType,
    TokenType::textStringLiteral,
    TokenType::sourceCount,
    TokenType::sourceOrder,
    TokenType::IGNORE,
    TokenType::INTO,
    TokenType::TABLE,
    TokenType::tableRef,
    TokenType::usePartition,
    TokenType::charsetClause,
    TokenType::xmlRowsIdentifiedBy,
    TokenType::fieldsClause,
    TokenType::linesClause,
    TokenType::loadDataFileTail,
    TokenType::loadParallel,
    TokenType::loadMemory,
    TokenType::loadAlgorithm
};

constexpr TokenType mysql_dataOrXml_tokens_320[] = {
    TokenType::DATA
};

constexpr TokenType mysql_dataOrXml_tokens_321[] = {
    TokenType::XML
};

constexpr TokenType mysql_loadDataLock_tokens_322[] = {
    TokenType::LOW_PRIORITY
};

constexpr TokenType mysql_loadDataLock_tokens_323[] = {
    TokenType::CONCURRENT
};

constexpr TokenType mysql_loadFrom_tokens_324[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::FROM
};

constexpr TokenType mysql_loadSourceType_tokens_325[] = {
    TokenType::INFILE
};

constexpr TokenType mysql_loadSourceType_tokens_326[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::URL
};

constexpr TokenType mysql_loadSourceType_tokens_327[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::S3
};

constexpr TokenType mysql_sourceCount_tokens_328[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::COUNT,
    TokenType::NUMBER
};

constexpr TokenType mysql_sourceCount_tokens_329[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::pureIdentifier,
    TokenType::NUMBER
};

constexpr TokenType mysql_sourceOrder_tokens_330[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::IN,
    TokenType::PRIMARY,
    TokenType::KEY,
    TokenType::ORDER
};

constexpr TokenType mysql_xmlRowsIdentifiedBy_tokens_331[] = {
    TokenType::ROWS,
    TokenType::IDENTIFIED,
    TokenType::BY,
    TokenType::textString
};

constexpr TokenType mysql_loadDataFileTail_tokens_332[] = {
    TokenType::IGNORE,
    TokenType::NUMBER,
    TokenType::LINES,
    TokenType::loadDataFileTargetList,
    TokenType::SET,
    TokenType::updateList
};

constexpr TokenType mysql_loadDataFileTail_tokens_333[] = {
    TokenType::IGNORE,
    TokenType::NUMBER,
    TokenType::ROWS,
    TokenType::loadDataFileTargetList,
    TokenType::SET,
    TokenType::updateList
};

constexpr TokenType mysql_loadDataFileTargetList_tokens_334[] = {
    TokenType::LPAREN,
    TokenType::fieldOrVariableList,
    TokenType::RPAREN
};

constexpr TokenType mysql_fieldOrVariableList_tokens_335[] = {
    TokenType::columnRef,
    TokenType::COMMA,
    TokenType::columnRef
};

constexpr TokenType mysql_fieldOrVariableList_tokens_336[] = {
    TokenType::columnRef,
    TokenType::COMMA,
    TokenType::AT_SIGN,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_fieldOrVariableList_tokens_337[] = {
    TokenType::columnRef,
    TokenType::COMMA,
    TokenType::AT_TEXT_SUFFIX
};

constexpr TokenType mysql_fieldOrVariableList_tokens_338[] = {
    TokenType::columnRef,
    TokenType::COMMA,
    TokenType::AT_AT_SIGN
};

constexpr TokenType mysql_fieldOrVariableList_tokens_339[] = {
    TokenType::AT_SIGN,
    TokenType::textOrIdentifier,
    TokenType::COMMA,
    TokenType::columnRef
};

constexpr TokenType mysql_fieldOrVariableList_tokens_340[] = {
    TokenType::AT_SIGN,
    TokenType::textOrIdentifier,
    TokenType::COMMA,
    TokenType::AT_SIGN,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_fieldOrVariableList_tokens_341[] = {
    TokenType::AT_SIGN,
    TokenType::textOrIdentifier,
    TokenType::COMMA,
    TokenType::AT_TEXT_SUFFIX
};

constexpr TokenType mysql_fieldOrVariableList_tokens_342[] = {
    TokenType::AT_SIGN,
    TokenType::textOrIdentifier,
    TokenType::COMMA,
    TokenType::AT_AT_SIGN
};

constexpr TokenType mysql_fieldOrVariableList_tokens_343[] = {
    TokenType::AT_AT_SIGN,
    TokenType::COMMA,
    TokenType::columnRef
};

constexpr TokenType mysql_fieldOrVariableList_tokens_344[] = {
    TokenType::AT_AT_SIGN,
    TokenType::COMMA,
    TokenType::AT_SIGN,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_fieldOrVariableList_tokens_345[] = {
    TokenType::AT_AT_SIGN,
    TokenType::COMMA,
    TokenType::AT_TEXT_SUFFIX
};

constexpr TokenType mysql_fieldOrVariableList_tokens_346[] = {
    TokenType::AT_AT_SIGN,
    TokenType::COMMA,
    TokenType::AT_AT_SIGN
};

constexpr TokenType mysql_loadAlgorithm_tokens_347[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::ALGORITHM,
    TokenType::EQ,
    TokenType::BULK
};

constexpr TokenType mysql_loadParallel_tokens_348[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::PARALLEL,
    TokenType::EQ,
    TokenType::NUMBER
};

constexpr TokenType mysql_loadMemory_tokens_349[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::MEMORY,
    TokenType::EQ,
    TokenType::sizeNumber
};

constexpr TokenType mysql_replaceStatement_tokens_350[] = {
    TokenType::REPLACE,
    TokenType::LOW_PRIORITY,
    TokenType::INTO,
    TokenType::tableRef,
    TokenType::usePartition,
    TokenType::insertFromConstructor
};

constexpr TokenType mysql_replaceStatement_tokens_351[] = {
    TokenType::REPLACE,
    TokenType::LOW_PRIORITY,
    TokenType::INTO,
    TokenType::tableRef,
    TokenType::usePartition,
    TokenType::SET,
    TokenType::updateList
};

constexpr TokenType mysql_replaceStatement_tokens_352[] = {
    TokenType::REPLACE,
    TokenType::LOW_PRIORITY,
    TokenType::INTO,
    TokenType::tableRef,
    TokenType::usePartition,
    TokenType::insertQueryExpression
};

constexpr TokenType mysql_replaceStatement_tokens_353[] = {
    TokenType::REPLACE,
    TokenType::DELAYED,
    TokenType::INTO,
    TokenType::tableRef,
    TokenType::usePartition,
    TokenType::insertFromConstructor
};

constexpr TokenType mysql_replaceStatement_tokens_354[] = {
    TokenType::REPLACE,
    TokenType::DELAYED,
    TokenType::INTO,
    TokenType::tableRef,
    TokenType::usePartition,
    TokenType::SET,
    TokenType::updateList
};

constexpr TokenType mysql_replaceStatement_tokens_355[] = {
    TokenType::REPLACE,
    TokenType::DELAYED,
    TokenType::INTO,
    TokenType::tableRef,
    TokenType::usePartition,
    TokenType::insertQueryExpression
};

constexpr TokenType mysql_queryPrimary_tokens_356[] = {
    TokenType::querySpecification
};

constexpr TokenType mysql_queryPrimary_tokens_357[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::tableValueConstructor
};

constexpr TokenType mysql_queryPrimary_tokens_358[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::explicitTable
};

constexpr TokenType mysql_querySpecification_tokens_359[] = {
    TokenType::SELECT,
    TokenType::selectOption,
    TokenType::selectItemList,
    TokenType::intoClause,
    TokenType::fromClause,
    TokenType::whereClause,
    TokenType::groupByClause,
    TokenType::havingClause,
    TokenType::windowClause,
    TokenType::qualifyClause
};

constexpr TokenType mysql_subquery_tokens_360[] = {
    TokenType::queryExpressionParens
};

constexpr TokenType mysql_querySpecOption_tokens_361[] = {
    TokenType::ALL
};

constexpr TokenType mysql_querySpecOption_tokens_362[] = {
    TokenType::DISTINCT
};

constexpr TokenType mysql_querySpecOption_tokens_363[] = {
    TokenType::STRAIGHT_JOIN
};

constexpr TokenType mysql_querySpecOption_tokens_364[] = {
    TokenType::HIGH_PRIORITY
};

constexpr TokenType mysql_querySpecOption_tokens_365[] = {
    TokenType::SQL_SMALL_RESULT
};

constexpr TokenType mysql_querySpecOption_tokens_366[] = {
    TokenType::SQL_BIG_RESULT
};

constexpr TokenType mysql_querySpecOption_tokens_367[] = {
    TokenType::SQL_BUFFER_RESULT
};

constexpr TokenType mysql_querySpecOption_tokens_368[] = {
    TokenType::SQL_CALC_FOUND_ROWS
};

constexpr TokenType mysql_limitClause_tokens_369[] = {
    TokenType::LIMIT,
    TokenType::limitOptions
};

constexpr TokenType mysql_simpleLimitClause_tokens_370[] = {
    TokenType::LIMIT,
    TokenType::limitOption
};

constexpr TokenType mysql_limitOptions_tokens_371[] = {
    TokenType::limitOption,
    TokenType::COMMA,
    TokenType::limitOption
};

constexpr TokenType mysql_limitOptions_tokens_372[] = {
    TokenType::limitOption,
    TokenType::OFFSET,
    TokenType::limitOption
};

constexpr TokenType mysql_limitOption_tokens_373[] = {
    TokenType::identifier
};

constexpr TokenType mysql_limitOption_tokens_374[] = {
    TokenType::PARAM_MARKER
};

constexpr TokenType mysql_limitOption_tokens_375[] = {
    TokenType::ULONGLONG_NUMBER
};

constexpr TokenType mysql_limitOption_tokens_376[] = {
    TokenType::LONG_NUMBER
};

constexpr TokenType mysql_limitOption_tokens_377[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_intoClause_tokens_378[] = {
    TokenType::INTO,
    TokenType::OUTFILE,
    TokenType::textStringLiteral,
    TokenType::charsetClause,
    TokenType::fieldsClause,
    TokenType::linesClause
};

constexpr TokenType mysql_intoClause_tokens_379[] = {
    TokenType::INTO,
    TokenType::DUMPFILE,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_intoClause_tokens_380[] = {
    TokenType::INTO,
    TokenType::textOrIdentifier,
    TokenType::COMMA,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_intoClause_tokens_381[] = {
    TokenType::INTO,
    TokenType::textOrIdentifier,
    TokenType::COMMA,
    TokenType::userVariable
};

constexpr TokenType mysql_intoClause_tokens_382[] = {
    TokenType::INTO,
    TokenType::userVariable,
    TokenType::COMMA,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_intoClause_tokens_383[] = {
    TokenType::INTO,
    TokenType::userVariable,
    TokenType::COMMA,
    TokenType::userVariable
};

constexpr TokenType mysql_procedureAnalyseClause_tokens_384[] = {
    TokenType::PROCEDURE,
    TokenType::LPAREN,
    TokenType::NUMBER,
    TokenType::COMMA,
    TokenType::NUMBER,
    TokenType::RPAREN
};

constexpr TokenType mysql_havingClause_tokens_385[] = {
    TokenType::HAVING,
    TokenType::expr
};

constexpr TokenType mysql_qualifyClause_tokens_386[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::QUALIFY,
    TokenType::expr
};

constexpr TokenType mysql_windowClause_tokens_387[] = {
    TokenType::WINDOW,
    TokenType::windowDefinition,
    TokenType::COMMA,
    TokenType::windowDefinition
};

constexpr TokenType mysql_windowDefinition_tokens_388[] = {
    TokenType::windowName,
    TokenType::AS,
    TokenType::windowSpec
};

constexpr TokenType mysql_windowSpec_tokens_389[] = {
    TokenType::LPAREN,
    TokenType::windowSpecDetails,
    TokenType::RPAREN
};

constexpr TokenType mysql_windowSpecDetails_tokens_390[] = {
    TokenType::windowName,
    TokenType::PARTITION,
    TokenType::BY,
    TokenType::orderList,
    TokenType::orderClause,
    TokenType::windowFrameClause
};

constexpr TokenType mysql_windowFrameClause_tokens_391[] = {
    TokenType::windowFrameUnits,
    TokenType::windowFrameExtent,
    TokenType::windowFrameExclusion
};

constexpr TokenType mysql_windowFrameUnits_tokens_392[] = {
    TokenType::ROWS
};

constexpr TokenType mysql_windowFrameUnits_tokens_393[] = {
    TokenType::RANGE
};

constexpr TokenType mysql_windowFrameUnits_tokens_394[] = {
    TokenType::GROUPS
};

constexpr TokenType mysql_windowFrameExtent_tokens_395[] = {
    TokenType::windowFrameStart
};

constexpr TokenType mysql_windowFrameExtent_tokens_396[] = {
    TokenType::windowFrameBetween
};

constexpr TokenType mysql_windowFrameStart_tokens_397[] = {
    TokenType::UNBOUNDED,
    TokenType::PRECEDING
};

constexpr TokenType mysql_windowFrameStart_tokens_398[] = {
    TokenType::ulonglongNumber,
    TokenType::PRECEDING
};

constexpr TokenType mysql_windowFrameStart_tokens_399[] = {
    TokenType::PARAM_MARKER,
    TokenType::PRECEDING
};

constexpr TokenType mysql_windowFrameStart_tokens_400[] = {
    TokenType::INTERVAL,
    TokenType::expr,
    TokenType::interval,
    TokenType::PRECEDING
};

constexpr TokenType mysql_windowFrameStart_tokens_401[] = {
    TokenType::CURRENT,
    TokenType::ROW
};

constexpr TokenType mysql_windowFrameBetween_tokens_402[] = {
    TokenType::BETWEEN,
    TokenType::windowFrameBound,
    TokenType::AND,
    TokenType::windowFrameBound
};

constexpr TokenType mysql_windowFrameBound_tokens_403[] = {
    TokenType::windowFrameStart
};

constexpr TokenType mysql_windowFrameBound_tokens_404[] = {
    TokenType::UNBOUNDED,
    TokenType::FOLLOWING
};

constexpr TokenType mysql_windowFrameBound_tokens_405[] = {
    TokenType::ulonglongNumber,
    TokenType::FOLLOWING
};

constexpr TokenType mysql_windowFrameBound_tokens_406[] = {
    TokenType::PARAM_MARKER,
    TokenType::FOLLOWING
};

constexpr TokenType mysql_windowFrameBound_tokens_407[] = {
    TokenType::INTERVAL,
    TokenType::expr,
    TokenType::interval,
    TokenType::FOLLOWING
};

constexpr TokenType mysql_windowFrameExclusion_tokens_408[] = {
    TokenType::EXCLUDE,
    TokenType::CURRENT,
    TokenType::ROW
};

constexpr TokenType mysql_windowFrameExclusion_tokens_409[] = {
    TokenType::EXCLUDE,
    TokenType::GROUP
};

constexpr TokenType mysql_windowFrameExclusion_tokens_410[] = {
    TokenType::EXCLUDE,
    TokenType::TIES
};

constexpr TokenType mysql_windowFrameExclusion_tokens_411[] = {
    TokenType::EXCLUDE,
    TokenType::NO,
    TokenType::OTHERS
};

constexpr TokenType mysql_withClause_tokens_412[] = {
    TokenType::WITH,
    TokenType::RECURSIVE,
    TokenType::commonTableExpression,
    TokenType::COMMA,
    TokenType::commonTableExpression
};

constexpr TokenType mysql_groupByClause_tokens_413[] = {
    TokenType::GROUP,
    TokenType::BY,
    TokenType::orderList,
    TokenType::olapOption
};

constexpr TokenType mysql_groupByClause_tokens_414[] = {
    TokenType::this,
    TokenType::isServerVersionGe80032,
    TokenType::GROUP,
    TokenType::BY,
    TokenType::ROLLUP,
    TokenType::LPAREN,
    TokenType::groupList,
    TokenType::RPAREN
};

constexpr TokenType mysql_groupByClause_tokens_415[] = {
    TokenType::this,
    TokenType::isServerVersionGe80032,
    TokenType::GROUP,
    TokenType::BY,
    TokenType::CUBE,
    TokenType::LPAREN,
    TokenType::groupList,
    TokenType::RPAREN
};

constexpr TokenType mysql_olapOption_tokens_416[] = {
    TokenType::WITH,
    TokenType::ROLLUP
};

constexpr TokenType mysql_orderClause_tokens_417[] = {
    TokenType::ORDER,
    TokenType::BY,
    TokenType::orderList
};

constexpr TokenType mysql_direction_tokens_418[] = {
    TokenType::ASC
};

constexpr TokenType mysql_direction_tokens_419[] = {
    TokenType::DESC
};

constexpr TokenType mysql_fromClause_tokens_420[] = {
    TokenType::FROM,
    TokenType::DUAL
};

constexpr TokenType mysql_fromClause_tokens_421[] = {
    TokenType::FROM,
    TokenType::tableReferenceList
};

constexpr TokenType mysql_tableReferenceList_tokens_422[] = {
    TokenType::tableReference,
    TokenType::COMMA,
    TokenType::tableReference
};

constexpr TokenType mysql_tableValueConstructor_tokens_423[] = {
    TokenType::VALUES,
    TokenType::rowValueExplicit,
    TokenType::COMMA,
    TokenType::rowValueExplicit
};

constexpr TokenType mysql_explicitTable_tokens_424[] = {
    TokenType::TABLE,
    TokenType::tableRef
};

constexpr TokenType mysql_rowValueExplicit_tokens_425[] = {
    TokenType::ROW,
    TokenType::LPAREN,
    TokenType::values,
    TokenType::RPAREN
};

constexpr TokenType mysql_lockingClauseList_tokens_426[] = {
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::lockingClause
};

constexpr TokenType mysql_lockingClause_tokens_427[] = {
    TokenType::FOR,
    TokenType::lockStrengh,
    TokenType::OF,
    TokenType::tableAliasRefList,
    TokenType::lockedRowAction
};

constexpr TokenType mysql_lockingClause_tokens_428[] = {
    TokenType::LOCK,
    TokenType::IN,
    TokenType::SHARE,
    TokenType::MODE
};

constexpr TokenType mysql_lockStrengh_tokens_429[] = {
    TokenType::UPDATE
};

constexpr TokenType mysql_lockStrengh_tokens_430[] = {
    TokenType::SHARE
};

constexpr TokenType mysql_lockedRowAction_tokens_431[] = {
    TokenType::SKIP,
    TokenType::LOCKED
};

constexpr TokenType mysql_lockedRowAction_tokens_432[] = {
    TokenType::NOWAIT
};

constexpr TokenType mysql_whereClause_tokens_433[] = {
    TokenType::WHERE,
    TokenType::expr
};

constexpr TokenType mysql_tableReference_tokens_434[] = {
    TokenType::tableFactor,
    TokenType::joinedTable
};

constexpr TokenType mysql_tableReference_tokens_435[] = {
    TokenType::LBRACE,
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::identifier,
    TokenType::escapedTableReference,
    TokenType::RBRACE,
    TokenType::joinedTable
};

constexpr TokenType mysql_tableReference_tokens_436[] = {
    TokenType::LBRACE,
    TokenType::OJ,
    TokenType::escapedTableReference,
    TokenType::RBRACE,
    TokenType::joinedTable
};

constexpr TokenType mysql_escapedTableReference_tokens_437[] = {
    TokenType::tableFactor,
    TokenType::joinedTable
};

constexpr TokenType mysql_joinedTable_tokens_438[] = {
    TokenType::innerJoinType,
    TokenType::tableReference,
    TokenType::ON,
    TokenType::expr
};

constexpr TokenType mysql_joinedTable_tokens_439[] = {
    TokenType::innerJoinType,
    TokenType::tableReference,
    TokenType::USING,
    TokenType::identifierListWithParentheses
};

constexpr TokenType mysql_joinedTable_tokens_440[] = {
    TokenType::outerJoinType,
    TokenType::tableReference,
    TokenType::ON,
    TokenType::expr
};

constexpr TokenType mysql_joinedTable_tokens_441[] = {
    TokenType::outerJoinType,
    TokenType::tableReference,
    TokenType::USING,
    TokenType::identifierListWithParentheses
};

constexpr TokenType mysql_joinedTable_tokens_442[] = {
    TokenType::naturalJoinType,
    TokenType::tableFactor
};

constexpr TokenType mysql_naturalJoinType_tokens_443[] = {
    TokenType::NATURAL,
    TokenType::INNER,
    TokenType::JOIN
};

constexpr TokenType mysql_naturalJoinType_tokens_444[] = {
    TokenType::NATURAL,
    TokenType::LEFT,
    TokenType::OUTER,
    TokenType::JOIN
};

constexpr TokenType mysql_naturalJoinType_tokens_445[] = {
    TokenType::NATURAL,
    TokenType::RIGHT,
    TokenType::OUTER,
    TokenType::JOIN
};

constexpr TokenType mysql_innerJoinType_tokens_446[] = {
    TokenType::type,
    TokenType::INNER,
    TokenType::JOIN
};

constexpr TokenType mysql_innerJoinType_tokens_447[] = {
    TokenType::type,
    TokenType::CROSS,
    TokenType::JOIN
};

constexpr TokenType mysql_innerJoinType_tokens_448[] = {
    TokenType::type,
    TokenType::STRAIGHT_JOIN
};

constexpr TokenType mysql_outerJoinType_tokens_449[] = {
    TokenType::type,
    TokenType::LEFT,
    TokenType::OUTER,
    TokenType::JOIN
};

constexpr TokenType mysql_outerJoinType_tokens_450[] = {
    TokenType::type,
    TokenType::RIGHT,
    TokenType::OUTER,
    TokenType::JOIN
};

constexpr TokenType mysql_tableFactor_tokens_451[] = {
    TokenType::singleTable
};

constexpr TokenType mysql_tableFactor_tokens_452[] = {
    TokenType::singleTableParens
};

constexpr TokenType mysql_tableFactor_tokens_453[] = {
    TokenType::derivedTable
};

constexpr TokenType mysql_tableFactor_tokens_454[] = {
    TokenType::tableReferenceListParens
};

constexpr TokenType mysql_tableFactor_tokens_455[] = {
    TokenType::this,
    TokenType::isServerVersionGe80004,
    TokenType::tableFunction
};

constexpr TokenType mysql_singleTable_tokens_456[] = {
    TokenType::tableRef,
    TokenType::usePartition,
    TokenType::tableAlias,
    TokenType::indexHintList,
    TokenType::tablesampleClause
};

constexpr TokenType mysql_singleTableParens_tokens_457[] = {
    TokenType::LPAREN,
    TokenType::singleTable,
    TokenType::RPAREN
};

constexpr TokenType mysql_singleTableParens_tokens_458[] = {
    TokenType::LPAREN,
    TokenType::singleTableParens,
    TokenType::RPAREN
};

constexpr TokenType mysql_derivedTable_tokens_459[] = {
    TokenType::subquery,
    TokenType::tableAlias,
    TokenType::columnInternalRefList
};

constexpr TokenType mysql_derivedTable_tokens_460[] = {
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::LATERAL,
    TokenType::subquery,
    TokenType::tableAlias,
    TokenType::columnInternalRefList
};

constexpr TokenType mysql_tableReferenceListParens_tokens_461[] = {
    TokenType::LPAREN,
    TokenType::tableReferenceList,
    TokenType::RPAREN
};

constexpr TokenType mysql_tableReferenceListParens_tokens_462[] = {
    TokenType::LPAREN,
    TokenType::tableReferenceListParens,
    TokenType::RPAREN
};

constexpr TokenType mysql_tableFunction_tokens_463[] = {
    TokenType::JSON_TABLE,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::textStringLiteral,
    TokenType::columnsClause,
    TokenType::RPAREN,
    TokenType::tableAlias
};

constexpr TokenType mysql_columnsClause_tokens_464[] = {
    TokenType::COLUMNS,
    TokenType::LPAREN,
    TokenType::jtColumn,
    TokenType::COMMA,
    TokenType::jtColumn,
    TokenType::RPAREN
};

constexpr TokenType mysql_jtColumn_tokens_465[] = {
    TokenType::identifier,
    TokenType::FOR,
    TokenType::ORDINALITY
};

constexpr TokenType mysql_jtColumn_tokens_466[] = {
    TokenType::identifier,
    TokenType::dataType,
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::collate,
    TokenType::EXISTS,
    TokenType::PATH,
    TokenType::textStringLiteral,
    TokenType::onEmptyOrErrorJsonTable
};

constexpr TokenType mysql_jtColumn_tokens_467[] = {
    TokenType::NESTED,
    TokenType::PATH,
    TokenType::textStringLiteral,
    TokenType::columnsClause
};

constexpr TokenType mysql_onEmptyOrError_tokens_468[] = {
    TokenType::onEmpty,
    TokenType::onError
};

constexpr TokenType mysql_onEmptyOrError_tokens_469[] = {
    TokenType::onError
};

constexpr TokenType mysql_onEmptyOrErrorJsonTable_tokens_470[] = {
    TokenType::onEmptyOrError
};

constexpr TokenType mysql_onEmptyOrErrorJsonTable_tokens_471[] = {
    TokenType::onError,
    TokenType::onEmpty
};

constexpr TokenType mysql_onEmpty_tokens_472[] = {
    TokenType::jsonOnResponse,
    TokenType::ON,
    TokenType::EMPTY
};

constexpr TokenType mysql_onError_tokens_473[] = {
    TokenType::jsonOnResponse,
    TokenType::ON,
    TokenType::ERROR
};

constexpr TokenType mysql_jsonOnResponse_tokens_474[] = {
    TokenType::ERROR
};

constexpr TokenType mysql_jsonOnResponse_tokens_475[] = {
    TokenType::NULL_KW
};

constexpr TokenType mysql_jsonOnResponse_tokens_476[] = {
    TokenType::DEFAULT,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_unionOption_tokens_477[] = {
    TokenType::DISTINCT
};

constexpr TokenType mysql_unionOption_tokens_478[] = {
    TokenType::ALL
};

constexpr TokenType mysql_tableAlias_tokens_479[] = {
    TokenType::AS,
    TokenType::identifier
};

constexpr TokenType mysql_tableAlias_tokens_480[] = {
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::EQ,
    TokenType::identifier
};

constexpr TokenType mysql_indexHintList_tokens_481[] = {
    TokenType::indexHint,
    TokenType::COMMA,
    TokenType::indexHint
};

constexpr TokenType mysql_indexHint_tokens_482[] = {
    TokenType::indexHintType,
    TokenType::keyOrIndex,
    TokenType::indexHintClause,
    TokenType::LPAREN,
    TokenType::indexList,
    TokenType::RPAREN
};

constexpr TokenType mysql_indexHint_tokens_483[] = {
    TokenType::USE,
    TokenType::keyOrIndex,
    TokenType::indexHintClause,
    TokenType::LPAREN,
    TokenType::indexList,
    TokenType::RPAREN
};

constexpr TokenType mysql_indexHintType_tokens_484[] = {
    TokenType::FORCE
};

constexpr TokenType mysql_indexHintType_tokens_485[] = {
    TokenType::IGNORE
};

constexpr TokenType mysql_keyOrIndex_tokens_486[] = {
    TokenType::KEY
};

constexpr TokenType mysql_keyOrIndex_tokens_487[] = {
    TokenType::INDEX
};

constexpr TokenType mysql_constraintKeyType_tokens_488[] = {
    TokenType::PRIMARY,
    TokenType::KEY
};

constexpr TokenType mysql_constraintKeyType_tokens_489[] = {
    TokenType::UNIQUE,
    TokenType::keyOrIndex
};

constexpr TokenType mysql_indexHintClause_tokens_490[] = {
    TokenType::FOR,
    TokenType::JOIN
};

constexpr TokenType mysql_indexHintClause_tokens_491[] = {
    TokenType::FOR,
    TokenType::ORDER,
    TokenType::BY
};

constexpr TokenType mysql_indexHintClause_tokens_492[] = {
    TokenType::FOR,
    TokenType::GROUP,
    TokenType::BY
};

constexpr TokenType mysql_indexList_tokens_493[] = {
    TokenType::indexListElement,
    TokenType::COMMA,
    TokenType::indexListElement
};

constexpr TokenType mysql_indexListElement_tokens_494[] = {
    TokenType::identifier
};

constexpr TokenType mysql_indexListElement_tokens_495[] = {
    TokenType::PRIMARY
};

constexpr TokenType mysql_transactionOrLockingStatement_tokens_496[] = {
    TokenType::transactionStatement
};

constexpr TokenType mysql_transactionOrLockingStatement_tokens_497[] = {
    TokenType::savepointStatement
};

constexpr TokenType mysql_transactionOrLockingStatement_tokens_498[] = {
    TokenType::lockStatement
};

constexpr TokenType mysql_transactionOrLockingStatement_tokens_499[] = {
    TokenType::xaStatement
};

constexpr TokenType mysql_transactionStatement_tokens_500[] = {
    TokenType::STAR,
    TokenType::TRANSACTION,
    TokenType::startTransactionOptionList
};

constexpr TokenType mysql_transactionStatement_tokens_501[] = {
    TokenType::COMMIT,
    TokenType::WORK,
    TokenType::AND,
    TokenType::NO,
    TokenType::CHAIN,
    TokenType::NO,
    TokenType::RELEASE
};

constexpr TokenType mysql_beginWork_tokens_502[] = {
    TokenType::BEGIN,
    TokenType::WORK
};

constexpr TokenType mysql_startTransactionOptionList_tokens_503[] = {
    TokenType::WITH,
    TokenType::CONSISTENT,
    TokenType::SNAPSHOT
};

constexpr TokenType mysql_startTransactionOptionList_tokens_504[] = {
    TokenType::READ,
    TokenType::WRITE
};

constexpr TokenType mysql_startTransactionOptionList_tokens_505[] = {
    TokenType::READ,
    TokenType::ONLY
};

constexpr TokenType mysql_savepointStatement_tokens_506[] = {
    TokenType::SAVEPOINT,
    TokenType::identifier
};

constexpr TokenType mysql_savepointStatement_tokens_507[] = {
    TokenType::ROLLBACK,
    TokenType::WORK,
    TokenType::TO,
    TokenType::SAVEPOINT,
    TokenType::identifier
};

constexpr TokenType mysql_savepointStatement_tokens_508[] = {
    TokenType::ROLLBACK,
    TokenType::WORK,
    TokenType::AND,
    TokenType::NO,
    TokenType::CHAIN,
    TokenType::NO,
    TokenType::RELEASE
};

constexpr TokenType mysql_savepointStatement_tokens_509[] = {
    TokenType::RELEASE,
    TokenType::SAVEPOINT,
    TokenType::identifier
};

constexpr TokenType mysql_lockStatement_tokens_510[] = {
    TokenType::LOCK,
    TokenType::TABLES,
    TokenType::lockItem,
    TokenType::COMMA,
    TokenType::lockItem
};

constexpr TokenType mysql_lockStatement_tokens_511[] = {
    TokenType::LOCK,
    TokenType::TABLE,
    TokenType::lockItem,
    TokenType::COMMA,
    TokenType::lockItem
};

constexpr TokenType mysql_lockStatement_tokens_512[] = {
    TokenType::LOCK,
    TokenType::INSTANCE,
    TokenType::FOR,
    TokenType::BACKUP
};

constexpr TokenType mysql_lockStatement_tokens_513[] = {
    TokenType::UNLOCK,
    TokenType::TABLES
};

constexpr TokenType mysql_lockStatement_tokens_514[] = {
    TokenType::UNLOCK,
    TokenType::TABLE
};

constexpr TokenType mysql_lockStatement_tokens_515[] = {
    TokenType::UNLOCK,
    TokenType::INSTANCE
};

constexpr TokenType mysql_lockItem_tokens_516[] = {
    TokenType::tableRef,
    TokenType::tableAlias,
    TokenType::lockOption
};

constexpr TokenType mysql_lockOption_tokens_517[] = {
    TokenType::READ,
    TokenType::LOCAL
};

constexpr TokenType mysql_lockOption_tokens_518[] = {
    TokenType::LOW_PRIORITY,
    TokenType::WRITE
};

constexpr TokenType mysql_xaStatement_tokens_519[] = {
    TokenType::XA,
    TokenType::STAR,
    TokenType::xid,
    TokenType::JOIN
};

constexpr TokenType mysql_xaStatement_tokens_520[] = {
    TokenType::XA,
    TokenType::STAR,
    TokenType::xid,
    TokenType::RESUME
};

constexpr TokenType mysql_xaStatement_tokens_521[] = {
    TokenType::XA,
    TokenType::BEGIN,
    TokenType::xid,
    TokenType::JOIN
};

constexpr TokenType mysql_xaStatement_tokens_522[] = {
    TokenType::XA,
    TokenType::BEGIN,
    TokenType::xid,
    TokenType::RESUME
};

constexpr TokenType mysql_xaStatement_tokens_523[] = {
    TokenType::XA,
    TokenType::END,
    TokenType::xid,
    TokenType::SUSPEND,
    TokenType::FOR,
    TokenType::MIGRATE
};

constexpr TokenType mysql_xaStatement_tokens_524[] = {
    TokenType::XA,
    TokenType::PREPARE,
    TokenType::xid
};

constexpr TokenType mysql_xaStatement_tokens_525[] = {
    TokenType::XA,
    TokenType::COMMIT,
    TokenType::xid,
    TokenType::ONE,
    TokenType::PHASE
};

constexpr TokenType mysql_xaStatement_tokens_526[] = {
    TokenType::XA,
    TokenType::ROLLBACK,
    TokenType::xid
};

constexpr TokenType mysql_xaStatement_tokens_527[] = {
    TokenType::XA,
    TokenType::RECOVER,
    TokenType::xaConvert
};

constexpr TokenType mysql_xaConvert_tokens_528[] = {
    TokenType::CONVERT,
    TokenType::XID
};

constexpr TokenType mysql_xid_tokens_529[] = {
    TokenType::textString,
    TokenType::COMMA,
    TokenType::textString,
    TokenType::COMMA,
    TokenType::ulong_number
};

constexpr TokenType mysql_replicationStatement_tokens_530[] = {
    TokenType::PURGE,
    TokenType::purgeOptions
};

constexpr TokenType mysql_replicationStatement_tokens_531[] = {
    TokenType::changeSource
};

constexpr TokenType mysql_replicationStatement_tokens_532[] = {
    TokenType::RESET,
    TokenType::resetOption,
    TokenType::COMMA,
    TokenType::resetOption
};

constexpr TokenType mysql_replicationStatement_tokens_533[] = {
    TokenType::RESET,
    TokenType::PERSIST,
    TokenType::ifExistsIdentifier
};

constexpr TokenType mysql_replicationStatement_tokens_534[] = {
    TokenType::startReplicaStatement
};

constexpr TokenType mysql_replicationStatement_tokens_535[] = {
    TokenType::stopReplicaStatement
};

constexpr TokenType mysql_replicationStatement_tokens_536[] = {
    TokenType::changeReplication
};

constexpr TokenType mysql_replicationStatement_tokens_537[] = {
    TokenType::replicationLoad
};

constexpr TokenType mysql_replicationStatement_tokens_538[] = {
    TokenType::groupReplication
};

constexpr TokenType mysql_purgeOptions_tokens_539[] = {
    TokenType::BINARY,
    TokenType::LOGS,
    TokenType::TO,
    TokenType::textLiteral
};

constexpr TokenType mysql_purgeOptions_tokens_540[] = {
    TokenType::BINARY,
    TokenType::LOGS,
    TokenType::BEFORE,
    TokenType::expr
};

constexpr TokenType mysql_purgeOptions_tokens_541[] = {
    TokenType::MASTER,
    TokenType::LOGS,
    TokenType::TO,
    TokenType::textLiteral
};

constexpr TokenType mysql_purgeOptions_tokens_542[] = {
    TokenType::MASTER,
    TokenType::LOGS,
    TokenType::BEFORE,
    TokenType::expr
};

constexpr TokenType mysql_resetOption_tokens_543[] = {
    TokenType::masterOrBinaryLogsAndGtids,
    TokenType::sourceResetOptions
};

constexpr TokenType mysql_resetOption_tokens_544[] = {
    TokenType::replica,
    TokenType::ALL,
    TokenType::channel
};

constexpr TokenType mysql_masterOrBinaryLogsAndGtids_tokens_545[] = {
    TokenType::MASTER
};

constexpr TokenType mysql_masterOrBinaryLogsAndGtids_tokens_546[] = {
    TokenType::this,
    TokenType::isServerVersionGe80032,
    TokenType::BINARY,
    TokenType::LOGS,
    TokenType::AND,
    TokenType::GTIDS
};

constexpr TokenType mysql_sourceResetOptions_tokens_547[] = {
    TokenType::TO,
    TokenType::real_ulonglong_number
};

constexpr TokenType mysql_replicationLoad_tokens_548[] = {
    TokenType::LOAD,
    TokenType::DATA,
    TokenType::FROM,
    TokenType::MASTER
};

constexpr TokenType mysql_replicationLoad_tokens_549[] = {
    TokenType::LOAD,
    TokenType::TABLE,
    TokenType::tableRef,
    TokenType::FROM,
    TokenType::MASTER
};

constexpr TokenType mysql_changeReplicationSource_tokens_550[] = {
    TokenType::MASTER
};

constexpr TokenType mysql_changeReplicationSource_tokens_551[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::REPLICATION,
    TokenType::SOURCE
};

constexpr TokenType mysql_changeSource_tokens_552[] = {
    TokenType::CHANGE,
    TokenType::changeReplicationSource,
    TokenType::TO,
    TokenType::sourceDefinitions,
    TokenType::channel
};

constexpr TokenType mysql_sourceDefinitions_tokens_553[] = {
    TokenType::sourceDefinition,
    TokenType::COMMA,
    TokenType::sourceDefinition
};

constexpr TokenType mysql_sourceDefinition_tokens_554[] = {
    TokenType::changeReplicationSourceHost,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceDefinition_tokens_555[] = {
    TokenType::NETWORK_NAMESPACE,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceDefinition_tokens_556[] = {
    TokenType::changeReplicationSourceBind,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceDefinition_tokens_557[] = {
    TokenType::changeReplicationSourceUser,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceDefinition_tokens_558[] = {
    TokenType::changeReplicationSourcePassword,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceDefinition_tokens_559[] = {
    TokenType::changeReplicationSourcePort,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_sourceDefinition_tokens_560[] = {
    TokenType::changeReplicationSourceConnectRetry,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_sourceDefinition_tokens_561[] = {
    TokenType::changeReplicationSourceRetryCount,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_sourceDefinition_tokens_562[] = {
    TokenType::changeReplicationSourceDelay,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_sourceDefinition_tokens_563[] = {
    TokenType::changeReplicationSourceSSL,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_sourceDefinition_tokens_564[] = {
    TokenType::changeReplicationSourceSSLCA,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceDefinition_tokens_565[] = {
    TokenType::changeReplicationSourceSSLCApath,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceDefinition_tokens_566[] = {
    TokenType::changeReplicationSourceTLSVersion,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceDefinition_tokens_567[] = {
    TokenType::changeReplicationSourceSSLCert,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceDefinition_tokens_568[] = {
    TokenType::changeReplicationSourceTLSCiphersuites,
    TokenType::EQ,
    TokenType::sourceTlsCiphersuitesDef
};

constexpr TokenType mysql_sourceDefinition_tokens_569[] = {
    TokenType::changeReplicationSourceSSLCipher,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceDefinition_tokens_570[] = {
    TokenType::changeReplicationSourceSSLKey,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceDefinition_tokens_571[] = {
    TokenType::changeReplicationSourceSSLVerifyServerCert,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_sourceDefinition_tokens_572[] = {
    TokenType::changeReplicationSourceSSLCLR,
    TokenType::EQ,
    TokenType::textLiteral
};

constexpr TokenType mysql_sourceDefinition_tokens_573[] = {
    TokenType::changeReplicationSourceSSLCLRpath,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceDefinition_tokens_574[] = {
    TokenType::changeReplicationSourcePublicKey,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceDefinition_tokens_575[] = {
    TokenType::changeReplicationSourceGetSourcePublicKey,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_sourceDefinition_tokens_576[] = {
    TokenType::changeReplicationSourceHeartbeatPeriod,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_sourceDefinition_tokens_577[] = {
    TokenType::IGNORE_SERVER_IDS,
    TokenType::EQ,
    TokenType::serverIdList
};

constexpr TokenType mysql_sourceDefinition_tokens_578[] = {
    TokenType::changeReplicationSourceCompressionAlgorithm,
    TokenType::EQ,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_sourceDefinition_tokens_579[] = {
    TokenType::changeReplicationSourceZstdCompressionLevel,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_sourceDefinition_tokens_580[] = {
    TokenType::changeReplicationSourceAutoPosition,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_sourceDefinition_tokens_581[] = {
    TokenType::PRIVILEGE_CHECKS_USER,
    TokenType::EQ,
    TokenType::privilegeCheckDef
};

constexpr TokenType mysql_sourceDefinition_tokens_582[] = {
    TokenType::REQUIRE_ROW_FORMAT,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_sourceDefinition_tokens_583[] = {
    TokenType::REQUIRE_TABLE_PRIMARY_KEY_CHECK,
    TokenType::EQ,
    TokenType::tablePrimaryKeyCheckDef
};

constexpr TokenType mysql_sourceDefinition_tokens_584[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::SOURCE_CONNECTION_AUTO_FAILOVER,
    TokenType::EQ,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_sourceDefinition_tokens_585[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::ASSIGN_GTIDS_TO_ANONYMOUS_TRANSACTIONS,
    TokenType::EQ,
    TokenType::assignGtidsToAnonymousTransactionsDefinition
};

constexpr TokenType mysql_sourceDefinition_tokens_586[] = {
    TokenType::this,
    TokenType::isServerVersionGe80027,
    TokenType::GTID_ONLY,
    TokenType::EQ,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_sourceDefinition_tokens_587[] = {
    TokenType::sourceFileDef
};

constexpr TokenType mysql_changeReplicationSourceAutoPosition_tokens_588[] = {
    TokenType::MASTER_AUTO_POSITION
};

constexpr TokenType mysql_changeReplicationSourceAutoPosition_tokens_589[] = {
    TokenType::SOURCE_AUTO_POSITION
};

constexpr TokenType mysql_changeReplicationSourceHost_tokens_590[] = {
    TokenType::MASTER_HOST
};

constexpr TokenType mysql_changeReplicationSourceHost_tokens_591[] = {
    TokenType::SOURCE_HOST
};

constexpr TokenType mysql_changeReplicationSourceBind_tokens_592[] = {
    TokenType::MASTER_BIND
};

constexpr TokenType mysql_changeReplicationSourceBind_tokens_593[] = {
    TokenType::SOURCE_BIND
};

constexpr TokenType mysql_changeReplicationSourceUser_tokens_594[] = {
    TokenType::MASTER_USER
};

constexpr TokenType mysql_changeReplicationSourceUser_tokens_595[] = {
    TokenType::SOURCE_USER
};

constexpr TokenType mysql_changeReplicationSourcePassword_tokens_596[] = {
    TokenType::MASTER_PASSWORD
};

constexpr TokenType mysql_changeReplicationSourcePassword_tokens_597[] = {
    TokenType::SOURCE_PASSWORD
};

constexpr TokenType mysql_changeReplicationSourcePort_tokens_598[] = {
    TokenType::MASTER_PORT
};

constexpr TokenType mysql_changeReplicationSourcePort_tokens_599[] = {
    TokenType::SOURCE_PORT
};

constexpr TokenType mysql_changeReplicationSourceConnectRetry_tokens_600[] = {
    TokenType::MASTER_CONNECT_RETRY
};

constexpr TokenType mysql_changeReplicationSourceConnectRetry_tokens_601[] = {
    TokenType::SOURCE_CONNECT_RETRY
};

constexpr TokenType mysql_changeReplicationSourceRetryCount_tokens_602[] = {
    TokenType::MASTER_RETRY_COUNT
};

constexpr TokenType mysql_changeReplicationSourceRetryCount_tokens_603[] = {
    TokenType::SOURCE_RETRY_COUNT
};

constexpr TokenType mysql_changeReplicationSourceDelay_tokens_604[] = {
    TokenType::MASTER_DELAY
};

constexpr TokenType mysql_changeReplicationSourceDelay_tokens_605[] = {
    TokenType::SOURCE_DELAY
};

constexpr TokenType mysql_changeReplicationSourceSSL_tokens_606[] = {
    TokenType::MASTER_SSL
};

constexpr TokenType mysql_changeReplicationSourceSSL_tokens_607[] = {
    TokenType::SOURCE_SSL
};

constexpr TokenType mysql_changeReplicationSourceSSLCA_tokens_608[] = {
    TokenType::MASTER_SSL_CA
};

constexpr TokenType mysql_changeReplicationSourceSSLCA_tokens_609[] = {
    TokenType::SOURCE_SSL_CA
};

constexpr TokenType mysql_changeReplicationSourceSSLCApath_tokens_610[] = {
    TokenType::MASTER_SSL_CAPATH
};

constexpr TokenType mysql_changeReplicationSourceSSLCApath_tokens_611[] = {
    TokenType::SOURCE_SSL_CAPATH
};

constexpr TokenType mysql_changeReplicationSourceSSLCipher_tokens_612[] = {
    TokenType::MASTER_SSL_CIPHER
};

constexpr TokenType mysql_changeReplicationSourceSSLCipher_tokens_613[] = {
    TokenType::SOURCE_SSL_CIPHER
};

constexpr TokenType mysql_changeReplicationSourceSSLCLR_tokens_614[] = {
    TokenType::MASTER_SSL_CRL
};

constexpr TokenType mysql_changeReplicationSourceSSLCLR_tokens_615[] = {
    TokenType::SOURCE_SSL_CRL
};

constexpr TokenType mysql_changeReplicationSourceSSLCLRpath_tokens_616[] = {
    TokenType::MASTER_SSL_CRLPATH
};

constexpr TokenType mysql_changeReplicationSourceSSLCLRpath_tokens_617[] = {
    TokenType::SOURCE_SSL_CRLPATH
};

constexpr TokenType mysql_changeReplicationSourceSSLKey_tokens_618[] = {
    TokenType::MASTER_SSL_KEY
};

constexpr TokenType mysql_changeReplicationSourceSSLKey_tokens_619[] = {
    TokenType::SOURCE_SSL_KEY
};

constexpr TokenType mysql_changeReplicationSourceSSLVerifyServerCert_tokens_620[] = {
    TokenType::MASTER_SSL_VERIFY_SERVER_CERT
};

constexpr TokenType mysql_changeReplicationSourceSSLVerifyServerCert_tokens_621[] = {
    TokenType::SOURCE_SSL_VERIFY_SERVER_CERT
};

constexpr TokenType mysql_changeReplicationSourceTLSVersion_tokens_622[] = {
    TokenType::MASTER_TLS_VERSION
};

constexpr TokenType mysql_changeReplicationSourceTLSVersion_tokens_623[] = {
    TokenType::SOURCE_TLS_VERSION
};

constexpr TokenType mysql_changeReplicationSourceTLSCiphersuites_tokens_624[] = {
    TokenType::MASTER_TLS_CIPHERSUITES
};

constexpr TokenType mysql_changeReplicationSourceTLSCiphersuites_tokens_625[] = {
    TokenType::SOURCE_TLS_CIPHERSUITES
};

constexpr TokenType mysql_changeReplicationSourceSSLCert_tokens_626[] = {
    TokenType::MASTER_SSL_CERT
};

constexpr TokenType mysql_changeReplicationSourceSSLCert_tokens_627[] = {
    TokenType::SOURCE_SSL_CERT
};

constexpr TokenType mysql_changeReplicationSourcePublicKey_tokens_628[] = {
    TokenType::MASTER_PUBLIC_KEY_PATH
};

constexpr TokenType mysql_changeReplicationSourcePublicKey_tokens_629[] = {
    TokenType::SOURCE_PUBLIC_KEY_PATH
};

constexpr TokenType mysql_changeReplicationSourceGetSourcePublicKey_tokens_630[] = {
    TokenType::GET_MASTER_PUBLIC_KEY
};

constexpr TokenType mysql_changeReplicationSourceGetSourcePublicKey_tokens_631[] = {
    TokenType::GET_SOURCE_PUBLIC_KEY
};

constexpr TokenType mysql_changeReplicationSourceHeartbeatPeriod_tokens_632[] = {
    TokenType::MASTER_HEARTBEAT_PERIOD
};

constexpr TokenType mysql_changeReplicationSourceHeartbeatPeriod_tokens_633[] = {
    TokenType::SOURCE_HEARTBEAT_PERIOD
};

constexpr TokenType mysql_changeReplicationSourceCompressionAlgorithm_tokens_634[] = {
    TokenType::MASTER_COMPRESSION_ALGORITHM
};

constexpr TokenType mysql_changeReplicationSourceCompressionAlgorithm_tokens_635[] = {
    TokenType::SOURCE_COMPRESSION_ALGORITHM
};

constexpr TokenType mysql_changeReplicationSourceZstdCompressionLevel_tokens_636[] = {
    TokenType::MASTER_ZSTD_COMPRESSION_LEVEL
};

constexpr TokenType mysql_changeReplicationSourceZstdCompressionLevel_tokens_637[] = {
    TokenType::SOURCE_ZSTD_COMPRESSION_LEVEL
};

constexpr TokenType mysql_privilegeCheckDef_tokens_638[] = {
    TokenType::userIdentifierOrText
};

constexpr TokenType mysql_privilegeCheckDef_tokens_639[] = {
    TokenType::NULL_KW
};

constexpr TokenType mysql_tablePrimaryKeyCheckDef_tokens_640[] = {
    TokenType::STREAM
};

constexpr TokenType mysql_tablePrimaryKeyCheckDef_tokens_641[] = {
    TokenType::ON
};

constexpr TokenType mysql_tablePrimaryKeyCheckDef_tokens_642[] = {
    TokenType::OFF
};

constexpr TokenType mysql_tablePrimaryKeyCheckDef_tokens_643[] = {
    TokenType::GENERATE
};

constexpr TokenType mysql_assignGtidsToAnonymousTransactionsDefinition_tokens_644[] = {
    TokenType::OFF
};

constexpr TokenType mysql_assignGtidsToAnonymousTransactionsDefinition_tokens_645[] = {
    TokenType::LOCAL
};

constexpr TokenType mysql_assignGtidsToAnonymousTransactionsDefinition_tokens_646[] = {
    TokenType::textStringLiteral
};

constexpr TokenType mysql_sourceTlsCiphersuitesDef_tokens_647[] = {
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceTlsCiphersuitesDef_tokens_648[] = {
    TokenType::NULL_KW
};

constexpr TokenType mysql_sourceFileDef_tokens_649[] = {
    TokenType::sourceLogFile,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceFileDef_tokens_650[] = {
    TokenType::sourceLogPos,
    TokenType::EQ,
    TokenType::ulonglongNumber
};

constexpr TokenType mysql_sourceFileDef_tokens_651[] = {
    TokenType::RELAY_LOG_FILE,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_sourceFileDef_tokens_652[] = {
    TokenType::RELAY_LOG_POS,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_sourceLogFile_tokens_653[] = {
    TokenType::MASTER_LOG_FILE
};

constexpr TokenType mysql_sourceLogFile_tokens_654[] = {
    TokenType::SOURCE_LOG_FILE
};

constexpr TokenType mysql_sourceLogPos_tokens_655[] = {
    TokenType::MASTER_LOG_POS
};

constexpr TokenType mysql_sourceLogPos_tokens_656[] = {
    TokenType::SOURCE_LOG_POS
};

constexpr TokenType mysql_serverIdList_tokens_657[] = {
    TokenType::LPAREN,
    TokenType::ulong_number,
    TokenType::COMMA,
    TokenType::ulong_number,
    TokenType::RPAREN
};

constexpr TokenType mysql_changeReplication_tokens_658[] = {
    TokenType::CHANGE,
    TokenType::REPLICATION,
    TokenType::FILTER,
    TokenType::filterDefinition,
    TokenType::COMMA,
    TokenType::filterDefinition,
    TokenType::channel
};

constexpr TokenType mysql_filterDefinition_tokens_659[] = {
    TokenType::REPLICATE_DO_DB,
    TokenType::EQ,
    TokenType::LPAREN,
    TokenType::filterDbList,
    TokenType::RPAREN
};

constexpr TokenType mysql_filterDefinition_tokens_660[] = {
    TokenType::REPLICATE_IGNORE_DB,
    TokenType::EQ,
    TokenType::LPAREN,
    TokenType::filterDbList,
    TokenType::RPAREN
};

constexpr TokenType mysql_filterDefinition_tokens_661[] = {
    TokenType::REPLICATE_DO_TABLE,
    TokenType::EQ,
    TokenType::LPAREN,
    TokenType::filterTableList,
    TokenType::RPAREN
};

constexpr TokenType mysql_filterDefinition_tokens_662[] = {
    TokenType::REPLICATE_IGNORE_TABLE,
    TokenType::EQ,
    TokenType::LPAREN,
    TokenType::filterTableList,
    TokenType::RPAREN
};

constexpr TokenType mysql_filterDefinition_tokens_663[] = {
    TokenType::REPLICATE_WILD_DO_TABLE,
    TokenType::EQ,
    TokenType::LPAREN,
    TokenType::filterStringList,
    TokenType::RPAREN
};

constexpr TokenType mysql_filterDefinition_tokens_664[] = {
    TokenType::REPLICATE_WILD_IGNORE_TABLE,
    TokenType::EQ,
    TokenType::LPAREN,
    TokenType::filterStringList,
    TokenType::RPAREN
};

constexpr TokenType mysql_filterDefinition_tokens_665[] = {
    TokenType::REPLICATE_REWRITE_DB,
    TokenType::EQ,
    TokenType::LPAREN,
    TokenType::filterDbPairList,
    TokenType::RPAREN
};

constexpr TokenType mysql_filterDbList_tokens_666[] = {
    TokenType::schemaRef,
    TokenType::COMMA,
    TokenType::schemaRef
};

constexpr TokenType mysql_filterTableList_tokens_667[] = {
    TokenType::filterTableRef,
    TokenType::COMMA,
    TokenType::filterTableRef
};

constexpr TokenType mysql_filterStringList_tokens_668[] = {
    TokenType::filterWildDbTableString,
    TokenType::COMMA,
    TokenType::filterWildDbTableString
};

constexpr TokenType mysql_filterWildDbTableString_tokens_669[] = {
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_filterDbPairList_tokens_670[] = {
    TokenType::schemaIdentifierPair,
    TokenType::COMMA,
    TokenType::schemaIdentifierPair
};

constexpr TokenType mysql_startReplicaStatement_tokens_671[] = {
    TokenType::STAR,
    TokenType::replica,
    TokenType::replicaThreadOptions,
    TokenType::UNTIL,
    TokenType::replicaUntil,
    TokenType::userOption,
    TokenType::passwordOption,
    TokenType::defaultAuthOption,
    TokenType::pluginDirOption,
    TokenType::channel
};

constexpr TokenType mysql_stopReplicaStatement_tokens_672[] = {
    TokenType::STOP,
    TokenType::replica,
    TokenType::replicaThreadOptions,
    TokenType::channel
};

constexpr TokenType mysql_replicaUntil_tokens_673[] = {
    TokenType::sourceFileDef,
    TokenType::COMMA,
    TokenType::sourceFileDef
};

constexpr TokenType mysql_replicaUntil_tokens_674[] = {
    TokenType::SQL_BEFORE_GTIDS,
    TokenType::EQ,
    TokenType::textString,
    TokenType::COMMA,
    TokenType::sourceFileDef
};

constexpr TokenType mysql_replicaUntil_tokens_675[] = {
    TokenType::SQL_AFTER_GTIDS,
    TokenType::EQ,
    TokenType::textString,
    TokenType::COMMA,
    TokenType::sourceFileDef
};

constexpr TokenType mysql_replicaUntil_tokens_676[] = {
    TokenType::SQL_AFTER_MTS_GAPS,
    TokenType::COMMA,
    TokenType::sourceFileDef
};

constexpr TokenType mysql_userOption_tokens_677[] = {
    TokenType::USER,
    TokenType::EQ,
    TokenType::textString
};

constexpr TokenType mysql_passwordOption_tokens_678[] = {
    TokenType::PASSWORD,
    TokenType::EQ,
    TokenType::textString
};

constexpr TokenType mysql_defaultAuthOption_tokens_679[] = {
    TokenType::DEFAULT_AUTH,
    TokenType::EQ,
    TokenType::textString
};

constexpr TokenType mysql_pluginDirOption_tokens_680[] = {
    TokenType::PLUGIN_DIR,
    TokenType::EQ,
    TokenType::textString
};

constexpr TokenType mysql_replicaThreadOptions_tokens_681[] = {
    TokenType::replicaThreadOption,
    TokenType::COMMA,
    TokenType::replicaThreadOption
};

constexpr TokenType mysql_replicaThreadOption_tokens_682[] = {
    TokenType::SQL_THREAD
};

constexpr TokenType mysql_replicaThreadOption_tokens_683[] = {
    TokenType::RELAY_THREAD
};

constexpr TokenType mysql_groupReplication_tokens_684[] = {
    TokenType::STAR,
    TokenType::groupReplicationStartOptions,
    TokenType::GROUP_REPLICATION
};

constexpr TokenType mysql_groupReplication_tokens_685[] = {
    TokenType::STOP,
    TokenType::GROUP_REPLICATION
};

constexpr TokenType mysql_groupReplicationStartOptions_tokens_686[] = {
    TokenType::groupReplicationStartOption,
    TokenType::COMMA,
    TokenType::groupReplicationStartOption
};

constexpr TokenType mysql_groupReplicationStartOption_tokens_687[] = {
    TokenType::groupReplicationUser
};

constexpr TokenType mysql_groupReplicationStartOption_tokens_688[] = {
    TokenType::groupReplicationPassword
};

constexpr TokenType mysql_groupReplicationStartOption_tokens_689[] = {
    TokenType::groupReplicationPluginAuth
};

constexpr TokenType mysql_groupReplicationUser_tokens_690[] = {
    TokenType::USER,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_groupReplicationPassword_tokens_691[] = {
    TokenType::PASSWORD,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_groupReplicationPluginAuth_tokens_692[] = {
    TokenType::DEFAULT_AUTH,
    TokenType::EQ,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_replica_tokens_693[] = {
    TokenType::SLAVE
};

constexpr TokenType mysql_replica_tokens_694[] = {
    TokenType::REPLICA
};

constexpr TokenType mysql_preparedStatement_tokens_695[] = {
    TokenType::type,
    TokenType::PREPARE,
    TokenType::identifier,
    TokenType::FROM,
    TokenType::textLiteral
};

constexpr TokenType mysql_preparedStatement_tokens_696[] = {
    TokenType::type,
    TokenType::PREPARE,
    TokenType::identifier,
    TokenType::FROM,
    TokenType::userVariable
};

constexpr TokenType mysql_preparedStatement_tokens_697[] = {
    TokenType::executeStatement
};

constexpr TokenType mysql_preparedStatement_tokens_698[] = {
    TokenType::type,
    TokenType::DEALLOCATE,
    TokenType::PREPARE,
    TokenType::identifier
};

constexpr TokenType mysql_preparedStatement_tokens_699[] = {
    TokenType::type,
    TokenType::DROP,
    TokenType::PREPARE,
    TokenType::identifier
};

constexpr TokenType mysql_executeStatement_tokens_700[] = {
    TokenType::EXECUTE,
    TokenType::identifier,
    TokenType::USING,
    TokenType::executeVarList
};

constexpr TokenType mysql_executeVarList_tokens_701[] = {
    TokenType::userVariable,
    TokenType::COMMA,
    TokenType::userVariable
};

constexpr TokenType mysql_cloneStatement_tokens_702[] = {
    TokenType::CLONE,
    TokenType::LOCAL,
    TokenType::DATA,
    TokenType::DIRECTORY,
    TokenType::equal,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_cloneStatement_tokens_703[] = {
    TokenType::CLONE,
    TokenType::REMOTE,
    TokenType::FOR,
    TokenType::REPLICATION
};

constexpr TokenType mysql_cloneStatement_tokens_704[] = {
    TokenType::CLONE,
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::INSTANCE,
    TokenType::FROM,
    TokenType::user,
    TokenType::COLON,
    TokenType::ulong_number,
    TokenType::IDENTIFIED,
    TokenType::BY,
    TokenType::textStringLiteral,
    TokenType::dataDirSSL
};

constexpr TokenType mysql_dataDirSSL_tokens_705[] = {
    TokenType::ssl
};

constexpr TokenType mysql_dataDirSSL_tokens_706[] = {
    TokenType::DATA,
    TokenType::DIRECTORY,
    TokenType::equal,
    TokenType::textStringLiteral,
    TokenType::ssl
};

constexpr TokenType mysql_ssl_tokens_707[] = {
    TokenType::REQUIRE,
    TokenType::NO,
    TokenType::SSL
};

constexpr TokenType mysql_accountManagementStatement_tokens_708[] = {
    TokenType::alterUserStatement
};

constexpr TokenType mysql_accountManagementStatement_tokens_709[] = {
    TokenType::createUserStatement
};

constexpr TokenType mysql_accountManagementStatement_tokens_710[] = {
    TokenType::dropUserStatement
};

constexpr TokenType mysql_accountManagementStatement_tokens_711[] = {
    TokenType::grantStatement
};

constexpr TokenType mysql_accountManagementStatement_tokens_712[] = {
    TokenType::renameUserStatement
};

constexpr TokenType mysql_accountManagementStatement_tokens_713[] = {
    TokenType::revokeStatement
};

constexpr TokenType mysql_accountManagementStatement_tokens_714[] = {
    TokenType::setRoleStatement
};

constexpr TokenType mysql_alterUserStatement_tokens_715[] = {
    TokenType::ALTER,
    TokenType::USER,
    TokenType::ifExists,
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::createUserList,
    TokenType::createUserTail
};

constexpr TokenType mysql_alterUserStatement_tokens_716[] = {
    TokenType::ALTER,
    TokenType::USER,
    TokenType::ifExists,
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::alterUserList,
    TokenType::createUserTail
};

constexpr TokenType mysql_alterUserStatement_tokens_717[] = {
    TokenType::ALTER,
    TokenType::USER,
    TokenType::ifExists,
    TokenType::userFunction,
    TokenType::identifiedByRandomPassword,
    TokenType::replacePassword,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_alterUserStatement_tokens_718[] = {
    TokenType::ALTER,
    TokenType::USER,
    TokenType::ifExists,
    TokenType::userFunction,
    TokenType::identifiedByPassword,
    TokenType::replacePassword,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_alterUserStatement_tokens_719[] = {
    TokenType::ALTER,
    TokenType::USER,
    TokenType::ifExists,
    TokenType::userFunction,
    TokenType::DISCARD,
    TokenType::OLD,
    TokenType::PASSWORD
};

constexpr TokenType mysql_alterUserStatement_tokens_720[] = {
    TokenType::ALTER,
    TokenType::USER,
    TokenType::ifExists,
    TokenType::userFunction,
    TokenType::userRegistration
};

constexpr TokenType mysql_alterUserStatement_tokens_721[] = {
    TokenType::ALTER,
    TokenType::USER,
    TokenType::ifExists,
    TokenType::user,
    TokenType::DEFAULT,
    TokenType::ROLE,
    TokenType::ALL
};

constexpr TokenType mysql_alterUserStatement_tokens_722[] = {
    TokenType::ALTER,
    TokenType::USER,
    TokenType::ifExists,
    TokenType::user,
    TokenType::DEFAULT,
    TokenType::ROLE,
    TokenType::NONE
};

constexpr TokenType mysql_alterUserStatement_tokens_723[] = {
    TokenType::ALTER,
    TokenType::USER,
    TokenType::ifExists,
    TokenType::user,
    TokenType::DEFAULT,
    TokenType::ROLE,
    TokenType::roleList
};

constexpr TokenType mysql_alterUserStatement_tokens_724[] = {
    TokenType::ALTER,
    TokenType::USER,
    TokenType::ifExists,
    TokenType::user,
    TokenType::userRegistration
};

constexpr TokenType mysql_alterUserList_tokens_725[] = {
    TokenType::alterUser,
    TokenType::COMMA,
    TokenType::alterUser
};

constexpr TokenType mysql_alterUser_tokens_726[] = {
    TokenType::this,
    TokenType::isServerVersionLt80025,
    TokenType::oldAlterUser
};

constexpr TokenType mysql_alterUser_tokens_727[] = {
    TokenType::this,
    TokenType::isServerVersionGe80025,
    TokenType::user,
    TokenType::identifiedByPassword,
    TokenType::REPLACE,
    TokenType::textStringLiteral,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_alterUser_tokens_728[] = {
    TokenType::this,
    TokenType::isServerVersionGe80025,
    TokenType::user,
    TokenType::identifiedByPassword,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_alterUser_tokens_729[] = {
    TokenType::this,
    TokenType::isServerVersionGe80025,
    TokenType::user,
    TokenType::identifiedByRandomPassword,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_alterUser_tokens_730[] = {
    TokenType::this,
    TokenType::isServerVersionGe80025,
    TokenType::user,
    TokenType::identifiedByRandomPassword,
    TokenType::REPLACE,
    TokenType::textStringLiteral,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_alterUser_tokens_731[] = {
    TokenType::this,
    TokenType::isServerVersionGe80025,
    TokenType::user,
    TokenType::identifiedWithPlugin
};

constexpr TokenType mysql_alterUser_tokens_732[] = {
    TokenType::this,
    TokenType::isServerVersionGe80025,
    TokenType::user,
    TokenType::identifiedWithPluginAsAuth,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_alterUser_tokens_733[] = {
    TokenType::this,
    TokenType::isServerVersionGe80025,
    TokenType::user,
    TokenType::identifiedWithPluginByPassword,
    TokenType::REPLACE,
    TokenType::textStringLiteral,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_alterUser_tokens_734[] = {
    TokenType::this,
    TokenType::isServerVersionGe80025,
    TokenType::user,
    TokenType::identifiedWithPluginByPassword,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_alterUser_tokens_735[] = {
    TokenType::this,
    TokenType::isServerVersionGe80025,
    TokenType::user,
    TokenType::identifiedWithPluginByRandomPassword,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_alterUser_tokens_736[] = {
    TokenType::this,
    TokenType::isServerVersionGe80025,
    TokenType::user,
    TokenType::discardOldPassword
};

constexpr TokenType mysql_alterUser_tokens_737[] = {
    TokenType::this,
    TokenType::isServerVersionGe80025,
    TokenType::user,
    TokenType::ADD,
    TokenType::factor,
    TokenType::identification,
    TokenType::ADD,
    TokenType::factor,
    TokenType::identification
};

constexpr TokenType mysql_alterUser_tokens_738[] = {
    TokenType::this,
    TokenType::isServerVersionGe80025,
    TokenType::user,
    TokenType::MODIFY,
    TokenType::factor,
    TokenType::identification,
    TokenType::MODIFY,
    TokenType::factor,
    TokenType::identification
};

constexpr TokenType mysql_alterUser_tokens_739[] = {
    TokenType::this,
    TokenType::isServerVersionGe80025,
    TokenType::user,
    TokenType::DROP,
    TokenType::factor,
    TokenType::DROP,
    TokenType::factor
};

constexpr TokenType mysql_oldAlterUser_tokens_740[] = {
    TokenType::user,
    TokenType::IDENTIFIED,
    TokenType::BY,
    TokenType::textString,
    TokenType::REPLACE,
    TokenType::textString,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_oldAlterUser_tokens_741[] = {
    TokenType::user,
    TokenType::IDENTIFIED,
    TokenType::BY,
    TokenType::textString,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_oldAlterUser_tokens_742[] = {
    TokenType::user,
    TokenType::IDENTIFIED,
    TokenType::BY,
    TokenType::RANDOM,
    TokenType::PASSWORD,
    TokenType::REPLACE,
    TokenType::textString,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_oldAlterUser_tokens_743[] = {
    TokenType::user,
    TokenType::IDENTIFIED,
    TokenType::WITH,
    TokenType::textOrIdentifier,
    TokenType::BY,
    TokenType::textString,
    TokenType::REPLACE,
    TokenType::textString,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_oldAlterUser_tokens_744[] = {
    TokenType::user,
    TokenType::IDENTIFIED,
    TokenType::WITH,
    TokenType::textOrIdentifier,
    TokenType::AS,
    TokenType::textStringHash,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_oldAlterUser_tokens_745[] = {
    TokenType::user,
    TokenType::IDENTIFIED,
    TokenType::WITH,
    TokenType::textOrIdentifier,
    TokenType::BY,
    TokenType::textString,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_oldAlterUser_tokens_746[] = {
    TokenType::user,
    TokenType::IDENTIFIED,
    TokenType::WITH,
    TokenType::textOrIdentifier,
    TokenType::BY,
    TokenType::RANDOM,
    TokenType::PASSWORD,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_oldAlterUser_tokens_747[] = {
    TokenType::user,
    TokenType::discardOldPassword
};

constexpr TokenType mysql_userFunction_tokens_748[] = {
    TokenType::USER,
    TokenType::parentheses
};

constexpr TokenType mysql_userAttributes_tokens_749[] = {
    TokenType::ATTRIBUTE,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_userAttributes_tokens_750[] = {
    TokenType::COMMENT,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_defaultRoleClause_tokens_751[] = {
    TokenType::DEFAULT,
    TokenType::ROLE,
    TokenType::roleList
};

constexpr TokenType mysql_requireClause_tokens_752[] = {
    TokenType::REQUIRE,
    TokenType::requireList
};

constexpr TokenType mysql_requireClause_tokens_753[] = {
    TokenType::REQUIRE,
    TokenType::option,
    TokenType::SSL
};

constexpr TokenType mysql_requireClause_tokens_754[] = {
    TokenType::REQUIRE,
    TokenType::option,
    TokenType::X509
};

constexpr TokenType mysql_requireClause_tokens_755[] = {
    TokenType::REQUIRE,
    TokenType::option,
    TokenType::NONE
};

constexpr TokenType mysql_connectOptions_tokens_756[] = {
    TokenType::WITH,
    TokenType::MAX_QUERIES_PER_HOUR,
    TokenType::ulong_number
};

constexpr TokenType mysql_connectOptions_tokens_757[] = {
    TokenType::WITH,
    TokenType::MAX_UPDATES_PER_HOUR,
    TokenType::ulong_number
};

constexpr TokenType mysql_connectOptions_tokens_758[] = {
    TokenType::WITH,
    TokenType::MAX_CONNECTIONS_PER_HOUR,
    TokenType::ulong_number
};

constexpr TokenType mysql_connectOptions_tokens_759[] = {
    TokenType::WITH,
    TokenType::MAX_USER_CONNECTIONS,
    TokenType::ulong_number
};

constexpr TokenType mysql_accountLockPasswordExpireOptions_tokens_760[] = {
    TokenType::ACCOUNT,
    TokenType::LOCK
};

constexpr TokenType mysql_accountLockPasswordExpireOptions_tokens_761[] = {
    TokenType::ACCOUNT,
    TokenType::UNLOCK
};

constexpr TokenType mysql_accountLockPasswordExpireOptions_tokens_762[] = {
    TokenType::PASSWORD,
    TokenType::EXPIRE,
    TokenType::INTERVAL,
    TokenType::real_ulong_number,
    TokenType::DAY
};

constexpr TokenType mysql_accountLockPasswordExpireOptions_tokens_763[] = {
    TokenType::PASSWORD,
    TokenType::EXPIRE,
    TokenType::NEVER
};

constexpr TokenType mysql_accountLockPasswordExpireOptions_tokens_764[] = {
    TokenType::PASSWORD,
    TokenType::EXPIRE,
    TokenType::DEFAULT
};

constexpr TokenType mysql_accountLockPasswordExpireOptions_tokens_765[] = {
    TokenType::PASSWORD,
    TokenType::HISTORY,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_accountLockPasswordExpireOptions_tokens_766[] = {
    TokenType::PASSWORD,
    TokenType::HISTORY,
    TokenType::DEFAULT
};

constexpr TokenType mysql_accountLockPasswordExpireOptions_tokens_767[] = {
    TokenType::PASSWORD,
    TokenType::REUSE,
    TokenType::INTERVAL,
    TokenType::real_ulong_number,
    TokenType::DAY
};

constexpr TokenType mysql_accountLockPasswordExpireOptions_tokens_768[] = {
    TokenType::PASSWORD,
    TokenType::REUSE,
    TokenType::INTERVAL,
    TokenType::DEFAULT
};

constexpr TokenType mysql_accountLockPasswordExpireOptions_tokens_769[] = {
    TokenType::PASSWORD,
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::REQUIRE,
    TokenType::CURRENT,
    TokenType::DEFAULT
};

constexpr TokenType mysql_accountLockPasswordExpireOptions_tokens_770[] = {
    TokenType::PASSWORD,
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::REQUIRE,
    TokenType::CURRENT,
    TokenType::OPTIONAL
};

constexpr TokenType mysql_accountLockPasswordExpireOptions_tokens_771[] = {
    TokenType::FAILED_LOGIN_ATTEMPTS,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_accountLockPasswordExpireOptions_tokens_772[] = {
    TokenType::PASSWORD_LOCK_TIME,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_accountLockPasswordExpireOptions_tokens_773[] = {
    TokenType::PASSWORD_LOCK_TIME,
    TokenType::UNBOUNDED
};

constexpr TokenType mysql_userAttribute_tokens_774[] = {
    TokenType::ATTRIBUTE,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_userAttribute_tokens_775[] = {
    TokenType::COMMENT,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_grantStatement_tokens_776[] = {
    TokenType::GRANT,
    TokenType::roleOrPrivilegesList,
    TokenType::TO,
    TokenType::userList,
    TokenType::WITH,
    TokenType::ADMIN,
    TokenType::OPTION
};

constexpr TokenType mysql_grantStatement_tokens_777[] = {
    TokenType::GRANT,
    TokenType::roleOrPrivilegesList,
    TokenType::ON,
    TokenType::aclType,
    TokenType::grantIdentifier,
    TokenType::TO,
    TokenType::grantTargetList,
    TokenType::versionedRequireClause,
    TokenType::grantOptions,
    TokenType::grantAs
};

constexpr TokenType mysql_grantStatement_tokens_778[] = {
    TokenType::GRANT,
    TokenType::ALL,
    TokenType::PRIVILEGES,
    TokenType::ON,
    TokenType::aclType,
    TokenType::grantIdentifier,
    TokenType::TO,
    TokenType::grantTargetList,
    TokenType::versionedRequireClause,
    TokenType::grantOptions,
    TokenType::grantAs
};

constexpr TokenType mysql_grantStatement_tokens_779[] = {
    TokenType::GRANT,
    TokenType::PROXY,
    TokenType::ON,
    TokenType::user,
    TokenType::TO,
    TokenType::grantTargetList,
    TokenType::WITH,
    TokenType::GRANT,
    TokenType::OPTION
};

constexpr TokenType mysql_grantTargetList_tokens_780[] = {
    TokenType::this,
    TokenType::isServerVersionLt80011,
    TokenType::createUserList
};

constexpr TokenType mysql_grantTargetList_tokens_781[] = {
    TokenType::this,
    TokenType::isServerVersionGe80011,
    TokenType::userList
};

constexpr TokenType mysql_grantOptions_tokens_782[] = {
    TokenType::WITH,
    TokenType::grantOption
};

constexpr TokenType mysql_exceptRoleList_tokens_783[] = {
    TokenType::EXCEPT,
    TokenType::roleList
};

constexpr TokenType mysql_withRoles_tokens_784[] = {
    TokenType::WITH,
    TokenType::ROLE,
    TokenType::roleList
};

constexpr TokenType mysql_withRoles_tokens_785[] = {
    TokenType::WITH,
    TokenType::ROLE,
    TokenType::ALL,
    TokenType::exceptRoleList
};

constexpr TokenType mysql_withRoles_tokens_786[] = {
    TokenType::WITH,
    TokenType::ROLE,
    TokenType::NONE
};

constexpr TokenType mysql_withRoles_tokens_787[] = {
    TokenType::WITH,
    TokenType::ROLE,
    TokenType::DEFAULT
};

constexpr TokenType mysql_grantAs_tokens_788[] = {
    TokenType::AS,
    TokenType::USER,
    TokenType::withRoles
};

constexpr TokenType mysql_versionedRequireClause_tokens_789[] = {
    TokenType::this,
    TokenType::isServerVersionLt80011,
    TokenType::requireClause
};

constexpr TokenType mysql_renameUserStatement_tokens_790[] = {
    TokenType::RENAME,
    TokenType::USER,
    TokenType::user,
    TokenType::TO,
    TokenType::user,
    TokenType::COMMA,
    TokenType::user,
    TokenType::TO,
    TokenType::user
};

constexpr TokenType mysql_revokeStatement_tokens_791[] = {
    TokenType::REVOKE,
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::ifExists,
    TokenType::roleOrPrivilegesList,
    TokenType::FROM,
    TokenType::userList,
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::ignoreUnknownUser
};

constexpr TokenType mysql_revokeStatement_tokens_792[] = {
    TokenType::REVOKE,
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::ifExists,
    TokenType::roleOrPrivilegesList,
    TokenType::ON,
    TokenType::aclType,
    TokenType::grantIdentifier,
    TokenType::FROM,
    TokenType::userList,
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::ignoreUnknownUser
};

constexpr TokenType mysql_revokeStatement_tokens_793[] = {
    TokenType::REVOKE,
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::ifExists,
    TokenType::ALL,
    TokenType::PRIVILEGES,
    TokenType::ON,
    TokenType::aclType,
    TokenType::grantIdentifier,
    TokenType::FROM,
    TokenType::userList,
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::ignoreUnknownUser
};

constexpr TokenType mysql_revokeStatement_tokens_794[] = {
    TokenType::REVOKE,
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::ifExists,
    TokenType::ALL,
    TokenType::PRIVILEGES,
    TokenType::COMMA,
    TokenType::GRANT,
    TokenType::OPTION,
    TokenType::FROM,
    TokenType::userList,
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::ignoreUnknownUser
};

constexpr TokenType mysql_revokeStatement_tokens_795[] = {
    TokenType::REVOKE,
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::ifExists,
    TokenType::PROXY,
    TokenType::ON,
    TokenType::user,
    TokenType::FROM,
    TokenType::userList,
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::ignoreUnknownUser
};

constexpr TokenType mysql_aclType_tokens_796[] = {
    TokenType::TABLE
};

constexpr TokenType mysql_aclType_tokens_797[] = {
    TokenType::FUNCTION
};

constexpr TokenType mysql_aclType_tokens_798[] = {
    TokenType::PROCEDURE
};

constexpr TokenType mysql_roleOrPrivilegesList_tokens_799[] = {
    TokenType::roleOrPrivilege,
    TokenType::COMMA,
    TokenType::roleOrPrivilege
};

constexpr TokenType mysql_roleOrPrivilege_tokens_800[] = {
    TokenType::roleIdentifierOrText,
    TokenType::columnInternalRefList
};

constexpr TokenType mysql_roleOrPrivilege_tokens_801[] = {
    TokenType::roleIdentifierOrText,
    TokenType::AT_TEXT_SUFFIX
};

constexpr TokenType mysql_roleOrPrivilege_tokens_802[] = {
    TokenType::roleIdentifierOrText,
    TokenType::AT_SIGN,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_roleOrPrivilege_tokens_803[] = {
    TokenType::SELECT,
    TokenType::columnInternalRefList
};

constexpr TokenType mysql_roleOrPrivilege_tokens_804[] = {
    TokenType::INSERT,
    TokenType::columnInternalRefList
};

constexpr TokenType mysql_roleOrPrivilege_tokens_805[] = {
    TokenType::UPDATE,
    TokenType::columnInternalRefList
};

constexpr TokenType mysql_roleOrPrivilege_tokens_806[] = {
    TokenType::REFERENCES,
    TokenType::columnInternalRefList
};

constexpr TokenType mysql_roleOrPrivilege_tokens_807[] = {
    TokenType::DELETE
};

constexpr TokenType mysql_roleOrPrivilege_tokens_808[] = {
    TokenType::USAGE
};

constexpr TokenType mysql_roleOrPrivilege_tokens_809[] = {
    TokenType::INDEX
};

constexpr TokenType mysql_roleOrPrivilege_tokens_810[] = {
    TokenType::DROP
};

constexpr TokenType mysql_roleOrPrivilege_tokens_811[] = {
    TokenType::EXECUTE
};

constexpr TokenType mysql_roleOrPrivilege_tokens_812[] = {
    TokenType::RELOAD
};

constexpr TokenType mysql_roleOrPrivilege_tokens_813[] = {
    TokenType::SHUTDOWN
};

constexpr TokenType mysql_roleOrPrivilege_tokens_814[] = {
    TokenType::PROCESS
};

constexpr TokenType mysql_roleOrPrivilege_tokens_815[] = {
    TokenType::FILE
};

constexpr TokenType mysql_roleOrPrivilege_tokens_816[] = {
    TokenType::PROXY
};

constexpr TokenType mysql_roleOrPrivilege_tokens_817[] = {
    TokenType::SUPER
};

constexpr TokenType mysql_roleOrPrivilege_tokens_818[] = {
    TokenType::EVENT
};

constexpr TokenType mysql_roleOrPrivilege_tokens_819[] = {
    TokenType::TRIGGER
};

constexpr TokenType mysql_roleOrPrivilege_tokens_820[] = {
    TokenType::GRANT,
    TokenType::OPTION
};

constexpr TokenType mysql_roleOrPrivilege_tokens_821[] = {
    TokenType::SHOW,
    TokenType::DATABASES
};

constexpr TokenType mysql_roleOrPrivilege_tokens_822[] = {
    TokenType::CREATE,
    TokenType::TEMPORARY,
    TokenType::object,
    TokenType::TABLES
};

constexpr TokenType mysql_roleOrPrivilege_tokens_823[] = {
    TokenType::CREATE,
    TokenType::object,
    TokenType::ROUTINE
};

constexpr TokenType mysql_roleOrPrivilege_tokens_824[] = {
    TokenType::CREATE,
    TokenType::object,
    TokenType::TABLESPACE
};

constexpr TokenType mysql_roleOrPrivilege_tokens_825[] = {
    TokenType::CREATE,
    TokenType::object,
    TokenType::USER
};

constexpr TokenType mysql_roleOrPrivilege_tokens_826[] = {
    TokenType::CREATE,
    TokenType::object,
    TokenType::VIEW
};

constexpr TokenType mysql_roleOrPrivilege_tokens_827[] = {
    TokenType::LOCK,
    TokenType::TABLES
};

constexpr TokenType mysql_roleOrPrivilege_tokens_828[] = {
    TokenType::REPLICATION,
    TokenType::CLIENT
};

constexpr TokenType mysql_roleOrPrivilege_tokens_829[] = {
    TokenType::REPLICATION,
    TokenType::replica
};

constexpr TokenType mysql_roleOrPrivilege_tokens_830[] = {
    TokenType::SHOW,
    TokenType::VIEW
};

constexpr TokenType mysql_roleOrPrivilege_tokens_831[] = {
    TokenType::ALTER,
    TokenType::ROUTINE
};

constexpr TokenType mysql_roleOrPrivilege_tokens_832[] = {
    TokenType::CREATE,
    TokenType::ROLE
};

constexpr TokenType mysql_roleOrPrivilege_tokens_833[] = {
    TokenType::DROP,
    TokenType::ROLE
};

constexpr TokenType mysql_grantIdentifier_tokens_834[] = {
    TokenType::STAR,
    TokenType::DOT,
    TokenType::STAR
};

constexpr TokenType mysql_grantIdentifier_tokens_835[] = {
    TokenType::schemaRef,
    TokenType::DOT,
    TokenType::STAR
};

constexpr TokenType mysql_grantIdentifier_tokens_836[] = {
    TokenType::tableRef
};

constexpr TokenType mysql_grantIdentifier_tokens_837[] = {
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::schemaRef,
    TokenType::DOT,
    TokenType::tableRef
};

constexpr TokenType mysql_requireList_tokens_838[] = {
    TokenType::requireListElement,
    TokenType::AND,
    TokenType::requireListElement
};

constexpr TokenType mysql_requireListElement_tokens_839[] = {
    TokenType::element,
    TokenType::CIPHER,
    TokenType::textString
};

constexpr TokenType mysql_requireListElement_tokens_840[] = {
    TokenType::element,
    TokenType::ISSUER,
    TokenType::textString
};

constexpr TokenType mysql_requireListElement_tokens_841[] = {
    TokenType::element,
    TokenType::SUBJECT,
    TokenType::textString
};

constexpr TokenType mysql_grantOption_tokens_842[] = {
    TokenType::option,
    TokenType::GRANT,
    TokenType::OPTION
};

constexpr TokenType mysql_grantOption_tokens_843[] = {
    TokenType::this,
    TokenType::isServerVersionLt80011,
    TokenType::option,
    TokenType::MAX_QUERIES_PER_HOUR,
    TokenType::ulong_number
};

constexpr TokenType mysql_grantOption_tokens_844[] = {
    TokenType::this,
    TokenType::isServerVersionLt80011,
    TokenType::option,
    TokenType::MAX_UPDATES_PER_HOUR,
    TokenType::ulong_number
};

constexpr TokenType mysql_grantOption_tokens_845[] = {
    TokenType::this,
    TokenType::isServerVersionLt80011,
    TokenType::option,
    TokenType::MAX_CONNECTIONS_PER_HOUR,
    TokenType::ulong_number
};

constexpr TokenType mysql_grantOption_tokens_846[] = {
    TokenType::this,
    TokenType::isServerVersionLt80011,
    TokenType::option,
    TokenType::MAX_USER_CONNECTIONS,
    TokenType::ulong_number
};

constexpr TokenType mysql_setRoleStatement_tokens_847[] = {
    TokenType::SET,
    TokenType::ROLE,
    TokenType::roleList
};

constexpr TokenType mysql_setRoleStatement_tokens_848[] = {
    TokenType::SET,
    TokenType::ROLE,
    TokenType::NONE
};

constexpr TokenType mysql_setRoleStatement_tokens_849[] = {
    TokenType::SET,
    TokenType::ROLE,
    TokenType::DEFAULT
};

constexpr TokenType mysql_setRoleStatement_tokens_850[] = {
    TokenType::SET,
    TokenType::DEFAULT,
    TokenType::ROLE,
    TokenType::roleList,
    TokenType::TO,
    TokenType::roleList
};

constexpr TokenType mysql_setRoleStatement_tokens_851[] = {
    TokenType::SET,
    TokenType::DEFAULT,
    TokenType::ROLE,
    TokenType::NONE,
    TokenType::TO,
    TokenType::roleList
};

constexpr TokenType mysql_setRoleStatement_tokens_852[] = {
    TokenType::SET,
    TokenType::DEFAULT,
    TokenType::ROLE,
    TokenType::ALL,
    TokenType::TO,
    TokenType::roleList
};

constexpr TokenType mysql_setRoleStatement_tokens_853[] = {
    TokenType::SET,
    TokenType::ROLE,
    TokenType::ALL,
    TokenType::EXCEPT,
    TokenType::roleList
};

constexpr TokenType mysql_roleList_tokens_854[] = {
    TokenType::role,
    TokenType::COMMA,
    TokenType::role
};

constexpr TokenType mysql_role_tokens_855[] = {
    TokenType::roleIdentifierOrText,
    TokenType::userVariable
};

constexpr TokenType mysql_tableAdministrationStatement_tokens_856[] = {
    TokenType::type,
    TokenType::ANALYZE,
    TokenType::noWriteToBinLog,
    TokenType::TABLE,
    TokenType::tableRefList,
    TokenType::histogram
};

constexpr TokenType mysql_tableAdministrationStatement_tokens_857[] = {
    TokenType::type,
    TokenType::CHECK,
    TokenType::TABLE,
    TokenType::tableRefList,
    TokenType::checkOption
};

constexpr TokenType mysql_tableAdministrationStatement_tokens_858[] = {
    TokenType::type,
    TokenType::CHECKSUM,
    TokenType::TABLE,
    TokenType::tableRefList,
    TokenType::QUICK
};

constexpr TokenType mysql_tableAdministrationStatement_tokens_859[] = {
    TokenType::type,
    TokenType::CHECKSUM,
    TokenType::TABLE,
    TokenType::tableRefList,
    TokenType::EXTENDED
};

constexpr TokenType mysql_tableAdministrationStatement_tokens_860[] = {
    TokenType::type,
    TokenType::OPTIMIZE,
    TokenType::noWriteToBinLog,
    TokenType::TABLE,
    TokenType::tableRefList
};

constexpr TokenType mysql_tableAdministrationStatement_tokens_861[] = {
    TokenType::type,
    TokenType::REPAIR,
    TokenType::noWriteToBinLog,
    TokenType::TABLE,
    TokenType::tableRefList,
    TokenType::repairType
};

constexpr TokenType mysql_histogramNumBuckets_tokens_862[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::WITH,
    TokenType::NUMBER,
    TokenType::BUCKETS
};

constexpr TokenType mysql_histogram_tokens_863[] = {
    TokenType::UPDATE,
    TokenType::HISTOGRAM,
    TokenType::ON,
    TokenType::identifierList,
    TokenType::histogramUpdateParam
};

constexpr TokenType mysql_histogram_tokens_864[] = {
    TokenType::DROP,
    TokenType::HISTOGRAM,
    TokenType::ON,
    TokenType::identifierList
};

constexpr TokenType mysql_checkOption_tokens_865[] = {
    TokenType::FOR,
    TokenType::UPGRADE
};

constexpr TokenType mysql_checkOption_tokens_866[] = {
    TokenType::QUICK
};

constexpr TokenType mysql_checkOption_tokens_867[] = {
    TokenType::FAST
};

constexpr TokenType mysql_checkOption_tokens_868[] = {
    TokenType::MEDIUM
};

constexpr TokenType mysql_checkOption_tokens_869[] = {
    TokenType::EXTENDED
};

constexpr TokenType mysql_checkOption_tokens_870[] = {
    TokenType::CHANGED
};

constexpr TokenType mysql_repairType_tokens_871[] = {
    TokenType::QUICK
};

constexpr TokenType mysql_repairType_tokens_872[] = {
    TokenType::EXTENDED
};

constexpr TokenType mysql_repairType_tokens_873[] = {
    TokenType::USE_FRM
};

constexpr TokenType mysql_uninstallStatement_tokens_874[] = {
    TokenType::UNINSTALL,
    TokenType::PLUGIN,
    TokenType::pluginRef
};

constexpr TokenType mysql_uninstallStatement_tokens_875[] = {
    TokenType::UNINSTALL,
    TokenType::COMPONENT,
    TokenType::componentRef,
    TokenType::COMMA,
    TokenType::componentRef
};

constexpr TokenType mysql_installStatement_tokens_876[] = {
    TokenType::INSTALL,
    TokenType::PLUGIN,
    TokenType::identifier,
    TokenType::SONAME,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_installStatement_tokens_877[] = {
    TokenType::INSTALL,
    TokenType::COMPONENT,
    TokenType::textStringLiteralList,
    TokenType::installSetValueList
};

constexpr TokenType mysql_installOptionType_tokens_878[] = {
    TokenType::GLOBAL
};

constexpr TokenType mysql_installOptionType_tokens_879[] = {
    TokenType::PERSIST
};

constexpr TokenType mysql_installSetRvalue_tokens_880[] = {
    TokenType::expr
};

constexpr TokenType mysql_installSetRvalue_tokens_881[] = {
    TokenType::ON
};

constexpr TokenType mysql_installSetValue_tokens_882[] = {
    TokenType::installOptionType,
    TokenType::lvalueVariable,
    TokenType::equal,
    TokenType::installSetRvalue
};

constexpr TokenType mysql_installSetValueList_tokens_883[] = {
    TokenType::this,
    TokenType::isServerVersionGe80032,
    TokenType::SET,
    TokenType::installSetValue,
    TokenType::COMMA,
    TokenType::installSetValue
};

constexpr TokenType mysql_setStatement_tokens_884[] = {
    TokenType::SET,
    TokenType::startOptionValueList
};

constexpr TokenType mysql_startOptionValueList_tokens_885[] = {
    TokenType::optionValueNoOptionType,
    TokenType::optionValueListContinued
};

constexpr TokenType mysql_startOptionValueList_tokens_886[] = {
    TokenType::TRANSACTION,
    TokenType::transactionCharacteristics
};

constexpr TokenType mysql_startOptionValueList_tokens_887[] = {
    TokenType::optionType,
    TokenType::startOptionValueListFollowingOptionType
};

constexpr TokenType mysql_startOptionValueList_tokens_888[] = {
    TokenType::PASSWORD,
    TokenType::FOR,
    TokenType::user,
    TokenType::equal,
    TokenType::textString,
    TokenType::replacePassword,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_startOptionValueList_tokens_889[] = {
    TokenType::PASSWORD,
    TokenType::FOR,
    TokenType::user,
    TokenType::equal,
    TokenType::textString,
    TokenType::replacePassword,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_startOptionValueList_tokens_890[] = {
    TokenType::PASSWORD,
    TokenType::FOR,
    TokenType::user,
    TokenType::equal,
    TokenType::this,
    TokenType::isServerVersionLt80014,
    TokenType::PASSWORD,
    TokenType::LPAREN,
    TokenType::textString,
    TokenType::RPAREN
};

constexpr TokenType mysql_startOptionValueList_tokens_891[] = {
    TokenType::this,
    TokenType::isServerVersionGe80018,
    TokenType::PASSWORD,
    TokenType::FOR,
    TokenType::user,
    TokenType::TO,
    TokenType::RANDOM,
    TokenType::replacePassword,
    TokenType::retainCurrentPassword
};

constexpr TokenType mysql_transactionCharacteristics_tokens_892[] = {
    TokenType::transactionAccessMode,
    TokenType::isolationLevel
};

constexpr TokenType mysql_transactionCharacteristics_tokens_893[] = {
    TokenType::isolationLevel,
    TokenType::COMMA,
    TokenType::transactionAccessMode
};

constexpr TokenType mysql_transactionAccessMode_tokens_894[] = {
    TokenType::READ,
    TokenType::WRITE
};

constexpr TokenType mysql_transactionAccessMode_tokens_895[] = {
    TokenType::READ,
    TokenType::ONLY
};

constexpr TokenType mysql_isolationLevel_tokens_896[] = {
    TokenType::ISOLATION,
    TokenType::LEVEL,
    TokenType::REPEATABLE,
    TokenType::READ
};

constexpr TokenType mysql_isolationLevel_tokens_897[] = {
    TokenType::ISOLATION,
    TokenType::LEVEL,
    TokenType::READ,
    TokenType::COMMITTED
};

constexpr TokenType mysql_isolationLevel_tokens_898[] = {
    TokenType::ISOLATION,
    TokenType::LEVEL,
    TokenType::READ,
    TokenType::UNCOMMITTED
};

constexpr TokenType mysql_isolationLevel_tokens_899[] = {
    TokenType::ISOLATION,
    TokenType::LEVEL,
    TokenType::SERIALIZABLE
};

constexpr TokenType mysql_optionValueListContinued_tokens_900[] = {
    TokenType::COMMA,
    TokenType::optionValue
};

constexpr TokenType mysql_optionValueNoOptionType_tokens_901[] = {
    TokenType::lvalueVariable,
    TokenType::equal,
    TokenType::setExprOrDefault
};

constexpr TokenType mysql_optionValueNoOptionType_tokens_902[] = {
    TokenType::charsetClause
};

constexpr TokenType mysql_optionValueNoOptionType_tokens_903[] = {
    TokenType::userVariable,
    TokenType::equal,
    TokenType::expr
};

constexpr TokenType mysql_optionValueNoOptionType_tokens_904[] = {
    TokenType::AT_AT_SIGN,
    TokenType::setVarIdentType,
    TokenType::lvalueVariable,
    TokenType::equal,
    TokenType::setExprOrDefault
};

constexpr TokenType mysql_optionValueNoOptionType_tokens_905[] = {
    TokenType::NAMES,
    TokenType::equal,
    TokenType::expr
};

constexpr TokenType mysql_optionValueNoOptionType_tokens_906[] = {
    TokenType::NAMES,
    TokenType::charsetName,
    TokenType::collate
};

constexpr TokenType mysql_optionValueNoOptionType_tokens_907[] = {
    TokenType::NAMES,
    TokenType::this,
    TokenType::isServerVersionGe80011,
    TokenType::DEFAULT
};

constexpr TokenType mysql_optionValue_tokens_908[] = {
    TokenType::optionType,
    TokenType::lvalueVariable,
    TokenType::equal,
    TokenType::setExprOrDefault
};

constexpr TokenType mysql_optionValue_tokens_909[] = {
    TokenType::optionValueNoOptionType
};

constexpr TokenType mysql_setSystemVariable_tokens_910[] = {
    TokenType::AT_AT_SIGN,
    TokenType::setVarIdentType,
    TokenType::lvalueVariable
};

constexpr TokenType mysql_startOptionValueListFollowingOptionType_tokens_911[] = {
    TokenType::optionValueFollowingOptionType,
    TokenType::optionValueListContinued
};

constexpr TokenType mysql_startOptionValueListFollowingOptionType_tokens_912[] = {
    TokenType::TRANSACTION,
    TokenType::transactionCharacteristics
};

constexpr TokenType mysql_optionValueFollowingOptionType_tokens_913[] = {
    TokenType::lvalueVariable,
    TokenType::equal,
    TokenType::setExprOrDefault
};

constexpr TokenType mysql_showDatabasesStatement_tokens_914[] = {
    TokenType::SHOW,
    TokenType::DATABASES,
    TokenType::likeOrWhere
};

constexpr TokenType mysql_showTablesStatement_tokens_915[] = {
    TokenType::SHOW,
    TokenType::showCommandType,
    TokenType::value,
    TokenType::TABLES,
    TokenType::inDb,
    TokenType::likeOrWhere
};

constexpr TokenType mysql_showTriggersStatement_tokens_916[] = {
    TokenType::SHOW,
    TokenType::FULL,
    TokenType::TRIGGERS,
    TokenType::inDb,
    TokenType::likeOrWhere
};

constexpr TokenType mysql_showEventsStatement_tokens_917[] = {
    TokenType::SHOW,
    TokenType::EVENTS,
    TokenType::inDb,
    TokenType::likeOrWhere
};

constexpr TokenType mysql_showTableStatusStatement_tokens_918[] = {
    TokenType::SHOW,
    TokenType::TABLE,
    TokenType::STATUS,
    TokenType::inDb,
    TokenType::likeOrWhere
};

constexpr TokenType mysql_showOpenTablesStatement_tokens_919[] = {
    TokenType::SHOW,
    TokenType::OPEN,
    TokenType::TABLES,
    TokenType::inDb,
    TokenType::likeOrWhere
};

constexpr TokenType mysql_showParseTreeStatement_tokens_920[] = {
    TokenType::this,
    TokenType::isServerVersionGe80100,
    TokenType::SHOW,
    TokenType::PARSE_TREE,
    TokenType::simpleStatement
};

constexpr TokenType mysql_showPluginsStatement_tokens_921[] = {
    TokenType::SHOW,
    TokenType::PLUGINS
};

constexpr TokenType mysql_showEngineLogsStatement_tokens_922[] = {
    TokenType::SHOW,
    TokenType::ENGINE,
    TokenType::engineOrAll,
    TokenType::LOGS
};

constexpr TokenType mysql_showEngineMutexStatement_tokens_923[] = {
    TokenType::SHOW,
    TokenType::ENGINE,
    TokenType::engineOrAll,
    TokenType::MUTEX
};

constexpr TokenType mysql_showEngineStatusStatement_tokens_924[] = {
    TokenType::SHOW,
    TokenType::ENGINE,
    TokenType::engineOrAll,
    TokenType::STATUS
};

constexpr TokenType mysql_showColumnsStatement_tokens_925[] = {
    TokenType::SHOW,
    TokenType::showCommandType,
    TokenType::COLUMNS,
    TokenType::FROM,
    TokenType::tableRef,
    TokenType::inDb,
    TokenType::likeOrWhere
};

constexpr TokenType mysql_showColumnsStatement_tokens_926[] = {
    TokenType::SHOW,
    TokenType::showCommandType,
    TokenType::COLUMNS,
    TokenType::IN,
    TokenType::tableRef,
    TokenType::inDb,
    TokenType::likeOrWhere
};

constexpr TokenType mysql_showBinaryLogsStatement_tokens_927[] = {
    TokenType::SHOW,
    TokenType::BINARY,
    TokenType::value,
    TokenType::LOGS
};

constexpr TokenType mysql_showBinaryLogsStatement_tokens_928[] = {
    TokenType::SHOW,
    TokenType::MASTER,
    TokenType::value,
    TokenType::LOGS
};

constexpr TokenType mysql_showBinaryLogStatusStatement_tokens_929[] = {
    TokenType::SHOW,
    TokenType::BINARY,
    TokenType::LOG,
    TokenType::STATUS
};

constexpr TokenType mysql_showReplicasStatement_tokens_930[] = {
    TokenType::SHOW,
    TokenType::replica,
    TokenType::HOSTS
};

constexpr TokenType mysql_showReplicasStatement_tokens_931[] = {
    TokenType::SHOW,
    TokenType::REPLICAS
};

constexpr TokenType mysql_showBinlogEventsStatement_tokens_932[] = {
    TokenType::SHOW,
    TokenType::BINLOG,
    TokenType::EVENTS,
    TokenType::IN,
    TokenType::textString,
    TokenType::FROM,
    TokenType::ulonglongNumber,
    TokenType::limitClause,
    TokenType::channel
};

constexpr TokenType mysql_showRelaylogEventsStatement_tokens_933[] = {
    TokenType::SHOW,
    TokenType::RELAYLOG,
    TokenType::EVENTS,
    TokenType::IN,
    TokenType::textString,
    TokenType::FROM,
    TokenType::ulonglongNumber,
    TokenType::limitClause,
    TokenType::channel
};

constexpr TokenType mysql_showKeysStatement_tokens_934[] = {
    TokenType::SHOW,
    TokenType::EXTENDED,
    TokenType::INDEX,
    TokenType::fromOrIn,
    TokenType::tableRef,
    TokenType::inDb,
    TokenType::whereClause
};

constexpr TokenType mysql_showKeysStatement_tokens_935[] = {
    TokenType::SHOW,
    TokenType::EXTENDED,
    TokenType::INDEXES,
    TokenType::fromOrIn,
    TokenType::tableRef,
    TokenType::inDb,
    TokenType::whereClause
};

constexpr TokenType mysql_showKeysStatement_tokens_936[] = {
    TokenType::SHOW,
    TokenType::EXTENDED,
    TokenType::KEYS,
    TokenType::fromOrIn,
    TokenType::tableRef,
    TokenType::inDb,
    TokenType::whereClause
};

constexpr TokenType mysql_showEnginesStatement_tokens_937[] = {
    TokenType::SHOW,
    TokenType::STORAGE,
    TokenType::value,
    TokenType::ENGINES
};

constexpr TokenType mysql_showCountWarningsStatement_tokens_938[] = {
    TokenType::SHOW,
    TokenType::COUNT,
    TokenType::LPAREN,
    TokenType::STAR,
    TokenType::RPAREN,
    TokenType::WARNINGS
};

constexpr TokenType mysql_showCountErrorsStatement_tokens_939[] = {
    TokenType::SHOW,
    TokenType::COUNT,
    TokenType::LPAREN,
    TokenType::STAR,
    TokenType::RPAREN,
    TokenType::ERRORS
};

constexpr TokenType mysql_showWarningsStatement_tokens_940[] = {
    TokenType::SHOW,
    TokenType::WARNINGS,
    TokenType::limitClause
};

constexpr TokenType mysql_showErrorsStatement_tokens_941[] = {
    TokenType::SHOW,
    TokenType::ERRORS,
    TokenType::limitClause
};

constexpr TokenType mysql_showProfilesStatement_tokens_942[] = {
    TokenType::SHOW,
    TokenType::PROFILES
};

constexpr TokenType mysql_showProfileStatement_tokens_943[] = {
    TokenType::SHOW,
    TokenType::PROFILE,
    TokenType::profileDefinitions,
    TokenType::FOR,
    TokenType::QUERY,
    TokenType::NUMBER,
    TokenType::limitClause
};

constexpr TokenType mysql_showStatusStatement_tokens_944[] = {
    TokenType::SHOW,
    TokenType::optionType,
    TokenType::STATUS,
    TokenType::likeOrWhere
};

constexpr TokenType mysql_showProcessListStatement_tokens_945[] = {
    TokenType::SHOW,
    TokenType::FULL,
    TokenType::PROCESSLIST
};

constexpr TokenType mysql_showVariablesStatement_tokens_946[] = {
    TokenType::SHOW,
    TokenType::optionType,
    TokenType::VARIABLES,
    TokenType::likeOrWhere
};

constexpr TokenType mysql_showCharacterSetStatement_tokens_947[] = {
    TokenType::SHOW,
    TokenType::charset,
    TokenType::likeOrWhere
};

constexpr TokenType mysql_showCollationStatement_tokens_948[] = {
    TokenType::SHOW,
    TokenType::COLLATION,
    TokenType::likeOrWhere
};

constexpr TokenType mysql_showPrivilegesStatement_tokens_949[] = {
    TokenType::SHOW,
    TokenType::PRIVILEGES
};

constexpr TokenType mysql_showGrantsStatement_tokens_950[] = {
    TokenType::SHOW,
    TokenType::GRANTS,
    TokenType::FOR,
    TokenType::user,
    TokenType::USING,
    TokenType::userList
};

constexpr TokenType mysql_showMasterStatusStatement_tokens_951[] = {
    TokenType::SHOW,
    TokenType::MASTER,
    TokenType::STATUS
};

constexpr TokenType mysql_showReplicaStatusStatement_tokens_952[] = {
    TokenType::SHOW,
    TokenType::replica,
    TokenType::STATUS,
    TokenType::channel
};

constexpr TokenType mysql_showCommandType_tokens_953[] = {
    TokenType::FULL
};

constexpr TokenType mysql_showCommandType_tokens_954[] = {
    TokenType::EXTENDED,
    TokenType::FULL
};

constexpr TokenType mysql_engineOrAll_tokens_955[] = {
    TokenType::engineRef
};

constexpr TokenType mysql_engineOrAll_tokens_956[] = {
    TokenType::ALL
};

constexpr TokenType mysql_fromOrIn_tokens_957[] = {
    TokenType::FROM
};

constexpr TokenType mysql_fromOrIn_tokens_958[] = {
    TokenType::IN
};

constexpr TokenType mysql_inDb_tokens_959[] = {
    TokenType::fromOrIn,
    TokenType::identifier
};

constexpr TokenType mysql_profileDefinitions_tokens_960[] = {
    TokenType::profileDefinition,
    TokenType::COMMA,
    TokenType::profileDefinition
};

constexpr TokenType mysql_profileDefinition_tokens_961[] = {
    TokenType::BLOCK,
    TokenType::IO
};

constexpr TokenType mysql_profileDefinition_tokens_962[] = {
    TokenType::CONTEXT,
    TokenType::SWITCHES
};

constexpr TokenType mysql_profileDefinition_tokens_963[] = {
    TokenType::PAGE,
    TokenType::FAULTS
};

constexpr TokenType mysql_profileDefinition_tokens_964[] = {
    TokenType::ALL
};

constexpr TokenType mysql_profileDefinition_tokens_965[] = {
    TokenType::CPU
};

constexpr TokenType mysql_profileDefinition_tokens_966[] = {
    TokenType::IPC
};

constexpr TokenType mysql_profileDefinition_tokens_967[] = {
    TokenType::MEMORY
};

constexpr TokenType mysql_profileDefinition_tokens_968[] = {
    TokenType::SOURCE
};

constexpr TokenType mysql_profileDefinition_tokens_969[] = {
    TokenType::SWAPS
};

constexpr TokenType mysql_otherAdministrativeStatement_tokens_970[] = {
    TokenType::type,
    TokenType::BINLOG,
    TokenType::textLiteral
};

constexpr TokenType mysql_otherAdministrativeStatement_tokens_971[] = {
    TokenType::type,
    TokenType::CACHE,
    TokenType::INDEX,
    TokenType::keyCacheListOrParts,
    TokenType::IN,
    TokenType::identifier
};

constexpr TokenType mysql_otherAdministrativeStatement_tokens_972[] = {
    TokenType::type,
    TokenType::CACHE,
    TokenType::INDEX,
    TokenType::keyCacheListOrParts,
    TokenType::IN,
    TokenType::DEFAULT
};

constexpr TokenType mysql_otherAdministrativeStatement_tokens_973[] = {
    TokenType::type,
    TokenType::FLUSH,
    TokenType::noWriteToBinLog,
    TokenType::flushTables
};

constexpr TokenType mysql_otherAdministrativeStatement_tokens_974[] = {
    TokenType::type,
    TokenType::FLUSH,
    TokenType::noWriteToBinLog,
    TokenType::flushOption,
    TokenType::COMMA,
    TokenType::flushOption
};

constexpr TokenType mysql_otherAdministrativeStatement_tokens_975[] = {
    TokenType::type,
    TokenType::KILL,
    TokenType::CONNECTION,
    TokenType::expr
};

constexpr TokenType mysql_otherAdministrativeStatement_tokens_976[] = {
    TokenType::type,
    TokenType::KILL,
    TokenType::QUERY,
    TokenType::expr
};

constexpr TokenType mysql_otherAdministrativeStatement_tokens_977[] = {
    TokenType::type,
    TokenType::LOAD,
    TokenType::INDEX,
    TokenType::INTO,
    TokenType::CACHE,
    TokenType::preloadTail
};

constexpr TokenType mysql_otherAdministrativeStatement_tokens_978[] = {
    TokenType::type,
    TokenType::SHUTDOWN
};

constexpr TokenType mysql_keyCacheListOrParts_tokens_979[] = {
    TokenType::keyCacheList
};

constexpr TokenType mysql_keyCacheListOrParts_tokens_980[] = {
    TokenType::assignToKeycachePartition
};

constexpr TokenType mysql_keyCacheList_tokens_981[] = {
    TokenType::assignToKeycache,
    TokenType::COMMA,
    TokenType::assignToKeycache
};

constexpr TokenType mysql_assignToKeycache_tokens_982[] = {
    TokenType::tableRef,
    TokenType::cacheKeyList
};

constexpr TokenType mysql_assignToKeycachePartition_tokens_983[] = {
    TokenType::tableRef,
    TokenType::PARTITION,
    TokenType::LPAREN,
    TokenType::allOrPartitionNameList,
    TokenType::RPAREN,
    TokenType::cacheKeyList
};

constexpr TokenType mysql_cacheKeyList_tokens_984[] = {
    TokenType::keyOrIndex,
    TokenType::LPAREN,
    TokenType::keyUsageList,
    TokenType::RPAREN
};

constexpr TokenType mysql_keyUsageElement_tokens_985[] = {
    TokenType::identifier
};

constexpr TokenType mysql_keyUsageElement_tokens_986[] = {
    TokenType::PRIMARY
};

constexpr TokenType mysql_keyUsageList_tokens_987[] = {
    TokenType::keyUsageElement,
    TokenType::COMMA,
    TokenType::keyUsageElement
};

constexpr TokenType mysql_flushOption_tokens_988[] = {
    TokenType::option,
    TokenType::HOSTS
};

constexpr TokenType mysql_flushOption_tokens_989[] = {
    TokenType::option,
    TokenType::PRIVILEGES
};

constexpr TokenType mysql_flushOption_tokens_990[] = {
    TokenType::option,
    TokenType::STATUS
};

constexpr TokenType mysql_flushOption_tokens_991[] = {
    TokenType::option,
    TokenType::USER_RESOURCES
};

constexpr TokenType mysql_flushOption_tokens_992[] = {
    TokenType::logType,
    TokenType::option,
    TokenType::LOGS
};

constexpr TokenType mysql_flushOption_tokens_993[] = {
    TokenType::option,
    TokenType::RELAY,
    TokenType::LOGS,
    TokenType::channel
};

constexpr TokenType mysql_flushOption_tokens_994[] = {
    TokenType::option,
    TokenType::OPTIMIZER_COSTS
};

constexpr TokenType mysql_logType_tokens_995[] = {
    TokenType::BINARY
};

constexpr TokenType mysql_logType_tokens_996[] = {
    TokenType::ENGINE
};

constexpr TokenType mysql_logType_tokens_997[] = {
    TokenType::ERROR
};

constexpr TokenType mysql_logType_tokens_998[] = {
    TokenType::GENERAL
};

constexpr TokenType mysql_logType_tokens_999[] = {
    TokenType::SLOW
};

constexpr TokenType mysql_flushTables_tokens_1000[] = {
    TokenType::TABLES,
    TokenType::WITH,
    TokenType::READ,
    TokenType::LOCK
};

constexpr TokenType mysql_flushTables_tokens_1001[] = {
    TokenType::TABLES,
    TokenType::identifierList,
    TokenType::flushTablesOptions
};

constexpr TokenType mysql_flushTables_tokens_1002[] = {
    TokenType::TABLE,
    TokenType::WITH,
    TokenType::READ,
    TokenType::LOCK
};

constexpr TokenType mysql_flushTables_tokens_1003[] = {
    TokenType::TABLE,
    TokenType::identifierList,
    TokenType::flushTablesOptions
};

constexpr TokenType mysql_flushTablesOptions_tokens_1004[] = {
    TokenType::FOR,
    TokenType::EXPORT
};

constexpr TokenType mysql_flushTablesOptions_tokens_1005[] = {
    TokenType::WITH,
    TokenType::READ,
    TokenType::LOCK
};

constexpr TokenType mysql_preloadTail_tokens_1006[] = {
    TokenType::tableRef,
    TokenType::adminPartition,
    TokenType::cacheKeyList,
    TokenType::IGNORE,
    TokenType::LEAVES
};

constexpr TokenType mysql_preloadTail_tokens_1007[] = {
    TokenType::preloadList
};

constexpr TokenType mysql_preloadList_tokens_1008[] = {
    TokenType::preloadKeys,
    TokenType::COMMA,
    TokenType::preloadKeys
};

constexpr TokenType mysql_preloadKeys_tokens_1009[] = {
    TokenType::tableRef,
    TokenType::cacheKeyList,
    TokenType::IGNORE,
    TokenType::LEAVES
};

constexpr TokenType mysql_adminPartition_tokens_1010[] = {
    TokenType::PARTITION,
    TokenType::LPAREN,
    TokenType::allOrPartitionNameList,
    TokenType::RPAREN
};

constexpr TokenType mysql_resourceGroupManagement_tokens_1011[] = {
    TokenType::createResourceGroup
};

constexpr TokenType mysql_resourceGroupManagement_tokens_1012[] = {
    TokenType::alterResourceGroup
};

constexpr TokenType mysql_resourceGroupManagement_tokens_1013[] = {
    TokenType::setResourceGroup
};

constexpr TokenType mysql_resourceGroupManagement_tokens_1014[] = {
    TokenType::dropResourceGroup
};

constexpr TokenType mysql_resourceGroupVcpuList_tokens_1015[] = {
    TokenType::VCPU,
    TokenType::equal,
    TokenType::vcpuNumOrRange,
    TokenType::COMMA,
    TokenType::vcpuNumOrRange
};

constexpr TokenType mysql_vcpuNumOrRange_tokens_1016[] = {
    TokenType::NUMBER,
    TokenType::MINUS,
    TokenType::NUMBER
};

constexpr TokenType mysql_resourceGroupPriority_tokens_1017[] = {
    TokenType::THREAD_PRIORITY,
    TokenType::equal,
    TokenType::NUMBER
};

constexpr TokenType mysql_resourceGroupEnableDisable_tokens_1018[] = {
    TokenType::ENABLE
};

constexpr TokenType mysql_resourceGroupEnableDisable_tokens_1019[] = {
    TokenType::DISABLE
};

constexpr TokenType mysql_alterResourceGroup_tokens_1020[] = {
    TokenType::ALTER,
    TokenType::RESOURCE,
    TokenType::GROUP,
    TokenType::resourceGroupRef,
    TokenType::resourceGroupVcpuList,
    TokenType::resourceGroupPriority,
    TokenType::resourceGroupEnableDisable,
    TokenType::FORCE
};

constexpr TokenType mysql_setResourceGroup_tokens_1021[] = {
    TokenType::SET,
    TokenType::RESOURCE,
    TokenType::GROUP,
    TokenType::identifier,
    TokenType::FOR,
    TokenType::threadIdList
};

constexpr TokenType mysql_threadIdList_tokens_1022[] = {
    TokenType::real_ulong_number,
    TokenType::COMMA,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_utilityStatement_tokens_1023[] = {
    TokenType::describeStatement
};

constexpr TokenType mysql_utilityStatement_tokens_1024[] = {
    TokenType::explainStatement
};

constexpr TokenType mysql_utilityStatement_tokens_1025[] = {
    TokenType::helpCommand
};

constexpr TokenType mysql_utilityStatement_tokens_1026[] = {
    TokenType::useCommand
};

constexpr TokenType mysql_utilityStatement_tokens_1027[] = {
    TokenType::this,
    TokenType::isServerVersionGe80011,
    TokenType::restartServer
};

constexpr TokenType mysql_describeStatement_tokens_1028[] = {
    TokenType::EXPLAIN,
    TokenType::tableRef,
    TokenType::textString
};

constexpr TokenType mysql_describeStatement_tokens_1029[] = {
    TokenType::EXPLAIN,
    TokenType::tableRef,
    TokenType::columnRef
};

constexpr TokenType mysql_describeStatement_tokens_1030[] = {
    TokenType::DESCRIBE,
    TokenType::tableRef,
    TokenType::textString
};

constexpr TokenType mysql_describeStatement_tokens_1031[] = {
    TokenType::DESCRIBE,
    TokenType::tableRef,
    TokenType::columnRef
};

constexpr TokenType mysql_describeStatement_tokens_1032[] = {
    TokenType::DESC,
    TokenType::tableRef,
    TokenType::textString
};

constexpr TokenType mysql_describeStatement_tokens_1033[] = {
    TokenType::DESC,
    TokenType::tableRef,
    TokenType::columnRef
};

constexpr TokenType mysql_explainStatement_tokens_1034[] = {
    TokenType::EXPLAIN,
    TokenType::explainOptions,
    TokenType::this,
    TokenType::isServerVersionGe80032,
    TokenType::FOR,
    TokenType::DATABASE,
    TokenType::textOrIdentifier,
    TokenType::explainableStatement
};

constexpr TokenType mysql_explainStatement_tokens_1035[] = {
    TokenType::DESCRIBE,
    TokenType::explainOptions,
    TokenType::this,
    TokenType::isServerVersionGe80032,
    TokenType::FOR,
    TokenType::DATABASE,
    TokenType::textOrIdentifier,
    TokenType::explainableStatement
};

constexpr TokenType mysql_explainStatement_tokens_1036[] = {
    TokenType::DESC,
    TokenType::explainOptions,
    TokenType::this,
    TokenType::isServerVersionGe80032,
    TokenType::FOR,
    TokenType::DATABASE,
    TokenType::textOrIdentifier,
    TokenType::explainableStatement
};

constexpr TokenType mysql_explainOptions_tokens_1037[] = {
    TokenType::FORMAT,
    TokenType::EQ,
    TokenType::textOrIdentifier,
    TokenType::this,
    TokenType::isServerVersionGe80032,
    TokenType::explainInto
};

constexpr TokenType mysql_explainOptions_tokens_1038[] = {
    TokenType::this,
    TokenType::isServerVersionLt80012,
    TokenType::EXTENDED
};

constexpr TokenType mysql_explainOptions_tokens_1039[] = {
    TokenType::this,
    TokenType::isServerVersionGe80018,
    TokenType::ANALYZE
};

constexpr TokenType mysql_explainOptions_tokens_1040[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::ANALYZE,
    TokenType::FORMAT,
    TokenType::EQ,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_explainableStatement_tokens_1041[] = {
    TokenType::selectStatement
};

constexpr TokenType mysql_explainableStatement_tokens_1042[] = {
    TokenType::deleteStatement
};

constexpr TokenType mysql_explainableStatement_tokens_1043[] = {
    TokenType::insertStatement
};

constexpr TokenType mysql_explainableStatement_tokens_1044[] = {
    TokenType::replaceStatement
};

constexpr TokenType mysql_explainableStatement_tokens_1045[] = {
    TokenType::updateStatement
};

constexpr TokenType mysql_explainableStatement_tokens_1046[] = {
    TokenType::FOR,
    TokenType::CONNECTION,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_explainInto_tokens_1047[] = {
    TokenType::INTO,
    TokenType::AT_SIGN,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_helpCommand_tokens_1048[] = {
    TokenType::HELP,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_useCommand_tokens_1049[] = {
    TokenType::USE,
    TokenType::schemaRef
};

constexpr TokenType mysql_restartServer_tokens_1050[] = {
    TokenType::STAR
};

constexpr TokenType mysql_boolPri_tokens_1051[] = {
    TokenType::predicate,
    TokenType::primaryExprPredicate
};

constexpr TokenType mysql_boolPri_tokens_1052[] = {
    TokenType::boolPri,
    TokenType::IS,
    TokenType::notRule,
    TokenType::NULL_KW,
    TokenType::primaryExprIsNull
};

constexpr TokenType mysql_boolPri_tokens_1053[] = {
    TokenType::boolPri,
    TokenType::compOp,
    TokenType::predicate,
    TokenType::primaryExprCompare
};

constexpr TokenType mysql_boolPri_tokens_1054[] = {
    TokenType::boolPri,
    TokenType::compOp,
    TokenType::ALL,
    TokenType::subquery,
    TokenType::primaryExprAllAny
};

constexpr TokenType mysql_boolPri_tokens_1055[] = {
    TokenType::boolPri,
    TokenType::compOp,
    TokenType::ANY,
    TokenType::subquery,
    TokenType::primaryExprAllAny
};

constexpr TokenType mysql_compOp_tokens_1056[] = {
    TokenType::EQ
};

constexpr TokenType mysql_compOp_tokens_1057[] = {
    TokenType::NULL_SAFE_EQUAL
};

constexpr TokenType mysql_compOp_tokens_1058[] = {
    TokenType::GTE
};

constexpr TokenType mysql_compOp_tokens_1059[] = {
    TokenType::GT
};

constexpr TokenType mysql_compOp_tokens_1060[] = {
    TokenType::LTE
};

constexpr TokenType mysql_compOp_tokens_1061[] = {
    TokenType::LT
};

constexpr TokenType mysql_compOp_tokens_1062[] = {
    TokenType::NEQ
};

constexpr TokenType mysql_predicate_tokens_1063[] = {
    TokenType::bitExpr,
    TokenType::notRule,
    TokenType::predicateOperations
};

constexpr TokenType mysql_predicate_tokens_1064[] = {
    TokenType::bitExpr,
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::MEMBER,
    TokenType::OF,
    TokenType::simpleExprWithParentheses
};

constexpr TokenType mysql_predicate_tokens_1065[] = {
    TokenType::bitExpr,
    TokenType::SOUNDS,
    TokenType::LIKE,
    TokenType::bitExpr
};

constexpr TokenType mysql_predicateOperations_tokens_1066[] = {
    TokenType::IN,
    TokenType::subquery,
    TokenType::predicateExprIn
};

constexpr TokenType mysql_predicateOperations_tokens_1067[] = {
    TokenType::IN,
    TokenType::LPAREN,
    TokenType::exprList,
    TokenType::RPAREN,
    TokenType::predicateExprIn
};

constexpr TokenType mysql_predicateOperations_tokens_1068[] = {
    TokenType::BETWEEN,
    TokenType::bitExpr,
    TokenType::AND,
    TokenType::predicate,
    TokenType::predicateExprBetween
};

constexpr TokenType mysql_predicateOperations_tokens_1069[] = {
    TokenType::LIKE,
    TokenType::simpleExpr,
    TokenType::ESCAPE,
    TokenType::simpleExpr,
    TokenType::predicateExprLike
};

constexpr TokenType mysql_predicateOperations_tokens_1070[] = {
    TokenType::REGEXP,
    TokenType::bitExpr,
    TokenType::predicateExprRegex
};

constexpr TokenType mysql_arrayCast_tokens_1071[] = {
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::ARRAY
};

constexpr TokenType mysql_jsonOperator_tokens_1072[] = {
    TokenType::JSON_SEPARATOR,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_jsonOperator_tokens_1073[] = {
    TokenType::JSON_UNQUOTED_SEPARATOR,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_groupingOperation_tokens_1074[] = {
    TokenType::GROUPING,
    TokenType::LPAREN,
    TokenType::exprList,
    TokenType::RPAREN
};

constexpr TokenType mysql_windowFunctionCall_tokens_1075[] = {
    TokenType::ROW_NUMBER,
    TokenType::parentheses,
    TokenType::windowingClause
};

constexpr TokenType mysql_windowFunctionCall_tokens_1076[] = {
    TokenType::RANK,
    TokenType::parentheses,
    TokenType::windowingClause
};

constexpr TokenType mysql_windowFunctionCall_tokens_1077[] = {
    TokenType::DENSE_RANK,
    TokenType::parentheses,
    TokenType::windowingClause
};

constexpr TokenType mysql_windowFunctionCall_tokens_1078[] = {
    TokenType::CUME_DIST,
    TokenType::parentheses,
    TokenType::windowingClause
};

constexpr TokenType mysql_windowFunctionCall_tokens_1079[] = {
    TokenType::PERCENT_RANK,
    TokenType::parentheses,
    TokenType::windowingClause
};

constexpr TokenType mysql_windowFunctionCall_tokens_1080[] = {
    TokenType::NTILE,
    TokenType::LPAREN,
    TokenType::stableInteger,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_windowFunctionCall_tokens_1081[] = {
    TokenType::NTILE,
    TokenType::this,
    TokenType::isServerVersionLt80024,
    TokenType::simpleExprWithParentheses,
    TokenType::windowingClause
};

constexpr TokenType mysql_windowFunctionCall_tokens_1082[] = {
    TokenType::LEAD,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::leadLagInfo,
    TokenType::RPAREN,
    TokenType::nullTreatment,
    TokenType::windowingClause
};

constexpr TokenType mysql_windowFunctionCall_tokens_1083[] = {
    TokenType::LAG,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::leadLagInfo,
    TokenType::RPAREN,
    TokenType::nullTreatment,
    TokenType::windowingClause
};

constexpr TokenType mysql_windowFunctionCall_tokens_1084[] = {
    TokenType::FIRST_VALUE,
    TokenType::exprWithParentheses,
    TokenType::nullTreatment,
    TokenType::windowingClause
};

constexpr TokenType mysql_windowFunctionCall_tokens_1085[] = {
    TokenType::LAST_VALUE,
    TokenType::exprWithParentheses,
    TokenType::nullTreatment,
    TokenType::windowingClause
};

constexpr TokenType mysql_windowFunctionCall_tokens_1086[] = {
    TokenType::NTH_VALUE,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::simpleExpr,
    TokenType::RPAREN,
    TokenType::FROM,
    TokenType::FIRST,
    TokenType::nullTreatment,
    TokenType::windowingClause
};

constexpr TokenType mysql_windowFunctionCall_tokens_1087[] = {
    TokenType::NTH_VALUE,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::simpleExpr,
    TokenType::RPAREN,
    TokenType::FROM,
    TokenType::LAST,
    TokenType::nullTreatment,
    TokenType::windowingClause
};

constexpr TokenType mysql_samplingMethod_tokens_1088[] = {
    TokenType::SYSTEM
};

constexpr TokenType mysql_samplingMethod_tokens_1089[] = {
    TokenType::BERNOULLI
};

constexpr TokenType mysql_samplingPercentage_tokens_1090[] = {
    TokenType::ulonglongNumber
};

constexpr TokenType mysql_samplingPercentage_tokens_1091[] = {
    TokenType::AT_SIGN,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_samplingPercentage_tokens_1092[] = {
    TokenType::PARAM_MARKER
};

constexpr TokenType mysql_tablesampleClause_tokens_1093[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::TABLESAMPLE,
    TokenType::samplingMethod,
    TokenType::LPAREN,
    TokenType::samplingPercentage,
    TokenType::RPAREN
};

constexpr TokenType mysql_windowingClause_tokens_1094[] = {
    TokenType::OVER,
    TokenType::windowName
};

constexpr TokenType mysql_windowingClause_tokens_1095[] = {
    TokenType::OVER,
    TokenType::windowSpec
};

constexpr TokenType mysql_leadLagInfo_tokens_1096[] = {
    TokenType::COMMA,
    TokenType::ulonglongNumber,
    TokenType::COMMA,
    TokenType::expr
};

constexpr TokenType mysql_leadLagInfo_tokens_1097[] = {
    TokenType::COMMA,
    TokenType::PARAM_MARKER,
    TokenType::COMMA,
    TokenType::expr
};

constexpr TokenType mysql_leadLagInfo_tokens_1098[] = {
    TokenType::COMMA,
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::stableInteger,
    TokenType::COMMA,
    TokenType::expr
};

constexpr TokenType mysql_stableInteger_tokens_1099[] = {
    TokenType::int64Literal
};

constexpr TokenType mysql_stableInteger_tokens_1100[] = {
    TokenType::paramOrVar
};

constexpr TokenType mysql_paramOrVar_tokens_1101[] = {
    TokenType::PARAM_MARKER
};

constexpr TokenType mysql_paramOrVar_tokens_1102[] = {
    TokenType::identifier
};

constexpr TokenType mysql_paramOrVar_tokens_1103[] = {
    TokenType::AT_SIGN,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_nullTreatment_tokens_1104[] = {
    TokenType::RESPECT,
    TokenType::NULLS
};

constexpr TokenType mysql_nullTreatment_tokens_1105[] = {
    TokenType::IGNORE,
    TokenType::NULLS
};

constexpr TokenType mysql_jsonFunction_tokens_1106[] = {
    TokenType::JSON_ARRAYAGG,
    TokenType::LPAREN,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_jsonFunction_tokens_1107[] = {
    TokenType::JSON_OBJECTAGG,
    TokenType::LPAREN,
    TokenType::inSumExpr,
    TokenType::COMMA,
    TokenType::inSumExpr,
    TokenType::RPAREN,
    TokenType::windowingClause
};

constexpr TokenType mysql_identListArg_tokens_1108[] = {
    TokenType::identList
};

constexpr TokenType mysql_identListArg_tokens_1109[] = {
    TokenType::LPAREN,
    TokenType::identList,
    TokenType::RPAREN
};

constexpr TokenType mysql_identList_tokens_1110[] = {
    TokenType::simpleIdentifier,
    TokenType::COMMA,
    TokenType::simpleIdentifier
};

constexpr TokenType mysql_fulltextOptions_tokens_1111[] = {
    TokenType::IN,
    TokenType::BOOLEAN,
    TokenType::MODE
};

constexpr TokenType mysql_fulltextOptions_tokens_1112[] = {
    TokenType::IN,
    TokenType::NATURAL,
    TokenType::LANGUAGE,
    TokenType::MODE,
    TokenType::WITH,
    TokenType::QUERY,
    TokenType::EXPANSION
};

constexpr TokenType mysql_fulltextOptions_tokens_1113[] = {
    TokenType::WITH,
    TokenType::QUERY,
    TokenType::EXPANSION
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1114[] = {
    TokenType::CHAR,
    TokenType::LPAREN,
    TokenType::exprList,
    TokenType::USING,
    TokenType::charsetName,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1115[] = {
    TokenType::CURRENT_USER,
    TokenType::parentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1116[] = {
    TokenType::DATE,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1117[] = {
    TokenType::DAY,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1118[] = {
    TokenType::HOUR,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1119[] = {
    TokenType::INSERT,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1120[] = {
    TokenType::INTERVAL,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1121[] = {
    TokenType::JSON_VALUE,
    TokenType::LPAREN,
    TokenType::simpleExpr,
    TokenType::COMMA,
    TokenType::textLiteral,
    TokenType::returningType,
    TokenType::onEmptyOrError,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1122[] = {
    TokenType::LEFT,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1123[] = {
    TokenType::MINUTE,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1124[] = {
    TokenType::MONTH,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1125[] = {
    TokenType::RIGHT,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1126[] = {
    TokenType::SECOND,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1127[] = {
    TokenType::TIME,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1128[] = {
    TokenType::TIMESTAMP,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1129[] = {
    TokenType::trimFunction
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1130[] = {
    TokenType::userFunction
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1131[] = {
    TokenType::VALUES,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1132[] = {
    TokenType::YEAR,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1133[] = {
    TokenType::ADDDATE,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1134[] = {
    TokenType::ADDDATE,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::INTERVAL,
    TokenType::expr,
    TokenType::interval,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1135[] = {
    TokenType::SUBDATE,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1136[] = {
    TokenType::SUBDATE,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::INTERVAL,
    TokenType::expr,
    TokenType::interval,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1137[] = {
    TokenType::CURDATE,
    TokenType::parentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1138[] = {
    TokenType::CURTIME,
    TokenType::timeFunctionParameters
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1139[] = {
    TokenType::DATE_ADD,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::INTERVAL,
    TokenType::expr,
    TokenType::interval,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1140[] = {
    TokenType::DATE_SUB,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::INTERVAL,
    TokenType::expr,
    TokenType::interval,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1141[] = {
    TokenType::EXTRACT,
    TokenType::LPAREN,
    TokenType::interval,
    TokenType::FROM,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1142[] = {
    TokenType::GET_FORMAT,
    TokenType::LPAREN,
    TokenType::dateTimeTtype,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1143[] = {
    TokenType::this,
    TokenType::isServerVersionGe80032,
    TokenType::LOG,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1144[] = {
    TokenType::NOW,
    TokenType::timeFunctionParameters
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1145[] = {
    TokenType::POSITION,
    TokenType::LPAREN,
    TokenType::bitExpr,
    TokenType::IN,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1146[] = {
    TokenType::substringFunction
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1147[] = {
    TokenType::SYSDATE,
    TokenType::timeFunctionParameters
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1148[] = {
    TokenType::TIMESTAMPADD,
    TokenType::LPAREN,
    TokenType::intervalTimeStamp,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1149[] = {
    TokenType::TIMESTAMPDIFF,
    TokenType::LPAREN,
    TokenType::intervalTimeStamp,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1150[] = {
    TokenType::UTC_DATE,
    TokenType::parentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1151[] = {
    TokenType::UTC_TIME,
    TokenType::timeFunctionParameters
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1152[] = {
    TokenType::UTC_TIMESTAMP,
    TokenType::timeFunctionParameters
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1153[] = {
    TokenType::ASCII,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1154[] = {
    TokenType::CHARSET,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1155[] = {
    TokenType::COALESCE,
    TokenType::exprListWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1156[] = {
    TokenType::COLLATION,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1157[] = {
    TokenType::DATABASE,
    TokenType::parentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1158[] = {
    TokenType::IF,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1159[] = {
    TokenType::FORMAT,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1160[] = {
    TokenType::MICROSECOND,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1161[] = {
    TokenType::MOD,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1162[] = {
    TokenType::this,
    TokenType::isServerVersionLt80011,
    TokenType::PASSWORD,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1163[] = {
    TokenType::QUARTER,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1164[] = {
    TokenType::REPEAT,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1165[] = {
    TokenType::REPLACE,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1166[] = {
    TokenType::REVERSE,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1167[] = {
    TokenType::ROW_COUNT,
    TokenType::parentheses
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1168[] = {
    TokenType::TRUNCATE,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1169[] = {
    TokenType::WEEK,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1170[] = {
    TokenType::WEIGHT_STRING,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::AS,
    TokenType::CHAR,
    TokenType::wsNumCodepoints,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1171[] = {
    TokenType::WEIGHT_STRING,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::AS,
    TokenType::BINARY,
    TokenType::wsNumCodepoints,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1172[] = {
    TokenType::WEIGHT_STRING,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::ulong_number,
    TokenType::COMMA,
    TokenType::ulong_number,
    TokenType::COMMA,
    TokenType::ulong_number,
    TokenType::RPAREN
};

constexpr TokenType mysql_runtimeFunctionCall_tokens_1173[] = {
    TokenType::geometryFunction
};

constexpr TokenType mysql_returningType_tokens_1174[] = {
    TokenType::RETURNING,
    TokenType::castType
};

constexpr TokenType mysql_geometryFunction_tokens_1175[] = {
    TokenType::GEOMETRYCOLLECTION,
    TokenType::LPAREN,
    TokenType::exprList,
    TokenType::RPAREN
};

constexpr TokenType mysql_geometryFunction_tokens_1176[] = {
    TokenType::LINESTRING,
    TokenType::exprListWithParentheses
};

constexpr TokenType mysql_geometryFunction_tokens_1177[] = {
    TokenType::STAR,
    TokenType::exprListWithParentheses
};

constexpr TokenType mysql_geometryFunction_tokens_1178[] = {
    TokenType::STAR,
    TokenType::exprListWithParentheses
};

constexpr TokenType mysql_geometryFunction_tokens_1179[] = {
    TokenType::STAR,
    TokenType::exprListWithParentheses
};

constexpr TokenType mysql_geometryFunction_tokens_1180[] = {
    TokenType::POINT,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_geometryFunction_tokens_1181[] = {
    TokenType::POLYGON,
    TokenType::exprListWithParentheses
};

constexpr TokenType mysql_timeFunctionParameters_tokens_1182[] = {
    TokenType::LPAREN,
    TokenType::fractionalPrecision,
    TokenType::RPAREN
};

constexpr TokenType mysql_fractionalPrecision_tokens_1183[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_weightStringLevels_tokens_1184[] = {
    TokenType::LEVEL,
    TokenType::real_ulong_number,
    TokenType::MINUS,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_weightStringLevels_tokens_1185[] = {
    TokenType::LEVEL,
    TokenType::weightStringLevelListItem,
    TokenType::COMMA,
    TokenType::weightStringLevelListItem
};

constexpr TokenType mysql_weightStringLevelListItem_tokens_1186[] = {
    TokenType::real_ulong_number,
    TokenType::ASC,
    TokenType::REVERSE
};

constexpr TokenType mysql_weightStringLevelListItem_tokens_1187[] = {
    TokenType::real_ulong_number,
    TokenType::DESC,
    TokenType::REVERSE
};

constexpr TokenType mysql_weightStringLevelListItem_tokens_1188[] = {
    TokenType::real_ulong_number,
    TokenType::REVERSE
};

constexpr TokenType mysql_dateTimeTtype_tokens_1189[] = {
    TokenType::DATE
};

constexpr TokenType mysql_dateTimeTtype_tokens_1190[] = {
    TokenType::TIME
};

constexpr TokenType mysql_dateTimeTtype_tokens_1191[] = {
    TokenType::DATETIME
};

constexpr TokenType mysql_dateTimeTtype_tokens_1192[] = {
    TokenType::TIMESTAMP
};

constexpr TokenType mysql_trimFunction_tokens_1193[] = {
    TokenType::TRIM,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::FROM,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_trimFunction_tokens_1194[] = {
    TokenType::TRIM,
    TokenType::LPAREN,
    TokenType::LEADING,
    TokenType::expr,
    TokenType::FROM,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_trimFunction_tokens_1195[] = {
    TokenType::TRIM,
    TokenType::LPAREN,
    TokenType::TRAILING,
    TokenType::expr,
    TokenType::FROM,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_trimFunction_tokens_1196[] = {
    TokenType::TRIM,
    TokenType::LPAREN,
    TokenType::BOTH,
    TokenType::expr,
    TokenType::FROM,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_substringFunction_tokens_1197[] = {
    TokenType::SUBSTRING,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::COMMA,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_substringFunction_tokens_1198[] = {
    TokenType::SUBSTRING,
    TokenType::LPAREN,
    TokenType::expr,
    TokenType::FROM,
    TokenType::expr,
    TokenType::FOR,
    TokenType::expr,
    TokenType::RPAREN
};

constexpr TokenType mysql_functionCall_tokens_1199[] = {
    TokenType::pureIdentifier,
    TokenType::LPAREN,
    TokenType::udfExprList,
    TokenType::RPAREN
};

constexpr TokenType mysql_functionCall_tokens_1200[] = {
    TokenType::qualifiedIdentifier,
    TokenType::LPAREN,
    TokenType::exprList,
    TokenType::RPAREN
};

constexpr TokenType mysql_userVariable_tokens_1201[] = {
    TokenType::AT_SIGN,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_userVariable_tokens_1202[] = {
    TokenType::AT_TEXT_SUFFIX
};

constexpr TokenType mysql_rvalueSystemOrUserVariable_tokens_1203[] = {
    TokenType::userVariable
};

constexpr TokenType mysql_rvalueSystemOrUserVariable_tokens_1204[] = {
    TokenType::AT_AT_SIGN,
    TokenType::rvalueSystemVariableType,
    TokenType::rvalueSystemVariable
};

constexpr TokenType mysql_lvalueVariable_tokens_1205[] = {
    TokenType::identifier,
    TokenType::dotIdentifier
};

constexpr TokenType mysql_lvalueVariable_tokens_1206[] = {
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::lValueIdentifier,
    TokenType::dotIdentifier
};

constexpr TokenType mysql_lvalueVariable_tokens_1207[] = {
    TokenType::DEFAULT,
    TokenType::dotIdentifier
};

constexpr TokenType mysql_rvalueSystemVariable_tokens_1208[] = {
    TokenType::textOrIdentifier,
    TokenType::dotIdentifier
};

constexpr TokenType mysql_castType_tokens_1209[] = {
    TokenType::BINARY,
    TokenType::fieldLength
};

constexpr TokenType mysql_castType_tokens_1210[] = {
    TokenType::CHAR,
    TokenType::fieldLength,
    TokenType::charsetWithOptBinary
};

constexpr TokenType mysql_castType_tokens_1211[] = {
    TokenType::nchar,
    TokenType::fieldLength
};

constexpr TokenType mysql_castType_tokens_1212[] = {
    TokenType::SIGNED,
    TokenType::INT
};

constexpr TokenType mysql_castType_tokens_1213[] = {
    TokenType::UNSIGNED,
    TokenType::INT
};

constexpr TokenType mysql_castType_tokens_1214[] = {
    TokenType::DATE
};

constexpr TokenType mysql_castType_tokens_1215[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::YEAR
};

constexpr TokenType mysql_castType_tokens_1216[] = {
    TokenType::TIME,
    TokenType::typeDatetimePrecision
};

constexpr TokenType mysql_castType_tokens_1217[] = {
    TokenType::DATETIME,
    TokenType::typeDatetimePrecision
};

constexpr TokenType mysql_castType_tokens_1218[] = {
    TokenType::DECIMAL,
    TokenType::floatOptions
};

constexpr TokenType mysql_castType_tokens_1219[] = {
    TokenType::JSON
};

constexpr TokenType mysql_castType_tokens_1220[] = {
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::realType
};

constexpr TokenType mysql_castType_tokens_1221[] = {
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::FLOAT,
    TokenType::standardFloatOptions
};

constexpr TokenType mysql_castType_tokens_1222[] = {
    TokenType::this,
    TokenType::isServerVersionGe80027,
    TokenType::POINT
};

constexpr TokenType mysql_castType_tokens_1223[] = {
    TokenType::this,
    TokenType::isServerVersionGe80027,
    TokenType::LINESTRING
};

constexpr TokenType mysql_castType_tokens_1224[] = {
    TokenType::this,
    TokenType::isServerVersionGe80027,
    TokenType::POLYGON
};

constexpr TokenType mysql_castType_tokens_1225[] = {
    TokenType::this,
    TokenType::isServerVersionGe80027,
    TokenType::STAR
};

constexpr TokenType mysql_castType_tokens_1226[] = {
    TokenType::this,
    TokenType::isServerVersionGe80027,
    TokenType::STAR
};

constexpr TokenType mysql_castType_tokens_1227[] = {
    TokenType::this,
    TokenType::isServerVersionGe80027,
    TokenType::STAR
};

constexpr TokenType mysql_castType_tokens_1228[] = {
    TokenType::this,
    TokenType::isServerVersionGe80027,
    TokenType::GEOMETRYCOLLECTION
};

constexpr TokenType mysql_charset_tokens_1229[] = {
    TokenType::CHAR,
    TokenType::SET
};

constexpr TokenType mysql_charset_tokens_1230[] = {
    TokenType::CHARSET
};

constexpr TokenType mysql_notRule_tokens_1231[] = {
    TokenType::NOT
};

constexpr TokenType mysql_notRule_tokens_1232[] = {
    TokenType::NOT2
};

constexpr TokenType mysql_not2Rule_tokens_1233[] = {
    TokenType::NOT
};

constexpr TokenType mysql_not2Rule_tokens_1234[] = {
    TokenType::NOT2
};

constexpr TokenType mysql_interval_tokens_1235[] = {
    TokenType::intervalTimeStamp
};

constexpr TokenType mysql_interval_tokens_1236[] = {
    TokenType::SECOND_MICROSECOND
};

constexpr TokenType mysql_interval_tokens_1237[] = {
    TokenType::MINUTE_MICROSECOND
};

constexpr TokenType mysql_interval_tokens_1238[] = {
    TokenType::MINUTE_SECOND
};

constexpr TokenType mysql_interval_tokens_1239[] = {
    TokenType::HOUR_MICROSECOND
};

constexpr TokenType mysql_interval_tokens_1240[] = {
    TokenType::HOUR_SECOND
};

constexpr TokenType mysql_interval_tokens_1241[] = {
    TokenType::HOUR_MINUTE
};

constexpr TokenType mysql_interval_tokens_1242[] = {
    TokenType::DAY_MICROSECOND
};

constexpr TokenType mysql_interval_tokens_1243[] = {
    TokenType::DAY_SECOND
};

constexpr TokenType mysql_interval_tokens_1244[] = {
    TokenType::DAY_MINUTE
};

constexpr TokenType mysql_interval_tokens_1245[] = {
    TokenType::DAY_HOUR
};

constexpr TokenType mysql_interval_tokens_1246[] = {
    TokenType::YEAR_MONTH
};

constexpr TokenType mysql_intervalTimeStamp_tokens_1247[] = {
    TokenType::MICROSECOND
};

constexpr TokenType mysql_intervalTimeStamp_tokens_1248[] = {
    TokenType::SECOND
};

constexpr TokenType mysql_intervalTimeStamp_tokens_1249[] = {
    TokenType::MINUTE
};

constexpr TokenType mysql_intervalTimeStamp_tokens_1250[] = {
    TokenType::HOUR
};

constexpr TokenType mysql_intervalTimeStamp_tokens_1251[] = {
    TokenType::DAY
};

constexpr TokenType mysql_intervalTimeStamp_tokens_1252[] = {
    TokenType::WEEK
};

constexpr TokenType mysql_intervalTimeStamp_tokens_1253[] = {
    TokenType::MONTH
};

constexpr TokenType mysql_intervalTimeStamp_tokens_1254[] = {
    TokenType::QUARTER
};

constexpr TokenType mysql_intervalTimeStamp_tokens_1255[] = {
    TokenType::YEAR
};

constexpr TokenType mysql_orderList_tokens_1256[] = {
    TokenType::orderExpression,
    TokenType::COMMA,
    TokenType::orderExpression
};

constexpr TokenType mysql_groupList_tokens_1257[] = {
    TokenType::groupingExpression,
    TokenType::COMMA,
    TokenType::groupingExpression
};

constexpr TokenType mysql_channel_tokens_1258[] = {
    TokenType::FOR,
    TokenType::CHANNEL,
    TokenType::textStringNoLinebreak
};

constexpr TokenType mysql_compoundStatement_tokens_1259[] = {
    TokenType::simpleStatement
};

constexpr TokenType mysql_compoundStatement_tokens_1260[] = {
    TokenType::returnStatement
};

constexpr TokenType mysql_compoundStatement_tokens_1261[] = {
    TokenType::ifStatement
};

constexpr TokenType mysql_compoundStatement_tokens_1262[] = {
    TokenType::caseStatement
};

constexpr TokenType mysql_compoundStatement_tokens_1263[] = {
    TokenType::labeledBlock
};

constexpr TokenType mysql_compoundStatement_tokens_1264[] = {
    TokenType::unlabeledBlock
};

constexpr TokenType mysql_compoundStatement_tokens_1265[] = {
    TokenType::labeledControl
};

constexpr TokenType mysql_compoundStatement_tokens_1266[] = {
    TokenType::unlabeledControl
};

constexpr TokenType mysql_compoundStatement_tokens_1267[] = {
    TokenType::leaveStatement
};

constexpr TokenType mysql_compoundStatement_tokens_1268[] = {
    TokenType::iterateStatement
};

constexpr TokenType mysql_compoundStatement_tokens_1269[] = {
    TokenType::cursorOpen
};

constexpr TokenType mysql_compoundStatement_tokens_1270[] = {
    TokenType::cursorFetch
};

constexpr TokenType mysql_compoundStatement_tokens_1271[] = {
    TokenType::cursorClose
};

constexpr TokenType mysql_returnStatement_tokens_1272[] = {
    TokenType::RETURN,
    TokenType::expr
};

constexpr TokenType mysql_ifStatement_tokens_1273[] = {
    TokenType::IF,
    TokenType::ifBody,
    TokenType::END,
    TokenType::IF
};

constexpr TokenType mysql_ifBody_tokens_1274[] = {
    TokenType::expr,
    TokenType::thenStatement,
    TokenType::ELSEIF,
    TokenType::ifBody
};

constexpr TokenType mysql_ifBody_tokens_1275[] = {
    TokenType::expr,
    TokenType::thenStatement,
    TokenType::ELSE,
    TokenType::compoundStatementList
};

constexpr TokenType mysql_thenStatement_tokens_1276[] = {
    TokenType::THEN,
    TokenType::compoundStatementList
};

constexpr TokenType mysql_compoundStatementList_tokens_1277[] = {
    TokenType::compoundStatement,
    TokenType::SEMICOLON
};

constexpr TokenType mysql_caseStatement_tokens_1278[] = {
    TokenType::CASE,
    TokenType::expr,
    TokenType::whenExpression,
    TokenType::thenStatement,
    TokenType::elseStatement,
    TokenType::END,
    TokenType::CASE
};

constexpr TokenType mysql_elseStatement_tokens_1279[] = {
    TokenType::ELSE,
    TokenType::compoundStatementList
};

constexpr TokenType mysql_labeledBlock_tokens_1280[] = {
    TokenType::label,
    TokenType::beginEndBlock,
    TokenType::labelRef
};

constexpr TokenType mysql_unlabeledBlock_tokens_1281[] = {
    TokenType::beginEndBlock
};

constexpr TokenType mysql_label_tokens_1282[] = {
    TokenType::labelIdentifier,
    TokenType::COLON
};

constexpr TokenType mysql_beginEndBlock_tokens_1283[] = {
    TokenType::BEGIN,
    TokenType::spDeclarations,
    TokenType::compoundStatementList,
    TokenType::END
};

constexpr TokenType mysql_labeledControl_tokens_1284[] = {
    TokenType::label,
    TokenType::unlabeledControl,
    TokenType::labelRef
};

constexpr TokenType mysql_unlabeledControl_tokens_1285[] = {
    TokenType::loopBlock
};

constexpr TokenType mysql_unlabeledControl_tokens_1286[] = {
    TokenType::whileDoBlock
};

constexpr TokenType mysql_unlabeledControl_tokens_1287[] = {
    TokenType::repeatUntilBlock
};

constexpr TokenType mysql_loopBlock_tokens_1288[] = {
    TokenType::LOOP,
    TokenType::compoundStatementList,
    TokenType::END,
    TokenType::LOOP
};

constexpr TokenType mysql_whileDoBlock_tokens_1289[] = {
    TokenType::WHILE,
    TokenType::expr,
    TokenType::DO,
    TokenType::compoundStatementList,
    TokenType::END,
    TokenType::WHILE
};

constexpr TokenType mysql_repeatUntilBlock_tokens_1290[] = {
    TokenType::REPEAT,
    TokenType::compoundStatementList,
    TokenType::UNTIL,
    TokenType::expr,
    TokenType::END,
    TokenType::REPEAT
};

constexpr TokenType mysql_spDeclarations_tokens_1291[] = {
    TokenType::spDeclaration,
    TokenType::SEMICOLON
};

constexpr TokenType mysql_spDeclaration_tokens_1292[] = {
    TokenType::variableDeclaration
};

constexpr TokenType mysql_spDeclaration_tokens_1293[] = {
    TokenType::conditionDeclaration
};

constexpr TokenType mysql_spDeclaration_tokens_1294[] = {
    TokenType::handlerDeclaration
};

constexpr TokenType mysql_spDeclaration_tokens_1295[] = {
    TokenType::cursorDeclaration
};

constexpr TokenType mysql_variableDeclaration_tokens_1296[] = {
    TokenType::DECLARE,
    TokenType::identifierList,
    TokenType::dataType,
    TokenType::collate,
    TokenType::DEFAULT,
    TokenType::expr
};

constexpr TokenType mysql_conditionDeclaration_tokens_1297[] = {
    TokenType::DECLARE,
    TokenType::identifier,
    TokenType::CONDITION,
    TokenType::FOR,
    TokenType::spCondition
};

constexpr TokenType mysql_spCondition_tokens_1298[] = {
    TokenType::ulong_number
};

constexpr TokenType mysql_spCondition_tokens_1299[] = {
    TokenType::sqlstate
};

constexpr TokenType mysql_sqlstate_tokens_1300[] = {
    TokenType::SQLSTATE,
    TokenType::VALUE,
    TokenType::textLiteral
};

constexpr TokenType mysql_handlerDeclaration_tokens_1301[] = {
    TokenType::DECLARE,
    TokenType::CONTINUE,
    TokenType::HANDLER,
    TokenType::FOR,
    TokenType::handlerCondition,
    TokenType::COMMA,
    TokenType::handlerCondition,
    TokenType::compoundStatement
};

constexpr TokenType mysql_handlerDeclaration_tokens_1302[] = {
    TokenType::DECLARE,
    TokenType::EXIT,
    TokenType::HANDLER,
    TokenType::FOR,
    TokenType::handlerCondition,
    TokenType::COMMA,
    TokenType::handlerCondition,
    TokenType::compoundStatement
};

constexpr TokenType mysql_handlerDeclaration_tokens_1303[] = {
    TokenType::DECLARE,
    TokenType::UNDO,
    TokenType::HANDLER,
    TokenType::FOR,
    TokenType::handlerCondition,
    TokenType::COMMA,
    TokenType::handlerCondition,
    TokenType::compoundStatement
};

constexpr TokenType mysql_handlerCondition_tokens_1304[] = {
    TokenType::spCondition
};

constexpr TokenType mysql_handlerCondition_tokens_1305[] = {
    TokenType::identifier
};

constexpr TokenType mysql_handlerCondition_tokens_1306[] = {
    TokenType::SQLWARNING
};

constexpr TokenType mysql_handlerCondition_tokens_1307[] = {
    TokenType::notRule,
    TokenType::FOUND
};

constexpr TokenType mysql_handlerCondition_tokens_1308[] = {
    TokenType::SQLEXCEPTION
};

constexpr TokenType mysql_cursorDeclaration_tokens_1309[] = {
    TokenType::DECLARE,
    TokenType::identifier,
    TokenType::CURSOR,
    TokenType::FOR,
    TokenType::selectStatement
};

constexpr TokenType mysql_iterateStatement_tokens_1310[] = {
    TokenType::ITERATE,
    TokenType::labelRef
};

constexpr TokenType mysql_leaveStatement_tokens_1311[] = {
    TokenType::LEAVE,
    TokenType::labelRef
};

constexpr TokenType mysql_getDiagnosticsStatement_tokens_1312[] = {
    TokenType::GET,
    TokenType::CURRENT,
    TokenType::DIAGNOSTICS,
    TokenType::statementInformationItem,
    TokenType::COMMA,
    TokenType::statementInformationItem
};

constexpr TokenType mysql_getDiagnosticsStatement_tokens_1313[] = {
    TokenType::GET,
    TokenType::CURRENT,
    TokenType::DIAGNOSTICS,
    TokenType::CONDITION,
    TokenType::signalAllowedExpr,
    TokenType::conditionInformationItem,
    TokenType::COMMA,
    TokenType::conditionInformationItem
};

constexpr TokenType mysql_getDiagnosticsStatement_tokens_1314[] = {
    TokenType::GET,
    TokenType::STACKED,
    TokenType::DIAGNOSTICS,
    TokenType::statementInformationItem,
    TokenType::COMMA,
    TokenType::statementInformationItem
};

constexpr TokenType mysql_getDiagnosticsStatement_tokens_1315[] = {
    TokenType::GET,
    TokenType::STACKED,
    TokenType::DIAGNOSTICS,
    TokenType::CONDITION,
    TokenType::signalAllowedExpr,
    TokenType::conditionInformationItem,
    TokenType::COMMA,
    TokenType::conditionInformationItem
};

constexpr TokenType mysql_statementInformationItem_tokens_1316[] = {
    TokenType::userVariable,
    TokenType::EQ,
    TokenType::NUMBER
};

constexpr TokenType mysql_statementInformationItem_tokens_1317[] = {
    TokenType::userVariable,
    TokenType::EQ,
    TokenType::ROW_COUNT
};

constexpr TokenType mysql_statementInformationItem_tokens_1318[] = {
    TokenType::identifier,
    TokenType::EQ,
    TokenType::NUMBER
};

constexpr TokenType mysql_statementInformationItem_tokens_1319[] = {
    TokenType::identifier,
    TokenType::EQ,
    TokenType::ROW_COUNT
};

constexpr TokenType mysql_conditionInformationItem_tokens_1320[] = {
    TokenType::userVariable,
    TokenType::EQ,
    TokenType::signalInformationItemName
};

constexpr TokenType mysql_conditionInformationItem_tokens_1321[] = {
    TokenType::userVariable,
    TokenType::EQ,
    TokenType::RETURNED_SQLSTATE
};

constexpr TokenType mysql_conditionInformationItem_tokens_1322[] = {
    TokenType::identifier,
    TokenType::EQ,
    TokenType::signalInformationItemName
};

constexpr TokenType mysql_conditionInformationItem_tokens_1323[] = {
    TokenType::identifier,
    TokenType::EQ,
    TokenType::RETURNED_SQLSTATE
};

constexpr TokenType mysql_signalInformationItemName_tokens_1324[] = {
    TokenType::CLASS_ORIGIN
};

constexpr TokenType mysql_signalInformationItemName_tokens_1325[] = {
    TokenType::SUBCLASS_ORIGIN
};

constexpr TokenType mysql_signalInformationItemName_tokens_1326[] = {
    TokenType::CONSTRAINT_CATALOG
};

constexpr TokenType mysql_signalInformationItemName_tokens_1327[] = {
    TokenType::CONSTRAINT_SCHEMA
};

constexpr TokenType mysql_signalInformationItemName_tokens_1328[] = {
    TokenType::CONSTRAINT_NAME
};

constexpr TokenType mysql_signalInformationItemName_tokens_1329[] = {
    TokenType::CATALOG_NAME
};

constexpr TokenType mysql_signalInformationItemName_tokens_1330[] = {
    TokenType::SCHEMA_NAME
};

constexpr TokenType mysql_signalInformationItemName_tokens_1331[] = {
    TokenType::TABLE_NAME
};

constexpr TokenType mysql_signalInformationItemName_tokens_1332[] = {
    TokenType::COLUMN_NAME
};

constexpr TokenType mysql_signalInformationItemName_tokens_1333[] = {
    TokenType::CURSOR_NAME
};

constexpr TokenType mysql_signalInformationItemName_tokens_1334[] = {
    TokenType::MESSAGE_TEXT
};

constexpr TokenType mysql_signalInformationItemName_tokens_1335[] = {
    TokenType::MYSQL_ERRNO
};

constexpr TokenType mysql_signalStatement_tokens_1336[] = {
    TokenType::SIGNAL,
    TokenType::identifier,
    TokenType::SET,
    TokenType::signalInformationItem,
    TokenType::COMMA,
    TokenType::signalInformationItem
};

constexpr TokenType mysql_signalStatement_tokens_1337[] = {
    TokenType::SIGNAL,
    TokenType::sqlstate,
    TokenType::SET,
    TokenType::signalInformationItem,
    TokenType::COMMA,
    TokenType::signalInformationItem
};

constexpr TokenType mysql_resignalStatement_tokens_1338[] = {
    TokenType::RESIGNAL,
    TokenType::identifier,
    TokenType::SET,
    TokenType::signalInformationItem,
    TokenType::COMMA,
    TokenType::signalInformationItem
};

constexpr TokenType mysql_resignalStatement_tokens_1339[] = {
    TokenType::RESIGNAL,
    TokenType::sqlstate,
    TokenType::SET,
    TokenType::signalInformationItem,
    TokenType::COMMA,
    TokenType::signalInformationItem
};

constexpr TokenType mysql_signalInformationItem_tokens_1340[] = {
    TokenType::signalInformationItemName,
    TokenType::EQ,
    TokenType::signalAllowedExpr
};

constexpr TokenType mysql_cursorOpen_tokens_1341[] = {
    TokenType::OPEN,
    TokenType::identifier
};

constexpr TokenType mysql_cursorClose_tokens_1342[] = {
    TokenType::CLOSE,
    TokenType::identifier
};

constexpr TokenType mysql_cursorFetch_tokens_1343[] = {
    TokenType::FETCH,
    TokenType::NEXT,
    TokenType::FROM,
    TokenType::identifier,
    TokenType::INTO,
    TokenType::identifierList
};

constexpr TokenType mysql_schedule_tokens_1344[] = {
    TokenType::AT,
    TokenType::expr
};

constexpr TokenType mysql_schedule_tokens_1345[] = {
    TokenType::EVERY,
    TokenType::expr,
    TokenType::interval,
    TokenType::STAR,
    TokenType::expr,
    TokenType::ENDS,
    TokenType::expr
};

constexpr TokenType mysql_columnDefinition_tokens_1346[] = {
    TokenType::columnName,
    TokenType::fieldDefinition,
    TokenType::checkOrReferences
};

constexpr TokenType mysql_checkOrReferences_tokens_1347[] = {
    TokenType::this,
    TokenType::isServerVersionLt80016,
    TokenType::checkConstraint
};

constexpr TokenType mysql_checkOrReferences_tokens_1348[] = {
    TokenType::references
};

constexpr TokenType mysql_checkConstraint_tokens_1349[] = {
    TokenType::CHECK,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_constraintEnforcement_tokens_1350[] = {
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::NOT,
    TokenType::ENFORCED
};

constexpr TokenType mysql_tableConstraintDef_tokens_1351[] = {
    TokenType::type,
    TokenType::KEY,
    TokenType::indexNameAndType,
    TokenType::keyListWithExpression,
    TokenType::indexOption
};

constexpr TokenType mysql_tableConstraintDef_tokens_1352[] = {
    TokenType::type,
    TokenType::INDEX,
    TokenType::indexNameAndType,
    TokenType::keyListWithExpression,
    TokenType::indexOption
};

constexpr TokenType mysql_tableConstraintDef_tokens_1353[] = {
    TokenType::type,
    TokenType::FULLTEXT,
    TokenType::keyOrIndex,
    TokenType::indexName,
    TokenType::keyListWithExpression,
    TokenType::fulltextIndexOption
};

constexpr TokenType mysql_tableConstraintDef_tokens_1354[] = {
    TokenType::type,
    TokenType::SPATIAL,
    TokenType::keyOrIndex,
    TokenType::indexName,
    TokenType::keyListWithExpression,
    TokenType::spatialIndexOption
};

constexpr TokenType mysql_tableConstraintDef_tokens_1355[] = {
    TokenType::constraintName,
    TokenType::type,
    TokenType::PRIMARY,
    TokenType::KEY,
    TokenType::indexNameAndType,
    TokenType::keyListWithExpression,
    TokenType::indexOption
};

constexpr TokenType mysql_tableConstraintDef_tokens_1356[] = {
    TokenType::constraintName,
    TokenType::type,
    TokenType::UNIQUE,
    TokenType::keyOrIndex,
    TokenType::indexNameAndType,
    TokenType::keyListWithExpression,
    TokenType::indexOption
};

constexpr TokenType mysql_tableConstraintDef_tokens_1357[] = {
    TokenType::constraintName,
    TokenType::type,
    TokenType::FOREIGN,
    TokenType::KEY,
    TokenType::indexName,
    TokenType::keyList,
    TokenType::references
};

constexpr TokenType mysql_tableConstraintDef_tokens_1358[] = {
    TokenType::constraintName,
    TokenType::checkConstraint,
    TokenType::constraintEnforcement
};

constexpr TokenType mysql_constraintName_tokens_1359[] = {
    TokenType::CONSTRAINT,
    TokenType::identifier
};

constexpr TokenType mysql_fieldDefinition_tokens_1360[] = {
    TokenType::dataType,
    TokenType::columnAttribute
};

constexpr TokenType mysql_fieldDefinition_tokens_1361[] = {
    TokenType::dataType,
    TokenType::collate,
    TokenType::GENERATED,
    TokenType::ALWAYS,
    TokenType::AS,
    TokenType::exprWithParentheses,
    TokenType::VIRTUAL,
    TokenType::columnAttribute
};

constexpr TokenType mysql_fieldDefinition_tokens_1362[] = {
    TokenType::dataType,
    TokenType::collate,
    TokenType::GENERATED,
    TokenType::ALWAYS,
    TokenType::AS,
    TokenType::exprWithParentheses,
    TokenType::STORED,
    TokenType::columnAttribute
};

constexpr TokenType mysql_columnAttribute_tokens_1363[] = {
    TokenType::NOT,
    TokenType::nullLiteral
};

constexpr TokenType mysql_columnAttribute_tokens_1364[] = {
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::NOT,
    TokenType::SECONDARY
};

constexpr TokenType mysql_columnAttribute_tokens_1365[] = {
    TokenType::value,
    TokenType::DEFAULT,
    TokenType::nowOrSignedLiteral
};

constexpr TokenType mysql_columnAttribute_tokens_1366[] = {
    TokenType::value,
    TokenType::DEFAULT,
    TokenType::this,
    TokenType::isServerVersionGe80013,
    TokenType::exprWithParentheses
};

constexpr TokenType mysql_columnAttribute_tokens_1367[] = {
    TokenType::value,
    TokenType::ON,
    TokenType::UPDATE,
    TokenType::NOW,
    TokenType::timeFunctionParameters
};

constexpr TokenType mysql_columnAttribute_tokens_1368[] = {
    TokenType::value,
    TokenType::AUTO_INCREMENT
};

constexpr TokenType mysql_columnAttribute_tokens_1369[] = {
    TokenType::value,
    TokenType::SERIAL,
    TokenType::DEFAULT,
    TokenType::VALUE
};

constexpr TokenType mysql_columnAttribute_tokens_1370[] = {
    TokenType::PRIMARY,
    TokenType::value,
    TokenType::KEY
};

constexpr TokenType mysql_columnAttribute_tokens_1371[] = {
    TokenType::value,
    TokenType::UNIQUE,
    TokenType::KEY
};

constexpr TokenType mysql_columnAttribute_tokens_1372[] = {
    TokenType::value,
    TokenType::COMMENT,
    TokenType::textLiteral
};

constexpr TokenType mysql_columnAttribute_tokens_1373[] = {
    TokenType::collate
};

constexpr TokenType mysql_columnAttribute_tokens_1374[] = {
    TokenType::value,
    TokenType::COLUMN_FORMAT,
    TokenType::columnFormat
};

constexpr TokenType mysql_columnAttribute_tokens_1375[] = {
    TokenType::value,
    TokenType::STORAGE,
    TokenType::storageMedia
};

constexpr TokenType mysql_columnAttribute_tokens_1376[] = {
    TokenType::value,
    TokenType::SRID,
    TokenType::real_ulonglong_number
};

constexpr TokenType mysql_columnAttribute_tokens_1377[] = {
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::constraintName,
    TokenType::checkConstraint
};

constexpr TokenType mysql_columnAttribute_tokens_1378[] = {
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::constraintEnforcement
};

constexpr TokenType mysql_columnAttribute_tokens_1379[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::value,
    TokenType::ENGINE_ATTRIBUTE,
    TokenType::EQ,
    TokenType::jsonAttribute
};

constexpr TokenType mysql_columnAttribute_tokens_1380[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::value,
    TokenType::SECONDARY_ENGINE_ATTRIBUTE,
    TokenType::EQ,
    TokenType::jsonAttribute
};

constexpr TokenType mysql_columnAttribute_tokens_1381[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::visibility
};

constexpr TokenType mysql_columnFormat_tokens_1382[] = {
    TokenType::FIXED
};

constexpr TokenType mysql_columnFormat_tokens_1383[] = {
    TokenType::DYNAMIC
};

constexpr TokenType mysql_columnFormat_tokens_1384[] = {
    TokenType::DEFAULT
};

constexpr TokenType mysql_storageMedia_tokens_1385[] = {
    TokenType::DISK
};

constexpr TokenType mysql_storageMedia_tokens_1386[] = {
    TokenType::MEMORY
};

constexpr TokenType mysql_storageMedia_tokens_1387[] = {
    TokenType::DEFAULT
};

constexpr TokenType mysql_now_tokens_1388[] = {
    TokenType::NOW,
    TokenType::functionDatetimePrecision
};

constexpr TokenType mysql_nowOrSignedLiteral_tokens_1389[] = {
    TokenType::now
};

constexpr TokenType mysql_nowOrSignedLiteral_tokens_1390[] = {
    TokenType::signedLiteralOrNull
};

constexpr TokenType mysql_gcolAttribute_tokens_1391[] = {
    TokenType::UNIQUE,
    TokenType::KEY
};

constexpr TokenType mysql_gcolAttribute_tokens_1392[] = {
    TokenType::COMMENT,
    TokenType::textString
};

constexpr TokenType mysql_gcolAttribute_tokens_1393[] = {
    TokenType::notRule,
    TokenType::NULL_KW
};

constexpr TokenType mysql_gcolAttribute_tokens_1394[] = {
    TokenType::PRIMARY,
    TokenType::KEY
};

constexpr TokenType mysql_references_tokens_1395[] = {
    TokenType::REFERENCES,
    TokenType::tableRef,
    TokenType::identifierListWithParentheses,
    TokenType::MATCH,
    TokenType::match,
    TokenType::FULL,
    TokenType::ON,
    TokenType::option,
    TokenType::UPDATE,
    TokenType::deleteOption,
    TokenType::ON,
    TokenType::DELETE,
    TokenType::deleteOption
};

constexpr TokenType mysql_references_tokens_1396[] = {
    TokenType::REFERENCES,
    TokenType::tableRef,
    TokenType::identifierListWithParentheses,
    TokenType::MATCH,
    TokenType::match,
    TokenType::FULL,
    TokenType::ON,
    TokenType::option,
    TokenType::DELETE,
    TokenType::deleteOption,
    TokenType::ON,
    TokenType::UPDATE,
    TokenType::deleteOption
};

constexpr TokenType mysql_references_tokens_1397[] = {
    TokenType::REFERENCES,
    TokenType::tableRef,
    TokenType::identifierListWithParentheses,
    TokenType::MATCH,
    TokenType::match,
    TokenType::PARTIAL,
    TokenType::ON,
    TokenType::option,
    TokenType::UPDATE,
    TokenType::deleteOption,
    TokenType::ON,
    TokenType::DELETE,
    TokenType::deleteOption
};

constexpr TokenType mysql_references_tokens_1398[] = {
    TokenType::REFERENCES,
    TokenType::tableRef,
    TokenType::identifierListWithParentheses,
    TokenType::MATCH,
    TokenType::match,
    TokenType::PARTIAL,
    TokenType::ON,
    TokenType::option,
    TokenType::DELETE,
    TokenType::deleteOption,
    TokenType::ON,
    TokenType::UPDATE,
    TokenType::deleteOption
};

constexpr TokenType mysql_references_tokens_1399[] = {
    TokenType::REFERENCES,
    TokenType::tableRef,
    TokenType::identifierListWithParentheses,
    TokenType::MATCH,
    TokenType::match,
    TokenType::SIMPLE,
    TokenType::ON,
    TokenType::option,
    TokenType::UPDATE,
    TokenType::deleteOption,
    TokenType::ON,
    TokenType::DELETE,
    TokenType::deleteOption
};

constexpr TokenType mysql_references_tokens_1400[] = {
    TokenType::REFERENCES,
    TokenType::tableRef,
    TokenType::identifierListWithParentheses,
    TokenType::MATCH,
    TokenType::match,
    TokenType::SIMPLE,
    TokenType::ON,
    TokenType::option,
    TokenType::DELETE,
    TokenType::deleteOption,
    TokenType::ON,
    TokenType::UPDATE,
    TokenType::deleteOption
};

constexpr TokenType mysql_keyList_tokens_1401[] = {
    TokenType::LPAREN,
    TokenType::keyPart,
    TokenType::COMMA,
    TokenType::keyPart,
    TokenType::RPAREN
};

constexpr TokenType mysql_keyPart_tokens_1402[] = {
    TokenType::identifier,
    TokenType::fieldLength,
    TokenType::direction
};

constexpr TokenType mysql_indexType_tokens_1403[] = {
    TokenType::algorithm,
    TokenType::BTREE
};

constexpr TokenType mysql_indexType_tokens_1404[] = {
    TokenType::algorithm,
    TokenType::RTREE
};

constexpr TokenType mysql_indexType_tokens_1405[] = {
    TokenType::algorithm,
    TokenType::HASH
};

constexpr TokenType mysql_indexOption_tokens_1406[] = {
    TokenType::commonIndexOption
};

constexpr TokenType mysql_indexOption_tokens_1407[] = {
    TokenType::indexTypeClause
};

constexpr TokenType mysql_commonIndexOption_tokens_1408[] = {
    TokenType::KEY_BLOCK_SIZE,
    TokenType::EQ,
    TokenType::ulong_number
};

constexpr TokenType mysql_commonIndexOption_tokens_1409[] = {
    TokenType::COMMENT,
    TokenType::textLiteral
};

constexpr TokenType mysql_commonIndexOption_tokens_1410[] = {
    TokenType::visibility
};

constexpr TokenType mysql_commonIndexOption_tokens_1411[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::ENGINE_ATTRIBUTE,
    TokenType::EQ,
    TokenType::jsonAttribute
};

constexpr TokenType mysql_commonIndexOption_tokens_1412[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::SECONDARY_ENGINE_ATTRIBUTE,
    TokenType::EQ,
    TokenType::jsonAttribute
};

constexpr TokenType mysql_visibility_tokens_1413[] = {
    TokenType::VISIBLE
};

constexpr TokenType mysql_visibility_tokens_1414[] = {
    TokenType::INVISIBLE
};

constexpr TokenType mysql_indexTypeClause_tokens_1415[] = {
    TokenType::USING,
    TokenType::indexType
};

constexpr TokenType mysql_indexTypeClause_tokens_1416[] = {
    TokenType::TYPE,
    TokenType::indexType
};

constexpr TokenType mysql_fulltextIndexOption_tokens_1417[] = {
    TokenType::commonIndexOption
};

constexpr TokenType mysql_fulltextIndexOption_tokens_1418[] = {
    TokenType::WITH,
    TokenType::PARSER,
    TokenType::identifier
};

constexpr TokenType mysql_spatialIndexOption_tokens_1419[] = {
    TokenType::commonIndexOption
};

constexpr TokenType mysql_dataTypeDefinition_tokens_1420[] = {
    TokenType::dataType,
    TokenType::EOF_TOKEN
};

constexpr TokenType mysql_dataType_tokens_1421[] = {
    TokenType::type,
    TokenType::INT,
    TokenType::fieldLength,
    TokenType::fieldOptions
};

constexpr TokenType mysql_dataType_tokens_1422[] = {
    TokenType::type,
    TokenType::TINYINT,
    TokenType::fieldLength,
    TokenType::fieldOptions
};

constexpr TokenType mysql_dataType_tokens_1423[] = {
    TokenType::type,
    TokenType::SMALLINT,
    TokenType::fieldLength,
    TokenType::fieldOptions
};

constexpr TokenType mysql_dataType_tokens_1424[] = {
    TokenType::type,
    TokenType::MEDIUMINT,
    TokenType::fieldLength,
    TokenType::fieldOptions
};

constexpr TokenType mysql_dataType_tokens_1425[] = {
    TokenType::type,
    TokenType::BIGINT,
    TokenType::fieldLength,
    TokenType::fieldOptions
};

constexpr TokenType mysql_dataType_tokens_1426[] = {
    TokenType::type,
    TokenType::REAL,
    TokenType::precision,
    TokenType::fieldOptions
};

constexpr TokenType mysql_dataType_tokens_1427[] = {
    TokenType::type,
    TokenType::DOUBLE,
    TokenType::PRECISION,
    TokenType::precision,
    TokenType::fieldOptions
};

constexpr TokenType mysql_dataType_tokens_1428[] = {
    TokenType::type,
    TokenType::FLOAT,
    TokenType::floatOptions,
    TokenType::fieldOptions
};

constexpr TokenType mysql_dataType_tokens_1429[] = {
    TokenType::type,
    TokenType::DECIMAL,
    TokenType::floatOptions,
    TokenType::fieldOptions
};

constexpr TokenType mysql_dataType_tokens_1430[] = {
    TokenType::type,
    TokenType::NUMERIC,
    TokenType::floatOptions,
    TokenType::fieldOptions
};

constexpr TokenType mysql_dataType_tokens_1431[] = {
    TokenType::type,
    TokenType::FIXED,
    TokenType::floatOptions,
    TokenType::fieldOptions
};

constexpr TokenType mysql_dataType_tokens_1432[] = {
    TokenType::type,
    TokenType::BIT,
    TokenType::fieldLength
};

constexpr TokenType mysql_dataType_tokens_1433[] = {
    TokenType::type,
    TokenType::BOOL
};

constexpr TokenType mysql_dataType_tokens_1434[] = {
    TokenType::type,
    TokenType::BOOLEAN
};

constexpr TokenType mysql_dataType_tokens_1435[] = {
    TokenType::type,
    TokenType::CHAR,
    TokenType::fieldLength,
    TokenType::charsetWithOptBinary
};

constexpr TokenType mysql_dataType_tokens_1436[] = {
    TokenType::nchar,
    TokenType::fieldLength,
    TokenType::BINARY
};

constexpr TokenType mysql_dataType_tokens_1437[] = {
    TokenType::type,
    TokenType::BINARY,
    TokenType::fieldLength
};

constexpr TokenType mysql_dataType_tokens_1438[] = {
    TokenType::type,
    TokenType::CHAR,
    TokenType::VARYING,
    TokenType::fieldLength,
    TokenType::charsetWithOptBinary
};

constexpr TokenType mysql_dataType_tokens_1439[] = {
    TokenType::type,
    TokenType::VARCHAR,
    TokenType::fieldLength,
    TokenType::charsetWithOptBinary
};

constexpr TokenType mysql_dataType_tokens_1440[] = {
    TokenType::type,
    TokenType::NATIONAL,
    TokenType::VARCHAR,
    TokenType::fieldLength,
    TokenType::BINARY
};

constexpr TokenType mysql_dataType_tokens_1441[] = {
    TokenType::type,
    TokenType::NVARCHAR,
    TokenType::fieldLength,
    TokenType::BINARY
};

constexpr TokenType mysql_dataType_tokens_1442[] = {
    TokenType::type,
    TokenType::NCHAR,
    TokenType::VARCHAR,
    TokenType::fieldLength,
    TokenType::BINARY
};

constexpr TokenType mysql_dataType_tokens_1443[] = {
    TokenType::type,
    TokenType::NATIONAL,
    TokenType::CHAR,
    TokenType::VARYING,
    TokenType::fieldLength,
    TokenType::BINARY
};

constexpr TokenType mysql_dataType_tokens_1444[] = {
    TokenType::type,
    TokenType::NCHAR,
    TokenType::VARYING,
    TokenType::fieldLength,
    TokenType::BINARY
};

constexpr TokenType mysql_dataType_tokens_1445[] = {
    TokenType::type,
    TokenType::VARBINARY,
    TokenType::fieldLength
};

constexpr TokenType mysql_dataType_tokens_1446[] = {
    TokenType::type,
    TokenType::YEAR,
    TokenType::fieldLength,
    TokenType::fieldOptions
};

constexpr TokenType mysql_dataType_tokens_1447[] = {
    TokenType::type,
    TokenType::DATE
};

constexpr TokenType mysql_dataType_tokens_1448[] = {
    TokenType::type,
    TokenType::TIME,
    TokenType::typeDatetimePrecision
};

constexpr TokenType mysql_dataType_tokens_1449[] = {
    TokenType::type,
    TokenType::TIMESTAMP,
    TokenType::typeDatetimePrecision
};

constexpr TokenType mysql_dataType_tokens_1450[] = {
    TokenType::type,
    TokenType::DATETIME,
    TokenType::typeDatetimePrecision
};

constexpr TokenType mysql_dataType_tokens_1451[] = {
    TokenType::type,
    TokenType::TINYBLOB
};

constexpr TokenType mysql_dataType_tokens_1452[] = {
    TokenType::type,
    TokenType::BLOB,
    TokenType::fieldLength
};

constexpr TokenType mysql_dataType_tokens_1453[] = {
    TokenType::type,
    TokenType::MEDIUMBLOB
};

constexpr TokenType mysql_dataType_tokens_1454[] = {
    TokenType::type,
    TokenType::LONGBLOB
};

constexpr TokenType mysql_dataType_tokens_1455[] = {
    TokenType::type,
    TokenType::LONG,
    TokenType::VARBINARY
};

constexpr TokenType mysql_dataType_tokens_1456[] = {
    TokenType::type,
    TokenType::LONG,
    TokenType::CHAR,
    TokenType::VARYING,
    TokenType::charsetWithOptBinary
};

constexpr TokenType mysql_dataType_tokens_1457[] = {
    TokenType::type,
    TokenType::LONG,
    TokenType::VARCHAR,
    TokenType::charsetWithOptBinary
};

constexpr TokenType mysql_dataType_tokens_1458[] = {
    TokenType::type,
    TokenType::TINYTEXT,
    TokenType::charsetWithOptBinary
};

constexpr TokenType mysql_dataType_tokens_1459[] = {
    TokenType::type,
    TokenType::TEXT,
    TokenType::fieldLength,
    TokenType::charsetWithOptBinary
};

constexpr TokenType mysql_dataType_tokens_1460[] = {
    TokenType::type,
    TokenType::MEDIUMTEXT,
    TokenType::charsetWithOptBinary
};

constexpr TokenType mysql_dataType_tokens_1461[] = {
    TokenType::type,
    TokenType::LONGTEXT,
    TokenType::charsetWithOptBinary
};

constexpr TokenType mysql_dataType_tokens_1462[] = {
    TokenType::type,
    TokenType::ENUM,
    TokenType::stringList,
    TokenType::charsetWithOptBinary
};

constexpr TokenType mysql_dataType_tokens_1463[] = {
    TokenType::type,
    TokenType::SET,
    TokenType::stringList,
    TokenType::charsetWithOptBinary
};

constexpr TokenType mysql_dataType_tokens_1464[] = {
    TokenType::type,
    TokenType::SERIAL
};

constexpr TokenType mysql_dataType_tokens_1465[] = {
    TokenType::type,
    TokenType::JSON
};

constexpr TokenType mysql_dataType_tokens_1466[] = {
    TokenType::type,
    TokenType::GEOMETRY
};

constexpr TokenType mysql_dataType_tokens_1467[] = {
    TokenType::type,
    TokenType::GEOMETRYCOLLECTION
};

constexpr TokenType mysql_dataType_tokens_1468[] = {
    TokenType::type,
    TokenType::POINT
};

constexpr TokenType mysql_dataType_tokens_1469[] = {
    TokenType::type,
    TokenType::STAR
};

constexpr TokenType mysql_dataType_tokens_1470[] = {
    TokenType::type,
    TokenType::LINESTRING
};

constexpr TokenType mysql_dataType_tokens_1471[] = {
    TokenType::type,
    TokenType::STAR
};

constexpr TokenType mysql_dataType_tokens_1472[] = {
    TokenType::type,
    TokenType::POLYGON
};

constexpr TokenType mysql_dataType_tokens_1473[] = {
    TokenType::type,
    TokenType::STAR
};

constexpr TokenType mysql_nchar_tokens_1474[] = {
    TokenType::type,
    TokenType::NCHAR
};

constexpr TokenType mysql_nchar_tokens_1475[] = {
    TokenType::type,
    TokenType::NATIONAL,
    TokenType::CHAR
};

constexpr TokenType mysql_realType_tokens_1476[] = {
    TokenType::type,
    TokenType::REAL
};

constexpr TokenType mysql_realType_tokens_1477[] = {
    TokenType::type,
    TokenType::DOUBLE,
    TokenType::PRECISION
};

constexpr TokenType mysql_fieldLength_tokens_1478[] = {
    TokenType::LPAREN,
    TokenType::real_ulonglong_number,
    TokenType::RPAREN
};

constexpr TokenType mysql_fieldLength_tokens_1479[] = {
    TokenType::LPAREN,
    TokenType::NUMBER,
    TokenType::RPAREN
};

constexpr TokenType mysql_fieldOptions_tokens_1480[] = {
    TokenType::SIGNED
};

constexpr TokenType mysql_fieldOptions_tokens_1481[] = {
    TokenType::UNSIGNED
};

constexpr TokenType mysql_fieldOptions_tokens_1482[] = {
    TokenType::ZEROFILL
};

constexpr TokenType mysql_charsetWithOptBinary_tokens_1483[] = {
    TokenType::ascii
};

constexpr TokenType mysql_charsetWithOptBinary_tokens_1484[] = {
    TokenType::unicode
};

constexpr TokenType mysql_charsetWithOptBinary_tokens_1485[] = {
    TokenType::BYTE
};

constexpr TokenType mysql_charsetWithOptBinary_tokens_1486[] = {
    TokenType::charset,
    TokenType::charsetName,
    TokenType::BINARY
};

constexpr TokenType mysql_charsetWithOptBinary_tokens_1487[] = {
    TokenType::BINARY,
    TokenType::charset,
    TokenType::charsetName
};

constexpr TokenType mysql_ascii_tokens_1488[] = {
    TokenType::ASCII,
    TokenType::BINARY
};

constexpr TokenType mysql_ascii_tokens_1489[] = {
    TokenType::BINARY,
    TokenType::ASCII
};

constexpr TokenType mysql_unicode_tokens_1490[] = {
    TokenType::UNICODE,
    TokenType::BINARY
};

constexpr TokenType mysql_unicode_tokens_1491[] = {
    TokenType::BINARY,
    TokenType::UNICODE
};

constexpr TokenType mysql_wsNumCodepoints_tokens_1492[] = {
    TokenType::LPAREN,
    TokenType::real_ulong_number,
    TokenType::RPAREN
};

constexpr TokenType mysql_typeDatetimePrecision_tokens_1493[] = {
    TokenType::LPAREN,
    TokenType::NUMBER,
    TokenType::RPAREN
};

constexpr TokenType mysql_functionDatetimePrecision_tokens_1494[] = {
    TokenType::parentheses
};

constexpr TokenType mysql_functionDatetimePrecision_tokens_1495[] = {
    TokenType::LPAREN,
    TokenType::NUMBER,
    TokenType::RPAREN
};

constexpr TokenType mysql_charsetName_tokens_1496[] = {
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_charsetName_tokens_1497[] = {
    TokenType::BINARY
};

constexpr TokenType mysql_charsetName_tokens_1498[] = {
    TokenType::this,
    TokenType::isServerVersionLt80011,
    TokenType::DEFAULT
};

constexpr TokenType mysql_collationName_tokens_1499[] = {
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_collationName_tokens_1500[] = {
    TokenType::this,
    TokenType::isServerVersionLt80011,
    TokenType::DEFAULT
};

constexpr TokenType mysql_collationName_tokens_1501[] = {
    TokenType::this,
    TokenType::isServerVersionGe80018,
    TokenType::BINARY
};

constexpr TokenType mysql_ternaryOption_tokens_1502[] = {
    TokenType::ulong_number
};

constexpr TokenType mysql_ternaryOption_tokens_1503[] = {
    TokenType::DEFAULT
};

constexpr TokenType mysql_defaultCollation_tokens_1504[] = {
    TokenType::DEFAULT,
    TokenType::COLLATE,
    TokenType::EQ,
    TokenType::collationName
};

constexpr TokenType mysql_defaultEncryption_tokens_1505[] = {
    TokenType::DEFAULT,
    TokenType::ENCRYPTION,
    TokenType::EQ,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_defaultCharset_tokens_1506[] = {
    TokenType::DEFAULT,
    TokenType::charset,
    TokenType::EQ,
    TokenType::charsetName
};

constexpr TokenType mysql_partitionClause_tokens_1507[] = {
    TokenType::PARTITION,
    TokenType::BY,
    TokenType::partitionTypeDef,
    TokenType::PARTITIONS,
    TokenType::real_ulong_number,
    TokenType::subPartitions,
    TokenType::partitionDefinitions
};

constexpr TokenType mysql_partitionTypeDef_tokens_1508[] = {
    TokenType::LINEAR,
    TokenType::KEY,
    TokenType::partitionKeyAlgorithm,
    TokenType::LPAREN,
    TokenType::identifierList,
    TokenType::RPAREN,
    TokenType::partitionDefKey
};

constexpr TokenType mysql_partitionTypeDef_tokens_1509[] = {
    TokenType::LINEAR,
    TokenType::HASH,
    TokenType::LPAREN,
    TokenType::bitExpr,
    TokenType::RPAREN,
    TokenType::partitionDefHash
};

constexpr TokenType mysql_partitionTypeDef_tokens_1510[] = {
    TokenType::RANGE,
    TokenType::LPAREN,
    TokenType::bitExpr,
    TokenType::RPAREN,
    TokenType::partitionDefRangeList
};

constexpr TokenType mysql_partitionTypeDef_tokens_1511[] = {
    TokenType::RANGE,
    TokenType::COLUMNS,
    TokenType::LPAREN,
    TokenType::identifierList,
    TokenType::RPAREN,
    TokenType::partitionDefRangeList
};

constexpr TokenType mysql_partitionTypeDef_tokens_1512[] = {
    TokenType::LIST,
    TokenType::LPAREN,
    TokenType::bitExpr,
    TokenType::RPAREN,
    TokenType::partitionDefRangeList
};

constexpr TokenType mysql_partitionTypeDef_tokens_1513[] = {
    TokenType::LIST,
    TokenType::COLUMNS,
    TokenType::LPAREN,
    TokenType::identifierList,
    TokenType::RPAREN,
    TokenType::partitionDefRangeList
};

constexpr TokenType mysql_subPartitions_tokens_1514[] = {
    TokenType::SUBPARTITION,
    TokenType::BY,
    TokenType::LINEAR,
    TokenType::HASH,
    TokenType::LPAREN,
    TokenType::bitExpr,
    TokenType::RPAREN,
    TokenType::SUBPARTITIONS,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_subPartitions_tokens_1515[] = {
    TokenType::SUBPARTITION,
    TokenType::BY,
    TokenType::LINEAR,
    TokenType::KEY,
    TokenType::partitionKeyAlgorithm,
    TokenType::identifierListWithParentheses,
    TokenType::SUBPARTITIONS,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_partitionKeyAlgorithm_tokens_1516[] = {
    TokenType::ALGORITHM,
    TokenType::EQ,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_partitionDefinitions_tokens_1517[] = {
    TokenType::LPAREN,
    TokenType::partitionDefinition,
    TokenType::COMMA,
    TokenType::partitionDefinition,
    TokenType::RPAREN
};

constexpr TokenType mysql_partitionDefinition_tokens_1518[] = {
    TokenType::PARTITION,
    TokenType::identifier,
    TokenType::VALUES,
    TokenType::LESS,
    TokenType::THAN,
    TokenType::partitionValueItemListParen,
    TokenType::partitionOption,
    TokenType::LPAREN,
    TokenType::subpartitionDefinition,
    TokenType::COMMA,
    TokenType::subpartitionDefinition,
    TokenType::RPAREN
};

constexpr TokenType mysql_partitionDefinition_tokens_1519[] = {
    TokenType::PARTITION,
    TokenType::identifier,
    TokenType::VALUES,
    TokenType::LESS,
    TokenType::THAN,
    TokenType::MAXVALUE,
    TokenType::partitionOption,
    TokenType::LPAREN,
    TokenType::subpartitionDefinition,
    TokenType::COMMA,
    TokenType::subpartitionDefinition,
    TokenType::RPAREN
};

constexpr TokenType mysql_partitionDefinition_tokens_1520[] = {
    TokenType::PARTITION,
    TokenType::identifier,
    TokenType::VALUES,
    TokenType::IN,
    TokenType::partitionValuesIn,
    TokenType::partitionOption,
    TokenType::LPAREN,
    TokenType::subpartitionDefinition,
    TokenType::COMMA,
    TokenType::subpartitionDefinition,
    TokenType::RPAREN
};

constexpr TokenType mysql_partitionValuesIn_tokens_1521[] = {
    TokenType::partitionValueItemListParen
};

constexpr TokenType mysql_partitionValuesIn_tokens_1522[] = {
    TokenType::LPAREN,
    TokenType::partitionValueItemListParen,
    TokenType::COMMA,
    TokenType::partitionValueItemListParen,
    TokenType::RPAREN
};

constexpr TokenType mysql_partitionOption_tokens_1523[] = {
    TokenType::option,
    TokenType::TABLESPACE,
    TokenType::EQ,
    TokenType::identifier
};

constexpr TokenType mysql_partitionOption_tokens_1524[] = {
    TokenType::STORAGE,
    TokenType::option,
    TokenType::ENGINE,
    TokenType::EQ,
    TokenType::engineRef
};

constexpr TokenType mysql_partitionOption_tokens_1525[] = {
    TokenType::option,
    TokenType::NODEGROUP,
    TokenType::EQ,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_partitionOption_tokens_1526[] = {
    TokenType::option,
    TokenType::MAX_ROWS,
    TokenType::EQ,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_partitionOption_tokens_1527[] = {
    TokenType::option,
    TokenType::MIN_ROWS,
    TokenType::EQ,
    TokenType::real_ulong_number
};

constexpr TokenType mysql_partitionOption_tokens_1528[] = {
    TokenType::option,
    TokenType::DATA,
    TokenType::DIRECTORY,
    TokenType::EQ,
    TokenType::textLiteral
};

constexpr TokenType mysql_partitionOption_tokens_1529[] = {
    TokenType::option,
    TokenType::INDEX,
    TokenType::DIRECTORY,
    TokenType::EQ,
    TokenType::textLiteral
};

constexpr TokenType mysql_partitionOption_tokens_1530[] = {
    TokenType::option,
    TokenType::COMMENT,
    TokenType::EQ,
    TokenType::textLiteral
};

constexpr TokenType mysql_subpartitionDefinition_tokens_1531[] = {
    TokenType::SUBPARTITION,
    TokenType::textOrIdentifier,
    TokenType::partitionOption
};

constexpr TokenType mysql_partitionValueItemListParen_tokens_1532[] = {
    TokenType::LPAREN,
    TokenType::partitionValueItem,
    TokenType::COMMA,
    TokenType::partitionValueItem,
    TokenType::RPAREN
};

constexpr TokenType mysql_partitionValueItem_tokens_1533[] = {
    TokenType::bitExpr
};

constexpr TokenType mysql_partitionValueItem_tokens_1534[] = {
    TokenType::MAXVALUE
};

constexpr TokenType mysql_definerClause_tokens_1535[] = {
    TokenType::DEFINER,
    TokenType::EQ,
    TokenType::user
};

constexpr TokenType mysql_ifExists_tokens_1536[] = {
    TokenType::IF,
    TokenType::EXISTS
};

constexpr TokenType mysql_ifExistsIdentifier_tokens_1537[] = {
    TokenType::ifExists,
    TokenType::persistedVariableIdentifier
};

constexpr TokenType mysql_persistedVariableIdentifier_tokens_1538[] = {
    TokenType::identifier
};

constexpr TokenType mysql_persistedVariableIdentifier_tokens_1539[] = {
    TokenType::this,
    TokenType::isServerVersionGe80032,
    TokenType::qualifiedIdentifier
};

constexpr TokenType mysql_persistedVariableIdentifier_tokens_1540[] = {
    TokenType::this,
    TokenType::isServerVersionGe80032,
    TokenType::DEFAULT,
    TokenType::dotIdentifier
};

constexpr TokenType mysql_ifNotExists_tokens_1541[] = {
    TokenType::IF,
    TokenType::notRule,
    TokenType::EXISTS
};

constexpr TokenType mysql_ignoreUnknownUser_tokens_1542[] = {
    TokenType::IGNORE,
    TokenType::UNKNOWN,
    TokenType::USER
};

constexpr TokenType mysql_procedureParameter_tokens_1543[] = {
    TokenType::type,
    TokenType::IN,
    TokenType::functionParameter
};

constexpr TokenType mysql_procedureParameter_tokens_1544[] = {
    TokenType::type,
    TokenType::OUT,
    TokenType::functionParameter
};

constexpr TokenType mysql_procedureParameter_tokens_1545[] = {
    TokenType::type,
    TokenType::INOUT,
    TokenType::functionParameter
};

constexpr TokenType mysql_functionParameter_tokens_1546[] = {
    TokenType::parameterName,
    TokenType::typeWithOptCollate
};

constexpr TokenType mysql_collate_tokens_1547[] = {
    TokenType::COLLATE,
    TokenType::collationName
};

constexpr TokenType mysql_typeWithOptCollate_tokens_1548[] = {
    TokenType::dataType,
    TokenType::collate
};

constexpr TokenType mysql_schemaIdentifierPair_tokens_1549[] = {
    TokenType::LPAREN,
    TokenType::schemaRef,
    TokenType::COMMA,
    TokenType::schemaRef,
    TokenType::RPAREN
};

constexpr TokenType mysql_viewRefList_tokens_1550[] = {
    TokenType::viewRef,
    TokenType::COMMA,
    TokenType::viewRef
};

constexpr TokenType mysql_charsetClause_tokens_1551[] = {
    TokenType::charset,
    TokenType::charsetName
};

constexpr TokenType mysql_fieldsClause_tokens_1552[] = {
    TokenType::COLUMNS,
    TokenType::fieldTerm
};

constexpr TokenType mysql_fieldTerm_tokens_1553[] = {
    TokenType::TERMINATED,
    TokenType::BY,
    TokenType::textString
};

constexpr TokenType mysql_fieldTerm_tokens_1554[] = {
    TokenType::OPTIONALLY,
    TokenType::ENCLOSED,
    TokenType::BY,
    TokenType::textString
};

constexpr TokenType mysql_fieldTerm_tokens_1555[] = {
    TokenType::ESCAPED,
    TokenType::BY,
    TokenType::textString
};

constexpr TokenType mysql_linesClause_tokens_1556[] = {
    TokenType::LINES,
    TokenType::lineTerm
};

constexpr TokenType mysql_lineTerm_tokens_1557[] = {
    TokenType::TERMINATED,
    TokenType::BY,
    TokenType::textString
};

constexpr TokenType mysql_lineTerm_tokens_1558[] = {
    TokenType::STAR,
    TokenType::BY,
    TokenType::textString
};

constexpr TokenType mysql_userList_tokens_1559[] = {
    TokenType::user,
    TokenType::COMMA,
    TokenType::user
};

constexpr TokenType mysql_identification_tokens_1560[] = {
    TokenType::identifiedByPassword
};

constexpr TokenType mysql_identification_tokens_1561[] = {
    TokenType::identifiedByRandomPassword
};

constexpr TokenType mysql_identification_tokens_1562[] = {
    TokenType::identifiedWithPlugin
};

constexpr TokenType mysql_identification_tokens_1563[] = {
    TokenType::identifiedWithPluginAsAuth
};

constexpr TokenType mysql_identification_tokens_1564[] = {
    TokenType::identifiedWithPluginByPassword
};

constexpr TokenType mysql_identification_tokens_1565[] = {
    TokenType::identifiedWithPluginByRandomPassword
};

constexpr TokenType mysql_identifiedByPassword_tokens_1566[] = {
    TokenType::IDENTIFIED,
    TokenType::BY,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_identifiedByRandomPassword_tokens_1567[] = {
    TokenType::IDENTIFIED,
    TokenType::BY,
    TokenType::RANDOM,
    TokenType::PASSWORD
};

constexpr TokenType mysql_identifiedWithPlugin_tokens_1568[] = {
    TokenType::IDENTIFIED,
    TokenType::WITH,
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_identifiedWithPluginAsAuth_tokens_1569[] = {
    TokenType::IDENTIFIED,
    TokenType::WITH,
    TokenType::textOrIdentifier,
    TokenType::AS,
    TokenType::textStringHash
};

constexpr TokenType mysql_identifiedWithPluginByPassword_tokens_1570[] = {
    TokenType::IDENTIFIED,
    TokenType::WITH,
    TokenType::textOrIdentifier,
    TokenType::BY,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_identifiedWithPluginByRandomPassword_tokens_1571[] = {
    TokenType::IDENTIFIED,
    TokenType::WITH,
    TokenType::textOrIdentifier,
    TokenType::BY,
    TokenType::RANDOM,
    TokenType::PASSWORD
};

constexpr TokenType mysql_initialAuth_tokens_1572[] = {
    TokenType::INITIAL,
    TokenType::AUTHENTICATION,
    TokenType::identifiedByRandomPassword
};

constexpr TokenType mysql_initialAuth_tokens_1573[] = {
    TokenType::INITIAL,
    TokenType::AUTHENTICATION,
    TokenType::identifiedWithPluginAsAuth
};

constexpr TokenType mysql_initialAuth_tokens_1574[] = {
    TokenType::INITIAL,
    TokenType::AUTHENTICATION,
    TokenType::identifiedByPassword
};

constexpr TokenType mysql_retainCurrentPassword_tokens_1575[] = {
    TokenType::RETAIN,
    TokenType::CURRENT,
    TokenType::PASSWORD
};

constexpr TokenType mysql_discardOldPassword_tokens_1576[] = {
    TokenType::DISCARD,
    TokenType::OLD,
    TokenType::PASSWORD
};

constexpr TokenType mysql_userRegistration_tokens_1577[] = {
    TokenType::factor,
    TokenType::INITIATE,
    TokenType::REGISTRATION
};

constexpr TokenType mysql_userRegistration_tokens_1578[] = {
    TokenType::factor,
    TokenType::UNREGISTER
};

constexpr TokenType mysql_userRegistration_tokens_1579[] = {
    TokenType::factor,
    TokenType::FINISH,
    TokenType::REGISTRATION,
    TokenType::SET,
    TokenType::CHALLENGE_RESPONSE,
    TokenType::AS,
    TokenType::textStringHash
};

constexpr TokenType mysql_factor_tokens_1580[] = {
    TokenType::numLiteral,
    TokenType::FACTOR
};

constexpr TokenType mysql_replacePassword_tokens_1581[] = {
    TokenType::REPLACE,
    TokenType::textString
};

constexpr TokenType mysql_userIdentifierOrText_tokens_1582[] = {
    TokenType::textOrIdentifier,
    TokenType::userVariable
};

constexpr TokenType mysql_user_tokens_1583[] = {
    TokenType::userIdentifierOrText
};

constexpr TokenType mysql_user_tokens_1584[] = {
    TokenType::CURRENT_USER,
    TokenType::parentheses
};

constexpr TokenType mysql_likeClause_tokens_1585[] = {
    TokenType::LIKE,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_likeOrWhere_tokens_1586[] = {
    TokenType::likeClause
};

constexpr TokenType mysql_likeOrWhere_tokens_1587[] = {
    TokenType::whereClause
};

constexpr TokenType mysql_onlineOption_tokens_1588[] = {
    TokenType::ONLINE
};

constexpr TokenType mysql_onlineOption_tokens_1589[] = {
    TokenType::OFFLINE
};

constexpr TokenType mysql_noWriteToBinLog_tokens_1590[] = {
    TokenType::LOCAL
};

constexpr TokenType mysql_noWriteToBinLog_tokens_1591[] = {
    TokenType::NO_WRITE_TO_BINLOG
};

constexpr TokenType mysql_usePartition_tokens_1592[] = {
    TokenType::PARTITION,
    TokenType::identifierListWithParentheses
};

constexpr TokenType mysql_fieldIdentifier_tokens_1593[] = {
    TokenType::dotIdentifier
};

constexpr TokenType mysql_fieldIdentifier_tokens_1594[] = {
    TokenType::qualifiedIdentifier,
    TokenType::dotIdentifier
};

constexpr TokenType mysql_columnName_tokens_1595[] = {
    TokenType::identifier
};

constexpr TokenType mysql_columnInternalRef_tokens_1596[] = {
    TokenType::identifier
};

constexpr TokenType mysql_columnInternalRefList_tokens_1597[] = {
    TokenType::LPAREN,
    TokenType::columnInternalRef,
    TokenType::COMMA,
    TokenType::columnInternalRef,
    TokenType::RPAREN
};

constexpr TokenType mysql_columnRef_tokens_1598[] = {
    TokenType::fieldIdentifier
};

constexpr TokenType mysql_indexName_tokens_1599[] = {
    TokenType::identifier
};

constexpr TokenType mysql_indexRef_tokens_1600[] = {
    TokenType::fieldIdentifier
};

constexpr TokenType mysql_tableWild_tokens_1601[] = {
    TokenType::identifier,
    TokenType::DOT,
    TokenType::identifier,
    TokenType::DOT,
    TokenType::STAR
};

constexpr TokenType mysql_schemaName_tokens_1602[] = {
    TokenType::identifier
};

constexpr TokenType mysql_schemaRef_tokens_1603[] = {
    TokenType::identifier
};

constexpr TokenType mysql_procedureName_tokens_1604[] = {
    TokenType::qualifiedIdentifier
};

constexpr TokenType mysql_procedureRef_tokens_1605[] = {
    TokenType::qualifiedIdentifier
};

constexpr TokenType mysql_functionName_tokens_1606[] = {
    TokenType::qualifiedIdentifier
};

constexpr TokenType mysql_functionRef_tokens_1607[] = {
    TokenType::qualifiedIdentifier
};

constexpr TokenType mysql_triggerName_tokens_1608[] = {
    TokenType::qualifiedIdentifier
};

constexpr TokenType mysql_triggerRef_tokens_1609[] = {
    TokenType::qualifiedIdentifier
};

constexpr TokenType mysql_viewName_tokens_1610[] = {
    TokenType::qualifiedIdentifier
};

constexpr TokenType mysql_viewName_tokens_1611[] = {
    TokenType::dotIdentifier
};

constexpr TokenType mysql_viewRef_tokens_1612[] = {
    TokenType::qualifiedIdentifier
};

constexpr TokenType mysql_viewRef_tokens_1613[] = {
    TokenType::dotIdentifier
};

constexpr TokenType mysql_tablespaceName_tokens_1614[] = {
    TokenType::identifier
};

constexpr TokenType mysql_tablespaceRef_tokens_1615[] = {
    TokenType::identifier
};

constexpr TokenType mysql_logfileGroupName_tokens_1616[] = {
    TokenType::identifier
};

constexpr TokenType mysql_logfileGroupRef_tokens_1617[] = {
    TokenType::identifier
};

constexpr TokenType mysql_eventName_tokens_1618[] = {
    TokenType::qualifiedIdentifier
};

constexpr TokenType mysql_eventRef_tokens_1619[] = {
    TokenType::qualifiedIdentifier
};

constexpr TokenType mysql_udfName_tokens_1620[] = {
    TokenType::identifier
};

constexpr TokenType mysql_serverName_tokens_1621[] = {
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_serverRef_tokens_1622[] = {
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_engineRef_tokens_1623[] = {
    TokenType::textOrIdentifier
};

constexpr TokenType mysql_tableName_tokens_1624[] = {
    TokenType::qualifiedIdentifier
};

constexpr TokenType mysql_tableName_tokens_1625[] = {
    TokenType::dotIdentifier
};

constexpr TokenType mysql_filterTableRef_tokens_1626[] = {
    TokenType::schemaRef,
    TokenType::dotIdentifier
};

constexpr TokenType mysql_tableRefWithWildcard_tokens_1627[] = {
    TokenType::identifier,
    TokenType::DOT,
    TokenType::STAR
};

constexpr TokenType mysql_tableRefWithWildcard_tokens_1628[] = {
    TokenType::identifier,
    TokenType::dotIdentifier,
    TokenType::DOT,
    TokenType::STAR
};

constexpr TokenType mysql_tableRef_tokens_1629[] = {
    TokenType::qualifiedIdentifier
};

constexpr TokenType mysql_tableRef_tokens_1630[] = {
    TokenType::dotIdentifier
};

constexpr TokenType mysql_tableRefList_tokens_1631[] = {
    TokenType::tableRef,
    TokenType::COMMA,
    TokenType::tableRef
};

constexpr TokenType mysql_tableAliasRefList_tokens_1632[] = {
    TokenType::tableRefWithWildcard,
    TokenType::COMMA,
    TokenType::tableRefWithWildcard
};

constexpr TokenType mysql_parameterName_tokens_1633[] = {
    TokenType::identifier
};

constexpr TokenType mysql_labelIdentifier_tokens_1634[] = {
    TokenType::pureIdentifier
};

constexpr TokenType mysql_labelIdentifier_tokens_1635[] = {
    TokenType::labelKeyword
};

constexpr TokenType mysql_labelRef_tokens_1636[] = {
    TokenType::labelIdentifier
};

constexpr TokenType mysql_roleIdentifier_tokens_1637[] = {
    TokenType::pureIdentifier
};

constexpr TokenType mysql_roleIdentifier_tokens_1638[] = {
    TokenType::roleKeyword
};

constexpr TokenType mysql_pluginRef_tokens_1639[] = {
    TokenType::identifier
};

constexpr TokenType mysql_componentRef_tokens_1640[] = {
    TokenType::textStringLiteral
};

constexpr TokenType mysql_resourceGroupRef_tokens_1641[] = {
    TokenType::identifier
};

constexpr TokenType mysql_windowName_tokens_1642[] = {
    TokenType::identifier
};

constexpr TokenType mysql_pureIdentifier_tokens_1643[] = {
    TokenType::IDENTIFIER
};

constexpr TokenType mysql_pureIdentifier_tokens_1644[] = {
    TokenType::IDENTIFIER
};

constexpr TokenType mysql_pureIdentifier_tokens_1645[] = {
    TokenType::this,
    TokenType::isPureIdentifier,
    TokenType::STRING
};

constexpr TokenType mysql_identifier_tokens_1646[] = {
    TokenType::pureIdentifier
};

constexpr TokenType mysql_identifier_tokens_1647[] = {
    TokenType::identifierKeyword
};

constexpr TokenType mysql_identifierList_tokens_1648[] = {
    TokenType::identifier,
    TokenType::COMMA,
    TokenType::identifier
};

constexpr TokenType mysql_identifierListWithParentheses_tokens_1649[] = {
    TokenType::LPAREN,
    TokenType::identifierList,
    TokenType::RPAREN
};

constexpr TokenType mysql_qualifiedIdentifier_tokens_1650[] = {
    TokenType::identifier,
    TokenType::dotIdentifier
};

constexpr TokenType mysql_simpleIdentifier_tokens_1651[] = {
    TokenType::identifier,
    TokenType::dotIdentifier,
    TokenType::dotIdentifier
};

constexpr TokenType mysql_dotIdentifier_tokens_1652[] = {
    TokenType::DOT,
    TokenType::identifier
};

constexpr TokenType mysql_ulong_number_tokens_1653[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_ulong_number_tokens_1654[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_ulong_number_tokens_1655[] = {
    TokenType::LONG_NUMBER
};

constexpr TokenType mysql_ulong_number_tokens_1656[] = {
    TokenType::ULONGLONG_NUMBER
};

constexpr TokenType mysql_ulong_number_tokens_1657[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_ulong_number_tokens_1658[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_real_ulong_number_tokens_1659[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_real_ulong_number_tokens_1660[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_real_ulong_number_tokens_1661[] = {
    TokenType::LONG_NUMBER
};

constexpr TokenType mysql_real_ulong_number_tokens_1662[] = {
    TokenType::ULONGLONG_NUMBER
};

constexpr TokenType mysql_ulonglongNumber_tokens_1663[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_ulonglongNumber_tokens_1664[] = {
    TokenType::LONG_NUMBER
};

constexpr TokenType mysql_ulonglongNumber_tokens_1665[] = {
    TokenType::ULONGLONG_NUMBER
};

constexpr TokenType mysql_ulonglongNumber_tokens_1666[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_ulonglongNumber_tokens_1667[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_real_ulonglong_number_tokens_1668[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_real_ulonglong_number_tokens_1669[] = {
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::NUMBER
};

constexpr TokenType mysql_real_ulonglong_number_tokens_1670[] = {
    TokenType::ULONGLONG_NUMBER
};

constexpr TokenType mysql_real_ulonglong_number_tokens_1671[] = {
    TokenType::LONG_NUMBER
};

constexpr TokenType mysql_signedLiteral_tokens_1672[] = {
    TokenType::literal
};

constexpr TokenType mysql_signedLiteral_tokens_1673[] = {
    TokenType::PLUS,
    TokenType::ulong_number
};

constexpr TokenType mysql_signedLiteral_tokens_1674[] = {
    TokenType::MINUS,
    TokenType::ulong_number
};

constexpr TokenType mysql_signedLiteralOrNull_tokens_1675[] = {
    TokenType::signedLiteral
};

constexpr TokenType mysql_signedLiteralOrNull_tokens_1676[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::nullAsLiteral
};

constexpr TokenType mysql_literal_tokens_1677[] = {
    TokenType::textLiteral
};

constexpr TokenType mysql_literal_tokens_1678[] = {
    TokenType::numLiteral
};

constexpr TokenType mysql_literal_tokens_1679[] = {
    TokenType::temporalLiteral
};

constexpr TokenType mysql_literal_tokens_1680[] = {
    TokenType::nullLiteral
};

constexpr TokenType mysql_literal_tokens_1681[] = {
    TokenType::boolLiteral
};

constexpr TokenType mysql_literal_tokens_1682[] = {
    TokenType::UNDERSCORE_CHARSET,
    TokenType::NUMBER
};

constexpr TokenType mysql_literal_tokens_1683[] = {
    TokenType::UNDERSCORE_CHARSET,
    TokenType::NUMBER
};

constexpr TokenType mysql_literalOrNull_tokens_1684[] = {
    TokenType::literal
};

constexpr TokenType mysql_literalOrNull_tokens_1685[] = {
    TokenType::this,
    TokenType::isServerVersionGe80024,
    TokenType::nullAsLiteral
};

constexpr TokenType mysql_nullAsLiteral_tokens_1686[] = {
    TokenType::NULL_KW
};

constexpr TokenType mysql_stringList_tokens_1687[] = {
    TokenType::LPAREN,
    TokenType::textString,
    TokenType::COMMA,
    TokenType::textString,
    TokenType::RPAREN
};

constexpr TokenType mysql_textStringLiteral_tokens_1688[] = {
    TokenType::value,
    TokenType::STRING
};

constexpr TokenType mysql_textStringLiteral_tokens_1689[] = {
    TokenType::this,
    TokenType::isTextStringLiteral,
    TokenType::value,
    TokenType::STRING
};

constexpr TokenType mysql_textString_tokens_1690[] = {
    TokenType::textStringLiteral
};

constexpr TokenType mysql_textString_tokens_1691[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_textString_tokens_1692[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_textStringHash_tokens_1693[] = {
    TokenType::textStringLiteral
};

constexpr TokenType mysql_textStringHash_tokens_1694[] = {
    TokenType::this,
    TokenType::isServerVersionGe80017,
    TokenType::NUMBER
};

constexpr TokenType mysql_textLiteral_tokens_1695[] = {
    TokenType::UNDERSCORE_CHARSET,
    TokenType::textStringLiteral,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_textLiteral_tokens_1696[] = {
    TokenType::NCHAR_TEXT,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_textStringNoLinebreak_tokens_1697[] = {
    TokenType::textStringLiteral
};

constexpr TokenType mysql_textStringLiteralList_tokens_1698[] = {
    TokenType::textStringLiteral,
    TokenType::COMMA,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_numLiteral_tokens_1699[] = {
    TokenType::int64Literal
};

constexpr TokenType mysql_numLiteral_tokens_1700[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_numLiteral_tokens_1701[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_boolLiteral_tokens_1702[] = {
    TokenType::TRUE
};

constexpr TokenType mysql_boolLiteral_tokens_1703[] = {
    TokenType::FALSE
};

constexpr TokenType mysql_nullLiteral_tokens_1704[] = {
    TokenType::NULL_KW
};

constexpr TokenType mysql_nullLiteral_tokens_1705[] = {
    TokenType::NULL2
};

constexpr TokenType mysql_int64Literal_tokens_1706[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_int64Literal_tokens_1707[] = {
    TokenType::LONG_NUMBER
};

constexpr TokenType mysql_int64Literal_tokens_1708[] = {
    TokenType::ULONGLONG_NUMBER
};

constexpr TokenType mysql_temporalLiteral_tokens_1709[] = {
    TokenType::DATE,
    TokenType::STRING
};

constexpr TokenType mysql_temporalLiteral_tokens_1710[] = {
    TokenType::TIME,
    TokenType::STRING
};

constexpr TokenType mysql_temporalLiteral_tokens_1711[] = {
    TokenType::TIMESTAMP,
    TokenType::STRING
};

constexpr TokenType mysql_floatOptions_tokens_1712[] = {
    TokenType::fieldLength
};

constexpr TokenType mysql_floatOptions_tokens_1713[] = {
    TokenType::precision
};

constexpr TokenType mysql_standardFloatOptions_tokens_1714[] = {
    TokenType::precision
};

constexpr TokenType mysql_precision_tokens_1715[] = {
    TokenType::LPAREN,
    TokenType::NUMBER,
    TokenType::COMMA,
    TokenType::NUMBER,
    TokenType::RPAREN
};

constexpr TokenType mysql_textOrIdentifier_tokens_1716[] = {
    TokenType::identifier
};

constexpr TokenType mysql_textOrIdentifier_tokens_1717[] = {
    TokenType::textStringLiteral
};

constexpr TokenType mysql_lValueIdentifier_tokens_1718[] = {
    TokenType::pureIdentifier
};

constexpr TokenType mysql_lValueIdentifier_tokens_1719[] = {
    TokenType::lValueKeyword
};

constexpr TokenType mysql_roleIdentifierOrText_tokens_1720[] = {
    TokenType::roleIdentifier
};

constexpr TokenType mysql_roleIdentifierOrText_tokens_1721[] = {
    TokenType::textStringLiteral
};

constexpr TokenType mysql_sizeNumber_tokens_1722[] = {
    TokenType::real_ulonglong_number
};

constexpr TokenType mysql_sizeNumber_tokens_1723[] = {
    TokenType::pureIdentifier
};

constexpr TokenType mysql_parentheses_tokens_1724[] = {
    TokenType::LPAREN,
    TokenType::RPAREN
};

constexpr TokenType mysql_equal_tokens_1725[] = {
    TokenType::EQ
};

constexpr TokenType mysql_equal_tokens_1726[] = {
    TokenType::EQ
};

constexpr TokenType mysql_optionType_tokens_1727[] = {
    TokenType::PERSIST
};

constexpr TokenType mysql_optionType_tokens_1728[] = {
    TokenType::PERSIST_ONLY
};

constexpr TokenType mysql_optionType_tokens_1729[] = {
    TokenType::GLOBAL
};

constexpr TokenType mysql_optionType_tokens_1730[] = {
    TokenType::LOCAL
};

constexpr TokenType mysql_optionType_tokens_1731[] = {
    TokenType::SESSION
};

constexpr TokenType mysql_rvalueSystemVariableType_tokens_1732[] = {
    TokenType::GLOBAL,
    TokenType::DOT
};

constexpr TokenType mysql_rvalueSystemVariableType_tokens_1733[] = {
    TokenType::LOCAL,
    TokenType::DOT
};

constexpr TokenType mysql_rvalueSystemVariableType_tokens_1734[] = {
    TokenType::SESSION,
    TokenType::DOT
};

constexpr TokenType mysql_setVarIdentType_tokens_1735[] = {
    TokenType::PERSIST,
    TokenType::DOT
};

constexpr TokenType mysql_setVarIdentType_tokens_1736[] = {
    TokenType::PERSIST_ONLY,
    TokenType::DOT
};

constexpr TokenType mysql_setVarIdentType_tokens_1737[] = {
    TokenType::GLOBAL,
    TokenType::DOT
};

constexpr TokenType mysql_setVarIdentType_tokens_1738[] = {
    TokenType::LOCAL,
    TokenType::DOT
};

constexpr TokenType mysql_setVarIdentType_tokens_1739[] = {
    TokenType::SESSION,
    TokenType::DOT
};

constexpr TokenType mysql_jsonAttribute_tokens_1740[] = {
    TokenType::textStringLiteral
};

constexpr TokenType mysql_identifierKeyword_tokens_1741[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::labelKeyword
};

constexpr TokenType mysql_identifierKeyword_tokens_1742[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::roleOrIdentifierKeyword
};

constexpr TokenType mysql_identifierKeyword_tokens_1743[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::EXECUTE
};

constexpr TokenType mysql_identifierKeyword_tokens_1744[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::SHUTDOWN
};

constexpr TokenType mysql_identifierKeyword_tokens_1745[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::this,
    TokenType::isServerVersionGe80011,
    TokenType::STAR
};

constexpr TokenType mysql_identifierKeyword_tokens_1746[] = {
    TokenType::identifierKeywordsUnambiguous
};

constexpr TokenType mysql_identifierKeyword_tokens_1747[] = {
    TokenType::identifierKeywordsAmbiguous1RolesAndLabels
};

constexpr TokenType mysql_identifierKeyword_tokens_1748[] = {
    TokenType::identifierKeywordsAmbiguous2Labels
};

constexpr TokenType mysql_identifierKeyword_tokens_1749[] = {
    TokenType::identifierKeywordsAmbiguous3Roles
};

constexpr TokenType mysql_identifierKeyword_tokens_1750[] = {
    TokenType::identifierKeywordsAmbiguous4SystemVariables
};

constexpr TokenType mysql_identifierKeywordsAmbiguous1RolesAndLabels_tokens_1751[] = {
    TokenType::EXECUTE
};

constexpr TokenType mysql_identifierKeywordsAmbiguous1RolesAndLabels_tokens_1752[] = {
    TokenType::STAR
};

constexpr TokenType mysql_identifierKeywordsAmbiguous1RolesAndLabels_tokens_1753[] = {
    TokenType::SHUTDOWN
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1754[] = {
    TokenType::ASCII
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1755[] = {
    TokenType::BEGIN
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1756[] = {
    TokenType::BYTE
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1757[] = {
    TokenType::CACHE
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1758[] = {
    TokenType::CHARSET
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1759[] = {
    TokenType::CHECKSUM
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1760[] = {
    TokenType::CLONE
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1761[] = {
    TokenType::COMMENT
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1762[] = {
    TokenType::COMMIT
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1763[] = {
    TokenType::CONTAINS
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1764[] = {
    TokenType::DEALLOCATE
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1765[] = {
    TokenType::DO
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1766[] = {
    TokenType::END
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1767[] = {
    TokenType::FLUSH
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1768[] = {
    TokenType::FOLLOWS
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1769[] = {
    TokenType::HANDLER
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1770[] = {
    TokenType::HELP
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1771[] = {
    TokenType::IMPORT
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1772[] = {
    TokenType::INSTALL
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1773[] = {
    TokenType::LANGUAGE
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1774[] = {
    TokenType::NO
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1775[] = {
    TokenType::PRECEDES
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1776[] = {
    TokenType::PREPARE
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1777[] = {
    TokenType::REPAIR
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1778[] = {
    TokenType::RESET
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1779[] = {
    TokenType::ROLLBACK
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1780[] = {
    TokenType::SAVEPOINT
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1781[] = {
    TokenType::SIGNED
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1782[] = {
    TokenType::SLAVE
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1783[] = {
    TokenType::STAR
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1784[] = {
    TokenType::STOP
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1785[] = {
    TokenType::TRUNCATE
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1786[] = {
    TokenType::UNICODE
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1787[] = {
    TokenType::UNINSTALL
};

constexpr TokenType mysql_identifierKeywordsAmbiguous2Labels_tokens_1788[] = {
    TokenType::XA
};

constexpr TokenType mysql_labelKeyword_tokens_1789[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::roleOrLabelKeyword
};

constexpr TokenType mysql_labelKeyword_tokens_1790[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::EVENT
};

constexpr TokenType mysql_labelKeyword_tokens_1791[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::FILE
};

constexpr TokenType mysql_labelKeyword_tokens_1792[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::NONE
};

constexpr TokenType mysql_labelKeyword_tokens_1793[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::PROCESS
};

constexpr TokenType mysql_labelKeyword_tokens_1794[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::PROXY
};

constexpr TokenType mysql_labelKeyword_tokens_1795[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::RELOAD
};

constexpr TokenType mysql_labelKeyword_tokens_1796[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::REPLICATION
};

constexpr TokenType mysql_labelKeyword_tokens_1797[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::RESOURCE
};

constexpr TokenType mysql_labelKeyword_tokens_1798[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::SUPER
};

constexpr TokenType mysql_labelKeyword_tokens_1799[] = {
    TokenType::identifierKeywordsUnambiguous
};

constexpr TokenType mysql_labelKeyword_tokens_1800[] = {
    TokenType::identifierKeywordsAmbiguous3Roles
};

constexpr TokenType mysql_labelKeyword_tokens_1801[] = {
    TokenType::identifierKeywordsAmbiguous4SystemVariables
};

constexpr TokenType mysql_identifierKeywordsAmbiguous3Roles_tokens_1802[] = {
    TokenType::EVENT
};

constexpr TokenType mysql_identifierKeywordsAmbiguous3Roles_tokens_1803[] = {
    TokenType::FILE
};

constexpr TokenType mysql_identifierKeywordsAmbiguous3Roles_tokens_1804[] = {
    TokenType::NONE
};

constexpr TokenType mysql_identifierKeywordsAmbiguous3Roles_tokens_1805[] = {
    TokenType::PROCESS
};

constexpr TokenType mysql_identifierKeywordsAmbiguous3Roles_tokens_1806[] = {
    TokenType::PROXY
};

constexpr TokenType mysql_identifierKeywordsAmbiguous3Roles_tokens_1807[] = {
    TokenType::RELOAD
};

constexpr TokenType mysql_identifierKeywordsAmbiguous3Roles_tokens_1808[] = {
    TokenType::REPLICATION
};

constexpr TokenType mysql_identifierKeywordsAmbiguous3Roles_tokens_1809[] = {
    TokenType::RESOURCE
};

constexpr TokenType mysql_identifierKeywordsAmbiguous3Roles_tokens_1810[] = {
    TokenType::SUPER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1811[] = {
    TokenType::ACTION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1812[] = {
    TokenType::ACCOUNT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1813[] = {
    TokenType::ACTIVE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1814[] = {
    TokenType::ADDDATE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1815[] = {
    TokenType::ADMIN
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1816[] = {
    TokenType::AFTER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1817[] = {
    TokenType::AGAINST
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1818[] = {
    TokenType::AGGREGATE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1819[] = {
    TokenType::ALGORITHM
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1820[] = {
    TokenType::ALWAYS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1821[] = {
    TokenType::ANY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1822[] = {
    TokenType::AT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1823[] = {
    TokenType::ATTRIBUTE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1824[] = {
    TokenType::AUTHENTICATION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1825[] = {
    TokenType::AUTOEXTEND_SIZE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1826[] = {
    TokenType::AUTO_INCREMENT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1827[] = {
    TokenType::AVG_ROW_LENGTH
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1828[] = {
    TokenType::AVG
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1829[] = {
    TokenType::BACKUP
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1830[] = {
    TokenType::BINLOG
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1831[] = {
    TokenType::BIT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1832[] = {
    TokenType::BLOCK
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1833[] = {
    TokenType::BOOLEAN
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1834[] = {
    TokenType::BOOL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1835[] = {
    TokenType::BTREE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1836[] = {
    TokenType::BUCKETS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1837[] = {
    TokenType::CASCADED
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1838[] = {
    TokenType::CATALOG_NAME
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1839[] = {
    TokenType::CHAIN
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1840[] = {
    TokenType::CHALLENGE_RESPONSE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1841[] = {
    TokenType::CHANGED
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1842[] = {
    TokenType::CHANNEL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1843[] = {
    TokenType::CIPHER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1844[] = {
    TokenType::CLASS_ORIGIN
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1845[] = {
    TokenType::CLIENT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1846[] = {
    TokenType::CLOSE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1847[] = {
    TokenType::COALESCE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1848[] = {
    TokenType::CODE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1849[] = {
    TokenType::COLLATION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1850[] = {
    TokenType::COLUMNS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1851[] = {
    TokenType::COLUMN_FORMAT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1852[] = {
    TokenType::COLUMN_NAME
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1853[] = {
    TokenType::COMMITTED
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1854[] = {
    TokenType::COMPACT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1855[] = {
    TokenType::COMPLETION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1856[] = {
    TokenType::COMPONENT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1857[] = {
    TokenType::COMPRESSED
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1858[] = {
    TokenType::COMPRESSION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1859[] = {
    TokenType::CONCURRENT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1860[] = {
    TokenType::CONNECTION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1861[] = {
    TokenType::CONSISTENT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1862[] = {
    TokenType::CONSTRAINT_CATALOG
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1863[] = {
    TokenType::CONSTRAINT_NAME
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1864[] = {
    TokenType::CONSTRAINT_SCHEMA
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1865[] = {
    TokenType::CONTEXT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1866[] = {
    TokenType::CPU
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1867[] = {
    TokenType::CURRENT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1868[] = {
    TokenType::CURSOR_NAME
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1869[] = {
    TokenType::DATAFILE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1870[] = {
    TokenType::DATA
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1871[] = {
    TokenType::DATETIME
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1872[] = {
    TokenType::DATE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1873[] = {
    TokenType::DAY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1874[] = {
    TokenType::DEFAULT_AUTH
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1875[] = {
    TokenType::DEFINER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1876[] = {
    TokenType::DEFINITION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1877[] = {
    TokenType::DELAY_KEY_WRITE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1878[] = {
    TokenType::DESCRIPTION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1879[] = {
    TokenType::DIAGNOSTICS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1880[] = {
    TokenType::DIRECTORY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1881[] = {
    TokenType::DISABLE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1882[] = {
    TokenType::DISCARD
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1883[] = {
    TokenType::DISK
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1884[] = {
    TokenType::DUMPFILE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1885[] = {
    TokenType::DUPLICATE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1886[] = {
    TokenType::DYNAMIC
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1887[] = {
    TokenType::ENABLE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1888[] = {
    TokenType::ENCRYPTION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1889[] = {
    TokenType::ENDS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1890[] = {
    TokenType::ENFORCED
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1891[] = {
    TokenType::ENGINES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1892[] = {
    TokenType::ENGINE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1893[] = {
    TokenType::ENUM
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1894[] = {
    TokenType::ERRORS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1895[] = {
    TokenType::ERROR
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1896[] = {
    TokenType::ESCAPE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1897[] = {
    TokenType::EVENTS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1898[] = {
    TokenType::EVERY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1899[] = {
    TokenType::EXCHANGE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1900[] = {
    TokenType::EXCLUDE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1901[] = {
    TokenType::EXPANSION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1902[] = {
    TokenType::EXPIRE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1903[] = {
    TokenType::EXPORT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1904[] = {
    TokenType::EXTENDED
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1905[] = {
    TokenType::EXTENT_SIZE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1906[] = {
    TokenType::FACTOR
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1907[] = {
    TokenType::FAST
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1908[] = {
    TokenType::FAULTS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1909[] = {
    TokenType::FILE_BLOCK_SIZE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1910[] = {
    TokenType::FILTER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1911[] = {
    TokenType::FINISH
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1912[] = {
    TokenType::FIRST
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1913[] = {
    TokenType::FIXED
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1914[] = {
    TokenType::FOLLOWING
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1915[] = {
    TokenType::FORMAT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1916[] = {
    TokenType::FOUND
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1917[] = {
    TokenType::FULL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1918[] = {
    TokenType::GENERAL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1919[] = {
    TokenType::GEOMETRYCOLLECTION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1920[] = {
    TokenType::GEOMETRY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1921[] = {
    TokenType::GET_FORMAT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1922[] = {
    TokenType::GET_MASTER_PUBLIC_KEY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1923[] = {
    TokenType::GET_SOURCE_PUBLIC_KEY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1924[] = {
    TokenType::GRANTS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1925[] = {
    TokenType::GROUP_REPLICATION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1926[] = {
    TokenType::GTID_ONLY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1927[] = {
    TokenType::HASH
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1928[] = {
    TokenType::HISTOGRAM
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1929[] = {
    TokenType::HISTORY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1930[] = {
    TokenType::HOSTS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1931[] = {
    TokenType::HOST
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1932[] = {
    TokenType::HOUR
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1933[] = {
    TokenType::IDENTIFIED
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1934[] = {
    TokenType::IGNORE_SERVER_IDS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1935[] = {
    TokenType::INACTIVE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1936[] = {
    TokenType::INDEXES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1937[] = {
    TokenType::INITIAL_SIZE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1938[] = {
    TokenType::INITIAL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1939[] = {
    TokenType::INITIATE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1940[] = {
    TokenType::INSERT_METHOD
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1941[] = {
    TokenType::INSTANCE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1942[] = {
    TokenType::INVISIBLE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1943[] = {
    TokenType::INVOKER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1944[] = {
    TokenType::IO
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1945[] = {
    TokenType::IPC
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1946[] = {
    TokenType::ISOLATION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1947[] = {
    TokenType::ISSUER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1948[] = {
    TokenType::JSON
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1949[] = {
    TokenType::JSON_VALUE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1950[] = {
    TokenType::KEY_BLOCK_SIZE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1951[] = {
    TokenType::KEYRING
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1952[] = {
    TokenType::LAST
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1953[] = {
    TokenType::LEAVES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1954[] = {
    TokenType::LESS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1955[] = {
    TokenType::LEVEL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1956[] = {
    TokenType::LINESTRING
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1957[] = {
    TokenType::LIST
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1958[] = {
    TokenType::LOCKED
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1959[] = {
    TokenType::LOCKS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1960[] = {
    TokenType::LOGFILE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1961[] = {
    TokenType::LOGS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1962[] = {
    TokenType::MASTER_AUTO_POSITION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1963[] = {
    TokenType::MASTER_COMPRESSION_ALGORITHM
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1964[] = {
    TokenType::MASTER_CONNECT_RETRY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1965[] = {
    TokenType::MASTER_DELAY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1966[] = {
    TokenType::MASTER_HEARTBEAT_PERIOD
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1967[] = {
    TokenType::MASTER_HOST
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1968[] = {
    TokenType::NETWORK_NAMESPACE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1969[] = {
    TokenType::MASTER_LOG_FILE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1970[] = {
    TokenType::MASTER_LOG_POS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1971[] = {
    TokenType::MASTER_PASSWORD
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1972[] = {
    TokenType::MASTER_PORT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1973[] = {
    TokenType::MASTER_PUBLIC_KEY_PATH
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1974[] = {
    TokenType::MASTER_RETRY_COUNT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1975[] = {
    TokenType::MASTER_SSL_CAPATH
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1976[] = {
    TokenType::MASTER_SSL_CA
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1977[] = {
    TokenType::MASTER_SSL_CERT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1978[] = {
    TokenType::MASTER_SSL_CIPHER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1979[] = {
    TokenType::MASTER_SSL_CRLPATH
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1980[] = {
    TokenType::MASTER_SSL_CRL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1981[] = {
    TokenType::MASTER_SSL_KEY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1982[] = {
    TokenType::MASTER_SSL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1983[] = {
    TokenType::MASTER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1984[] = {
    TokenType::MASTER_TLS_CIPHERSUITES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1985[] = {
    TokenType::MASTER_TLS_VERSION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1986[] = {
    TokenType::MASTER_USER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1987[] = {
    TokenType::MASTER_ZSTD_COMPRESSION_LEVEL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1988[] = {
    TokenType::MAX_CONNECTIONS_PER_HOUR
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1989[] = {
    TokenType::MAX_QUERIES_PER_HOUR
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1990[] = {
    TokenType::MAX_ROWS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1991[] = {
    TokenType::MAX_SIZE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1992[] = {
    TokenType::MAX_UPDATES_PER_HOUR
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1993[] = {
    TokenType::MAX_USER_CONNECTIONS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1994[] = {
    TokenType::MEDIUM
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1995[] = {
    TokenType::MEMORY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1996[] = {
    TokenType::MERGE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1997[] = {
    TokenType::MESSAGE_TEXT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1998[] = {
    TokenType::MICROSECOND
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_1999[] = {
    TokenType::MIGRATE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2000[] = {
    TokenType::MINUTE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2001[] = {
    TokenType::MIN_ROWS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2002[] = {
    TokenType::MODE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2003[] = {
    TokenType::MODIFY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2004[] = {
    TokenType::MONTH
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2005[] = {
    TokenType::STAR
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2006[] = {
    TokenType::STAR
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2007[] = {
    TokenType::STAR
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2008[] = {
    TokenType::MUTEX
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2009[] = {
    TokenType::MYSQL_ERRNO
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2010[] = {
    TokenType::NAMES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2011[] = {
    TokenType::NAME
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2012[] = {
    TokenType::NATIONAL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2013[] = {
    TokenType::NCHAR
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2014[] = {
    TokenType::NDBCLUSTER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2015[] = {
    TokenType::NESTED
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2016[] = {
    TokenType::NEVER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2017[] = {
    TokenType::NEW
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2018[] = {
    TokenType::NEXT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2019[] = {
    TokenType::NODEGROUP
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2020[] = {
    TokenType::NOWAIT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2021[] = {
    TokenType::NO_WAIT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2022[] = {
    TokenType::NULLS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2023[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2024[] = {
    TokenType::NVARCHAR
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2025[] = {
    TokenType::OFFSET
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2026[] = {
    TokenType::OJ
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2027[] = {
    TokenType::OLD
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2028[] = {
    TokenType::ONE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2029[] = {
    TokenType::ONLY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2030[] = {
    TokenType::OPEN
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2031[] = {
    TokenType::OPTIONAL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2032[] = {
    TokenType::OPTIONS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2033[] = {
    TokenType::ORDINALITY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2034[] = {
    TokenType::ORGANIZATION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2035[] = {
    TokenType::OTHERS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2036[] = {
    TokenType::OWNER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2037[] = {
    TokenType::PACK_KEYS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2038[] = {
    TokenType::PAGE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2039[] = {
    TokenType::PARSER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2040[] = {
    TokenType::PARTIAL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2041[] = {
    TokenType::PARTITIONING
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2042[] = {
    TokenType::PARTITIONS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2043[] = {
    TokenType::PASSWORD
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2044[] = {
    TokenType::PATH
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2045[] = {
    TokenType::PHASE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2046[] = {
    TokenType::PLUGINS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2047[] = {
    TokenType::PLUGIN_DIR
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2048[] = {
    TokenType::PLUGIN
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2049[] = {
    TokenType::POINT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2050[] = {
    TokenType::POLYGON
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2051[] = {
    TokenType::PORT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2052[] = {
    TokenType::PRECEDING
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2053[] = {
    TokenType::PRESERVE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2054[] = {
    TokenType::PREV
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2055[] = {
    TokenType::PRIVILEGES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2056[] = {
    TokenType::PRIVILEGE_CHECKS_USER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2057[] = {
    TokenType::PROCESSLIST
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2058[] = {
    TokenType::PROFILES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2059[] = {
    TokenType::PROFILE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2060[] = {
    TokenType::QUARTER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2061[] = {
    TokenType::QUERY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2062[] = {
    TokenType::QUICK
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2063[] = {
    TokenType::READ_ONLY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2064[] = {
    TokenType::REBUILD
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2065[] = {
    TokenType::RECOVER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2066[] = {
    TokenType::REDO_BUFFER_SIZE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2067[] = {
    TokenType::REDUNDANT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2068[] = {
    TokenType::REFERENCE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2069[] = {
    TokenType::REGISTRATION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2070[] = {
    TokenType::RELAY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2071[] = {
    TokenType::RELAYLOG
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2072[] = {
    TokenType::RELAY_LOG_FILE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2073[] = {
    TokenType::RELAY_LOG_POS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2074[] = {
    TokenType::RELAY_THREAD
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2075[] = {
    TokenType::REMOVE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2076[] = {
    TokenType::ASSIGN_GTIDS_TO_ANONYMOUS_TRANSACTIONS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2077[] = {
    TokenType::REORGANIZE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2078[] = {
    TokenType::REPEATABLE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2079[] = {
    TokenType::REPLICAS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2080[] = {
    TokenType::REPLICATE_DO_DB
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2081[] = {
    TokenType::REPLICATE_DO_TABLE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2082[] = {
    TokenType::REPLICATE_IGNORE_DB
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2083[] = {
    TokenType::REPLICATE_IGNORE_TABLE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2084[] = {
    TokenType::REPLICATE_REWRITE_DB
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2085[] = {
    TokenType::REPLICATE_WILD_DO_TABLE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2086[] = {
    TokenType::REPLICATE_WILD_IGNORE_TABLE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2087[] = {
    TokenType::REPLICA
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2088[] = {
    TokenType::USER_RESOURCES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2089[] = {
    TokenType::RESPECT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2090[] = {
    TokenType::RESTORE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2091[] = {
    TokenType::RESUME
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2092[] = {
    TokenType::RETAIN
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2093[] = {
    TokenType::RETURNED_SQLSTATE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2094[] = {
    TokenType::RETURNING
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2095[] = {
    TokenType::RETURNS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2096[] = {
    TokenType::REUSE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2097[] = {
    TokenType::REVERSE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2098[] = {
    TokenType::ROLE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2099[] = {
    TokenType::ROLLUP
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2100[] = {
    TokenType::ROTATE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2101[] = {
    TokenType::ROUTINE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2102[] = {
    TokenType::ROW_COUNT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2103[] = {
    TokenType::ROW_FORMAT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2104[] = {
    TokenType::RTREE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2105[] = {
    TokenType::SCHEDULE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2106[] = {
    TokenType::SCHEMA_NAME
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2107[] = {
    TokenType::SECONDARY_ENGINE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2108[] = {
    TokenType::SECONDARY_ENGINE_ATTRIBUTE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2109[] = {
    TokenType::SECONDARY_LOAD
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2110[] = {
    TokenType::SECONDARY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2111[] = {
    TokenType::SECONDARY_UNLOAD
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2112[] = {
    TokenType::SECOND
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2113[] = {
    TokenType::SECURITY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2114[] = {
    TokenType::SERIALIZABLE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2115[] = {
    TokenType::SERIAL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2116[] = {
    TokenType::SERVER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2117[] = {
    TokenType::SHARE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2118[] = {
    TokenType::SIMPLE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2119[] = {
    TokenType::SKIP
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2120[] = {
    TokenType::SLOW
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2121[] = {
    TokenType::SNAPSHOT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2122[] = {
    TokenType::SOCKET
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2123[] = {
    TokenType::SONAME
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2124[] = {
    TokenType::SOUNDS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2125[] = {
    TokenType::SOURCE_AUTO_POSITION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2126[] = {
    TokenType::SOURCE_BIND
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2127[] = {
    TokenType::SOURCE_COMPRESSION_ALGORITHM
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2128[] = {
    TokenType::SOURCE_CONNECTION_AUTO_FAILOVER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2129[] = {
    TokenType::SOURCE_CONNECT_RETRY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2130[] = {
    TokenType::SOURCE_DELAY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2131[] = {
    TokenType::SOURCE_HEARTBEAT_PERIOD
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2132[] = {
    TokenType::SOURCE_HOST
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2133[] = {
    TokenType::SOURCE_LOG_FILE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2134[] = {
    TokenType::SOURCE_LOG_POS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2135[] = {
    TokenType::SOURCE_PASSWORD
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2136[] = {
    TokenType::SOURCE_PORT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2137[] = {
    TokenType::SOURCE_PUBLIC_KEY_PATH
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2138[] = {
    TokenType::SOURCE_RETRY_COUNT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2139[] = {
    TokenType::SOURCE_SSL_CAPATH
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2140[] = {
    TokenType::SOURCE_SSL_CA
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2141[] = {
    TokenType::SOURCE_SSL_CERT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2142[] = {
    TokenType::SOURCE_SSL_CIPHER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2143[] = {
    TokenType::SOURCE_SSL_CRLPATH
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2144[] = {
    TokenType::SOURCE_SSL_CRL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2145[] = {
    TokenType::SOURCE_SSL_KEY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2146[] = {
    TokenType::SOURCE_SSL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2147[] = {
    TokenType::SOURCE_SSL_VERIFY_SERVER_CERT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2148[] = {
    TokenType::SOURCE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2149[] = {
    TokenType::SOURCE_TLS_CIPHERSUITES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2150[] = {
    TokenType::SOURCE_TLS_VERSION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2151[] = {
    TokenType::SOURCE_USER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2152[] = {
    TokenType::SOURCE_ZSTD_COMPRESSION_LEVEL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2153[] = {
    TokenType::SQL_AFTER_GTIDS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2154[] = {
    TokenType::SQL_AFTER_MTS_GAPS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2155[] = {
    TokenType::SQL_BEFORE_GTIDS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2156[] = {
    TokenType::SQL_BUFFER_RESULT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2157[] = {
    TokenType::SQL_NO_CACHE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2158[] = {
    TokenType::SQL_THREAD
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2159[] = {
    TokenType::SRID
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2160[] = {
    TokenType::STACKED
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2161[] = {
    TokenType::STAR
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2162[] = {
    TokenType::STATS_AUTO_RECALC
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2163[] = {
    TokenType::STATS_PERSISTENT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2164[] = {
    TokenType::STATS_SAMPLE_PAGES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2165[] = {
    TokenType::STATUS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2166[] = {
    TokenType::STORAGE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2167[] = {
    TokenType::STRING
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2168[] = {
    TokenType::ST_COLLECT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2169[] = {
    TokenType::SUBCLASS_ORIGIN
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2170[] = {
    TokenType::SUBDATE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2171[] = {
    TokenType::SUBJECT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2172[] = {
    TokenType::SUBPARTITIONS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2173[] = {
    TokenType::SUBPARTITION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2174[] = {
    TokenType::SUSPEND
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2175[] = {
    TokenType::SWAPS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2176[] = {
    TokenType::SWITCHES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2177[] = {
    TokenType::TABLES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2178[] = {
    TokenType::TABLESPACE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2179[] = {
    TokenType::TABLE_CHECKSUM
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2180[] = {
    TokenType::TABLE_NAME
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2181[] = {
    TokenType::TEMPORARY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2182[] = {
    TokenType::TEMPTABLE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2183[] = {
    TokenType::TEXT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2184[] = {
    TokenType::THAN
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2185[] = {
    TokenType::THREAD_PRIORITY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2186[] = {
    TokenType::TIES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2187[] = {
    TokenType::TIMESTAMPADD
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2188[] = {
    TokenType::TIMESTAMPDIFF
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2189[] = {
    TokenType::TIMESTAMP
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2190[] = {
    TokenType::TIME
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2191[] = {
    TokenType::TLS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2192[] = {
    TokenType::TRANSACTION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2193[] = {
    TokenType::TRIGGERS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2194[] = {
    TokenType::TYPES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2195[] = {
    TokenType::TYPE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2196[] = {
    TokenType::UNBOUNDED
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2197[] = {
    TokenType::UNCOMMITTED
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2198[] = {
    TokenType::UNDEFINED
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2199[] = {
    TokenType::UNDOFILE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2200[] = {
    TokenType::UNDO_BUFFER_SIZE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2201[] = {
    TokenType::UNKNOWN
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2202[] = {
    TokenType::UNREGISTER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2203[] = {
    TokenType::UNTIL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2204[] = {
    TokenType::UPGRADE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2205[] = {
    TokenType::USER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2206[] = {
    TokenType::USE_FRM
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2207[] = {
    TokenType::VALIDATION
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2208[] = {
    TokenType::VALUE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2209[] = {
    TokenType::VARIABLES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2210[] = {
    TokenType::VCPU
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2211[] = {
    TokenType::VIEW
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2212[] = {
    TokenType::VISIBLE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2213[] = {
    TokenType::WAIT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2214[] = {
    TokenType::WARNINGS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2215[] = {
    TokenType::WEEK
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2216[] = {
    TokenType::WEIGHT_STRING
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2217[] = {
    TokenType::WITHOUT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2218[] = {
    TokenType::WORK
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2219[] = {
    TokenType::WRAPPER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2220[] = {
    TokenType::X509
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2221[] = {
    TokenType::XID
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2222[] = {
    TokenType::XML
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2223[] = {
    TokenType::YEAR
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2224[] = {
    TokenType::ZONE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2225[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::ARRAY
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2226[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::FAILED_LOGIN_ATTEMPTS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2227[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::MASTER_COMPRESSION_ALGORITHM
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2228[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::MASTER_TLS_CIPHERSUITES
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2229[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::MASTER_ZSTD_COMPRESSION_LEVEL
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2230[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::MEMBER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2231[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::OFF
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2232[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::PASSWORD_LOCK_TIME
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2233[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::PRIVILEGE_CHECKS_USER
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2234[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::RANDOM
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2235[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::REQUIRE_ROW_FORMAT
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2236[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::REQUIRE_TABLE_PRIMARY_KEY_CHECK
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2237[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::STREAM
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2238[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::TIMESTAMP
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2239[] = {
    TokenType::this,
    TokenType::isServerVersionGe80019,
    TokenType::TIME
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2240[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::BULK
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2241[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::GENERATE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2242[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::GTIDS
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2243[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::LOG
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2244[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::PARSE_TREE
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2245[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::S3
};

constexpr TokenType mysql_identifierKeywordsUnambiguous_tokens_2246[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::BERNOULLI
};

constexpr TokenType mysql_roleKeyword_tokens_2247[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::roleOrLabelKeyword
};

constexpr TokenType mysql_roleKeyword_tokens_2248[] = {
    TokenType::this,
    TokenType::isServerVersionLt80017,
    TokenType::roleOrIdentifierKeyword
};

constexpr TokenType mysql_roleKeyword_tokens_2249[] = {
    TokenType::identifierKeywordsUnambiguous
};

constexpr TokenType mysql_roleKeyword_tokens_2250[] = {
    TokenType::identifierKeywordsAmbiguous2Labels
};

constexpr TokenType mysql_roleKeyword_tokens_2251[] = {
    TokenType::identifierKeywordsAmbiguous4SystemVariables
};

constexpr TokenType mysql_lValueKeyword_tokens_2252[] = {
    TokenType::identifierKeywordsUnambiguous
};

constexpr TokenType mysql_lValueKeyword_tokens_2253[] = {
    TokenType::identifierKeywordsAmbiguous1RolesAndLabels
};

constexpr TokenType mysql_lValueKeyword_tokens_2254[] = {
    TokenType::identifierKeywordsAmbiguous2Labels
};

constexpr TokenType mysql_lValueKeyword_tokens_2255[] = {
    TokenType::identifierKeywordsAmbiguous3Roles
};

constexpr TokenType mysql_identifierKeywordsAmbiguous4SystemVariables_tokens_2256[] = {
    TokenType::GLOBAL
};

constexpr TokenType mysql_identifierKeywordsAmbiguous4SystemVariables_tokens_2257[] = {
    TokenType::LOCAL
};

constexpr TokenType mysql_identifierKeywordsAmbiguous4SystemVariables_tokens_2258[] = {
    TokenType::PERSIST
};

constexpr TokenType mysql_identifierKeywordsAmbiguous4SystemVariables_tokens_2259[] = {
    TokenType::PERSIST_ONLY
};

constexpr TokenType mysql_identifierKeywordsAmbiguous4SystemVariables_tokens_2260[] = {
    TokenType::SESSION
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2261[] = {
    TokenType::ACCOUNT
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2262[] = {
    TokenType::ASCII
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2263[] = {
    TokenType::ALWAYS
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2264[] = {
    TokenType::BACKUP
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2265[] = {
    TokenType::BEGIN
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2266[] = {
    TokenType::BYTE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2267[] = {
    TokenType::CACHE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2268[] = {
    TokenType::CHARSET
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2269[] = {
    TokenType::CHECKSUM
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2270[] = {
    TokenType::CLONE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2271[] = {
    TokenType::CLOSE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2272[] = {
    TokenType::COMMENT
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2273[] = {
    TokenType::COMMIT
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2274[] = {
    TokenType::CONTAINS
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2275[] = {
    TokenType::DEALLOCATE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2276[] = {
    TokenType::DO
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2277[] = {
    TokenType::END
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2278[] = {
    TokenType::FLUSH
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2279[] = {
    TokenType::FOLLOWS
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2280[] = {
    TokenType::FORMAT
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2281[] = {
    TokenType::GROUP_REPLICATION
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2282[] = {
    TokenType::HANDLER
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2283[] = {
    TokenType::HELP
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2284[] = {
    TokenType::HOST
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2285[] = {
    TokenType::INSTALL
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2286[] = {
    TokenType::INVISIBLE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2287[] = {
    TokenType::LANGUAGE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2288[] = {
    TokenType::NO
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2289[] = {
    TokenType::OPEN
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2290[] = {
    TokenType::OPTIONS
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2291[] = {
    TokenType::OWNER
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2292[] = {
    TokenType::PARSER
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2293[] = {
    TokenType::PARTITION
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2294[] = {
    TokenType::PORT
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2295[] = {
    TokenType::PRECEDES
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2296[] = {
    TokenType::PREPARE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2297[] = {
    TokenType::REMOVE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2298[] = {
    TokenType::REPAIR
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2299[] = {
    TokenType::RESET
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2300[] = {
    TokenType::RESTORE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2301[] = {
    TokenType::ROLE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2302[] = {
    TokenType::ROLLBACK
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2303[] = {
    TokenType::SAVEPOINT
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2304[] = {
    TokenType::SECONDARY
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2305[] = {
    TokenType::SECONDARY_ENGINE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2306[] = {
    TokenType::SECONDARY_LOAD
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2307[] = {
    TokenType::SECONDARY_UNLOAD
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2308[] = {
    TokenType::SECURITY
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2309[] = {
    TokenType::SERVER
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2310[] = {
    TokenType::SIGNED
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2311[] = {
    TokenType::SOCKET
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2312[] = {
    TokenType::SLAVE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2313[] = {
    TokenType::SONAME
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2314[] = {
    TokenType::STAR
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2315[] = {
    TokenType::STOP
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2316[] = {
    TokenType::TRUNCATE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2317[] = {
    TokenType::UNICODE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2318[] = {
    TokenType::UNINSTALL
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2319[] = {
    TokenType::UPGRADE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2320[] = {
    TokenType::VISIBLE
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2321[] = {
    TokenType::WRAPPER
};

constexpr TokenType mysql_roleOrIdentifierKeyword_tokens_2322[] = {
    TokenType::XA
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2323[] = {
    TokenType::ACTION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2324[] = {
    TokenType::ACTIVE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2325[] = {
    TokenType::ADDDATE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2326[] = {
    TokenType::AFTER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2327[] = {
    TokenType::AGAINST
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2328[] = {
    TokenType::AGGREGATE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2329[] = {
    TokenType::ALGORITHM
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2330[] = {
    TokenType::ANY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2331[] = {
    TokenType::AT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2332[] = {
    TokenType::AUTO_INCREMENT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2333[] = {
    TokenType::AUTOEXTEND_SIZE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2334[] = {
    TokenType::AVG_ROW_LENGTH
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2335[] = {
    TokenType::AVG
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2336[] = {
    TokenType::BINLOG
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2337[] = {
    TokenType::BIT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2338[] = {
    TokenType::BLOCK
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2339[] = {
    TokenType::BOOL
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2340[] = {
    TokenType::BOOLEAN
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2341[] = {
    TokenType::BTREE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2342[] = {
    TokenType::BUCKETS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2343[] = {
    TokenType::CASCADED
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2344[] = {
    TokenType::CATALOG_NAME
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2345[] = {
    TokenType::CHAIN
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2346[] = {
    TokenType::CHANGED
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2347[] = {
    TokenType::CHANNEL
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2348[] = {
    TokenType::CIPHER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2349[] = {
    TokenType::CLIENT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2350[] = {
    TokenType::CLASS_ORIGIN
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2351[] = {
    TokenType::COALESCE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2352[] = {
    TokenType::CODE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2353[] = {
    TokenType::COLLATION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2354[] = {
    TokenType::COLUMN_NAME
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2355[] = {
    TokenType::COLUMN_FORMAT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2356[] = {
    TokenType::COLUMNS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2357[] = {
    TokenType::COMMITTED
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2358[] = {
    TokenType::COMPACT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2359[] = {
    TokenType::COMPLETION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2360[] = {
    TokenType::COMPONENT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2361[] = {
    TokenType::COMPRESSED
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2362[] = {
    TokenType::COMPRESSION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2363[] = {
    TokenType::CONCURRENT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2364[] = {
    TokenType::CONNECTION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2365[] = {
    TokenType::CONSISTENT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2366[] = {
    TokenType::CONSTRAINT_CATALOG
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2367[] = {
    TokenType::CONSTRAINT_SCHEMA
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2368[] = {
    TokenType::CONSTRAINT_NAME
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2369[] = {
    TokenType::CONTEXT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2370[] = {
    TokenType::CPU
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2371[] = {
    TokenType::CURRENT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2372[] = {
    TokenType::CURSOR_NAME
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2373[] = {
    TokenType::DATA
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2374[] = {
    TokenType::DATAFILE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2375[] = {
    TokenType::DATETIME
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2376[] = {
    TokenType::DATE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2377[] = {
    TokenType::DAY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2378[] = {
    TokenType::DEFAULT_AUTH
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2379[] = {
    TokenType::DEFINER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2380[] = {
    TokenType::DELAY_KEY_WRITE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2381[] = {
    TokenType::DESCRIPTION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2382[] = {
    TokenType::DIAGNOSTICS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2383[] = {
    TokenType::DIRECTORY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2384[] = {
    TokenType::DISABLE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2385[] = {
    TokenType::DISCARD
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2386[] = {
    TokenType::DISK
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2387[] = {
    TokenType::DUMPFILE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2388[] = {
    TokenType::DUPLICATE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2389[] = {
    TokenType::DYNAMIC
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2390[] = {
    TokenType::ENCRYPTION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2391[] = {
    TokenType::ENDS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2392[] = {
    TokenType::ENUM
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2393[] = {
    TokenType::ENGINE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2394[] = {
    TokenType::ENGINES
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2395[] = {
    TokenType::ENGINE_ATTRIBUTE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2396[] = {
    TokenType::ERROR
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2397[] = {
    TokenType::ERRORS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2398[] = {
    TokenType::ESCAPE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2399[] = {
    TokenType::EVENTS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2400[] = {
    TokenType::EVERY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2401[] = {
    TokenType::EXCLUDE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2402[] = {
    TokenType::EXPANSION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2403[] = {
    TokenType::EXPORT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2404[] = {
    TokenType::EXTENDED
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2405[] = {
    TokenType::EXTENT_SIZE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2406[] = {
    TokenType::FAULTS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2407[] = {
    TokenType::FAST
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2408[] = {
    TokenType::FOLLOWING
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2409[] = {
    TokenType::FOUND
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2410[] = {
    TokenType::ENABLE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2411[] = {
    TokenType::FULL
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2412[] = {
    TokenType::FILE_BLOCK_SIZE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2413[] = {
    TokenType::FILTER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2414[] = {
    TokenType::FIRST
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2415[] = {
    TokenType::FIXED
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2416[] = {
    TokenType::GENERAL
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2417[] = {
    TokenType::GEOMETRY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2418[] = {
    TokenType::GEOMETRYCOLLECTION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2419[] = {
    TokenType::GET_FORMAT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2420[] = {
    TokenType::GRANTS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2421[] = {
    TokenType::GLOBAL
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2422[] = {
    TokenType::HASH
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2423[] = {
    TokenType::HISTOGRAM
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2424[] = {
    TokenType::HISTORY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2425[] = {
    TokenType::HOSTS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2426[] = {
    TokenType::HOUR
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2427[] = {
    TokenType::IDENTIFIED
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2428[] = {
    TokenType::IGNORE_SERVER_IDS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2429[] = {
    TokenType::INVOKER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2430[] = {
    TokenType::INDEXES
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2431[] = {
    TokenType::INITIAL_SIZE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2432[] = {
    TokenType::INSTANCE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2433[] = {
    TokenType::INACTIVE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2434[] = {
    TokenType::IO
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2435[] = {
    TokenType::IPC
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2436[] = {
    TokenType::ISOLATION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2437[] = {
    TokenType::ISSUER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2438[] = {
    TokenType::INSERT_METHOD
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2439[] = {
    TokenType::JSON
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2440[] = {
    TokenType::KEY_BLOCK_SIZE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2441[] = {
    TokenType::LAST
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2442[] = {
    TokenType::LEAVES
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2443[] = {
    TokenType::LESS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2444[] = {
    TokenType::LEVEL
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2445[] = {
    TokenType::LINESTRING
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2446[] = {
    TokenType::LIST
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2447[] = {
    TokenType::LOCAL
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2448[] = {
    TokenType::LOCKED
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2449[] = {
    TokenType::LOCKS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2450[] = {
    TokenType::LOGFILE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2451[] = {
    TokenType::LOGS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2452[] = {
    TokenType::MAX_ROWS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2453[] = {
    TokenType::MASTER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2454[] = {
    TokenType::MASTER_HEARTBEAT_PERIOD
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2455[] = {
    TokenType::MASTER_HOST
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2456[] = {
    TokenType::MASTER_PORT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2457[] = {
    TokenType::MASTER_LOG_FILE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2458[] = {
    TokenType::MASTER_LOG_POS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2459[] = {
    TokenType::MASTER_USER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2460[] = {
    TokenType::MASTER_PASSWORD
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2461[] = {
    TokenType::MASTER_PUBLIC_KEY_PATH
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2462[] = {
    TokenType::MASTER_CONNECT_RETRY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2463[] = {
    TokenType::MASTER_RETRY_COUNT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2464[] = {
    TokenType::MASTER_DELAY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2465[] = {
    TokenType::MASTER_SSL
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2466[] = {
    TokenType::MASTER_SSL_CA
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2467[] = {
    TokenType::MASTER_SSL_CAPATH
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2468[] = {
    TokenType::MASTER_TLS_VERSION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2469[] = {
    TokenType::MASTER_SSL_CERT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2470[] = {
    TokenType::MASTER_SSL_CIPHER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2471[] = {
    TokenType::MASTER_SSL_CRL
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2472[] = {
    TokenType::MASTER_SSL_CRLPATH
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2473[] = {
    TokenType::MASTER_SSL_KEY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2474[] = {
    TokenType::MASTER_AUTO_POSITION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2475[] = {
    TokenType::MAX_CONNECTIONS_PER_HOUR
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2476[] = {
    TokenType::MAX_QUERIES_PER_HOUR
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2477[] = {
    TokenType::MAX_SIZE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2478[] = {
    TokenType::MAX_UPDATES_PER_HOUR
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2479[] = {
    TokenType::MAX_USER_CONNECTIONS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2480[] = {
    TokenType::MEDIUM
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2481[] = {
    TokenType::MEMORY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2482[] = {
    TokenType::MERGE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2483[] = {
    TokenType::MESSAGE_TEXT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2484[] = {
    TokenType::MICROSECOND
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2485[] = {
    TokenType::MIGRATE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2486[] = {
    TokenType::MINUTE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2487[] = {
    TokenType::MIN_ROWS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2488[] = {
    TokenType::MODIFY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2489[] = {
    TokenType::MODE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2490[] = {
    TokenType::MONTH
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2491[] = {
    TokenType::STAR
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2492[] = {
    TokenType::STAR
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2493[] = {
    TokenType::STAR
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2494[] = {
    TokenType::MUTEX
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2495[] = {
    TokenType::MYSQL_ERRNO
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2496[] = {
    TokenType::NAME
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2497[] = {
    TokenType::NAMES
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2498[] = {
    TokenType::NATIONAL
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2499[] = {
    TokenType::NCHAR
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2500[] = {
    TokenType::NDBCLUSTER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2501[] = {
    TokenType::NESTED
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2502[] = {
    TokenType::NEVER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2503[] = {
    TokenType::NEXT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2504[] = {
    TokenType::NEW
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2505[] = {
    TokenType::NO_WAIT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2506[] = {
    TokenType::NODEGROUP
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2507[] = {
    TokenType::NULLS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2508[] = {
    TokenType::NOWAIT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2509[] = {
    TokenType::NUMBER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2510[] = {
    TokenType::NVARCHAR
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2511[] = {
    TokenType::OFFSET
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2512[] = {
    TokenType::OLD
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2513[] = {
    TokenType::ONE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2514[] = {
    TokenType::OPTIONAL
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2515[] = {
    TokenType::ORDINALITY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2516[] = {
    TokenType::ORGANIZATION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2517[] = {
    TokenType::OTHERS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2518[] = {
    TokenType::PACK_KEYS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2519[] = {
    TokenType::PAGE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2520[] = {
    TokenType::PARTIAL
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2521[] = {
    TokenType::PARTITIONING
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2522[] = {
    TokenType::PARTITIONS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2523[] = {
    TokenType::PASSWORD
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2524[] = {
    TokenType::PATH
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2525[] = {
    TokenType::PHASE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2526[] = {
    TokenType::PLUGIN_DIR
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2527[] = {
    TokenType::PLUGIN
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2528[] = {
    TokenType::PLUGINS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2529[] = {
    TokenType::POINT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2530[] = {
    TokenType::POLYGON
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2531[] = {
    TokenType::PRECEDING
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2532[] = {
    TokenType::PRESERVE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2533[] = {
    TokenType::PREV
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2534[] = {
    TokenType::THREAD_PRIORITY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2535[] = {
    TokenType::PRIVILEGES
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2536[] = {
    TokenType::PROCESSLIST
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2537[] = {
    TokenType::PROFILE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2538[] = {
    TokenType::PROFILES
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2539[] = {
    TokenType::QUARTER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2540[] = {
    TokenType::QUERY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2541[] = {
    TokenType::QUICK
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2542[] = {
    TokenType::READ_ONLY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2543[] = {
    TokenType::REBUILD
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2544[] = {
    TokenType::RECOVER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2545[] = {
    TokenType::REDO_BUFFER_SIZE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2546[] = {
    TokenType::REDUNDANT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2547[] = {
    TokenType::RELAY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2548[] = {
    TokenType::RELAYLOG
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2549[] = {
    TokenType::RELAY_LOG_FILE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2550[] = {
    TokenType::RELAY_LOG_POS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2551[] = {
    TokenType::RELAY_THREAD
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2552[] = {
    TokenType::REMOTE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2553[] = {
    TokenType::REORGANIZE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2554[] = {
    TokenType::REPEATABLE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2555[] = {
    TokenType::REPLICATE_DO_DB
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2556[] = {
    TokenType::REPLICATE_IGNORE_DB
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2557[] = {
    TokenType::REPLICATE_DO_TABLE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2558[] = {
    TokenType::REPLICATE_IGNORE_TABLE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2559[] = {
    TokenType::REPLICATE_WILD_DO_TABLE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2560[] = {
    TokenType::REPLICATE_WILD_IGNORE_TABLE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2561[] = {
    TokenType::REPLICATE_REWRITE_DB
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2562[] = {
    TokenType::USER_RESOURCES
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2563[] = {
    TokenType::RESPECT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2564[] = {
    TokenType::RESUME
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2565[] = {
    TokenType::RETAIN
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2566[] = {
    TokenType::RETURNED_SQLSTATE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2567[] = {
    TokenType::RETURNS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2568[] = {
    TokenType::REUSE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2569[] = {
    TokenType::REVERSE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2570[] = {
    TokenType::ROLLUP
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2571[] = {
    TokenType::ROTATE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2572[] = {
    TokenType::ROUTINE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2573[] = {
    TokenType::ROW_COUNT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2574[] = {
    TokenType::ROW_FORMAT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2575[] = {
    TokenType::RTREE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2576[] = {
    TokenType::SCHEDULE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2577[] = {
    TokenType::SCHEMA_NAME
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2578[] = {
    TokenType::SECOND
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2579[] = {
    TokenType::SERIAL
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2580[] = {
    TokenType::SERIALIZABLE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2581[] = {
    TokenType::SESSION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2582[] = {
    TokenType::SHARE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2583[] = {
    TokenType::SIMPLE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2584[] = {
    TokenType::SKIP
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2585[] = {
    TokenType::SLOW
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2586[] = {
    TokenType::SNAPSHOT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2587[] = {
    TokenType::SOUNDS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2588[] = {
    TokenType::SOURCE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2589[] = {
    TokenType::SQL_AFTER_GTIDS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2590[] = {
    TokenType::SQL_AFTER_MTS_GAPS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2591[] = {
    TokenType::SQL_BEFORE_GTIDS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2592[] = {
    TokenType::SQL_BUFFER_RESULT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2593[] = {
    TokenType::SQL_NO_CACHE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2594[] = {
    TokenType::SQL_THREAD
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2595[] = {
    TokenType::SRID
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2596[] = {
    TokenType::STACKED
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2597[] = {
    TokenType::STAR
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2598[] = {
    TokenType::STATS_AUTO_RECALC
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2599[] = {
    TokenType::STATS_PERSISTENT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2600[] = {
    TokenType::STATS_SAMPLE_PAGES
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2601[] = {
    TokenType::STATUS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2602[] = {
    TokenType::STORAGE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2603[] = {
    TokenType::STRING
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2604[] = {
    TokenType::SUBCLASS_ORIGIN
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2605[] = {
    TokenType::SUBDATE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2606[] = {
    TokenType::SUBJECT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2607[] = {
    TokenType::SUBPARTITION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2608[] = {
    TokenType::SUBPARTITIONS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2609[] = {
    TokenType::SUPER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2610[] = {
    TokenType::SUSPEND
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2611[] = {
    TokenType::SWAPS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2612[] = {
    TokenType::SWITCHES
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2613[] = {
    TokenType::TABLE_NAME
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2614[] = {
    TokenType::TABLES
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2615[] = {
    TokenType::TABLE_CHECKSUM
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2616[] = {
    TokenType::TABLESPACE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2617[] = {
    TokenType::TEMPORARY
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2618[] = {
    TokenType::TEMPTABLE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2619[] = {
    TokenType::TEXT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2620[] = {
    TokenType::THAN
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2621[] = {
    TokenType::TIES
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2622[] = {
    TokenType::TRANSACTION
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2623[] = {
    TokenType::TRIGGERS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2624[] = {
    TokenType::TIMESTAMP
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2625[] = {
    TokenType::TIMESTAMPADD
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2626[] = {
    TokenType::TIMESTAMPDIFF
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2627[] = {
    TokenType::TIME
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2628[] = {
    TokenType::TYPES
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2629[] = {
    TokenType::TYPE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2630[] = {
    TokenType::UDF_RETURNS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2631[] = {
    TokenType::UNBOUNDED
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2632[] = {
    TokenType::UNCOMMITTED
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2633[] = {
    TokenType::UNDEFINED
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2634[] = {
    TokenType::UNDO_BUFFER_SIZE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2635[] = {
    TokenType::UNDOFILE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2636[] = {
    TokenType::UNKNOWN
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2637[] = {
    TokenType::UNTIL
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2638[] = {
    TokenType::USER
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2639[] = {
    TokenType::USE_FRM
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2640[] = {
    TokenType::VARIABLES
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2641[] = {
    TokenType::VCPU
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2642[] = {
    TokenType::VIEW
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2643[] = {
    TokenType::VALUE
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2644[] = {
    TokenType::WARNINGS
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2645[] = {
    TokenType::WAIT
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2646[] = {
    TokenType::WEEK
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2647[] = {
    TokenType::WORK
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2648[] = {
    TokenType::WEIGHT_STRING
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2649[] = {
    TokenType::X509
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2650[] = {
    TokenType::XID
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2651[] = {
    TokenType::XML
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2652[] = {
    TokenType::YEAR
};

constexpr TokenType mysql_roleOrLabelKeyword_tokens_2653[] = {
    TokenType::this,
    TokenType::isServerVersionGe80014,
    TokenType::ADMIN
};

// SELECT_STATEMENT patterns

constexpr TokenType mysql_selectStatement_tokens_0[] = {
    TokenType::queryExpression,
    TokenType::lockingClauseList
};

constexpr TokenType mysql_selectStatement_tokens_1[] = {
    TokenType::selectStatementWithInto
};

constexpr TokenType mysql_selectStatementWithInto_tokens_2[] = {
    TokenType::LPAREN,
    TokenType::selectStatementWithInto,
    TokenType::RPAREN
};

constexpr TokenType mysql_selectStatementWithInto_tokens_3[] = {
    TokenType::queryExpression,
    TokenType::intoClause,
    TokenType::lockingClauseList
};

constexpr TokenType mysql_selectStatementWithInto_tokens_4[] = {
    TokenType::queryExpression,
    TokenType::lockingClauseList,
    TokenType::intoClause
};

constexpr TokenType mysql_selectStatementWithInto_tokens_5[] = {
    TokenType::this,
    TokenType::isSelectStatementWithInto,
    TokenType::queryExpressionParens,
    TokenType::intoClause
};

constexpr TokenType mysql_selectOption_tokens_6[] = {
    TokenType::querySpecOption
};

constexpr TokenType mysql_selectOption_tokens_7[] = {
    TokenType::SQL_NO_CACHE
};

constexpr TokenType mysql_selectItemList_tokens_8[] = {
    TokenType::selectItem,
    TokenType::COMMA,
    TokenType::selectItem
};

constexpr TokenType mysql_selectItemList_tokens_9[] = {
    TokenType::STAR,
    TokenType::COMMA,
    TokenType::selectItem
};

constexpr TokenType mysql_selectItem_tokens_10[] = {
    TokenType::tableWild
};

constexpr TokenType mysql_selectItem_tokens_11[] = {
    TokenType::expr,
    TokenType::selectAlias
};

constexpr TokenType mysql_selectAlias_tokens_12[] = {
    TokenType::AS,
    TokenType::identifier
};

constexpr TokenType mysql_selectAlias_tokens_13[] = {
    TokenType::AS,
    TokenType::textStringLiteral
};

// UPDATE_STATEMENT patterns

constexpr TokenType mysql_updateStatement_tokens_0[] = {
    TokenType::withClause,
    TokenType::UPDATE,
    TokenType::LOW_PRIORITY,
    TokenType::IGNORE,
    TokenType::tableReferenceList,
    TokenType::SET,
    TokenType::updateList,
    TokenType::whereClause,
    TokenType::orderClause,
    TokenType::simpleLimitClause
};

constexpr TokenType mysql_histogramAutoUpdate_tokens_1[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::MANUAL,
    TokenType::UPDATE
};

constexpr TokenType mysql_histogramAutoUpdate_tokens_2[] = {
    TokenType::this,
    TokenType::isServerVersionGe80200,
    TokenType::AUTO,
    TokenType::UPDATE
};

constexpr TokenType mysql_histogramUpdateParam_tokens_3[] = {
    TokenType::histogramNumBuckets,
    TokenType::histogramAutoUpdate
};

constexpr TokenType mysql_histogramUpdateParam_tokens_4[] = {
    TokenType::this,
    TokenType::isServerVersionGe80031,
    TokenType::USING,
    TokenType::DATA,
    TokenType::textStringLiteral
};

constexpr TokenType mysql_updateList_tokens_5[] = {
    TokenType::updateElement,
    TokenType::COMMA,
    TokenType::updateElement
};

constexpr TokenType mysql_updateElement_tokens_6[] = {
    TokenType::columnRef,
    TokenType::EQ,
    TokenType::expr
};

constexpr TokenType mysql_updateElement_tokens_7[] = {
    TokenType::columnRef,
    TokenType::EQ,
    TokenType::DEFAULT
};

// Unified pattern table
constexpr Pattern all_patterns[] = {
    {"createStatement", Dialect::MySQL, mysql_createStatement_tokens_0, 2, "create_statement"},
    {"createStatement", Dialect::MySQL, mysql_createStatement_tokens_1, 2, "create_statement"},
    {"createStatement", Dialect::MySQL, mysql_createStatement_tokens_2, 2, "create_statement"},
    {"createStatement", Dialect::MySQL, mysql_createStatement_tokens_3, 2, "create_statement"},
    {"createStatement", Dialect::MySQL, mysql_createStatement_tokens_4, 2, "create_statement"},
    {"createStatement", Dialect::MySQL, mysql_createStatement_tokens_5, 2, "create_statement"},
    {"createStatement", Dialect::MySQL, mysql_createStatement_tokens_6, 2, "create_statement"},
    {"createStatement", Dialect::MySQL, mysql_createStatement_tokens_7, 2, "create_statement"},
    {"createStatement", Dialect::MySQL, mysql_createStatement_tokens_8, 2, "create_statement"},
    {"createStatement", Dialect::MySQL, mysql_createStatement_tokens_9, 2, "create_statement"},
    {"createStatement", Dialect::MySQL, mysql_createStatement_tokens_10, 2, "create_statement"},
    {"createStatement", Dialect::MySQL, mysql_createStatement_tokens_11, 2, "create_statement"},
    {"createStatement", Dialect::MySQL, mysql_createStatement_tokens_12, 2, "create_statement"},
    {"createStatement", Dialect::MySQL, mysql_createStatement_tokens_13, 4, "create_statement"},
    {"createStatement", Dialect::MySQL, mysql_createStatement_tokens_14, 4, "create_statement"},
    {"createDatabase", Dialect::MySQL, mysql_createDatabase_tokens_15, 4, "create_statement"},
    {"createDatabaseOption", Dialect::MySQL, mysql_createDatabaseOption_tokens_16, 1, "create_statement"},
    {"createDatabaseOption", Dialect::MySQL, mysql_createDatabaseOption_tokens_17, 1, "create_statement"},
    {"createDatabaseOption", Dialect::MySQL, mysql_createDatabaseOption_tokens_18, 3, "create_statement"},
    {"createTable", Dialect::MySQL, mysql_createTable_tokens_19, 8, "create_statement"},
    {"createTable", Dialect::MySQL, mysql_createTable_tokens_20, 6, "create_statement"},
    {"createTable", Dialect::MySQL, mysql_createTable_tokens_21, 8, "create_statement"},
    {"asCreateQueryExpression", Dialect::MySQL, mysql_asCreateQueryExpression_tokens_22, 2, "create_statement"},
    {"createRoutine", Dialect::MySQL, mysql_createRoutine_tokens_23, 4, "create_statement"},
    {"createRoutine", Dialect::MySQL, mysql_createRoutine_tokens_24, 4, "create_statement"},
    {"createRoutine", Dialect::MySQL, mysql_createRoutine_tokens_25, 4, "create_statement"},
    {"createProcedure", Dialect::MySQL, mysql_createProcedure_tokens_26, 11, "create_statement"},
    {"createFunction", Dialect::MySQL, mysql_createFunction_tokens_27, 13, "create_statement"},
    {"createUdf", Dialect::MySQL, mysql_createUdf_tokens_28, 9, "create_statement"},
    {"createUdf", Dialect::MySQL, mysql_createUdf_tokens_29, 9, "create_statement"},
    {"createUdf", Dialect::MySQL, mysql_createUdf_tokens_30, 9, "create_statement"},
    {"createUdf", Dialect::MySQL, mysql_createUdf_tokens_31, 9, "create_statement"},
    {"routineCreateOption", Dialect::MySQL, mysql_routineCreateOption_tokens_32, 1, "create_statement"},
    {"routineCreateOption", Dialect::MySQL, mysql_routineCreateOption_tokens_33, 2, "create_statement"},
    {"createIndex", Dialect::MySQL, mysql_createIndex_tokens_34, 9, "create_statement"},
    {"createIndex", Dialect::MySQL, mysql_createIndex_tokens_35, 8, "create_statement"},
    {"createIndex", Dialect::MySQL, mysql_createIndex_tokens_36, 8, "create_statement"},
    {"createIndexTarget", Dialect::MySQL, mysql_createIndexTarget_tokens_37, 3, "create_statement"},
    {"createLogfileGroup", Dialect::MySQL, mysql_createLogfileGroup_tokens_38, 7, "create_statement"},
    {"createServer", Dialect::MySQL, mysql_createServer_tokens_39, 7, "create_statement"},
    {"createTablespace", Dialect::MySQL, mysql_createTablespace_tokens_40, 8, "create_statement"},
    {"createUndoTablespace", Dialect::MySQL, mysql_createUndoTablespace_tokens_41, 6, "create_statement"},
    {"createView", Dialect::MySQL, mysql_createView_tokens_42, 6, "create_statement"},
    {"createTrigger", Dialect::MySQL, mysql_createTrigger_tokens_43, 15, "create_statement"},
    {"createTrigger", Dialect::MySQL, mysql_createTrigger_tokens_44, 15, "create_statement"},
    {"createTrigger", Dialect::MySQL, mysql_createTrigger_tokens_45, 15, "create_statement"},
    {"createTrigger", Dialect::MySQL, mysql_createTrigger_tokens_46, 15, "create_statement"},
    {"createTrigger", Dialect::MySQL, mysql_createTrigger_tokens_47, 15, "create_statement"},
    {"createTrigger", Dialect::MySQL, mysql_createTrigger_tokens_48, 15, "create_statement"},
    {"createEvent", Dialect::MySQL, mysql_createEvent_tokens_49, 16, "create_statement"},
    {"createEvent", Dialect::MySQL, mysql_createEvent_tokens_50, 18, "create_statement"},
    {"createRole", Dialect::MySQL, mysql_createRole_tokens_51, 3, "create_statement"},
    {"createSpatialReference", Dialect::MySQL, mysql_createSpatialReference_tokens_52, 7, "create_statement"},
    {"createSpatialReference", Dialect::MySQL, mysql_createSpatialReference_tokens_53, 6, "create_statement"},
    {"createUserStatement", Dialect::MySQL, mysql_createUserStatement_tokens_54, 6, "create_statement"},
    {"createUserTail", Dialect::MySQL, mysql_createUserTail_tokens_55, 6, "create_statement"},
    {"showCreateDatabaseStatement", Dialect::MySQL, mysql_showCreateDatabaseStatement_tokens_56, 5, "create_statement"},
    {"showCreateTableStatement", Dialect::MySQL, mysql_showCreateTableStatement_tokens_57, 4, "create_statement"},
    {"showCreateViewStatement", Dialect::MySQL, mysql_showCreateViewStatement_tokens_58, 4, "create_statement"},
    {"showCreateProcedureStatement", Dialect::MySQL, mysql_showCreateProcedureStatement_tokens_59, 4, "create_statement"},
    {"showCreateFunctionStatement", Dialect::MySQL, mysql_showCreateFunctionStatement_tokens_60, 4, "create_statement"},
    {"showCreateTriggerStatement", Dialect::MySQL, mysql_showCreateTriggerStatement_tokens_61, 4, "create_statement"},
    {"showCreateProcedureStatusStatement", Dialect::MySQL, mysql_showCreateProcedureStatusStatement_tokens_62, 5, "create_statement"},
    {"showCreateFunctionStatusStatement", Dialect::MySQL, mysql_showCreateFunctionStatusStatement_tokens_63, 5, "create_statement"},
    {"showCreateProcedureCodeStatement", Dialect::MySQL, mysql_showCreateProcedureCodeStatement_tokens_64, 5, "create_statement"},
    {"showCreateFunctionCodeStatement", Dialect::MySQL, mysql_showCreateFunctionCodeStatement_tokens_65, 5, "create_statement"},
    {"showCreateEventStatement", Dialect::MySQL, mysql_showCreateEventStatement_tokens_66, 4, "create_statement"},
    {"showCreateUserStatement", Dialect::MySQL, mysql_showCreateUserStatement_tokens_67, 4, "create_statement"},
    {"createResourceGroup", Dialect::MySQL, mysql_createResourceGroup_tokens_68, 10, "create_statement"},
    {"createResourceGroup", Dialect::MySQL, mysql_createResourceGroup_tokens_69, 10, "create_statement"},
    {"createTableOptions", Dialect::MySQL, mysql_createTableOptions_tokens_70, 3, "create_statement"},
    {"createTableOptionsEtc", Dialect::MySQL, mysql_createTableOptionsEtc_tokens_71, 2, "create_statement"},
    {"createTableOptionsEtc", Dialect::MySQL, mysql_createTableOptionsEtc_tokens_72, 1, "create_statement"},
    {"createPartitioningEtc", Dialect::MySQL, mysql_createPartitioningEtc_tokens_73, 2, "create_statement"},
    {"createPartitioningEtc", Dialect::MySQL, mysql_createPartitioningEtc_tokens_74, 1, "create_statement"},
    {"createTableOptionsSpaceSeparated", Dialect::MySQL, mysql_createTableOptionsSpaceSeparated_tokens_75, 1, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_76, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_77, 6, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_78, 6, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_79, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_80, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_81, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_82, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_83, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_84, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_85, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_86, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_87, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_88, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_89, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_90, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_91, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_92, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_93, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_94, 5, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_95, 5, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_96, 5, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_97, 5, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_98, 5, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_99, 5, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_100, 6, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_101, 1, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_102, 1, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_103, 5, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_104, 5, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_105, 5, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_106, 5, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_107, 5, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_108, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_109, 3, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_110, 3, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_111, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_112, 4, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_113, 5, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_114, 6, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_115, 6, "create_statement"},
    {"createTableOption", Dialect::MySQL, mysql_createTableOption_tokens_116, 3, "create_statement"},
    {"createUserList", Dialect::MySQL, mysql_createUserList_tokens_117, 3, "create_statement"},
    {"createUser", Dialect::MySQL, mysql_createUser_tokens_118, 3, "create_statement"},
    {"createUser", Dialect::MySQL, mysql_createUser_tokens_119, 3, "create_statement"},
    {"createUser", Dialect::MySQL, mysql_createUser_tokens_120, 2, "create_statement"},
    {"createUserWithMfa", Dialect::MySQL, mysql_createUserWithMfa_tokens_121, 4, "create_statement"},
    {"deleteStatement", Dialect::MySQL, mysql_deleteStatement_tokens_0, 8, "delete_statement"},
    {"deleteStatement", Dialect::MySQL, mysql_deleteStatement_tokens_1, 12, "delete_statement"},
    {"deleteStatement", Dialect::MySQL, mysql_deleteStatement_tokens_2, 7, "delete_statement"},
    {"partitionDelete", Dialect::MySQL, mysql_partitionDelete_tokens_3, 4, "delete_statement"},
    {"deleteStatementOption", Dialect::MySQL, mysql_deleteStatementOption_tokens_4, 1, "delete_statement"},
    {"deleteStatementOption", Dialect::MySQL, mysql_deleteStatementOption_tokens_5, 1, "delete_statement"},
    {"deleteStatementOption", Dialect::MySQL, mysql_deleteStatementOption_tokens_6, 1, "delete_statement"},
    {"deleteStatementOption", Dialect::MySQL, mysql_deleteStatementOption_tokens_7, 1, "delete_statement"},
    {"deleteOption", Dialect::MySQL, mysql_deleteOption_tokens_8, 1, "delete_statement"},
    {"deleteOption", Dialect::MySQL, mysql_deleteOption_tokens_9, 1, "delete_statement"},
    {"deleteOption", Dialect::MySQL, mysql_deleteOption_tokens_10, 2, "delete_statement"},
    {"deleteOption", Dialect::MySQL, mysql_deleteOption_tokens_11, 2, "delete_statement"},
    {"deleteOption", Dialect::MySQL, mysql_deleteOption_tokens_12, 2, "delete_statement"},
    {"dropStatement", Dialect::MySQL, mysql_dropStatement_tokens_0, 2, "drop_statement"},
    {"dropStatement", Dialect::MySQL, mysql_dropStatement_tokens_1, 2, "drop_statement"},
    {"dropStatement", Dialect::MySQL, mysql_dropStatement_tokens_2, 2, "drop_statement"},
    {"dropStatement", Dialect::MySQL, mysql_dropStatement_tokens_3, 2, "drop_statement"},
    {"dropStatement", Dialect::MySQL, mysql_dropStatement_tokens_4, 2, "drop_statement"},
    {"dropStatement", Dialect::MySQL, mysql_dropStatement_tokens_5, 2, "drop_statement"},
    {"dropStatement", Dialect::MySQL, mysql_dropStatement_tokens_6, 2, "drop_statement"},
    {"dropStatement", Dialect::MySQL, mysql_dropStatement_tokens_7, 2, "drop_statement"},
    {"dropStatement", Dialect::MySQL, mysql_dropStatement_tokens_8, 2, "drop_statement"},
    {"dropStatement", Dialect::MySQL, mysql_dropStatement_tokens_9, 2, "drop_statement"},
    {"dropStatement", Dialect::MySQL, mysql_dropStatement_tokens_10, 2, "drop_statement"},
    {"dropStatement", Dialect::MySQL, mysql_dropStatement_tokens_11, 2, "drop_statement"},
    {"dropStatement", Dialect::MySQL, mysql_dropStatement_tokens_12, 4, "drop_statement"},
    {"dropStatement", Dialect::MySQL, mysql_dropStatement_tokens_13, 4, "drop_statement"},
    {"dropDatabase", Dialect::MySQL, mysql_dropDatabase_tokens_14, 3, "drop_statement"},
    {"dropEvent", Dialect::MySQL, mysql_dropEvent_tokens_15, 3, "drop_statement"},
    {"dropFunction", Dialect::MySQL, mysql_dropFunction_tokens_16, 3, "drop_statement"},
    {"dropProcedure", Dialect::MySQL, mysql_dropProcedure_tokens_17, 3, "drop_statement"},
    {"dropIndex", Dialect::MySQL, mysql_dropIndex_tokens_18, 7, "drop_statement"},
    {"dropLogfileGroup", Dialect::MySQL, mysql_dropLogfileGroup_tokens_19, 6, "drop_statement"},
    {"dropLogfileGroupOption", Dialect::MySQL, mysql_dropLogfileGroupOption_tokens_20, 1, "drop_statement"},
    {"dropLogfileGroupOption", Dialect::MySQL, mysql_dropLogfileGroupOption_tokens_21, 1, "drop_statement"},
    {"dropServer", Dialect::MySQL, mysql_dropServer_tokens_22, 3, "drop_statement"},
    {"dropTable", Dialect::MySQL, mysql_dropTable_tokens_23, 6, "drop_statement"},
    {"dropTable", Dialect::MySQL, mysql_dropTable_tokens_24, 6, "drop_statement"},
    {"dropTable", Dialect::MySQL, mysql_dropTable_tokens_25, 6, "drop_statement"},
    {"dropTable", Dialect::MySQL, mysql_dropTable_tokens_26, 6, "drop_statement"},
    {"dropTableSpace", Dialect::MySQL, mysql_dropTableSpace_tokens_27, 5, "drop_statement"},
    {"dropTrigger", Dialect::MySQL, mysql_dropTrigger_tokens_28, 3, "drop_statement"},
    {"dropView", Dialect::MySQL, mysql_dropView_tokens_29, 4, "drop_statement"},
    {"dropView", Dialect::MySQL, mysql_dropView_tokens_30, 4, "drop_statement"},
    {"dropRole", Dialect::MySQL, mysql_dropRole_tokens_31, 3, "drop_statement"},
    {"dropSpatialReference", Dialect::MySQL, mysql_dropSpatialReference_tokens_32, 5, "drop_statement"},
    {"dropUndoTablespace", Dialect::MySQL, mysql_dropUndoTablespace_tokens_33, 4, "drop_statement"},
    {"dropUserStatement", Dialect::MySQL, mysql_dropUserStatement_tokens_34, 4, "drop_statement"},
    {"dropResourceGroup", Dialect::MySQL, mysql_dropResourceGroup_tokens_35, 5, "drop_statement"},
    {"queryExpressionOrParens", Dialect::MySQL, mysql_queryExpressionOrParens_tokens_0, 2, "expression"},
    {"queryExpressionOrParens", Dialect::MySQL, mysql_queryExpressionOrParens_tokens_1, 1, "expression"},
    {"queryExpressionWithOptLockingClauses", Dialect::MySQL, mysql_queryExpressionWithOptLockingClauses_tokens_2, 2, "expression"},
    {"queryExpression", Dialect::MySQL, mysql_queryExpression_tokens_3, 4, "expression"},
    {"queryExpressionBody", Dialect::MySQL, mysql_queryExpressionBody_tokens_4, 4, "expression"},
    {"queryExpressionBody", Dialect::MySQL, mysql_queryExpressionBody_tokens_5, 6, "expression"},
    {"queryExpressionBody", Dialect::MySQL, mysql_queryExpressionBody_tokens_6, 6, "expression"},
    {"queryExpressionBody", Dialect::MySQL, mysql_queryExpressionBody_tokens_7, 4, "expression"},
    {"queryExpressionBody", Dialect::MySQL, mysql_queryExpressionBody_tokens_8, 6, "expression"},
    {"queryExpressionBody", Dialect::MySQL, mysql_queryExpressionBody_tokens_9, 6, "expression"},
    {"queryExpressionParens", Dialect::MySQL, mysql_queryExpressionParens_tokens_10, 3, "expression"},
    {"queryExpressionParens", Dialect::MySQL, mysql_queryExpressionParens_tokens_11, 3, "expression"},
    {"commonTableExpression", Dialect::MySQL, mysql_commonTableExpression_tokens_12, 4, "expression"},
    {"setExprOrDefault", Dialect::MySQL, mysql_setExprOrDefault_tokens_13, 1, "expression"},
    {"setExprOrDefault", Dialect::MySQL, mysql_setExprOrDefault_tokens_14, 1, "expression"},
    {"setExprOrDefault", Dialect::MySQL, mysql_setExprOrDefault_tokens_15, 1, "expression"},
    {"setExprOrDefault", Dialect::MySQL, mysql_setExprOrDefault_tokens_16, 1, "expression"},
    {"setExprOrDefault", Dialect::MySQL, mysql_setExprOrDefault_tokens_17, 1, "expression"},
    {"setExprOrDefault", Dialect::MySQL, mysql_setExprOrDefault_tokens_18, 1, "expression"},
    {"setExprOrDefault", Dialect::MySQL, mysql_setExprOrDefault_tokens_19, 1, "expression"},
    {"expr", Dialect::MySQL, mysql_expr_tokens_20, 6, "expression"},
    {"expr", Dialect::MySQL, mysql_expr_tokens_21, 6, "expression"},
    {"expr", Dialect::MySQL, mysql_expr_tokens_22, 6, "expression"},
    {"expr", Dialect::MySQL, mysql_expr_tokens_23, 3, "expression"},
    {"expr", Dialect::MySQL, mysql_expr_tokens_24, 5, "expression"},
    {"expr", Dialect::MySQL, mysql_expr_tokens_25, 5, "expression"},
    {"expr", Dialect::MySQL, mysql_expr_tokens_26, 4, "expression"},
    {"expr", Dialect::MySQL, mysql_expr_tokens_27, 5, "expression"},
    {"expr", Dialect::MySQL, mysql_expr_tokens_28, 5, "expression"},
    {"bitExpr", Dialect::MySQL, mysql_bitExpr_tokens_29, 1, "expression"},
    {"bitExpr", Dialect::MySQL, mysql_bitExpr_tokens_30, 4, "expression"},
    {"bitExpr", Dialect::MySQL, mysql_bitExpr_tokens_31, 4, "expression"},
    {"bitExpr", Dialect::MySQL, mysql_bitExpr_tokens_32, 4, "expression"},
    {"bitExpr", Dialect::MySQL, mysql_bitExpr_tokens_33, 4, "expression"},
    {"bitExpr", Dialect::MySQL, mysql_bitExpr_tokens_34, 4, "expression"},
    {"bitExpr", Dialect::MySQL, mysql_bitExpr_tokens_35, 4, "expression"},
    {"bitExpr", Dialect::MySQL, mysql_bitExpr_tokens_36, 4, "expression"},
    {"bitExpr", Dialect::MySQL, mysql_bitExpr_tokens_37, 4, "expression"},
    {"bitExpr", Dialect::MySQL, mysql_bitExpr_tokens_38, 6, "expression"},
    {"bitExpr", Dialect::MySQL, mysql_bitExpr_tokens_39, 6, "expression"},
    {"bitExpr", Dialect::MySQL, mysql_bitExpr_tokens_40, 4, "expression"},
    {"bitExpr", Dialect::MySQL, mysql_bitExpr_tokens_41, 4, "expression"},
    {"bitExpr", Dialect::MySQL, mysql_bitExpr_tokens_42, 4, "expression"},
    {"bitExpr", Dialect::MySQL, mysql_bitExpr_tokens_43, 4, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_44, 3, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_45, 2, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_46, 2, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_47, 4, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_48, 2, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_49, 2, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_50, 2, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_51, 2, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_52, 2, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_53, 2, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_54, 2, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_55, 4, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_56, 4, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_57, 4, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_58, 4, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_59, 3, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_60, 5, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_61, 3, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_62, 5, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_63, 8, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_64, 3, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_65, 10, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_66, 13, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_67, 7, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_68, 7, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_69, 7, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_70, 5, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_71, 5, "expression"},
    {"simpleExpr", Dialect::MySQL, mysql_simpleExpr_tokens_72, 6, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_73, 7, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_74, 6, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_75, 6, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_76, 6, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_77, 1, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_78, 7, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_79, 7, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_80, 6, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_81, 7, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_82, 7, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_83, 7, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_84, 6, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_85, 6, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_86, 6, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_87, 6, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_88, 6, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_89, 7, "expression"},
    {"sumExpr", Dialect::MySQL, mysql_sumExpr_tokens_90, 10, "expression"},
    {"inSumExpr", Dialect::MySQL, mysql_inSumExpr_tokens_91, 2, "expression"},
    {"udfExprList", Dialect::MySQL, mysql_udfExprList_tokens_92, 3, "expression"},
    {"udfExpr", Dialect::MySQL, mysql_udfExpr_tokens_93, 2, "expression"},
    {"inExpressionUserVariableAssignment", Dialect::MySQL, mysql_inExpressionUserVariableAssignment_tokens_94, 3, "expression"},
    {"whenExpression", Dialect::MySQL, mysql_whenExpression_tokens_95, 2, "expression"},
    {"thenExpression", Dialect::MySQL, mysql_thenExpression_tokens_96, 2, "expression"},
    {"elseExpression", Dialect::MySQL, mysql_elseExpression_tokens_97, 2, "expression"},
    {"exprList", Dialect::MySQL, mysql_exprList_tokens_98, 3, "expression"},
    {"exprListWithParentheses", Dialect::MySQL, mysql_exprListWithParentheses_tokens_99, 3, "expression"},
    {"exprWithParentheses", Dialect::MySQL, mysql_exprWithParentheses_tokens_100, 3, "expression"},
    {"simpleExprWithParentheses", Dialect::MySQL, mysql_simpleExprWithParentheses_tokens_101, 3, "expression"},
    {"orderExpression", Dialect::MySQL, mysql_orderExpression_tokens_102, 2, "expression"},
    {"groupingExpression", Dialect::MySQL, mysql_groupingExpression_tokens_103, 1, "expression"},
    {"signalAllowedExpr", Dialect::MySQL, mysql_signalAllowedExpr_tokens_104, 1, "expression"},
    {"signalAllowedExpr", Dialect::MySQL, mysql_signalAllowedExpr_tokens_105, 1, "expression"},
    {"signalAllowedExpr", Dialect::MySQL, mysql_signalAllowedExpr_tokens_106, 1, "expression"},
    {"keyListWithExpression", Dialect::MySQL, mysql_keyListWithExpression_tokens_107, 5, "expression"},
    {"keyPartOrExpression", Dialect::MySQL, mysql_keyPartOrExpression_tokens_108, 1, "expression"},
    {"keyPartOrExpression", Dialect::MySQL, mysql_keyPartOrExpression_tokens_109, 4, "expression"},
    {"insertStatement", Dialect::MySQL, mysql_insertStatement_tokens_0, 9, "insert_statement"},
    {"insertStatement", Dialect::MySQL, mysql_insertStatement_tokens_1, 10, "insert_statement"},
    {"insertStatement", Dialect::MySQL, mysql_insertStatement_tokens_2, 8, "insert_statement"},
    {"insertLockOption", Dialect::MySQL, mysql_insertLockOption_tokens_3, 1, "insert_statement"},
    {"insertLockOption", Dialect::MySQL, mysql_insertLockOption_tokens_4, 1, "insert_statement"},
    {"insertLockOption", Dialect::MySQL, mysql_insertLockOption_tokens_5, 1, "insert_statement"},
    {"insertFromConstructor", Dialect::MySQL, mysql_insertFromConstructor_tokens_6, 4, "insert_statement"},
    {"insertValues", Dialect::MySQL, mysql_insertValues_tokens_7, 2, "insert_statement"},
    {"insertValues", Dialect::MySQL, mysql_insertValues_tokens_8, 2, "insert_statement"},
    {"insertQueryExpression", Dialect::MySQL, mysql_insertQueryExpression_tokens_9, 1, "insert_statement"},
    {"insertQueryExpression", Dialect::MySQL, mysql_insertQueryExpression_tokens_10, 1, "insert_statement"},
    {"insertQueryExpression", Dialect::MySQL, mysql_insertQueryExpression_tokens_11, 4, "insert_statement"},
    {"insertUpdateList", Dialect::MySQL, mysql_insertUpdateList_tokens_12, 5, "insert_statement"},
    {"insertIdentifier", Dialect::MySQL, mysql_insertIdentifier_tokens_13, 1, "insert_statement"},
    {"insertIdentifier", Dialect::MySQL, mysql_insertIdentifier_tokens_14, 1, "insert_statement"},
    {"queries", Dialect::MySQL, mysql_queries_tokens_0, 2, "other"},
    {"query", Dialect::MySQL, mysql_query_tokens_1, 2, "other"},
    {"query", Dialect::MySQL, mysql_query_tokens_2, 2, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_3, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_4, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_5, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_6, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_7, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_8, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_9, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_10, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_11, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_12, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_13, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_14, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_15, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_16, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_17, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_18, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_19, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_20, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_21, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_22, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_23, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_24, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_25, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_26, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_27, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_28, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_29, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_30, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_31, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_32, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_33, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_34, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_35, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_36, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_37, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_38, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_39, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_40, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_41, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_42, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_43, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_44, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_45, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_46, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_47, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_48, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_49, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_50, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_51, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_52, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_53, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_54, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_55, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_56, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_57, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_58, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_59, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_60, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_61, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_62, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_63, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_64, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_65, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_66, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_67, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_68, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_69, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_70, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_71, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_72, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_73, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_74, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_75, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_76, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_77, 1, "other"},
    {"simpleStatement", Dialect::MySQL, mysql_simpleStatement_tokens_78, 1, "other"},
    {"alterStatement", Dialect::MySQL, mysql_alterStatement_tokens_79, 2, "other"},
    {"alterStatement", Dialect::MySQL, mysql_alterStatement_tokens_80, 2, "other"},
    {"alterStatement", Dialect::MySQL, mysql_alterStatement_tokens_81, 4, "other"},
    {"alterStatement", Dialect::MySQL, mysql_alterStatement_tokens_82, 4, "other"},
    {"alterStatement", Dialect::MySQL, mysql_alterStatement_tokens_83, 2, "other"},
    {"alterStatement", Dialect::MySQL, mysql_alterStatement_tokens_84, 2, "other"},
    {"alterStatement", Dialect::MySQL, mysql_alterStatement_tokens_85, 2, "other"},
    {"alterStatement", Dialect::MySQL, mysql_alterStatement_tokens_86, 4, "other"},
    {"alterStatement", Dialect::MySQL, mysql_alterStatement_tokens_87, 2, "other"},
    {"alterStatement", Dialect::MySQL, mysql_alterStatement_tokens_88, 2, "other"},
    {"alterStatement", Dialect::MySQL, mysql_alterStatement_tokens_89, 2, "other"},
    {"alterDatabase", Dialect::MySQL, mysql_alterDatabase_tokens_90, 3, "other"},
    {"alterDatabaseOption", Dialect::MySQL, mysql_alterDatabaseOption_tokens_91, 1, "other"},
    {"alterDatabaseOption", Dialect::MySQL, mysql_alterDatabaseOption_tokens_92, 4, "other"},
    {"alterEvent", Dialect::MySQL, mysql_alterEvent_tokens_93, 18, "other"},
    {"alterEvent", Dialect::MySQL, mysql_alterEvent_tokens_94, 20, "other"},
    {"alterLogfileGroup", Dialect::MySQL, mysql_alterLogfileGroup_tokens_95, 7, "other"},
    {"alterLogfileGroupOptions", Dialect::MySQL, mysql_alterLogfileGroupOptions_tokens_96, 3, "other"},
    {"alterLogfileGroupOption", Dialect::MySQL, mysql_alterLogfileGroupOption_tokens_97, 1, "other"},
    {"alterLogfileGroupOption", Dialect::MySQL, mysql_alterLogfileGroupOption_tokens_98, 1, "other"},
    {"alterLogfileGroupOption", Dialect::MySQL, mysql_alterLogfileGroupOption_tokens_99, 1, "other"},
    {"alterServer", Dialect::MySQL, mysql_alterServer_tokens_100, 3, "other"},
    {"alterTable", Dialect::MySQL, mysql_alterTable_tokens_101, 4, "other"},
    {"alterTableActions", Dialect::MySQL, mysql_alterTableActions_tokens_102, 2, "other"},
    {"alterTableActions", Dialect::MySQL, mysql_alterTableActions_tokens_103, 2, "other"},
    {"alterTableActions", Dialect::MySQL, mysql_alterTableActions_tokens_104, 1, "other"},
    {"alterTableActions", Dialect::MySQL, mysql_alterTableActions_tokens_105, 1, "other"},
    {"alterTableActions", Dialect::MySQL, mysql_alterTableActions_tokens_106, 3, "other"},
    {"alterCommandList", Dialect::MySQL, mysql_alterCommandList_tokens_107, 1, "other"},
    {"alterCommandList", Dialect::MySQL, mysql_alterCommandList_tokens_108, 3, "other"},
    {"alterCommandsModifierList", Dialect::MySQL, mysql_alterCommandsModifierList_tokens_109, 3, "other"},
    {"standaloneAlterCommands", Dialect::MySQL, mysql_standaloneAlterCommands_tokens_110, 2, "other"},
    {"standaloneAlterCommands", Dialect::MySQL, mysql_standaloneAlterCommands_tokens_111, 2, "other"},
    {"standaloneAlterCommands", Dialect::MySQL, mysql_standaloneAlterCommands_tokens_112, 1, "other"},
    {"standaloneAlterCommands", Dialect::MySQL, mysql_standaloneAlterCommands_tokens_113, 3, "other"},
    {"standaloneAlterCommands", Dialect::MySQL, mysql_standaloneAlterCommands_tokens_114, 3, "other"},
    {"alterPartition", Dialect::MySQL, mysql_alterPartition_tokens_115, 4, "other"},
    {"alterPartition", Dialect::MySQL, mysql_alterPartition_tokens_116, 5, "other"},
    {"alterPartition", Dialect::MySQL, mysql_alterPartition_tokens_117, 3, "other"},
    {"alterPartition", Dialect::MySQL, mysql_alterPartition_tokens_118, 4, "other"},
    {"alterPartition", Dialect::MySQL, mysql_alterPartition_tokens_119, 5, "other"},
    {"alterPartition", Dialect::MySQL, mysql_alterPartition_tokens_120, 4, "other"},
    {"alterPartition", Dialect::MySQL, mysql_alterPartition_tokens_121, 4, "other"},
    {"alterPartition", Dialect::MySQL, mysql_alterPartition_tokens_122, 5, "other"},
    {"alterPartition", Dialect::MySQL, mysql_alterPartition_tokens_123, 4, "other"},
    {"alterPartition", Dialect::MySQL, mysql_alterPartition_tokens_124, 3, "other"},
    {"alterPartition", Dialect::MySQL, mysql_alterPartition_tokens_125, 6, "other"},
    {"alterPartition", Dialect::MySQL, mysql_alterPartition_tokens_126, 7, "other"},
    {"alterPartition", Dialect::MySQL, mysql_alterPartition_tokens_127, 4, "other"},
    {"alterPartition", Dialect::MySQL, mysql_alterPartition_tokens_128, 4, "other"},
    {"alterList", Dialect::MySQL, mysql_alterList_tokens_129, 3, "other"},
    {"alterList", Dialect::MySQL, mysql_alterList_tokens_130, 3, "other"},
    {"alterList", Dialect::MySQL, mysql_alterList_tokens_131, 3, "other"},
    {"alterList", Dialect::MySQL, mysql_alterList_tokens_132, 3, "other"},
    {"alterList", Dialect::MySQL, mysql_alterList_tokens_133, 3, "other"},
    {"alterList", Dialect::MySQL, mysql_alterList_tokens_134, 3, "other"},
    {"alterCommandsModifier", Dialect::MySQL, mysql_alterCommandsModifier_tokens_135, 1, "other"},
    {"alterCommandsModifier", Dialect::MySQL, mysql_alterCommandsModifier_tokens_136, 1, "other"},
    {"alterCommandsModifier", Dialect::MySQL, mysql_alterCommandsModifier_tokens_137, 1, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_138, 6, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_139, 5, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_140, 2, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_141, 6, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_142, 5, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_143, 4, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_144, 4, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_145, 3, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_146, 3, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_147, 5, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_148, 5, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_149, 2, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_150, 2, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_151, 8, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_152, 6, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_153, 5, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_154, 7, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_155, 4, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_156, 6, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_157, 6, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_158, 5, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_159, 3, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_160, 3, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_161, 5, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_162, 7, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_163, 5, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_164, 1, "other"},
    {"alterListItem", Dialect::MySQL, mysql_alterListItem_tokens_165, 3, "other"},
    {"place", Dialect::MySQL, mysql_place_tokens_166, 2, "other"},
    {"place", Dialect::MySQL, mysql_place_tokens_167, 1, "other"},
    {"restrict", Dialect::MySQL, mysql_restrict_tokens_168, 1, "other"},
    {"restrict", Dialect::MySQL, mysql_restrict_tokens_169, 1, "other"},
    {"alterOrderList", Dialect::MySQL, mysql_alterOrderList_tokens_170, 5, "other"},
    {"alterAlgorithmOption", Dialect::MySQL, mysql_alterAlgorithmOption_tokens_171, 3, "other"},
    {"alterAlgorithmOption", Dialect::MySQL, mysql_alterAlgorithmOption_tokens_172, 3, "other"},
    {"alterLockOption", Dialect::MySQL, mysql_alterLockOption_tokens_173, 3, "other"},
    {"alterLockOption", Dialect::MySQL, mysql_alterLockOption_tokens_174, 3, "other"},
    {"indexLockAndAlgorithm", Dialect::MySQL, mysql_indexLockAndAlgorithm_tokens_175, 2, "other"},
    {"indexLockAndAlgorithm", Dialect::MySQL, mysql_indexLockAndAlgorithm_tokens_176, 2, "other"},
    {"withValidation", Dialect::MySQL, mysql_withValidation_tokens_177, 2, "other"},
    {"withValidation", Dialect::MySQL, mysql_withValidation_tokens_178, 2, "other"},
    {"removePartitioning", Dialect::MySQL, mysql_removePartitioning_tokens_179, 2, "other"},
    {"allOrPartitionNameList", Dialect::MySQL, mysql_allOrPartitionNameList_tokens_180, 1, "other"},
    {"allOrPartitionNameList", Dialect::MySQL, mysql_allOrPartitionNameList_tokens_181, 1, "other"},
    {"alterTablespace", Dialect::MySQL, mysql_alterTablespace_tokens_182, 6, "other"},
    {"alterTablespace", Dialect::MySQL, mysql_alterTablespace_tokens_183, 6, "other"},
    {"alterTablespace", Dialect::MySQL, mysql_alterTablespace_tokens_184, 5, "other"},
    {"alterTablespace", Dialect::MySQL, mysql_alterTablespace_tokens_185, 5, "other"},
    {"alterUndoTablespace", Dialect::MySQL, mysql_alterUndoTablespace_tokens_186, 6, "other"},
    {"alterUndoTablespace", Dialect::MySQL, mysql_alterUndoTablespace_tokens_187, 6, "other"},
    {"undoTableSpaceOptions", Dialect::MySQL, mysql_undoTableSpaceOptions_tokens_188, 3, "other"},
    {"undoTableSpaceOption", Dialect::MySQL, mysql_undoTableSpaceOption_tokens_189, 1, "other"},
    {"alterTablespaceOptions", Dialect::MySQL, mysql_alterTablespaceOptions_tokens_190, 3, "other"},
    {"alterTablespaceOption", Dialect::MySQL, mysql_alterTablespaceOption_tokens_191, 3, "other"},
    {"alterTablespaceOption", Dialect::MySQL, mysql_alterTablespaceOption_tokens_192, 1, "other"},
    {"alterTablespaceOption", Dialect::MySQL, mysql_alterTablespaceOption_tokens_193, 1, "other"},
    {"alterTablespaceOption", Dialect::MySQL, mysql_alterTablespaceOption_tokens_194, 1, "other"},
    {"alterTablespaceOption", Dialect::MySQL, mysql_alterTablespaceOption_tokens_195, 1, "other"},
    {"alterTablespaceOption", Dialect::MySQL, mysql_alterTablespaceOption_tokens_196, 1, "other"},
    {"alterTablespaceOption", Dialect::MySQL, mysql_alterTablespaceOption_tokens_197, 3, "other"},
    {"changeTablespaceOption", Dialect::MySQL, mysql_changeTablespaceOption_tokens_198, 3, "other"},
    {"changeTablespaceOption", Dialect::MySQL, mysql_changeTablespaceOption_tokens_199, 1, "other"},
    {"changeTablespaceOption", Dialect::MySQL, mysql_changeTablespaceOption_tokens_200, 1, "other"},
    {"alterView", Dialect::MySQL, mysql_alterView_tokens_201, 6, "other"},
    {"viewTail", Dialect::MySQL, mysql_viewTail_tokens_202, 3, "other"},
    {"viewQueryBlock", Dialect::MySQL, mysql_viewQueryBlock_tokens_203, 2, "other"},
    {"viewCheckOption", Dialect::MySQL, mysql_viewCheckOption_tokens_204, 4, "other"},
    {"viewCheckOption", Dialect::MySQL, mysql_viewCheckOption_tokens_205, 4, "other"},
    {"alterInstanceStatement", Dialect::MySQL, mysql_alterInstanceStatement_tokens_206, 5, "other"},
    {"alterInstanceStatement", Dialect::MySQL, mysql_alterInstanceStatement_tokens_207, 8, "other"},
    {"alterInstanceStatement", Dialect::MySQL, mysql_alterInstanceStatement_tokens_208, 11, "other"},
    {"alterInstanceStatement", Dialect::MySQL, mysql_alterInstanceStatement_tokens_209, 5, "other"},
    {"alterInstanceStatement", Dialect::MySQL, mysql_alterInstanceStatement_tokens_210, 5, "other"},
    {"alterInstanceStatement", Dialect::MySQL, mysql_alterInstanceStatement_tokens_211, 4, "other"},
    {"tableElementList", Dialect::MySQL, mysql_tableElementList_tokens_212, 3, "other"},
    {"tableElement", Dialect::MySQL, mysql_tableElement_tokens_213, 1, "other"},
    {"tableElement", Dialect::MySQL, mysql_tableElement_tokens_214, 1, "other"},
    {"duplicateAsQe", Dialect::MySQL, mysql_duplicateAsQe_tokens_215, 2, "other"},
    {"duplicateAsQe", Dialect::MySQL, mysql_duplicateAsQe_tokens_216, 2, "other"},
    {"routineString", Dialect::MySQL, mysql_routineString_tokens_217, 1, "other"},
    {"routineString", Dialect::MySQL, mysql_routineString_tokens_218, 1, "other"},
    {"storedRoutineBody", Dialect::MySQL, mysql_storedRoutineBody_tokens_219, 1, "other"},
    {"storedRoutineBody", Dialect::MySQL, mysql_storedRoutineBody_tokens_220, 4, "other"},
    {"routineAlterOptions", Dialect::MySQL, mysql_routineAlterOptions_tokens_221, 1, "other"},
    {"routineOption", Dialect::MySQL, mysql_routineOption_tokens_222, 3, "other"},
    {"routineOption", Dialect::MySQL, mysql_routineOption_tokens_223, 3, "other"},
    {"routineOption", Dialect::MySQL, mysql_routineOption_tokens_224, 5, "other"},
    {"routineOption", Dialect::MySQL, mysql_routineOption_tokens_225, 3, "other"},
    {"routineOption", Dialect::MySQL, mysql_routineOption_tokens_226, 3, "other"},
    {"routineOption", Dialect::MySQL, mysql_routineOption_tokens_227, 4, "other"},
    {"routineOption", Dialect::MySQL, mysql_routineOption_tokens_228, 4, "other"},
    {"routineOption", Dialect::MySQL, mysql_routineOption_tokens_229, 5, "other"},
    {"routineOption", Dialect::MySQL, mysql_routineOption_tokens_230, 5, "other"},
    {"indexNameAndType", Dialect::MySQL, mysql_indexNameAndType_tokens_231, 1, "other"},
    {"indexNameAndType", Dialect::MySQL, mysql_indexNameAndType_tokens_232, 3, "other"},
    {"indexNameAndType", Dialect::MySQL, mysql_indexNameAndType_tokens_233, 3, "other"},
    {"logfileGroupOptions", Dialect::MySQL, mysql_logfileGroupOptions_tokens_234, 3, "other"},
    {"logfileGroupOption", Dialect::MySQL, mysql_logfileGroupOption_tokens_235, 1, "other"},
    {"logfileGroupOption", Dialect::MySQL, mysql_logfileGroupOption_tokens_236, 1, "other"},
    {"logfileGroupOption", Dialect::MySQL, mysql_logfileGroupOption_tokens_237, 1, "other"},
    {"logfileGroupOption", Dialect::MySQL, mysql_logfileGroupOption_tokens_238, 1, "other"},
    {"logfileGroupOption", Dialect::MySQL, mysql_logfileGroupOption_tokens_239, 1, "other"},
    {"logfileGroupOption", Dialect::MySQL, mysql_logfileGroupOption_tokens_240, 1, "other"},
    {"serverOptions", Dialect::MySQL, mysql_serverOptions_tokens_241, 6, "other"},
    {"serverOption", Dialect::MySQL, mysql_serverOption_tokens_242, 3, "other"},
    {"serverOption", Dialect::MySQL, mysql_serverOption_tokens_243, 3, "other"},
    {"serverOption", Dialect::MySQL, mysql_serverOption_tokens_244, 3, "other"},
    {"serverOption", Dialect::MySQL, mysql_serverOption_tokens_245, 3, "other"},
    {"serverOption", Dialect::MySQL, mysql_serverOption_tokens_246, 3, "other"},
    {"serverOption", Dialect::MySQL, mysql_serverOption_tokens_247, 3, "other"},
    {"serverOption", Dialect::MySQL, mysql_serverOption_tokens_248, 3, "other"},
    {"tsDataFileName", Dialect::MySQL, mysql_tsDataFileName_tokens_249, 2, "other"},
    {"tsDataFileName", Dialect::MySQL, mysql_tsDataFileName_tokens_250, 4, "other"},
    {"tsDataFile", Dialect::MySQL, mysql_tsDataFile_tokens_251, 2, "other"},
    {"tablespaceOptions", Dialect::MySQL, mysql_tablespaceOptions_tokens_252, 3, "other"},
    {"tablespaceOption", Dialect::MySQL, mysql_tablespaceOption_tokens_253, 1, "other"},
    {"tablespaceOption", Dialect::MySQL, mysql_tablespaceOption_tokens_254, 1, "other"},
    {"tablespaceOption", Dialect::MySQL, mysql_tablespaceOption_tokens_255, 1, "other"},
    {"tablespaceOption", Dialect::MySQL, mysql_tablespaceOption_tokens_256, 1, "other"},
    {"tablespaceOption", Dialect::MySQL, mysql_tablespaceOption_tokens_257, 1, "other"},
    {"tablespaceOption", Dialect::MySQL, mysql_tablespaceOption_tokens_258, 1, "other"},
    {"tablespaceOption", Dialect::MySQL, mysql_tablespaceOption_tokens_259, 1, "other"},
    {"tablespaceOption", Dialect::MySQL, mysql_tablespaceOption_tokens_260, 1, "other"},
    {"tablespaceOption", Dialect::MySQL, mysql_tablespaceOption_tokens_261, 1, "other"},
    {"tablespaceOption", Dialect::MySQL, mysql_tablespaceOption_tokens_262, 3, "other"},
    {"tsOptionInitialSize", Dialect::MySQL, mysql_tsOptionInitialSize_tokens_263, 3, "other"},
    {"tsOptionUndoRedoBufferSize", Dialect::MySQL, mysql_tsOptionUndoRedoBufferSize_tokens_264, 3, "other"},
    {"tsOptionUndoRedoBufferSize", Dialect::MySQL, mysql_tsOptionUndoRedoBufferSize_tokens_265, 3, "other"},
    {"tsOptionAutoextendSize", Dialect::MySQL, mysql_tsOptionAutoextendSize_tokens_266, 3, "other"},
    {"tsOptionMaxSize", Dialect::MySQL, mysql_tsOptionMaxSize_tokens_267, 3, "other"},
    {"tsOptionExtentSize", Dialect::MySQL, mysql_tsOptionExtentSize_tokens_268, 3, "other"},
    {"tsOptionNodegroup", Dialect::MySQL, mysql_tsOptionNodegroup_tokens_269, 3, "other"},
    {"tsOptionEngine", Dialect::MySQL, mysql_tsOptionEngine_tokens_270, 4, "other"},
    {"tsOptionWait", Dialect::MySQL, mysql_tsOptionWait_tokens_271, 1, "other"},
    {"tsOptionWait", Dialect::MySQL, mysql_tsOptionWait_tokens_272, 1, "other"},
    {"tsOptionComment", Dialect::MySQL, mysql_tsOptionComment_tokens_273, 3, "other"},
    {"tsOptionFileblockSize", Dialect::MySQL, mysql_tsOptionFileblockSize_tokens_274, 3, "other"},
    {"tsOptionEncryption", Dialect::MySQL, mysql_tsOptionEncryption_tokens_275, 3, "other"},
    {"tsOptionEngineAttribute", Dialect::MySQL, mysql_tsOptionEngineAttribute_tokens_276, 3, "other"},
    {"viewReplaceOrAlgorithm", Dialect::MySQL, mysql_viewReplaceOrAlgorithm_tokens_277, 3, "other"},
    {"viewReplaceOrAlgorithm", Dialect::MySQL, mysql_viewReplaceOrAlgorithm_tokens_278, 1, "other"},
    {"viewAlgorithm", Dialect::MySQL, mysql_viewAlgorithm_tokens_279, 4, "other"},
    {"viewAlgorithm", Dialect::MySQL, mysql_viewAlgorithm_tokens_280, 4, "other"},
    {"viewAlgorithm", Dialect::MySQL, mysql_viewAlgorithm_tokens_281, 4, "other"},
    {"viewSuid", Dialect::MySQL, mysql_viewSuid_tokens_282, 3, "other"},
    {"viewSuid", Dialect::MySQL, mysql_viewSuid_tokens_283, 3, "other"},
    {"triggerFollowsPrecedesClause", Dialect::MySQL, mysql_triggerFollowsPrecedesClause_tokens_284, 3, "other"},
    {"triggerFollowsPrecedesClause", Dialect::MySQL, mysql_triggerFollowsPrecedesClause_tokens_285, 3, "other"},
    {"srsAttribute", Dialect::MySQL, mysql_srsAttribute_tokens_286, 3, "other"},
    {"srsAttribute", Dialect::MySQL, mysql_srsAttribute_tokens_287, 3, "other"},
    {"srsAttribute", Dialect::MySQL, mysql_srsAttribute_tokens_288, 5, "other"},
    {"srsAttribute", Dialect::MySQL, mysql_srsAttribute_tokens_289, 3, "other"},
    {"renameTableStatement", Dialect::MySQL, mysql_renameTableStatement_tokens_290, 5, "other"},
    {"renameTableStatement", Dialect::MySQL, mysql_renameTableStatement_tokens_291, 5, "other"},
    {"renamePair", Dialect::MySQL, mysql_renamePair_tokens_292, 3, "other"},
    {"truncateTableStatement", Dialect::MySQL, mysql_truncateTableStatement_tokens_293, 3, "other"},
    {"importStatement", Dialect::MySQL, mysql_importStatement_tokens_294, 4, "other"},
    {"callStatement", Dialect::MySQL, mysql_callStatement_tokens_295, 5, "other"},
    {"doStatement", Dialect::MySQL, mysql_doStatement_tokens_296, 2, "other"},
    {"handlerStatement", Dialect::MySQL, mysql_handlerStatement_tokens_297, 4, "other"},
    {"handlerStatement", Dialect::MySQL, mysql_handlerStatement_tokens_298, 3, "other"},
    {"handlerStatement", Dialect::MySQL, mysql_handlerStatement_tokens_299, 6, "other"},
    {"handlerReadOrScan", Dialect::MySQL, mysql_handlerReadOrScan_tokens_300, 1, "other"},
    {"handlerReadOrScan", Dialect::MySQL, mysql_handlerReadOrScan_tokens_301, 1, "other"},
    {"handlerReadOrScan", Dialect::MySQL, mysql_handlerReadOrScan_tokens_302, 2, "other"},
    {"handlerReadOrScan", Dialect::MySQL, mysql_handlerReadOrScan_tokens_303, 2, "other"},
    {"handlerReadOrScan", Dialect::MySQL, mysql_handlerReadOrScan_tokens_304, 2, "other"},
    {"handlerReadOrScan", Dialect::MySQL, mysql_handlerReadOrScan_tokens_305, 2, "other"},
    {"handlerReadOrScan", Dialect::MySQL, mysql_handlerReadOrScan_tokens_306, 5, "other"},
    {"handlerReadOrScan", Dialect::MySQL, mysql_handlerReadOrScan_tokens_307, 5, "other"},
    {"handlerReadOrScan", Dialect::MySQL, mysql_handlerReadOrScan_tokens_308, 5, "other"},
    {"handlerReadOrScan", Dialect::MySQL, mysql_handlerReadOrScan_tokens_309, 5, "other"},
    {"handlerReadOrScan", Dialect::MySQL, mysql_handlerReadOrScan_tokens_310, 5, "other"},
    {"fields", Dialect::MySQL, mysql_fields_tokens_311, 3, "other"},
    {"valueList", Dialect::MySQL, mysql_valueList_tokens_312, 7, "other"},
    {"values", Dialect::MySQL, mysql_values_tokens_313, 3, "other"},
    {"values", Dialect::MySQL, mysql_values_tokens_314, 3, "other"},
    {"values", Dialect::MySQL, mysql_values_tokens_315, 3, "other"},
    {"values", Dialect::MySQL, mysql_values_tokens_316, 3, "other"},
    {"valuesReference", Dialect::MySQL, mysql_valuesReference_tokens_317, 5, "other"},
    {"loadStatement", Dialect::MySQL, mysql_loadStatement_tokens_318, 22, "other"},
    {"loadStatement", Dialect::MySQL, mysql_loadStatement_tokens_319, 22, "other"},
    {"dataOrXml", Dialect::MySQL, mysql_dataOrXml_tokens_320, 1, "other"},
    {"dataOrXml", Dialect::MySQL, mysql_dataOrXml_tokens_321, 1, "other"},
    {"loadDataLock", Dialect::MySQL, mysql_loadDataLock_tokens_322, 1, "other"},
    {"loadDataLock", Dialect::MySQL, mysql_loadDataLock_tokens_323, 1, "other"},
    {"loadFrom", Dialect::MySQL, mysql_loadFrom_tokens_324, 3, "other"},
    {"loadSourceType", Dialect::MySQL, mysql_loadSourceType_tokens_325, 1, "other"},
    {"loadSourceType", Dialect::MySQL, mysql_loadSourceType_tokens_326, 3, "other"},
    {"loadSourceType", Dialect::MySQL, mysql_loadSourceType_tokens_327, 3, "other"},
    {"sourceCount", Dialect::MySQL, mysql_sourceCount_tokens_328, 4, "other"},
    {"sourceCount", Dialect::MySQL, mysql_sourceCount_tokens_329, 4, "other"},
    {"sourceOrder", Dialect::MySQL, mysql_sourceOrder_tokens_330, 6, "other"},
    {"xmlRowsIdentifiedBy", Dialect::MySQL, mysql_xmlRowsIdentifiedBy_tokens_331, 4, "other"},
    {"loadDataFileTail", Dialect::MySQL, mysql_loadDataFileTail_tokens_332, 6, "other"},
    {"loadDataFileTail", Dialect::MySQL, mysql_loadDataFileTail_tokens_333, 6, "other"},
    {"loadDataFileTargetList", Dialect::MySQL, mysql_loadDataFileTargetList_tokens_334, 3, "other"},
    {"fieldOrVariableList", Dialect::MySQL, mysql_fieldOrVariableList_tokens_335, 3, "other"},
    {"fieldOrVariableList", Dialect::MySQL, mysql_fieldOrVariableList_tokens_336, 4, "other"},
    {"fieldOrVariableList", Dialect::MySQL, mysql_fieldOrVariableList_tokens_337, 3, "other"},
    {"fieldOrVariableList", Dialect::MySQL, mysql_fieldOrVariableList_tokens_338, 3, "other"},
    {"fieldOrVariableList", Dialect::MySQL, mysql_fieldOrVariableList_tokens_339, 4, "other"},
    {"fieldOrVariableList", Dialect::MySQL, mysql_fieldOrVariableList_tokens_340, 5, "other"},
    {"fieldOrVariableList", Dialect::MySQL, mysql_fieldOrVariableList_tokens_341, 4, "other"},
    {"fieldOrVariableList", Dialect::MySQL, mysql_fieldOrVariableList_tokens_342, 4, "other"},
    {"fieldOrVariableList", Dialect::MySQL, mysql_fieldOrVariableList_tokens_343, 3, "other"},
    {"fieldOrVariableList", Dialect::MySQL, mysql_fieldOrVariableList_tokens_344, 4, "other"},
    {"fieldOrVariableList", Dialect::MySQL, mysql_fieldOrVariableList_tokens_345, 3, "other"},
    {"fieldOrVariableList", Dialect::MySQL, mysql_fieldOrVariableList_tokens_346, 3, "other"},
    {"loadAlgorithm", Dialect::MySQL, mysql_loadAlgorithm_tokens_347, 5, "other"},
    {"loadParallel", Dialect::MySQL, mysql_loadParallel_tokens_348, 5, "other"},
    {"loadMemory", Dialect::MySQL, mysql_loadMemory_tokens_349, 5, "other"},
    {"replaceStatement", Dialect::MySQL, mysql_replaceStatement_tokens_350, 6, "other"},
    {"replaceStatement", Dialect::MySQL, mysql_replaceStatement_tokens_351, 7, "other"},
    {"replaceStatement", Dialect::MySQL, mysql_replaceStatement_tokens_352, 6, "other"},
    {"replaceStatement", Dialect::MySQL, mysql_replaceStatement_tokens_353, 6, "other"},
    {"replaceStatement", Dialect::MySQL, mysql_replaceStatement_tokens_354, 7, "other"},
    {"replaceStatement", Dialect::MySQL, mysql_replaceStatement_tokens_355, 6, "other"},
    {"queryPrimary", Dialect::MySQL, mysql_queryPrimary_tokens_356, 1, "other"},
    {"queryPrimary", Dialect::MySQL, mysql_queryPrimary_tokens_357, 3, "other"},
    {"queryPrimary", Dialect::MySQL, mysql_queryPrimary_tokens_358, 3, "other"},
    {"querySpecification", Dialect::MySQL, mysql_querySpecification_tokens_359, 10, "other"},
    {"subquery", Dialect::MySQL, mysql_subquery_tokens_360, 1, "other"},
    {"querySpecOption", Dialect::MySQL, mysql_querySpecOption_tokens_361, 1, "other"},
    {"querySpecOption", Dialect::MySQL, mysql_querySpecOption_tokens_362, 1, "other"},
    {"querySpecOption", Dialect::MySQL, mysql_querySpecOption_tokens_363, 1, "other"},
    {"querySpecOption", Dialect::MySQL, mysql_querySpecOption_tokens_364, 1, "other"},
    {"querySpecOption", Dialect::MySQL, mysql_querySpecOption_tokens_365, 1, "other"},
    {"querySpecOption", Dialect::MySQL, mysql_querySpecOption_tokens_366, 1, "other"},
    {"querySpecOption", Dialect::MySQL, mysql_querySpecOption_tokens_367, 1, "other"},
    {"querySpecOption", Dialect::MySQL, mysql_querySpecOption_tokens_368, 1, "other"},
    {"limitClause", Dialect::MySQL, mysql_limitClause_tokens_369, 2, "other"},
    {"simpleLimitClause", Dialect::MySQL, mysql_simpleLimitClause_tokens_370, 2, "other"},
    {"limitOptions", Dialect::MySQL, mysql_limitOptions_tokens_371, 3, "other"},
    {"limitOptions", Dialect::MySQL, mysql_limitOptions_tokens_372, 3, "other"},
    {"limitOption", Dialect::MySQL, mysql_limitOption_tokens_373, 1, "other"},
    {"limitOption", Dialect::MySQL, mysql_limitOption_tokens_374, 1, "other"},
    {"limitOption", Dialect::MySQL, mysql_limitOption_tokens_375, 1, "other"},
    {"limitOption", Dialect::MySQL, mysql_limitOption_tokens_376, 1, "other"},
    {"limitOption", Dialect::MySQL, mysql_limitOption_tokens_377, 1, "other"},
    {"intoClause", Dialect::MySQL, mysql_intoClause_tokens_378, 6, "other"},
    {"intoClause", Dialect::MySQL, mysql_intoClause_tokens_379, 3, "other"},
    {"intoClause", Dialect::MySQL, mysql_intoClause_tokens_380, 4, "other"},
    {"intoClause", Dialect::MySQL, mysql_intoClause_tokens_381, 4, "other"},
    {"intoClause", Dialect::MySQL, mysql_intoClause_tokens_382, 4, "other"},
    {"intoClause", Dialect::MySQL, mysql_intoClause_tokens_383, 4, "other"},
    {"procedureAnalyseClause", Dialect::MySQL, mysql_procedureAnalyseClause_tokens_384, 6, "other"},
    {"havingClause", Dialect::MySQL, mysql_havingClause_tokens_385, 2, "other"},
    {"qualifyClause", Dialect::MySQL, mysql_qualifyClause_tokens_386, 4, "other"},
    {"windowClause", Dialect::MySQL, mysql_windowClause_tokens_387, 4, "other"},
    {"windowDefinition", Dialect::MySQL, mysql_windowDefinition_tokens_388, 3, "other"},
    {"windowSpec", Dialect::MySQL, mysql_windowSpec_tokens_389, 3, "other"},
    {"windowSpecDetails", Dialect::MySQL, mysql_windowSpecDetails_tokens_390, 6, "other"},
    {"windowFrameClause", Dialect::MySQL, mysql_windowFrameClause_tokens_391, 3, "other"},
    {"windowFrameUnits", Dialect::MySQL, mysql_windowFrameUnits_tokens_392, 1, "other"},
    {"windowFrameUnits", Dialect::MySQL, mysql_windowFrameUnits_tokens_393, 1, "other"},
    {"windowFrameUnits", Dialect::MySQL, mysql_windowFrameUnits_tokens_394, 1, "other"},
    {"windowFrameExtent", Dialect::MySQL, mysql_windowFrameExtent_tokens_395, 1, "other"},
    {"windowFrameExtent", Dialect::MySQL, mysql_windowFrameExtent_tokens_396, 1, "other"},
    {"windowFrameStart", Dialect::MySQL, mysql_windowFrameStart_tokens_397, 2, "other"},
    {"windowFrameStart", Dialect::MySQL, mysql_windowFrameStart_tokens_398, 2, "other"},
    {"windowFrameStart", Dialect::MySQL, mysql_windowFrameStart_tokens_399, 2, "other"},
    {"windowFrameStart", Dialect::MySQL, mysql_windowFrameStart_tokens_400, 4, "other"},
    {"windowFrameStart", Dialect::MySQL, mysql_windowFrameStart_tokens_401, 2, "other"},
    {"windowFrameBetween", Dialect::MySQL, mysql_windowFrameBetween_tokens_402, 4, "other"},
    {"windowFrameBound", Dialect::MySQL, mysql_windowFrameBound_tokens_403, 1, "other"},
    {"windowFrameBound", Dialect::MySQL, mysql_windowFrameBound_tokens_404, 2, "other"},
    {"windowFrameBound", Dialect::MySQL, mysql_windowFrameBound_tokens_405, 2, "other"},
    {"windowFrameBound", Dialect::MySQL, mysql_windowFrameBound_tokens_406, 2, "other"},
    {"windowFrameBound", Dialect::MySQL, mysql_windowFrameBound_tokens_407, 4, "other"},
    {"windowFrameExclusion", Dialect::MySQL, mysql_windowFrameExclusion_tokens_408, 3, "other"},
    {"windowFrameExclusion", Dialect::MySQL, mysql_windowFrameExclusion_tokens_409, 2, "other"},
    {"windowFrameExclusion", Dialect::MySQL, mysql_windowFrameExclusion_tokens_410, 2, "other"},
    {"windowFrameExclusion", Dialect::MySQL, mysql_windowFrameExclusion_tokens_411, 3, "other"},
    {"withClause", Dialect::MySQL, mysql_withClause_tokens_412, 5, "other"},
    {"groupByClause", Dialect::MySQL, mysql_groupByClause_tokens_413, 4, "other"},
    {"groupByClause", Dialect::MySQL, mysql_groupByClause_tokens_414, 8, "other"},
    {"groupByClause", Dialect::MySQL, mysql_groupByClause_tokens_415, 8, "other"},
    {"olapOption", Dialect::MySQL, mysql_olapOption_tokens_416, 2, "other"},
    {"orderClause", Dialect::MySQL, mysql_orderClause_tokens_417, 3, "other"},
    {"direction", Dialect::MySQL, mysql_direction_tokens_418, 1, "other"},
    {"direction", Dialect::MySQL, mysql_direction_tokens_419, 1, "other"},
    {"fromClause", Dialect::MySQL, mysql_fromClause_tokens_420, 2, "other"},
    {"fromClause", Dialect::MySQL, mysql_fromClause_tokens_421, 2, "other"},
    {"tableReferenceList", Dialect::MySQL, mysql_tableReferenceList_tokens_422, 3, "other"},
    {"tableValueConstructor", Dialect::MySQL, mysql_tableValueConstructor_tokens_423, 4, "other"},
    {"explicitTable", Dialect::MySQL, mysql_explicitTable_tokens_424, 2, "other"},
    {"rowValueExplicit", Dialect::MySQL, mysql_rowValueExplicit_tokens_425, 4, "other"},
    {"lockingClauseList", Dialect::MySQL, mysql_lockingClauseList_tokens_426, 3, "other"},
    {"lockingClause", Dialect::MySQL, mysql_lockingClause_tokens_427, 5, "other"},
    {"lockingClause", Dialect::MySQL, mysql_lockingClause_tokens_428, 4, "other"},
    {"lockStrengh", Dialect::MySQL, mysql_lockStrengh_tokens_429, 1, "other"},
    {"lockStrengh", Dialect::MySQL, mysql_lockStrengh_tokens_430, 1, "other"},
    {"lockedRowAction", Dialect::MySQL, mysql_lockedRowAction_tokens_431, 2, "other"},
    {"lockedRowAction", Dialect::MySQL, mysql_lockedRowAction_tokens_432, 1, "other"},
    {"whereClause", Dialect::MySQL, mysql_whereClause_tokens_433, 2, "other"},
    {"tableReference", Dialect::MySQL, mysql_tableReference_tokens_434, 2, "other"},
    {"tableReference", Dialect::MySQL, mysql_tableReference_tokens_435, 7, "other"},
    {"tableReference", Dialect::MySQL, mysql_tableReference_tokens_436, 5, "other"},
    {"escapedTableReference", Dialect::MySQL, mysql_escapedTableReference_tokens_437, 2, "other"},
    {"joinedTable", Dialect::MySQL, mysql_joinedTable_tokens_438, 4, "other"},
    {"joinedTable", Dialect::MySQL, mysql_joinedTable_tokens_439, 4, "other"},
    {"joinedTable", Dialect::MySQL, mysql_joinedTable_tokens_440, 4, "other"},
    {"joinedTable", Dialect::MySQL, mysql_joinedTable_tokens_441, 4, "other"},
    {"joinedTable", Dialect::MySQL, mysql_joinedTable_tokens_442, 2, "other"},
    {"naturalJoinType", Dialect::MySQL, mysql_naturalJoinType_tokens_443, 3, "other"},
    {"naturalJoinType", Dialect::MySQL, mysql_naturalJoinType_tokens_444, 4, "other"},
    {"naturalJoinType", Dialect::MySQL, mysql_naturalJoinType_tokens_445, 4, "other"},
    {"innerJoinType", Dialect::MySQL, mysql_innerJoinType_tokens_446, 3, "other"},
    {"innerJoinType", Dialect::MySQL, mysql_innerJoinType_tokens_447, 3, "other"},
    {"innerJoinType", Dialect::MySQL, mysql_innerJoinType_tokens_448, 2, "other"},
    {"outerJoinType", Dialect::MySQL, mysql_outerJoinType_tokens_449, 4, "other"},
    {"outerJoinType", Dialect::MySQL, mysql_outerJoinType_tokens_450, 4, "other"},
    {"tableFactor", Dialect::MySQL, mysql_tableFactor_tokens_451, 1, "other"},
    {"tableFactor", Dialect::MySQL, mysql_tableFactor_tokens_452, 1, "other"},
    {"tableFactor", Dialect::MySQL, mysql_tableFactor_tokens_453, 1, "other"},
    {"tableFactor", Dialect::MySQL, mysql_tableFactor_tokens_454, 1, "other"},
    {"tableFactor", Dialect::MySQL, mysql_tableFactor_tokens_455, 3, "other"},
    {"singleTable", Dialect::MySQL, mysql_singleTable_tokens_456, 5, "other"},
    {"singleTableParens", Dialect::MySQL, mysql_singleTableParens_tokens_457, 3, "other"},
    {"singleTableParens", Dialect::MySQL, mysql_singleTableParens_tokens_458, 3, "other"},
    {"derivedTable", Dialect::MySQL, mysql_derivedTable_tokens_459, 3, "other"},
    {"derivedTable", Dialect::MySQL, mysql_derivedTable_tokens_460, 6, "other"},
    {"tableReferenceListParens", Dialect::MySQL, mysql_tableReferenceListParens_tokens_461, 3, "other"},
    {"tableReferenceListParens", Dialect::MySQL, mysql_tableReferenceListParens_tokens_462, 3, "other"},
    {"tableFunction", Dialect::MySQL, mysql_tableFunction_tokens_463, 8, "other"},
    {"columnsClause", Dialect::MySQL, mysql_columnsClause_tokens_464, 6, "other"},
    {"jtColumn", Dialect::MySQL, mysql_jtColumn_tokens_465, 3, "other"},
    {"jtColumn", Dialect::MySQL, mysql_jtColumn_tokens_466, 9, "other"},
    {"jtColumn", Dialect::MySQL, mysql_jtColumn_tokens_467, 4, "other"},
    {"onEmptyOrError", Dialect::MySQL, mysql_onEmptyOrError_tokens_468, 2, "other"},
    {"onEmptyOrError", Dialect::MySQL, mysql_onEmptyOrError_tokens_469, 1, "other"},
    {"onEmptyOrErrorJsonTable", Dialect::MySQL, mysql_onEmptyOrErrorJsonTable_tokens_470, 1, "other"},
    {"onEmptyOrErrorJsonTable", Dialect::MySQL, mysql_onEmptyOrErrorJsonTable_tokens_471, 2, "other"},
    {"onEmpty", Dialect::MySQL, mysql_onEmpty_tokens_472, 3, "other"},
    {"onError", Dialect::MySQL, mysql_onError_tokens_473, 3, "other"},
    {"jsonOnResponse", Dialect::MySQL, mysql_jsonOnResponse_tokens_474, 1, "other"},
    {"jsonOnResponse", Dialect::MySQL, mysql_jsonOnResponse_tokens_475, 1, "other"},
    {"jsonOnResponse", Dialect::MySQL, mysql_jsonOnResponse_tokens_476, 2, "other"},
    {"unionOption", Dialect::MySQL, mysql_unionOption_tokens_477, 1, "other"},
    {"unionOption", Dialect::MySQL, mysql_unionOption_tokens_478, 1, "other"},
    {"tableAlias", Dialect::MySQL, mysql_tableAlias_tokens_479, 2, "other"},
    {"tableAlias", Dialect::MySQL, mysql_tableAlias_tokens_480, 4, "other"},
    {"indexHintList", Dialect::MySQL, mysql_indexHintList_tokens_481, 3, "other"},
    {"indexHint", Dialect::MySQL, mysql_indexHint_tokens_482, 6, "other"},
    {"indexHint", Dialect::MySQL, mysql_indexHint_tokens_483, 6, "other"},
    {"indexHintType", Dialect::MySQL, mysql_indexHintType_tokens_484, 1, "other"},
    {"indexHintType", Dialect::MySQL, mysql_indexHintType_tokens_485, 1, "other"},
    {"keyOrIndex", Dialect::MySQL, mysql_keyOrIndex_tokens_486, 1, "other"},
    {"keyOrIndex", Dialect::MySQL, mysql_keyOrIndex_tokens_487, 1, "other"},
    {"constraintKeyType", Dialect::MySQL, mysql_constraintKeyType_tokens_488, 2, "other"},
    {"constraintKeyType", Dialect::MySQL, mysql_constraintKeyType_tokens_489, 2, "other"},
    {"indexHintClause", Dialect::MySQL, mysql_indexHintClause_tokens_490, 2, "other"},
    {"indexHintClause", Dialect::MySQL, mysql_indexHintClause_tokens_491, 3, "other"},
    {"indexHintClause", Dialect::MySQL, mysql_indexHintClause_tokens_492, 3, "other"},
    {"indexList", Dialect::MySQL, mysql_indexList_tokens_493, 3, "other"},
    {"indexListElement", Dialect::MySQL, mysql_indexListElement_tokens_494, 1, "other"},
    {"indexListElement", Dialect::MySQL, mysql_indexListElement_tokens_495, 1, "other"},
    {"transactionOrLockingStatement", Dialect::MySQL, mysql_transactionOrLockingStatement_tokens_496, 1, "other"},
    {"transactionOrLockingStatement", Dialect::MySQL, mysql_transactionOrLockingStatement_tokens_497, 1, "other"},
    {"transactionOrLockingStatement", Dialect::MySQL, mysql_transactionOrLockingStatement_tokens_498, 1, "other"},
    {"transactionOrLockingStatement", Dialect::MySQL, mysql_transactionOrLockingStatement_tokens_499, 1, "other"},
    {"transactionStatement", Dialect::MySQL, mysql_transactionStatement_tokens_500, 3, "other"},
    {"transactionStatement", Dialect::MySQL, mysql_transactionStatement_tokens_501, 7, "other"},
    {"beginWork", Dialect::MySQL, mysql_beginWork_tokens_502, 2, "other"},
    {"startTransactionOptionList", Dialect::MySQL, mysql_startTransactionOptionList_tokens_503, 3, "other"},
    {"startTransactionOptionList", Dialect::MySQL, mysql_startTransactionOptionList_tokens_504, 2, "other"},
    {"startTransactionOptionList", Dialect::MySQL, mysql_startTransactionOptionList_tokens_505, 2, "other"},
    {"savepointStatement", Dialect::MySQL, mysql_savepointStatement_tokens_506, 2, "other"},
    {"savepointStatement", Dialect::MySQL, mysql_savepointStatement_tokens_507, 5, "other"},
    {"savepointStatement", Dialect::MySQL, mysql_savepointStatement_tokens_508, 7, "other"},
    {"savepointStatement", Dialect::MySQL, mysql_savepointStatement_tokens_509, 3, "other"},
    {"lockStatement", Dialect::MySQL, mysql_lockStatement_tokens_510, 5, "other"},
    {"lockStatement", Dialect::MySQL, mysql_lockStatement_tokens_511, 5, "other"},
    {"lockStatement", Dialect::MySQL, mysql_lockStatement_tokens_512, 4, "other"},
    {"lockStatement", Dialect::MySQL, mysql_lockStatement_tokens_513, 2, "other"},
    {"lockStatement", Dialect::MySQL, mysql_lockStatement_tokens_514, 2, "other"},
    {"lockStatement", Dialect::MySQL, mysql_lockStatement_tokens_515, 2, "other"},
    {"lockItem", Dialect::MySQL, mysql_lockItem_tokens_516, 3, "other"},
    {"lockOption", Dialect::MySQL, mysql_lockOption_tokens_517, 2, "other"},
    {"lockOption", Dialect::MySQL, mysql_lockOption_tokens_518, 2, "other"},
    {"xaStatement", Dialect::MySQL, mysql_xaStatement_tokens_519, 4, "other"},
    {"xaStatement", Dialect::MySQL, mysql_xaStatement_tokens_520, 4, "other"},
    {"xaStatement", Dialect::MySQL, mysql_xaStatement_tokens_521, 4, "other"},
    {"xaStatement", Dialect::MySQL, mysql_xaStatement_tokens_522, 4, "other"},
    {"xaStatement", Dialect::MySQL, mysql_xaStatement_tokens_523, 6, "other"},
    {"xaStatement", Dialect::MySQL, mysql_xaStatement_tokens_524, 3, "other"},
    {"xaStatement", Dialect::MySQL, mysql_xaStatement_tokens_525, 5, "other"},
    {"xaStatement", Dialect::MySQL, mysql_xaStatement_tokens_526, 3, "other"},
    {"xaStatement", Dialect::MySQL, mysql_xaStatement_tokens_527, 3, "other"},
    {"xaConvert", Dialect::MySQL, mysql_xaConvert_tokens_528, 2, "other"},
    {"xid", Dialect::MySQL, mysql_xid_tokens_529, 5, "other"},
    {"replicationStatement", Dialect::MySQL, mysql_replicationStatement_tokens_530, 2, "other"},
    {"replicationStatement", Dialect::MySQL, mysql_replicationStatement_tokens_531, 1, "other"},
    {"replicationStatement", Dialect::MySQL, mysql_replicationStatement_tokens_532, 4, "other"},
    {"replicationStatement", Dialect::MySQL, mysql_replicationStatement_tokens_533, 3, "other"},
    {"replicationStatement", Dialect::MySQL, mysql_replicationStatement_tokens_534, 1, "other"},
    {"replicationStatement", Dialect::MySQL, mysql_replicationStatement_tokens_535, 1, "other"},
    {"replicationStatement", Dialect::MySQL, mysql_replicationStatement_tokens_536, 1, "other"},
    {"replicationStatement", Dialect::MySQL, mysql_replicationStatement_tokens_537, 1, "other"},
    {"replicationStatement", Dialect::MySQL, mysql_replicationStatement_tokens_538, 1, "other"},
    {"purgeOptions", Dialect::MySQL, mysql_purgeOptions_tokens_539, 4, "other"},
    {"purgeOptions", Dialect::MySQL, mysql_purgeOptions_tokens_540, 4, "other"},
    {"purgeOptions", Dialect::MySQL, mysql_purgeOptions_tokens_541, 4, "other"},
    {"purgeOptions", Dialect::MySQL, mysql_purgeOptions_tokens_542, 4, "other"},
    {"resetOption", Dialect::MySQL, mysql_resetOption_tokens_543, 2, "other"},
    {"resetOption", Dialect::MySQL, mysql_resetOption_tokens_544, 3, "other"},
    {"masterOrBinaryLogsAndGtids", Dialect::MySQL, mysql_masterOrBinaryLogsAndGtids_tokens_545, 1, "other"},
    {"masterOrBinaryLogsAndGtids", Dialect::MySQL, mysql_masterOrBinaryLogsAndGtids_tokens_546, 6, "other"},
    {"sourceResetOptions", Dialect::MySQL, mysql_sourceResetOptions_tokens_547, 2, "other"},
    {"replicationLoad", Dialect::MySQL, mysql_replicationLoad_tokens_548, 4, "other"},
    {"replicationLoad", Dialect::MySQL, mysql_replicationLoad_tokens_549, 5, "other"},
    {"changeReplicationSource", Dialect::MySQL, mysql_changeReplicationSource_tokens_550, 1, "other"},
    {"changeReplicationSource", Dialect::MySQL, mysql_changeReplicationSource_tokens_551, 4, "other"},
    {"changeSource", Dialect::MySQL, mysql_changeSource_tokens_552, 5, "other"},
    {"sourceDefinitions", Dialect::MySQL, mysql_sourceDefinitions_tokens_553, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_554, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_555, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_556, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_557, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_558, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_559, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_560, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_561, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_562, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_563, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_564, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_565, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_566, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_567, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_568, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_569, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_570, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_571, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_572, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_573, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_574, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_575, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_576, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_577, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_578, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_579, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_580, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_581, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_582, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_583, 3, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_584, 5, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_585, 5, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_586, 5, "other"},
    {"sourceDefinition", Dialect::MySQL, mysql_sourceDefinition_tokens_587, 1, "other"},
    {"changeReplicationSourceAutoPosition", Dialect::MySQL, mysql_changeReplicationSourceAutoPosition_tokens_588, 1, "other"},
    {"changeReplicationSourceAutoPosition", Dialect::MySQL, mysql_changeReplicationSourceAutoPosition_tokens_589, 1, "other"},
    {"changeReplicationSourceHost", Dialect::MySQL, mysql_changeReplicationSourceHost_tokens_590, 1, "other"},
    {"changeReplicationSourceHost", Dialect::MySQL, mysql_changeReplicationSourceHost_tokens_591, 1, "other"},
    {"changeReplicationSourceBind", Dialect::MySQL, mysql_changeReplicationSourceBind_tokens_592, 1, "other"},
    {"changeReplicationSourceBind", Dialect::MySQL, mysql_changeReplicationSourceBind_tokens_593, 1, "other"},
    {"changeReplicationSourceUser", Dialect::MySQL, mysql_changeReplicationSourceUser_tokens_594, 1, "other"},
    {"changeReplicationSourceUser", Dialect::MySQL, mysql_changeReplicationSourceUser_tokens_595, 1, "other"},
    {"changeReplicationSourcePassword", Dialect::MySQL, mysql_changeReplicationSourcePassword_tokens_596, 1, "other"},
    {"changeReplicationSourcePassword", Dialect::MySQL, mysql_changeReplicationSourcePassword_tokens_597, 1, "other"},
    {"changeReplicationSourcePort", Dialect::MySQL, mysql_changeReplicationSourcePort_tokens_598, 1, "other"},
    {"changeReplicationSourcePort", Dialect::MySQL, mysql_changeReplicationSourcePort_tokens_599, 1, "other"},
    {"changeReplicationSourceConnectRetry", Dialect::MySQL, mysql_changeReplicationSourceConnectRetry_tokens_600, 1, "other"},
    {"changeReplicationSourceConnectRetry", Dialect::MySQL, mysql_changeReplicationSourceConnectRetry_tokens_601, 1, "other"},
    {"changeReplicationSourceRetryCount", Dialect::MySQL, mysql_changeReplicationSourceRetryCount_tokens_602, 1, "other"},
    {"changeReplicationSourceRetryCount", Dialect::MySQL, mysql_changeReplicationSourceRetryCount_tokens_603, 1, "other"},
    {"changeReplicationSourceDelay", Dialect::MySQL, mysql_changeReplicationSourceDelay_tokens_604, 1, "other"},
    {"changeReplicationSourceDelay", Dialect::MySQL, mysql_changeReplicationSourceDelay_tokens_605, 1, "other"},
    {"changeReplicationSourceSSL", Dialect::MySQL, mysql_changeReplicationSourceSSL_tokens_606, 1, "other"},
    {"changeReplicationSourceSSL", Dialect::MySQL, mysql_changeReplicationSourceSSL_tokens_607, 1, "other"},
    {"changeReplicationSourceSSLCA", Dialect::MySQL, mysql_changeReplicationSourceSSLCA_tokens_608, 1, "other"},
    {"changeReplicationSourceSSLCA", Dialect::MySQL, mysql_changeReplicationSourceSSLCA_tokens_609, 1, "other"},
    {"changeReplicationSourceSSLCApath", Dialect::MySQL, mysql_changeReplicationSourceSSLCApath_tokens_610, 1, "other"},
    {"changeReplicationSourceSSLCApath", Dialect::MySQL, mysql_changeReplicationSourceSSLCApath_tokens_611, 1, "other"},
    {"changeReplicationSourceSSLCipher", Dialect::MySQL, mysql_changeReplicationSourceSSLCipher_tokens_612, 1, "other"},
    {"changeReplicationSourceSSLCipher", Dialect::MySQL, mysql_changeReplicationSourceSSLCipher_tokens_613, 1, "other"},
    {"changeReplicationSourceSSLCLR", Dialect::MySQL, mysql_changeReplicationSourceSSLCLR_tokens_614, 1, "other"},
    {"changeReplicationSourceSSLCLR", Dialect::MySQL, mysql_changeReplicationSourceSSLCLR_tokens_615, 1, "other"},
    {"changeReplicationSourceSSLCLRpath", Dialect::MySQL, mysql_changeReplicationSourceSSLCLRpath_tokens_616, 1, "other"},
    {"changeReplicationSourceSSLCLRpath", Dialect::MySQL, mysql_changeReplicationSourceSSLCLRpath_tokens_617, 1, "other"},
    {"changeReplicationSourceSSLKey", Dialect::MySQL, mysql_changeReplicationSourceSSLKey_tokens_618, 1, "other"},
    {"changeReplicationSourceSSLKey", Dialect::MySQL, mysql_changeReplicationSourceSSLKey_tokens_619, 1, "other"},
    {"changeReplicationSourceSSLVerifyServerCert", Dialect::MySQL, mysql_changeReplicationSourceSSLVerifyServerCert_tokens_620, 1, "other"},
    {"changeReplicationSourceSSLVerifyServerCert", Dialect::MySQL, mysql_changeReplicationSourceSSLVerifyServerCert_tokens_621, 1, "other"},
    {"changeReplicationSourceTLSVersion", Dialect::MySQL, mysql_changeReplicationSourceTLSVersion_tokens_622, 1, "other"},
    {"changeReplicationSourceTLSVersion", Dialect::MySQL, mysql_changeReplicationSourceTLSVersion_tokens_623, 1, "other"},
    {"changeReplicationSourceTLSCiphersuites", Dialect::MySQL, mysql_changeReplicationSourceTLSCiphersuites_tokens_624, 1, "other"},
    {"changeReplicationSourceTLSCiphersuites", Dialect::MySQL, mysql_changeReplicationSourceTLSCiphersuites_tokens_625, 1, "other"},
    {"changeReplicationSourceSSLCert", Dialect::MySQL, mysql_changeReplicationSourceSSLCert_tokens_626, 1, "other"},
    {"changeReplicationSourceSSLCert", Dialect::MySQL, mysql_changeReplicationSourceSSLCert_tokens_627, 1, "other"},
    {"changeReplicationSourcePublicKey", Dialect::MySQL, mysql_changeReplicationSourcePublicKey_tokens_628, 1, "other"},
    {"changeReplicationSourcePublicKey", Dialect::MySQL, mysql_changeReplicationSourcePublicKey_tokens_629, 1, "other"},
    {"changeReplicationSourceGetSourcePublicKey", Dialect::MySQL, mysql_changeReplicationSourceGetSourcePublicKey_tokens_630, 1, "other"},
    {"changeReplicationSourceGetSourcePublicKey", Dialect::MySQL, mysql_changeReplicationSourceGetSourcePublicKey_tokens_631, 1, "other"},
    {"changeReplicationSourceHeartbeatPeriod", Dialect::MySQL, mysql_changeReplicationSourceHeartbeatPeriod_tokens_632, 1, "other"},
    {"changeReplicationSourceHeartbeatPeriod", Dialect::MySQL, mysql_changeReplicationSourceHeartbeatPeriod_tokens_633, 1, "other"},
    {"changeReplicationSourceCompressionAlgorithm", Dialect::MySQL, mysql_changeReplicationSourceCompressionAlgorithm_tokens_634, 1, "other"},
    {"changeReplicationSourceCompressionAlgorithm", Dialect::MySQL, mysql_changeReplicationSourceCompressionAlgorithm_tokens_635, 1, "other"},
    {"changeReplicationSourceZstdCompressionLevel", Dialect::MySQL, mysql_changeReplicationSourceZstdCompressionLevel_tokens_636, 1, "other"},
    {"changeReplicationSourceZstdCompressionLevel", Dialect::MySQL, mysql_changeReplicationSourceZstdCompressionLevel_tokens_637, 1, "other"},
    {"privilegeCheckDef", Dialect::MySQL, mysql_privilegeCheckDef_tokens_638, 1, "other"},
    {"privilegeCheckDef", Dialect::MySQL, mysql_privilegeCheckDef_tokens_639, 1, "other"},
    {"tablePrimaryKeyCheckDef", Dialect::MySQL, mysql_tablePrimaryKeyCheckDef_tokens_640, 1, "other"},
    {"tablePrimaryKeyCheckDef", Dialect::MySQL, mysql_tablePrimaryKeyCheckDef_tokens_641, 1, "other"},
    {"tablePrimaryKeyCheckDef", Dialect::MySQL, mysql_tablePrimaryKeyCheckDef_tokens_642, 1, "other"},
    {"tablePrimaryKeyCheckDef", Dialect::MySQL, mysql_tablePrimaryKeyCheckDef_tokens_643, 1, "other"},
    {"assignGtidsToAnonymousTransactionsDefinition", Dialect::MySQL, mysql_assignGtidsToAnonymousTransactionsDefinition_tokens_644, 1, "other"},
    {"assignGtidsToAnonymousTransactionsDefinition", Dialect::MySQL, mysql_assignGtidsToAnonymousTransactionsDefinition_tokens_645, 1, "other"},
    {"assignGtidsToAnonymousTransactionsDefinition", Dialect::MySQL, mysql_assignGtidsToAnonymousTransactionsDefinition_tokens_646, 1, "other"},
    {"sourceTlsCiphersuitesDef", Dialect::MySQL, mysql_sourceTlsCiphersuitesDef_tokens_647, 1, "other"},
    {"sourceTlsCiphersuitesDef", Dialect::MySQL, mysql_sourceTlsCiphersuitesDef_tokens_648, 1, "other"},
    {"sourceFileDef", Dialect::MySQL, mysql_sourceFileDef_tokens_649, 3, "other"},
    {"sourceFileDef", Dialect::MySQL, mysql_sourceFileDef_tokens_650, 3, "other"},
    {"sourceFileDef", Dialect::MySQL, mysql_sourceFileDef_tokens_651, 3, "other"},
    {"sourceFileDef", Dialect::MySQL, mysql_sourceFileDef_tokens_652, 3, "other"},
    {"sourceLogFile", Dialect::MySQL, mysql_sourceLogFile_tokens_653, 1, "other"},
    {"sourceLogFile", Dialect::MySQL, mysql_sourceLogFile_tokens_654, 1, "other"},
    {"sourceLogPos", Dialect::MySQL, mysql_sourceLogPos_tokens_655, 1, "other"},
    {"sourceLogPos", Dialect::MySQL, mysql_sourceLogPos_tokens_656, 1, "other"},
    {"serverIdList", Dialect::MySQL, mysql_serverIdList_tokens_657, 5, "other"},
    {"changeReplication", Dialect::MySQL, mysql_changeReplication_tokens_658, 7, "other"},
    {"filterDefinition", Dialect::MySQL, mysql_filterDefinition_tokens_659, 5, "other"},
    {"filterDefinition", Dialect::MySQL, mysql_filterDefinition_tokens_660, 5, "other"},
    {"filterDefinition", Dialect::MySQL, mysql_filterDefinition_tokens_661, 5, "other"},
    {"filterDefinition", Dialect::MySQL, mysql_filterDefinition_tokens_662, 5, "other"},
    {"filterDefinition", Dialect::MySQL, mysql_filterDefinition_tokens_663, 5, "other"},
    {"filterDefinition", Dialect::MySQL, mysql_filterDefinition_tokens_664, 5, "other"},
    {"filterDefinition", Dialect::MySQL, mysql_filterDefinition_tokens_665, 5, "other"},
    {"filterDbList", Dialect::MySQL, mysql_filterDbList_tokens_666, 3, "other"},
    {"filterTableList", Dialect::MySQL, mysql_filterTableList_tokens_667, 3, "other"},
    {"filterStringList", Dialect::MySQL, mysql_filterStringList_tokens_668, 3, "other"},
    {"filterWildDbTableString", Dialect::MySQL, mysql_filterWildDbTableString_tokens_669, 1, "other"},
    {"filterDbPairList", Dialect::MySQL, mysql_filterDbPairList_tokens_670, 3, "other"},
    {"startReplicaStatement", Dialect::MySQL, mysql_startReplicaStatement_tokens_671, 10, "other"},
    {"stopReplicaStatement", Dialect::MySQL, mysql_stopReplicaStatement_tokens_672, 4, "other"},
    {"replicaUntil", Dialect::MySQL, mysql_replicaUntil_tokens_673, 3, "other"},
    {"replicaUntil", Dialect::MySQL, mysql_replicaUntil_tokens_674, 5, "other"},
    {"replicaUntil", Dialect::MySQL, mysql_replicaUntil_tokens_675, 5, "other"},
    {"replicaUntil", Dialect::MySQL, mysql_replicaUntil_tokens_676, 3, "other"},
    {"userOption", Dialect::MySQL, mysql_userOption_tokens_677, 3, "other"},
    {"passwordOption", Dialect::MySQL, mysql_passwordOption_tokens_678, 3, "other"},
    {"defaultAuthOption", Dialect::MySQL, mysql_defaultAuthOption_tokens_679, 3, "other"},
    {"pluginDirOption", Dialect::MySQL, mysql_pluginDirOption_tokens_680, 3, "other"},
    {"replicaThreadOptions", Dialect::MySQL, mysql_replicaThreadOptions_tokens_681, 3, "other"},
    {"replicaThreadOption", Dialect::MySQL, mysql_replicaThreadOption_tokens_682, 1, "other"},
    {"replicaThreadOption", Dialect::MySQL, mysql_replicaThreadOption_tokens_683, 1, "other"},
    {"groupReplication", Dialect::MySQL, mysql_groupReplication_tokens_684, 3, "other"},
    {"groupReplication", Dialect::MySQL, mysql_groupReplication_tokens_685, 2, "other"},
    {"groupReplicationStartOptions", Dialect::MySQL, mysql_groupReplicationStartOptions_tokens_686, 3, "other"},
    {"groupReplicationStartOption", Dialect::MySQL, mysql_groupReplicationStartOption_tokens_687, 1, "other"},
    {"groupReplicationStartOption", Dialect::MySQL, mysql_groupReplicationStartOption_tokens_688, 1, "other"},
    {"groupReplicationStartOption", Dialect::MySQL, mysql_groupReplicationStartOption_tokens_689, 1, "other"},
    {"groupReplicationUser", Dialect::MySQL, mysql_groupReplicationUser_tokens_690, 3, "other"},
    {"groupReplicationPassword", Dialect::MySQL, mysql_groupReplicationPassword_tokens_691, 3, "other"},
    {"groupReplicationPluginAuth", Dialect::MySQL, mysql_groupReplicationPluginAuth_tokens_692, 3, "other"},
    {"replica", Dialect::MySQL, mysql_replica_tokens_693, 1, "other"},
    {"replica", Dialect::MySQL, mysql_replica_tokens_694, 1, "other"},
    {"preparedStatement", Dialect::MySQL, mysql_preparedStatement_tokens_695, 5, "other"},
    {"preparedStatement", Dialect::MySQL, mysql_preparedStatement_tokens_696, 5, "other"},
    {"preparedStatement", Dialect::MySQL, mysql_preparedStatement_tokens_697, 1, "other"},
    {"preparedStatement", Dialect::MySQL, mysql_preparedStatement_tokens_698, 4, "other"},
    {"preparedStatement", Dialect::MySQL, mysql_preparedStatement_tokens_699, 4, "other"},
    {"executeStatement", Dialect::MySQL, mysql_executeStatement_tokens_700, 4, "other"},
    {"executeVarList", Dialect::MySQL, mysql_executeVarList_tokens_701, 3, "other"},
    {"cloneStatement", Dialect::MySQL, mysql_cloneStatement_tokens_702, 6, "other"},
    {"cloneStatement", Dialect::MySQL, mysql_cloneStatement_tokens_703, 4, "other"},
    {"cloneStatement", Dialect::MySQL, mysql_cloneStatement_tokens_704, 12, "other"},
    {"dataDirSSL", Dialect::MySQL, mysql_dataDirSSL_tokens_705, 1, "other"},
    {"dataDirSSL", Dialect::MySQL, mysql_dataDirSSL_tokens_706, 5, "other"},
    {"ssl", Dialect::MySQL, mysql_ssl_tokens_707, 3, "other"},
    {"accountManagementStatement", Dialect::MySQL, mysql_accountManagementStatement_tokens_708, 1, "other"},
    {"accountManagementStatement", Dialect::MySQL, mysql_accountManagementStatement_tokens_709, 1, "other"},
    {"accountManagementStatement", Dialect::MySQL, mysql_accountManagementStatement_tokens_710, 1, "other"},
    {"accountManagementStatement", Dialect::MySQL, mysql_accountManagementStatement_tokens_711, 1, "other"},
    {"accountManagementStatement", Dialect::MySQL, mysql_accountManagementStatement_tokens_712, 1, "other"},
    {"accountManagementStatement", Dialect::MySQL, mysql_accountManagementStatement_tokens_713, 1, "other"},
    {"accountManagementStatement", Dialect::MySQL, mysql_accountManagementStatement_tokens_714, 1, "other"},
    {"alterUserStatement", Dialect::MySQL, mysql_alterUserStatement_tokens_715, 7, "other"},
    {"alterUserStatement", Dialect::MySQL, mysql_alterUserStatement_tokens_716, 7, "other"},
    {"alterUserStatement", Dialect::MySQL, mysql_alterUserStatement_tokens_717, 7, "other"},
    {"alterUserStatement", Dialect::MySQL, mysql_alterUserStatement_tokens_718, 7, "other"},
    {"alterUserStatement", Dialect::MySQL, mysql_alterUserStatement_tokens_719, 7, "other"},
    {"alterUserStatement", Dialect::MySQL, mysql_alterUserStatement_tokens_720, 5, "other"},
    {"alterUserStatement", Dialect::MySQL, mysql_alterUserStatement_tokens_721, 7, "other"},
    {"alterUserStatement", Dialect::MySQL, mysql_alterUserStatement_tokens_722, 7, "other"},
    {"alterUserStatement", Dialect::MySQL, mysql_alterUserStatement_tokens_723, 7, "other"},
    {"alterUserStatement", Dialect::MySQL, mysql_alterUserStatement_tokens_724, 5, "other"},
    {"alterUserList", Dialect::MySQL, mysql_alterUserList_tokens_725, 3, "other"},
    {"alterUser", Dialect::MySQL, mysql_alterUser_tokens_726, 3, "other"},
    {"alterUser", Dialect::MySQL, mysql_alterUser_tokens_727, 7, "other"},
    {"alterUser", Dialect::MySQL, mysql_alterUser_tokens_728, 5, "other"},
    {"alterUser", Dialect::MySQL, mysql_alterUser_tokens_729, 5, "other"},
    {"alterUser", Dialect::MySQL, mysql_alterUser_tokens_730, 7, "other"},
    {"alterUser", Dialect::MySQL, mysql_alterUser_tokens_731, 4, "other"},
    {"alterUser", Dialect::MySQL, mysql_alterUser_tokens_732, 5, "other"},
    {"alterUser", Dialect::MySQL, mysql_alterUser_tokens_733, 7, "other"},
    {"alterUser", Dialect::MySQL, mysql_alterUser_tokens_734, 5, "other"},
    {"alterUser", Dialect::MySQL, mysql_alterUser_tokens_735, 5, "other"},
    {"alterUser", Dialect::MySQL, mysql_alterUser_tokens_736, 4, "other"},
    {"alterUser", Dialect::MySQL, mysql_alterUser_tokens_737, 9, "other"},
    {"alterUser", Dialect::MySQL, mysql_alterUser_tokens_738, 9, "other"},
    {"alterUser", Dialect::MySQL, mysql_alterUser_tokens_739, 7, "other"},
    {"oldAlterUser", Dialect::MySQL, mysql_oldAlterUser_tokens_740, 7, "other"},
    {"oldAlterUser", Dialect::MySQL, mysql_oldAlterUser_tokens_741, 5, "other"},
    {"oldAlterUser", Dialect::MySQL, mysql_oldAlterUser_tokens_742, 8, "other"},
    {"oldAlterUser", Dialect::MySQL, mysql_oldAlterUser_tokens_743, 9, "other"},
    {"oldAlterUser", Dialect::MySQL, mysql_oldAlterUser_tokens_744, 7, "other"},
    {"oldAlterUser", Dialect::MySQL, mysql_oldAlterUser_tokens_745, 7, "other"},
    {"oldAlterUser", Dialect::MySQL, mysql_oldAlterUser_tokens_746, 8, "other"},
    {"oldAlterUser", Dialect::MySQL, mysql_oldAlterUser_tokens_747, 2, "other"},
    {"userFunction", Dialect::MySQL, mysql_userFunction_tokens_748, 2, "other"},
    {"userAttributes", Dialect::MySQL, mysql_userAttributes_tokens_749, 2, "other"},
    {"userAttributes", Dialect::MySQL, mysql_userAttributes_tokens_750, 2, "other"},
    {"defaultRoleClause", Dialect::MySQL, mysql_defaultRoleClause_tokens_751, 3, "other"},
    {"requireClause", Dialect::MySQL, mysql_requireClause_tokens_752, 2, "other"},
    {"requireClause", Dialect::MySQL, mysql_requireClause_tokens_753, 3, "other"},
    {"requireClause", Dialect::MySQL, mysql_requireClause_tokens_754, 3, "other"},
    {"requireClause", Dialect::MySQL, mysql_requireClause_tokens_755, 3, "other"},
    {"connectOptions", Dialect::MySQL, mysql_connectOptions_tokens_756, 3, "other"},
    {"connectOptions", Dialect::MySQL, mysql_connectOptions_tokens_757, 3, "other"},
    {"connectOptions", Dialect::MySQL, mysql_connectOptions_tokens_758, 3, "other"},
    {"connectOptions", Dialect::MySQL, mysql_connectOptions_tokens_759, 3, "other"},
    {"accountLockPasswordExpireOptions", Dialect::MySQL, mysql_accountLockPasswordExpireOptions_tokens_760, 2, "other"},
    {"accountLockPasswordExpireOptions", Dialect::MySQL, mysql_accountLockPasswordExpireOptions_tokens_761, 2, "other"},
    {"accountLockPasswordExpireOptions", Dialect::MySQL, mysql_accountLockPasswordExpireOptions_tokens_762, 5, "other"},
    {"accountLockPasswordExpireOptions", Dialect::MySQL, mysql_accountLockPasswordExpireOptions_tokens_763, 3, "other"},
    {"accountLockPasswordExpireOptions", Dialect::MySQL, mysql_accountLockPasswordExpireOptions_tokens_764, 3, "other"},
    {"accountLockPasswordExpireOptions", Dialect::MySQL, mysql_accountLockPasswordExpireOptions_tokens_765, 3, "other"},
    {"accountLockPasswordExpireOptions", Dialect::MySQL, mysql_accountLockPasswordExpireOptions_tokens_766, 3, "other"},
    {"accountLockPasswordExpireOptions", Dialect::MySQL, mysql_accountLockPasswordExpireOptions_tokens_767, 5, "other"},
    {"accountLockPasswordExpireOptions", Dialect::MySQL, mysql_accountLockPasswordExpireOptions_tokens_768, 4, "other"},
    {"accountLockPasswordExpireOptions", Dialect::MySQL, mysql_accountLockPasswordExpireOptions_tokens_769, 6, "other"},
    {"accountLockPasswordExpireOptions", Dialect::MySQL, mysql_accountLockPasswordExpireOptions_tokens_770, 6, "other"},
    {"accountLockPasswordExpireOptions", Dialect::MySQL, mysql_accountLockPasswordExpireOptions_tokens_771, 2, "other"},
    {"accountLockPasswordExpireOptions", Dialect::MySQL, mysql_accountLockPasswordExpireOptions_tokens_772, 2, "other"},
    {"accountLockPasswordExpireOptions", Dialect::MySQL, mysql_accountLockPasswordExpireOptions_tokens_773, 2, "other"},
    {"userAttribute", Dialect::MySQL, mysql_userAttribute_tokens_774, 2, "other"},
    {"userAttribute", Dialect::MySQL, mysql_userAttribute_tokens_775, 2, "other"},
    {"grantStatement", Dialect::MySQL, mysql_grantStatement_tokens_776, 7, "other"},
    {"grantStatement", Dialect::MySQL, mysql_grantStatement_tokens_777, 10, "other"},
    {"grantStatement", Dialect::MySQL, mysql_grantStatement_tokens_778, 11, "other"},
    {"grantStatement", Dialect::MySQL, mysql_grantStatement_tokens_779, 9, "other"},
    {"grantTargetList", Dialect::MySQL, mysql_grantTargetList_tokens_780, 3, "other"},
    {"grantTargetList", Dialect::MySQL, mysql_grantTargetList_tokens_781, 3, "other"},
    {"grantOptions", Dialect::MySQL, mysql_grantOptions_tokens_782, 2, "other"},
    {"exceptRoleList", Dialect::MySQL, mysql_exceptRoleList_tokens_783, 2, "other"},
    {"withRoles", Dialect::MySQL, mysql_withRoles_tokens_784, 3, "other"},
    {"withRoles", Dialect::MySQL, mysql_withRoles_tokens_785, 4, "other"},
    {"withRoles", Dialect::MySQL, mysql_withRoles_tokens_786, 3, "other"},
    {"withRoles", Dialect::MySQL, mysql_withRoles_tokens_787, 3, "other"},
    {"grantAs", Dialect::MySQL, mysql_grantAs_tokens_788, 3, "other"},
    {"versionedRequireClause", Dialect::MySQL, mysql_versionedRequireClause_tokens_789, 3, "other"},
    {"renameUserStatement", Dialect::MySQL, mysql_renameUserStatement_tokens_790, 9, "other"},
    {"revokeStatement", Dialect::MySQL, mysql_revokeStatement_tokens_791, 10, "other"},
    {"revokeStatement", Dialect::MySQL, mysql_revokeStatement_tokens_792, 13, "other"},
    {"revokeStatement", Dialect::MySQL, mysql_revokeStatement_tokens_793, 14, "other"},
    {"revokeStatement", Dialect::MySQL, mysql_revokeStatement_tokens_794, 14, "other"},
    {"revokeStatement", Dialect::MySQL, mysql_revokeStatement_tokens_795, 12, "other"},
    {"aclType", Dialect::MySQL, mysql_aclType_tokens_796, 1, "other"},
    {"aclType", Dialect::MySQL, mysql_aclType_tokens_797, 1, "other"},
    {"aclType", Dialect::MySQL, mysql_aclType_tokens_798, 1, "other"},
    {"roleOrPrivilegesList", Dialect::MySQL, mysql_roleOrPrivilegesList_tokens_799, 3, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_800, 2, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_801, 2, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_802, 3, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_803, 2, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_804, 2, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_805, 2, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_806, 2, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_807, 1, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_808, 1, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_809, 1, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_810, 1, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_811, 1, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_812, 1, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_813, 1, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_814, 1, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_815, 1, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_816, 1, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_817, 1, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_818, 1, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_819, 1, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_820, 2, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_821, 2, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_822, 4, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_823, 3, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_824, 3, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_825, 3, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_826, 3, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_827, 2, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_828, 2, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_829, 2, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_830, 2, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_831, 2, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_832, 2, "other"},
    {"roleOrPrivilege", Dialect::MySQL, mysql_roleOrPrivilege_tokens_833, 2, "other"},
    {"grantIdentifier", Dialect::MySQL, mysql_grantIdentifier_tokens_834, 3, "other"},
    {"grantIdentifier", Dialect::MySQL, mysql_grantIdentifier_tokens_835, 3, "other"},
    {"grantIdentifier", Dialect::MySQL, mysql_grantIdentifier_tokens_836, 1, "other"},
    {"grantIdentifier", Dialect::MySQL, mysql_grantIdentifier_tokens_837, 5, "other"},
    {"requireList", Dialect::MySQL, mysql_requireList_tokens_838, 3, "other"},
    {"requireListElement", Dialect::MySQL, mysql_requireListElement_tokens_839, 3, "other"},
    {"requireListElement", Dialect::MySQL, mysql_requireListElement_tokens_840, 3, "other"},
    {"requireListElement", Dialect::MySQL, mysql_requireListElement_tokens_841, 3, "other"},
    {"grantOption", Dialect::MySQL, mysql_grantOption_tokens_842, 3, "other"},
    {"grantOption", Dialect::MySQL, mysql_grantOption_tokens_843, 5, "other"},
    {"grantOption", Dialect::MySQL, mysql_grantOption_tokens_844, 5, "other"},
    {"grantOption", Dialect::MySQL, mysql_grantOption_tokens_845, 5, "other"},
    {"grantOption", Dialect::MySQL, mysql_grantOption_tokens_846, 5, "other"},
    {"setRoleStatement", Dialect::MySQL, mysql_setRoleStatement_tokens_847, 3, "other"},
    {"setRoleStatement", Dialect::MySQL, mysql_setRoleStatement_tokens_848, 3, "other"},
    {"setRoleStatement", Dialect::MySQL, mysql_setRoleStatement_tokens_849, 3, "other"},
    {"setRoleStatement", Dialect::MySQL, mysql_setRoleStatement_tokens_850, 6, "other"},
    {"setRoleStatement", Dialect::MySQL, mysql_setRoleStatement_tokens_851, 6, "other"},
    {"setRoleStatement", Dialect::MySQL, mysql_setRoleStatement_tokens_852, 6, "other"},
    {"setRoleStatement", Dialect::MySQL, mysql_setRoleStatement_tokens_853, 5, "other"},
    {"roleList", Dialect::MySQL, mysql_roleList_tokens_854, 3, "other"},
    {"role", Dialect::MySQL, mysql_role_tokens_855, 2, "other"},
    {"tableAdministrationStatement", Dialect::MySQL, mysql_tableAdministrationStatement_tokens_856, 6, "other"},
    {"tableAdministrationStatement", Dialect::MySQL, mysql_tableAdministrationStatement_tokens_857, 5, "other"},
    {"tableAdministrationStatement", Dialect::MySQL, mysql_tableAdministrationStatement_tokens_858, 5, "other"},
    {"tableAdministrationStatement", Dialect::MySQL, mysql_tableAdministrationStatement_tokens_859, 5, "other"},
    {"tableAdministrationStatement", Dialect::MySQL, mysql_tableAdministrationStatement_tokens_860, 5, "other"},
    {"tableAdministrationStatement", Dialect::MySQL, mysql_tableAdministrationStatement_tokens_861, 6, "other"},
    {"histogramNumBuckets", Dialect::MySQL, mysql_histogramNumBuckets_tokens_862, 5, "other"},
    {"histogram", Dialect::MySQL, mysql_histogram_tokens_863, 5, "other"},
    {"histogram", Dialect::MySQL, mysql_histogram_tokens_864, 4, "other"},
    {"checkOption", Dialect::MySQL, mysql_checkOption_tokens_865, 2, "other"},
    {"checkOption", Dialect::MySQL, mysql_checkOption_tokens_866, 1, "other"},
    {"checkOption", Dialect::MySQL, mysql_checkOption_tokens_867, 1, "other"},
    {"checkOption", Dialect::MySQL, mysql_checkOption_tokens_868, 1, "other"},
    {"checkOption", Dialect::MySQL, mysql_checkOption_tokens_869, 1, "other"},
    {"checkOption", Dialect::MySQL, mysql_checkOption_tokens_870, 1, "other"},
    {"repairType", Dialect::MySQL, mysql_repairType_tokens_871, 1, "other"},
    {"repairType", Dialect::MySQL, mysql_repairType_tokens_872, 1, "other"},
    {"repairType", Dialect::MySQL, mysql_repairType_tokens_873, 1, "other"},
    {"uninstallStatement", Dialect::MySQL, mysql_uninstallStatement_tokens_874, 3, "other"},
    {"uninstallStatement", Dialect::MySQL, mysql_uninstallStatement_tokens_875, 5, "other"},
    {"installStatement", Dialect::MySQL, mysql_installStatement_tokens_876, 5, "other"},
    {"installStatement", Dialect::MySQL, mysql_installStatement_tokens_877, 4, "other"},
    {"installOptionType", Dialect::MySQL, mysql_installOptionType_tokens_878, 1, "other"},
    {"installOptionType", Dialect::MySQL, mysql_installOptionType_tokens_879, 1, "other"},
    {"installSetRvalue", Dialect::MySQL, mysql_installSetRvalue_tokens_880, 1, "other"},
    {"installSetRvalue", Dialect::MySQL, mysql_installSetRvalue_tokens_881, 1, "other"},
    {"installSetValue", Dialect::MySQL, mysql_installSetValue_tokens_882, 4, "other"},
    {"installSetValueList", Dialect::MySQL, mysql_installSetValueList_tokens_883, 6, "other"},
    {"setStatement", Dialect::MySQL, mysql_setStatement_tokens_884, 2, "other"},
    {"startOptionValueList", Dialect::MySQL, mysql_startOptionValueList_tokens_885, 2, "other"},
    {"startOptionValueList", Dialect::MySQL, mysql_startOptionValueList_tokens_886, 2, "other"},
    {"startOptionValueList", Dialect::MySQL, mysql_startOptionValueList_tokens_887, 2, "other"},
    {"startOptionValueList", Dialect::MySQL, mysql_startOptionValueList_tokens_888, 7, "other"},
    {"startOptionValueList", Dialect::MySQL, mysql_startOptionValueList_tokens_889, 7, "other"},
    {"startOptionValueList", Dialect::MySQL, mysql_startOptionValueList_tokens_890, 10, "other"},
    {"startOptionValueList", Dialect::MySQL, mysql_startOptionValueList_tokens_891, 9, "other"},
    {"transactionCharacteristics", Dialect::MySQL, mysql_transactionCharacteristics_tokens_892, 2, "other"},
    {"transactionCharacteristics", Dialect::MySQL, mysql_transactionCharacteristics_tokens_893, 3, "other"},
    {"transactionAccessMode", Dialect::MySQL, mysql_transactionAccessMode_tokens_894, 2, "other"},
    {"transactionAccessMode", Dialect::MySQL, mysql_transactionAccessMode_tokens_895, 2, "other"},
    {"isolationLevel", Dialect::MySQL, mysql_isolationLevel_tokens_896, 4, "other"},
    {"isolationLevel", Dialect::MySQL, mysql_isolationLevel_tokens_897, 4, "other"},
    {"isolationLevel", Dialect::MySQL, mysql_isolationLevel_tokens_898, 4, "other"},
    {"isolationLevel", Dialect::MySQL, mysql_isolationLevel_tokens_899, 3, "other"},
    {"optionValueListContinued", Dialect::MySQL, mysql_optionValueListContinued_tokens_900, 2, "other"},
    {"optionValueNoOptionType", Dialect::MySQL, mysql_optionValueNoOptionType_tokens_901, 3, "other"},
    {"optionValueNoOptionType", Dialect::MySQL, mysql_optionValueNoOptionType_tokens_902, 1, "other"},
    {"optionValueNoOptionType", Dialect::MySQL, mysql_optionValueNoOptionType_tokens_903, 3, "other"},
    {"optionValueNoOptionType", Dialect::MySQL, mysql_optionValueNoOptionType_tokens_904, 5, "other"},
    {"optionValueNoOptionType", Dialect::MySQL, mysql_optionValueNoOptionType_tokens_905, 3, "other"},
    {"optionValueNoOptionType", Dialect::MySQL, mysql_optionValueNoOptionType_tokens_906, 3, "other"},
    {"optionValueNoOptionType", Dialect::MySQL, mysql_optionValueNoOptionType_tokens_907, 4, "other"},
    {"optionValue", Dialect::MySQL, mysql_optionValue_tokens_908, 4, "other"},
    {"optionValue", Dialect::MySQL, mysql_optionValue_tokens_909, 1, "other"},
    {"setSystemVariable", Dialect::MySQL, mysql_setSystemVariable_tokens_910, 3, "other"},
    {"startOptionValueListFollowingOptionType", Dialect::MySQL, mysql_startOptionValueListFollowingOptionType_tokens_911, 2, "other"},
    {"startOptionValueListFollowingOptionType", Dialect::MySQL, mysql_startOptionValueListFollowingOptionType_tokens_912, 2, "other"},
    {"optionValueFollowingOptionType", Dialect::MySQL, mysql_optionValueFollowingOptionType_tokens_913, 3, "other"},
    {"showDatabasesStatement", Dialect::MySQL, mysql_showDatabasesStatement_tokens_914, 3, "other"},
    {"showTablesStatement", Dialect::MySQL, mysql_showTablesStatement_tokens_915, 6, "other"},
    {"showTriggersStatement", Dialect::MySQL, mysql_showTriggersStatement_tokens_916, 5, "other"},
    {"showEventsStatement", Dialect::MySQL, mysql_showEventsStatement_tokens_917, 4, "other"},
    {"showTableStatusStatement", Dialect::MySQL, mysql_showTableStatusStatement_tokens_918, 5, "other"},
    {"showOpenTablesStatement", Dialect::MySQL, mysql_showOpenTablesStatement_tokens_919, 5, "other"},
    {"showParseTreeStatement", Dialect::MySQL, mysql_showParseTreeStatement_tokens_920, 5, "other"},
    {"showPluginsStatement", Dialect::MySQL, mysql_showPluginsStatement_tokens_921, 2, "other"},
    {"showEngineLogsStatement", Dialect::MySQL, mysql_showEngineLogsStatement_tokens_922, 4, "other"},
    {"showEngineMutexStatement", Dialect::MySQL, mysql_showEngineMutexStatement_tokens_923, 4, "other"},
    {"showEngineStatusStatement", Dialect::MySQL, mysql_showEngineStatusStatement_tokens_924, 4, "other"},
    {"showColumnsStatement", Dialect::MySQL, mysql_showColumnsStatement_tokens_925, 7, "other"},
    {"showColumnsStatement", Dialect::MySQL, mysql_showColumnsStatement_tokens_926, 7, "other"},
    {"showBinaryLogsStatement", Dialect::MySQL, mysql_showBinaryLogsStatement_tokens_927, 4, "other"},
    {"showBinaryLogsStatement", Dialect::MySQL, mysql_showBinaryLogsStatement_tokens_928, 4, "other"},
    {"showBinaryLogStatusStatement", Dialect::MySQL, mysql_showBinaryLogStatusStatement_tokens_929, 4, "other"},
    {"showReplicasStatement", Dialect::MySQL, mysql_showReplicasStatement_tokens_930, 3, "other"},
    {"showReplicasStatement", Dialect::MySQL, mysql_showReplicasStatement_tokens_931, 2, "other"},
    {"showBinlogEventsStatement", Dialect::MySQL, mysql_showBinlogEventsStatement_tokens_932, 9, "other"},
    {"showRelaylogEventsStatement", Dialect::MySQL, mysql_showRelaylogEventsStatement_tokens_933, 9, "other"},
    {"showKeysStatement", Dialect::MySQL, mysql_showKeysStatement_tokens_934, 7, "other"},
    {"showKeysStatement", Dialect::MySQL, mysql_showKeysStatement_tokens_935, 7, "other"},
    {"showKeysStatement", Dialect::MySQL, mysql_showKeysStatement_tokens_936, 7, "other"},
    {"showEnginesStatement", Dialect::MySQL, mysql_showEnginesStatement_tokens_937, 4, "other"},
    {"showCountWarningsStatement", Dialect::MySQL, mysql_showCountWarningsStatement_tokens_938, 6, "other"},
    {"showCountErrorsStatement", Dialect::MySQL, mysql_showCountErrorsStatement_tokens_939, 6, "other"},
    {"showWarningsStatement", Dialect::MySQL, mysql_showWarningsStatement_tokens_940, 3, "other"},
    {"showErrorsStatement", Dialect::MySQL, mysql_showErrorsStatement_tokens_941, 3, "other"},
    {"showProfilesStatement", Dialect::MySQL, mysql_showProfilesStatement_tokens_942, 2, "other"},
    {"showProfileStatement", Dialect::MySQL, mysql_showProfileStatement_tokens_943, 7, "other"},
    {"showStatusStatement", Dialect::MySQL, mysql_showStatusStatement_tokens_944, 4, "other"},
    {"showProcessListStatement", Dialect::MySQL, mysql_showProcessListStatement_tokens_945, 3, "other"},
    {"showVariablesStatement", Dialect::MySQL, mysql_showVariablesStatement_tokens_946, 4, "other"},
    {"showCharacterSetStatement", Dialect::MySQL, mysql_showCharacterSetStatement_tokens_947, 3, "other"},
    {"showCollationStatement", Dialect::MySQL, mysql_showCollationStatement_tokens_948, 3, "other"},
    {"showPrivilegesStatement", Dialect::MySQL, mysql_showPrivilegesStatement_tokens_949, 2, "other"},
    {"showGrantsStatement", Dialect::MySQL, mysql_showGrantsStatement_tokens_950, 6, "other"},
    {"showMasterStatusStatement", Dialect::MySQL, mysql_showMasterStatusStatement_tokens_951, 3, "other"},
    {"showReplicaStatusStatement", Dialect::MySQL, mysql_showReplicaStatusStatement_tokens_952, 4, "other"},
    {"showCommandType", Dialect::MySQL, mysql_showCommandType_tokens_953, 1, "other"},
    {"showCommandType", Dialect::MySQL, mysql_showCommandType_tokens_954, 2, "other"},
    {"engineOrAll", Dialect::MySQL, mysql_engineOrAll_tokens_955, 1, "other"},
    {"engineOrAll", Dialect::MySQL, mysql_engineOrAll_tokens_956, 1, "other"},
    {"fromOrIn", Dialect::MySQL, mysql_fromOrIn_tokens_957, 1, "other"},
    {"fromOrIn", Dialect::MySQL, mysql_fromOrIn_tokens_958, 1, "other"},
    {"inDb", Dialect::MySQL, mysql_inDb_tokens_959, 2, "other"},
    {"profileDefinitions", Dialect::MySQL, mysql_profileDefinitions_tokens_960, 3, "other"},
    {"profileDefinition", Dialect::MySQL, mysql_profileDefinition_tokens_961, 2, "other"},
    {"profileDefinition", Dialect::MySQL, mysql_profileDefinition_tokens_962, 2, "other"},
    {"profileDefinition", Dialect::MySQL, mysql_profileDefinition_tokens_963, 2, "other"},
    {"profileDefinition", Dialect::MySQL, mysql_profileDefinition_tokens_964, 1, "other"},
    {"profileDefinition", Dialect::MySQL, mysql_profileDefinition_tokens_965, 1, "other"},
    {"profileDefinition", Dialect::MySQL, mysql_profileDefinition_tokens_966, 1, "other"},
    {"profileDefinition", Dialect::MySQL, mysql_profileDefinition_tokens_967, 1, "other"},
    {"profileDefinition", Dialect::MySQL, mysql_profileDefinition_tokens_968, 1, "other"},
    {"profileDefinition", Dialect::MySQL, mysql_profileDefinition_tokens_969, 1, "other"},
    {"otherAdministrativeStatement", Dialect::MySQL, mysql_otherAdministrativeStatement_tokens_970, 3, "other"},
    {"otherAdministrativeStatement", Dialect::MySQL, mysql_otherAdministrativeStatement_tokens_971, 6, "other"},
    {"otherAdministrativeStatement", Dialect::MySQL, mysql_otherAdministrativeStatement_tokens_972, 6, "other"},
    {"otherAdministrativeStatement", Dialect::MySQL, mysql_otherAdministrativeStatement_tokens_973, 4, "other"},
    {"otherAdministrativeStatement", Dialect::MySQL, mysql_otherAdministrativeStatement_tokens_974, 6, "other"},
    {"otherAdministrativeStatement", Dialect::MySQL, mysql_otherAdministrativeStatement_tokens_975, 4, "other"},
    {"otherAdministrativeStatement", Dialect::MySQL, mysql_otherAdministrativeStatement_tokens_976, 4, "other"},
    {"otherAdministrativeStatement", Dialect::MySQL, mysql_otherAdministrativeStatement_tokens_977, 6, "other"},
    {"otherAdministrativeStatement", Dialect::MySQL, mysql_otherAdministrativeStatement_tokens_978, 2, "other"},
    {"keyCacheListOrParts", Dialect::MySQL, mysql_keyCacheListOrParts_tokens_979, 1, "other"},
    {"keyCacheListOrParts", Dialect::MySQL, mysql_keyCacheListOrParts_tokens_980, 1, "other"},
    {"keyCacheList", Dialect::MySQL, mysql_keyCacheList_tokens_981, 3, "other"},
    {"assignToKeycache", Dialect::MySQL, mysql_assignToKeycache_tokens_982, 2, "other"},
    {"assignToKeycachePartition", Dialect::MySQL, mysql_assignToKeycachePartition_tokens_983, 6, "other"},
    {"cacheKeyList", Dialect::MySQL, mysql_cacheKeyList_tokens_984, 4, "other"},
    {"keyUsageElement", Dialect::MySQL, mysql_keyUsageElement_tokens_985, 1, "other"},
    {"keyUsageElement", Dialect::MySQL, mysql_keyUsageElement_tokens_986, 1, "other"},
    {"keyUsageList", Dialect::MySQL, mysql_keyUsageList_tokens_987, 3, "other"},
    {"flushOption", Dialect::MySQL, mysql_flushOption_tokens_988, 2, "other"},
    {"flushOption", Dialect::MySQL, mysql_flushOption_tokens_989, 2, "other"},
    {"flushOption", Dialect::MySQL, mysql_flushOption_tokens_990, 2, "other"},
    {"flushOption", Dialect::MySQL, mysql_flushOption_tokens_991, 2, "other"},
    {"flushOption", Dialect::MySQL, mysql_flushOption_tokens_992, 3, "other"},
    {"flushOption", Dialect::MySQL, mysql_flushOption_tokens_993, 4, "other"},
    {"flushOption", Dialect::MySQL, mysql_flushOption_tokens_994, 2, "other"},
    {"logType", Dialect::MySQL, mysql_logType_tokens_995, 1, "other"},
    {"logType", Dialect::MySQL, mysql_logType_tokens_996, 1, "other"},
    {"logType", Dialect::MySQL, mysql_logType_tokens_997, 1, "other"},
    {"logType", Dialect::MySQL, mysql_logType_tokens_998, 1, "other"},
    {"logType", Dialect::MySQL, mysql_logType_tokens_999, 1, "other"},
    {"flushTables", Dialect::MySQL, mysql_flushTables_tokens_1000, 4, "other"},
    {"flushTables", Dialect::MySQL, mysql_flushTables_tokens_1001, 3, "other"},
    {"flushTables", Dialect::MySQL, mysql_flushTables_tokens_1002, 4, "other"},
    {"flushTables", Dialect::MySQL, mysql_flushTables_tokens_1003, 3, "other"},
    {"flushTablesOptions", Dialect::MySQL, mysql_flushTablesOptions_tokens_1004, 2, "other"},
    {"flushTablesOptions", Dialect::MySQL, mysql_flushTablesOptions_tokens_1005, 3, "other"},
    {"preloadTail", Dialect::MySQL, mysql_preloadTail_tokens_1006, 5, "other"},
    {"preloadTail", Dialect::MySQL, mysql_preloadTail_tokens_1007, 1, "other"},
    {"preloadList", Dialect::MySQL, mysql_preloadList_tokens_1008, 3, "other"},
    {"preloadKeys", Dialect::MySQL, mysql_preloadKeys_tokens_1009, 4, "other"},
    {"adminPartition", Dialect::MySQL, mysql_adminPartition_tokens_1010, 4, "other"},
    {"resourceGroupManagement", Dialect::MySQL, mysql_resourceGroupManagement_tokens_1011, 1, "other"},
    {"resourceGroupManagement", Dialect::MySQL, mysql_resourceGroupManagement_tokens_1012, 1, "other"},
    {"resourceGroupManagement", Dialect::MySQL, mysql_resourceGroupManagement_tokens_1013, 1, "other"},
    {"resourceGroupManagement", Dialect::MySQL, mysql_resourceGroupManagement_tokens_1014, 1, "other"},
    {"resourceGroupVcpuList", Dialect::MySQL, mysql_resourceGroupVcpuList_tokens_1015, 5, "other"},
    {"vcpuNumOrRange", Dialect::MySQL, mysql_vcpuNumOrRange_tokens_1016, 3, "other"},
    {"resourceGroupPriority", Dialect::MySQL, mysql_resourceGroupPriority_tokens_1017, 3, "other"},
    {"resourceGroupEnableDisable", Dialect::MySQL, mysql_resourceGroupEnableDisable_tokens_1018, 1, "other"},
    {"resourceGroupEnableDisable", Dialect::MySQL, mysql_resourceGroupEnableDisable_tokens_1019, 1, "other"},
    {"alterResourceGroup", Dialect::MySQL, mysql_alterResourceGroup_tokens_1020, 8, "other"},
    {"setResourceGroup", Dialect::MySQL, mysql_setResourceGroup_tokens_1021, 6, "other"},
    {"threadIdList", Dialect::MySQL, mysql_threadIdList_tokens_1022, 3, "other"},
    {"utilityStatement", Dialect::MySQL, mysql_utilityStatement_tokens_1023, 1, "other"},
    {"utilityStatement", Dialect::MySQL, mysql_utilityStatement_tokens_1024, 1, "other"},
    {"utilityStatement", Dialect::MySQL, mysql_utilityStatement_tokens_1025, 1, "other"},
    {"utilityStatement", Dialect::MySQL, mysql_utilityStatement_tokens_1026, 1, "other"},
    {"utilityStatement", Dialect::MySQL, mysql_utilityStatement_tokens_1027, 3, "other"},
    {"describeStatement", Dialect::MySQL, mysql_describeStatement_tokens_1028, 3, "other"},
    {"describeStatement", Dialect::MySQL, mysql_describeStatement_tokens_1029, 3, "other"},
    {"describeStatement", Dialect::MySQL, mysql_describeStatement_tokens_1030, 3, "other"},
    {"describeStatement", Dialect::MySQL, mysql_describeStatement_tokens_1031, 3, "other"},
    {"describeStatement", Dialect::MySQL, mysql_describeStatement_tokens_1032, 3, "other"},
    {"describeStatement", Dialect::MySQL, mysql_describeStatement_tokens_1033, 3, "other"},
    {"explainStatement", Dialect::MySQL, mysql_explainStatement_tokens_1034, 8, "other"},
    {"explainStatement", Dialect::MySQL, mysql_explainStatement_tokens_1035, 8, "other"},
    {"explainStatement", Dialect::MySQL, mysql_explainStatement_tokens_1036, 8, "other"},
    {"explainOptions", Dialect::MySQL, mysql_explainOptions_tokens_1037, 6, "other"},
    {"explainOptions", Dialect::MySQL, mysql_explainOptions_tokens_1038, 3, "other"},
    {"explainOptions", Dialect::MySQL, mysql_explainOptions_tokens_1039, 3, "other"},
    {"explainOptions", Dialect::MySQL, mysql_explainOptions_tokens_1040, 6, "other"},
    {"explainableStatement", Dialect::MySQL, mysql_explainableStatement_tokens_1041, 1, "other"},
    {"explainableStatement", Dialect::MySQL, mysql_explainableStatement_tokens_1042, 1, "other"},
    {"explainableStatement", Dialect::MySQL, mysql_explainableStatement_tokens_1043, 1, "other"},
    {"explainableStatement", Dialect::MySQL, mysql_explainableStatement_tokens_1044, 1, "other"},
    {"explainableStatement", Dialect::MySQL, mysql_explainableStatement_tokens_1045, 1, "other"},
    {"explainableStatement", Dialect::MySQL, mysql_explainableStatement_tokens_1046, 3, "other"},
    {"explainInto", Dialect::MySQL, mysql_explainInto_tokens_1047, 3, "other"},
    {"helpCommand", Dialect::MySQL, mysql_helpCommand_tokens_1048, 2, "other"},
    {"useCommand", Dialect::MySQL, mysql_useCommand_tokens_1049, 2, "other"},
    {"restartServer", Dialect::MySQL, mysql_restartServer_tokens_1050, 1, "other"},
    {"boolPri", Dialect::MySQL, mysql_boolPri_tokens_1051, 2, "other"},
    {"boolPri", Dialect::MySQL, mysql_boolPri_tokens_1052, 5, "other"},
    {"boolPri", Dialect::MySQL, mysql_boolPri_tokens_1053, 4, "other"},
    {"boolPri", Dialect::MySQL, mysql_boolPri_tokens_1054, 5, "other"},
    {"boolPri", Dialect::MySQL, mysql_boolPri_tokens_1055, 5, "other"},
    {"compOp", Dialect::MySQL, mysql_compOp_tokens_1056, 1, "other"},
    {"compOp", Dialect::MySQL, mysql_compOp_tokens_1057, 1, "other"},
    {"compOp", Dialect::MySQL, mysql_compOp_tokens_1058, 1, "other"},
    {"compOp", Dialect::MySQL, mysql_compOp_tokens_1059, 1, "other"},
    {"compOp", Dialect::MySQL, mysql_compOp_tokens_1060, 1, "other"},
    {"compOp", Dialect::MySQL, mysql_compOp_tokens_1061, 1, "other"},
    {"compOp", Dialect::MySQL, mysql_compOp_tokens_1062, 1, "other"},
    {"predicate", Dialect::MySQL, mysql_predicate_tokens_1063, 3, "other"},
    {"predicate", Dialect::MySQL, mysql_predicate_tokens_1064, 6, "other"},
    {"predicate", Dialect::MySQL, mysql_predicate_tokens_1065, 4, "other"},
    {"predicateOperations", Dialect::MySQL, mysql_predicateOperations_tokens_1066, 3, "other"},
    {"predicateOperations", Dialect::MySQL, mysql_predicateOperations_tokens_1067, 5, "other"},
    {"predicateOperations", Dialect::MySQL, mysql_predicateOperations_tokens_1068, 5, "other"},
    {"predicateOperations", Dialect::MySQL, mysql_predicateOperations_tokens_1069, 5, "other"},
    {"predicateOperations", Dialect::MySQL, mysql_predicateOperations_tokens_1070, 3, "other"},
    {"arrayCast", Dialect::MySQL, mysql_arrayCast_tokens_1071, 3, "other"},
    {"jsonOperator", Dialect::MySQL, mysql_jsonOperator_tokens_1072, 2, "other"},
    {"jsonOperator", Dialect::MySQL, mysql_jsonOperator_tokens_1073, 2, "other"},
    {"groupingOperation", Dialect::MySQL, mysql_groupingOperation_tokens_1074, 4, "other"},
    {"windowFunctionCall", Dialect::MySQL, mysql_windowFunctionCall_tokens_1075, 3, "other"},
    {"windowFunctionCall", Dialect::MySQL, mysql_windowFunctionCall_tokens_1076, 3, "other"},
    {"windowFunctionCall", Dialect::MySQL, mysql_windowFunctionCall_tokens_1077, 3, "other"},
    {"windowFunctionCall", Dialect::MySQL, mysql_windowFunctionCall_tokens_1078, 3, "other"},
    {"windowFunctionCall", Dialect::MySQL, mysql_windowFunctionCall_tokens_1079, 3, "other"},
    {"windowFunctionCall", Dialect::MySQL, mysql_windowFunctionCall_tokens_1080, 5, "other"},
    {"windowFunctionCall", Dialect::MySQL, mysql_windowFunctionCall_tokens_1081, 5, "other"},
    {"windowFunctionCall", Dialect::MySQL, mysql_windowFunctionCall_tokens_1082, 7, "other"},
    {"windowFunctionCall", Dialect::MySQL, mysql_windowFunctionCall_tokens_1083, 7, "other"},
    {"windowFunctionCall", Dialect::MySQL, mysql_windowFunctionCall_tokens_1084, 4, "other"},
    {"windowFunctionCall", Dialect::MySQL, mysql_windowFunctionCall_tokens_1085, 4, "other"},
    {"windowFunctionCall", Dialect::MySQL, mysql_windowFunctionCall_tokens_1086, 10, "other"},
    {"windowFunctionCall", Dialect::MySQL, mysql_windowFunctionCall_tokens_1087, 10, "other"},
    {"samplingMethod", Dialect::MySQL, mysql_samplingMethod_tokens_1088, 1, "other"},
    {"samplingMethod", Dialect::MySQL, mysql_samplingMethod_tokens_1089, 1, "other"},
    {"samplingPercentage", Dialect::MySQL, mysql_samplingPercentage_tokens_1090, 1, "other"},
    {"samplingPercentage", Dialect::MySQL, mysql_samplingPercentage_tokens_1091, 2, "other"},
    {"samplingPercentage", Dialect::MySQL, mysql_samplingPercentage_tokens_1092, 1, "other"},
    {"tablesampleClause", Dialect::MySQL, mysql_tablesampleClause_tokens_1093, 7, "other"},
    {"windowingClause", Dialect::MySQL, mysql_windowingClause_tokens_1094, 2, "other"},
    {"windowingClause", Dialect::MySQL, mysql_windowingClause_tokens_1095, 2, "other"},
    {"leadLagInfo", Dialect::MySQL, mysql_leadLagInfo_tokens_1096, 4, "other"},
    {"leadLagInfo", Dialect::MySQL, mysql_leadLagInfo_tokens_1097, 4, "other"},
    {"leadLagInfo", Dialect::MySQL, mysql_leadLagInfo_tokens_1098, 6, "other"},
    {"stableInteger", Dialect::MySQL, mysql_stableInteger_tokens_1099, 1, "other"},
    {"stableInteger", Dialect::MySQL, mysql_stableInteger_tokens_1100, 1, "other"},
    {"paramOrVar", Dialect::MySQL, mysql_paramOrVar_tokens_1101, 1, "other"},
    {"paramOrVar", Dialect::MySQL, mysql_paramOrVar_tokens_1102, 1, "other"},
    {"paramOrVar", Dialect::MySQL, mysql_paramOrVar_tokens_1103, 2, "other"},
    {"nullTreatment", Dialect::MySQL, mysql_nullTreatment_tokens_1104, 2, "other"},
    {"nullTreatment", Dialect::MySQL, mysql_nullTreatment_tokens_1105, 2, "other"},
    {"jsonFunction", Dialect::MySQL, mysql_jsonFunction_tokens_1106, 5, "other"},
    {"jsonFunction", Dialect::MySQL, mysql_jsonFunction_tokens_1107, 7, "other"},
    {"identListArg", Dialect::MySQL, mysql_identListArg_tokens_1108, 1, "other"},
    {"identListArg", Dialect::MySQL, mysql_identListArg_tokens_1109, 3, "other"},
    {"identList", Dialect::MySQL, mysql_identList_tokens_1110, 3, "other"},
    {"fulltextOptions", Dialect::MySQL, mysql_fulltextOptions_tokens_1111, 3, "other"},
    {"fulltextOptions", Dialect::MySQL, mysql_fulltextOptions_tokens_1112, 7, "other"},
    {"fulltextOptions", Dialect::MySQL, mysql_fulltextOptions_tokens_1113, 3, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1114, 6, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1115, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1116, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1117, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1118, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1119, 10, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1120, 6, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1121, 8, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1122, 6, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1123, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1124, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1125, 6, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1126, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1127, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1128, 6, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1129, 1, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1130, 1, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1131, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1132, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1133, 6, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1134, 8, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1135, 6, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1136, 8, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1137, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1138, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1139, 8, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1140, 8, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1141, 6, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1142, 6, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1143, 8, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1144, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1145, 6, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1146, 1, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1147, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1148, 8, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1149, 8, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1150, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1151, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1152, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1153, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1154, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1155, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1156, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1157, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1158, 8, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1159, 8, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1160, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1161, 6, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1162, 4, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1163, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1164, 6, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1165, 8, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1166, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1167, 2, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1168, 6, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1169, 6, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1170, 7, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1171, 7, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1172, 10, "other"},
    {"runtimeFunctionCall", Dialect::MySQL, mysql_runtimeFunctionCall_tokens_1173, 1, "other"},
    {"returningType", Dialect::MySQL, mysql_returningType_tokens_1174, 2, "other"},
    {"geometryFunction", Dialect::MySQL, mysql_geometryFunction_tokens_1175, 4, "other"},
    {"geometryFunction", Dialect::MySQL, mysql_geometryFunction_tokens_1176, 2, "other"},
    {"geometryFunction", Dialect::MySQL, mysql_geometryFunction_tokens_1177, 2, "other"},
    {"geometryFunction", Dialect::MySQL, mysql_geometryFunction_tokens_1178, 2, "other"},
    {"geometryFunction", Dialect::MySQL, mysql_geometryFunction_tokens_1179, 2, "other"},
    {"geometryFunction", Dialect::MySQL, mysql_geometryFunction_tokens_1180, 6, "other"},
    {"geometryFunction", Dialect::MySQL, mysql_geometryFunction_tokens_1181, 2, "other"},
    {"timeFunctionParameters", Dialect::MySQL, mysql_timeFunctionParameters_tokens_1182, 3, "other"},
    {"fractionalPrecision", Dialect::MySQL, mysql_fractionalPrecision_tokens_1183, 1, "other"},
    {"weightStringLevels", Dialect::MySQL, mysql_weightStringLevels_tokens_1184, 4, "other"},
    {"weightStringLevels", Dialect::MySQL, mysql_weightStringLevels_tokens_1185, 4, "other"},
    {"weightStringLevelListItem", Dialect::MySQL, mysql_weightStringLevelListItem_tokens_1186, 3, "other"},
    {"weightStringLevelListItem", Dialect::MySQL, mysql_weightStringLevelListItem_tokens_1187, 3, "other"},
    {"weightStringLevelListItem", Dialect::MySQL, mysql_weightStringLevelListItem_tokens_1188, 2, "other"},
    {"dateTimeTtype", Dialect::MySQL, mysql_dateTimeTtype_tokens_1189, 1, "other"},
    {"dateTimeTtype", Dialect::MySQL, mysql_dateTimeTtype_tokens_1190, 1, "other"},
    {"dateTimeTtype", Dialect::MySQL, mysql_dateTimeTtype_tokens_1191, 1, "other"},
    {"dateTimeTtype", Dialect::MySQL, mysql_dateTimeTtype_tokens_1192, 1, "other"},
    {"trimFunction", Dialect::MySQL, mysql_trimFunction_tokens_1193, 6, "other"},
    {"trimFunction", Dialect::MySQL, mysql_trimFunction_tokens_1194, 7, "other"},
    {"trimFunction", Dialect::MySQL, mysql_trimFunction_tokens_1195, 7, "other"},
    {"trimFunction", Dialect::MySQL, mysql_trimFunction_tokens_1196, 7, "other"},
    {"substringFunction", Dialect::MySQL, mysql_substringFunction_tokens_1197, 8, "other"},
    {"substringFunction", Dialect::MySQL, mysql_substringFunction_tokens_1198, 8, "other"},
    {"functionCall", Dialect::MySQL, mysql_functionCall_tokens_1199, 4, "other"},
    {"functionCall", Dialect::MySQL, mysql_functionCall_tokens_1200, 4, "other"},
    {"userVariable", Dialect::MySQL, mysql_userVariable_tokens_1201, 2, "other"},
    {"userVariable", Dialect::MySQL, mysql_userVariable_tokens_1202, 1, "other"},
    {"rvalueSystemOrUserVariable", Dialect::MySQL, mysql_rvalueSystemOrUserVariable_tokens_1203, 1, "other"},
    {"rvalueSystemOrUserVariable", Dialect::MySQL, mysql_rvalueSystemOrUserVariable_tokens_1204, 3, "other"},
    {"lvalueVariable", Dialect::MySQL, mysql_lvalueVariable_tokens_1205, 2, "other"},
    {"lvalueVariable", Dialect::MySQL, mysql_lvalueVariable_tokens_1206, 4, "other"},
    {"lvalueVariable", Dialect::MySQL, mysql_lvalueVariable_tokens_1207, 2, "other"},
    {"rvalueSystemVariable", Dialect::MySQL, mysql_rvalueSystemVariable_tokens_1208, 2, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1209, 2, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1210, 3, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1211, 2, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1212, 2, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1213, 2, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1214, 1, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1215, 3, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1216, 2, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1217, 2, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1218, 2, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1219, 1, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1220, 3, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1221, 4, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1222, 3, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1223, 3, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1224, 3, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1225, 3, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1226, 3, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1227, 3, "other"},
    {"castType", Dialect::MySQL, mysql_castType_tokens_1228, 3, "other"},
    {"charset", Dialect::MySQL, mysql_charset_tokens_1229, 2, "other"},
    {"charset", Dialect::MySQL, mysql_charset_tokens_1230, 1, "other"},
    {"notRule", Dialect::MySQL, mysql_notRule_tokens_1231, 1, "other"},
    {"notRule", Dialect::MySQL, mysql_notRule_tokens_1232, 1, "other"},
    {"not2Rule", Dialect::MySQL, mysql_not2Rule_tokens_1233, 1, "other"},
    {"not2Rule", Dialect::MySQL, mysql_not2Rule_tokens_1234, 1, "other"},
    {"interval", Dialect::MySQL, mysql_interval_tokens_1235, 1, "other"},
    {"interval", Dialect::MySQL, mysql_interval_tokens_1236, 1, "other"},
    {"interval", Dialect::MySQL, mysql_interval_tokens_1237, 1, "other"},
    {"interval", Dialect::MySQL, mysql_interval_tokens_1238, 1, "other"},
    {"interval", Dialect::MySQL, mysql_interval_tokens_1239, 1, "other"},
    {"interval", Dialect::MySQL, mysql_interval_tokens_1240, 1, "other"},
    {"interval", Dialect::MySQL, mysql_interval_tokens_1241, 1, "other"},
    {"interval", Dialect::MySQL, mysql_interval_tokens_1242, 1, "other"},
    {"interval", Dialect::MySQL, mysql_interval_tokens_1243, 1, "other"},
    {"interval", Dialect::MySQL, mysql_interval_tokens_1244, 1, "other"},
    {"interval", Dialect::MySQL, mysql_interval_tokens_1245, 1, "other"},
    {"interval", Dialect::MySQL, mysql_interval_tokens_1246, 1, "other"},
    {"intervalTimeStamp", Dialect::MySQL, mysql_intervalTimeStamp_tokens_1247, 1, "other"},
    {"intervalTimeStamp", Dialect::MySQL, mysql_intervalTimeStamp_tokens_1248, 1, "other"},
    {"intervalTimeStamp", Dialect::MySQL, mysql_intervalTimeStamp_tokens_1249, 1, "other"},
    {"intervalTimeStamp", Dialect::MySQL, mysql_intervalTimeStamp_tokens_1250, 1, "other"},
    {"intervalTimeStamp", Dialect::MySQL, mysql_intervalTimeStamp_tokens_1251, 1, "other"},
    {"intervalTimeStamp", Dialect::MySQL, mysql_intervalTimeStamp_tokens_1252, 1, "other"},
    {"intervalTimeStamp", Dialect::MySQL, mysql_intervalTimeStamp_tokens_1253, 1, "other"},
    {"intervalTimeStamp", Dialect::MySQL, mysql_intervalTimeStamp_tokens_1254, 1, "other"},
    {"intervalTimeStamp", Dialect::MySQL, mysql_intervalTimeStamp_tokens_1255, 1, "other"},
    {"orderList", Dialect::MySQL, mysql_orderList_tokens_1256, 3, "other"},
    {"groupList", Dialect::MySQL, mysql_groupList_tokens_1257, 3, "other"},
    {"channel", Dialect::MySQL, mysql_channel_tokens_1258, 3, "other"},
    {"compoundStatement", Dialect::MySQL, mysql_compoundStatement_tokens_1259, 1, "other"},
    {"compoundStatement", Dialect::MySQL, mysql_compoundStatement_tokens_1260, 1, "other"},
    {"compoundStatement", Dialect::MySQL, mysql_compoundStatement_tokens_1261, 1, "other"},
    {"compoundStatement", Dialect::MySQL, mysql_compoundStatement_tokens_1262, 1, "other"},
    {"compoundStatement", Dialect::MySQL, mysql_compoundStatement_tokens_1263, 1, "other"},
    {"compoundStatement", Dialect::MySQL, mysql_compoundStatement_tokens_1264, 1, "other"},
    {"compoundStatement", Dialect::MySQL, mysql_compoundStatement_tokens_1265, 1, "other"},
    {"compoundStatement", Dialect::MySQL, mysql_compoundStatement_tokens_1266, 1, "other"},
    {"compoundStatement", Dialect::MySQL, mysql_compoundStatement_tokens_1267, 1, "other"},
    {"compoundStatement", Dialect::MySQL, mysql_compoundStatement_tokens_1268, 1, "other"},
    {"compoundStatement", Dialect::MySQL, mysql_compoundStatement_tokens_1269, 1, "other"},
    {"compoundStatement", Dialect::MySQL, mysql_compoundStatement_tokens_1270, 1, "other"},
    {"compoundStatement", Dialect::MySQL, mysql_compoundStatement_tokens_1271, 1, "other"},
    {"returnStatement", Dialect::MySQL, mysql_returnStatement_tokens_1272, 2, "other"},
    {"ifStatement", Dialect::MySQL, mysql_ifStatement_tokens_1273, 4, "other"},
    {"ifBody", Dialect::MySQL, mysql_ifBody_tokens_1274, 4, "other"},
    {"ifBody", Dialect::MySQL, mysql_ifBody_tokens_1275, 4, "other"},
    {"thenStatement", Dialect::MySQL, mysql_thenStatement_tokens_1276, 2, "other"},
    {"compoundStatementList", Dialect::MySQL, mysql_compoundStatementList_tokens_1277, 2, "other"},
    {"caseStatement", Dialect::MySQL, mysql_caseStatement_tokens_1278, 7, "other"},
    {"elseStatement", Dialect::MySQL, mysql_elseStatement_tokens_1279, 2, "other"},
    {"labeledBlock", Dialect::MySQL, mysql_labeledBlock_tokens_1280, 3, "other"},
    {"unlabeledBlock", Dialect::MySQL, mysql_unlabeledBlock_tokens_1281, 1, "other"},
    {"label", Dialect::MySQL, mysql_label_tokens_1282, 2, "other"},
    {"beginEndBlock", Dialect::MySQL, mysql_beginEndBlock_tokens_1283, 4, "other"},
    {"labeledControl", Dialect::MySQL, mysql_labeledControl_tokens_1284, 3, "other"},
    {"unlabeledControl", Dialect::MySQL, mysql_unlabeledControl_tokens_1285, 1, "other"},
    {"unlabeledControl", Dialect::MySQL, mysql_unlabeledControl_tokens_1286, 1, "other"},
    {"unlabeledControl", Dialect::MySQL, mysql_unlabeledControl_tokens_1287, 1, "other"},
    {"loopBlock", Dialect::MySQL, mysql_loopBlock_tokens_1288, 4, "other"},
    {"whileDoBlock", Dialect::MySQL, mysql_whileDoBlock_tokens_1289, 6, "other"},
    {"repeatUntilBlock", Dialect::MySQL, mysql_repeatUntilBlock_tokens_1290, 6, "other"},
    {"spDeclarations", Dialect::MySQL, mysql_spDeclarations_tokens_1291, 2, "other"},
    {"spDeclaration", Dialect::MySQL, mysql_spDeclaration_tokens_1292, 1, "other"},
    {"spDeclaration", Dialect::MySQL, mysql_spDeclaration_tokens_1293, 1, "other"},
    {"spDeclaration", Dialect::MySQL, mysql_spDeclaration_tokens_1294, 1, "other"},
    {"spDeclaration", Dialect::MySQL, mysql_spDeclaration_tokens_1295, 1, "other"},
    {"variableDeclaration", Dialect::MySQL, mysql_variableDeclaration_tokens_1296, 6, "other"},
    {"conditionDeclaration", Dialect::MySQL, mysql_conditionDeclaration_tokens_1297, 5, "other"},
    {"spCondition", Dialect::MySQL, mysql_spCondition_tokens_1298, 1, "other"},
    {"spCondition", Dialect::MySQL, mysql_spCondition_tokens_1299, 1, "other"},
    {"sqlstate", Dialect::MySQL, mysql_sqlstate_tokens_1300, 3, "other"},
    {"handlerDeclaration", Dialect::MySQL, mysql_handlerDeclaration_tokens_1301, 8, "other"},
    {"handlerDeclaration", Dialect::MySQL, mysql_handlerDeclaration_tokens_1302, 8, "other"},
    {"handlerDeclaration", Dialect::MySQL, mysql_handlerDeclaration_tokens_1303, 8, "other"},
    {"handlerCondition", Dialect::MySQL, mysql_handlerCondition_tokens_1304, 1, "other"},
    {"handlerCondition", Dialect::MySQL, mysql_handlerCondition_tokens_1305, 1, "other"},
    {"handlerCondition", Dialect::MySQL, mysql_handlerCondition_tokens_1306, 1, "other"},
    {"handlerCondition", Dialect::MySQL, mysql_handlerCondition_tokens_1307, 2, "other"},
    {"handlerCondition", Dialect::MySQL, mysql_handlerCondition_tokens_1308, 1, "other"},
    {"cursorDeclaration", Dialect::MySQL, mysql_cursorDeclaration_tokens_1309, 5, "other"},
    {"iterateStatement", Dialect::MySQL, mysql_iterateStatement_tokens_1310, 2, "other"},
    {"leaveStatement", Dialect::MySQL, mysql_leaveStatement_tokens_1311, 2, "other"},
    {"getDiagnosticsStatement", Dialect::MySQL, mysql_getDiagnosticsStatement_tokens_1312, 6, "other"},
    {"getDiagnosticsStatement", Dialect::MySQL, mysql_getDiagnosticsStatement_tokens_1313, 8, "other"},
    {"getDiagnosticsStatement", Dialect::MySQL, mysql_getDiagnosticsStatement_tokens_1314, 6, "other"},
    {"getDiagnosticsStatement", Dialect::MySQL, mysql_getDiagnosticsStatement_tokens_1315, 8, "other"},
    {"statementInformationItem", Dialect::MySQL, mysql_statementInformationItem_tokens_1316, 3, "other"},
    {"statementInformationItem", Dialect::MySQL, mysql_statementInformationItem_tokens_1317, 3, "other"},
    {"statementInformationItem", Dialect::MySQL, mysql_statementInformationItem_tokens_1318, 3, "other"},
    {"statementInformationItem", Dialect::MySQL, mysql_statementInformationItem_tokens_1319, 3, "other"},
    {"conditionInformationItem", Dialect::MySQL, mysql_conditionInformationItem_tokens_1320, 3, "other"},
    {"conditionInformationItem", Dialect::MySQL, mysql_conditionInformationItem_tokens_1321, 3, "other"},
    {"conditionInformationItem", Dialect::MySQL, mysql_conditionInformationItem_tokens_1322, 3, "other"},
    {"conditionInformationItem", Dialect::MySQL, mysql_conditionInformationItem_tokens_1323, 3, "other"},
    {"signalInformationItemName", Dialect::MySQL, mysql_signalInformationItemName_tokens_1324, 1, "other"},
    {"signalInformationItemName", Dialect::MySQL, mysql_signalInformationItemName_tokens_1325, 1, "other"},
    {"signalInformationItemName", Dialect::MySQL, mysql_signalInformationItemName_tokens_1326, 1, "other"},
    {"signalInformationItemName", Dialect::MySQL, mysql_signalInformationItemName_tokens_1327, 1, "other"},
    {"signalInformationItemName", Dialect::MySQL, mysql_signalInformationItemName_tokens_1328, 1, "other"},
    {"signalInformationItemName", Dialect::MySQL, mysql_signalInformationItemName_tokens_1329, 1, "other"},
    {"signalInformationItemName", Dialect::MySQL, mysql_signalInformationItemName_tokens_1330, 1, "other"},
    {"signalInformationItemName", Dialect::MySQL, mysql_signalInformationItemName_tokens_1331, 1, "other"},
    {"signalInformationItemName", Dialect::MySQL, mysql_signalInformationItemName_tokens_1332, 1, "other"},
    {"signalInformationItemName", Dialect::MySQL, mysql_signalInformationItemName_tokens_1333, 1, "other"},
    {"signalInformationItemName", Dialect::MySQL, mysql_signalInformationItemName_tokens_1334, 1, "other"},
    {"signalInformationItemName", Dialect::MySQL, mysql_signalInformationItemName_tokens_1335, 1, "other"},
    {"signalStatement", Dialect::MySQL, mysql_signalStatement_tokens_1336, 6, "other"},
    {"signalStatement", Dialect::MySQL, mysql_signalStatement_tokens_1337, 6, "other"},
    {"resignalStatement", Dialect::MySQL, mysql_resignalStatement_tokens_1338, 6, "other"},
    {"resignalStatement", Dialect::MySQL, mysql_resignalStatement_tokens_1339, 6, "other"},
    {"signalInformationItem", Dialect::MySQL, mysql_signalInformationItem_tokens_1340, 3, "other"},
    {"cursorOpen", Dialect::MySQL, mysql_cursorOpen_tokens_1341, 2, "other"},
    {"cursorClose", Dialect::MySQL, mysql_cursorClose_tokens_1342, 2, "other"},
    {"cursorFetch", Dialect::MySQL, mysql_cursorFetch_tokens_1343, 6, "other"},
    {"schedule", Dialect::MySQL, mysql_schedule_tokens_1344, 2, "other"},
    {"schedule", Dialect::MySQL, mysql_schedule_tokens_1345, 7, "other"},
    {"columnDefinition", Dialect::MySQL, mysql_columnDefinition_tokens_1346, 3, "other"},
    {"checkOrReferences", Dialect::MySQL, mysql_checkOrReferences_tokens_1347, 3, "other"},
    {"checkOrReferences", Dialect::MySQL, mysql_checkOrReferences_tokens_1348, 1, "other"},
    {"checkConstraint", Dialect::MySQL, mysql_checkConstraint_tokens_1349, 2, "other"},
    {"constraintEnforcement", Dialect::MySQL, mysql_constraintEnforcement_tokens_1350, 4, "other"},
    {"tableConstraintDef", Dialect::MySQL, mysql_tableConstraintDef_tokens_1351, 5, "other"},
    {"tableConstraintDef", Dialect::MySQL, mysql_tableConstraintDef_tokens_1352, 5, "other"},
    {"tableConstraintDef", Dialect::MySQL, mysql_tableConstraintDef_tokens_1353, 6, "other"},
    {"tableConstraintDef", Dialect::MySQL, mysql_tableConstraintDef_tokens_1354, 6, "other"},
    {"tableConstraintDef", Dialect::MySQL, mysql_tableConstraintDef_tokens_1355, 7, "other"},
    {"tableConstraintDef", Dialect::MySQL, mysql_tableConstraintDef_tokens_1356, 7, "other"},
    {"tableConstraintDef", Dialect::MySQL, mysql_tableConstraintDef_tokens_1357, 7, "other"},
    {"tableConstraintDef", Dialect::MySQL, mysql_tableConstraintDef_tokens_1358, 3, "other"},
    {"constraintName", Dialect::MySQL, mysql_constraintName_tokens_1359, 2, "other"},
    {"fieldDefinition", Dialect::MySQL, mysql_fieldDefinition_tokens_1360, 2, "other"},
    {"fieldDefinition", Dialect::MySQL, mysql_fieldDefinition_tokens_1361, 8, "other"},
    {"fieldDefinition", Dialect::MySQL, mysql_fieldDefinition_tokens_1362, 8, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1363, 2, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1364, 4, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1365, 3, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1366, 5, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1367, 5, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1368, 2, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1369, 4, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1370, 3, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1371, 3, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1372, 3, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1373, 1, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1374, 3, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1375, 3, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1376, 3, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1377, 4, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1378, 3, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1379, 6, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1380, 6, "other"},
    {"columnAttribute", Dialect::MySQL, mysql_columnAttribute_tokens_1381, 3, "other"},
    {"columnFormat", Dialect::MySQL, mysql_columnFormat_tokens_1382, 1, "other"},
    {"columnFormat", Dialect::MySQL, mysql_columnFormat_tokens_1383, 1, "other"},
    {"columnFormat", Dialect::MySQL, mysql_columnFormat_tokens_1384, 1, "other"},
    {"storageMedia", Dialect::MySQL, mysql_storageMedia_tokens_1385, 1, "other"},
    {"storageMedia", Dialect::MySQL, mysql_storageMedia_tokens_1386, 1, "other"},
    {"storageMedia", Dialect::MySQL, mysql_storageMedia_tokens_1387, 1, "other"},
    {"now", Dialect::MySQL, mysql_now_tokens_1388, 2, "other"},
    {"nowOrSignedLiteral", Dialect::MySQL, mysql_nowOrSignedLiteral_tokens_1389, 1, "other"},
    {"nowOrSignedLiteral", Dialect::MySQL, mysql_nowOrSignedLiteral_tokens_1390, 1, "other"},
    {"gcolAttribute", Dialect::MySQL, mysql_gcolAttribute_tokens_1391, 2, "other"},
    {"gcolAttribute", Dialect::MySQL, mysql_gcolAttribute_tokens_1392, 2, "other"},
    {"gcolAttribute", Dialect::MySQL, mysql_gcolAttribute_tokens_1393, 2, "other"},
    {"gcolAttribute", Dialect::MySQL, mysql_gcolAttribute_tokens_1394, 2, "other"},
    {"references", Dialect::MySQL, mysql_references_tokens_1395, 13, "other"},
    {"references", Dialect::MySQL, mysql_references_tokens_1396, 13, "other"},
    {"references", Dialect::MySQL, mysql_references_tokens_1397, 13, "other"},
    {"references", Dialect::MySQL, mysql_references_tokens_1398, 13, "other"},
    {"references", Dialect::MySQL, mysql_references_tokens_1399, 13, "other"},
    {"references", Dialect::MySQL, mysql_references_tokens_1400, 13, "other"},
    {"keyList", Dialect::MySQL, mysql_keyList_tokens_1401, 5, "other"},
    {"keyPart", Dialect::MySQL, mysql_keyPart_tokens_1402, 3, "other"},
    {"indexType", Dialect::MySQL, mysql_indexType_tokens_1403, 2, "other"},
    {"indexType", Dialect::MySQL, mysql_indexType_tokens_1404, 2, "other"},
    {"indexType", Dialect::MySQL, mysql_indexType_tokens_1405, 2, "other"},
    {"indexOption", Dialect::MySQL, mysql_indexOption_tokens_1406, 1, "other"},
    {"indexOption", Dialect::MySQL, mysql_indexOption_tokens_1407, 1, "other"},
    {"commonIndexOption", Dialect::MySQL, mysql_commonIndexOption_tokens_1408, 3, "other"},
    {"commonIndexOption", Dialect::MySQL, mysql_commonIndexOption_tokens_1409, 2, "other"},
    {"commonIndexOption", Dialect::MySQL, mysql_commonIndexOption_tokens_1410, 1, "other"},
    {"commonIndexOption", Dialect::MySQL, mysql_commonIndexOption_tokens_1411, 5, "other"},
    {"commonIndexOption", Dialect::MySQL, mysql_commonIndexOption_tokens_1412, 5, "other"},
    {"visibility", Dialect::MySQL, mysql_visibility_tokens_1413, 1, "other"},
    {"visibility", Dialect::MySQL, mysql_visibility_tokens_1414, 1, "other"},
    {"indexTypeClause", Dialect::MySQL, mysql_indexTypeClause_tokens_1415, 2, "other"},
    {"indexTypeClause", Dialect::MySQL, mysql_indexTypeClause_tokens_1416, 2, "other"},
    {"fulltextIndexOption", Dialect::MySQL, mysql_fulltextIndexOption_tokens_1417, 1, "other"},
    {"fulltextIndexOption", Dialect::MySQL, mysql_fulltextIndexOption_tokens_1418, 3, "other"},
    {"spatialIndexOption", Dialect::MySQL, mysql_spatialIndexOption_tokens_1419, 1, "other"},
    {"dataTypeDefinition", Dialect::MySQL, mysql_dataTypeDefinition_tokens_1420, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1421, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1422, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1423, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1424, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1425, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1426, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1427, 5, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1428, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1429, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1430, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1431, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1432, 3, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1433, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1434, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1435, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1436, 3, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1437, 3, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1438, 5, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1439, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1440, 5, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1441, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1442, 5, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1443, 6, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1444, 5, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1445, 3, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1446, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1447, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1448, 3, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1449, 3, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1450, 3, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1451, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1452, 3, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1453, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1454, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1455, 3, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1456, 5, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1457, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1458, 3, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1459, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1460, 3, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1461, 3, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1462, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1463, 4, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1464, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1465, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1466, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1467, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1468, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1469, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1470, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1471, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1472, 2, "other"},
    {"dataType", Dialect::MySQL, mysql_dataType_tokens_1473, 2, "other"},
    {"nchar", Dialect::MySQL, mysql_nchar_tokens_1474, 2, "other"},
    {"nchar", Dialect::MySQL, mysql_nchar_tokens_1475, 3, "other"},
    {"realType", Dialect::MySQL, mysql_realType_tokens_1476, 2, "other"},
    {"realType", Dialect::MySQL, mysql_realType_tokens_1477, 3, "other"},
    {"fieldLength", Dialect::MySQL, mysql_fieldLength_tokens_1478, 3, "other"},
    {"fieldLength", Dialect::MySQL, mysql_fieldLength_tokens_1479, 3, "other"},
    {"fieldOptions", Dialect::MySQL, mysql_fieldOptions_tokens_1480, 1, "other"},
    {"fieldOptions", Dialect::MySQL, mysql_fieldOptions_tokens_1481, 1, "other"},
    {"fieldOptions", Dialect::MySQL, mysql_fieldOptions_tokens_1482, 1, "other"},
    {"charsetWithOptBinary", Dialect::MySQL, mysql_charsetWithOptBinary_tokens_1483, 1, "other"},
    {"charsetWithOptBinary", Dialect::MySQL, mysql_charsetWithOptBinary_tokens_1484, 1, "other"},
    {"charsetWithOptBinary", Dialect::MySQL, mysql_charsetWithOptBinary_tokens_1485, 1, "other"},
    {"charsetWithOptBinary", Dialect::MySQL, mysql_charsetWithOptBinary_tokens_1486, 3, "other"},
    {"charsetWithOptBinary", Dialect::MySQL, mysql_charsetWithOptBinary_tokens_1487, 3, "other"},
    {"ascii", Dialect::MySQL, mysql_ascii_tokens_1488, 2, "other"},
    {"ascii", Dialect::MySQL, mysql_ascii_tokens_1489, 2, "other"},
    {"unicode", Dialect::MySQL, mysql_unicode_tokens_1490, 2, "other"},
    {"unicode", Dialect::MySQL, mysql_unicode_tokens_1491, 2, "other"},
    {"wsNumCodepoints", Dialect::MySQL, mysql_wsNumCodepoints_tokens_1492, 3, "other"},
    {"typeDatetimePrecision", Dialect::MySQL, mysql_typeDatetimePrecision_tokens_1493, 3, "other"},
    {"functionDatetimePrecision", Dialect::MySQL, mysql_functionDatetimePrecision_tokens_1494, 1, "other"},
    {"functionDatetimePrecision", Dialect::MySQL, mysql_functionDatetimePrecision_tokens_1495, 3, "other"},
    {"charsetName", Dialect::MySQL, mysql_charsetName_tokens_1496, 1, "other"},
    {"charsetName", Dialect::MySQL, mysql_charsetName_tokens_1497, 1, "other"},
    {"charsetName", Dialect::MySQL, mysql_charsetName_tokens_1498, 3, "other"},
    {"collationName", Dialect::MySQL, mysql_collationName_tokens_1499, 1, "other"},
    {"collationName", Dialect::MySQL, mysql_collationName_tokens_1500, 3, "other"},
    {"collationName", Dialect::MySQL, mysql_collationName_tokens_1501, 3, "other"},
    {"ternaryOption", Dialect::MySQL, mysql_ternaryOption_tokens_1502, 1, "other"},
    {"ternaryOption", Dialect::MySQL, mysql_ternaryOption_tokens_1503, 1, "other"},
    {"defaultCollation", Dialect::MySQL, mysql_defaultCollation_tokens_1504, 4, "other"},
    {"defaultEncryption", Dialect::MySQL, mysql_defaultEncryption_tokens_1505, 4, "other"},
    {"defaultCharset", Dialect::MySQL, mysql_defaultCharset_tokens_1506, 4, "other"},
    {"partitionClause", Dialect::MySQL, mysql_partitionClause_tokens_1507, 7, "other"},
    {"partitionTypeDef", Dialect::MySQL, mysql_partitionTypeDef_tokens_1508, 7, "other"},
    {"partitionTypeDef", Dialect::MySQL, mysql_partitionTypeDef_tokens_1509, 6, "other"},
    {"partitionTypeDef", Dialect::MySQL, mysql_partitionTypeDef_tokens_1510, 5, "other"},
    {"partitionTypeDef", Dialect::MySQL, mysql_partitionTypeDef_tokens_1511, 6, "other"},
    {"partitionTypeDef", Dialect::MySQL, mysql_partitionTypeDef_tokens_1512, 5, "other"},
    {"partitionTypeDef", Dialect::MySQL, mysql_partitionTypeDef_tokens_1513, 6, "other"},
    {"subPartitions", Dialect::MySQL, mysql_subPartitions_tokens_1514, 9, "other"},
    {"subPartitions", Dialect::MySQL, mysql_subPartitions_tokens_1515, 8, "other"},
    {"partitionKeyAlgorithm", Dialect::MySQL, mysql_partitionKeyAlgorithm_tokens_1516, 3, "other"},
    {"partitionDefinitions", Dialect::MySQL, mysql_partitionDefinitions_tokens_1517, 5, "other"},
    {"partitionDefinition", Dialect::MySQL, mysql_partitionDefinition_tokens_1518, 12, "other"},
    {"partitionDefinition", Dialect::MySQL, mysql_partitionDefinition_tokens_1519, 12, "other"},
    {"partitionDefinition", Dialect::MySQL, mysql_partitionDefinition_tokens_1520, 11, "other"},
    {"partitionValuesIn", Dialect::MySQL, mysql_partitionValuesIn_tokens_1521, 1, "other"},
    {"partitionValuesIn", Dialect::MySQL, mysql_partitionValuesIn_tokens_1522, 5, "other"},
    {"partitionOption", Dialect::MySQL, mysql_partitionOption_tokens_1523, 4, "other"},
    {"partitionOption", Dialect::MySQL, mysql_partitionOption_tokens_1524, 5, "other"},
    {"partitionOption", Dialect::MySQL, mysql_partitionOption_tokens_1525, 4, "other"},
    {"partitionOption", Dialect::MySQL, mysql_partitionOption_tokens_1526, 4, "other"},
    {"partitionOption", Dialect::MySQL, mysql_partitionOption_tokens_1527, 4, "other"},
    {"partitionOption", Dialect::MySQL, mysql_partitionOption_tokens_1528, 5, "other"},
    {"partitionOption", Dialect::MySQL, mysql_partitionOption_tokens_1529, 5, "other"},
    {"partitionOption", Dialect::MySQL, mysql_partitionOption_tokens_1530, 4, "other"},
    {"subpartitionDefinition", Dialect::MySQL, mysql_subpartitionDefinition_tokens_1531, 3, "other"},
    {"partitionValueItemListParen", Dialect::MySQL, mysql_partitionValueItemListParen_tokens_1532, 5, "other"},
    {"partitionValueItem", Dialect::MySQL, mysql_partitionValueItem_tokens_1533, 1, "other"},
    {"partitionValueItem", Dialect::MySQL, mysql_partitionValueItem_tokens_1534, 1, "other"},
    {"definerClause", Dialect::MySQL, mysql_definerClause_tokens_1535, 3, "other"},
    {"ifExists", Dialect::MySQL, mysql_ifExists_tokens_1536, 2, "other"},
    {"ifExistsIdentifier", Dialect::MySQL, mysql_ifExistsIdentifier_tokens_1537, 2, "other"},
    {"persistedVariableIdentifier", Dialect::MySQL, mysql_persistedVariableIdentifier_tokens_1538, 1, "other"},
    {"persistedVariableIdentifier", Dialect::MySQL, mysql_persistedVariableIdentifier_tokens_1539, 3, "other"},
    {"persistedVariableIdentifier", Dialect::MySQL, mysql_persistedVariableIdentifier_tokens_1540, 4, "other"},
    {"ifNotExists", Dialect::MySQL, mysql_ifNotExists_tokens_1541, 3, "other"},
    {"ignoreUnknownUser", Dialect::MySQL, mysql_ignoreUnknownUser_tokens_1542, 3, "other"},
    {"procedureParameter", Dialect::MySQL, mysql_procedureParameter_tokens_1543, 3, "other"},
    {"procedureParameter", Dialect::MySQL, mysql_procedureParameter_tokens_1544, 3, "other"},
    {"procedureParameter", Dialect::MySQL, mysql_procedureParameter_tokens_1545, 3, "other"},
    {"functionParameter", Dialect::MySQL, mysql_functionParameter_tokens_1546, 2, "other"},
    {"collate", Dialect::MySQL, mysql_collate_tokens_1547, 2, "other"},
    {"typeWithOptCollate", Dialect::MySQL, mysql_typeWithOptCollate_tokens_1548, 2, "other"},
    {"schemaIdentifierPair", Dialect::MySQL, mysql_schemaIdentifierPair_tokens_1549, 5, "other"},
    {"viewRefList", Dialect::MySQL, mysql_viewRefList_tokens_1550, 3, "other"},
    {"charsetClause", Dialect::MySQL, mysql_charsetClause_tokens_1551, 2, "other"},
    {"fieldsClause", Dialect::MySQL, mysql_fieldsClause_tokens_1552, 2, "other"},
    {"fieldTerm", Dialect::MySQL, mysql_fieldTerm_tokens_1553, 3, "other"},
    {"fieldTerm", Dialect::MySQL, mysql_fieldTerm_tokens_1554, 4, "other"},
    {"fieldTerm", Dialect::MySQL, mysql_fieldTerm_tokens_1555, 3, "other"},
    {"linesClause", Dialect::MySQL, mysql_linesClause_tokens_1556, 2, "other"},
    {"lineTerm", Dialect::MySQL, mysql_lineTerm_tokens_1557, 3, "other"},
    {"lineTerm", Dialect::MySQL, mysql_lineTerm_tokens_1558, 3, "other"},
    {"userList", Dialect::MySQL, mysql_userList_tokens_1559, 3, "other"},
    {"identification", Dialect::MySQL, mysql_identification_tokens_1560, 1, "other"},
    {"identification", Dialect::MySQL, mysql_identification_tokens_1561, 1, "other"},
    {"identification", Dialect::MySQL, mysql_identification_tokens_1562, 1, "other"},
    {"identification", Dialect::MySQL, mysql_identification_tokens_1563, 1, "other"},
    {"identification", Dialect::MySQL, mysql_identification_tokens_1564, 1, "other"},
    {"identification", Dialect::MySQL, mysql_identification_tokens_1565, 1, "other"},
    {"identifiedByPassword", Dialect::MySQL, mysql_identifiedByPassword_tokens_1566, 3, "other"},
    {"identifiedByRandomPassword", Dialect::MySQL, mysql_identifiedByRandomPassword_tokens_1567, 4, "other"},
    {"identifiedWithPlugin", Dialect::MySQL, mysql_identifiedWithPlugin_tokens_1568, 3, "other"},
    {"identifiedWithPluginAsAuth", Dialect::MySQL, mysql_identifiedWithPluginAsAuth_tokens_1569, 5, "other"},
    {"identifiedWithPluginByPassword", Dialect::MySQL, mysql_identifiedWithPluginByPassword_tokens_1570, 5, "other"},
    {"identifiedWithPluginByRandomPassword", Dialect::MySQL, mysql_identifiedWithPluginByRandomPassword_tokens_1571, 6, "other"},
    {"initialAuth", Dialect::MySQL, mysql_initialAuth_tokens_1572, 3, "other"},
    {"initialAuth", Dialect::MySQL, mysql_initialAuth_tokens_1573, 3, "other"},
    {"initialAuth", Dialect::MySQL, mysql_initialAuth_tokens_1574, 3, "other"},
    {"retainCurrentPassword", Dialect::MySQL, mysql_retainCurrentPassword_tokens_1575, 3, "other"},
    {"discardOldPassword", Dialect::MySQL, mysql_discardOldPassword_tokens_1576, 3, "other"},
    {"userRegistration", Dialect::MySQL, mysql_userRegistration_tokens_1577, 3, "other"},
    {"userRegistration", Dialect::MySQL, mysql_userRegistration_tokens_1578, 2, "other"},
    {"userRegistration", Dialect::MySQL, mysql_userRegistration_tokens_1579, 7, "other"},
    {"factor", Dialect::MySQL, mysql_factor_tokens_1580, 2, "other"},
    {"replacePassword", Dialect::MySQL, mysql_replacePassword_tokens_1581, 2, "other"},
    {"userIdentifierOrText", Dialect::MySQL, mysql_userIdentifierOrText_tokens_1582, 2, "other"},
    {"user", Dialect::MySQL, mysql_user_tokens_1583, 1, "other"},
    {"user", Dialect::MySQL, mysql_user_tokens_1584, 2, "other"},
    {"likeClause", Dialect::MySQL, mysql_likeClause_tokens_1585, 2, "other"},
    {"likeOrWhere", Dialect::MySQL, mysql_likeOrWhere_tokens_1586, 1, "other"},
    {"likeOrWhere", Dialect::MySQL, mysql_likeOrWhere_tokens_1587, 1, "other"},
    {"onlineOption", Dialect::MySQL, mysql_onlineOption_tokens_1588, 1, "other"},
    {"onlineOption", Dialect::MySQL, mysql_onlineOption_tokens_1589, 1, "other"},
    {"noWriteToBinLog", Dialect::MySQL, mysql_noWriteToBinLog_tokens_1590, 1, "other"},
    {"noWriteToBinLog", Dialect::MySQL, mysql_noWriteToBinLog_tokens_1591, 1, "other"},
    {"usePartition", Dialect::MySQL, mysql_usePartition_tokens_1592, 2, "other"},
    {"fieldIdentifier", Dialect::MySQL, mysql_fieldIdentifier_tokens_1593, 1, "other"},
    {"fieldIdentifier", Dialect::MySQL, mysql_fieldIdentifier_tokens_1594, 2, "other"},
    {"columnName", Dialect::MySQL, mysql_columnName_tokens_1595, 1, "other"},
    {"columnInternalRef", Dialect::MySQL, mysql_columnInternalRef_tokens_1596, 1, "other"},
    {"columnInternalRefList", Dialect::MySQL, mysql_columnInternalRefList_tokens_1597, 5, "other"},
    {"columnRef", Dialect::MySQL, mysql_columnRef_tokens_1598, 1, "other"},
    {"indexName", Dialect::MySQL, mysql_indexName_tokens_1599, 1, "other"},
    {"indexRef", Dialect::MySQL, mysql_indexRef_tokens_1600, 1, "other"},
    {"tableWild", Dialect::MySQL, mysql_tableWild_tokens_1601, 5, "other"},
    {"schemaName", Dialect::MySQL, mysql_schemaName_tokens_1602, 1, "other"},
    {"schemaRef", Dialect::MySQL, mysql_schemaRef_tokens_1603, 1, "other"},
    {"procedureName", Dialect::MySQL, mysql_procedureName_tokens_1604, 1, "other"},
    {"procedureRef", Dialect::MySQL, mysql_procedureRef_tokens_1605, 1, "other"},
    {"functionName", Dialect::MySQL, mysql_functionName_tokens_1606, 1, "other"},
    {"functionRef", Dialect::MySQL, mysql_functionRef_tokens_1607, 1, "other"},
    {"triggerName", Dialect::MySQL, mysql_triggerName_tokens_1608, 1, "other"},
    {"triggerRef", Dialect::MySQL, mysql_triggerRef_tokens_1609, 1, "other"},
    {"viewName", Dialect::MySQL, mysql_viewName_tokens_1610, 1, "other"},
    {"viewName", Dialect::MySQL, mysql_viewName_tokens_1611, 1, "other"},
    {"viewRef", Dialect::MySQL, mysql_viewRef_tokens_1612, 1, "other"},
    {"viewRef", Dialect::MySQL, mysql_viewRef_tokens_1613, 1, "other"},
    {"tablespaceName", Dialect::MySQL, mysql_tablespaceName_tokens_1614, 1, "other"},
    {"tablespaceRef", Dialect::MySQL, mysql_tablespaceRef_tokens_1615, 1, "other"},
    {"logfileGroupName", Dialect::MySQL, mysql_logfileGroupName_tokens_1616, 1, "other"},
    {"logfileGroupRef", Dialect::MySQL, mysql_logfileGroupRef_tokens_1617, 1, "other"},
    {"eventName", Dialect::MySQL, mysql_eventName_tokens_1618, 1, "other"},
    {"eventRef", Dialect::MySQL, mysql_eventRef_tokens_1619, 1, "other"},
    {"udfName", Dialect::MySQL, mysql_udfName_tokens_1620, 1, "other"},
    {"serverName", Dialect::MySQL, mysql_serverName_tokens_1621, 1, "other"},
    {"serverRef", Dialect::MySQL, mysql_serverRef_tokens_1622, 1, "other"},
    {"engineRef", Dialect::MySQL, mysql_engineRef_tokens_1623, 1, "other"},
    {"tableName", Dialect::MySQL, mysql_tableName_tokens_1624, 1, "other"},
    {"tableName", Dialect::MySQL, mysql_tableName_tokens_1625, 1, "other"},
    {"filterTableRef", Dialect::MySQL, mysql_filterTableRef_tokens_1626, 2, "other"},
    {"tableRefWithWildcard", Dialect::MySQL, mysql_tableRefWithWildcard_tokens_1627, 3, "other"},
    {"tableRefWithWildcard", Dialect::MySQL, mysql_tableRefWithWildcard_tokens_1628, 4, "other"},
    {"tableRef", Dialect::MySQL, mysql_tableRef_tokens_1629, 1, "other"},
    {"tableRef", Dialect::MySQL, mysql_tableRef_tokens_1630, 1, "other"},
    {"tableRefList", Dialect::MySQL, mysql_tableRefList_tokens_1631, 3, "other"},
    {"tableAliasRefList", Dialect::MySQL, mysql_tableAliasRefList_tokens_1632, 3, "other"},
    {"parameterName", Dialect::MySQL, mysql_parameterName_tokens_1633, 1, "other"},
    {"labelIdentifier", Dialect::MySQL, mysql_labelIdentifier_tokens_1634, 1, "other"},
    {"labelIdentifier", Dialect::MySQL, mysql_labelIdentifier_tokens_1635, 1, "other"},
    {"labelRef", Dialect::MySQL, mysql_labelRef_tokens_1636, 1, "other"},
    {"roleIdentifier", Dialect::MySQL, mysql_roleIdentifier_tokens_1637, 1, "other"},
    {"roleIdentifier", Dialect::MySQL, mysql_roleIdentifier_tokens_1638, 1, "other"},
    {"pluginRef", Dialect::MySQL, mysql_pluginRef_tokens_1639, 1, "other"},
    {"componentRef", Dialect::MySQL, mysql_componentRef_tokens_1640, 1, "other"},
    {"resourceGroupRef", Dialect::MySQL, mysql_resourceGroupRef_tokens_1641, 1, "other"},
    {"windowName", Dialect::MySQL, mysql_windowName_tokens_1642, 1, "other"},
    {"pureIdentifier", Dialect::MySQL, mysql_pureIdentifier_tokens_1643, 1, "other"},
    {"pureIdentifier", Dialect::MySQL, mysql_pureIdentifier_tokens_1644, 1, "other"},
    {"pureIdentifier", Dialect::MySQL, mysql_pureIdentifier_tokens_1645, 3, "other"},
    {"identifier", Dialect::MySQL, mysql_identifier_tokens_1646, 1, "other"},
    {"identifier", Dialect::MySQL, mysql_identifier_tokens_1647, 1, "other"},
    {"identifierList", Dialect::MySQL, mysql_identifierList_tokens_1648, 3, "other"},
    {"identifierListWithParentheses", Dialect::MySQL, mysql_identifierListWithParentheses_tokens_1649, 3, "other"},
    {"qualifiedIdentifier", Dialect::MySQL, mysql_qualifiedIdentifier_tokens_1650, 2, "other"},
    {"simpleIdentifier", Dialect::MySQL, mysql_simpleIdentifier_tokens_1651, 3, "other"},
    {"dotIdentifier", Dialect::MySQL, mysql_dotIdentifier_tokens_1652, 2, "other"},
    {"ulong_number", Dialect::MySQL, mysql_ulong_number_tokens_1653, 1, "other"},
    {"ulong_number", Dialect::MySQL, mysql_ulong_number_tokens_1654, 1, "other"},
    {"ulong_number", Dialect::MySQL, mysql_ulong_number_tokens_1655, 1, "other"},
    {"ulong_number", Dialect::MySQL, mysql_ulong_number_tokens_1656, 1, "other"},
    {"ulong_number", Dialect::MySQL, mysql_ulong_number_tokens_1657, 1, "other"},
    {"ulong_number", Dialect::MySQL, mysql_ulong_number_tokens_1658, 1, "other"},
    {"real_ulong_number", Dialect::MySQL, mysql_real_ulong_number_tokens_1659, 1, "other"},
    {"real_ulong_number", Dialect::MySQL, mysql_real_ulong_number_tokens_1660, 1, "other"},
    {"real_ulong_number", Dialect::MySQL, mysql_real_ulong_number_tokens_1661, 1, "other"},
    {"real_ulong_number", Dialect::MySQL, mysql_real_ulong_number_tokens_1662, 1, "other"},
    {"ulonglongNumber", Dialect::MySQL, mysql_ulonglongNumber_tokens_1663, 1, "other"},
    {"ulonglongNumber", Dialect::MySQL, mysql_ulonglongNumber_tokens_1664, 1, "other"},
    {"ulonglongNumber", Dialect::MySQL, mysql_ulonglongNumber_tokens_1665, 1, "other"},
    {"ulonglongNumber", Dialect::MySQL, mysql_ulonglongNumber_tokens_1666, 1, "other"},
    {"ulonglongNumber", Dialect::MySQL, mysql_ulonglongNumber_tokens_1667, 1, "other"},
    {"real_ulonglong_number", Dialect::MySQL, mysql_real_ulonglong_number_tokens_1668, 1, "other"},
    {"real_ulonglong_number", Dialect::MySQL, mysql_real_ulonglong_number_tokens_1669, 3, "other"},
    {"real_ulonglong_number", Dialect::MySQL, mysql_real_ulonglong_number_tokens_1670, 1, "other"},
    {"real_ulonglong_number", Dialect::MySQL, mysql_real_ulonglong_number_tokens_1671, 1, "other"},
    {"signedLiteral", Dialect::MySQL, mysql_signedLiteral_tokens_1672, 1, "other"},
    {"signedLiteral", Dialect::MySQL, mysql_signedLiteral_tokens_1673, 2, "other"},
    {"signedLiteral", Dialect::MySQL, mysql_signedLiteral_tokens_1674, 2, "other"},
    {"signedLiteralOrNull", Dialect::MySQL, mysql_signedLiteralOrNull_tokens_1675, 1, "other"},
    {"signedLiteralOrNull", Dialect::MySQL, mysql_signedLiteralOrNull_tokens_1676, 3, "other"},
    {"literal", Dialect::MySQL, mysql_literal_tokens_1677, 1, "other"},
    {"literal", Dialect::MySQL, mysql_literal_tokens_1678, 1, "other"},
    {"literal", Dialect::MySQL, mysql_literal_tokens_1679, 1, "other"},
    {"literal", Dialect::MySQL, mysql_literal_tokens_1680, 1, "other"},
    {"literal", Dialect::MySQL, mysql_literal_tokens_1681, 1, "other"},
    {"literal", Dialect::MySQL, mysql_literal_tokens_1682, 2, "other"},
    {"literal", Dialect::MySQL, mysql_literal_tokens_1683, 2, "other"},
    {"literalOrNull", Dialect::MySQL, mysql_literalOrNull_tokens_1684, 1, "other"},
    {"literalOrNull", Dialect::MySQL, mysql_literalOrNull_tokens_1685, 3, "other"},
    {"nullAsLiteral", Dialect::MySQL, mysql_nullAsLiteral_tokens_1686, 1, "other"},
    {"stringList", Dialect::MySQL, mysql_stringList_tokens_1687, 5, "other"},
    {"textStringLiteral", Dialect::MySQL, mysql_textStringLiteral_tokens_1688, 2, "other"},
    {"textStringLiteral", Dialect::MySQL, mysql_textStringLiteral_tokens_1689, 4, "other"},
    {"textString", Dialect::MySQL, mysql_textString_tokens_1690, 1, "other"},
    {"textString", Dialect::MySQL, mysql_textString_tokens_1691, 1, "other"},
    {"textString", Dialect::MySQL, mysql_textString_tokens_1692, 1, "other"},
    {"textStringHash", Dialect::MySQL, mysql_textStringHash_tokens_1693, 1, "other"},
    {"textStringHash", Dialect::MySQL, mysql_textStringHash_tokens_1694, 3, "other"},
    {"textLiteral", Dialect::MySQL, mysql_textLiteral_tokens_1695, 3, "other"},
    {"textLiteral", Dialect::MySQL, mysql_textLiteral_tokens_1696, 2, "other"},
    {"textStringNoLinebreak", Dialect::MySQL, mysql_textStringNoLinebreak_tokens_1697, 1, "other"},
    {"textStringLiteralList", Dialect::MySQL, mysql_textStringLiteralList_tokens_1698, 3, "other"},
    {"numLiteral", Dialect::MySQL, mysql_numLiteral_tokens_1699, 1, "other"},
    {"numLiteral", Dialect::MySQL, mysql_numLiteral_tokens_1700, 1, "other"},
    {"numLiteral", Dialect::MySQL, mysql_numLiteral_tokens_1701, 1, "other"},
    {"boolLiteral", Dialect::MySQL, mysql_boolLiteral_tokens_1702, 1, "other"},
    {"boolLiteral", Dialect::MySQL, mysql_boolLiteral_tokens_1703, 1, "other"},
    {"nullLiteral", Dialect::MySQL, mysql_nullLiteral_tokens_1704, 1, "other"},
    {"nullLiteral", Dialect::MySQL, mysql_nullLiteral_tokens_1705, 1, "other"},
    {"int64Literal", Dialect::MySQL, mysql_int64Literal_tokens_1706, 1, "other"},
    {"int64Literal", Dialect::MySQL, mysql_int64Literal_tokens_1707, 1, "other"},
    {"int64Literal", Dialect::MySQL, mysql_int64Literal_tokens_1708, 1, "other"},
    {"temporalLiteral", Dialect::MySQL, mysql_temporalLiteral_tokens_1709, 2, "other"},
    {"temporalLiteral", Dialect::MySQL, mysql_temporalLiteral_tokens_1710, 2, "other"},
    {"temporalLiteral", Dialect::MySQL, mysql_temporalLiteral_tokens_1711, 2, "other"},
    {"floatOptions", Dialect::MySQL, mysql_floatOptions_tokens_1712, 1, "other"},
    {"floatOptions", Dialect::MySQL, mysql_floatOptions_tokens_1713, 1, "other"},
    {"standardFloatOptions", Dialect::MySQL, mysql_standardFloatOptions_tokens_1714, 1, "other"},
    {"precision", Dialect::MySQL, mysql_precision_tokens_1715, 5, "other"},
    {"textOrIdentifier", Dialect::MySQL, mysql_textOrIdentifier_tokens_1716, 1, "other"},
    {"textOrIdentifier", Dialect::MySQL, mysql_textOrIdentifier_tokens_1717, 1, "other"},
    {"lValueIdentifier", Dialect::MySQL, mysql_lValueIdentifier_tokens_1718, 1, "other"},
    {"lValueIdentifier", Dialect::MySQL, mysql_lValueIdentifier_tokens_1719, 1, "other"},
    {"roleIdentifierOrText", Dialect::MySQL, mysql_roleIdentifierOrText_tokens_1720, 1, "other"},
    {"roleIdentifierOrText", Dialect::MySQL, mysql_roleIdentifierOrText_tokens_1721, 1, "other"},
    {"sizeNumber", Dialect::MySQL, mysql_sizeNumber_tokens_1722, 1, "other"},
    {"sizeNumber", Dialect::MySQL, mysql_sizeNumber_tokens_1723, 1, "other"},
    {"parentheses", Dialect::MySQL, mysql_parentheses_tokens_1724, 2, "other"},
    {"equal", Dialect::MySQL, mysql_equal_tokens_1725, 1, "other"},
    {"equal", Dialect::MySQL, mysql_equal_tokens_1726, 1, "other"},
    {"optionType", Dialect::MySQL, mysql_optionType_tokens_1727, 1, "other"},
    {"optionType", Dialect::MySQL, mysql_optionType_tokens_1728, 1, "other"},
    {"optionType", Dialect::MySQL, mysql_optionType_tokens_1729, 1, "other"},
    {"optionType", Dialect::MySQL, mysql_optionType_tokens_1730, 1, "other"},
    {"optionType", Dialect::MySQL, mysql_optionType_tokens_1731, 1, "other"},
    {"rvalueSystemVariableType", Dialect::MySQL, mysql_rvalueSystemVariableType_tokens_1732, 2, "other"},
    {"rvalueSystemVariableType", Dialect::MySQL, mysql_rvalueSystemVariableType_tokens_1733, 2, "other"},
    {"rvalueSystemVariableType", Dialect::MySQL, mysql_rvalueSystemVariableType_tokens_1734, 2, "other"},
    {"setVarIdentType", Dialect::MySQL, mysql_setVarIdentType_tokens_1735, 2, "other"},
    {"setVarIdentType", Dialect::MySQL, mysql_setVarIdentType_tokens_1736, 2, "other"},
    {"setVarIdentType", Dialect::MySQL, mysql_setVarIdentType_tokens_1737, 2, "other"},
    {"setVarIdentType", Dialect::MySQL, mysql_setVarIdentType_tokens_1738, 2, "other"},
    {"setVarIdentType", Dialect::MySQL, mysql_setVarIdentType_tokens_1739, 2, "other"},
    {"jsonAttribute", Dialect::MySQL, mysql_jsonAttribute_tokens_1740, 1, "other"},
    {"identifierKeyword", Dialect::MySQL, mysql_identifierKeyword_tokens_1741, 3, "other"},
    {"identifierKeyword", Dialect::MySQL, mysql_identifierKeyword_tokens_1742, 3, "other"},
    {"identifierKeyword", Dialect::MySQL, mysql_identifierKeyword_tokens_1743, 3, "other"},
    {"identifierKeyword", Dialect::MySQL, mysql_identifierKeyword_tokens_1744, 3, "other"},
    {"identifierKeyword", Dialect::MySQL, mysql_identifierKeyword_tokens_1745, 5, "other"},
    {"identifierKeyword", Dialect::MySQL, mysql_identifierKeyword_tokens_1746, 1, "other"},
    {"identifierKeyword", Dialect::MySQL, mysql_identifierKeyword_tokens_1747, 1, "other"},
    {"identifierKeyword", Dialect::MySQL, mysql_identifierKeyword_tokens_1748, 1, "other"},
    {"identifierKeyword", Dialect::MySQL, mysql_identifierKeyword_tokens_1749, 1, "other"},
    {"identifierKeyword", Dialect::MySQL, mysql_identifierKeyword_tokens_1750, 1, "other"},
    {"identifierKeywordsAmbiguous1RolesAndLabels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous1RolesAndLabels_tokens_1751, 1, "other"},
    {"identifierKeywordsAmbiguous1RolesAndLabels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous1RolesAndLabels_tokens_1752, 1, "other"},
    {"identifierKeywordsAmbiguous1RolesAndLabels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous1RolesAndLabels_tokens_1753, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1754, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1755, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1756, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1757, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1758, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1759, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1760, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1761, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1762, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1763, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1764, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1765, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1766, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1767, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1768, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1769, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1770, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1771, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1772, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1773, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1774, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1775, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1776, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1777, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1778, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1779, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1780, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1781, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1782, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1783, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1784, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1785, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1786, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1787, 1, "other"},
    {"identifierKeywordsAmbiguous2Labels", Dialect::MySQL, mysql_identifierKeywordsAmbiguous2Labels_tokens_1788, 1, "other"},
    {"labelKeyword", Dialect::MySQL, mysql_labelKeyword_tokens_1789, 3, "other"},
    {"labelKeyword", Dialect::MySQL, mysql_labelKeyword_tokens_1790, 3, "other"},
    {"labelKeyword", Dialect::MySQL, mysql_labelKeyword_tokens_1791, 3, "other"},
    {"labelKeyword", Dialect::MySQL, mysql_labelKeyword_tokens_1792, 3, "other"},
    {"labelKeyword", Dialect::MySQL, mysql_labelKeyword_tokens_1793, 3, "other"},
    {"labelKeyword", Dialect::MySQL, mysql_labelKeyword_tokens_1794, 3, "other"},
    {"labelKeyword", Dialect::MySQL, mysql_labelKeyword_tokens_1795, 3, "other"},
    {"labelKeyword", Dialect::MySQL, mysql_labelKeyword_tokens_1796, 3, "other"},
    {"labelKeyword", Dialect::MySQL, mysql_labelKeyword_tokens_1797, 3, "other"},
    {"labelKeyword", Dialect::MySQL, mysql_labelKeyword_tokens_1798, 3, "other"},
    {"labelKeyword", Dialect::MySQL, mysql_labelKeyword_tokens_1799, 1, "other"},
    {"labelKeyword", Dialect::MySQL, mysql_labelKeyword_tokens_1800, 1, "other"},
    {"labelKeyword", Dialect::MySQL, mysql_labelKeyword_tokens_1801, 1, "other"},
    {"identifierKeywordsAmbiguous3Roles", Dialect::MySQL, mysql_identifierKeywordsAmbiguous3Roles_tokens_1802, 1, "other"},
    {"identifierKeywordsAmbiguous3Roles", Dialect::MySQL, mysql_identifierKeywordsAmbiguous3Roles_tokens_1803, 1, "other"},
    {"identifierKeywordsAmbiguous3Roles", Dialect::MySQL, mysql_identifierKeywordsAmbiguous3Roles_tokens_1804, 1, "other"},
    {"identifierKeywordsAmbiguous3Roles", Dialect::MySQL, mysql_identifierKeywordsAmbiguous3Roles_tokens_1805, 1, "other"},
    {"identifierKeywordsAmbiguous3Roles", Dialect::MySQL, mysql_identifierKeywordsAmbiguous3Roles_tokens_1806, 1, "other"},
    {"identifierKeywordsAmbiguous3Roles", Dialect::MySQL, mysql_identifierKeywordsAmbiguous3Roles_tokens_1807, 1, "other"},
    {"identifierKeywordsAmbiguous3Roles", Dialect::MySQL, mysql_identifierKeywordsAmbiguous3Roles_tokens_1808, 1, "other"},
    {"identifierKeywordsAmbiguous3Roles", Dialect::MySQL, mysql_identifierKeywordsAmbiguous3Roles_tokens_1809, 1, "other"},
    {"identifierKeywordsAmbiguous3Roles", Dialect::MySQL, mysql_identifierKeywordsAmbiguous3Roles_tokens_1810, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1811, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1812, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1813, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1814, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1815, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1816, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1817, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1818, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1819, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1820, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1821, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1822, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1823, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1824, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1825, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1826, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1827, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1828, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1829, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1830, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1831, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1832, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1833, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1834, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1835, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1836, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1837, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1838, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1839, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1840, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1841, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1842, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1843, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1844, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1845, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1846, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1847, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1848, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1849, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1850, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1851, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1852, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1853, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1854, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1855, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1856, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1857, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1858, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1859, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1860, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1861, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1862, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1863, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1864, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1865, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1866, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1867, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1868, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1869, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1870, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1871, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1872, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1873, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1874, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1875, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1876, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1877, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1878, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1879, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1880, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1881, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1882, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1883, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1884, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1885, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1886, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1887, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1888, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1889, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1890, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1891, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1892, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1893, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1894, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1895, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1896, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1897, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1898, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1899, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1900, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1901, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1902, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1903, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1904, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1905, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1906, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1907, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1908, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1909, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1910, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1911, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1912, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1913, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1914, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1915, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1916, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1917, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1918, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1919, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1920, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1921, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1922, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1923, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1924, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1925, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1926, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1927, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1928, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1929, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1930, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1931, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1932, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1933, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1934, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1935, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1936, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1937, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1938, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1939, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1940, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1941, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1942, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1943, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1944, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1945, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1946, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1947, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1948, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1949, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1950, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1951, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1952, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1953, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1954, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1955, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1956, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1957, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1958, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1959, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1960, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1961, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1962, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1963, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1964, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1965, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1966, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1967, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1968, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1969, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1970, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1971, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1972, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1973, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1974, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1975, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1976, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1977, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1978, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1979, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1980, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1981, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1982, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1983, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1984, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1985, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1986, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1987, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1988, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1989, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1990, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1991, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1992, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1993, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1994, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1995, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1996, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1997, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1998, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_1999, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2000, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2001, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2002, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2003, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2004, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2005, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2006, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2007, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2008, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2009, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2010, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2011, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2012, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2013, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2014, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2015, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2016, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2017, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2018, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2019, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2020, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2021, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2022, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2023, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2024, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2025, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2026, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2027, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2028, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2029, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2030, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2031, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2032, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2033, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2034, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2035, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2036, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2037, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2038, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2039, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2040, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2041, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2042, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2043, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2044, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2045, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2046, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2047, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2048, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2049, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2050, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2051, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2052, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2053, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2054, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2055, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2056, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2057, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2058, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2059, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2060, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2061, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2062, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2063, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2064, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2065, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2066, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2067, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2068, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2069, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2070, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2071, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2072, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2073, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2074, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2075, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2076, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2077, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2078, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2079, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2080, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2081, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2082, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2083, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2084, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2085, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2086, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2087, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2088, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2089, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2090, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2091, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2092, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2093, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2094, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2095, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2096, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2097, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2098, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2099, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2100, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2101, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2102, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2103, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2104, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2105, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2106, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2107, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2108, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2109, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2110, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2111, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2112, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2113, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2114, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2115, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2116, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2117, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2118, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2119, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2120, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2121, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2122, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2123, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2124, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2125, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2126, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2127, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2128, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2129, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2130, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2131, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2132, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2133, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2134, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2135, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2136, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2137, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2138, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2139, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2140, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2141, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2142, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2143, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2144, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2145, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2146, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2147, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2148, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2149, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2150, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2151, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2152, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2153, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2154, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2155, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2156, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2157, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2158, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2159, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2160, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2161, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2162, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2163, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2164, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2165, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2166, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2167, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2168, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2169, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2170, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2171, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2172, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2173, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2174, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2175, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2176, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2177, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2178, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2179, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2180, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2181, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2182, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2183, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2184, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2185, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2186, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2187, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2188, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2189, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2190, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2191, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2192, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2193, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2194, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2195, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2196, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2197, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2198, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2199, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2200, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2201, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2202, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2203, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2204, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2205, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2206, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2207, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2208, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2209, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2210, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2211, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2212, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2213, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2214, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2215, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2216, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2217, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2218, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2219, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2220, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2221, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2222, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2223, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2224, 1, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2225, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2226, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2227, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2228, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2229, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2230, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2231, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2232, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2233, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2234, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2235, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2236, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2237, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2238, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2239, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2240, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2241, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2242, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2243, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2244, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2245, 3, "other"},
    {"identifierKeywordsUnambiguous", Dialect::MySQL, mysql_identifierKeywordsUnambiguous_tokens_2246, 3, "other"},
    {"roleKeyword", Dialect::MySQL, mysql_roleKeyword_tokens_2247, 3, "other"},
    {"roleKeyword", Dialect::MySQL, mysql_roleKeyword_tokens_2248, 3, "other"},
    {"roleKeyword", Dialect::MySQL, mysql_roleKeyword_tokens_2249, 1, "other"},
    {"roleKeyword", Dialect::MySQL, mysql_roleKeyword_tokens_2250, 1, "other"},
    {"roleKeyword", Dialect::MySQL, mysql_roleKeyword_tokens_2251, 1, "other"},
    {"lValueKeyword", Dialect::MySQL, mysql_lValueKeyword_tokens_2252, 1, "other"},
    {"lValueKeyword", Dialect::MySQL, mysql_lValueKeyword_tokens_2253, 1, "other"},
    {"lValueKeyword", Dialect::MySQL, mysql_lValueKeyword_tokens_2254, 1, "other"},
    {"lValueKeyword", Dialect::MySQL, mysql_lValueKeyword_tokens_2255, 1, "other"},
    {"identifierKeywordsAmbiguous4SystemVariables", Dialect::MySQL, mysql_identifierKeywordsAmbiguous4SystemVariables_tokens_2256, 1, "other"},
    {"identifierKeywordsAmbiguous4SystemVariables", Dialect::MySQL, mysql_identifierKeywordsAmbiguous4SystemVariables_tokens_2257, 1, "other"},
    {"identifierKeywordsAmbiguous4SystemVariables", Dialect::MySQL, mysql_identifierKeywordsAmbiguous4SystemVariables_tokens_2258, 1, "other"},
    {"identifierKeywordsAmbiguous4SystemVariables", Dialect::MySQL, mysql_identifierKeywordsAmbiguous4SystemVariables_tokens_2259, 1, "other"},
    {"identifierKeywordsAmbiguous4SystemVariables", Dialect::MySQL, mysql_identifierKeywordsAmbiguous4SystemVariables_tokens_2260, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2261, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2262, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2263, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2264, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2265, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2266, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2267, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2268, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2269, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2270, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2271, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2272, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2273, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2274, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2275, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2276, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2277, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2278, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2279, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2280, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2281, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2282, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2283, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2284, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2285, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2286, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2287, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2288, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2289, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2290, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2291, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2292, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2293, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2294, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2295, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2296, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2297, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2298, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2299, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2300, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2301, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2302, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2303, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2304, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2305, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2306, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2307, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2308, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2309, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2310, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2311, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2312, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2313, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2314, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2315, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2316, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2317, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2318, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2319, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2320, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2321, 1, "other"},
    {"roleOrIdentifierKeyword", Dialect::MySQL, mysql_roleOrIdentifierKeyword_tokens_2322, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2323, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2324, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2325, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2326, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2327, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2328, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2329, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2330, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2331, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2332, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2333, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2334, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2335, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2336, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2337, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2338, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2339, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2340, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2341, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2342, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2343, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2344, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2345, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2346, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2347, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2348, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2349, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2350, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2351, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2352, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2353, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2354, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2355, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2356, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2357, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2358, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2359, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2360, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2361, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2362, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2363, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2364, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2365, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2366, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2367, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2368, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2369, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2370, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2371, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2372, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2373, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2374, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2375, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2376, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2377, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2378, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2379, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2380, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2381, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2382, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2383, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2384, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2385, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2386, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2387, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2388, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2389, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2390, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2391, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2392, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2393, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2394, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2395, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2396, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2397, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2398, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2399, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2400, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2401, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2402, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2403, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2404, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2405, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2406, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2407, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2408, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2409, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2410, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2411, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2412, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2413, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2414, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2415, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2416, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2417, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2418, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2419, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2420, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2421, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2422, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2423, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2424, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2425, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2426, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2427, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2428, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2429, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2430, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2431, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2432, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2433, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2434, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2435, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2436, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2437, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2438, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2439, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2440, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2441, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2442, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2443, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2444, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2445, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2446, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2447, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2448, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2449, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2450, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2451, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2452, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2453, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2454, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2455, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2456, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2457, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2458, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2459, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2460, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2461, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2462, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2463, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2464, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2465, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2466, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2467, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2468, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2469, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2470, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2471, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2472, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2473, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2474, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2475, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2476, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2477, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2478, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2479, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2480, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2481, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2482, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2483, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2484, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2485, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2486, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2487, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2488, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2489, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2490, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2491, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2492, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2493, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2494, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2495, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2496, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2497, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2498, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2499, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2500, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2501, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2502, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2503, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2504, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2505, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2506, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2507, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2508, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2509, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2510, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2511, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2512, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2513, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2514, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2515, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2516, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2517, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2518, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2519, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2520, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2521, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2522, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2523, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2524, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2525, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2526, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2527, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2528, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2529, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2530, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2531, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2532, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2533, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2534, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2535, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2536, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2537, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2538, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2539, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2540, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2541, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2542, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2543, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2544, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2545, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2546, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2547, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2548, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2549, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2550, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2551, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2552, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2553, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2554, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2555, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2556, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2557, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2558, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2559, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2560, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2561, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2562, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2563, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2564, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2565, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2566, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2567, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2568, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2569, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2570, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2571, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2572, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2573, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2574, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2575, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2576, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2577, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2578, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2579, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2580, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2581, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2582, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2583, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2584, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2585, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2586, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2587, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2588, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2589, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2590, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2591, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2592, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2593, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2594, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2595, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2596, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2597, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2598, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2599, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2600, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2601, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2602, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2603, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2604, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2605, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2606, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2607, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2608, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2609, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2610, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2611, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2612, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2613, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2614, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2615, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2616, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2617, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2618, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2619, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2620, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2621, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2622, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2623, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2624, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2625, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2626, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2627, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2628, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2629, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2630, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2631, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2632, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2633, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2634, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2635, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2636, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2637, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2638, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2639, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2640, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2641, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2642, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2643, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2644, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2645, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2646, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2647, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2648, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2649, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2650, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2651, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2652, 1, "other"},
    {"roleOrLabelKeyword", Dialect::MySQL, mysql_roleOrLabelKeyword_tokens_2653, 3, "other"},
    {"selectStatement", Dialect::MySQL, mysql_selectStatement_tokens_0, 2, "select_statement"},
    {"selectStatement", Dialect::MySQL, mysql_selectStatement_tokens_1, 1, "select_statement"},
    {"selectStatementWithInto", Dialect::MySQL, mysql_selectStatementWithInto_tokens_2, 3, "select_statement"},
    {"selectStatementWithInto", Dialect::MySQL, mysql_selectStatementWithInto_tokens_3, 3, "select_statement"},
    {"selectStatementWithInto", Dialect::MySQL, mysql_selectStatementWithInto_tokens_4, 3, "select_statement"},
    {"selectStatementWithInto", Dialect::MySQL, mysql_selectStatementWithInto_tokens_5, 4, "select_statement"},
    {"selectOption", Dialect::MySQL, mysql_selectOption_tokens_6, 1, "select_statement"},
    {"selectOption", Dialect::MySQL, mysql_selectOption_tokens_7, 1, "select_statement"},
    {"selectItemList", Dialect::MySQL, mysql_selectItemList_tokens_8, 3, "select_statement"},
    {"selectItemList", Dialect::MySQL, mysql_selectItemList_tokens_9, 3, "select_statement"},
    {"selectItem", Dialect::MySQL, mysql_selectItem_tokens_10, 1, "select_statement"},
    {"selectItem", Dialect::MySQL, mysql_selectItem_tokens_11, 2, "select_statement"},
    {"selectAlias", Dialect::MySQL, mysql_selectAlias_tokens_12, 2, "select_statement"},
    {"selectAlias", Dialect::MySQL, mysql_selectAlias_tokens_13, 2, "select_statement"},
    {"updateStatement", Dialect::MySQL, mysql_updateStatement_tokens_0, 10, "update_statement"},
    {"histogramAutoUpdate", Dialect::MySQL, mysql_histogramAutoUpdate_tokens_1, 4, "update_statement"},
    {"histogramAutoUpdate", Dialect::MySQL, mysql_histogramAutoUpdate_tokens_2, 4, "update_statement"},
    {"histogramUpdateParam", Dialect::MySQL, mysql_histogramUpdateParam_tokens_3, 2, "update_statement"},
    {"histogramUpdateParam", Dialect::MySQL, mysql_histogramUpdateParam_tokens_4, 5, "update_statement"},
    {"updateList", Dialect::MySQL, mysql_updateList_tokens_5, 3, "update_statement"},
    {"updateElement", Dialect::MySQL, mysql_updateElement_tokens_6, 3, "update_statement"},
    {"updateElement", Dialect::MySQL, mysql_updateElement_tokens_7, 3, "update_statement"}
};

constexpr size_t pattern_count = 2972;

}  // namespace grammar
}  // namespace libsqlglot
