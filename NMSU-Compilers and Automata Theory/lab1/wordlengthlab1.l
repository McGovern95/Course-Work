     /*  This lex routine uses a counting array to match alphabeticstrings 
         and make a frequency count.
  
         The real item to notice is that yywrap() is called at EOF and then is run
         to do what we need to do.   yywrap() returns true when we have a successful 
         end to the program.  We may want to return false (0) if we want to lexing process 
         to fail 

        Shaun Cooper
        January 2015
   */

   /*
   		Christian McGovern
   		Lab1, 1/19/2018
   		Changes to lines: 20, 23, and 37
    */

	int lgths[100];
	int countnums = 0;//int added to count numbers 
%%
[a-zA-Z]+	lgths[yyleng]++;
[0-9]+ 		countnums++;// rule/line added to count numbers 
.	|
\n	;

%%
yywrap()
{
	int i;
	printf("Length  No. words  \n");
	for (i=1; i<100; i++) {
		if (lgths[i] > 0) {
			printf("%5d%10d\n",i,lgths[i]);
		}
	}
	printf("No. Numbers: %15d\n", countnums);//line added to print No. Numbers
	return(1);
}

main()
{  yylex();

}
