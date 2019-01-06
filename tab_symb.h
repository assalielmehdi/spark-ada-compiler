#ifndef TAB_SYMB_H
#define TAB_SYMB_H

typedef enum {
  VAR_VALUE_NUMBER,
  VAR_VALUE_BOOLEAN,
  VAR_VALUE_STRING,
  CHARACTER_LITERAL
} _var_value_type;

typedef union {
  char *string_value;
  float number_value;
} _var_value;

typedef struct {
  char *name;
  char *type;
  int  line;
  bool initialized;
  _var_value_type value_type;
  _var_value value;   
} _var_info;

_var_info *_create_var(char *name, char *type, int line, bool initialized, _var_value_type value_type, _var_value value);

bool _add_var_to_tab_symbol(_var_info *var);

bool _in_tab_symbol(char * name);

bool _check_value_type(_var_value_type value_type, _var_value value);

void _reset_tab_symbol();

void _print_tab_symbol();

#endif