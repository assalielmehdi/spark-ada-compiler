#ifndef error_H

#define error_H



typedef enum{

AlreadyDeclared,              

BadlyInitialized,

}SemanticErrorType;

typedef struct {

  char *name;

  int line;

  SemanticErrorType type;

} smerror;

smerror *_create_sm_error(SemanticErrorType et, int line, char * name);

void _create_sm_error_declaration(SemanticErrorType et, int line, char* name);

void _show_sm_error(SemanticErrorType et, int line, char* name);

void _show_sm_errors();

int nombre_sm_errors();



#endif