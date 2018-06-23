/*
   Abstract syntax tree code 
   Code which takes in input code and outputs it into a 
   Abstract Syntax tree. 
  
  Christian McGovern 
  March 28th, 2018
*/

#include "ast.h"

/* uses malloc to create an ASTnode and passes back the heap address of the newly created node */
ASTnode *ASTCreateNode(enum ASTtype mytype)
{
    ASTnode *p;
    //if (mydebug) fprintf(stderr,"Creating AST Node \n");
    p=(ASTnode *)malloc(sizeof(ASTnode));
    p->type=mytype;
    p->next=NULL;
    p->s1=NULL;
    p->s2=NULL;
    p->s3=NULL;
    p->value=0; /*elements in array*/
    p->name=NULL;
    p->label=NULL;
    p->symbol=NULL;
    return(p);
}

void PT(int level) {
  int i;
     for (i=0;i<level;i++) printf("   "); /* print tabbing blanks */
} // of PT

/*  Print out the abstract syntax tree */
void ASTprint(int level,ASTnode *p)
{
   int i;
   if (p == NULL ) return;
   else
     { 
     PT(level);
      
     switch (p->type) {

        case VARDEC :  

		printf("variable ");
		if(p->operator == VOIDDEC)
			printf("void ");
		else
			printf("int ");
		printf("%s ", p->name);
                if (p->value > 0)
                	printf("[%d]",p->value);
                printf("\n");
                break;

        case FUNDEC :
		
		if(p->operator == VOIDDEC)
			printf("void ");
		else
			printf("int ");
		printf("function %s\n", p->name);
		if(p->s1 == NULL)
			printf("void\n");
		else
			ASTprint(level+1, p->s1);/*paramlist*/
		printf("\n");
	        ASTprint(level+1, p->s2);/*paramlist*/
		break;

	case CMPDSTMT :
		printf("Block \n");

		ASTprint(level+1, p->s1);/*local decs*/
		ASTprint(level+1, p->s2);/*statement list*/		
		
		break;

	case PARAM :

		printf("parameter ");
		if(p->operator == VOIDDEC)
			printf("   void ");
		else
			printf("int ");
		printf("%s", p->name);
		if(p->value < 0)
			printf("[]");
		printf("\n");
		
		break;

	case EXPRSTMT :
		
		printf("expression statement \n");
		ASTprint(level+1, p->s1);/*expression statement*/		
		break;

	case ASIGNSTMT :
		
		printf("assignment statement \n");
		ASTprint(level+1, p->s1);/*var*/
		printf(" = ");
		ASTprint(level+1, p->s2);/*expression statement*/
		break;

	case SELECSTMT :
		
		printf("selection statement\n"); 
		PT(level);
		printf("if ");
		ASTprint(level, p->s1);/*expression*/
		printf(" \n");
		ASTprint(level+1, p->s2);/*statement*/
		if(p->s3 != NULL){
			PT(level);
			printf("else\n");
			ASTprint(level+1, p->s3);/*else statement*/
		}
		break;

	case ITRASTMT :
		
		printf("iteration statement\n");
		PT(level);
		printf("while ");
		ASTprint(level+1, p->s1);/*expression*/
		printf("\n");
		ASTprint(level+1, p->s2);/*statement*/
		break;

	case RTRNSTMT :
		
		if(p->s1 == NULL)
			printf("return\n");
		else
			printf("return \n");
			ASTprint(level+1, p->s1);/*expression*/
			printf("\n");
		break;

	case READSTMT :
		
		printf("read \n");
		ASTprint(level+1, p->s1);/*var*/
		printf("\n");
		break;

	case WRITESTMT :
		
		printf("write \n");
		ASTprint(level+1, p->s1);/*expression*/
		printf("\n");
		break;

	case EXPR :
		
		printf("expression ");
		switch(p->operator){
			case LESSTHANEQUAL :
				printf("<= ");
				break;
			case LESSTHAN :
				printf("< ");
				break;
			case GREATERTHAN :
				printf("> ");
				break;
			case GREATERTHANEQUAL :
				printf(">= ");
				break;
			case EQUAL :
				printf("== ");
				break;
			case NOTEQUAL :
				printf("!= ");
				break;
			case PLUS :
				printf("+ ");
				break;
			case MINUS :
				printf("- ");
				break;
			case TIMES :
				printf("* ");
				break;
			case DIVIDE :
				printf("/ ");
				break;
			default : printf("unknown operator");
		} // of switch
		printf("\n");
		ASTprint(level+1, p->s1);/*additive expression / term / factor/ num/ var/ call*/
		printf("\n");
		ASTprint(level+1, p->s2);/*additive expression / term / factor/ num/ var/ call*/
		printf("\n");
		break;

	case IDENT :
		
		printf("%s ", p->name);
		if(p->s1 != NULL){
			printf("[");
			ASTprint(0, p->s1);/*expression*/
			printf("]");
		}
		//printf("\n");
		break;

	case NUMB :
		printf("number ");
		printf("%d", p->value);		
		break;

	case FUNCALL :
		
		printf("function call %s ", p->name);
		ASTprint(level, p->s1);/*args*/
		printf("\n");
		break;

	case ARG :
		
		ASTprint(level, p->s1);/*expression*/
		break;

        default: printf("unknown type in ASTprint\n");
	
     }//end switch
     ASTprint(level,p->next);
     }//end else

} // of ASTprint


