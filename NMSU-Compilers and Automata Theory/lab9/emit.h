#ifndef EMIT_H
#define EMIT_H
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>

#define WSIZE 8

int GLABEL;
char *CURRENT_FUNCTION;

void emitNASM(ASTnode *p, FILE *output);
void emitGlobals(ASTnode *p,FILE *output);
void emitStrings(ASTnode *p,FILE *output);
void emitText(ASTnode *p,FILE *output);
int max(int maxoffset, int offset);
void emitReturn(FILE *output);
void emitIdentifier(ASTnode *p,FILE *output);
void emitExpr(ASTnode *p, FILE *output);
void emitCall(ASTnode *p, FILE *output);

/*void emit(FILE *output, char *label, char *command, char *comment){

	char s[100];
	fprintf(fp, "%s\t%s\t\t%s\n", label, command, comment);
}*/

#endif
