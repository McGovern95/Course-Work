//CS 271
//Program Name: Lab5Test
//@author: Christian McGovern
//@date: 4/14/17
//This program demonstrates futher understanding of classes 
//and operator overloading 

#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include "Concert.h"
#include "Time.h"


int main(){
    //ends Concert 
	Concert test;
	//overloaded the >> operator 
	cin >> test;
	//overloaded the << operator 
	cout << test;
    cout << endl << endl;
    //testing the various functions 

    cout << "testing the mutators and accessors: " << endl;
   
    //setArtist(); and getArtist(); test
    cout << "setArtist(); and getArtist(); test (setting to 'The band'): ";
    test.setArtist("the band");
    cout << test.getArtist() << endl;
    //setPrice(); and getPrice(); test
    cout << "setPrice(); and getPrice(); test (setting to '69'): ";
    test.setPrice(69);
    cout << test.getPrice() << endl;
    //setLength(); and getLength(); test
    cout << "setLength(); and getLength(); test (setting to 1,20,8): ";
    Time t2(1,20,8);
    test.setLength(t2);
    test.getLength().printUniversal();
    cout << endl;








}//end main();

