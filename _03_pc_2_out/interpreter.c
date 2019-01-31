#include <stdio.h>
#include <stdlib.h>
#include "pseudo_code.h"
#include "interpreter.h"

_pc_token_type _token;

bool _follow = false;

int main(int argc, char **argv) {

  return EXIT_SUCCESS;
}

void _interpreter_read_token() {
  if (_follow) {
    _follow = false;
  } else {
    _token = (_pc_token_type) yylex();
  }
}

bool _interpreter_pseudo_code() {
  bool result = false;

  return result;
}

bool _interpreter_list_decl() {
  bool result = false;

  return result;
}

bool _interpreter_list_decl_aux() {
  bool result = false;

  return result;
}

bool _interpreter_list_inst() {
  bool result = false;

  return result;
}

bool _interpreter_list_inst_aux() {
  bool result = false;

  return result;
}

bool _interpreter_inst() {
  bool result = false;

  return result;
}

bool _interpreter_jump_label() {
  bool result = false;

  return result;
}