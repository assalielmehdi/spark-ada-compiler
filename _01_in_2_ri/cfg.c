/**
 * Author: El Mehdi ASSALI
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cfg.h"

_cfg_list_inst _cfg_init() {
  return NULL;
}

_cfg_list_inst _cfg_add_assign_inst(_cfg_list_inst list_inst, char *name, _ast value) {
  _cfg_inst_node *node = (_cfg_inst_node *) malloc(sizeof(_cfg_inst_node));
  node->instruction.type = CFG_INST_ASSIGN;
  node->instruction.body.assign_statement.name = (char *) malloc((1 + strlen(name)) * sizeof(char));
  strcpy(node->instruction.body.assign_statement.name, name);
  node->instruction.body.assign_statement.value = value;
  node->next = NULL;
  if (list_inst == NULL) {
    list_inst = node;
  } else {
    _cfg_inst_node *cur = list_inst;
    while (cur->next != NULL) {
      cur = cur->next;
    }
    cur->next = node;
  }
  return list_inst;
}

_cfg_list_inst _cfg_add_if_inst(_cfg_list_inst list_inst, _cfg_if_statement if_statement) {
  _cfg_inst_node *node = (_cfg_inst_node *) malloc(sizeof(_cfg_inst_node));
  node->instruction.type = CFG_INST_IF;
  node->instruction.body.if_statement = if_statement;
  node->next = NULL;
  if (list_inst == NULL) {
    list_inst = node;
  } else {
    _cfg_inst_node *cur = list_inst;
    while (cur->next != NULL) {
      cur = cur->next;
    }
    cur->next = node;
  }
  return list_inst;
}

_cfg_if_statement _cfg_if_statement_init() {
  return NULL;
}

_cfg_if_statement _cfg_add_if_statement(_cfg_if_statement if_statement, _ast condition, _cfg_list_inst body) {
  _cfg_if_bloc *node = (_cfg_if_bloc *) malloc(sizeof(_cfg_if_bloc));
  node->type = CFG_IF_BLOC;
  node->condition = condition;
  node->body = body;
  node->next = NULL;
  if (if_statement == NULL) {
    if_statement = node;
  } else {
    _cfg_if_bloc *cur = if_statement;
    while (cur->next != NULL) {
      cur = cur->next;
    }
    cur->next = node;
  }
  return if_statement;
}

_cfg_if_statement _cfg_add_else_if_statement(_cfg_if_statement if_statement, _ast condition, _cfg_list_inst body) {
  _cfg_if_bloc *node = (_cfg_if_bloc *) malloc(sizeof(_cfg_if_bloc));
  node->type = CFG_ELSE_IF_BLOC;
  node->condition = condition;
  node->body = body;
  node->next = NULL;
  if (if_statement == NULL) {
    if_statement = node;
  } else {
    _cfg_if_bloc *cur = if_statement;
    while (cur->next != NULL) {
      cur = cur->next;
    }
    cur->next = node;
  }
  return if_statement;
}

_cfg_if_statement _cfg_add_else_statement(_cfg_if_statement if_statement, _cfg_list_inst body) {
  _cfg_if_bloc *node = (_cfg_if_bloc *) malloc(sizeof(_cfg_if_bloc));
  node->type = CFG_ELSE_BLOC;
  node->condition = NULL;
  node->body = body;
  node->next = NULL;
  if (if_statement == NULL) {
    if_statement = node;
  } else {
    _cfg_if_bloc *cur = if_statement;
    while (cur->next != NULL) {
      cur = cur->next;
    }
    cur->next = node;
  }
  return if_statement;
}

_cfg_list_inst _cfg_add_while_inst(_cfg_list_inst list_inst, _ast condition, _cfg_list_inst body) {
  _cfg_inst_node *node = (_cfg_inst_node *) malloc(sizeof(_cfg_inst_node));
  node->instruction.type = CFG_INST_WHILE;
  node->instruction.body.while_statement.condition = condition;
  node->instruction.body.while_statement.body = body;
  node->next = NULL;
  if (list_inst == NULL) {
    list_inst = node;
  } else {
    _cfg_inst_node *cur = list_inst;
    while (cur->next != NULL) {
      cur = cur->next;
    }
    cur->next = node;
  }
  return list_inst;
}

void _cfg_print_indent(int indent) {
  if (indent > 0) {
    printf(" ");
    _cfg_print_indent(indent - 1);
  }
}

void _cfg_print_list_inst(_cfg_list_inst list_inst, int indent) {
  _cfg_inst_node *cur = list_inst;
  while (cur != NULL) {
    _cfg_print_indent(indent);
    _cfg_if_bloc *curIf;
    switch (cur->instruction.type) {
      case CFG_INST_ASSIGN:
        printf("Assign: %s := ", cur->instruction.body.assign_statement.name);
        _ast_print_infix(cur->instruction.body.assign_statement.value);
        printf("\n");
        break;
      case CFG_INST_IF:
        curIf = cur->instruction.body.if_statement;
        while (curIf != NULL) {
          if (curIf != cur->instruction.body.if_statement) {
            _cfg_print_indent(indent);
          }
          switch (curIf->type) {
            case CFG_IF_BLOC:
              printf("If: ");
              _ast_print_infix(curIf->condition);
              printf("\n");
              _cfg_print_list_inst(curIf->body, indent + 2);
              break;
            case CFG_ELSE_IF_BLOC:
              printf("Else If: ");
              _ast_print_infix(curIf->condition);
              printf("\n");
              _cfg_print_list_inst(curIf->body, indent + 2);
              break;
            case CFG_ELSE_BLOC:
              printf("Else: \n");
              _cfg_print_list_inst(curIf->body, indent + 2);
              break;
          }
          curIf = curIf->next;
        }
        break;
      case CFG_INST_WHILE:
        printf("While: ");
        _ast_print_infix(cur->instruction.body.while_statement.condition);
        printf("\n");
        _cfg_print_list_inst(cur->instruction.body.while_statement.body, indent + 2);
        break;
    }
    cur = cur->next;
  }
}