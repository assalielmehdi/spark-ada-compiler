#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pseudo_code.h"
#include "interpreter.h"

#define DEBUG_MODE false

_pc_token_type _token;

bool _follow = false;

int main(int argc, char **argv) {
  _interpreter_read_token();
  if (_interpreter_pseudo_code()) {
    puts("OK");
  } else {
    puts("NOK");
  }
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
  if (DEBUG_MODE == true) printf("_pseudo_code() : %s\n", yytext);
  bool result = false;
  if (_interpreter_list_decl()) {
    _interpreter_read_token();
    if (_token == PC_KEY_WORD_BEGIN) {
      _interpreter_read_token();
      if (_interpreter_list_inst()) {
        _interpreter_read_token();
        if (_token == PC_KEY_WORD_END) {
          result = true;
        }
      }
    }
  }
  return result;
}

bool _interpreter_list_decl() {
  if (DEBUG_MODE == true) printf("_list_decl() : %s\n", yytext);
  bool result = false;
  if (_token == PC_KEY_WORD_DATA) {
    _interpreter_read_token();
    if (_token == PC_IDENTIFIER) {
      _interpreter_read_token();
      if (_token == PC_NUMBER) {
        _interpreter_read_token();
        if(_interpreter_list_decl_aux()) {
          result = true;
        }
      }
    }
  }
  return result;
}

bool _interpreter_list_decl_aux() {
  if (DEBUG_MODE == true) printf("_list_decl_aux() : %s\n", yytext);
  bool result = false;
  if (_interpreter_list_decl()) {
    result = true;
  } else if (_token == PC_KEY_WORD_BEGIN) {
    result = _follow = true;
  }
  return result;
}

bool _interpreter_list_inst() {
  if (DEBUG_MODE == true) printf("_list_inst() : %s\n", yytext);
  bool result = false;
  if (_interpreter_inst()) {
    _interpreter_read_token();
    if (_interpreter_list_inst_aux()) {
      result = true;
    }
  }
  return result;
}

bool _interpreter_list_inst_aux() {
  if (DEBUG_MODE == true) printf("_list_inst_aux() : %s\n", yytext);
  bool result = false;
  if (_interpreter_list_inst()) {
    result = true;
  } else if (_token == PC_KEY_WORD_END) {
    result = _follow = true;
  }
  return result;
}

bool _interpreter_inst() {
  if (DEBUG_MODE == true) printf("_inst() : %s\n", yytext);
  bool result = false;
  if (_token == PC_LABEL_BEGIN) {
    result = true;
  } else if (_token == PC_LABEL_END) {
    result = true;
  } else if (_token == PC_KEY_WORD_DATA) {
    _interpreter_read_token();
    if (_token == PC_IDENTIFIER) {
      _interpreter_read_token();
      if (_token == PC_NUMBER) {
        result = true;
      }
    }
  } else if (_token == PC_KEY_WORD_LOAD) {
    _interpreter_read_token();
    if (_token == PC_IDENTIFIER) {
      result = true;
    }
  } else if (_token == PC_KEY_WORD_PUSH) {
    _interpreter_read_token();
    if (_token == PC_NUMBER) {
      result = true;
    }
  } else if (_token == PC_KEY_WORD_STORE) {
    _interpreter_read_token();
    if (_token == PC_IDENTIFIER) {
      result = true;
    }
  } else if (_token == PC_KEY_WORD_ADD) {
    result = true;
  } else if (_token == PC_KEY_WORD_SUB) {
    result = true;
  } else if (_token == PC_KEY_WORD_MULT) {
    result = true;
  } else if (_token == PC_KEY_WORD_DIV) {
    result = true;
  } else if (_token == PC_KEY_WORD_MOD) {
    result = true;
  } else if (_token == PC_KEY_WORD_JMP) {
    _interpreter_read_token();
    if (_interpreter_jump_label()) {
      result = true;
    }
  } else if (_token == PC_KEY_WORD_JT) {
    _interpreter_read_token();
    if (_interpreter_jump_label()) {
      result = true;
    }
  } else if (_token == PC_KEY_WORD_JF) {
    _interpreter_read_token();
    if (_interpreter_jump_label()) {
      result = true;
    }
  } else if (_token == PC_KEY_WORD_EVAL_G) {
    result = true;
  } else if (_token == PC_KEY_WORD_EVAL_GE) {
    result = true;
  } else if (_token == PC_KEY_WORD_EVAL_L) {
    result = true;
  } else if (_token == PC_KEY_WORD_EVAL_LE) {
    result = true;
  } else if (_token == PC_KEY_WORD_EVAL_E) {
    result = true;
  } else if (_token == PC_KEY_WORD_EVAL_NE) {
    result = true;
  }
  return result;
}

bool _interpreter_jump_label() {
  if (DEBUG_MODE == true) printf("_jump_label() : %s\n", yytext);
  bool result = false;
  if (_token == PC_LABEL_BEGIN) {
    result = true;
  } else if (_token == PC_LABEL_END) {
    result = true;
  }
  return result;
}