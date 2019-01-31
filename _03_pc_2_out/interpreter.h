#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdbool.h>

extern int yylex();

extern char *yytext;

extern int yylineno;

void _interpreter_read_token();

bool _interpreter_pseudo_code();

bool _interpreter_list_decl();

bool _interpreter_list_decl_aux();

bool _interpreter_list_inst();

bool _interpreter_list_inst_aux();

bool _interpreter_inst();

bool _interpreter_jump_label();

#endif