BASE_DIR := ${shell pwd}
TARGET_DIR := ${BASE_DIR}/target
IN_2_RI_DIR := ${BASE_DIR}/_01_in_2_ri
RI_2_PC_DIR := ${BASE_DIR}/_02_ri_2_pc
PC_2_OUT_DIR := ${BASE_DIR}/_03_pc_2_out

all: compile clean

compile: in_to_ri pc_to_out

# Compile files in _01_in_2_ri directory

in_to_ri: lexical_analyzer ast symbols_table errors syntactical_analyzer
	cd ${IN_2_RI_DIR}; \
	gcc -o compiler lex.yy.o syntactical_analyzer.o errors.o tab_symb.o ast.o; \
	mv compiler ${TARGET_DIR}/compiler

lexical_analyzer:
	cd ${IN_2_RI_DIR}; \
	flex _lexical_analyzer.lex; \
	gcc -c lex.yy.c

symbols_table:
	cd ${IN_2_RI_DIR}; \
	gcc -c tab_symb.c

errors:
	cd ${IN_2_RI_DIR}; \
	gcc -c errors.c

syntactical_analyzer:
	cd ${IN_2_RI_DIR}; \
	gcc -c syntactical_analyzer.c

ast:
	cd ${IN_2_RI_DIR}; \
	gcc -c ast.c

# ----------------------------------------------

# Compile files in _03_pc_2_out directory

pc_to_out: pseudo_code_lex pseudo_code interpreter
	cd ${PC_2_OUT_DIR}; \
	gcc -o interpreter lex.yy.o interpreter.o pseudo_code.o; \
	mv interpreter ${TARGET_DIR}/interpreter

pseudo_code_lex:
	cd ${PC_2_OUT_DIR}; \
	flex _pseudo_code.lex; \
	gcc -c lex.yy.c

pseudo_code:
	cd ${PC_2_OUT_DIR}; \
	gcc -c pseudo_code.c

interpreter:
	cd ${PC_2_OUT_DIR}; \
	gcc -c interpreter.c

# ----------------------------------------------

clean: clean_in_to_ri clean_pc_to_out

# Compile files in _01_in_2_ri directory

clean_in_to_ri:
	rm ${IN_2_RI_DIR}/lex.yy.c
	rm ${IN_2_RI_DIR}/*.o

# ---------------------------------------

# Compile files in _03_pc_2_out directory

clean_pc_to_out:
	rm ${PC_2_OUT_DIR}/lex.yy.c
	rm ${PC_2_OUT_DIR}/*.o

# ---------------------------------------