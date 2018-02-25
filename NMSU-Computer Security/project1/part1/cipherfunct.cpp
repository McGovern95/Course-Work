
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "cipherfunct.h"

int freq[26][3];
int pos[26];
char cipher[1000], plain[1000], key[27];

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

int dictionarycompute(){

	char str[10000];
	int score;
	FILE *ptr;
	ptr = fopen("dictionary.txt","r");
	if(!ptr) return 1;

	while(fgets(str, sizeof(str), ptr)) {

		stringUpr(str);

		if(strstr(plain, str)){
			//printf("Word found: %s",str);
			score++;
		}

   
}//end while
    //printf("total words matched with dictionary.txt: %d\n ",score);
    return score;
}

int computeFrequency(){
	FILE *ptr;
	ptr = fopen("ciphertext.txt","r");
	if(!ptr) return 1;
	char current;
	int count = 0, index = 0;
	count = 0;
	while((current = fgetc(ptr)) != EOF){
		index = current- 'A';
		if(index >= 0) {
			freq[index][1]++;
		}
		cipher[count] = current;
		count++;
	}

	fclose(ptr);
	return 0;
}

int printFrequency(){
	puts("Frequency Analysis");

	puts("Letter		Frequency           Mapped");

	int count;

	for(count = 0; count < 26; count++)
		printf("%c		%d          	    %c\n", freq[count][0], freq[count][1], freq[count][2]);

	return 0;

}


int manualDecrypt(){
	
	int i, k, tempInt, count, index;
	char tempChar;

	puts("Enter your key (by order of most to least freq character \n\t\t EX: ETAOINSHRDLCUMWFGYPBVKJXQZ): \n");
	fflush(stdout);
	scanf("%s", key);


	strcpy(plain, cipher);

     	for(i = 0; i < 26; i++){
		    freq[i][2] = key[i];
     	}

	for(i=0; i<26; i++){

	  for(k=0; k<26-i-1; k++){

		if(freq[k][0] > freq[k+1][0]){
			tempInt = freq[k][0];
			freq[k][0] = freq[k+1][0];
			freq[k+1][0] = tempInt;
			
			tempChar = freq[k][1];
			freq[k][1] = freq[k+1][1];
			freq[k+1][1] = tempChar;

			tempChar = freq[k][2];
			freq[k][2] = freq[k+1][2];
			freq[k+1][2] = tempChar;
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
}

int sortByFreq(){

     int tempInt, tempPos, i, k;
     char tempChar;
     for(i=0; i<26;i++){
          freq[i][0] = 'A' + i;
	      freq[i][2] = i;
     }

    for(i=0; i<26; i++){
 
	  for(k=0; k<26-i-1; k++){

		if(freq[k][1] < freq[k+1][1]){
			tempInt = freq[k][1];
			freq[k][1] = freq[k+1][1];
			freq[k+1][1] = tempInt;
			
			tempChar = freq[k][0];
			freq[k][0] = freq[k+1][0];
			freq[k+1][0] = tempChar;
		}
	  }
    }
}//end sortByFreq()

int permute(){

  int newScore, oldScore = 0;
  char temp;

  for(int i = 0; i < 22; i += 4){
      
      for(int j = i; j < i + 4; j++ ){
      
         for(int k = j; k < i + 3; k++){

              temp = freq[k][2];
              freq[k][2] = freq[k+1][2];
              freq[k+1][2] = temp;

               newScore = dictionarycompute();

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