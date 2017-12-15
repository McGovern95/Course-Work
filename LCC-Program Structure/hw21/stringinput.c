/*
Safer functions for string input: getstring() and getline()
*/

#include <stdio.h>
#include <stdlib.h>
#include "stringinput.h"

/*
  This function reads characters from the input steam,
  and stores the characters in a string, 
  and adds a null character ('\0') after the last character in the string. 
  It will read up to size-1 number of characters.
  And will read until the end of file, newline, blank space, or tab.
  And will leave the rest of the characters on the input steam.
  Warning: If the string array has less than size number of characters,
  this may crash the program, or write over memory!
  If there are no characters added to the string, a 0 is returned. 
  string: An array of characters, with size number of elements.
  size: The number of characters in the string array.
  returns: The number of characters read into the string.  
*/
int getstring(char string[], const int size){
   int index = 0;
   char character = 'z';
   /*get input from the user*/
   for(index=0; index < size-1; index++){
      character = getchar();
      /*check for end of file*/
      if(EOF == character)
         break;
      /*check for end of line*/
      if('\n' == character)
         break;
      /*check for space*/
      if(' ' == character)
         break;
      /*check for a tab*/
      if('\t' == character)
         break;
      string[index] = character;
   }
   //add the null character
   string[index] = END_OF_STRING;
   return index; //number of characters in the string
}


/*
  This function reads characters from the input steam,
  and stores the characters in a string, 
  and adds a null character ('\0') after the last character in the string. 
  It will read up to size-1 number of characters.
  And will read until the end of file or newline.
  And will remove the rest of the characters from the input steam.
  Warning: If the string has less than size number of characters,
  this may crash the program, or write over memory!
  If there are no characters added to the string, a 0 is returned. 
  string: An array of characters, with size number of elements.
  size: The number of characters in the string array.
  returns: The number of characters read into the string.  
*/
int getline(char string[], const int size){
   int index = 0;
   char character = 'z';
   /*get input from the user*/
   for(index=0; index < size-1; index++){
      character = getchar();
      /*check for end of file*/
      if(EOF == character)
         break;
      /*check for end of line*/
      if('\n' == character)
         break;
      string[index] = character;
   }
   //add the null character
   string[index] = END_OF_STRING;
   
   //remove the rest of the characters from input stream
   while(('\n' != character) && (EOF != character)){
      character = getchar();
   }
   
   return index; //number of characters in the string
}

