/*
 Header file for lab6ast.c

 Christian McGovern 
 March 28th, 2018
*/

#ifndef LAB6AST_H
#define LAB6AST_H
#include <stdio.h>
#include <ctype.h>
#include <malloc.h>

static int mydebug;

/* define the enumerated types for the AST.  THis is used to tell us what 
sort of production rule we came across */

/* this is a partial list of NODE types for the ASTNode */

enum ASTtype {
   PROGRAM,
   VARDEC,
   FUNCTDEC,
   PARAM,
   INTTYPE,
   IDENTIFER,
   BLOCK,
   EXPRSTMT,
   ASSIGNSTMT,
   IFSTMT,
   WHILESTMT,
   READSTMT,
   RETURNSTMT,
   WRITESTMT,
   EXPR,
   CALL,
   NUMBER,
   ARGLIST,

};

enum OPERATORS {
   PLUS,
   MINUS,
   TIMES,
   DIV,
   MOD,
   INTDEC,
   VOIDDEC,
   LESSTHANEQUAL,
   LESSTHAN,
   GREATERTHAN,
   GREATERTHANEQUAL,
   EQUAL,
   NOTEQUAL,
};

/* define a type AST node which will hold pointers to AST structs that will
   allow us to represent the parsed code 
*/
typedef struct ASTnodetype
{
     enum ASTtype type;
     enum OPERATORS operator;
     char * name;
     int value;
     struct ASTnodetype *next; /* I would call these Next left is usually the connector for statements */
     struct ASTnodetype *s0,*s1,*s2 ; /* used for holding IF and WHILE components -- not very descriptive */
} ASTnode;

ASTnode *ASTCreateNode(enum ASTtype);

void ASTattachleft(ASTnode *,ASTnode *);

void ASTprint(int ,ASTnode *);

ASTnode *program; 

#endif
