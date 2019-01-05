#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "tab_symb.h"

#define MAX_VAR 100

_var_info *_tab_symbol[MAX_VAR];
int _var_count = 0;

_var_info *_create_var(char *name, char *type, int line, bool initialized, float value) {
  _var_info *var = (_var_info*) malloc(sizeof (_var_info));
  var->name = (char *) malloc((strlen(name) + 1) * sizeof(char));
  strcpy(var->name, name);
  var->type = (char *) malloc((strlen(type) + 1) * sizeof(char));
  strcpy(var->type, type);
  var->line = line;
  var->initialized = initialized;
  var->value = value;
  return var;
}

bool _add_var_to_tab_symbol(_var_info *var) {
  bool result = false;
  if (_in_tab_symbol(var->name) == false) {
    _tab_symbol[_var_count++] = _create_var(var->name, var->type, var->line, var->initialized, var->value);
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

void _reset_tab_symbol() {
  memset(_tab_symbol, 0, sizeof(_tab_symbol));
  _var_count = 0;
}

