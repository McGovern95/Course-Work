/*
 Header file for lab6ast.c
 Christian McGovern 
 March 28th, 2018
*/

#ifndef AST_H
#define AST_H

//prototype info
#include <stdio.h>
#include <malloc.h>

int mydebug;

/* Define the enumerated types for the AST. This is used to tell us what 
sort of production rule we came across */

/* this is a partial list of NODE types for the ASTNode */

enum ASTtype {
   VARDEC,
   FUNDEC,
   CMPDSTMT,
   PARAM,
   EXPRSTMT,
   ASIGNSTMT,
   SELECSTMT,
   ITRASTMT,
   RTRNSTMT,
   READSTMT,
   WRITESTMT,
   EXPR,
   IDENT,
   NUMB,
   FUNCALL,
   ARG
};


enum OPERATORS {
   PLUS,
   MINUS,
   TIMES,
   DIVIDE,
   MOD, 
   EQUAL, 
   NOTEQUAL, 
   LESSTHAN, 
   LESSTHANEQUAL, 
   GREATERTHANEQUAL, 
   GREATERTHAN, 
   INTDEC, 
   VOIDDEC, 

};

/* define a type AST node which will hold pointers to AST structs that will
   allow us to represent the parsed code 
*/
typedef struct ASTnodetype
{
     enum ASTtype type;
     enum OPERATORS istype;
     enum OPERATORS operator;
     char * name;
     char * label;
     int value;
     struct ASTnodetype *next;
     struct ASTnodetype *s1,*s2,*s3;
     struct SymbTab *symbol;
} ASTnode;

ASTnode *ASTCreateNode(enum ASTtype mytype);
void ASTattachleft(ASTnode *p,ASTnode *q);
void ASTprint(int level,ASTnode *p);
ASTnode *program;

#endif
