/*
  Lab5, LEX and YACC routines using BNF to parse input

  Christian McGovern
  Feb 28 2018
*/


%{	/* begin specs */
#include <stdio.h>
#include <ctype.h>
#include "lex.yy.c"
int base, debugsw;

void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("%s %d\n", s, lineno);
}


%}//end of c definitions 

/*  defines the start symbol, what values come back from LEX and how the operators are associated  */

%start P

%token ID NUM INT VOID IF ELSE WHILE RETURN READ WRITE LE GE EQ NE

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
			| paramlist ',' param
			;

param   : typespec ID
		| typespec ID '[' ']'
		;

compoundstmt : '{' localdeclarations statementlist '}'
			 ;

localdeclarations : VARDEC localdeclarations
				  | /*empty*/
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



%% /* end rules */

main()
{ yyparse();
}







/*ld -> /*empty*/
//  | VAR DEC LD
// ; */

//additiveexpresoin relop simpleexpression