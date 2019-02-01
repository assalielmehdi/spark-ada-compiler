/**
 * Author: El Mehdi ASSALI
 */

#ifndef CFG_H
#define CFG_H

#include "ast.h"

struct _cfg_inst_node;
typedef struct _cfg_inst_node *_cfg_list_inst;

typedef enum {
  CFG_INST_ASSIGN,
  CFG_INST_IF,
  CFG_INST_WHILE
} _cfg_inst_type;

typedef enum {
  CFG_IF_BLOC,
  CFG_ELSE_IF_BLOC,
  CFG_ELSE_BLOC
} _cfg_if_bloc_type;

typedef struct _cfg_if_bloc {
  _cfg_if_bloc_type type;
  _ast condition;
  _cfg_list_inst body;
  struct _cfg_if_bloc *next;
} _cfg_if_bloc;

typedef _cfg_if_bloc *_cfg_if_statement;

typedef union {
  struct {
    char *name;
    _ast value;
  } assign_statement;
  _cfg_if_statement if_statement;
  struct {
    _ast condition;
    _cfg_list_inst body;
  } while_statement;
} _cfg_inst_body;

typedef struct {
  _cfg_inst_type type;
  _cfg_inst_body body;
} _cfg_inst;

typedef struct _cfg_inst_node {
  _cfg_inst instruction;
  struct _cfg_inst_node *next;
} _cfg_inst_node;

_cfg_list_inst _cfg_init();

_cfg_list_inst _cfg_add_assign_inst(_cfg_list_inst list_inst, char *name, _ast value);

_cfg_list_inst _cfg_add_if_inst(_cfg_list_inst list_inst, _cfg_if_statement if_statement);

_cfg_if_statement _cfg_if_statement_init();

_cfg_if_statement _cfg_add_if_statement(_cfg_if_statement if_statement, _ast condition, _cfg_list_inst body);

_cfg_if_statement _cfg_add_else_if_statement(_cfg_if_statement if_statement, _ast condition, _cfg_list_inst body);

_cfg_if_statement _cfg_add_else_statement(_cfg_if_statement if_statement, _cfg_list_inst body);

_cfg_list_inst _cfg_add_while_inst(_cfg_list_inst list_inst, _ast condition, _cfg_list_inst body);

void _cfg_print_list_inst(_cfg_list_inst list_inst, int indent);

#endif