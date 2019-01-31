#include <stdio.h>
#include <stdlib.h>
#include "pseudo_code.h"

_pc_code *_pc_init() {
  _pc_code *pc_code = (_pc_code *) malloc(sizeof(_pc_code));
  pc_code->first = pc_code->last = NULL;
  return pc_code;
}

void _pc_add_instruction(_pc_code *pc_code, _pc_instruction_code code, _pc_instruction_param param) {
  _pc_node *node = (_pc_node *) malloc(sizeof(_pc_node));
  node->instruction.code = code;
  node->instruction.param = param;
  if (pc_code->first == NULL) {
    pc_code->first = pc_code->last = node;
  } else {
    pc_code->last->next = node;
    pc_code->last = node;
  }
}

void _pc_print_instruction(_pc_instruction instruction) {
  // TODO:
  printf("Instruction\n");
}

void _pc_print_code(_pc_code pc_code) {
  _pc_node *cur = pc_code.first;
  while (cur != NULL) {
    _pc_print_instruction(cur->instruction);
    cur = cur->next;
  }
}