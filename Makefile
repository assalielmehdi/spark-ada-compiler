BASE_DIR := ${shell pwd}
TARGET_DIR := ${BASE_DIR}/target
IN_2_RI_DIR := ${BASE_DIR}/_01_in_2_ri
RI_2_PC_DIR := ${BASE_DIR}/_02_ri_2_pc
PC_2_OUT_DIR := ${BASE_DIR}/_03_pc_2_out

all: in_to_ri

in_to_ri: lexical_analyzer symbols_table errors syntactical_analyzer
	cd ${IN_2_RI_DIR}; \
	gcc -o main lex.yy.o syntactical_analyzer.o errors.o tab_symb.o; \
	mv main ${TARGET_DIR}/main

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

clean:
	rm ${IN_2_RI_DIR}/lex.yy.c
	rm ${IN_2_RI_DIR}/*.o