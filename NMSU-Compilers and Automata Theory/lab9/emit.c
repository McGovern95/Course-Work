/*
  Lab9, "Emiter" file for NASM generation 
  Christian McGovern
  May 4, 2018
*/

#include "emit.h"

//calls what to print at the correct time
void emitNASM(ASTnode *p, FILE *out){

	if(p==NULL) return;
	fprintf(out, "%%include \"io64.inc\"\n\n");
	ASTglobals(p, out);
	fprintf(out, "\nsection .data\n\n");
	ASTstrings(p, out);
	fprintf(out, "\nsection .text\n\n");
	fprintf(out, "\tglobal main\n\n");
	ASTtext(p, out);

}

//prints global variables
void ASTglobals(ASTnode *p, FILE *out){
	if(p==NULL)
		return;
	if((p->type == VARDEC) && (p->value == 0)){
		fprintf(out, "common\t%s\t%d\n", p->name, WSIZE);
	}
	else if((p->type == VARDEC) && (p->value > 0)){
		fprintf(out, "common\t%s\t%d\n", p->name, (p->value * WSIZE));
	}
	ASTglobals(p->next, out);
}

//prints strings
void ASTstrings(ASTnode *p, FILE *out){
	if(p==NULL)
		return;
	if((p->type == WRITESTMT) && (p->name != NULL)){
		fprintf(out, "%s:\tdb\t%s,%d\t;global string\n",p->label,p->name,0);
	}
	ASTstrings(p->next, out);
	ASTstrings(p->s1, out);
	ASTstrings(p->s2, out);
	ASTstrings(p->s3, out);
}

void ASTtext(ASTnode *p, FILE *out){
	
	if (p == NULL) 
		return;
	else{ 
		char *L1, *L2;

		switch (p->type) {

			case VARDEC :  
				break;

			case FUNDEC :
				/*header*/
				currentFunction = p->name;
				fprintf(out, "%s:\t\t;Start of Function\n",p->name);
				if(strcmp(p->name, "main") == 0)
					fprintf(out, "\tmov\trbp, rsp\t;For main only\n");
				fprintf(out, "\tmov\tr8, rsp\t;FUNC header RSP has to be at most RBP\n");
				fprintf(out, "\tadd\tr8, -%d\t;adjust Stack Pointer for Activation record\n",p->value * WSIZE);
				fprintf(out, "\tmov\t[r8], rbp\t;FUNC header store old BP\n");
				fprintf(out, "\tmov\t[r8+8], rsp\t;FUNC header store old SP\n");
				if(strcmp(p->name, "main") != 0)
					fprintf(out, "\tmov\trbp, rsp\t;FUNC header TSP has to be at most rbp\n");
				fprintf(out, "\tmov\trsp, r8\t;FUNC header new SP\n");

				ASTtext(p->s2, out);

				/*footer*/
				fprintf(out, "\txor\trax, rax\t;nothing to return\n");
	
				fprintf(out,"\n\tmov\trbp, [rsp]\t;FUNC end restore old BP\n");
				fprintf(out,"\tmov\trsp, [rsp+8]\t;FUNC end restore old SP\n");
				if(strcmp(currentFunction, "main") == 0)
					fprintf(out,"\tmov\trsp, rbp\t;stack and BP need to be same on exit for main\n");
				fprintf(out,"\tret\n");
				
				break;

			case CMPDSTMT :
				ASTtext(p->s1, out);
				ASTtext(p->s2, out);
				break;

			case PARAM :
				break;

			case EXPRSTMT :
				if(p->s1 != NULL){
					switch(p->s1->type){
						case NUMB: 
							fprintf(out, "\tmov\trax, %d \t;get identifier offset\n", p->s1->value);
							break;
						case IDENT: 
							emitIdent(p->s1, out);
							fprintf(out, "\tmov\trax, [rax]\t;expression ident\n");
							break;
						case EXPR: 
							emitExpr(p->s1, out);
							fprintf(out, "\tmov\trax, [rsp+%d]\t;expressionstmt expr\n", p->s1->symbol->offset*WSIZE);
							break;
						case FUNCALL:
							emitFunction(p->s1, out);
							break;
						default:
							fprintf(out, "\tBAD EXPRSTMT\n");
							break;
					}
					fprintf(out, "\tmov\t[rsp+%d], rax\t;store rhs\n", p->symbol->offset*WSIZE);
				}		
				break;

			case ASIGNSTMT :
				ASTtext(p->s2, out);
				emitIdent(p->s1, out);
				fprintf(out, "\tmov\trbx, [rsp+%d]\t;fetch rhs of assign temporarily\n", p->s2->symbol->offset*WSIZE);
				fprintf(out, "\tmov\t[rax], rbx\t;move rhs into rax\n");
				break;

			case SELECSTMT :

				L1=CreateLabel();
				L2=CreateLabel();
				
				switch(p->s1->type){
					case NUMB:
						fprintf(out, "\tmov\trax, %d \t;If value loaded\n", p->s1->value);
						break;
						
					case IDENT:
						emitIdent(p->s1, out);
						fprintf(out, "\tmov\trax, [rax]\t;if expression IDENT\n");
						break;
						
					case FUNCALL:
						emitFunction(p->s1, out);
						break;
						
					case EXPR:
						emitExpr(p->s1, out);
						fprintf(out, "\tmov\trax, [rsp+%d]\t;if expression expr\n", p->s1->symbol->offset*WSIZE);
						break;
						
					default:
						fprintf(out, "\t;Bad if\n");
						break;
				}
				
				fprintf(out, "\tCMP\trax, 0\t;if compare\n");
				fprintf(out, "\tJE\t%s, \t;if branch to else\n", L1);
				
				ASTtext(p->s2, out);
				
				fprintf(out, "\tJMP\t%s\t;If s1 end\n", L2);
				fprintf(out, "\n%s:\t;else target\n", L1);
				
				ASTtext(p->s3, out);
				
				fprintf(out, "\n%s:\t;IF bottom target\n", L2);
				
				break;

			case ITRASTMT :
				L1=CreateLabel();
				L2=CreateLabel();
				
				fprintf(out, "\n%s:\t;while top target\n", L1);
				
				switch(p->s1->type){
				
					case NUMB:
						fprintf(out, "\tmov\trax, %d \t;while value loaded\n", p->s1->value);
						break;
					case IDENT:
						emitIdent(p->s1, out);
						fprintf(out, "\tmov\trax, [rax]\t;while expression ident\n");
						break;
					case FUNCALL:
						emitFunction(p->s1, out);
						break;
					case EXPR:
						emitExpr(p->s1, out);
						fprintf(out, "\tmov\trax, [rsp+%d]\t;while expression expr\n", p->s1->symbol->offset*WSIZE);
						break;
					default:
						fprintf(out, "\t;bad while\n");
						break;
				}
				
				fprintf(out, "\tCMP\trax, 0\t;while compare\n");
				fprintf(out, "\tJE\t%s,\t;while branch\n", L2);
				
				ASTtext(p->s2, out);
				
				fprintf(out, "\tJMP\t%s\t;while jump back \n", L1);
				fprintf(out, "\n%s:\t;while end target\n", L2);
			
				break;

			case RTRNSTMT :
				emitReturn(p, out);
				break;

			case READSTMT :
				emitIdent(p->s1, out);
				fprintf(out, "\tGET_DEC\t8, [rax]\t;readstmt\n");
				break;

			case WRITESTMT :
				if(p->s1 != NULL){
				
					switch(p->s1->type){
					
						case NUMB:
							fprintf(out, "\tmov\trsi, %d \t;load immediate value\n", p->s1->value);
							break;
							
						case IDENT:
							emitIdent(p->s1, out);
							fprintf(out, "\tmov\trsi, [rax]\t;load immediate value\n");
							break;
						
						case EXPR:
							emitExpr(p->s1, out);
							fprintf(out, "\tmov\trsi, [rsp+%d]\t;load expr value from expr mem\n", p->s1->symbol->offset*WSIZE);
							break;
						
						case FUNCALL:
							emitFunction(p->s1, out);
							fprintf(out, "\tmov\trsi, rax\t;store function return into rsi\n");
							break;
						
						default:
							fprintf(out, "\t;bad WRITESTMT\n");
							break;
					
					}
					
					fprintf(out, "\tPRINT_DEC\t8, rsi\t;standard write value\n");
					fprintf(out, "\tNEWLINE\t\t;standard newline\n");
				
				}
				
				if(p->name != NULL){
					fprintf(out, "\tPRINT_STRING\t%s\t;standard write value\n", p->label);
					fprintf(out, "\tNEWLINE\t\t;standard newline\n");
				}
				
				break;

			case EXPR :
				fprintf(out, "\t;EXPR\n");
				break;

			case IDENT :
				fprintf(out, "\t;IDENT\n");
				break;

			case NUMB :	
				fprintf(out, "\t;NUMB\n");
				break;

			case FUNCALL :
				emitFunction(p->s1, out);
				break;

			case ARG :
				fprintf(out, "\t;ARG\n");
				break;

			default: fprintf(out, "\t;unknown type in ASTtext\n");

		}//end switch

		ASTtext(p->next, out);

	}//end else
}//end ASTtext()

void emitExpr(ASTnode *p, FILE *out){

	//left side
	switch(p->s1->type){
	
		case NUMB:
			fprintf(out, "\tmov\trax, %d \t;get identifier offset\n", p->s1->value);
			break;
		
		case IDENT:
			emitIdent(p->s1, out);
			fprintf(out, "\tmov\trax, [rax]\t;LHS expression is identifier\n");
			break;
		
		case EXPR:
			emitExpr(p->s1, out);
			fprintf(out, "\tmov\trax, [rsp+%d]\t;fetch LHS of expression from memory\n", p->s1->symbol->offset * WSIZE);
			break;
		
		case FUNCALL:
			emitFunction(p->s1, out);
			break;
		
		default:
			fprintf(out, "\t;bad left side\n");
			break;
	
	}//end left switch
	
	//store
	fprintf(out, "\tmov\t[rsp+%d], rax\t;store rax\n", p->symbol->offset * WSIZE);
	
	//right side
	switch(p->s2->type){
	
		case NUMB:
			fprintf(out, "\tmov\trbx, %d \t;get identifier offset\n", p->s2->value);
			break;
		
		case IDENT:
			emitIdent(p->s2, out);
			fprintf(out, "\tmov\trbx, [rax]\t;RHS expression is identifier\n");
			break;
		
		case EXPR:
			emitExpr(p->s2, out);
			fprintf(out, "\tmov\trbx, [rsp+%d]\t;fetch RHS of expression from memory\n", p->s2->symbol->offset * WSIZE);
			break;
		
		case FUNCALL:
			emitFunction(p->s1, out);
			fprintf(out, "\tmov\trbx, rax\t;store function return into rbx\n");
			break;
		
		default:
			fprintf(out, "\t;bad right side\n");
			break;
	
	}//end right switch
	
	//store
	fprintf(out, "\tmov\trax, [rsp+%d]\t;store rsp + offset into rax\n", p->symbol->offset * WSIZE);

	//operators
	switch(p->operator){
	
		case PLUS:
			fprintf(out, "\tadd\trax, rbx\t;EXPR ADD\n");
			break;
			
		case MINUS:
			fprintf(out, "\tsub\trax, rbx\t;EXPR SUB\n");
			break;
			
		case TIMES:
			fprintf(out, "\timul\trax, rbx\t;EXPR TIMES\n");
			break;
			
		case DIVIDE:
			fprintf(out, "\txor\trdx, rdx\t;EXPR XOR\n");
			fprintf(out, "\tidiv\trbx\t;EXPR DIV\n");
			break;
			
		case EQUAL:
			fprintf(out, "\tcmp\trax, rbx\t;EXPR EQUAL\n");
			fprintf(out, "\tsete\tal\t;EXPR EQUAL\n");
			fprintf(out, "\tmov\trbx, 1\t;set rbx to one to filter rax\n");
			fprintf(out, "\tand\trax, rbx\t;filter rax\n");
			break;
			
		case NOTEQUAL:
			fprintf(out, "\tcmp\trax, rbx\t;EXPR NOTEQUAL\n");
			fprintf(out, "\tsetne\tal\t;EXPR NOTEQUAL\n");
			fprintf(out, "\tmov\trbx, 1\t;Set rbx to 1 to filter rax\n");
			fprintf(out, "\tand\trax, rbx\t;filter rax\n");
			break;
			
		case LESSTHAN:
			fprintf(out, "\tcmp\trax, rbx\t;EXPR LESSTHAN \n");
			fprintf(out, "\tsetl\tal\t;EXPR LESSTHAN\n");
			fprintf(out, "\tmov\trbx, 1\t;set rbx to 1 to filter rax\n");
			fprintf(out, "\tand\trax, rbx\t;filter RAX\n");
			break;
			
		case GREATERTHAN:
			fprintf(out, "\tcmp\trax, rbx\t;EXPR GREATERTHAN\n");
			fprintf(out, "\tsetg\tal\t;EXPR GREATERTHAN\n");
			fprintf(out, "\tmov\trbx, 1\t;set rbx to 1 to filter rax\n");
			fprintf(out, "\tand\trax, rbx\t;filter rax\n");
			break;
			
		case LESSTHANEQUAL:
			fprintf(out, "\tcmp\trax, rbx\t;EXPR LESSTHANEQUAL\n");
			fprintf(out, "\tsetle\tal\t;EXPR LESSTHANEQUAL\n");
			fprintf(out, "\tmov\trbx, 1\t;Set rbx to 1 to filter rax\n");
			fprintf(out, "\tand\trax, rbx\t;filter rax\n");
			break;
		
		case GREATERTHANEQUAL:
			fprintf(out, "\tcmp\trax, rbx\t;EXPR GREATERTHANEQUAL\n");
			fprintf(out, "\tsetge\tal\t;EXPRE GREATERTHANEQUAL\n");
			fprintf(out, "\tmov\trbx, 1\t;set rbx to one to filter rax\n");
			fprintf(out, "\tand\trax, rbx\t;filter rax\n");
			break;
			
		default:
			fprintf(out, "\tbad operator\n");
			break;
	
	}
	
	//store
	fprintf(out, "\tmov\t[rsp+%d], rax\t;store rax\n", p->symbol->offset * WSIZE);

}//end emitExpr

void emitIdent(ASTnode *p, FILE *out){

	if(p->s1 != NULL){
	
		switch(p->s1->type){
		
			case NUMB:
				fprintf(out, "\tmov\trbx, %d \t;assign value to rbx\n",p->s1->value*WSIZE);
				break;
			
			case IDENT:
				emitIdent(p->s1, out);
				fprintf(out, "\tmov\trbx, [rax]\t;move rax value to rbx\n");
				fprintf(out, "\tshl\trbx, 3\t;Array reference needs WSIZE differencing\n");
				break;
				
			case EXPR:
				emitExpr(p->s1, out);
				fprintf(out, "\tmov\trbx, [rsp+%d]\t;move array value at sp to rbx\n", p->s1->symbol->offset*WSIZE);
				fprintf(out, "\tshl\trbx, 3\t;Array reference needs WSIZE differencing\n");
				break;
				
			case FUNCALL:
				emitFunction(p->s1, out);
				fprintf(out, "\tmov\trbx, rax\t;store function return\n");
				fprintf(out, "\tshl\trbx, 3\t;Array reference needs WSIZE differencing\n");
				break;
				
			default:
				fprintf(out, "\t;bad array idents\n");
				break;
		
		}//end switch
	
	}//end if
	
	if(p->symbol->level == 0){
		fprintf(out, "\n\tmov\trax, %s\t;put address into rax\n", p->name);
	}
	else{
		fprintf(out, "\n\tmov\trax, %d \t;get identifier offset\n", p->symbol->offset *WSIZE);
		fprintf(out, "\tadd\trax, rsp\t;Add the sp to have direct reference to memory\n");

	}
	
	if(p->s1 != NULL)
		fprintf(out, "\tadd\trax, rbx\t;add offset and stack pointer\n");

}//end emitIdent


void emitFunction(ASTnode *p, FILE *out){
	//gets value from arg
	evaluateArgs(p->s1, out);
	//moves args of function call to params of function
	emitArgsToParams(p->s1, p->symbol->fparms, p->symbol->mysize, out);
	fprintf(out, "\tcall\t%s\t;call function\n", p->name);
	return;
}//end emitFunction

void evaluateArgs(ASTnode *p, FILE *out){
	if(p == NULL){
		return;
	}
	switch(p->s1->type){
		case NUMB:
			fprintf(out, "\tmov\trax, %d \t;arg number\n", p->s1->value);
			break;
		case IDENT:
			emitIdent(p->s1, out);
			fprintf(out, "\tmov\trax, [rax]\t;arg identifier value\n");
			break;
		case EXPR:
			emitExpr(p->s1, out);
			fprintf(out, "\tmov\trax, [rsp+%d]\t;arg expression\n", p->s1->symbol->offset * WSIZE);
			break;
		case FUNCALL:
			emitFunction(p->s1, out);
			break;
		default:
			fprintf(out, "\t;bad arg type\n");
			break;
	}
	fprintf(out, "\tmov\t[rsp+%d], rax\t;store arg into arglist offset\n", p->symbol->offset * WSIZE);
	evaluateArgs(p->next, out);
}//end evaluateArgs

//moves all args of function call to params of function
void emitArgsToParams(ASTnode *arg, ASTnode *param, int functionSize, FILE *out){
	fprintf(out, "\tmov\trbx, rsp\t;store rsp in rbx\n");
	fprintf(out, "\tsub\trbx, %d \t;subtract functionSize+1 to get location on stack\n", ((functionSize+1)*WSIZE));
	while(param != NULL){
		//copy arg
		fprintf(out, "\tmov\trax, [rsp+%d]\t;temporarily store arg contents\n", arg->symbol->offset * WSIZE);
		//mov arg to param
		fprintf(out, "\tmov\t[rbx+%d], rax\t;copy contents of rax into param\n", param->symbol->offset * WSIZE);
		//go through all params/args
		arg=arg->next;
		param=param->next;
	}//end while still params
}//end emitArgsToParams

//returns value or nothing
void emitReturn(ASTnode *p, FILE *out){
	if((p != NULL) && (p->s1 != NULL)){
		switch(p->s1->type){
			case NUMB:
				fprintf(out, "\tmov\trax, %d \t;return number\n", p->s1->value);
				break;
			case IDENT:
				emitIdent(p->s1, out);
				fprintf(out, "\tmov\trax, [rax]\t;return identifier value\n");
				break;
			case EXPR:
				emitExpr(p->s1, out);
				fprintf(out, "\tmov\trax, [rsp+%d]\t;return value of expression\n", p->s1->symbol->offset * WSIZE);
				break;
			case FUNCALL:
				emitFunction(p->s1, out);
				break;
			default:
				fprintf(out, "\t;bad return\n");
				break;
		}//end return switch
	}//end if has something to return
	else{
		fprintf(out, "\txor\trax, rax\t;nothing to return\n");
	}
	fprintf(out,"\n\tmov\trbp, [rsp]\t;FUNC end restore old BP\n");
	fprintf(out,"\tmov\trsp, [rsp+8]\t;FUNC end restore old SP\n");
	if(strcmp(currentFunction, "main") == 0)
		fprintf(out,"\tmov\trsp, rbp\t;stack and BP need to be same on exit for main\n");
	fprintf(out,"\tret\n");
}//end emitReturn()


