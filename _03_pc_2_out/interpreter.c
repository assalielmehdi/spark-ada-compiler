/**
 * Author: El Mehdi ASSALI
 */

#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"
#include "stack.h"

#define DEBUG_MODE false

_stack _data_stack;

void _interpreter_process(_pc_code pseudo_code, _pc_parser_data data, _pc_parser_labels labels) {
  _data_stack = _stack_init();
  _pc_node *currentInstruction = pseudo_code.first;
  _pc_parser_variable variable;
  _stack_node_element element1, element2;
  _pc_parser_label label;
  double value;
  while (currentInstruction != NULL) {
    switch (currentInstruction->instruction.code) {
      case INSTRUCTION_LOAD:
        if (DEBUG_MODE == true) printf("LOAD: ");
        variable = _pc_parser_get_variable(data, currentInstruction->instruction.param.variable);
        _data_stack = _stack_push_number(_data_stack, variable.value);
        currentInstruction = currentInstruction->next;
        break;
      case INSTRUCTION_PUSH:
        if (DEBUG_MODE == true) printf("PUSH: ");
        _data_stack = _stack_push_number(_data_stack, currentInstruction->instruction.param.constant);
        currentInstruction = currentInstruction->next;
        break;
      case INSTRUCTION_STORE:
        if (DEBUG_MODE == true) printf("STORE: ");
        variable = _pc_parser_get_variable(data, currentInstruction->instruction.param.variable);
        element1 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        data = _pc_parser_update_variable(data, variable.name, element1.value.number);
        currentInstruction = currentInstruction->next;
        break;
      case INSTRUCTION_ADD:
        if (DEBUG_MODE == true) printf("ADD: ");
        element2 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        element1 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        value = element1.value.number + element2.value.number;
        _data_stack = _stack_push_number(_data_stack, value);
        currentInstruction = currentInstruction->next;
        break;
      case INSTRUCTION_SUB:
        if (DEBUG_MODE == true) printf("SUB: ");
        element2 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        element1 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        value = element1.value.number - element2.value.number;
        _data_stack = _stack_push_number(_data_stack, value);
        currentInstruction = currentInstruction->next;
        break;
      case INSTRUCTION_MULT:
        if (DEBUG_MODE == true) printf("MULT: ");
        element2 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        element1 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        value = element1.value.number * element2.value.number;
        _data_stack = _stack_push_number(_data_stack, value);
        currentInstruction = currentInstruction->next;
        break;
      case INSTRUCTION_DIV:
        if (DEBUG_MODE == true) printf("DIV: ");
        element2 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        element1 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        value = element1.value.number / element2.value.number;
        _data_stack = _stack_push_number(_data_stack, value);
        currentInstruction = currentInstruction->next;
        break;
      case INSTRUCTION_MOD:
        if (DEBUG_MODE == true) printf("MOD: ");
        element2 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        element1 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        value = (int) element1.value.number % (int) element2.value.number;
        _data_stack = _stack_push_number(_data_stack, value);
        currentInstruction = currentInstruction->next;
        break;
      case INSTRUCTION_JMP:
        if (DEBUG_MODE == true) printf("JMP: ");
        label = _pc_parser_get_label(labels, currentInstruction->instruction.param.label);
        currentInstruction = label.instruction;
        break;
      case INSTRUCTION_JT:
        if (DEBUG_MODE == true) printf("JT: ");
        label = _pc_parser_get_label(labels, currentInstruction->instruction.param.label);
        element1 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        if (element1.value.number == 1.0) {
          currentInstruction = label.instruction;
        } else {
          currentInstruction = currentInstruction->next;
        }
        break;
      case INSTRUCTION_JF:
        if (DEBUG_MODE == true) printf("JF: ");
        label = _pc_parser_get_label(labels, currentInstruction->instruction.param.label);
        element1 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        if (element1.value.number == 0.0) {
          currentInstruction = label.instruction;
        } else {
          currentInstruction = currentInstruction->next;
        }
        break;
      case INSTRUCTION_EVAL_G:
        if (DEBUG_MODE == true) printf("EVAL_G: ");
        element2 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        element1 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        value = element1.value.number > element2.value.number ? 1 : 0;
        _data_stack = _stack_push_number(_data_stack, value);
        currentInstruction = currentInstruction->next;
        break;
      case INSTRUCTION_EVAL_GE:
        if (DEBUG_MODE == true) printf("EVAL_GE: ");
        element2 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        element1 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        value = element1.value.number >= element2.value.number ? 1 : 0;
        _data_stack = _stack_push_number(_data_stack, value);
        currentInstruction = currentInstruction->next;
        break;
      case INSTRUCTION_EVAL_L:
        if (DEBUG_MODE == true) printf("EVAL_L: ");
        element2 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        element1 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        value = element1.value.number < element2.value.number ? 1 : 0;
        _data_stack = _stack_push_number(_data_stack, value);
        currentInstruction = currentInstruction->next;
        break;
      case INSTRUCTION_EVAL_LE:
        if (DEBUG_MODE == true) printf("EVAL_LE: ");
        element2 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        element1 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        value = element1.value.number <= element2.value.number ? 1 : 0;
        _data_stack = _stack_push_number(_data_stack, value);
        currentInstruction = currentInstruction->next;
        break;
      case INSTRUCTION_EVAL_E:
        if (DEBUG_MODE == true) printf("EVAL_E: ");
        element2 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        element1 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        value = element1.value.number == element2.value.number ? 1 : 0;
        _data_stack = _stack_push_number(_data_stack, value);
        currentInstruction = currentInstruction->next;
        break;
      case INSTRUCTION_EVAL_NE:
        if (DEBUG_MODE == true) printf("EVAL_NE: ");
        element2 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        element1 = _stack_peek(_data_stack);
        _data_stack = _stack_pop(_data_stack);
        value = element1.value.number != element2.value.number ? 1 : 0;
        _data_stack = _stack_push_number(_data_stack, value);
        currentInstruction = currentInstruction->next;
        break;
      case INSTRUCTION_PRINT_NUMBER:
        if (DEBUG_MODE == true) printf("PRINT_NUMBER: ");
        element1 = _stack_peek(_data_stack);
        printf("%.2lf\n", element1.value.number);
        _data_stack = _stack_pop(_data_stack);
        currentInstruction = currentInstruction->next;
        break;
    }
    if (DEBUG_MODE == true) {
      _stack_print(_data_stack);
      printf("\n");
    }
  }
}