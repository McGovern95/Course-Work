#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "getdouble.h"
   
/*This function reads a double from the input steam. 
  It will read up to the MAX number of characters.
  And will read until the end of file, newline, blank space, or tab.
  And will leave the rest of the characters on the input steam.
  If there is any error, a 0.0 is returned.
*/
double getdouble(){
  /*declare character array to store up to MAX characters, and leave one more space for end of string character*/
  char buffer[MAX + 1] = {'\0'};
  double number = 0.0;
  int i = 0;
  char character = 'c';
  
  /*get input from the user*/
  for(i=0; i < MAX; i++){
    character = getchar();
    /*check for end of file*/
    if(EOF == character){
      break;
    }
    /*check for end of line*/
    if('\n' == character){
      break;
    }
    /*check for end of number (space)*/
    if(' ' == character){
      break;
    }
    /*check for a tab*/
    if('\t' == character){
      break;
    }
    buffer[i] = character;
  }
  
  //printf("buffer = %s\n", buffer);
  
  /*convert to a double*/
  number = atof(buffer);
  
  /*if number is too large to be represented as a double, return a 0.0*/
  if(number == HUGE_VAL || number == -HUGE_VAL){
    number = 0.0;
  }
  
  //printf("number = %f\n", number);
  
  return number;
}

/*
 Declaration:

    double atof(const char *str); 

The string pointed to by the argument str is converted to a floating-point number (type double). Any initial whitespace characters are skipped (space, tab, carriage return, new line, vertical tab, or formfeed). The number may consist of an optional sign, a string of digits with an optional decimal character, and an optional e or E followed by a optionally signed exponent. Conversion stops when the first unrecognized character is reached.

On success the converted number is returned. If no conversion can be made, zero is returned. If the value is out of range of the type double, then HUGE_VAL is returned with the appropriate sign and ERANGE is stored in the variable errno. If the value is too small to be returned in the type double, then zero is returned and ERANGE is stored in the variable errno. 
*/

