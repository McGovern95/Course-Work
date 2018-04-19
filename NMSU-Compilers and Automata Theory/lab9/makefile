all:	lab9ast.l lab9ast.y 
	lex lab9ast.l
	yacc -d lab9ast.y
	gcc y.tab.c lex.yy.c lab9ast.c symtable.c emit.c -o lab9
