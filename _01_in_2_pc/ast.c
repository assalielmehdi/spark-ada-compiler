/**
 * Author: El Mehdi ASSALI
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

_ast _ast_create_constant_node(_constant_type type, double value) {
  _ast node = (_ast) malloc(sizeof(_node));
  node->type = NODE_CONSTANT;
  node->value.constant.type = type;
  node->value.constant.value = value;
  return node;
}

_ast _ast_create_variable_node(char *name) {
  _ast node = (_ast) malloc(sizeof(_node));
  node->type = NODE_VARIABLE;
  node->value.variable.name = (char *) malloc((strlen(name) + 1) * sizeof(char));
  strcpy(node->value.variable.name, name);
  return node;
}

_ast _ast_create_operation_node(_operation_type type, _ast left, _ast right) {
  _ast node = (_ast) malloc(sizeof(_node));
  node->type = NODE_OPERATION;
  node->value.operation.type = type;
  node->value.operation.left = left;
  node->value.operation.right = right;
  return node;
}

void _ast_print_operation(_operation_type type) {
  switch (type) {
    case OPERATION_DIV:
      printf("/ ");
      break;
    case OPERATION_EQUAL:
      printf("= ");
      break;
    case OPERATION_GREATER_THAN:
      printf("> ");
      break;
    case OPERATION_GREATER_THAN_EQUAL:
      printf(">= ");
      break;
    case OPERATION_LESS_THAN:
      printf("< ");
      break;
    case OPERATION_LESS_THAN_EQUAL:
      printf("<= ");
      break;
    case OPERATION_MINUS:
      printf("- ");
      break;
    case OPERATION_MULT:
      printf("* ");
      break;
    case OPERATION_NOT_EQUAL:
      printf("/= ");
      break;
    case OPERATION_PLUS:
      printf("+ ");
      break;
    case OPERATION_MOD:
      printf("%% ");
      break;
    case OPERATION_AND:
      printf("and ");
      break;
    case OPERATION_OR:
      printf("or ");
      break;
  }
}

void _ast_print_infix(_ast root) {
  if (root != NULL) {
    if (root->type == NODE_CONSTANT) {
      printf("%lf ", root->value.constant.value);
    } else if (root->type == NODE_VARIABLE) {
      printf("%s ", root->value.variable.name);
    } else {
      _ast_print_infix(root->value.operation.left);
      _ast_print_operation(root->value.operation.type);
      _ast_print_infix(root->value.operation.right);
    }
  }
}

void _ast_print_postfix(_ast root) {
  if (root != NULL) {
    if (root->type == NODE_CONSTANT) {
      printf("%lf ", root->value.constant.value);
    } else if (root->type == NODE_VARIABLE) {
      printf("%s ", root->value.variable.name);
    } else {
      _ast_print_postfix(root->value.operation.left);
      _ast_print_postfix(root->value.operation.right);
      _ast_print_operation(root->value.operation.type);
    }
  }
}