//Concert class definitions 
#ifndef CONCERT_H
#define CONCERT_H

#include <iostream>
#include "Time.h"
using namespace std;

class Concert{

  //friend prototypes 
	friend ostream & operator<<(ostream & out, const Concert & c);//overload << operator 
	friend istream & operator>>(istream & in, Concert & c);//overload >> operator 

public: 
  
  //defualt constructor 
  Concert();
  //mutator/set fucntions 
  Concert &setArtist(string);//set artist
  Concert &setLength(Time);//set Length
  Concert &setPrice(float);//set price 
  //accessor/get functions | all const 
  string getArtist() const;//return artist
  Time getLength() const; //return length
  float getPrice() const; //return price 
    
private: 
  string artist;
  Time length; //Time object file
  float price; 
};//end class Concert

#endif