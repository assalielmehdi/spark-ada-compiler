#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdbool.h>

typedef struct {
  char *name;
  double value;
} _interpreter_variable;


typedef struct _interpreter_data_node {
  _interpreter_variable variable;
  struct _interpreter_data_node *next;
} _interpreter_data_node;

typedef _interpreter_data_node *_interpreter_data;

extern int yylex();

extern char *yytext;

extern int yylineno;

void _interpreter_read_token();

_interpreter_data _interpreter_data_init();

_interpreter_data _interpreter_add_variable(_interpreter_data data, char *name, double value);

_interpreter_variable _interpreter_get_variable(_interpreter_data data, char *name);

bool _interpreter_pseudo_code();

bool _interpreter_list_decl();

bool _interpreter_list_decl_aux();

bool _interpreter_list_inst();

bool _interpreter_list_inst_aux();

bool _interpreter_inst();

bool _interpreter_jump_label();

#endif