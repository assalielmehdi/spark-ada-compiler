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
  if (_if_statement()) {
    _read_token();
    if (_list_inst_aux()) {
      result = true;
    } 
  } else if (token == KEY_WORD_END || token == KEY_WORD_ELSIF || token == KEY_WORD_ELSE) {
    result = follow = true;
  }
  return result;
}

bool _list_inst_aux() {
  bool result = false;
  if (_list_inst()) {
    result = true;
  } else if (token == KEY_WORD_END || token == KEY_WORD_ELSIF || token == KEY_WORD_ELSE) {
    result = follow = true;
  }
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
        if (_list_inst()) {
          _read_token();
          if (_elsif_statement()) {
            result = true;
          }
        }
      }
    }
  }
  return result;
}

bool _elsif_statement() {
  bool result = false;
  if (token == KEY_WORD_ELSIF) {
    _read_token();
    if (_expression()) {
      _read_token();
      if (token == KEY_WORD_THEN) {
        _read_token();
        if (_list_inst()) {
          _read_token();
          if (_elsif_statement()) {
            result = true;
          }
        }
      }
    }
  } else if (token == KEY_WORD_ELSE) {
    _read_token();
    if (_list_inst()) {
      _read_token();
      if (_endif_statement()) {
        result = true;
      }
    }
  } else if (_endif_statement()) {
    result = true;
  }
  return result;
}

bool _endif_statement() {
  bool result = false;
  if (token == KEY_WORD_END) {
    _read_token();
    if (token == KEY_WORD_IF) {
      _read_token();
      if (token == DELIMITER_SEMICOLON) {
        result = true;
      }
    }
  }
  return result;
}

bool _expression() {
  bool result = false;
  if (_relation()) {
    _read_token();
    if (_expression_aux()) {
      result = true;
    }
  }
  return result;
}

bool _expression_aux() {
  bool result = false;
  if (token == KEY_WORD_AND) {
    _read_token();
    if (_relation()) {
      result = true;
    }
  } else if (token == KEY_WORD_XOR) {
    _read_token();
    if (_relation()) {
      result = true;
    }
  } else if (token == KEY_WORD_OR) {
    _read_token();
    if (_relation()) {
      result = true;
    }
  } else if (token == KEY_WORD_THEN) {
    result = follow = true;
  }
  return result;
}

bool _relation() {
  bool result = false;
  if (_simple_expression()) {
    _read_token();
    if (_relation_aux()) {
      result = true;
    }
  }
  return result;
}

bool _relation_aux() {
  bool result = false;
  if (token == DELIMITER_EQUAL) {
    _read_token();
    if (_simple_expression()) {
      result = true;
    }
  } else if (token == DELIMITER_DIVIDE_EQUAL) {
    _read_token();
    if (_simple_expression()) {
      result = true;
    }
  } else if (token == DELIMITER_LESS_THAN) {
    _read_token();
    if (_simple_expression()) {
      result = true;
    }
  } else if (token == DELIMITER_LESS_THAN_EQUAL) {
    _read_token();
    if (_simple_expression()) {
      result = true;
    }
  } else if (token == DELIMITER_GREATER_THAN) {
    _read_token();
    if (_simple_expression()) {
      result = true;
    }
  } else if (token == DELIMITER_GREATER_THAN_EQUAL) {
    _read_token();
    if (_simple_expression()) {
      result = true;
    }
  } else if (token == KEY_WORD_AND || token == KEY_WORD_OR || token == KEY_WORD_THEN || token == KEY_WORD_XOR) {
    result = follow = true;
  }
  return result;
}

bool _simple_expression() {
  bool result = false;
  return result;
}