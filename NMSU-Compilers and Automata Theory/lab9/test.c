int y;
int b[100];
int main(void) {
  int x;
  int z;
  int a;
  int p[100];

   write "Enter a number";
   read y;
   write y;
   write "read and write success!";

   x = 0;
   z = 0;
   a = 2;
   
   write "value of x for while";
   write x;
   while(x<5){
   write "while success!";
     x=x+1;
   }
    write "value of z for if";
    write z;
   if(z<1){
    write "if success!";
    z=z+1;
   }
   write "value of a for if/else";
   write a;
   if(a<1){
   write "SHOULD NOT GO HERE";
   }else{write "else success!";
	}
   write "math operators tests";
   write 5+5-5;
   write 10/5*2;
   write 5+5-5*1/1;
   write "math tests success!";

   b[26] = 5;
   write b[25 + 1];
}
