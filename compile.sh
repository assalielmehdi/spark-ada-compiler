#!/bin/bash

# Script used to:
#   1. Generate .c file from .lex file.
#   2. Compile each of the generated file (lexical analyzer) and the syntactical analyzer .c file.
#   3. Generate executable file after editing links between .o files.

# How to use ?
#   1. Make sure the script has execution permission (+x)
#   2. run the following command: 
# ./compile.sh <my_flex_file.lex> <my_syntactic_analyzer_file.c> <my_executable_file_name>

flex "$1"
gcc -c lex.yy.c
gcc -c "$2"
file_name1=$(echo "$2" | cut -d '.' -f 1)
#file_name2=$(echo "$3" | cut -d '.' -f 1)
#file_name3=$(echo "$4" | cut -d '.' -f 1)
gcc -o "$3" lex.yy.o "$file_name1.o"
rm lex.yy.c *.o