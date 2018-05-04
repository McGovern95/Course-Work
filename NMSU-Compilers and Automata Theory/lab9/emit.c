/*
  Lab9, "Emiter" file for NASM generation 

  Christian McGovern
  May 4, 2018
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include "lab9ast.h"
#include "symtable.h"
#include "emit.h"

char *L1, *L2;//temp variables for if/else and while
/*

	returns the max of offset and maxoffset used in yacc

*/
int max(int maxoffset, int offset){

	if(maxoffset > offset) return maxoffset;
	else return offset;

}//end max
/*

	adds the ending of a NASM program

*/
void emitReturn(FILE *output){
	fprintf(output,"\n\tmov rbp, [rsp] ;FUNC end restore old BP\n");
	fprintf(output,"\tmov rsp, [rsp+8] ;FUNC end restore old SP\n");
	fprintf(output,"\tmov rsp, rbp	 ;stack and BP need to be same on exit for main\n");
	fprintf(output,"\tret ;return\n");
}//end emitreturn();

//- 10% :(
void emitCall(ASTnode *p, FILE *output){


}//end emitCall();

/*

	handles the Identifiers from YACC
	
*/
void emitIdentifier(ASTnode *p, FILE *output){
        //array code
	if(p->s0 != NULL){
	   switch(p->s0->type){
	   case NUMBER:
		fprintf(output,"\tmov rbx, %d ;assign value to rbx\n",p->s0->value*WSIZE);
		break;
	   case IDENTIFER: emitIdentifier(p->s0,output);
		fprintf(output,"\tmov rbx, [rax] \n");
		fprintf(output,"\tshl rbx, 3 ;dereference array size \n"); 
		break;
	   case EXPR: emitExpr(p->s0,output);
		fprintf(output,"\tmov rbx, [rsp + %d] \n",p->s0->symbol->offset*WSIZE);
		fprintf(output,"\tshl rbx, 3 ;dereference array size \n");
                break;
	   case CALL: //emitCall(p->s0,output);
	        break;
	default: fprintf(output,"\t;BROKEN array idents\n"); 
	        break;
		
           }//end switch
	}//end if
        //identifier
        if(p->symbol->level == 0){
	 fprintf(output,"\n\tmov rax, %s ;name moved to rax\n", p->name);		
	}
	else{
	 fprintf(output,"\n\tmov rax, %d ;offset moved to rax\n", p->symbol->offset *WSIZE);
	 fprintf(output,"\tadd rax, rsp ;stack added to rax\n");	
	}
       //more array
	if(p->s0 != NULL)
	   fprintf(output,"\tadd rax, rbx ;add offset and stack pointer \n");//takes internal offset and adds it to main

}//end emitIdentifier
/*

	handles the expressions from YACC
	
*/
void emitExpr(ASTnode *p, FILE *output){

        //left side of expressions
	switch(p->s0->type){

	case NUMBER:
		fprintf(output,"\tmov rax, %d ;move NUMBER to rax, left \n",p->s0->value);
		break;
	case IDENTIFER: emitIdentifier(p->s0,output);
		fprintf(output,"\tmov rax, [rax] ;move value rax to rax, ident left \n");
		break;
	case EXPR: emitExpr(p->s0,output);
		fprintf(output,"\tmov rax, [rsp+%d] ;add offset to rsp and move to rax, expr left\n",p->s0->symbol->offset *WSIZE);
                break;
	case CALL: break;

	default:fprintf(output,"\t;BROKEN left side of expr\n"); break; 

       }//end switch

	fprintf(output,"\tmov [rsp+%d], rax ;move rax to rsp value with added offset, after left\n", p->symbol->offset*WSIZE);//Stores

        //right side of expressions
	switch(p->s1->type){
	case NUMBER:
		fprintf(output,"\tmov rbx, %d ;move NUMBER to rbx, right\n",p->s1->value);
		break;
	case IDENTIFER: emitIdentifier(p->s1,output);
		fprintf(output,"\tmov rbx, [rax] ;move value of rax to rbx, IDENT right\n");
		break;
	case EXPR: emitExpr(p->s1,output);
		fprintf(output,"\tmov rbx, [rsp+%d] ;add offset to rsp and move to rax, expr right\n",p->s1->symbol->offset*WSIZE);
		break;
	case CALL: 
		break;
	default:fprintf(output,"\t;BROKEN right side of expr\n");break;

	}//end switch

	fprintf(output,"\tmov rax, [rsp+%d] ;offset add to rsp value and move to rax\n",p->symbol->offset*WSIZE);//Stores
        //operators
	switch(p->operator){
	case PLUS:  fprintf(output,"\tadd rax, rbx ;EXPR ADD \n");
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
		    fprintf(output,"\tmov rbx, 1 ;set rbx to one to filter rax\n");
		    fprintf(output,"\tand rax, rbx ;filter RAX\n");
		    break;
	case NOTEQUAL: fprintf(output,"\tcmp rax, rbx ;EXPR NOTEQUAL \n");
		    fprintf(output,"\tsetne al ;EXPR EQUAL \n");
		    fprintf(output,"\tmov rbx, 1 ;set rbx to one to filter rax\n");
		    fprintf(output,"\tand rax, rbx ;filter RAX\n");
		    break;
	case LESSTHAN: fprintf(output,"\tcmp rax, rbx ;EXPR LESSTHAN \n");
		    fprintf(output,"\tsetl al ;EXPR LESSTHAN \n");
		    fprintf(output,"\tmov rbx, 1 ;set rbx to one to filter rax\n");
		    fprintf(output,"\tand rax, rbx ;filter RAX\n");
		    break;
	case GREATERTHAN: fprintf(output,"\tcmp rax, rbx ;EXPR GREATERTHAN \n");
		    fprintf(output,"\tsetg al ;EXPR GREATERTHAN \n");
		    fprintf(output,"\tmov rbx, 1 ;set rbx to one to filter rax\n");
		    fprintf(output,"\tand rax, rbx ;filter RAX\n");
		    break;
	case LESSTHANEQUAL:fprintf(output,"\tcmp rax, rbx ;EXPR LESSTHANEQUAL \n");
		    fprintf(output,"\tsetle al ;EXPR LESSTHANEQUAL \n");
		    fprintf(output,"\tmov rbx, 1 ;set rbx to one to filter rax\n");
		    fprintf(output,"\tand rax, rbx ;filter RAX\n");
		    break;

	case GREATERTHANEQUAL:fprintf(output,"\tcmp rax, rbx ;EXPR GREATERTHANEQUAL \n");
		    fprintf(output,"\tsetge al ;EXPR GREATERTHANEQUAL \n");
		    fprintf(output,"\tmov rbx, 1 ;set rbx to one to filter rax\n");
		    fprintf(output,"\tand rax, rbx ;filter RAX\n");
		    break;
	
	default: fprintf(output,"\tBROKEN operator\n"); break;

	}//end switch

	fprintf(output,"\tmov [rsp+%d], rax ;rax to value of rsp + offset end\n",p->symbol->offset*WSIZE);//Stores


}//end emitEXPR
/*

	large function which prints out the entire NASM code after starting 
        headers

*/
void emitText(ASTnode *p, FILE *output){
	if(p==NULL) return;
	
	     switch(p->type){
		case VARDEC: break;
		case FUNCTDEC: fprintf(output,"%s:\n",p->name);
			       CURRENT_FUNCTION=p->name;
		     	       if(strcmp("main", CURRENT_FUNCTION)==0)
				  fprintf(output,"\tmov rbp, rsp; for main only\n");
		     	       fprintf(output,"\tmov r8, rsp ;inital mov to r8\n");
		     	       fprintf(output,"\tadd r8, -%d ;add - total value to r8\n", p->value * WSIZE);
		     	       fprintf(output,"\tmov [r8], rbp ; initial move of base to value r8\n");
		     	       fprintf(output,"\tmov [r8+%d],rsp ;initial move of stack p to value r8 with added 8\n",WSIZE);
			       if(strcmp("main", CURRENT_FUNCTION)!=0)
				  fprintf(output,"\tmov rbp, rsp ;FUNC header RSP has to be at most rbp\n");
			       fprintf(output,"\tmov rsp, r8 ;FUNC header new sp\n");
		     	       emitText(p->s1, output);
		     	       emitReturn(output);
		            break;
		case PARAM: break;

	        case BLOCK: emitText(p->s0,output);
	                    emitText(p->s1,output);
			    break; 
		case RETURNSTMT: emitReturn(output); 
			    break;
		case READSTMT: emitIdentifier(p->s0,output);
			       fprintf(output,"\tGET_DEC 8, [rax] ;read into value of rax\n");
			    break;

		case WRITESTMT: if(p->s0!=NULL){ 
				   switch(p->s0->type){
				   case NUMBER: fprintf(output,"\tmov rsi, %d  ; load immediate value to rsi, writestmt\n", p->value);
                            	   break;
				   case IDENTIFER: emitIdentifier(p->s0, output);
						   fprintf(output,"\tmov rsi,[rax] ; load immediate value  to rsi IDENT\n");
				   break; 	
				   case EXPR: emitExpr(p->s0,output);
				      	      fprintf(output,"\tmov rsi, [rsp+%d] ;offset added to stack p mov to rsi, expr writestmt\n", p->s0->symbol->offset * WSIZE);
			           break;
				   case CALL: //emitCall(p->s0,output);
					      //fprintf(output,"\tmov rsi, rax ;function call value \n");
				default: fprintf(output, "\tBROKEN WRITESEMT\n"); break;

				}//end WRITESTMT switch
				fprintf(output,"\tPRINT_DEC 8, rsi   ;standard write value \n");
				fprintf(output,"\tNEWLINE	;standard newline\n");

			        }//end if
				if(p->name!=NULL){
				   fprintf(output,"\tPRINT_STRING %s  ;standard write value with string \n",p->string);
				   fprintf(output,"\tNEWLINE ;standard newline\n");
				 }
   
		   	    break;

                case EXPRSTMT: if(p->s0 != NULL){
			  	   switch(p->s0->type){
				   case NUMBER: fprintf(output,"\tmov rax, %d ; move NUMBER to rax \n",p->s0->value);
				   break;
				   case IDENTIFER: emitIdentifier(p->s0,output);
					           fprintf(output,"\tmov rax, [rax] ;move IDENTIFER memory address to rax\n");  
				   break;
				   case EXPR: emitExpr(p->s0,output);
					      fprintf(output,"\tmov rax, [rsp+%d] ; expression offset adding to stack and then move to rax\n",p->s0->symbol->offset*WSIZE);
				   break;
			           default: fprintf(output, "\tBROKEN exprstmt\n"); break;

			           }//end EXPRSTMT switch
		                   fprintf(output,"\tmov [rsp+%d],rax ;move rax to memory address of added offset to rsp \n",p->symbol->offset*WSIZE);
		               }//end if
                            break;
		case ASSIGNSTMT: emitText(p->s1,output);
			         emitIdentifier(p->s0,output);
				 fprintf(output,"\tmov rbx, [rsp+%d] ;offset of assignment added to rsp then moved to rax\n",p->s1->symbol->offset*WSIZE);
				 fprintf(output,"\tmov [rax], rbx ;move rbx to value of \n");
		            break; 

	        case IFSTMT: L1=CreateTemp();
			     L2=CreateTemp();

			     fprintf(output,"\n%s:   ;IF TOP target \n",L1);
		
		             switch(p->s0->type){
			     case NUMBER: fprintf(output,"\tmov rax, %d ;IF value loaded\n",p->s0->value);
		             break;
			     case IDENTIFER: emitIdentifier(p->s0,output);
			                     fprintf(output,"\tmov rax, [rax] ;IF expression IDENT\n");
		     	     break;
			     case CALL: fprintf(output,"IFSTMT CALL");
			     break;
			     case EXPR: emitExpr(p->s0,output);
			  	        fprintf(output,"\tmov rax, [rsp+%d] ;IF expression expr \n",p->s0->symbol->offset*WSIZE);
		     	     break;
               		     default: fprintf(output, "\tBROKEN IF switch\n"); break;
			     }//end IFSTMT switch

			     fprintf(output,"\tCMP rax, 0 ;IF compare\n");
		             fprintf(output,"\tJE %s, ;IF branch to ELSE\n",L2);
		
			     emitText(p->s1,output);//if stuff

			     fprintf(output,"\tJMP %s ;IF S1 end\n",L1);
		
			     fprintf(output,"\n%s:   ;ELSE target \n",L2);
		
			     emitText(p->s2,output);//all the else stuff
	
		            break; 
		case WHILESTMT: L1=CreateTemp();
			        L2=CreateTemp();
			        fprintf(output,"\n%s:   ;WHILE TOP target \n",L1);

			        switch(p->s0->type){
				case NUMBER: fprintf(output,"\tmov rax, %d ;WHILE value loaded\n",p->s0->value);
		     		break;
				case IDENTIFER: emitIdentifier(p->s0,output);
			        	        fprintf(output,"\tmov rax, [rax] ;WHILE expression IDENT\n");
		    	        break;
			        case CALL: fprintf(output,"CALL WHILE");
			    	break;
			        case EXPR: emitExpr(p->s0,output);
			   	           fprintf(output,"\tmov rax, [rsp+%d] ;WHILE expression expr \n",p->s0->symbol->offset*WSIZE);
		     	        break;
                
			       default: fprintf(output, "\tBROKEN while switch\n"); break;
			       }//end switch

			       fprintf(output,"\tCMP rax, 0 ;WHILE compare\n");
			       fprintf(output,"\tJE %s, ;WHILE branch out\n",L2);
	
			       emitText(p->s1,output);//puts inside of while loop
	
			       fprintf(output,"\tJMP %s ; WHILE jump back \n",L1);
			       fprintf(output,"\n%s:   ;WHILE END target \n",L2);
		                				 
		     	    break;
	        
	        case IDENTIFER:fprintf(output,"IDENT"); 
		            break;
		case NUMBER: fprintf(output,"NUM"); 
		            break;
		case CALL: fprintf(output,"CALL");
			    break;
		case ARGLIST: fprintf(output,"ARGLIST");
		            break;

		default: fprintf(output,";Case: not recognized");
			    break;


	      }//end emitText switch
	      emitText(p->next,output);
}//end emitText();
/*

	handles global variables
	
*/
void emitGlobals(ASTnode *p, FILE *output){

   if(p==NULL) return;

   if(p->type==VARDEC){
     if (p->value>0) 
        fprintf(output,"\tcommon %s %d\n",p->name,p->value*WSIZE);
     else
        fprintf(output, "\tcommon %s %d\n", p->name,WSIZE);
   }//end vardec if 

   emitGlobals(p->next,output);

}//end emitGlobals();
/*

	handles strings from YACC
	
*/
void emitStrings(ASTnode *p, FILE *output){
	
   if(p==NULL) return;
   //prints out global string on top for writing strings
   if(p->type == WRITESTMT){
       if(p->s0 == NULL) 
          fprintf(output,"%s: db %s, 0\t; global string\n",p->string,p->name);
   }//end if.
  
    if(p->next != NULL)
       emitStrings(p->next,output);
    if(p->s0 != NULL)
       emitStrings(p->s0,output);
    if(p->s1 != NULL)
       emitStrings(p->s1,output);
    if(p->s2 != NULL)
       emitStrings(p->s2,output);
}//end emitStrings(); 

void emitNASM(ASTnode *p, FILE *output){
        //syntax of starting NASM code
    	fprintf(output, "%%include \"io64.inc\" \n");
	emitGlobals(p, output);
	fprintf(output,"section .data \n");
	emitStrings(p, output);
	fprintf(output,"\n");
	fprintf(output,"section .text \n");
	fprintf(output, "	global main\n");
        //the whole thing basically 
	emitText(p,output);

}//end emitNASM();


