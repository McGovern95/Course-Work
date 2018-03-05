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
   FUNCDEC,
   INTTYPE,
   IDENT,

};

enum OPERATORS {
   PLUS,
   MINUS,
   TIMES,
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
     struct ASTnodetype *left,*right; /* I would call these Next left is usually the connector for statements */
     struct ASTnodetype *s1,*s2 ; /* used for holding IF and WHILE components -- not very descriptive */
} ASTnode;

ASTnode *ASTCreateNode(enum ASTtype);

void ASTattachleft(ASTnode *,ASTnode *);

void ASTprint(int ,ASTnode *);

ASTnode *program; 

#endif