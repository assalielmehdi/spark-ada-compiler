#include "syntactical_analyzer.h"

_token_type token;

bool follow = false;

int main() {
  _read_token();
  if (_proc()) {
    puts("OK");
  } else {
    puts("NOK");
  }
  return 0;
}

void _read_token() {
  if (follow) {
    follow = false;
  } else {
    token = (_token_type) yylex();
  }
}

bool _proc() {
  bool result = false;
  if (token == KEY_WORD_PROCEDURE) {
    _read_token();
    if (token == IDENTIFIER) {
      _read_token();
      if (token == KEY_WORD_IS) {
        _read_token();
        if (_list_decl()) {
          _read_token();
          if (token == KEY_WORD_BEGIN) {
            _read_token();
            if (_list_inst()) {
              _read_token();
              if (token == KEY_WORD_END) {
                _read_token();
                if (token == IDENTIFIER) {
                  _read_token();
                  if (token == DELIMITER_SEMICOLON) {
                    result = true;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
}

bool _list_decl() {
  bool result = false;
  if (_decl()) {
    _read_token();
    if (_list_decl_aux()) {
      result = true;
    }
  }
  return result;
}

bool _decl() {
  bool result = false;
  if (token == IDENTIFIER) {
    _read_token();
    if (token == DELIMITER_PERIOD) {
      _read_token();
      if (_decl_aux()) {
        result = true;
      }
    }
  }
  return result;
}

bool _decl_aux() {
  bool result = false;
  if (_type()) {
    _read_token();
    if (_decl_aux_aux()) {
      result = true;
    }
  } else if (token == KEY_WORD_CONSTANT) {
    _read_token();
    if (_type()) {
      _read_token();
      if (_decl_aux_aux()) {
        result = true;
      }
    }
  }
  return result;
}

bool _decl_aux_aux() {
  bool result = false;
  if (token == DELIMITER_ASSIGN) {
    _read_token();
    if (_const()) {
      _read_token();
      if (token == DELIMITER_SEMICOLON) {
        result = true;
      }
    }
  } else if (token == DELIMITER_SEMICOLON) {
    result = true;
  }
  return result;
}

bool _list_decl_aux() {
  bool result = false;
  if (_list_decl()) {
    result  = true;
  } else if (token == KEY_WORD_BEGIN) {
    result = follow = true;
  }
  return result;
}

bool _type() {
  bool result = false;
  if (token == IDENTIFIER && !(
      strcmp(yytext, "Integer") * strcmp(yytext, "Float")  *
      strcmp(yytext, "Boolean") * strcmp(yytext, "Character") *
      strcmp(yytext, "Natural") * strcmp(yytext, "Positive") *
      strcmp(yytext, "String"))
  ) {
    result = true;
  }
  return result;
}

bool _const() {
  bool result = false;
  if (
    token == CHARACTER_LITERAL ||
    token == STRING_LITERAL ||
    token == BOOLEAN_TRUE_VALUE ||
    token == BOOLEAN_FALSE_VALUE ||
    token == INTEGER_VALUE ||
    token == FLOAT_VALUE
  ) {
    result = true;
  }
  return result;
}

bool _list_inst() {
  bool result = false;
  if (token == KEY_WORD_END) {
    result = follow = true;
  }
  return result;
}

// TODO: Implementation
bool _expression() {
  bool result = false;
  return result;
}

bool _if_statement() {
  bool result = false;
  if (token == KEY_WORD_IF) {
    _read_token();
    if (_expression()) {
      _read_token();
      if (token == KEY_WORD_THEN) {
        _read_token();
        if (_expression()) {
          _read_token();
          if (token == KEY_WORD_END) {
            _read_token();
            if (token == KEY_WORD_IF) {
              result = true;
            }
          }else if (_elsif_statement()) {
            result = true;
          }else if (_else_statement()) {
            result = true;
          }
        }
      }
    }
  }
  return result;
}

bool _else_statement() {
  bool result = false;
  if (token == KEY_WORD_ELSE) {
    _read_token();
    if (_expression()) {
      _read_token();
      if (token == KEY_WORD_END) {
        _read_token();
        if (token == KEY_WORD_IF) {
          result = true;
        }
      }
    }
  }
  return result;
}

bool _elsif_statement(){
  bool result = false;
  if (token == KEY_WORD_ELSIF) {
    _read_token();
    if (_expression()) {
      _read_token();
      if (token == KEY_WORD_THEN) {
        _read_token();
        if (_expression()) {
          _read_token();
          if (token == KEY_WORD_END) {
            _read_token();
            if (token == KEY_WORD_IF) {
              result = true;
            }
          } else if (_elsif_statement()) {
            result = true;
          } else if (_else_statement()) {
            result = true;
          }
        }
      }
    }
  }
  return result;
}