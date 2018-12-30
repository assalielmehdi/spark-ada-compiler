#include "error.h"

#include <stdlib.h>

#include <string.h>

#include <stdio.h>



#define MAXSIZE 100

static int NODEr = 0; //NumberOfDeclarationErrors

static smerror * ARRAYDECL[MAXSIZE];



smerror *_create_sm_error(SemanticErrorType et, int line, char * name){

  smerror *e = (smerror*) malloc (sizeof (smerror) );

  e->type = et;

  e->line = line;

  e->name = (char *) malloc (strlen(name));

  strcpy(e->name, name);

  return e;

}

void _create_sm_error_declaration(SemanticErrorType et, int line, char* name){

  ARRAYDECL[NODEr++]= _create_sm_error(et, line, name);

}

void _show_sm_error(SemanticErrorType et, int line, char* name){

	printf("ligne %d : %s ", line,  name);

  switch (et){

  case AlreadyDeclared: printf("AlreadyDeclared\n"); break;

  case BadlyInitialized:  printf("BadlyInitialized\n"); break;

  }

}

void _show_sm_errors(){

	for(int i=0;i<NODEr;i++){

		_show_sm_error(ARRAYDECL[i]->type,ARRAYDECL[i]->line,ARRAYDECL[i]->name);

	}

}


int nombre_sm_errors(){

	return NODEr;

}