#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "pseudo_code.h"
#include "pseudo_code_parser.h"

void _interpreter_process(_pc_code pseudo_code, _pc_parser_data data, _pc_parser_labels labels);

#endif