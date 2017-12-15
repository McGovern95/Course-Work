/*
 * Program which loops from 1 -9999 and outputs number in a different language
 * @author Christian McGovern
 * @assignments: ICS 212 assignment #8
 * @date 9/14/2015
 *
 */

 #include <stdio.h>

int main() {

   printf("This program will count in Japanese from 1 to 9999. \n");

   int romNum = 0;
   int digit10s = 0;
   int digit100s = 0;
   int digit1000s = 0;
  
      
   


   for(romNum = 1; romNum <= 9999; romNum++) {
   
      digit10s = (romNum/10)%10;
      digit100s = (romNum/100)%10;
      digit1000s = (romNum/1000)%10;
   
   
       
      printf(" = %i  \n",romNum , digit10s , digit100s , digit1000s );
    
    
      switch(digit1000s) {
         case 1:
            printf("sen ");
            break;
         case 2:
           printf("nisen ");
            break;
         case 3:
            printf("sanzen ");
            break;
         case 4:
            printf("yonsen ");
            break;
         case 5:
            printf("gosen ");
            break;
         case 6:
            printf("rokusen ");
            break;
         case 7:
            printf("nanasen ");
            break;
         case 8:
            printf("hassen ");
            break;
         case 9:
            printf("kyuusen ");
            break;
           
      }//end of digit1000s 
      
       switch(digit100s) {
         case 1:
            printf("hyaku ");
            break;
         case 2:
            printf("nihyaku ");
            break;
         case 3:
            printf("sanbyaku ");
            break;
         case 4:
            printf("yonhyaku ");
            break;
         case 5:
            printf("gohyaku ");
            break;
         case 6:
            printf("rokppyaku ");
            break;
         case 7:
           printf("nanahyaku ");
            break;
         case 8:
           printf("happyaku ");
            break;
         case 9:
            printf("kyuuhyaku ");
            break;
           
      }//end of digit100s
      
        switch(digit10s) {
         case 1:
            printf("jyuu ");
            break;
         case 2:
            printf("nijyuu ");
            break;
         case 3:
            printf("sanjyuu ");
            break;
         case 4:
            printf("yonjyuu ");
            break;
         case 5:
            printf("gojyuu ");
            break;
         case 6:
            printf("rokujyuu ");
            break;
         case 7:
            printf("nanajyuu ");
            break;
         case 8:
            printf("hachijyuu ");
            break;
         case 9:
            printf("kyuujyuu ");
            break;
           
      }//end of digit10s
      
 
    
   
      switch(romNum%10) {
         case 1:
            printf("ichi ");
            break;
         case 2:
            printf("ni ");
            break;
         case 3:
            printf("san ");
            break;
         case 4:
            printf("yon ");
            break;
         case 5:
           printf("go ");
            break;
         case 6:
            printf("roku ");
            break;
         case 7:
            printf("nana ");
            break;
         case 8:
            printf("hachi ");
            break;
         case 9:
            printf("kyuu ");
            break; 
         
      }//end of switch single digits switch
      
    

        
    
     
    
     
    
    
   
   
      
   } //end of for

  

   return 0;
   
}//end of main
