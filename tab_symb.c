#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tab_symb.h"

#define MAX_VAR 100

_var_value_type *_tab_symbol[MAX_VAR];
int _var_count = 0; // NumberOfVar





_var_value_type *_create_var(char *name, char *type, int  line,bool initialized, float  value){
  _var_value_type *var = (_var_value_type*) malloc (sizeof (_var_value_type) );
  var->name = (char *) malloc (strlen(name));
  strcpy(var->name, name);
  var->type = (char *) malloc (strlen(type));
  strcpy(var->type, type);
  var->line = line;
  var->initialized = initialized;
  var->value = value;
  return var;
}

  bool _add_var_to_tab_symbol(_var_value_type *var){
  bool result = false;
  if(_in_tab_symbol(var->name)){
    _tab_symbol[_var_count++] = _create_var(var->name, var->type, var->line, var->initialized, var->value);
    result = true;
  }
  return result;
}
bool _in_tab_symbol(char * name){
  bool result = false;
  int i =0;
  while ((i < _var_count) && (strcmp(_tab_symbol[i]->name,name) != 0)) i++;
    result = true;
  return result;
}

void _reset_tab_symbol(){
memset(_tab_symbol, 0, sizeof (_tab_symbol));
}

