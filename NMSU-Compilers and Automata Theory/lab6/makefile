all: lab6ast.l lab6ast.y
	lex lab6ast.l
	yacc -d lab6ast.y
	gcc y.tab.c lex.yy.c lab6ast.c -o lab6ast