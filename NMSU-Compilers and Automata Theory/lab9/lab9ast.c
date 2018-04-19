/*   Abstract syntax tree codeS

     This code is used to define an AST node, 
    routine for printing out the AST
    defining an enumerated type so we can figure out what we need to
    do with this.  The ENUM is basically going to be every non-terminal
    and terminal in our language.

    Shaun Cooper February 2015

*/

/*
   Abstract syntax tree code 

   Code which takes in input code and outputs it into a 
   Abstract Syntax tree. 
  
  Christian McGovern 
  March 28th, 2018
*/

#include<stdio.h>
#include<malloc.h>
#include <ctype.h>
#include "lab9ast.h"
#include "symtable.h"


/* uses malloc to create an ASTnode and passes back the heap address of the newly created node */
ASTnode *ASTCreateNode(enum ASTtype mytype)
{
    ASTnode *p;
    //if (mydebug) fprintf(stderr,"Creating AST Node \n");
    p=(ASTnode *)malloc(sizeof(ASTnode));
    p->type=mytype;
    p->next=NULL;
    p->s0=NULL;
    p->s1=NULL;
    p->s2=NULL;
    p->value=0;
    p->symbol=NULL;
    p->name=NULL;
    p->string=NULL;
    return(p);
}

/* attach q to the left most part of p */
void ASTattachleft(ASTnode *p,ASTnode *q)
{   
        //not used yet
        /*while(p->next ==NULL){
            p = p->next;
            p->next = q;
        }*/
        
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
	//beginning of case statements
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

                     if (p->s0 == NULL){
                        printf(" (VOID) ");
                     }
                     else{
                        printf("( \n");
                        ASTprint(level+2,p->s0);
                        printf(") ");
                     }
                     printf("\n");
                     ASTprint(level+2,p->s1);
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
                    ASTprint(level+1,p->s1);
                    break;

        case ASSIGNSTMT : printf("ASSIGNMENT STATEMENT \n");

                    ASTprint(level+1,p->s0);
                    ASTprint(level+1,p->s1);
                    break;

        case IFSTMT : printf("IF STATEMENT \n");

                    ASTprint(level+1,p->s0);
                    ASTprint(level+2,p->s1);
                    //else 
                    if(p->s2 != NULL){
                        for (i=0;i<level;i++) printf(" ");
                        printf("ELSE STATEMENT \n");
                        ASTprint(level+2,p->s2);
                    }
                    break;

        case WHILESTMT : printf("WHILE STATEMENT \n");

                         ASTprint(level+1,p->s0);
                         ASTprint(level+2,p->s1);
                    break;


        case ARGLIST : printf("ARGLIST \n");

                       ASTprint(level+1,p->s0);
                    break;

        case WRITESTMT : printf("WRITE STMT \n");

                         ASTprint(level+1,p->s0);
                    break;  

        case READSTMT : printf("READ STATEMENT \n");

                        ASTprint(level+1,p->s0);
                    break;

        case RETURNSTMT :
                         if(p->s0 == NULL){
                            printf("RETURN STATEMENT \n");
                            //ASTprint(level+1,p->s0);
                         }
                         else{
                            printf("RETURN STATEMENT with expression: \n");
                            ASTprint(level+1,p->s0);
                         }   
                    break;

        case CALL : printf("CALL: %s \n", p->name);

                    ASTprint(level+1,p->s0);
                    break;

        case EXPRSTMT : printf("EXPRESSION STATEMENT \n");
                        
                        ASTprint(level+1,p->s0);
                    break;

        case EXPR :
                    if(p->operator == PLUS)
                        printf("EXPR + \n");
                    if(p->operator == MINUS)
                        printf("EXPR - \n");
                    if(p->operator == TIMES)
                        printf("EXPR * \n");
                    if(p->operator == DIV)
                        printf("EXPR / \n");
                    if(p->operator == LESSTHANEQUAL)
                        printf("EXPR <= \n");
                    if(p->operator == LESSTHAN)
                        printf("EXPR < \n");
                    if(p->operator == GREATERTHAN)
                        printf("EXPR > \n");
                    if(p->operator == GREATERTHANEQUAL)
                        printf("EXPR >= \n");
                    if(p->operator == EQUAL)
                        printf("EXPR = \n");
                    if(p->operator == NOTEQUAL)
                        printf("EXPR != \n");

                    ASTprint(level+1,p->s0);
                    ASTprint(level+1,p->s1);
                    break;

        case NUMBER : printf("NUMBER with value: %d \n", p->value);

                      ASTprint(level+1,p->s0);
                      break;

        case IDENTIFER: 
                        if (p->s0 == NULL){
                        printf("IDENTIFER %s \n",p->name);
                        ASTprint(level+1,p->s0);
                        }
                        else{
                            printf("IDENTIFER %s \n",p->name);
			    for (i=0;i<level;i++) printf(" ");
                            printf("array reference [ \n");
                            ASTprint(level+1,p->s0);
                            for (i=0;i<level;i++) printf(" ");
                            printf("] end array \n");
                        }
                      break;

        default: printf("unknown type in ASTprint\n");
                
       }
     }
     //won't print ast without this
     ASTprint(level, p->next);
}//end ASTprint



/* dummy main program so I can compile for syntax error independently  
main()
{
}
/* */
