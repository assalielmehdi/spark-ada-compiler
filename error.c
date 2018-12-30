#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

#define MAX_ERRORS 100

int _errors_count = 0;
_semantic_error *_errors[MAX_ERRORS];

_semantic_error *_create_semantic_error(_semantic_error_type type, int line, char *name) {
  _semantic_error *e = (_semantic_error *) malloc(sizeof(_semantic_error));
  e->type = type;
  e->line = line;
  e->name = (char *) malloc(strlen(name) + 1);
  strcpy(e->name, name);
  return e;
}

void _add_semantic_error(_semantic_error_type type, int line, char *name) {
  _errors[_errors_count++] = _create_semantic_error(type, line, name);
}

void _show_semantic_error(_semantic_error *error) {
  printf("ligne %d : %s ", error->line, error->name);
  switch (error->type) {
    case ALREADY_DECLARED : 
      printf("Already Declared\n");
      break;
    case BADLY_INITIALIZED:
      printf("Badly Initialized\n");
      break;
  }
}

void _show_semantic_errors() {
  for(int i = 0; i < _errors_count; i++) {
		_show_semantic_error(_errors[i]);
	}
}

int _count_semantic_errors() {
	return _errors_count;
}