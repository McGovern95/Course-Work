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
#include "lab6ast.h"

static int mydebug;
static int lineno; 
static int level;

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
			    $$ = $1;
			    $1->next=$2;}			
		;

DEC     : VARDEC{$$=$1;} | FUNDEC{$$=$1;}
		;

VARDEC  : typespec ID ';'{$$=ASTCreateNode(VARDEC);
                          $$->operator=$1;
			  $$->name=$2;}
		| typespec ID '[' NUM ']' ';' {$$=ASTCreateNode(VARDEC); 
                                   	       $$->name=$2;
                                   	       $$->operator=$1;
                                   	       $$->value=$4;}
		;

typespec  : INT   {$$ = INTDEC;}
          | VOID  {$$ = VOIDDEC;}
			;	

FUNDEC  : typespec ID '(' params ')' compoundstmt {$$=ASTCreateNode(FUNCTDEC); 
						   $$->operator =$1;
                                                   $$->name=$2;
                                                   $$->s0 = $4;
                                                   $$->s1 = $6;}
		;

params	: VOID       {$$ = NULL;}    
        | paramlist  {$$=$1;}				
		;

paramlist	: param  {$$ = $1;}
			| param ',' paramlist {$1->next=$3;
			                       $$=$1;}
			;

param   : typespec ID  {$$=ASTCreateNode(PARAM);
		        $$->operator=$1;
                        $$->name=$2;}
		| typespec ID '[' NUM ']' {$$=ASTCreateNode(PARAM);
					  $$->operator=$1;
                               		  $$->name=$2;
                               		  $$->value=$4;}
		;

compoundstmt : '{' localdeclarations statementlist '}' {$$=ASTCreateNode(BLOCK);
                                                        if ($2==NULL) 
                                                            $$->s0=$3;
                                                        else{  
                                                            $$->s0=$2;
                                                            $$->s1=$3;}}
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
                                          $$->s0=$1;
                                          $$->s1=$3;}
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

var : ID   {$$=ASTCreateNode(IDENTIFER);
			      $$->name=$1;
			      $$->s0=NULL;}
    | ID '[' expression ']' {$$=ASTCreateNode(IDENTIFER);
	                     $$->name=$1;
		             $$->s0=$3;}
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
		   | additiveexpression addop term {$$=ASTCreateNode(EXPR);
                                            	    $$->s0=$1;
                                            	    $$->s1=$3;
                                            	    $$->operator=$2;}
				   ;

addop : '+'{$$=PLUS;} | '-' {$$=MINUS;}
	  ;

term : factor {$$=$1;}
	   /*switched term with factor*/
     | term multop factor {$$=ASTCreateNode(EXPR);
                           $$->s0=$1;
                           $$->s1=$3;
                           $$->operator=$2;}
        ;
	 ;

multop : '*' {$$=TIMES;} | '/' {$$=DIV;}
       ;

factor : '(' expression ')' {$$=$2;}
       | NUM  {$$=ASTCreateNode(NUMBER);
               $$->value=$1;}
       | var  {$$=$1;}
       | call {$$=$1;}
       ;

call : ID '(' args ')' {$$=ASTCreateNode(CALL);
                        $$->s0=$3;
                        $$->name=$1;}
	 ;

args : /*empty*/ {$$=NULL;} | arglist{$$=$1;}
	 ;

arglist : expression {$$=ASTCreateNode(ARGLIST);
                      $$->s0=$1;
                      $$->next=NULL;}
	| expression ',' arglist  {$$=ASTCreateNode(ARGLIST);
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

