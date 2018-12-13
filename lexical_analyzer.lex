%option noyywrap
%option caseless
%option yylineno

%{
#ifndef SYNTACTICAL_ANALYZER
#include "syntactical_analyzer.h"
#endif
%}

INTEGER   ([+-]?[0-9]+)|([+-]?[0-9]{1,3}("_"[0-9]{3})*)
FLOAT {INTEGER}"."[0-9]+([Ee]{INTEGER})?
CHARACTER  [A-Za-z]

%%

[\n\t ]+
"--"[^\n]* return COMMENT;
"abort" return KEY_WORD_ABORT;
"else" return KEY_WORD_ELSE;
"new" return KEY_WORD_NEW;
"return" return KEY_WORD_RETURN;
"abs" return KEY_WORD_ABS;
"elsif" return KEY_WORD_ELSIF;
"not" return KEY_WORD_NOT;
"reverse" return KEY_WORD_REVERSE;
"abstract" return KEY_WORD_ABSTRACT;
"end" return KEY_WORD_END;
"null" return KEY_WORD_NULL;
"accept" return KEY_WORD_ACCEPT;
"entry" return KEY_WORD_ENTRY;
"select" return KEY_WORD_SELECT;
"access" return KEY_WORD_ACCESS;
"exception" return KEY_WORD_EXCEPTION;
"of" return KEY_WORD_OF;
"separate" return KEY_WORD_SEPARATE;
"aliased" return KEY_WORD_ALIASED;
"exit" return KEY_WORD_EXIT;
"or" return KEY_WORD_OR;
"some" return KEY_WORD_SOME;
"all" return KEY_WORD_ALL;
"others" return KEY_WORD_OTHERS;
"subtype" return KEY_WORD_SUBTYPE;
"and" return KEY_WORD_AND;
"for" return KEY_WORD_FOR;
"out" return KEY_WORD_OUT;
"synchronized" return KEY_WORD_SYNCHRONIZED;
"array" return KEY_WORD_ARRAY;
"function" return KEY_WORD_FUNCTION;
"overriding" return KEY_WORD_OVERRIDING;
"at" return KEY_WORD_AT;
"tagged" return KEY_WORD_TAGGED;
"generic" return KEY_WORD_GENERIC;
"package" return KEY_WORD_PACKAGE;
"task" return KEY_WORD_TASK;
"begin" return KEY_WORD_BEGIN;
"goto" return KEY_WORD_GOTO;
"pragma" return KEY_WORD_PRAGMA;
"terminate" return KEY_WORD_TERMINATE;
"body" return KEY_WORD_BODY;
"private" return KEY_WORD_PRIVATE;
"then" return KEY_WORD_THEN;
"if" return KEY_WORD_IF;
"procedure" return KEY_WORD_PROCEDURE;
"type" return KEY_WORD_TYPE;
"case" return KEY_WORD_CASE;
"in" return KEY_WORD_IN;
"protected" return KEY_WORD_PROTECTED;
"constant" return KEY_WORD_CONSTANT;
"interface" return KEY_WORD_INTERFACE;
"until" return KEY_WORD_UNTIL;
"is" return KEY_WORD_IS;
"raise" return KEY_WORD_RAISE;
"use" return KEY_WORD_USE;
"declare" return KEY_WORD_DECLARE;
"range" return KEY_WORD_RANGE;
"delay" return KEY_WORD_DELAY;
"limited" return KEY_WORD_LIMITED;
"record" return KEY_WORD_RECORD;
"when" return KEY_WORD_WHEN;
"delta" return KEY_WORD_DELTA;
"loop" return KEY_WORD_LOOP;
"rem" return KEY_WORD_REM;
"while" return KEY_WORD_WHILE;
"digits" return KEY_WORD_DIGITS;
"renames" return KEY_WORD_RENAMES;
"with" return KEY_WORD_WITH;
"do" return KEY_WORD_DO;
"mod" return KEY_WORD_MOD;
"requeue" return KEY_WORD_REQUEUE;
"xor" return KEY_WORD_XOR;
"|" return DELIMITER_PIPE;
"&" return DELIMITER_AND;
"'" return DELIMITER_QUOTE;
"(" return DELIMITER_PAR_OPENED;
")" return DELIMITER_PAR_CLOSED;
"*" return DELIMITER_STAR;
"+" return DELIMITER_PLUS;
"," return DELIMITER_COMMA;
"-" return DELIMITER_DASH;
"." return DELIMITER_DOT;
"/" return DELIMITER_SLASH;
":" return DELIMITER_PERIOD;
";" return DELIMITER_SEMICOLON;
"<" return DELIMITER_LESS_THAN;
"=" return DELIMITER_EQUAL;
">" return DELIMITER_GREATER_THAN;
"=>" return DELIMITER_FAT_ARROW;
".." return DELIMITER_DOUBLE_DOT;
"**" return DELIMITER_DOUBLE_STAR;
":=" return DELIMITER_ASSIGN;
"/=" return DELIMITER_DIVIDE_EQUAL;
">=" return DELIMITER_GREATER_THAN_EQUAL;
"<=" return DELIMITER_LESS_THAN_EQUAL;
"<<" return DELIMITER_SHIFT_LEFT;
">>" return DELIMITER_SHIFT_RIGHT;
"<>" return DELIMITER_NOT_EQUAL;
"true" return BOOLEAN_TRUE_VALUE;
"false" return BOOLEAN_FALSE_VALUE;
[A-Za-z_][A-Za-z0-9_]* return IDENTIFIER;
{INTEGER} return INTEGER_VALUE;
{FLOAT} return FLOAT_VALUE;
'{CHARACTER}'|'"%"' return CHARACTER_LITERAL;
\"({CHARACTER}*[ ]?{CHARACTER}*)*\" return STRING_LITERAL;
. printf("ERRORLEX(%s)",yytext);

%%
