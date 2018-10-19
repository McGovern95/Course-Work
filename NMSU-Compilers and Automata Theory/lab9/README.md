#	NASM Compiler


 Description: 
	This Compiler takes in c code and output intels x64 NASM code, using LEX, YACC and C as backend

	Currently this compiler supports all syntax for c including arrays, functions, expressions, variables, etc.

 Included Files:

	SRC: emit.c emit.h ast.c ast.h lex.l yacc.y symtable.c symtable.h makefile

	Test c files: test.c 
	
 Instuctions on using this program:

	Type make to compile 

	Example parameter input:
	./NASMout -o "output file name".asm < "your test c file"
	or for debugging 
	./NASMout -d -o "output file name".asm < "your test c file"

	with the supplied files you can use: 
	./NASMout -o output.asm < test.c

	The program will output asm code to parameter output. Recomend .asm file so you can test the code.
	
	
