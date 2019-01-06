#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<stdbool.h>

#include "tab_symb.h"
#include "syntactical_analyzer.h"



#define MAX_VAR 100



_var_info *_tab_symbol[MAX_VAR];

int _var_count = 0;



_var_info *_create_var(char *name, char *type, int line, bool initialized, _var_value_type value_type, _var_value value) {

  _var_info *var = (_var_info*) malloc(sizeof (_var_info));

  var->name = (char *) malloc((strlen(name) + 1) * sizeof(char));

  strcpy(var->name, name);

  var->type = (char *) malloc((strlen(type) + 1) * sizeof(char));

  strcpy(var->type, type);

  var->line = line;

  var->initialized = initialized;

  var->value_type = value_type;

  var->value = value;

  return var;

}



bool _add_var_to_tab_symbol(_var_info *var) {

  bool result = false;

  if (_in_tab_symbol(var->name) == false) {

    _tab_symbol[_var_count++] = _create_var(var->name, var->type, var->line, var->initialized, var->value_type, var->value);

    result = true;

  }

  return result;

}



bool _in_tab_symbol(char *name) {

  bool result = false;

  for (int i = 0; i < _var_count && result == false; i++) {

    result = (strcmp(_tab_symbol[i]->name, name) == 0);

  }

  return result;

}



bool _check_value_type(_var_value_type value_type, _var_value value){

  bool result = false;

  if(value_type == VAR_VALUE_NUMBER && value.number_value == INTEGER_VALUE)

    result = true;

  else if(value_type == VAR_VALUE_NUMBER && value.number_value == FLOAT_VALUE)

    result = true;

  else if(value_type == VAR_VALUE_BOOLEAN && value.number_value == BOOLEAN_TRUE_VALUE || value.number_value == BOOLEAN_FALSE_VALUE)

    result = true;

  else if(value_type == VAR_VALUE_STRING && value.string_value == "STRING_LITERAL")

    result = true;

  else if(value_type == VAR_VALUE_CHARACTER && value.string_value == "CHARACTER_LITERAL")

    result = true;

  return result;

}



void _reset_tab_symbol() {

  memset(_tab_symbol, 0, sizeof(_tab_symbol));

  _var_count = 0;

}



void _print_tab_symbol() {

  printf("Table de symboles: [");

  for (int i = 0; i < _var_count; i++) {

    if (i > 0) {

      printf(", ");

    }

    printf("{\n");

    printf("  name: %s,\n", _tab_symbol[i]->name);

    printf("  type: %s,\n", _tab_symbol[i]->type);

    printf("  initialized: %d", _tab_symbol[i]->initialized);

    if (_tab_symbol[i]->initialized) {

      printf(",\n");

      switch(_tab_symbol[i]->value_type) {

        case VAR_VALUE_BOOLEAN:

          printf("  value: %s\n", _tab_symbol[i]->value.number_value == 1.0 ? "true" : "false");

          break;

        case VAR_VALUE_STRING:

          printf("  value: %s\n", _tab_symbol[i]->value.string_value);

          break;

        case VAR_VALUE_NUMBER:

          printf("  value: %f\n", _tab_symbol[i]->value.number_value);

          break;

      }

    } else {

      printf("\n");

    }

    printf("}");

  }

  printf("]\n");

}