#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include "lab9ast.h"
#include "symtable.h"
#include "emit.h"

int max(int maxoffset, int offset){
	if(maxoffset > offset) return maxoffset;
	else return offset;

}//end max

void emitReturn(FILE *output){
	fprintf(output,"\n\tmov rbp, [rsp] ;FUNC end restore old BP\n");
	fprintf(output,"\tmov rsp, [rsp+8] ;FUNC end restore old SP\n");
	fprintf(output,"\tmov rsp, rbp	 ;stack and BP need to be same on exit for main\n");
	fprintf(output,"\tret\n");
}//end emitreturn();

void emitIdentifier(ASTnode *p, FILE *output){

      struct SymbTab *s;
      s = p->symbol;
      if(s->level == 0)
	{
		fprintf(output,"\n\tmov rax, %s\n", s->name);	
		
	}
	else
	{
		fprintf(output,"\n\tmov rax, %d\n", WSIZE*2);
		fprintf(output,"\tadd rax, rsp\n");	
	}

}//end emitIdentifier

void emitExpr(ASTnode *p, FILE *output){
        //left side of expressions
	switch(p->s0->type){

	case NUMBER:
		fprintf(output,"\tmov rax, %d\n",p->s0->value);
		break;
	case IDENTIFER: emitIdentifier(p->s0,output);
		fprintf(output,"\tmov rax, [rax] \n");
		break;
	case EXPR: emitExpr(p->s0,output);
		fprintf(output,"\tmov rax, [rsp + %d] \n",p->s0->symbol->offset *WSIZE);
                break;
	default: break; 

       }//end switch

	fprintf(output,"\tmov [rsp + %d], rax\n", p->symbol->offset*WSIZE);
        //right side of expressions
	switch(p->s1->type){
	case NUMBER:
		fprintf(output,"\tmov rbx, %d\n",p->s1->value);
		break;
	case IDENTIFER: emitIdentifier(p->s1,output);
		fprintf(output,"\tmov rbx, [rax] \n");
		break;
	case EXPR: emitExpr(p->s0,output);
		fprintf(output,"\tmov rbx,[rsp+%d] \n",p->s1->symbol->offset*WSIZE);
		break;
	default: break;

	}//end switch

	fprintf(output,"\tmov rax, [rsp+%d]\n",p->symbol->offset*WSIZE);
        //operators
	switch(p->operator){
	case PLUS: fprintf(output,"\tadd rax, rbx ;EXPR ADD \n");
		    break;
	case MINUS: fprintf(output,"\tsub rax, rbx ;EXPR SUB \n");
		    break;
	case TIMES: fprintf(output,"\timul rax, rbx ;EXPR TIMES \n");
		    break;
	case DIV:   fprintf(output,"\txor rdx, rdx \n");
		    fprintf(output,"\tidiv rbx ;EXPR DIV \n");
		    break;
	case EQUAL: fprintf(output,"\tcmp rax, rbx ;EXPR EQUAL \n");
		    fprintf(output,"\tsete al ;EXPR EQUAL \n");
		    fprintf(output,"\tmov rbx, 1 ;set rbx to one to filter rax");
		    fprintf(output,"\tand rax, rbx ;filter RAX");
		    break;
	case NOTEQUAL: fprintf(output,"\tcmp rax, rbx ;EXPR NOTEQUAL \n");
		    fprintf(output,"\tsetne al ;EXPR EQUAL \n");
		    fprintf(output,"\tmov rbx, 1 ;set rbx to one to filter rax");
		    fprintf(output,"\tand rax, rbx ;filter RAX");
		    break;
	case LESSTHAN: fprintf(output,"\tcmp rax, rbx ;EXPR LESSTHAN \n");
		    fprintf(output,"\tsetl al ;EXPR LESSTHAN \n");
		    fprintf(output,"\tmov rbx, 1 ;set rbx to one to filter rax");
		    fprintf(output,"\tand rax, rbx ;filter RAX");
		    break;
	case LESSTHANEQUAL:fprintf(output,"\tcmp rax, rbx ;EXPR LESSTHANEQUAL \n");
		    fprintf(output,"\tsetle al ;EXPR LESSTHANEQUAL \n");
		    fprintf(output,"\tmov rbx, 1 ;set rbx to one to filter rax");
		    fprintf(output,"\tand rax, rbx ;filter RAX");
		    break;

	case GREATERTHANEQUAL:fprintf(output,"\tcmp rax, rbx ;EXPR GREATERTHANEQUAL \n");
		    fprintf(output,"\tsetge al ;EXPR GREATERTHANEQUAL \n");
		    fprintf(output,"\tmov rbx, 1 ;set rbx to one to filter rax");
		    fprintf(output,"\tand rax, rbx ;filter RAX");
		    break;
	
	default: break;

	}//end switch

	fprintf(output,"\tmov [rsp+%d], rax \n",p->symbol->offset*WSIZE);


}//end emitEXPR

void emitText(ASTnode *p, FILE *output){
	int level = 0;
	if(p==NULL) return;
	else{
	     switch(p->type){
		case VARDEC: break;
		case FUNCTDEC: 
		     fprintf(output,"%s:\n",p->name);
		     if(strcmp("main", p->name)==0)
			fprintf(output,"\tmov rbp, rsp\n");

		     fprintf(output,"\tmov r8, rsp\n");
		     fprintf(output,"\tadd r8, -%d\n", p->value * WSIZE);
		     fprintf(output,"\tmov [r8], rbp\n");
		     fprintf(output,"\tmov [r8+8],rsp\n");
		     fprintf(output,"\tmov rsp, r8\n");
		     emitText(p->s1, output);
		     emitReturn(output);

		     break;
		case PARAM: break;

	        case BLOCK: emitText(p->s1,output);
			    break; 
		case RETURNSTMT: emitReturn(output); 
				 break;
		case READSTMT: emitIdentifier(p->s0,output);
			       fprintf(output,"\tGET_DEC 8, [rax]\n");
			       break;

		case WRITESTMT: if(p->s0!=NULL){ 
				 switch(p->s0->type){
				 case NUMBER:
				 fprintf(output,"\tmov rsi, %d  ; load immediate value\n", p->s1->value);
                                 break;
				 case IDENTIFER: emitIdentifier(p->s0, output);
						 fprintf(output,"\tmov rsi,[rax] ; load immediate value \n");
				 break; 	
				 case EXPR: emitExpr(p->s0,output);
				      fprintf(output,"\tmov rsi, [rsp+%d] \n", p->s0->symbol->offset * WSIZE);
			                    break;
				 default: break;

				}//end switch
				fprintf(output,"\tPRINT_DEC 8, rsi   ;standard write value \n");
				fprintf(output,"\tNEWLINE	;standard newline\n");
			   }//end if
			if(p->name!=NULL){fprintf(output,"\tPRINT_STRING %s  ;standard write value \n",p->string);
				    	  fprintf(output,"\tNEWLINE ;standard newline\n");}

			      
		   break;

                case EXPRSTMT:
			  if(p->s0 != NULL){
			  switch(p->s0->type){
				case NUMBER: fprintf(output,"\tmov rax, %d \n",p->s0->value);
				  break;
				case IDENTIFER:emitIdentifier(p->s0,output);
					       fprintf(output,"\tmov rax, [rax] \n");  
				  break;
				case EXPR: emitExpr(p->s0,output);
					   fprintf(output,"\tmov rax, [rsp+%d] \n",p->s0->symbol->offset*WSIZE);
				  break;
			        default: break;

			  }
		           fprintf(output,"\tmov [rsp+%d],rax \n",p->symbol->offset*WSIZE);
		    }//end if
 break;
		case ASSIGNSTMT: emitText(p->s1,output);
			         emitIdentifier(p->s0,output);
				 fprintf(output,"\tmov rbx, [%d + rsp] \n",p->s1->symbol->offset*WSIZE);
				 fprintf(output,"\tmov [rax], rbx \n");
		     break; 

	        case IFSTMT: break; //THIS IS NEXT BUDDY
	        case IDENTIFER: break;
		case NUMBER: break;
		case CALL: break;
		case ARGLIST: break;

		default: fprintf(output,"not regocnized");break;


	      }//switch
	emitText(p->next,output);
   }//else

}//end emitText();

void emitGlobals(ASTnode *p, FILE *output){

	if(p==NULL) return;

	else{ 
	switch(p->type){
	     case VARDEC:  
		if(p->operator==INTDEC){
		   if (p->value>0)
		      fprintf(output,"\tcommon %s %d\n",p->name, WSIZE*(p->value));
		   else 
		      fprintf(output,"\tcommon %s %d\n",p->name,WSIZE);		
		}
		if(p->operator==VOIDDEC){
		   fprintf(output,"\tcommon %s %d\n", p->name,WSIZE);
		}
	     break;

	    default: break;
	   	
	}//end switch

	emitGlobals(p->next,output);
  }//END ELSE


}//end emitGlobals();

void emitStrings(ASTnode *p, FILE *output){
	if(p==NULL) return;
	else{
	 switch(p->type){
	   case VARDEC: emitStrings(p->next,output);
	   break;
	   case FUNCTDEC: emitStrings(p->s1,output);
	   break;
	   case BLOCK: emitStrings(p->s1,output);
	         break;
	   case WRITESTMT:
	     if(p->string!=NULL)
	     fprintf(output,"\n%s: db %s, 0", p->string, p->name);
	     emitStrings(p->next,output);
	     break;
	   case READSTMT:
	      emitStrings(p->next,output);
	     break;
	   case ASSIGNSTMT:
	    break;
	   default: break;		
	 }//end switch
      }//end else
 //emitStrings(p->next,output);
}//end emitStrings(); 

void emitNASM(ASTnode *p, FILE *output){

	fprintf(output, "%%include \"io64.inc\" \n");
	emitGlobals(p, output);
	fprintf(output,"section .data \n");
	emitStrings(p, output);
	fprintf(output,"\n");
	fprintf(output,"section .text \n");
	fprintf(output, "	global main\n");

	emitText(p,output);

}//end emitAST();


