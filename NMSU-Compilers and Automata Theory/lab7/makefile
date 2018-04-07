all:	lab7ast.l lab7ast.y 
	lex lab7ast.l
	yacc -d lab7ast.y
	gcc y.tab.c lex.yy.c lab7ast.c symtable.c -o lab7sym
