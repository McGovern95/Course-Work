#	Compiler

 Description: 
	This Compiler takes in c code and output intels x64 NASM code, using LEX, YACC and C as backend

 Included Files:

	SRC: emit.c emit.h lab9.ast.c lab9ast.h lab9ast.l lab9ast.y symtable.c symtable.h makefile

	Test c files: test.c 
	
 Instuctions on using this program:

	Type make to compile 

	Example parameter input:
	./lab9 -o "output file name".asm < "your test c file"
	or for debugging 
	./lab9 -d -o "output file name".asm < "your test c file"

	with the supplied files you can use: 
	./lab9 -o output.asm < test.c

	The program will output asm code to parameter output. Reccomend .asm file so you can test the code.
	
	

