#include <stdio.h>
#include <stdlib.h>
#include "pseudo_code_generator.h"
#include "tab_symb.h"

int labelIdx = 0;

void _pc_generator_ast_to_pc(_ast root) {
  if (root != NULL) {
    if (root->type == NODE_CONSTANT) {
      printf("PUSH %.2lf\n", root->value.constant.value);
    } else if (root->type == NODE_VARIABLE) {
      printf("LOAD %s\n", root->value.variable.name);
    } else {
      _pc_generator_ast_to_pc(root->value.operation.left);
      _pc_generator_ast_to_pc(root->value.operation.right);
      switch (root->value.operation.type) {
        case OPERATION_DIV:
          printf("DIV\n");
          break;
        case OPERATION_EQUAL:
          printf("EVAL_E\n");
          break;
        case OPERATION_GREATER_THAN:
          printf("EVAL_G\n");
          break;
        case OPERATION_GREATER_THAN_EQUAL:
          printf("EVAL_GE\n");
          break;
        case OPERATION_LESS_THAN:
          printf("EVAL_L\n");
          break;
        case OPERATION_LESS_THAN_EQUAL:
          printf("EVAL_LE\n");
          break;
        case OPERATION_MINUS:
          printf("SUB\n");
          break;
        case OPERATION_MULT:
          printf("MULT\n");
          break;
        case OPERATION_NOT_EQUAL:
          printf("EVAL_NE\n");
          break;
        case OPERATION_PLUS:
          printf("ADD\n");
          break;
      }
    }
  }
}

void _pc_generator_cfg_to_pc(_cfg_list_inst list_inst) {
  _cfg_inst_node *cur = list_inst;
  int firstTime = labelIdx++;
  if (firstTime == 0) {
    _tab_sym_to_pc();
    printf("begin:\n");
  }
  int idx;
  while (cur != NULL) {
    switch (cur->instruction.type) {
      case CFG_INST_ASSIGN:
        _pc_generator_ast_to_pc(cur->instruction.body.assign_statement.value);
        printf("STORE %s\n",cur->instruction.body.assign_statement.name);
        break;
      case CFG_INST_IF:
        break;
      case CFG_INST_WHILE:
        idx = labelIdx++;
        printf("begin_%d:\n", idx);
        _pc_generator_ast_to_pc(cur->instruction.body.while_statement.condition);
        printf("JF end_%d:\n", idx);
        _pc_generator_cfg_to_pc(cur->instruction.body.while_statement.body);
        printf("JMP begin_%d:\n", idx);
        printf("end_%d:\n", idx);
        break;
      case CFG_INST_PRINT:
        printf("LOAD %s\n", cur->instruction.body.var_to_print);
        printf("PRINT_NUMBER\n");
        break;
    }
    cur = cur->next;
  }
  if (firstTime == 0) {
    printf("end:\n");
  }
}