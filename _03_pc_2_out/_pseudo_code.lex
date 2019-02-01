%option noyywrap
%option caseless
%option yylineno

%{
#include "pseudo_code.h"
%}

INTEGER [+-]?[0-9]+
NUMBER {INTEGER}("."{INTEGER})?

%%

[\n\t ]+
"DATA" return PC_KEY_WORD_DATA;
"LOAD" return PC_KEY_WORD_LOAD;
"PUSH" return PC_KEY_WORD_PUSH;
"STORE" return PC_KEY_WORD_STORE;
"ADD" return PC_KEY_WORD_ADD;
"SUB" return PC_KEY_WORD_SUB;
"MULT" return PC_KEY_WORD_MULT;
"DIV" return PC_KEY_WORD_DIV;
"MOD" return PC_KEY_WORD_MOD;
"JMP" return PC_KEY_WORD_JMP;
"JT" return PC_KEY_WORD_JT;
"JF" return PC_KEY_WORD_JF;
"EVAL_G" return PC_KEY_WORD_EVAL_G;
"EVAL_GE" return PC_KEY_WORD_EVAL_GE;
"EVAL_L" return PC_KEY_WORD_EVAL_L;
"EVAL_LE" return PC_KEY_WORD_EVAL_LE;
"EVAL_E" return PC_KEY_WORD_EVAL_E;
"EVAL_NE" return PC_KEY_WORD_EVAL_E;
"PRINT_NUMBER" return PC_KEY_WORD_PRINT_NUMBER;
"begin:" return PC_KEY_WORD_BEGIN;
"end:" return PC_KEY_WORD_END;
"begin_"{INTEGER}":" return PC_LABEL_BEGIN;
"end_"{INTEGER}":" return PC_LABEL_END;
[A-Za-z_][A-Za-z0-9_]* return PC_IDENTIFIER;
{NUMBER} return PC_NUMBER;
. printf("ERRORLEX(%s)", yytext);

%%
