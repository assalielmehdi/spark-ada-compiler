/**
 * Author: El Mehdi ASSALI
 */

#ifndef PSEUDO_CODE_GENERATOR_H
#define PSEUDO_CODE_GENERATOR_H

#include "ast.h"
#include "cfg.h"

void _pc_generator_ast_to_pc(_ast root);

void _pc_generator_cfg_to_pc(_cfg_list_inst list_inst);

#endif