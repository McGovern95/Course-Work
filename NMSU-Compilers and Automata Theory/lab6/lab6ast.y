/*
  Lab6, AST program

  Christian McGovern
  Feb 28 2018
*/


%{	/* begin specs */

#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include "lab6ast.h"

static int mydebug;
static int lineno; 

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

%type <node> P
%type <operator> relop

%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS 

%%	/* end specs, begin rules */

P 		: 	DL /*program -Decleration-list*/
		;
DL 		: 	DEC
		|   DEC DL
		;

DEC     : VARDEC | FUNDEC
		;

VARDEC  : typespec ID ';'
		| typespec ID '[' NUM ']' ';'
		;

typespec	: INT
			| VOID
			;	

FUNDEC  : typespec ID '(' params ')' compoundstmt
		;

params	: VOID
		| paramlist
		;

paramlist	: param
			| param ',' paramlist
			;

param   : typespec ID
		| typespec ID '[' ']'
		;

compoundstmt : '{' localdeclarations statementlist '}'
			 ;

localdeclarations : /* empty */ 
				  | VARDEC localdeclarations
				  ;

statementlist : /*empty */
			  | statement statementlist
			  ;

statement :  expressionstmt
		  |	 compoundstmt
		  |  selectionstmt
		  |  iterationstmt
		  |  assignmentstmt
		  |  returnstmt
		  |  readstmt
		  |  writestmt
		  ;

expressionstmt : ';'
			   | expression ';'
			   ;

assignmentstmt  : var '=' expression ';'
			   ;

selectionstmt : IF '(' expression ')' statement
			  | IF '(' expression ')' statement ELSE statement
			  ;

iterationstmt : WHILE '(' expression ')' statement
			 ;

returnstmt : RETURN ';'
		   | RETURN expression ';'
		   ;

readstmt : READ var ';'
		 ;

writestmt : WRITE expression ';'
		  ;

expression : simpleexpression
		   ;

var : ID 
    | ID '[' expression ']' 
    ;

simpleexpression : additiveexpression 
				 | additiveexpression relop simpleexpression
				 ;

relop : LE | LT | GT | GE | EQ | NE
      ;

additiveexpression : term
				   | term addop additiveexpression
				   ;

addop : '+' | '-'
	  ;

term : factor
	 | factor multop term
	 ;

multop : '*' | '/' 
       ;

factor : '(' expression ')' | NUM | var | call
       ;

call : ID '(' args ')'
	 ;

args : /*empty*/ | arglist
	 ;

arglist : expression
		| expression ',' arglist
		;


%% /* end rules */

main()
{ yyparse();
}

