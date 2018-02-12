all: lab4docalc.l
	lex lab4docalc.l 
	yacc lab4docalc.y -d 
	gcc y.tab.c symtable.c -o lab4
