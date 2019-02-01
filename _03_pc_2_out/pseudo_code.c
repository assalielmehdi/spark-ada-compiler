#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pseudo_code.h"

_pc_code *_pc_init() {
  _pc_code *pc_code = (_pc_code *) malloc(sizeof(_pc_code));
  pc_code->first = pc_code->last = NULL;
  return pc_code;
}

void _pc_add_variable_instruction(_pc_code *pc_code, _pc_instruction_code code, char *name) {
  _pc_node *node = (_pc_node *) malloc(sizeof(_pc_node));
  node->instruction.code = code;
  node->instruction.param.variable = (char *) malloc((1 + strlen(name) * sizeof(char)));
  strcpy(node->instruction.param.variable, name);
  if (pc_code->first == NULL) {
    pc_code->first = pc_code->last = node;
  } else {
    pc_code->last->next = node;
    pc_code->last = node;
  }
}

void _pc_add_labeled_instruction(_pc_code *pc_code, _pc_instruction_code code, char *label) {
  _pc_node *node = (_pc_node *) malloc(sizeof(_pc_node));
  node->instruction.code = code;
  node->instruction.param.label = (char *) malloc((1 + strlen(label) * sizeof(char)));
  strcpy(node->instruction.param.label, label);
  if (pc_code->first == NULL) {
    pc_code->first = pc_code->last = node;
  } else {
    pc_code->last->next = node;
    pc_code->last = node;
  }
}

void _pc_add_constant_instruction(_pc_code *pc_code, _pc_instruction_code code, double constant) {
  _pc_node *node = (_pc_node *) malloc(sizeof(_pc_node));
  node->instruction.code = code;
  node->instruction.param.constant = constant;
  if (pc_code->first == NULL) {
    pc_code->first = pc_code->last = node;
  } else {
    pc_code->last->next = node;
    pc_code->last = node;
  }
}

void _pc_print_instruction(_pc_instruction instruction) {
  switch (instruction.code) {
    case INSTRUCTION_LOAD:
      printf("LOAD\n");
      break;
    case INSTRUCTION_PUSH:
      printf("PUSH\n");
      break;
    case INSTRUCTION_STORE:
      printf("STORE\n");
      break;
    case INSTRUCTION_ADD:
      printf("ADD\n");
      break;
    case INSTRUCTION_SUB:
      printf("SUB\n");
      break;
    case INSTRUCTION_MULT:
      printf("MULT\n");
      break;
    case INSTRUCTION_DIV:
      printf("DIV\n");
      break;
    case INSTRUCTION_MOD:
      printf("MOD\n");
      break;
    case INSTRUCTION_JMP:
      printf("JMP\n");
      break;
    case INSTRUCTION_JT:
      printf("JT\n");
      break;
    case INSTRUCTION_JF:
      printf("JF\n");
      break;
    case INSTRUCTION_EVAL_G:
      printf("EVAL_G\n");
      break;
    case INSTRUCTION_EVAL_GE:
      printf("EVAL_GE\n");
      break;
    case INSTRUCTION_EVAL_L:
      printf("EVAL_L\n");
      break;
    case INSTRUCTION_EVAL_LE:
      printf("EVAL_LE\n");
      break;
      case INSTRUCTION_EVAL_E:
      printf("EVAL_E\n");
      break;
    case INSTRUCTION_EVAL_NE:
      printf("EVAL_NE\n");
      break;
    case INSTRUCTION_PRINT_NUMBER:
      printf("PRINT_NUMBER\n");
      break;
  }
}

void _pc_print_code(_pc_code pc_code) {
  _pc_node *cur = pc_code.first;
  while (cur != NULL) {
    _pc_print_instruction(cur->instruction);
    cur = cur->next;
  }
}