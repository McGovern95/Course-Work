/*
  Lab9, YACC file for NASM generation

  Christian McGovern
  May 4, 2018
*/

%{

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "ast.h"
#include "symtable.c"
#include "emit.c"

#define max(x,y) ((x)>(y) ? (x) : (y))

int mydebug;
int lineno;
int level = 0;
int offset = 0;
int goffset;
int moffset;

static FILE *out;

void yyerror (s)
	char *s;
	{
		printf("YACC PARSE ERROR: %s on line number %d\n", s, lineno);
	}
%}

%start program

%union {
	int value;
	char * string;
	ASTnode * node;
	enum OPERATORS operator;
}

%type <node>  declarationlist declaration vardeclaration fundeclaration params paramlist param compoundstmt localdeclaration statementlist statement expressionstmt assignmentstmt selectionstmt iterationstmt returnstmt readstmt writestmt expression var simpleexpression additiveexpression term factor call args arglist
%type <operator> typespecifier relop addop multop
%token <value> NUM INT VOID WHILE IF THEN ELSE READ WRITE RETURN LE GE EQ NE GT LT
%token <string> ID STRING

%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS

%%

program : declarationlist {program=$1;}
	;

declarationlist : declaration {$$=$1;}
		| declaration declarationlist { $1->next=$2; $$=$1;}
		;

declaration : vardeclaration {$$=$1;}
	    | fundeclaration {$$=$1;}
	    ;

vardeclaration : typespecifier ID ';' {
					
					if(Search($2,level,0) == NULL){
					$$=ASTCreateNode(VARDEC);
					$$->name=$2;
					$$->operator=$1;
					$$->istype=$1;
					$$->symbol=Insert($2,$1,0,level,1,offset,NULL);
					offset = offset +1;
					moffset = offset;
				       }
				       else{
					yyerror($2);
					yyerror("symbol already used");
					exit(1);
				       }
				      }
	       | typespecifier ID '[' NUM ']' ';' {
							struct SymbTab *p;
							if(Search($2,level,0) == NULL){
								$$=ASTCreateNode(VARDEC);
								$$->name=$2;
								$$->value=$4;
								$$->operator=$1;
								$$->istype=$1;//??what is the point of istype and what is it
								$$->symbol=Insert($2,$1,2,level,$4,offset,NULL);
								offset = offset + $4;
								moffset = offset;
							}
							else{
								yyerror($2);
								yyerror("symbol already used");
								exit(1);
							}
						  }
	       ;

typespecifier : INT {$$=INTDEC;}
	      | VOID {$$=VOIDDEC;}
	      ;

fundeclaration : typespecifier ID '('{
					if(Search($2,level,0) == NULL){
						Insert($2,$1,1,level,0,0,NULL);
						goffset = offset;
						offset = 2;
						moffset=offset;
					}
					else{
						yyerror($2);
						yyerror("name already used");
						exit(1);
					}
				     }

		 params{
			(Search($2,0,0))->fparms = $5;
		       }
		 ')' compoundstmt {
					$$=ASTCreateNode(FUNDEC); 
    					$$->name=$2;
    					$$->s2=$8;
					$$->s1=$5;
					$$->operator=$1;
					$$->istype=$1;
					$$->symbol=Search($2,0,0);
					offset = offset - Delete(1);//remove all symbols from what we put in from the function
					level = 0;
					offset = goffset;
					$$->symbol->mysize = moffset;
					$$->value = moffset;
				  }
	       ;

params : VOID {$$=NULL;} /* no parameters */
       | paramlist {$$=$1;}
       ;

paramlist : param {$$=$1;}
	  | param ',' paramlist {$1->next=$3; $$=$1;}
	  ;

param : typespecifier ID '[' ']'{
				 if(Search($2,level+1,0) == NULL){
					 $$=ASTCreateNode(PARAM);
					 $$->name=$2;
					 $$->operator=$1;
					 $$->value=-1;
					 $$->istype=$1;
					 $$->symbol=Insert($2,$1,2,level+1,1,offset,NULL);
					 offset = offset + 1;
				 }
				 else{
					yyerror($2);
					yyerror("symbol already used");
					exit(1);
				 }
				}
      | typespecifier ID {
				if(mydebug) 
					Display();
				if(Search($2,level+1,0) == NULL){
					$$=ASTCreateNode(PARAM);
				  	$$->name=$2;
					$$->operator=$1;
					$$->istype=$1;
					$$->symbol=Insert($2,$1,0,level+1,1,offset,NULL);
					mydebug && printf("in param insert %s %d\n",$2,level+1);
					if(mydebug)
						Display();
					$$->value=0;
					offset = offset + 1;
				}
				else{
					yyerror($2);
					yyerror("symbol already used");
					exit(1);
				}
			}
      ;

compoundstmt : '{'{
			level++;
			mydebug && printf("BLOCK level is %d\n", level);
		  }
		 localdeclaration 
		 statementlist 
		'}'
			{$$=ASTCreateNode(CMPDSTMT);
			 if($3 == NULL)
				$$->s1 = $4;
			else{
                         $$->s1=$3;
			 $$->s2=$4;
			}
			 if(mydebug)
				Display();
			 moffset = max(offset, moffset);
			 offset = offset - Delete(level);
			 level--;
                      	}
	     ;

localdeclaration : /* empty */ {$$=NULL; mydebug && printf("var dec level is %d\n", level);}
		 | vardeclaration localdeclaration {$1->next=$2; $$=$1;}
		 ;

statementlist : /* empty */ {$$=NULL;}
	      | statement statementlist {$1->next=$2; $$=$1;}
	      ;

statement : expressionstmt {$$=$1;}
	  | compoundstmt {$$=$1;}
	  | selectionstmt {$$=$1;}
	  | iterationstmt {$$=$1;}
	  | assignmentstmt {$$=$1;}
	  | returnstmt {$$=$1;}
	  | readstmt {$$=$1;}
	  | writestmt {$$=$1;}
	  ;

expressionstmt : expression ';' {
					$$=ASTCreateNode(EXPRSTMT); 
					$$->s1=$1; 
					$$->istype=$1->istype;
					$$->name = CreateTemp();
					$$->symbol=Insert($$->name, $$->istype,0,level,1,offset,NULL);
					offset = offset + 1;
				}
	       | ';' {$$=NULL;
		     $$=ASTCreateNode(EXPRSTMT);
		     $$->s1 = NULL;
		     }
	       ;

assignmentstmt : var '=' expressionstmt
		      {
				
				$$=ASTCreateNode(ASIGNSTMT);
				if(($1->istype == VOIDDEC) || ($1->istype != $3-> istype)){
					yyerror("type error in assignment statement");
					exit(1);
				}
				$$->s1=$1;
	                        $$->s2=$3;
                      }
	       ;

selectionstmt : IF '(' expression ')' statement { $$=ASTCreateNode(SELECSTMT);
                                                  $$->s1=$3;
                                                  $$->s2=$5;
                                                  $$->s3=NULL;
                                                }
	      | IF '(' expression ')' statement ELSE statement {$$=ASTCreateNode(SELECSTMT);
								$$->s1=$3;
								$$->s2=$5;
								$$->s3=$7;
							       }
	      ;

iterationstmt : WHILE '(' expression ')' statement
					{
					$$=ASTCreateNode(ITRASTMT);
					$$->s1=$3;
					$$->s2=$5;
					}
	      ;

returnstmt : RETURN ';' { $$=ASTCreateNode(RTRNSTMT);}
	   | RETURN expression ';' {$$=ASTCreateNode(RTRNSTMT); $$->s1=$2;}
	   ;

readstmt : READ var ';' {
                            $$=ASTCreateNode(READSTMT);
                            $$->s1=$2;
                        }
	 ;

writestmt : WRITE expression ';' {$$=ASTCreateNode(WRITESTMT);
				  $$->s1=$2;
                                 }
	  | WRITE STRING ';' {
					$$=ASTCreateNode(WRITESTMT);
					$$->name=$2;
					$$->label=CreateLabel();
				 }
	  ;

expression : simpleexpression {$$=$1;}
	   ;

var : ID {
		struct SymbTab *p;
		if((p=Search($1,level,1)) != NULL){	
			$$=ASTCreateNode(IDENT);
			$$->name=$1;
			$$->symbol=p;
			$$->istype=p->Type;
			if(p->IsAFunc == 2){
				yyerror($1);
				yyerror("variable is an array, syntax error");
				exit(1);
			}
		}
		else{
			yyerror($1);
			yyerror("undeclared variable");
			exit(1);
		}
	 }
    | ID '[' expression ']'
                 { 
			struct SymbTab *p;
			if((p=Search($1,level,1)) != NULL){
				$$=ASTCreateNode(IDENT);
				$$->name=$1;
			 	$$->s1=$3;
				$$->istype=p->Type;
				if(p->IsAFunc == 2)
					$$->symbol=p;
				else{
					yyerror($1);
					yyerror("not an array, type mismatch");
					exit(1);
				}
			}
			else{
				yyerror($1);
				yyerror("undeclared variable");
				exit(1);
			}
		 }
    ;

simpleexpression : additiveexpression {$$=$1;}
		 | simpleexpression relop additiveexpression
			{
				if($1->istype != $3->istype){
					yyerror("simple expression type mismsatch");
					exit(1);
				}
				$$=ASTCreateNode(EXPR);
				$$->s1=$1;
				$$->s2=$3;
				$$->operator=$2;
				$$->istype=INTDEC;
				$$->name=CreateTemp();
				$$->symbol=Insert($$->name,INTDEC,0,level,1,offset,NULL);
				offset++;
			}
		 ;

relop : LE {$$=LESSTHANEQUAL;}
      | LT {$$=LESSTHAN;}
      | GT {$$=GREATERTHAN;}
      | GE {$$=GREATERTHANEQUAL;}
      | EQ {$$=EQUAL;}
      | NE {$$=NOTEQUAL;}
      ;

additiveexpression : term {$$=$1;} 
		   | additiveexpression addop term
			{
				if($1->istype != $3->istype){
					yyerror("additive expression type mismsatch");
					exit(1);
				}
				$$=ASTCreateNode(EXPR);
				$$->s1=$1;
				$$->s2=$3;
				$$->operator=$2;
				$$->istype=INTDEC;
				$$->name=CreateTemp();
				$$->symbol=Insert($$->name,INTDEC,0,level,1,offset,NULL);
				offset++;
			}
		   ;

addop : '+' {$$=PLUS;}
      | '-' {$$=MINUS;}
      ;

term : factor {$$=$1;}
     | term multop factor
		{
			if($1->istype != $3->istype){
				yyerror("term type mismsatch");
				exit(1);
			}
			$$=ASTCreateNode(EXPR);
			$$->s1=$1;
			$$->s2=$3;
			$$->operator=$2;
			$$->istype=INTDEC;
			$$->name=CreateTemp();
			$$->symbol=Insert($$->name,INTDEC,0,level,1,offset,NULL);
			offset++;
		}
     ;

multop : '*' {$$=TIMES;}
       | '/' {$$=DIVIDE;}
       | '%' {$$=MOD;}
       ;

factor : '(' expression ')' {$$=$2;}
       | NUM {  $$=ASTCreateNode(NUMB);
                $$->value=$1;
		$$->istype=INTDEC;
	     }
       | var {$$=$1;}
       | call {$$=$1;}
       ;

call : ID '(' args ')'
	  {
		struct SymbTab *p;
		if((p=Search($1,0,0)) != NULL){
			if(p->IsAFunc != 1){
				yyerror($1);
				yyerror("Function name not defined");
				exit(1);
			}
			if(CompareFormals(p->fparms,$3) != 1){
				yyerror($1);
				yyerror("parameter type or length mismatch between formals and actuals");
				exit(1);
			}
			$$=ASTCreateNode(FUNCALL);
      			$$->s1=$3;
         		$$->name=$1;
			$$->istype=p->Type;
			$$->symbol=p;
		}
		else{
			yyerror($1);
			yyerror("Function name not defined");
			exit(1);
		}
          }
     ;

args :  /* empty */ {$$=NULL;}
     | arglist {$$=$1;}
     ;

arglist : expression {
			$$=ASTCreateNode(ARG);
			$$->name=CreateTemp();
			$$->symbol=Insert($$->name,INTDEC,0,level,1,offset,NULL);
			offset++;
       			$$->s1 = $1;
			$$->istype=$1->istype;
			$$->next=NULL;
		     }
	| expression ',' arglist {
      		$$=ASTCreateNode(ARG);
		$$->name=CreateTemp();
		$$->symbol=Insert($$->name,INTDEC,0,level,1,offset,NULL);
		offset++;
		$$->istype=$1->istype;
       		$$->next=$3;
    		$$->s1=$1;
           }
	;

%%
int main(int argc,char *argv[]){  

if(argc < 2){printf("input at least 1 parameter\n");exit(0);}

if((strcmp(argv[1], "-o")==1) && (strcmp(argv[1], "-d")==1)){printf("please input either a -o or -d for first argument\n");exit(0);}

if((strcmp(argv[1],"-d")==0) && (!argv[2])){printf("more than just -d please\n");exit(0);}

else if((strcmp(argv[1],"-d")==0) && (strcmp(argv[2],"-o")==0)){
	if(argc != 4){printf("please write an output file\n");exit(0);}
	mydebug=1;
	out=fopen(argv[3],"wb");
	if(!out){printf("could not open file\n");exit(0);}
	yyparse();
	Display();
	emitNASM(program,out);
	fclose(out);
	return 1;
}
else if(strcmp(argv[1],"-o")==0){
	if(argc != 3){printf("please write an output file\n");exit(0);}
	out=fopen(argv[2],"wb");
	if(!out){printf("Could not open file\n");exit(0);}
	yyparse();
	emitNASM(program,out);
	fclose(out);
	return 1;
}
 else printf("error: not correct arguments! \n");

return 0;


//yyparse();
//emitAST(program);

}//end main





