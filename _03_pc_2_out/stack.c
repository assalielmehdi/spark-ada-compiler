#include <stdlib.h>
#include "stack.h"

_stack _stack_init() {
  return NULL;
}

_stack _stack_push(_stack stack, _stack_node_type type, _stack_node_value value) {
  _stack_node *node = (_stack_node *) malloc(sizeof(_stack_node));
  node->element.type = type;
  node->element.value = value;
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