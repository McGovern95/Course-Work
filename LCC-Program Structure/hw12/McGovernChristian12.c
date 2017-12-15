/* 
 * Program demonstrating the use of Arrays
 * @author: Christian McGovern
 * @assignment: ICS 212 #12
 *@date 10/9/15
 */
 
#include <stdio.h> 

void printInstructions();
int loopAndCounrLetters(int letters[]);
int outputResults(int letters[]);


int main() {

 int letters[26] = {0};
 
 printInstructions();
 
 loopAndCountLetters(letters);
 
 outputResults(letters);
 

return 0;
}//end of main

void printInstructions(){

  printf("This program will count the letters of the alphabet.\n");
  printf("Type several sentences, or use input redirection to input a file.\n");
  printf("To exit program, enter EOF (end of file) by pressing Crtl-D.\n");

}//end of printInstructions

int loopAndCountLetters(int letters[]){
   int c;
   int count;
   
   c = getchar();
   count = 0;
   
   while(c != EOF){
    if (c >= 'a' && c <= 'z') {
       
        ++letters[c - 'a'];

    }
    
     if (c >= 'A' && c <= 'Z') {
       
        ++letters[c - 'A'];

    }

     c = getchar();
   }

}//end of loopAndCountLetters

int outputResults(int letters[]) {
 int i;
 printf("The character counts are: \n");
 for(i = 0; i < 26; i++){
      printf("%c \t  %d\n", i + 'a', letters[i]);
    }
 
}//end of outputResults 

