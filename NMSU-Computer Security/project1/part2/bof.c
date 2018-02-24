#include <stdio.h>
 
char pass[] = "abcd";
 
int validate_user() {
   char buff[8];
   printf("Enter your password:\n -> ");
   printf("here alex");
   gets(buff);
   printf("here alex");
   return !strcmp(buff, pass);
}

void failure(){
   printf("Your password was not correct :(\n");
}

void success(){
   printf("Your password was correct :)\n");
}
 
int main(int argc, char *argv[]){
   if(validate_user()){
       success();
   }
   else{
       failure();
   }
   return 0;
}
