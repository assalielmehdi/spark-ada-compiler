/**
 * Author: El Mehdi ASSALI
 */

#ifndef PC_PARSER_H
#define PC_PARSER_H

#include <stdbool.h>
#include "pseudo_code.h"

typedef struct {
  char *name;
  double value;
} _pc_parser_variable;

typedef struct _pc_parser_data_node {
  _pc_parser_variable variable;
  struct _pc_parser_data_node *next;
} _pc_parser_data_node;

typedef _pc_parser_data_node *_pc_parser_data;

typedef struct {
  char *label;
  _pc_node *instruction;
} _pc_parser_label;

typedef struct _pc_parser_label_node {
  _pc_parser_label label;
  struct _pc_parser_label_node *next;
} _pc_parser_label_node;

typedef _pc_parser_label_node *_pc_parser_labels;

extern int yylex();

extern char *yytext;

extern int yylineno;

void _pc_parser_read_token();

_pc_parser_data _pc_parser_data_init();

_pc_parser_data _pc_parser_add_variable(_pc_parser_data data, char *name, double value);

_pc_parser_variable _pc_parser_get_variable(_pc_parser_data data, char *name);

_pc_parser_data _pc_parser_update_variable(_pc_parser_data data, char *name, double value);

void _pc_parser_print_data(_pc_parser_data data);

_pc_parser_labels _pc_parser_labels_init();

_pc_parser_labels _pc_parser_add_label(_pc_parser_labels labels, char *label, _pc_node *instruction);

_pc_parser_labels _pc_parser_add_labels(_pc_parser_labels labels, _pc_parser_labels labelsToAdd, _pc_node *instruction);

_pc_parser_label _pc_parser_get_label(_pc_parser_labels labels, char *label);

_pc_parser_labels _pc_paser_clear_labels(_pc_parser_labels labels);

void _pc_parser_print_labels(_pc_parser_labels labels);

bool _pc_parser_pseudo_code();

bool _pc_parser_list_decl();

bool _pc_parser_list_decl_aux();

bool _pc_parser_list_inst();

bool _pc_parser_list_inst_aux();

bool _pc_parser_inst();

bool _pc_parser_jump_label();

#endif