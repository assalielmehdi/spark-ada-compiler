/**
 * Author: El Mehdi ASSALI
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pseudo_code.h"
#include "pseudo_code_parser.h"
#include "interpreter.h"

#define DEBUG_MODE false

_pc_token_type _token;

bool _follow = false;

_pc_code *_pseudo_code;

_pc_parser_data _data;

char *_variable_name;

double _variable_value;

char *_instruction_param_value;

_pc_parser_labels _allLabels;

_pc_parser_labels _currentLabels;

int main(int argc, char **argv) {
  _pseudo_code = _pc_init();
  _data = _pc_parser_data_init();
  _allLabels = _pc_parser_labels_init();
  _currentLabels = _pc_parser_labels_init();
  _pc_parser_read_token();
  if (_pc_parser_pseudo_code()) {
    _interpreter_process(*_pseudo_code, _data, _allLabels);
  }
  return EXIT_SUCCESS;
}

void _pc_parser_read_token() {
  if (_follow) {
    _follow = false;
  } else {
    _token = (_pc_token_type) yylex();
  }
}

_pc_parser_data _pc_parser_data_init() {
  return NULL;
}

_pc_parser_data _pc_parser_add_variable(_pc_parser_data data, char *name, double value) {
  _pc_parser_data_node *node = (_pc_parser_data_node *) malloc(sizeof(_pc_parser_data_node));
  node->variable.name = (char *) malloc((1 + strlen(name)) * sizeof(char));
  strcpy(node->variable.name, name);
  node->variable.value = value;
  node->next = data;
  return node;
}

_pc_parser_variable _pc_parser_get_variable(_pc_parser_data data, char *name) {
  _pc_parser_data_node *cur = data;
  while (cur != NULL) {
    if (strcmp(cur->variable.name, name) == 0) {
      break;
    }
    cur = cur->next;
  }
  return cur->variable;
}

_pc_parser_data _pc_parser_update_variable(_pc_parser_data data, char *name, double value) {
  _pc_parser_data_node *cur = data, *prev = NULL;
  while (cur != NULL && strcmp(cur->variable.name, name) != 0) {
    prev = cur;
    cur = cur->next;
  }
  if (prev == NULL) {
    data = data->next;
    free(cur);
  } else {
    prev->next = cur->next;
    free(cur);
  }
  data = _pc_parser_add_variable(data, name, value);
  return data;
}

void _pc_parser_print_data(_pc_parser_data data) {
  printf("[");
  _pc_parser_data_node *cur = data;
  while (cur != NULL) {
    if (cur != data) {
      printf(", ");
    }
    puts("{");
    printf("  name: %s,\n", cur->variable.name);
    printf("  value: %.2lf\n", cur->variable.value);
    printf("}");
    cur = cur->next;
  }
  printf("]\n");
}

_pc_parser_labels _pc_parser_labels_init() {
  return NULL;
}

_pc_parser_labels _pc_parser_add_label(_pc_parser_labels labels, char *label, _pc_node *instruction) {
  _pc_parser_label_node *node = (_pc_parser_label_node *) malloc(sizeof(_pc_parser_label_node));
  node->label.label = (char *) malloc((1 + strlen(label)) * sizeof(char));
  strcpy(node->label.label, label);
  node->label.instruction = instruction;
  node->next = labels;
  return node;
}

_pc_parser_labels _pc_parser_add_labels(_pc_parser_labels labels, _pc_parser_labels labelsToAdd, _pc_node *instruction) {
  _pc_parser_label_node *cur = labelsToAdd;
  while (cur != NULL) {
    labels = _pc_parser_add_label(labels, cur->label.label, instruction);
    cur = cur->next;
  }
  return labels;
}

_pc_parser_label _pc_parser_get_label(_pc_parser_labels labels, char *label) {
  _pc_parser_label_node *cur = labels;
  while (cur != NULL) {
    if (strcmp(cur->label.label, label) == 0) {
      break;
    }
    cur = cur->next;
  }
  return cur->label;
}

_pc_parser_labels _pc_paser_clear_labels(_pc_parser_labels labels) {
  _pc_parser_label_node *cur = labels, *prev;
  while (cur != NULL) {
    prev = cur;
    cur = cur->next;
    free(prev);
  }
  return NULL;
}

void _pc_parser_print_labels(_pc_parser_labels labels) {
  printf("[");
  _pc_parser_label_node *cur = labels;
  while (cur != NULL) {
    if (cur != labels) {
      printf(", ");
    }
    puts("{");
    printf("  label: %s\n", cur->label.label);
    printf("}");
    cur = cur->next;
  }
  printf("]\n");
}

bool _pc_parser_pseudo_code() {
  if (DEBUG_MODE == true) printf("_pseudo_code() : %s\n", yytext);
  bool result = false;
  if (_pc_parser_list_decl()) {
    _pc_parser_read_token();
    if (_token == PC_KEY_WORD_BEGIN) {
      _pc_parser_read_token();
      if (_pc_parser_list_inst()) {
        _pc_parser_read_token();
        if (_token == PC_KEY_WORD_END) {
          _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, NULL);
          _currentLabels = _pc_paser_clear_labels(_currentLabels);
          result = true;
        }
      }
    }
  }
  return result;
}

bool _pc_parser_list_decl() {
  if (DEBUG_MODE == true) printf("_list_decl() : %s\n", yytext);
  bool result = false;
  if (_token == PC_KEY_WORD_DATA) {
    _pc_parser_read_token();
    if (_token == PC_IDENTIFIER) {
      _variable_name = (char *) malloc((1 + strlen(yytext)) * sizeof(char));
      strcpy(_variable_name, yytext);
      _pc_parser_read_token();
      if (_token == PC_NUMBER) {
        _variable_value = atof(yytext);
        _data = _pc_parser_add_variable(_data, _variable_name, _variable_value);
        _pc_parser_read_token();
        if(_pc_parser_list_decl_aux()) {
          result = true;
        }
      }
    }
  }
  return result;
}

bool _pc_parser_list_decl_aux() {
  if (DEBUG_MODE == true) printf("_list_decl_aux() : %s\n", yytext);
  bool result = false;
  if (_pc_parser_list_decl()) {
    result = true;
  } else if (_token == PC_KEY_WORD_BEGIN) {
    result = _follow = true;
  }
  return result;
}

bool _pc_parser_list_inst() {
  if (DEBUG_MODE == true) printf("_list_inst() : %s\n", yytext);
  bool result = false;
  if (_pc_parser_inst()) {
    _pc_parser_read_token();
    if (_pc_parser_list_inst_aux()) {
      result = true;
    }
  }
  return result;
}

bool _pc_parser_list_inst_aux() {
  if (DEBUG_MODE == true) printf("_list_inst_aux() : %s\n", yytext);
  bool result = false;
  if (_pc_parser_list_inst()) {
    result = true;
  } else if (_token == PC_KEY_WORD_END) {
    result = _follow = true;
  }
  return result;
}

bool _pc_parser_inst() {
  if (DEBUG_MODE == true) printf("_inst() : %s\n", yytext);
  bool result = false;
  if (_token == PC_LABEL_BEGIN) {
    _currentLabels = _pc_parser_add_label(_currentLabels, yytext, NULL);
    result = true;
  } else if (_token == PC_LABEL_END) {
    _currentLabels = _pc_parser_add_label(_currentLabels, yytext, NULL);
    result = true;
  } else if (_token == PC_KEY_WORD_LOAD) {
    _pc_parser_read_token();
    if (_token == PC_IDENTIFIER) {
      _pc_add_variable_instruction(_pseudo_code, INSTRUCTION_LOAD, yytext);
      _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
      _currentLabels = _pc_paser_clear_labels(_currentLabels);
      result = true;
    }
  } else if (_token == PC_KEY_WORD_PUSH) {
    _pc_parser_read_token();
    if (_token == PC_NUMBER) {
      _pc_add_constant_instruction(_pseudo_code, INSTRUCTION_PUSH, atof(yytext));
      _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
      _currentLabels = _pc_paser_clear_labels(_currentLabels);
      result = true;
    }
  } else if (_token == PC_KEY_WORD_STORE) {
    _pc_parser_read_token();
    if (_token == PC_IDENTIFIER) {
      _pc_add_variable_instruction(_pseudo_code, INSTRUCTION_STORE, yytext);
      _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
      _currentLabels = _pc_paser_clear_labels(_currentLabels);
      result = true;
    }
  } else if (_token == PC_KEY_WORD_ADD) {
    _pc_add_constant_instruction(_pseudo_code, INSTRUCTION_ADD, 0);
    _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
    _currentLabels = _pc_paser_clear_labels(_currentLabels);
    result = true;
  } else if (_token == PC_KEY_WORD_SUB) {
    _pc_add_constant_instruction(_pseudo_code, INSTRUCTION_SUB, 0);
    _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
    _currentLabels = _pc_paser_clear_labels(_currentLabels);
    result = true;
  } else if (_token == PC_KEY_WORD_MULT) {
    _pc_add_constant_instruction(_pseudo_code, INSTRUCTION_MULT, 0);
    _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
    _currentLabels = _pc_paser_clear_labels(_currentLabels);
    result = true;
  } else if (_token == PC_KEY_WORD_DIV) {
    _pc_add_constant_instruction(_pseudo_code, INSTRUCTION_DIV, 0);
    _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
    _currentLabels = _pc_paser_clear_labels(_currentLabels);
    result = true;
  } else if (_token == PC_KEY_WORD_MOD) {
    _pc_add_constant_instruction(_pseudo_code, INSTRUCTION_MOD, 0);
    _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
    _currentLabels = _pc_paser_clear_labels(_currentLabels);
    result = true;
  } else if (_token == PC_KEY_WORD_JMP) {
    _pc_parser_read_token();
    if (_pc_parser_jump_label()) {
      _pc_add_labeled_instruction(_pseudo_code, INSTRUCTION_JMP, yytext);
      _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
      _currentLabels = _pc_paser_clear_labels(_currentLabels);
      result = true;
    }
  } else if (_token == PC_KEY_WORD_JT) {
    _pc_parser_read_token();
    if (_pc_parser_jump_label()) {
      _pc_add_labeled_instruction(_pseudo_code, INSTRUCTION_JT, yytext);
      _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
      _currentLabels = _pc_paser_clear_labels(_currentLabels);
      result = true;
    }
  } else if (_token == PC_KEY_WORD_JF) {
    _pc_parser_read_token();
    if (_pc_parser_jump_label()) {
      _pc_add_labeled_instruction(_pseudo_code, INSTRUCTION_JF, yytext);
      _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
      _currentLabels = _pc_paser_clear_labels(_currentLabels);
      result = true;
    }
  } else if (_token == PC_KEY_WORD_EVAL_G) {
    _pc_add_constant_instruction(_pseudo_code, INSTRUCTION_EVAL_G, 0);
    _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
    _currentLabels = _pc_paser_clear_labels(_currentLabels);
    result = true;
  } else if (_token == PC_KEY_WORD_EVAL_GE) {
    _pc_add_constant_instruction(_pseudo_code, INSTRUCTION_EVAL_GE, 0);
      _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
      _currentLabels = _pc_paser_clear_labels(_currentLabels);
    result = true;
  } else if (_token == PC_KEY_WORD_EVAL_L) {
    _pc_add_constant_instruction(_pseudo_code, INSTRUCTION_EVAL_L, 0);
    _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
    _currentLabels = _pc_paser_clear_labels(_currentLabels);
    result = true;
  } else if (_token == PC_KEY_WORD_EVAL_LE) {
    _pc_add_constant_instruction(_pseudo_code, INSTRUCTION_EVAL_LE, 0);
    _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
    _currentLabels = _pc_paser_clear_labels(_currentLabels);
    result = true;
  } else if (_token == PC_KEY_WORD_EVAL_E) {
    _pc_add_constant_instruction(_pseudo_code, INSTRUCTION_EVAL_E, 0);
    _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
    _currentLabels = _pc_paser_clear_labels(_currentLabels);
    result = true;
  } else if (_token == PC_KEY_WORD_EVAL_NE) {
    _pc_add_constant_instruction(_pseudo_code, INSTRUCTION_EVAL_NE, 0);
    _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
    _currentLabels = _pc_paser_clear_labels(_currentLabels);
    result = true;
  } else if (_token == PC_KEY_WORD_PRINT_NUMBER) {
    _pc_add_constant_instruction(_pseudo_code, INSTRUCTION_PRINT_NUMBER, 0);
    _allLabels = _pc_parser_add_labels(_allLabels, _currentLabels, _pseudo_code->last);
    _currentLabels = _pc_paser_clear_labels(_currentLabels);
    result = true;
  }
  return result;
}

bool _pc_parser_jump_label() {
  if (DEBUG_MODE == true) printf("_jump_label() : %s\n", yytext);
  bool result = false;
  if (_token == PC_LABEL_BEGIN) {
    result = true;
  } else if (_token == PC_LABEL_END) {
    result = true;
  }
  return result;
}