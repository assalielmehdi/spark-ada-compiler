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