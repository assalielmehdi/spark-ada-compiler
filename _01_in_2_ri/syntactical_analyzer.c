#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntactical_analyzer.h"
#include "tab_symb.h"
#include "errors.h"
#include "ast.h"

#define DEBUG_MODE false

_token_type _token;

bool _follow = false;

_var_info *_var = NULL;

char *_current_var_name = NULL;

int main() {
  _reset_tab_symbol();
  _read_token();
  if (_proc()) {
    puts("--------------------");
    puts("Program syntactically correct");
  } else {
    puts("--------------------");
    puts("Program syntactically incorrect");
  }
  if (DEBUG_MODE == true) {
    puts("--------------------");
    puts("Sym Table:");
    _print_tab_symbol();
  }
  puts("--------------------");
  puts("Errors:");
  _show_semantic_errors();
  return 0;
}

void _read_token() {
  if (_follow) {
    _follow = false;
  } else {
    _token = (_token_type) yylex();
  }
}

bool _proc() {
  if (DEBUG_MODE == true) printf("_proc() : %s\n", yytext);
  bool result = false;
  if (_token == KEY_WORD_PROCEDURE) {
    _read_token();
    if (_token == IDENTIFIER) {
      _read_token();
      if (_token == KEY_WORD_IS) {
        _read_token();
        if (_list_decl()) {
          _read_token();
          if (_token == KEY_WORD_BEGIN) {
            _read_token();
            if (_list_inst()) {
              _read_token();
              if (_token == KEY_WORD_END) {
                _read_token();
                if (_token == IDENTIFIER) {
                  _read_token();
                  if (_token == DELIMITER_SEMICOLON) {
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
  if (DEBUG_MODE == true) printf("_list_decl() : %s\n", yytext);
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
  if (DEBUG_MODE == true) printf("_decl() : %s\n", yytext);
  bool result = false;
  if (_token == IDENTIFIER) {
    _var = (_var_info *) malloc(sizeof(_var_info));
    _var->name = (char *) malloc((strlen(yytext) + 1) * sizeof(char));
    strcpy(_var->name, yytext);
    if (DEBUG_MODE == true) printf("var_name: %s\n", _var->name);
    _read_token();
    if (_token == DELIMITER_PERIOD) {
      _read_token();
      if (_decl_aux()) {
        result = true;
      }
    }
  }
  return result;
}

bool _decl_aux() {
  if (DEBUG_MODE == true) printf("_decl_aux() : %s\n", yytext);
  bool result = false;
  if (_type()) {
    _var->type = (char *) malloc((strlen(yytext) + 1) * sizeof(char));
    strcpy(_var->type, yytext);
    _var->line = yylineno;
    if (strcmp(yytext, "Integer") == 0) {
      _var->value_type = VAR_VALUE_INTEGER;
    }  else if (strcmp(yytext, "Float") == 0) {
      _var->value_type = VAR_VALUE_FLOAT;
    } else if (strcmp(yytext, "Boolean") == 0) {
      _var->value_type = VAR_VALUE_BOOLEAN;
    } else if (strcmp(yytext, "String") == 0) {
      _var->value_type = VAR_VALUE_STRING;
    } else if (strcmp(yytext, "Character") == 0) {
      _var->value_type = VAR_VALUE_CHARACTER;
    }
    if (DEBUG_MODE == true) printf("var_type: %s\n", _var->type);
    _read_token();
    if (_decl_aux_aux()) {
      result = true;
    }
  } else if (_token == KEY_WORD_CONSTANT) {
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
  if (DEBUG_MODE == true) printf("_decl_aux_aux() : %s\n", yytext);
  bool result = false;
  if (_token == DELIMITER_ASSIGN) {
    _var->initialized = true;
    if (DEBUG_MODE == true) printf("var_initialized: %d\n", _var->initialized);
    _read_token();
    if (_const()) {
      if (
        (_token == CHARACTER_LITERAL && _var->value_type != VAR_VALUE_CHARACTER) ||
        (_token == STRING_LITERAL && _var->value_type != VAR_VALUE_STRING) ||
        (_token == INTEGER_VALUE && _var->value_type != VAR_VALUE_INTEGER) ||
        (_token == FLOAT_VALUE && _var->value_type != VAR_VALUE_FLOAT) ||
        ((_token == BOOLEAN_TRUE_VALUE || _token == BOOLEAN_FALSE_VALUE) && _var->value_type != VAR_VALUE_BOOLEAN)
      ) {
        _add_semantic_error(BADLY_INITIALIZED, _var->line, _var->name);
      }
      _read_token();
      if (_token == DELIMITER_SEMICOLON) {
        if (_add_var_to_tab_symbol(_var) == false) {
          _add_semantic_error(ALREADY_DECLARED, _var->line, _var->name);
        };
        result = true;
      }
    }
  } else if (_token == DELIMITER_SEMICOLON) {
    _var->initialized = false;
    if (_add_var_to_tab_symbol(_var) == false) {
      _add_semantic_error(ALREADY_DECLARED, _var->line, _var->name);
    };
    result = true;
  }
  return result;
}

bool _list_decl_aux() {
  if (DEBUG_MODE == true) printf("_list_decl_aux() : %s\n", yytext);
  bool result = false;
  if (_list_decl()) {
    result  = true;
  } else if (_token == KEY_WORD_BEGIN) {
    result = _follow = true;
  }
  return result;
}

bool _type() {
  if (DEBUG_MODE == true) printf("_type() : %s\n", yytext);
  bool result = false;
  if (_token == IDENTIFIER && !(
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
  if (DEBUG_MODE == true) printf("_const() : %s\n", yytext);
  bool result = false;
  if (
    _token == CHARACTER_LITERAL ||
    _token == STRING_LITERAL ||
    _token == BOOLEAN_TRUE_VALUE ||
    _token == BOOLEAN_FALSE_VALUE ||
    _token == INTEGER_VALUE ||
    _token == FLOAT_VALUE
  ) {
    result = true;
  }
  return result;
}

bool _list_inst() {
  if (DEBUG_MODE == true) printf("_list_inst() : %s\n", yytext);
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
  } else if (_identified_statement()){
    _read_token();
    if(_list_inst_aux()){
      result = true;
    }
  } else if (_loop_statement()) {
    _read_token();
    if(_list_inst_aux()){
      result = true;
    }
  } else if (
    _token == KEY_WORD_END || _token == KEY_WORD_ELSIF ||
    _token == KEY_WORD_ELSE || _token == KEY_WORD_WHEN
  ) {
    result = _follow = true;
  }
  return result;
}

bool _list_inst_aux() {
  if (DEBUG_MODE == true) printf("_list_inst_aux() : %s\n", yytext);
  bool result = false;
  if (_list_inst()) {
    result = true;
  } else if (
    _token == KEY_WORD_END || _token == KEY_WORD_ELSIF ||
    _token == KEY_WORD_ELSE || _token == KEY_WORD_WHEN
  ) {
    result = _follow = true;
  }
  return result;
}

bool _if_statement() {
  if (DEBUG_MODE == true) printf("_if_statement() : %s\n", yytext);
  bool result = false;
  if (_token == KEY_WORD_IF) {
    _read_token();
    _ast *_past = (_ast *) malloc(sizeof(_ast));
    if (_expression(_past)) {
      _read_token();
      if (_token == KEY_WORD_THEN) {
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
  if (DEBUG_MODE == true) printf("_elsif_statement() : %s\n", yytext);
  bool result = false;
  if (_token == KEY_WORD_ELSIF) {
    _read_token();
    _ast *_past = (_ast *) malloc(sizeof(_ast));
    if (_expression(_past)) {
      _read_token();
      if (_token == KEY_WORD_THEN) {
        _read_token();
        if (_list_inst()) {
          _read_token();
          if (_elsif_statement()) {
            result = true;
          }
        }
      }
    }
  } else if (_token == KEY_WORD_ELSE) {
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
  if (DEBUG_MODE == true) printf("_endif_statement() : %s\n", yytext);
  bool result = false;
  if (_token == KEY_WORD_END) {
    _read_token();
    if (_token == KEY_WORD_IF) {
      _read_token();
      if (_token == DELIMITER_SEMICOLON) {
        result = true;
      }
    }
  }
  return result;
}

bool _expression(_ast *_past) {
  if (DEBUG_MODE == true) printf("_expression() : %s\n", yytext);
  bool result = false;
  if (_relation(_past)) {
    _read_token();
    if (_expression_aux(_past)) {
      result = true;
    }
  }
  return result;
}

bool _expression_aux(_ast *_past) {
  if (DEBUG_MODE == true) printf("_expression_aux() : %s\n", yytext);
  bool result = false;
  if (_token == KEY_WORD_AND) {
    _read_token();
    if (_relation(_past)) {
      result = true;
    }
  } else if (_token == KEY_WORD_XOR) {
    _read_token();
    if (_relation(_past)) {
      result = true;
    }
  } else if (_token == KEY_WORD_OR) {
    _read_token();
    if (_relation(_past)) {
      result = true;
    }
  } else if (
    _token == KEY_WORD_THEN || _token == DELIMITER_PAR_CLOSED || _token == DELIMITER_FAT_ARROW || 
    _token == KEY_WORD_IS || _token == DELIMITER_PIPE || _token == DELIMITER_SEMICOLON ||
    _token == KEY_WORD_LOOP
  ) {
    result = _follow = true;
  }
  return result;
}

bool _relation(_ast *_past) {
  if (DEBUG_MODE == true) printf("_relation() : %s\n", yytext);
  bool result = false;
  if (_simple_expression(_past)) {
    _read_token();
    if (_relation_aux(_past)) {
      result = true;
    }
  }
  return result;
}

bool _relation_aux(_ast *_past) {
  if (DEBUG_MODE == true) printf("_relation_aux() : %s\n", yytext);
  bool result = false;
  if (_token == DELIMITER_EQUAL) {
    *_past = _ast_create_operation_node(OPERATION_EQUAL, *_past, NULL);
    _ast *_right = (_ast *) malloc(sizeof(_ast));
    _read_token();
    if (_simple_expression(_right)) {
      (*_past)->value.operation.right = *_right;
      result = true;
    }
  } else if (_token == DELIMITER_DIVIDE_EQUAL) {
    *_past = _ast_create_operation_node(OPERATION_NOT_EQUAL, *_past, NULL);
    _ast *_right = (_ast *) malloc(sizeof(_ast));
    _read_token();
    if (_simple_expression(_right)) {
      (*_past)->value.operation.right = *_right;
      result = true;
    }
  } else if (_token == DELIMITER_LESS_THAN) {
    *_past = _ast_create_operation_node(OPERATION_LESS_THAN, *_past, NULL);
    _ast *_right = (_ast *) malloc(sizeof(_ast));
    _read_token();
    if (_simple_expression(_right)) {
      (*_past)->value.operation.right = *_right;
      result = true;
    }
  } else if (_token == DELIMITER_LESS_THAN_EQUAL) {
    *_past = _ast_create_operation_node(OPERATION_LESS_THAN_EQUAL, *_past, NULL);
    _ast *_right = (_ast *) malloc(sizeof(_ast));
    _read_token();
    if (_simple_expression(_right)) {
      (*_past)->value.operation.right = *_right;
      result = true;
    }
  } else if (_token == DELIMITER_GREATER_THAN) {
    *_past = _ast_create_operation_node(OPERATION_GREATER_THAN, *_past, NULL);
    _ast *_right = (_ast *) malloc(sizeof(_ast));
    _read_token();
    if (_simple_expression(_right)) {
      (*_past)->value.operation.right = *_right;
      result = true;
    }
  } else if (_token == DELIMITER_GREATER_THAN_EQUAL) {
    *_past = _ast_create_operation_node(OPERATION_GREATER_THAN_EQUAL, *_past, NULL);
    _ast *_right = (_ast *) malloc(sizeof(_ast));
    _read_token();
    if (_simple_expression(_right)) {
      (*_past)->value.operation.right = *_right;
      result = true;
    }
  } else if (
    _token == KEY_WORD_AND || _token == KEY_WORD_OR || _token == KEY_WORD_THEN || 
    _token == KEY_WORD_XOR || _token == DELIMITER_PAR_CLOSED || _token == DELIMITER_FAT_ARROW || 
    _token == KEY_WORD_IS || _token == DELIMITER_PIPE || _token == DELIMITER_SEMICOLON ||
    _token == KEY_WORD_LOOP
  ) {
    result = _follow = true;
  }
  return result;
}

bool _simple_expression(_ast *_past) {
  if (DEBUG_MODE == true) printf("_simple_expression() : %s\n", yytext);
  bool result = false;
  if (_token == DELIMITER_PLUS) {
    _read_token();
    if (_term(_past)) {
      _read_token();
      if (_simple_expression_aux(_past)) {
        result = true;
      }
    }
  } else if (_token == DELIMITER_DASH) {
    _read_token();
    if (_term(_past)) {
      _read_token();
      if (_simple_expression_aux(_past)) {
        result = true;
      }
    }
  } else if (_term(_past)) {
    _read_token();
    if (_simple_expression_aux(_past)) {
      result = true;
    }
  }
  return result;
}

bool _simple_expression_aux(_ast *_past) {
  if (DEBUG_MODE == true) printf("_simple_expression_aux() : %s\n", yytext);
  bool result = false;
  if (_token == DELIMITER_PLUS) {
    *_past = _ast_create_operation_node(OPERATION_PLUS, *_past, NULL);
    _ast *_right = (_ast *) malloc(sizeof(_ast));
    _read_token();
    if (_term(_right)) {
      _read_token();
      if (_simple_expression_aux(_right)) {
        (*_past)->value.operation.right = *_right;
        result = true;
      }
    }
  } else if (_token == DELIMITER_DASH) {
    *_past = _ast_create_operation_node(OPERATION_MINUS, *_past, NULL);
    _ast *_right = (_ast *) malloc(sizeof(_ast));
    _read_token();
    if (_term(_right)) {
      _read_token();
      if (_simple_expression_aux(_right)) {
        (*_past)->value.operation.right = *_right;
        result = true;
      }
    }
  } else if (_token == DELIMITER_AND) {
    _read_token();
    if (_term(_past)) {
      _read_token();
      if (_simple_expression_aux(_past)) {
        result = true;
      }
    }
  } else if (
    _token == KEY_WORD_AND || _token == KEY_WORD_OR || _token == KEY_WORD_THEN || _token == KEY_WORD_XOR ||
    _token == DELIMITER_EQUAL || _token == DELIMITER_DIVIDE_EQUAL || _token == DELIMITER_LESS_THAN ||
    _token == DELIMITER_LESS_THAN_EQUAL || _token == DELIMITER_GREATER_THAN || 
    _token == DELIMITER_GREATER_THAN_EQUAL || _token == DELIMITER_PAR_CLOSED ||
    _token == DELIMITER_FAT_ARROW || _token == KEY_WORD_IS || _token == DELIMITER_PIPE || 
    _token == DELIMITER_SEMICOLON || _token == KEY_WORD_LOOP
  ) {
    result = _follow = true;
  }
  return result;
}

bool _term(_ast *_past) {
  if (DEBUG_MODE == true) printf("_term() : %s\n", yytext);
  bool result = false;
  if (_factor(_past)) {
    _read_token();
    if (_term_aux(_past)) {
      result = true;
    }
  }
  return result;
}

bool _term_aux(_ast *_past) {
  if (DEBUG_MODE == true) printf("_term_aux() : %s\n", yytext);
  bool result = false;
  if (_token == DELIMITER_STAR) {
    *_past = _ast_create_operation_node(OPERATION_MULT, *_past, NULL);
    _ast *_right = (_ast *) malloc(sizeof(_ast));
    _read_token();
    if (_factor(_right)) {
      _read_token();
      if (_term_aux(_right)) {
        (*_past)->value.operation.right = *_right;
        result = true;
      }
    }
  } else if (_token == DELIMITER_SLASH) {
    *_past = _ast_create_operation_node(OPERATION_DIV, *_past, NULL);
    _ast *_right = (_ast *) malloc(sizeof(_ast));
    _read_token();
    if (_factor(_right)) {
      _read_token();
      if (_term_aux(_right)) {
        (*_past)->value.operation.right = *_right;
        result = true;
      }
    }
  } else if (_token == KEY_WORD_MOD) {
    _read_token();
    if (_factor(_past)) {
      _read_token();
      if (_term_aux(_past)) {
        result = true;
      }
    }
  } else if (_token == KEY_WORD_REM) {
    _read_token();
    if (_factor(_past)) {
      _read_token();
      if (_term_aux(_past)) {
        result = true;
      }
    }
  } else if (
    _token == KEY_WORD_AND || _token == KEY_WORD_OR || _token == KEY_WORD_THEN || _token == KEY_WORD_XOR ||
    _token == DELIMITER_EQUAL || _token == DELIMITER_DIVIDE_EQUAL || _token == DELIMITER_LESS_THAN ||
    _token == DELIMITER_LESS_THAN_EQUAL || _token == DELIMITER_GREATER_THAN || _token == DELIMITER_GREATER_THAN_EQUAL ||
    _token == DELIMITER_PLUS || _token == DELIMITER_DASH || _token == DELIMITER_AND || _token == DELIMITER_PAR_CLOSED ||
    _token == DELIMITER_FAT_ARROW || _token == KEY_WORD_IS || _token == DELIMITER_PIPE || _token == DELIMITER_SEMICOLON ||
    _token == KEY_WORD_LOOP
  ) {
    result = _follow = true;
  }
  return result;
}

bool _factor(_ast *_past) {
  if (DEBUG_MODE == true) printf("_factor() : %s\n", yytext);
  bool result = false;
  if (_primary(_past)) {
    result = true;
  }
  return result;
}

bool _primary(_ast *_past) {
  if (DEBUG_MODE == true) printf("_primary() : %s\n", yytext);
  bool result = false;
  if (_token == INTEGER_VALUE) {
    *_past = _ast_create_constant_node(NODE_CONSTANT_INT, atof(yytext));
    result = true;
  } else if (_token == FLOAT_VALUE) {
    *_past = _ast_create_constant_node(NODE_CONSTANT_DOUBLE, atof(yytext));
    result = true;
  } else if (_token == BOOLEAN_TRUE_VALUE) {
    *_past = _ast_create_constant_node(NODE_CONSTANT_BOOL, 1.0);
    result = true;
  }  else if (_token == BOOLEAN_FALSE_VALUE) {
    *_past = _ast_create_constant_node(NODE_CONSTANT_BOOL, 0.0);
    result = true;
  } else if (_token == KEY_WORD_NULL) {
    result = true;
  } else if (_token == STRING_LITERAL) {
    result = true;
  } else if (_token == IDENTIFIER) {
    if (_in_tab_symbol(yytext) == false) {
      _add_semantic_error(NOT_DECLARED, yylineno, yytext);
    } else if (_var_initialized(yytext) == false) {
      _add_semantic_error(NOT_INITIALIZED, yylineno, yytext);
    } else {
      *_past = _ast_create_variable_node(yytext);
    }
    result = true;
  } else if (_token == DELIMITER_PAR_OPENED) {
    _read_token();
    if (_expression(_past)) {
      _read_token();
      if (DELIMITER_PAR_CLOSED) {
        result = true;
      }
    }
  }
  return result;
}

bool _case_statement() {
  if (DEBUG_MODE == true) printf("_case_statement() : %s\n", yytext);
  bool result = false;
  if (_token == KEY_WORD_CASE) {
    _read_token();
    _ast *_past = (_ast *) malloc(sizeof(_ast));
    if (_expression(_past)) {
      _read_token();
      if (_token == KEY_WORD_IS) {
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
  if (DEBUG_MODE == true) printf("_case_statement_aux() : %s\n", yytext);
  bool result = false;
  if (_token == KEY_WORD_END) {
    _read_token();
    if (_token == KEY_WORD_CASE) {
      _read_token();
      if (_token == DELIMITER_SEMICOLON) {
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
  if (DEBUG_MODE == true) printf("_case_statement_alternative() : %s\n", yytext);
  bool result = false;
  if (_token == KEY_WORD_WHEN) {
    _read_token();
    if (_choice_list()) {
      _read_token();
      if (_token == DELIMITER_FAT_ARROW) {
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
  if (DEBUG_MODE == true) printf("_choice_list() : %s\n", yytext);
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
  if (DEBUG_MODE == true) printf("_choice_list_aux() : %s\n", yytext);
  bool result = false;
  if (_token == DELIMITER_PIPE) {
    _read_token();
    if (_choice()) {
      _read_token();
      if (_choice_list_aux()) {
        result = true;
      }
    }
  } else if (_token == DELIMITER_FAT_ARROW) {
    result = _follow = true;
  }
  return result;
}

bool _choice() {
  if (DEBUG_MODE == true) printf("_choice() : %s\n", yytext);
  bool result = false;
  _ast *_past = (_ast *) malloc(sizeof(_ast));
  if (_token == KEY_WORD_OTHERS) {
    result = true;
  } else if (_expression(_past)) {
    result = true;
  }
  return result;
}

bool _identified_statement() {
  if (DEBUG_MODE == true) printf("_identified_statement() : %s\n", yytext);
  bool result = false;
  if (_token == IDENTIFIER) {
    _current_var_name = (char *) malloc((strlen(yytext) + 1) * sizeof(char));
    strcpy(_current_var_name, yytext);
    _read_token();
    if (_identified_statement_aux()) {
      result = true;
    }
  }
  return result;
}

bool _identified_statement_aux() {
  if (DEBUG_MODE == true) printf("_identified_statement_aux() : %s\n", yytext);
  bool result = false;
  if (_sample_inst()) {
    result = true;
  } else if (_identified_loop_statement()) {
    result = true;
  }
  return result;
}

bool _sample_inst() {
  if (DEBUG_MODE == true) printf("_sample_inst() : %s\n", yytext);
  bool result = false;
  if (_token == DELIMITER_ASSIGN) {
    if (_in_tab_symbol(_current_var_name) == false) {
      _add_semantic_error(NOT_DECLARED, yylineno, _current_var_name);
    }
    _read_token();
    _ast *_past = (_ast *) malloc(sizeof(_ast));
    if (_expression(_past)) {
      _read_token();
      if (_token == DELIMITER_SEMICOLON) {
        result = true;
      }
    }
  }
  return result;
}

bool _identified_loop_statement() {
  if (DEBUG_MODE == true) printf("_identified_loop_statement() : %s\n", yytext);
  bool result = false;
  if (_token == DELIMITER_PERIOD) {
    _read_token();
    if (_loop_statement()) {
      result = true;
    }
  }
  return result;
}

bool _loop_statement() {
  if (DEBUG_MODE == true) printf("_loop_statement() : %s\n", yytext);
  bool result = false;
  if (_token == KEY_WORD_WHILE) {
    _read_token();
    _ast *_past = (_ast *) malloc(sizeof(_ast));
    if (_expression(_past)) {
      _read_token();
      if (_loop_statement_aux()) {
        result = true;
      }
    }
  } else if (_loop_statement_aux()) {
    result = true;
  } 
  return result;
}

bool _loop_statement_aux() {
  if (DEBUG_MODE == true) printf("_loop_statement_aux() : %s\n", yytext);
  bool result = false;
  if (_token == KEY_WORD_LOOP) {
    _read_token();
    if (_list_inst()) {
      _read_token();
      if (KEY_WORD_END) {
        _read_token();
        if (_token == KEY_WORD_LOOP) {
          _read_token();
          if (_loop_statement_aux_aux()) {
            result = true;
          }
        }
      }
    }
  }
  return result;
}

bool _loop_statement_aux_aux() {
  if (DEBUG_MODE == true) printf("_loop_statement_aux_aux() : %s\n", yytext);
  bool result = false;
  if (_token == DELIMITER_SEMICOLON) {
    result = true;
  } else if (_token == IDENTIFIER) {
    _read_token();
    if (_token == DELIMITER_SEMICOLON) {
      result = true;
    }
  }
  return result;
}