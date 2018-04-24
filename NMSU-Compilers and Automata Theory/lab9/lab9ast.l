/*
*  Lex Program for NASM generator
* Christian McGovern
* Lab 6, 2/28
*/
%{

int mydebug=0;
int lineno=1;
#include "lab9ast.h"
#include "symtable.h"
#include "y.tab.h"



%}

letter 		[a-zA-Z][a-zA-Z]*
num 		[0-9][0-9]*
id 		{letter}({letter}|{num})*
string          \".*\"

/*Begin Rules*/
%%

int 		{if (mydebug) fprintf(stderr,"int found\n"); 
            							    return(INT);}
void		{if (mydebug) fprintf(stderr,"void found\n"); 
            							    return(VOID);}
if 			{if (mydebug) fprintf(stderr,"if found\n"); 
            							    return(IF);}
else 		{if (mydebug) fprintf(stderr,"else found\n"); 
            							    return(ELSE);}	
while	 	{if (mydebug) fprintf(stderr,"while found\n"); 
            							    return(WHILE);}
return		{if (mydebug) fprintf(stderr,"return found\n"); 
            							    return(RETURN);}
read		{if (mydebug) fprintf(stderr,"read found\n"); 
            							    return(READ);}
write		{if (mydebug) fprintf(stderr,"write found\n"); 
            							    return(WRITE);}

[<][\=]			{if (mydebug) fprintf(stderr,"LE found\n"); 
            							    return(LE);}

[>][\=]			{if (mydebug) fprintf(stderr,"GE found\n"); 
            							    return(GE);}

[\=][\=]			{if (mydebug) fprintf(stderr,"EQ found\n"); 
            							    return(EQ);}

[\!][\=]			{if (mydebug) fprintf(stderr,"LE found\n"); 
            							    return(NE);}

[<]			{if (mydebug) fprintf(stderr,"LT found\n"); 
            							    return(LT);}

[>]			{if (mydebug) fprintf(stderr,"GT found\n"); 
            							    return(GT);}

                                            
{id}		{if (mydebug) fprintf(stderr,"id found\n"); 
              yylval.string=strdup(yytext);return(ID);}

{num}		{if (mydebug) fprintf(stderr,"num found\n"); 
              yylval.value=atoi((const char *)yytext); return(NUM);}	


[ \t]		{}
[;]		        {if (mydebug) fprintf(stderr, "return a semicolon %c\n", *yytext);
					   				   return (*yytext);}
[<>=()\-+*/%&\[\]|;{},] 	{ if (mydebug) fprintf(stderr,"return a token %c\n",*yytext); //added () to set
                       					                   return (*yytext);}
\n 			{lineno++;} 

{string}		{if (mydebug) fprintf(stderr,"string found\n"); 
            		 yylval.string=strdup(yytext); return(STRING);}

%%
/*End Rules*/

int yywrap(void)
{ return 1;}
