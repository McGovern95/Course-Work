/*
 * Morse code program
 * @author: Christian McGovern
 * @assignment: ICS 212 #17
 * @date: 10/26/15
 */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define SIZE 36

const char *morse[SIZE] = {
    "-----",
    ".----",
    "..---",
    "...--",
    "....-",
    ".....",
    "-....",
    "--.. ",
    "---.. ",
    "----.",
    ".-",
    "-...",
    "-.-.",
    "-..",
    ".",
    "..-.",
    "--.",
    "....",
    "..",
    ".---",
    "-.-",
    ".-..",
    "--",
    "-.",
    "---",
    ".--.",
    "--.-",
    ".-.",
    "...",
    "-",
    "..-",
    "...-",
    ".--",
    "-..-",
    "-.--",
    "--..",
};

const char *alpha[SIZE] = {
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "a",
    "b",
    "c",
    "d",
    "e",
    "f",
    "g",
    "h",
    "i",
    "j",
    "k",
    "l",
    "m",
    "n",
    "o",
    "p",
    "q",
    "r",
    "s",
    "t",
    "u",
    "v",
    "w",
    "x",
    "y",
    "z",
};




int main(int argc, char *argv[]){

 //error checking
  if(argc < 2){
      printf("Enter at least 2 arguments on the commandline\n");
      exit(1); //quit the program
   }

  //efe
  //initialize variables
  int i;
  int j;

  //nested for-loop for converting
   for(i = 0; i < argc; i++){

     for(j = 0; j < 36; j++){

      if(strcmp(morse[j], argv[i]) == 0){
         printf("%c", *alpha[j]);
       }
    }//end of for-loop through morse[]
  }//end of for-loop through arguments
  printf("\n");//used to get newline and better formating


}//end of main
