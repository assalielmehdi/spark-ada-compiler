/**
 * Author: El Mehdi ASSALI
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

_stack _stack_init() {
  return NULL;
}

_stack _stack_push_number(_stack stack, double value) {
  _stack_node *node = (_stack_node *) malloc(sizeof(_stack_node));
  node->element.type = STACK_NODE_NUMBER;
  node->element.value.number = value;
  node->next = stack;
  return node;
}

_stack _stack_push_string(_stack stack, char *value) {
  _stack_node *node = (_stack_node *) malloc(sizeof(_stack_node));
  node->element.type = STACK_NODE_STRING;
  node->element.value.string = (char *) malloc((1 + strlen(value)) * sizeof(char));
  strcpy(node->element.value.string, value);
  node->next = stack;
  return node;
}

_stack _stack_pop(_stack stack) {
  _stack_node *toFree = stack;
  stack = stack->next;
  free(toFree);
  return stack;
}

_stack_node_element _stack_peek(_stack stack) {
  return stack->element;
}

void _stack_print(_stack stack) {
  if (stack != NULL) {
    _stack_print(stack->next);
    if (stack->element.type == STACK_NODE_NUMBER) {
      printf("%.2lf ", stack->element.value.number);
    } else if (stack->element.type == STACK_NODE_STRING) {
      printf("%s ", stack->element.value.string);
    }
  }
}