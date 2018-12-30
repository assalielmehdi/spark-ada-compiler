#ifndef TAB_SYMB_H
#define TAB_SYMB_H

#ifndef SYNTACTICAL_ANALYZER
#include "syntactical_analyzer.h"
#endif


typedef struct {
  char *name;
  char *type;
  int  line;
  bool initialized;
  float  value;   
}_var_value_type;

_var_value_type *_create_var(char *name, char *type, int  line,bool initialized, float  value);

bool _add_var_to_tab_symbol(_var_value_type *var);

bool _in_tab_symbol(char * name);

void _reset_tab_symbol();

#endif