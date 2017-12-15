/*
   Program which demontrates operator overloads
 */
 #include <iostream>
 #include <cmath>
 using namespace std;
 
 
 class Complex{
    private:
        double real;
        double imaginary;
        
        
    public:
    
void set(double REAL, double IMAGINARY){
    
    real = REAL;
    imaginary = IMAGINARY;
}//end of set

 //copy constructor
 void copy(const Complex &complex){
 
   set(complex.real, complex.imaginary);
   
}

Complex operator+(Complex &complex){

    cout<<"add() function: ";
    cout<<endl;
    //math
    cout<<"("<<real<<" + "<<imaginary<<"i)"<<" + "<<"("<<complex.real<<" + "<<complex.imaginary<<"i) = ";
    Complex result;
    result.real = complex.real + real;
    result.imaginary = complex.imaginary + imaginary;
    
    return result;
} //end of add 

Complex operator-(Complex &complex){
 
  cout<<"subtract() function: ";
  cout<<endl;
  cout<<"("<<real<<" + "<<imaginary<<"i)"<<" - "<<"("<<complex.real<<" + "<<complex.imaginary<<"i) = ";
  //math 
  Complex result;
  result.real = complex.real - real;
  result.imaginary = complex.imaginary - imaginary;
  
 
    return result;

}//end of subtract

Complex operator*(Complex &complex){
 
   cout<<"multiply() function: ";
   cout<<endl;
   cout<<"("<<real<<" + "<<imaginary<<"i)"<<" * "<<"("<<complex.real<<" + "<<complex.imaginary<<"i) = ";
   //math
   Complex result;
   result.real = (complex.real * real) - (complex.imaginary * imaginary);
   result.imaginary = (complex.real * imaginary) + (complex.imaginary * real);
   
   //print out
   return result;

}//end of multiply 

Complex operator/(Complex &complex){

  cout<<"divide() function: ";
  cout<<endl;
  cout<<"("<<real<<" + "<<imaginary<<"i)"<<" / "<<"("<<complex.real<<" + "<<complex.imaginary<<"i) = ";
  //math
  Complex result;
  result.real = ((complex.real * real) + (complex.imaginary * imaginary)) / ((real * real) + (imaginary * imaginary));
  result.imaginary = ((complex.imaginary * real) - (complex.real * imaginary)) / ((real * real) + (imaginary * imaginary));
  
  //print
    return result;
}//end of divide 

bool operator==(Complex &complex){
 cout<<"the == operator: ";
 cout<<endl;
 cout<<"("<<real<<" + "<<imaginary<<"i)"<<" == "<<"("<<complex.real<<" + "<<complex.imaginary<<"i) = ";
 
 
 
 if(complex.real == real && complex.imaginary == imaginary) {
  return true;
 }
 
 else if(complex.real != real || complex.imaginary != imaginary){
   return false;
 }

 
 
}//end of bool ==

bool operator!=(Complex &complex){

 cout<<"the != operator: ";
 cout<<endl;
 cout<<"("<<real<<" + "<<imaginary<<"i)"<<" != "<<"("<<complex.real<<" + "<<complex.imaginary<<"i) = ";
 
 
 
 if(complex.real == real && complex.imaginary == imaginary) {
   return false;
 }
 
 else if(complex.real != real || complex.imaginary != imaginary){
   return true;
 }

 
 
}//end of bool !=*/


void print() {
      
      cout<<"("<<real<<" + "<<imaginary<<"i)";
       cout<<endl;
       
}//end of print

friend istream &operator>>(istream &input, Complex &complex){
    
    input>>complex.real>>complex.imaginary;
    return input;
  }

friend ostream &operator<<(ostream &output, const Complex & complex){
    output<<"("<<complex.real << " + "<<complex.imaginary<<"i)";
    return output;
  }


    
};//end of class Complex


int main(){

  Complex  c, c1, c2;
  bool b;
  double real, imaginary;
  
  cout<<"Please enter the real and imaginary parts of the first complex number: ";
  cin>>c1;
  cout<<"First Complex number is now: ";
  cout<<c1;
  cout<<endl;
  
  cout<<"Please enter the real and imaginary parts of the second complex number: ";
  cin>>c2; 
  cout<<"Second Complex number is now: ";
  cout<<c2;
  cout<<endl;

  c = c1 + c2;
  cout<<c;
  cout<<endl;
  
  c = c1 - c2;
  cout<<c;
  cout<<endl;
  
  c = c1 * c2;
  cout<<c;
  cout<<endl;
  
  c = c1 / c2;
  cout<<c;
  cout<<endl;
  
  b = c1 == c2;
  cout<<boolalpha<<b<<endl;
  
  b = c1 != c2;
  cout<<boolalpha<<b<<endl;
  
  
 return 0;
}//end of main