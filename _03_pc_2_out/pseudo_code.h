/**
 * Author: El Mehdi ASSALI
 */

#ifndef PSEUDO_CODE_H
#define PSEUDO_CODE_H

typedef enum {
  PC_KEY_WORD_DATA,
  PC_KEY_WORD_LOAD,
  PC_KEY_WORD_PUSH,
  PC_KEY_WORD_STORE,
  PC_KEY_WORD_ADD,
  PC_KEY_WORD_SUB,
  PC_KEY_WORD_MULT,
  PC_KEY_WORD_DIV,
  PC_KEY_WORD_MOD,
  PC_KEY_WORD_JMP,
  PC_KEY_WORD_JT,
  PC_KEY_WORD_JF,
  PC_KEY_WORD_EVAL_G,
  PC_KEY_WORD_EVAL_GE,
  PC_KEY_WORD_EVAL_L,
  PC_KEY_WORD_EVAL_LE,
  PC_KEY_WORD_EVAL_E,
  PC_KEY_WORD_EVAL_NE,
  PC_KEY_WORD_BEGIN,
  PC_KEY_WORD_END,
  PC_LABEL_BEGIN,
  PC_LABEL_END,
  PC_IDENTIFIER,
  PC_NUMBER,
  PC_KEY_WORD_PRINT_NUMBER
} _pc_token_type;

typedef enum {
  INSTRUCTION_LOAD,
  INSTRUCTION_PUSH,
  INSTRUCTION_STORE,
  INSTRUCTION_ADD,
  INSTRUCTION_SUB,
  INSTRUCTION_MULT,
  INSTRUCTION_DIV,
  INSTRUCTION_MOD,
  INSTRUCTION_JMP,
  INSTRUCTION_JT,
  INSTRUCTION_JF,
  INSTRUCTION_EVAL_G,
  INSTRUCTION_EVAL_GE,
  INSTRUCTION_EVAL_L,
  INSTRUCTION_EVAL_LE,
  INSTRUCTION_EVAL_E,
  INSTRUCTION_EVAL_NE,
  INSTRUCTION_PRINT_NUMBER
} _pc_instruction_code;

typedef union {
  char *label;
  char *variable;
  double constant;
} _pc_instruction_param;

typedef struct {
  _pc_instruction_code code;
  _pc_instruction_param param;
} _pc_instruction;

typedef struct _pc_node {
  _pc_instruction instruction;
  struct _pc_node *next;
} _pc_node;

typedef struct {
  _pc_node *first;
  _pc_node *last;
} _pc_code;

_pc_code *_pc_init();

void _pc_add_variable_instruction(_pc_code *pc_code, _pc_instruction_code code, char *name);

void _pc_add_labeled_instruction(_pc_code *pc_code, _pc_instruction_code code, char *label);

void _pc_add_constant_instruction(_pc_code *pc_code, _pc_instruction_code code, double constant);

void _pc_print_code(_pc_code pc_code);

#endif