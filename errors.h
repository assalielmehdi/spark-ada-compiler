#ifndef ERROR_H
#define ERROR_H

typedef enum {
  ALREADY_DECLARED,
  BADLY_INITIALIZED,
  NOT_DECLARED,
  NOT_INITIALIZED
} _semantic_error_type;

typedef struct {
  char *name;
  int line;
  _semantic_error_type type;
} _semantic_error;

_semantic_error *_create_semantic_error(_semantic_error_type type, int line, char *name);

void _add_semantic_error(_semantic_error_type type, int line, char *name);

void _show_semantic_error(_semantic_error *error);

void _show_semantic_errors();

int _count_semantic_errors();

#endif