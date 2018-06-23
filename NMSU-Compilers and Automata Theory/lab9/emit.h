#ifndef EMITAST_H
#define EMITAST_H

//prototype info
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>

#include "ast.h"

#define WSIZE 8

char *currentFunction;

void emitNASM(ASTnode *p, FILE *out);
void ASTglobals(ASTnode *p, FILE *out);
void ASTstrings(ASTnode *p, FILE *out);
void ASTtext(ASTnode *p, FILE *out);
void emitExpr(ASTnode *p, FILE *out);
void emitIdent(ASTnode *p, FILE *out);
void emitFunction(ASTnode *p, FILE *out);
void evaluateArgs(ASTnode *p, FILE *out);
void emitArgsToParams(ASTnode *arg, ASTnode *param, int functionSize, FILE *out);
void emitReturn(ASTnode *p, FILE *out);

#endif
