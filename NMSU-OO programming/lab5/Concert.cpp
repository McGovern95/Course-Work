//Concert class member-function definitions 
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include "Concert.h"
#include "Time.h"
using namespace std;

//default constructor
//defualt values are 0 and "defualt" 
Concert::Concert(){
	artist = "default";
	length = 0;
	price = 0.0;
}//end Concert constructer 
//sets artist
Concert &Concert::setArtist(string a){
		
	if(a != " " )
	   artist = a;
	else
		throw invalid_argument("Please actually enter a name!");
	
	return *this;//enables cascading
}//end setArtist();
//sets length
Concert &Concert::setLength(Time l){
   //memberwise assignment 
    length = l;
}//end setLength();
//sets price
Concert &Concert::setPrice(float p){
		
	if(p >= 0)
	   price = p; 
	else 
		throw invalid_argument("They're not paying you to come here, stop lying.");

	return *this;//enables cascading 

}//end setPrice();

string Concert::getArtist() const{
	return artist;
}//end getArtist();
Time Concert::getLength() const{
	return length; //is a time object
}//end getLength()

float Concert::getPrice() const{
	return price;
}//end getPrice();
//function used to overload the << operator or the output cout operator
ostream & operator<<(ostream & out, const Concert & c){
     
    out << "Artist/Group: " << c.artist << endl << "Length of Concert: " 
	<< setfill('0') << setw(2) << c.length.getHour() << ":" << setw(2) 
	<< c.length.getMinute() << ":" << c.length.getSecond() << 
	endl << "Admission: $" << c.price;

	return out; 
}//end operator<<();
//function used to overload the >> operator or the the input cin operator 
istream & operator>>(istream & in, Concert & c){
    //input for setArtist();
	cout << "input the artists name: ";
	string a;
	getline(in,a);//used for letting the input of spaces
	c.setArtist(a);
 	//input for setLength();
	cout << "input the length of the concert starting with hours: ";
	int h;
	in >> h;
	c.length.setHour(h);

	cout << "Now minutes please: ";
	int m;
	in >> m;
	c.length.setMinute(m);

	cout << "Now seconds please: ";
	int s;
	in >> s;
	c.length.setSecond(s);
    //input for setPrice();
	cout << "input the price of admission: ";
	float p;
	in >> p;
	c.setPrice(p);

	return in;
}//end operator>>();