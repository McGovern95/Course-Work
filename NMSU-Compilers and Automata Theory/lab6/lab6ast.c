/*   Abstract syntax tree code

     This code is used to define an AST node, 
    routine for printing out the AST
    defining an enumerated type so we can figure out what we need to
    do with this.  The ENUM is basically going to be every non-terminal
    and terminal in our language.

    Shaun Cooper February 2015

*/

#include<stdio.h>
#include<malloc.h>
#include <ctype.h>
#include "lab6ast.h"
static int mydebug;

/* uses malloc to create an ASTnode and passes back the heap address of the newly created node */
ASTnode *ASTCreateNode(enum ASTtype mytype)
{
    ASTnode *p;
    if (mydebug) fprintf(stderr,"Creating AST Node \n");
    p=(ASTnode *)malloc(sizeof(ASTnode));
    p->type=mytype;
    p->left=NULL;
    p->right=NULL;
    p->s1=NULL;
    p->s2=NULL;
    p->value=0;
    return(p);
}

/* attach q to the left most part of p */
void ASTattachleft(ASTnode *p,ASTnode *q)
{
//... missing
        ;
}



/*  Print out the abstract syntax tree */
void ASTprint(int level,ASTnode *p)
{
   int i;
   if (p == NULL ) return;
   else
     { 
     for (i=0;i<level;i++) printf(" "); /* print tabbing blanks */
      
       switch (p->type) {
        case VARDEC :  printf("Variable declaration with name %s",p->name);
                     if (p->value > 0)
                        printf("[%d]",p->value);
                     printf("\n");
                     break;

        default: printf("unknown type in ASTprint\n");


       }
     }

}



/* dummy main program so I can compile for syntax error independently  
main()
{
}
/* */
