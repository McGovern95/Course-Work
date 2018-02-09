/*                 Small LEX routine which returns two formal tokens (INTEGER and VARIABLE)
                   along with single string elements like '+'.
 
                    This LEX definition is the companion to the docalc.y YACC routine which
                   is a simple calculator

                    Shaun Cooper
                    January 2015
*/
%{

int mydebug=1;
#include "y.tab.h"
#include "symtable.h"

%}

letter 		[A-Za-z]
digit 		[0-9]
id 			{letter}({letter}|{digit})*

%%



{id}		{if (mydebug) fprintf(stderr,"Variable found\n"); 
                       yylval=*yytext-'a'; return(VARIABLE);}

[0-9][0-9]*	{if (mydebug) fprintf(stderr,"Digit found\n"); 
                       yylval=atoi((const char *)yytext); return(INTEGER);}
[ \t]		{if (mydebug) fprintf(stderr,"Whitespace found\n");}
[=()\-+*/%&|] 	{ if (mydebug) fprintf(stderr,"return a token %c\n",*yytext); //added () to set
                       return (*yytext);}
\n 		{ if (mydebug) fprintf(stderr,"cariage return %c\n",*yytext); 
                       return (*yytext);}

%%

int yywrap(void)
{ return 1;}


