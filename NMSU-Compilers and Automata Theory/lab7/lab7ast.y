/*
  Lab6, YACC file for lab6ast.c 
  includes semantic action for 
  building a AST 

  Christian McGovern
  March 28, 2018
*/


%{	/* begin specs */

#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>
#include "symtable.h"
#include "lab7ast.h"


extern int mydebug;
static int level;
extern int lineno;
static int offset=0;
static int goffset=0;

void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("%s on Line number: %d\n", s, lineno);
}


%}//end of c definitions 

/*  defines the start symbol, what values come back from LEX and how the operators are associated  */

%start P

%union{
	int value;
	char * string;
	ASTnode *node;  /* so we can build an AST */
  	enum OPERATORS operator;
}

%token <string> ID

%token <value> NUM INT VOID IF ELSE WHILE RETURN READ WRITE LE LT GT GE EQ NE

%type <node> P DL DEC VARDEC FUNDEC params paramlist param compoundstmt localdeclarations statementlist statement expressionstmt selectionstmt iterationstmt assignmentstmt  simpleexpression additiveexpression returnstmt readstmt writestmt expression var arglist args call factor term

%type <operator> relop addop multop typespec 


%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS 

%%	/* end specs, begin rules */

P 		: 	DL /*program -Decleration-list*/
            		{program=$1;}
		;
DL 		: 	DEC  {$$ = $1;}   
		|   DEC DL {$$ = $1;
			    $1->next=$2;}			
		;

DEC     : VARDEC{$$=$1;} | FUNDEC{$$=$1;}
		;
/*symtable stuff for VARDEC*/
VARDEC  : typespec ID ';'{
			  if(!Search($2,level,0)){
			  $$=ASTCreateNode(VARDEC);
                          $$->operator=$1;
			  $$->name=$2;
			  $$->symbol=Insert($2,$1,0,level,1,offset,0);
			  offset += 1;
			  Display();
		          } 
			  else{
			     yyerror($2);
		             yyerror("symbol is already used");
			     exit(1);
			  } 	 				  
			 }
		| typespec ID '[' NUM ']' ';' {
					       if(!Search($2,level,0)){
					       $$=ASTCreateNode(VARDEC); 
                                   	       $$->name=$2;
                                   	       $$->operator=$1;
					       $$->istype=$1;
                                   	       $$->value=$4;
					       $$->symbol=Insert($2,$1,2,level,$4,offset,0);
					       offset += $4;
					       }
					       else{yyerror($2);
						    yyerror("symbol is already used");
			     			    exit(1);
					      }}
		;				

typespec  : INT   {$$ = INTDEC;}
          | VOID  {$$ = VOIDDEC;}
			;	
/*symtable stuff for FUNDEC*/
FUNDEC  : typespec ID '('
			{if (!Search($2,level,0)){
			  Insert($2,$1,1,level,0,offset,1);
			  goffset=offset;
			  offset=0;
			 }else{yyerror($2);
				yyerror("symbol is already used");
			     	exit(1);
			  }
			} 
	  params {
			//(Search($2,0,0))->fparms = $5;
		 } 


		   ')' compoundstmt {$$=ASTCreateNode(FUNCTDEC); 
				     $$->operator =$1;
                                     $$->name=$2;
                                     $$->s0 = $5;
                                     $$->s1 = $8;
				     $$->istype=$1;
				     //$$->symbol=Search($2,0,0);
				     offset-=Delete(1);
				     level=0;
				     offset=goffset;
			            }
		;

params	: VOID       {$$ = NULL;}    
        | paramlist  {$$=$1;}				
		;

paramlist	: param  {$$ = $1;}
			| param ',' paramlist {$1->next=$3;
			                       $$=$1;}
			;
/*symtable stuff for PARAM*/
param   : typespec ID  {if (mydebug) Display();
			if(!Search($2,level+1,0)){
			 $$=ASTCreateNode(PARAM);
		         $$->operator=$1;
                         $$->name=$2;
			 $$->istype=$1;
			 $$->symbol=Insert($2,$1,0,level+1,1,offset,0);
			 if (mydebug) Display();
			 $$->value=0;
			 offset+=1;			  
			 }else{yyerror($2);
				yyerror("symbol is already used");
			     	exit(1);
			  }}
		| typespec ID '[' NUM ']'{if(!Search($2,level+1,0)){
					  $$=ASTCreateNode(PARAM);
					  $$->operator=$1;
					  $$->istype=$1;
                               		  $$->name=$2;
                               		  $$->value=$4;
					  $$->symbol=Insert($2,$1,2,level+1,1,offset,0);
					  offset+=1;
					  }else{yyerror($2);
						yyerror("symbol is already used");
			     			exit(1);
			  		   }
					 }
		;

compoundstmt : '{' {level++; mydebug && printf("Block level is %d\n",level);}	
	          localdeclarations statementlist '}' {$$=ASTCreateNode(BLOCK);
                                                        if ($3==NULL) 
                                                            $$->s0=$4;
                                                        else{  
                                                            $$->s0=$3;
                                                            $$->s1=$4;}
							Display();
						        offset-=Delete(level);
							level--;}
			 ;

localdeclarations : /* empty */ {$$=NULL;}
				  | VARDEC localdeclarations {$1->next=$2;
                                      			      $$=$1;}
				  ;

statementlist : /*empty */ {$$=NULL;} 
			  | statement statementlist {if($1 !=NULL){
							$1->next=$2;
                                       			$$=$1;}
                                   		     else $$=$2;}
			  ;

statement : expressionstmt {$$ = $1;}
		  |  compoundstmt   	{$$ = $1;}
		  |  selectionstmt	{$$ = $1;}
		  |  iterationstmt	{$$ = $1;}
		  |  assignmentstmt	{$$ = $1;}
		  |  returnstmt		{$$ = $1;}
		  |  readstmt		{$$ = $1;}
		  |  writestmt		{$$ = $1;}
		  ;

expressionstmt : ';' {$$=NULL;
		      $$=ASTCreateNode(EXPRSTMT);
		      $$->s0=NULL;}
	       | expression ';' {$$=ASTCreateNode(EXPRSTMT);
	       		         $$->s0=$1;}
			   ;

assignmentstmt  : var '=' expression ';' {$$=ASTCreateNode(ASSIGNSTMT);
					   if(($1->istype ==VOIDDEC) || ($1->istype != $3->istype)){
						yyerror("type error in assignment statement ");
						exit(1);
					   }
                                          $$->s0=$1;
                                          $$->s1=$3;
					  $$->name=CreateTemp();
                           		  $$->symbol=Insert($$->name,INTDEC,0,level,1,offset,0);
					  offset++;}
			   ;

selectionstmt : IF '(' expression ')' statement {$$=ASTCreateNode(IFSTMT);
                                                 $$->s0=$3;
                                                 $$->s1=$5;
                                                 $$->s2=NULL;}

			  | IF '(' expression ')' statement ELSE statement {$$=ASTCreateNode(IFSTMT);
                                                          		    $$->s0=$3;
                                                          	            $$->s1=$5;
                                                                            $$->s2=$7;}
			  ;

iterationstmt : WHILE '(' expression ')' statement {$$=ASTCreateNode(WHILESTMT);
                                                    $$->s0=$3;
                                                    $$->s1=$5;}
			 ;

returnstmt : RETURN ';' {$$=ASTCreateNode(RETURNSTMT);
                         $$->s0=NULL;}
		   | RETURN expression ';' {$$=ASTCreateNode(RETURNSTMT);
                                	    $$->s0=$2;}
		   ;

readstmt : READ var ';' {$$=ASTCreateNode(READSTMT);
                         $$->s0=$2;}
		 ;

writestmt : WRITE expression ';' {$$=ASTCreateNode(WRITESTMT);
                                  $$->s0=$2;}
		  ;

expression : simpleexpression {$$=$1;}
		   ;
/*Symtable stuff needed because ID*/
var : ID   {struct SymbTab *p;
	   if(!(p=Search($1,level,1))){
			      $$=ASTCreateNode(IDENTIFER);
			      $$->name=$1;
			      $$->s0=NULL;
			      $$->symbol=p;
			      $$->istype=p->Type;
			     if(p->IsAFunc==2){
				yyerror($1);
				yyerror("variable is an array, syntax error ");
				exit(1);
			      }		       
	   }
	    else{yyerror($1);
		 yyerror("undeclared variable");
		 exit(1);
	    }}
    | ID '[' expression ']' {struct SymbTab *p;
			     if(!(p=Search($1,level,1))){
			     $$=ASTCreateNode(IDENTIFER);
	                     $$->name=$1;
		             $$->s0=$3;
			     $$->type=p->Type;
			     if(p->IsAFunc==2) $$->symbol=p;
			     else{yyerror($1);
				yyerror("variable is not array, syntax error ");
				exit(1);
			     }
			     }
			    else{yyerror($1);
		 	    yyerror("undeclared variable");
		            exit(1);
	    		    }}
    ;

simpleexpression : additiveexpression {$$=$1;}
 		  /*switched simpleexpr with additiveexpr*/
		 | simpleexpression relop additiveexpression {$$=ASTCreateNode(EXPR);
                                                     	      $$->s0=$1;
                                                     	      $$->s1=$3;
                                                     	      $$->operator=$2;}
				 ;

relop : LE {$$=LESSTHANEQUAL;}
      | LT {$$=LESSTHAN;} 
      | GT {$$=GREATERTHAN;}
      | GE {$$=GREATERTHANEQUAL;}
      | EQ {$$=EQUAL;}
      | NE {$$=NOTEQUAL;}
      ;

additiveexpression : term {$$=$1;}
		    /*switched additive with term*/
		   | additiveexpression addop term {
						    if($1->istype!=$3->istype){
						      yyerror("additive expression type mismatch ");
						       exit(1); 
						    }
								
						    $$=ASTCreateNode(EXPR);
                                            	    $$->s0=$1;
                                            	    $$->s1=$3;
                                            	    $$->operator=$2;
						    $$->istype=INTDEC;
					            $$->name=CreateTemp();
						    $$->symbol=Insert($$->name,INTDEC,0,level,1,offset,0);
}
				   ;

addop : '+'{$$=PLUS;} | '-' {$$=MINUS;}
	  ;

term : factor {$$=$1;}
	   /*switched term with factor*/
     | term multop factor { if($1->istype!=$3->istype){
			    yyerror("term type mismatch ");
			    exit(1); 
			    }
		           $$=ASTCreateNode(EXPR);
                           $$->s0=$1;
                           $$->s1=$3;
                           $$->operator=$2;
			   $$->istype=INTDEC;
		           $$->name=CreateTemp();
                           $$->symbol=Insert($$->name,INTDEC,0,level,1,offset,0);
			   offset++;}
        
	 ;

multop : '*' {$$=TIMES;} | '/' {$$=DIV;}
       ;

factor : '(' expression ')' {$$=$2;}
       | NUM  {$$=ASTCreateNode(NUMBER);
               $$->value=$1;}
       | var  {$$=$1;}
       | call {$$=$1;}
       ;

call : ID '(' args ')' {struct Symbtab *p;
			if(!(p=Search($1,0,0))){
			   /*if(p->IsAFunc!=1){
			      yyerror($1);
			      yyerror("Function name not defined "); 
		           }

			   /*if(CompareFormals(p->fparms,$3) != 1){
				yyerror($1);
			        yyerror("parameter type or length mismatch between formals and actuals ");			   
				exit(1);						   
			   }*/
			
			$$=ASTCreateNode(CALL);
                        $$->s0=$3;
                        $$->name=$1;
			//$$->istype=p->Type;
			$$->symbol=p;
		          }else{yyerror($1);
				printf("function name undefined");
				exit(1);
				}
			}

	 ;

args : /*empty*/ {$$=NULL;} | arglist{$$=$1;}
	 ;

arglist : expression {$$=ASTCreateNode(ARGLIST);
		      $$->name=CreateTemp();
		      $$->symbol=Insert($$->name,INTDEC,0,level,1,offset,0);
		      offset++;
                      $$->s0=$1;
		      $$->istype=$1->istype;
                      $$->next=NULL;}
	| expression ',' arglist  {$$=ASTCreateNode(ARGLIST);
			           $$->name=CreateTemp();
		      		   $$->symbol=Insert($$->name,INTDEC,0,level,1,offset,0);
		      		   offset++;
                               	   $$->next=$3;
                               	   $$->s0=$1;}
		;


%% /* end rules */

main(int argv,char *arg[])
{  

   yyparse();

fprintf(stderr, "The input has been syntatically checked\n");
ASTprint(0,program);
}

