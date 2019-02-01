/**
 * Author: El Mehdi ASSALI
 */

#ifndef STACK_H
#define STACK_H

typedef enum {
  STACK_NODE_NUMBER,
  STACK_NODE_STRING
} _stack_node_type;

typedef union {
  char *string;
  double number;
} _stack_node_value;

typedef struct {
  _stack_node_type type;
  _stack_node_value value;
} _stack_node_element;

typedef struct _stack_node {
  _stack_node_element element;
  struct _stack_node *next;
} _stack_node;

typedef _stack_node *_stack;

_stack _stack_init();

_stack _stack_push_number(_stack stack, double value);

_stack _stack_push_string(_stack stack, char *value);

_stack _stack_pop(_stack stack);

_stack_node_element _stack_peek(_stack stack);

void _stack_print(_stack stack);

#endif