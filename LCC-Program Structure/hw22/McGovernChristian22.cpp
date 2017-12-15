/* 
   Program which demonstrates classes in c++
*/

#include <iostream>
#include <cmath>
using namespace std;

class Complex{

public:
  
   double real;
   double imaginary;
   
   Complex(){
     real = 0;
     imaginary = 0;  
   }

  void print(){
   cout << real << " + " << imaginary << "i";
  }//end of print()
  
  void set(double rea, double ima){
    
    real = rea;
    imaginary = ima;
  
  }//end of set()
  
  double getReal(double real1){
     real = real1;
     cout<<real1;
  }//end of getReal();
  
  double getImaginary(double imaginary1){
     imaginary = imaginary1;
     cout<<imaginary1;
  }//end of getImaginary();

};//end of class Complex

int main(){

   Complex c1;
   cout<<"Complex number c1 is: ";
   c1.print();
   cout<<endl;
   
   cout<<"Complex number c2 is: ";
   c1.set(3.3, 4.4);
   c1.print();
   cout<<endl;
   
   Complex c2;
   cout<<"Complex number c3's real part is: ";
   c2.getReal(5.5);
   cout<<endl;
   cout<<"Complex number c3's imaginary part is: ";
   c2.getImaginary(6.6);
   cout<<endl;
   
   
 return 0;
}//end of main