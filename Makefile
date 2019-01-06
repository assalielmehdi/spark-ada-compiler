all: main

lexical_analyzer: lexical_analyzer.lex
	flex lexical_analyzer.lex
	gcc -c lex.yy.c

symbols_table: tab_symb.h tab_symb.c
	gcc -c tab_symb.c

errors: errors.h errors.c
	gcc -c errors.c

syntactical_analyzer: tab_symb.h errors.h syntactical_analyzer.h syntactical_analyzer.c
	gcc -c syntactical_analyzer.c

main: lexical_analyzer symbols_table errors syntactical_analyzer
	gcc -o main lex.yy.o syntactical_analyzer.o errors.o tab_symb.o

clean:
	rm lex.yy.c
	rm *.o