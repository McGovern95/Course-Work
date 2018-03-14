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
    p->next=NULL;
    p->s0=NULL;
    p->s1=NULL;
    p->s2=NULL;
    p->value=0;
    return(p);
}

/* attach q to the left most part of p */
void ASTattachleft(ASTnode *p,ASTnode *q)
{
        while(p->next ==NULL){
            p = p->next;
            p->next = q;
        }
        
}



/*  Print out the abstract syntax tree */
void ASTprint(int level,ASTnode *p)
{
   int i;
   if (p == NULL ) return;
   else
     { 
     for (i=0;i<level;i++) printf("\t"); /* print tabbing blanks */
      
       switch (p->type) {

        case VARDEC :  printf("Variable ");
                     if(p->operator == INTDEC)
                        printf("INT");
                     if(p->operator == VOIDDEC)
                           printf("VOID");
                        printf(" %s",p->name);
                     if (p->value > 0)
                        printf("[%d]",p->value);
                     printf("\n");
                     break;

        case FUNCTDEC : 
                     if(p->operator == INTDEC)
                        printf("INT ");
                     if(p->operator == VOIDDEC)
                           printf("VOID ");

                     printf("FUNCTION %s \n",p->name);

                     if (p->s1 == NULL){
                        printf(" (VOID) ");
                     }
                     else{
                        printf("{ \n");
                        ASTprint(level+2,p->s1);
                        printf("} ");
                     }
                     printf("\n");
                     ASTprint(level+2,p->s0);
                     break;

        case PARAM : printf("PARAMETER ");

                     if(p->operator == INTDEC)
                        printf("INT ");
                     if(p->operator == VOIDDEC)
                        printf("VOID ");
                    
                    printf("%s \n",p->name);
                    ASTprint(level+1,p->s0);
                    break;



        case BLOCK : printf("BLOCK STATEMENT \n");
                    ASTprint(level+1,p->s0);
                    break;

        case ASSIGNSTMT : printf("ASSIGNMENT STATEMENT \n");
                    ASTprint(level+1,p->s0);
                    ASTprint(level+1,p->s1);
                    break;

        case IFSTMT : printf("IF STATEMENT \n");
                    ASTprint(level+1,p->s0);
                    ASTprint(level+2,p->s1);
                    if(p->s2 != NULL){
                        printf("ELSE \n");
                        ASTprint(level+2,p->s2);
                    }
                    break;


        case ARGLIST : printf("ARGLIST\n");
                       ASTprint(level+1,p->s0);
                    break;

        case READSTMT : printf("READ STATEMENT \n");
                        ASTprint(level+1,p->s0);
                    break;

        case RETURNSTMT : printf("RETURN STATEMENT");
                          ASTprint(level+1,p->s0);
                    break;

        case CALL : printf("CALL: %s \n", p->name);
                    ASTprint(level+1,p->s0);
                    break;

        case EXPRSTMT : printf("EXPR STMT \n");
                        ASTprint(level+1,p->s0);
                    break;
        //where all the case statements go: 

        default: printf("unknown type in ASTprint\n");


       }
     }
     ASTprint(level -1, p->next);
}//end ASTprint



/* dummy main program so I can compile for syntax error independently  
main()
{
}
/* */
