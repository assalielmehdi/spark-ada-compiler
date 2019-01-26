#ifndef AST_H
#define AST_H

typedef struct _node _node;
typedef _node *_ast;

typedef enum {
  NODE_CONSTANT,
  NODE_VARIABLE,
  NODE_OPERATION
} _node_type;

typedef enum {
  OPERATION_PLUS,
  OPERATION_MINUS,
  OPERATION_DIV,
  OPERATION_MULT
} _operation_type;

typedef struct {
  _operation_type type;
  _ast left;
  _ast right;
} _operation;

typedef enum {
  NODE_CONSTANT_INT,
  NODE_CONSTANT_DOUBLE,
  NODE_CONSTANT_BOOL
} _constant_type;

typedef struct {
  _constant_type type;
  double value;
} _constant;

typedef struct {
  char *name;
} _variable;

typedef union {
  _constant constant;
  _variable variable;
  _operation operation;
} _node_value;

struct _node {
  _node_type type;
  _node_value value;
};

_ast _ast_create_constant_node(_constant_type type, double value);

_ast _ast_create_variable_node(char *name);

_ast _ast_create_operation_node(_operation_type type, _ast left, _ast right);

#endif
