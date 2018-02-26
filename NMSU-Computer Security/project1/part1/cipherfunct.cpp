
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "cipherfunct.h"

int freq[26][3];
int pos[26];
char cipher[1000], plain[1000], key[26];

/*code taken from- since standard c libary wasn't working: 
http://www.includehelp.com/c-programs/c-program-to-convert-string-into-lower-and-upper-case.aspx
*/
void stringUpr(char *s){
    int i=0;
    while(s[i]!='\0')
    {
        if(s[i]>='a' && s[i]<='z'){
            s[i]=s[i]-32;
        }
        ++i;
    }
}//end stringUpr();

//compares plain text with dictionary.txt
int dictCompute(){

	char str[10000];
	int score;
	FILE *ptr;
	ptr = fopen("dictionary.txt","r");
	if(!ptr)
		printf("dictionary.txt not found!");

	while(fgets(str, sizeof(str), ptr)) {

		stringUpr(str);

		if(strstr(plain, str)){
			//printf("Word found: %s",str); not working 100%
			score++;
		}

   
}//end while
    fclose(ptr);
    printf("total words matched with dictionary.txt: %d\n ",score);
    return score;
}//end dictcompute();

//computes the letter freq
int computeFreq(){
	FILE *ptr;
	ptr = fopen("ciphertext.txt","r");
	if(!ptr)
		printf("ciphertext.txt not found!");
	char current;
	int count = 0, index = 0;
	count = 0;
	while((current = fgetc(ptr)) != EOF){
		index = current - 'A';
		if(index >= 0) {
			freq[index][1]++;
		}
		cipher[count] = current;
		count++;
	}

	fclose(ptr);
	return 0;
}//end computeFreq

//assigns new freq by key entered
int decrypt(){
	
	int i, j, temp, count, index;
	char tempChar;

	puts("Enter your key (by order of most to least freq character \n\t\t EX: ETAOINSHRDLCUMWFGYPBVKJXQZ): \n");
	fflush(stdout);
	scanf("%s", key);


	strcpy(plain, cipher);

     	for(i = 0; i < 26; i++){
		    freq[i][2] = key[i];
     	}
    //bubble sort
	for(i=0; i<26; i++){

	  for(j=0; j<26-i-1; j++){

		if(freq[j][0] > freq[j+1][0]){
			temp = freq[j][0];
			freq[j][0] = freq[j+1][0];
			freq[j+1][0] = temp;
			
			tempChar = freq[j][1];
			freq[j][1] = freq[j+1][1];
			freq[j+1][1] = tempChar;

			tempChar = freq[j][2];
			freq[j][2] = freq[j+1][2];
			freq[j+1][2] = tempChar;
		}
	  }
    }

	while(count < strlen(plain)) {
		index = plain[count] - 'A';
		if(index >=0 && index < 27)
			plain[count] = freq[index][2];
		count++;
	}

	return 0;
}//end decrypt();

//sorts the freq alphabetically for easier reading
int sortFreq(){

     int tempInt, tempPos;
     char tempChar;
     for(int i=0; i<26;i++){
          freq[i][0] = 'A' + i;
	      freq[i][2] = i;
     }

    for(int i=0; i<26; i++){
 
	  for(int j=0; j<26-i-1; j++){

		if(freq[j][1] < freq[j+1][1]){
			tempInt = freq[j][1];
			freq[j][1] = freq[j+1][1];
			freq[j+1][1] = tempInt;
			
			tempChar = freq[j][0];
			freq[j][0] = freq[j+1][0];
			freq[j+1][0] = tempChar;
		}
	  }
    }
}//end sortByFreq()

//prints the freq analysis
int printFreq(){
	puts("Frequency Analysis");

	puts("Letter		Frequency           Mapped");

	int count;

	for(count = 0; count < 26; count++)
		printf("%c		%d          	    %c\n", freq[count][0], freq[count][1], freq[count][2]);

	return 0;

}

//was not able to get automatic permutation to work
int permute(){

  int newScore, oldScore = 0;
  char temp;

  for(int i = 0; i < 22; i += 4){
      
      for(int j = i; j < i + 4; j++ ){
      
         for(int k = j; k < i + 3; k++){

              temp = freq[k][2];
              freq[k][2] = freq[k+1][2];
              freq[k+1][2] = temp;

               newScore = dictCompute();

               if(newScore > oldScore)
               	  oldScore = newScore;

               else{
               	   temp = freq[k][2];
                   freq[k][2] = freq[k+1][2];
                   freq[k+1][2] = temp;
			   }

          }
      }
   }

   for(int i = 0; i< 26; i++){
   	   printf("%c",freq[i][2]);
   }

}