/**
 * Authors: El Mehdi ASSALI and Widad BOUJAAFAR
 */

#ifndef SYNTACTICAL_ANALYZER
#define SYNTACTICAL_ANALYZER

#include <stdbool.h>
#include "ast.h"
#include "cfg.h"

typedef enum {
  KEY_WORD_PRINT,
  KEY_WORD_ABORT,
  KEY_WORD_ELSE,
  KEY_WORD_NEW,
  KEY_WORD_RETURN,
  KEY_WORD_ABS,
  KEY_WORD_ELSIF,
  KEY_WORD_NOT,
  KEY_WORD_REVERSE,
  KEY_WORD_ABSTRACT,
  KEY_WORD_END,
  KEY_WORD_NULL,
  KEY_WORD_ACCEPT,
  KEY_WORD_ENTRY,
  KEY_WORD_SELECT,
  KEY_WORD_ACCESS,
  KEY_WORD_EXCEPTION,
  KEY_WORD_OF,
  KEY_WORD_SEPARATE,
  KEY_WORD_ALIASED,
  KEY_WORD_EXIT,
  KEY_WORD_OR,
  KEY_WORD_SOME,
  KEY_WORD_ALL,
  KEY_WORD_OTHERS,
  KEY_WORD_SUBTYPE,
  KEY_WORD_AND,
  KEY_WORD_FOR,
  KEY_WORD_OUT,
  KEY_WORD_SYNCHRONIZED,
  KEY_WORD_ARRAY,
  KEY_WORD_FUNCTION,
  KEY_WORD_OVERRIDING,
  KEY_WORD_AT,
  KEY_WORD_TAGGED,
  KEY_WORD_GENERIC,
  KEY_WORD_PACKAGE,
  KEY_WORD_TASK,
  KEY_WORD_BEGIN,
  KEY_WORD_GOTO,
  KEY_WORD_PRAGMA,
  KEY_WORD_TERMINATE,
  KEY_WORD_BODY,
  KEY_WORD_PRIVATE,
  KEY_WORD_THEN,
  KEY_WORD_IF,
  KEY_WORD_PROCEDURE,
  KEY_WORD_TYPE,
  KEY_WORD_CASE,
  KEY_WORD_IN,
  KEY_WORD_PROTECTED,
  KEY_WORD_CONSTANT,
  KEY_WORD_INTERFACE,
  KEY_WORD_UNTIL,
  KEY_WORD_IS,
  KEY_WORD_RAISE,
  KEY_WORD_USE,
  KEY_WORD_DECLARE,
  KEY_WORD_RANGE,
  KEY_WORD_DELAY,
  KEY_WORD_LIMITED,
  KEY_WORD_RECORD,
  KEY_WORD_WHEN,
  KEY_WORD_DELTA,
  KEY_WORD_LOOP,
  KEY_WORD_REM,
  KEY_WORD_WHILE,
  KEY_WORD_DIGITS,
  KEY_WORD_RENAMES,
  KEY_WORD_WITH,
  KEY_WORD_DO,
  KEY_WORD_MOD,
  KEY_WORD_REQUEUE,
  KEY_WORD_XOR,
  DELIMITER_PIPE,
  DELIMITER_AND,
  DELIMITER_QUOTE,
  DELIMITER_PAR_OPENED,
  DELIMITER_PAR_CLOSED,
  DELIMITER_STAR,
  DELIMITER_PLUS,
  DELIMITER_COMMA,
  DELIMITER_DASH,
  DELIMITER_DOT,
  DELIMITER_SLASH,
  DELIMITER_PERIOD,
  DELIMITER_SEMICOLON,
  DELIMITER_LESS_THAN,
  DELIMITER_EQUAL,
  DELIMITER_GREATER_THAN,
  DELIMITER_FAT_ARROW,
  DELIMITER_DOUBLE_DOT,
  DELIMITER_DOUBLE_STAR,
  DELIMITER_ASSIGN,
  DELIMITER_DIVIDE_EQUAL,
  DELIMITER_GREATER_THAN_EQUAL,
  DELIMITER_LESS_THAN_EQUAL,
  DELIMITER_SHIFT_LEFT,
  DELIMITER_SHIFT_RIGHT,
  DELIMITER_NOT_EQUAL,
  COMMENT,
  IDENTIFIER,
  CHARACTER_LITERAL,
  STRING_LITERAL,
  BOOLEAN_TRUE_VALUE,
  BOOLEAN_FALSE_VALUE,
  INTEGER_VALUE,
  FLOAT_VALUE
} _token_type;

extern int yylex();

extern char *yytext;

extern int yylineno;

void _read_token();

bool _proc(_cfg_list_inst *pastCfg);

bool _list_decl();

bool _decl();

bool _decl_aux();

bool _decl_aux_aux();

bool _list_decl_aux();

bool _type();

bool _const();

bool _list_inst(_cfg_list_inst *pastCfg);

bool _list_inst_aux(_cfg_list_inst *pastCfg);

bool _if_statement(_cfg_list_inst *pastCfg);

bool _elsif_statement(_cfg_if_statement *pastIfStatements);

bool _endif_statement(_cfg_if_statement *pastIfStatements);

bool _expression(_ast *_past);

bool _expression_aux(_ast *_past);

bool _relation(_ast *_past);

bool _relation_aux(_ast *_past);

bool _simple_expression(_ast *_past);

bool _simple_expression_aux(_ast *_past);

bool _term(_ast *_past);

bool _term_aux(_ast *_past);

bool _factor(_ast *_past);

bool _primary(_ast *_past);

bool _case_statement(_cfg_list_inst *pastCfg);

bool _case_statement_aux(_cfg_list_inst *pastCfg);

bool _case_statement_alternative(_cfg_list_inst *pastCfg);

bool _choice_list(_cfg_list_inst *pastCfg);

bool _choice_list_aux(_cfg_list_inst *pastCfg);

bool _choice(_cfg_list_inst *pastCfg);

bool _identified_statement(_cfg_list_inst *pastCfg);

bool _identified_statement_aux(_cfg_list_inst *pastCfg);

bool _sample_inst(_cfg_list_inst *pastCfg);

bool _identified_loop_statement(_cfg_list_inst *pastCfg);

bool _loop_statement(_cfg_list_inst *pastCfg);

bool _loop_statement_aux(_cfg_list_inst *pastCfg);

bool _loop_statement_aux_aux(_cfg_list_inst *pastCfg);

#endif