/*
 Program which demonstrates derived classes using circles and cylinders
 */

#include <iostream>
 using namespace std;

//base class Circle
 class Circle{

  protected:
  	   double height;
  	   double radius;

  public: 
    
     static const double PI = 3.1415926;
     static const double ZERO = 0.0; 



 Circle(){
       
      setHeight(ZERO);
      setRadius(ZERO);

 }

 Circle(double height2, double radius2){
 	setHeight(height2);
 	setRadius(radius2);
 }

 char * name() const{
 	return "Circle: ";
 }
//set function
void setHeight(double height2){
	height = height2;
}
//set function
void setRadius(double radius2){
	radius = radius2;
}
//get function
double getHeight() const{
	return height;
}
//get function
double getRadius() const{
	return radius;
}
//area of a circle
double area() const{
	return PI * (radius * radius);
}
//output operator
 friend ostream &operator<<(ostream &output, const Circle & circ){
 	output<<circ.name()<<"radius = "<<circ.radius<< ", area = "<<circ.area()<<endl
 	<<"testing the get() methods: "<<circ.getRadius();
 	 return output;
 }

 };//end of Circle 

class Cylinder: public Circle{

    public:

    //stuff from the base class
   Cylinder(): Circle(ZERO, ZERO){} 

   Cylinder(double height2, double radius2): Circle(height2, radius2){}
//simple name function
char * name() const{
    	return "Cylinder: ";
 }
  //calculate the area of a Cylinder
double area() const{
 return (2 * PI * radius * height) + (2 * PI * (radius * radius));
 }
   //calculate the volume of a Cylinder
double volume() const{
 return PI * (radius * radius) * height;
 }
//output operator
friend ostream &operator<<(ostream &output, const Cylinder & cyli){
 	output<<cyli.name()<<"height = "<<cyli.height<<", radius = "<<cyli.radius<<", Volume = "<<cyli.volume()<<", area = "<<cyli.area()<<endl
 	<<"data members: "<<cyli.getRadius()<<","<<cyli.getHeight();
 	 return output;
 }



 };//end of Cylinder

 int main() {
    //circle test
    Circle cir1;
    cout<<"cir1 test: "<<endl;
    cir1.setRadius(10);
    cout<<cir1<<endl;
    //cylinder 1 test
    Cylinder cyl1;
    cout<<"cyl1 test: "<<endl;
    cyl1.setRadius(20);
    cyl1.setHeight(30);
    cout<<cyl1<<endl;
    //cylinder 2 test
    Cylinder cyl2;
    cout<<"cyl2 test: "<<endl;
    cyl2.setRadius(40);
    cyl2.setHeight(50);
    cout<<cyl2<<endl;

    

   return 0;
 }//end of main