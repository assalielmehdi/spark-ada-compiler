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
  } else if (_case_statement()) {
    _read_token();
    if (_list_inst_aux()) {
      result = true;
    } 
  } else if(_sample_inst()){
    _read_token();
    if(_list_inst_aux()){
      result = true;
    }
  }
  else if (
    token == KEY_WORD_END || token == KEY_WORD_ELSIF ||
    token == KEY_WORD_ELSE || token == KEY_WORD_WHEN
  ) {
    result = follow = true;
  }
  return result;
}

bool _list_inst_aux() {
  bool result = false;
  if (_list_inst()) {
    result = true;
  } else if (
    token == KEY_WORD_END || token == KEY_WORD_ELSIF ||
    token == KEY_WORD_ELSE || token == KEY_WORD_WHEN
  ) {
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
  printf("_expression() : %s\n", yytext);
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
  printf("_expression_aux() : %s\n", yytext);
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
  } else if (
    token == KEY_WORD_THEN || token == DELIMITER_PAR_CLOSED || token == DELIMITER_FAT_ARROW || 
    token == KEY_WORD_IS || token == DELIMITER_PIPE || token == DELIMITER_SEMICOLON
  ) {
    result = follow = true;
  }
  return result;
}

bool _relation() {
  printf("_relation() : %s\n", yytext);
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
  printf("_relation_aux() : %s\n", yytext);
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
  } else if (
    token == KEY_WORD_AND || token == KEY_WORD_OR || token == KEY_WORD_THEN || 
    token == KEY_WORD_XOR || token == DELIMITER_PAR_CLOSED || token == DELIMITER_FAT_ARROW || 
    token == KEY_WORD_IS || token == DELIMITER_PIPE || token == DELIMITER_SEMICOLON
  ) {
    result = follow = true;
  }
  return result;
}

bool _simple_expression() {
  printf("_simple_expression() : %s\n", yytext);
  bool result = false;
  if (token == DELIMITER_PLUS) {
    _read_token();
    if (_term()) {
      _read_token();
      if (_simple_expression_aux()) {
        result = true;
      }
    }
  } else if (token == DELIMITER_DASH) {
    _read_token();
    if (_term()) {
      _read_token();
      if (_simple_expression_aux()) {
        result = true;
      }
    }
  } else if (_term()) {
    _read_token();
    if (_simple_expression_aux()) {
      result = true;
    }
  }
  return result;
}

bool _simple_expression_aux() {
  printf("_simple_expression_aux() : %s\n", yytext);
  bool result = false;
  if (token == DELIMITER_PLUS) {
    _read_token();
    if (_term()) {
      _read_token();
      if (_simple_expression_aux()) {
        result = true;
      }
    }
  } else if (token == DELIMITER_DASH) {
    _read_token();
    if (_term()) {
      _read_token();
      if (_simple_expression_aux()) {
        result = true;
      }
    }
  } else if (token == DELIMITER_AND) {
    _read_token();
    if (_term()) {
      _read_token();
      if (_simple_expression_aux()) {
        result = true;
      }
    }
  } else if (
    token == KEY_WORD_AND || token == KEY_WORD_OR || token == KEY_WORD_THEN || token == KEY_WORD_XOR ||
    token == DELIMITER_EQUAL || token == DELIMITER_DIVIDE_EQUAL || token == DELIMITER_LESS_THAN ||
    token == DELIMITER_LESS_THAN_EQUAL || token == DELIMITER_GREATER_THAN || 
    token == DELIMITER_GREATER_THAN_EQUAL || token == DELIMITER_PAR_CLOSED ||
    token == DELIMITER_FAT_ARROW || token == KEY_WORD_IS || token == DELIMITER_PIPE || token == DELIMITER_SEMICOLON
  ) {
    result = follow = true;
  }
  return result;
}

bool _term() {
  printf("_term() : %s\n", yytext);
  bool result = false;
  if (_factor()) {
    _read_token();
    if (_term_aux()) {
      result = true;
    }
  }
  return result;
}

bool _term_aux() {
  printf("_term_aux() : %s\n", yytext);
  bool result = false;
  if (token == DELIMITER_STAR) {
    _read_token();
    if (_factor()) {
      _read_token();
      if (_term_aux()) {
        result = true;
      }
    }
  } else if (token == DELIMITER_SLASH) {
    _read_token();
    if (_factor()) {
      _read_token();
      if (_term_aux()) {
        result = true;
      }
    }
  } else if (token == KEY_WORD_MOD) {
    _read_token();
    if (_factor()) {
      _read_token();
      if (_term_aux()) {
        result = true;
      }
    }
  } else if (token == KEY_WORD_REM) {
    _read_token();
    if (_factor()) {
      _read_token();
      if (_term_aux()) {
        result = true;
      }
    }
  } else if (
    token == KEY_WORD_AND || token == KEY_WORD_OR || token == KEY_WORD_THEN || token == KEY_WORD_XOR ||
    token == DELIMITER_EQUAL || token == DELIMITER_DIVIDE_EQUAL || token == DELIMITER_LESS_THAN ||
    token == DELIMITER_LESS_THAN_EQUAL || token == DELIMITER_GREATER_THAN || token == DELIMITER_GREATER_THAN_EQUAL ||
    token == DELIMITER_PLUS || token == DELIMITER_DASH || token == DELIMITER_AND || token == DELIMITER_PAR_CLOSED ||
    token == DELIMITER_FAT_ARROW || token == KEY_WORD_IS || token == DELIMITER_PIPE || token == DELIMITER_SEMICOLON
  ) {
    result = follow = true;
  }
  return result;
}

bool _factor() {
  printf("_factor() : %s\n", yytext);
  bool result = false;
  if (_primary()) {
    result = true;
  }
  return result;
}

bool _primary() {
  printf("_primary() : %s\n", yytext);
  bool result = false;
  if (token == INTEGER_VALUE) {
    result = true;
  } else if (token == FLOAT_VALUE) {
    result = true;
  } else if (token == KEY_WORD_NULL) {
    result = true;
  } else if (token == STRING_LITERAL) {
    result = true;
  } else if (token == IDENTIFIER) {
    result = true;
  } else if (token == DELIMITER_PAR_OPENED) {
    _read_token();
    if (_expression()) {
      _read_token();
      if (DELIMITER_PAR_CLOSED) {
        result = true;
      }
    }
  }
  return result;
}

bool _case_statement() {
  printf("_case_statement() : %s\n", yytext);
  bool result = false;
  if (token == KEY_WORD_CASE) {
    _read_token();
    if (_expression()) {
      _read_token();
      if (token == KEY_WORD_IS) {
        _read_token();
        if (_case_statement_alternative()) {
          _read_token();
          if (_case_statement_aux()) {
            result = true;
          }
        }
      }
    }
  }
  return result;
}

bool _case_statement_aux() {
  printf("_case_statement_aux() : %s\n", yytext);
  bool result = false;
  if (token == KEY_WORD_END) {
    _read_token();
    if (token == KEY_WORD_CASE) {
      _read_token();
      if (token == DELIMITER_SEMICOLON) {
        result = true;
      }
    }
  } else if (_case_statement_alternative()) {
    _read_token();
    if (_case_statement_aux()) {
      result = true;
    }
  }
  return result;
}

bool _case_statement_alternative() {
  printf("_case_statement_alternative() : %s\n", yytext);
  bool result = false;
  if (token == KEY_WORD_WHEN) {
    _read_token();
    if (_choice_list()) {
      _read_token();
      if (token == DELIMITER_FAT_ARROW) {
        _read_token();
        if (_list_inst()) {
          result = true;
        }
      }
    }
  }
  return result;
}

bool _choice_list() {
  printf("_choice_list() : %s\n", yytext);
  bool result = false;
  if (_choice()) {
    _read_token();
    if (_choice_list_aux()) {
      result = true;
    }
  }
  return result;
}

bool _choice_list_aux() {
  printf("_choice_list_aux() : %s\n", yytext);
  bool result = false;
  if (token == DELIMITER_PIPE) {
    _read_token();
    if (_choice()) {
      _read_token();
      if (_choice_list_aux()) {
        result = true;
      }
    }
  } else if (token == DELIMITER_FAT_ARROW) {
    result = follow = true;
  }
  return result;
}

bool _choice() {
  printf("_choice() : %s\n", yytext);
  bool result = false;
  if (token == KEY_WORD_OTHERS) {
    result = true;
  } else if (_expression()) {
    result = true;
  }
  return result;
}

bool _sample_inst() {
  printf("_sample_inst() : %s\n", yytext);
  bool result = false;
  if (token == IDENTIFIER) {
    _read_token();
    if (token == DELIMITER_ASSIGN) {
      _read_token();
      if (_expression()) {
        _read_token();
        if( token == DELIMITER_SEMICOLON) {
          result = true;
        }
      }
    }
  }
  return result;
}