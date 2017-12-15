/*
   Program which demonstrates classes and decontructors with complex numbers
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

void print() const{
       cout << real << " + " << imaginary << "i";
       cout<<endl;
       
}//end of print

void add(Complex &complex){

    cout<<"add() function: ";
    cout<<endl;
    //math
    Complex result;
    result.real = complex.real + real;
    result.imaginary = complex.imaginary + imaginary;
    
    //print out
      cd} //end of add 

void subtract(Complex &complex){
 
  cout<<"subtract() function: ";
  cout<<endl;
  //math 
  Complex result;
  result.real = complex.real - real;
  result.imaginary = complex.imaginary - imaginary;
  
  //print out
    cout<<"("<< real<<" + "<<imaginary<<"i) - ("<<complex.real <<" + "<<complex.imaginary<<"i) = ";
    cout<<"("<<result.real<<" + "<<result.imaginary<<"i)";
    cout<<endl;


}//end of subtract

void multiply(Complex &complex){
 
   cout<<"multiply() function: ";
   cout<<endl;
   //math
   Complex result;
   result.real = (complex.real * real) - (complex.imaginary * imaginary);
   result.imaginary = (complex.real * imaginary) + (complex.imaginary * real);
   
   //print out
    cout<<"("<< real<<" + "<<imaginary<<"i) * ("<<complex.real <<" + "<<complex.imaginary<<"i) = ";
    cout<<"("<<result.real<<" + "<<result.imaginary<<"i)";
    cout<<endl;

}//end of multiply 

void divide(Complex &complex){

  cout<<"divide() function: ";
  cout<<endl;
  
  //math
  Complex result;
  result.real = ((complex.real * real) + (complex.imaginary * imaginary)) / ((real * real) + (imaginary * imaginary));
  result.imaginary = ((complex.imaginary * real) - (complex.real * imaginary)) / ((real * real) + (imaginary * imaginary));
  
  //print
    cout<<"("<< real<<" + "<<imaginary<<"i) / ("<<complex.real <<" + "<<complex.imaginary<<"i) = ";  
    cout<<"("<<result.real<<" + "<<result.imaginary<<"i)";
    cout<<endl;

}//end of divide 

//destructor
~Complex(){
  cout<<"Destructor ("<<real<<" + "<<imaginary<<"i)";
  cout<<endl;

 
}//end of destructor



    
};//end of class Complex


int main(){

  Complex c1, c2, c3, c4;
  
  c1.set(1.1,2.3);
  c3.set(3.5,4.5); 
  c4.set(10.9,6);
  
  cout<<"Complex number c1 is: ";
  c1.print();
  
  cout<<"Copy Complex number for c1 is: ";
  c2.copy(c1);
  c2.print();
  //complex number 1 stuff
  cout<<"test c1 math functions :";
  cout<<endl;
  c2.add(c1);
  c2.subtract(c1);
  c2.multiply(c1);
  c2.divide(c1);
  cout<<endl;
  //complex number 2 stuff
  cout<<"test c2 math functions :";
  cout<<endl;
  c3.add(c3);
  c3.subtract(c3);
  c3.multiply(c3);
  c3.divide(c3);
  cout<<endl;
  //complex number 3 stuff
  cout<<"test c3 math functions :";
  cout<<endl;
  c4.add(c4);
  c4.subtract(c4);
  c4.multiply(c4);
  c4.divide(c4);
  cout<<endl;

 return 0;
}//end of main