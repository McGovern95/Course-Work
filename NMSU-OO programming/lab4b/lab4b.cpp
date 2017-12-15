//CS 271
//Program Name: lab4b
//Author: Christian McGovern
//Date: 3/10/17
//This program demonstrates an understanding of C++ Classes

#include <iostream>
#include <iomanip>
#include "BankAccount.h"

using namespace std;

	int main(){

        //two BankAccount objects I created
		BankAccount christianSavings("Christian", "McGovern", 1990);
		BankAccount johnDoe("John", "Doe", 6666);
        //my display(); function 
		christianSavings.display();
		johnDoe.display();

		//testing set functions
		//setting first,last, and account number to blank and zero
		christianSavings.setFirstName("");
		christianSavings.setLastName("");
		christianSavings.setAccountNumber(0);
		//testing get funcitons
         cout << "Getting First name: " << christianSavings.getFirstName() << endl;
         cout << "Getting Last Name: " << christianSavings.getLastName() << endl;
         cout << "Getting Account Number: " << christianSavings.getAccountNumber() << endl;
         cout << endl;
         cout << "Getting First name: " << johnDoe.getFirstName() << endl;
         cout << "Getting Last Name: " << johnDoe.getLastName() << endl;
         cout << "Getting Account Number: " << johnDoe.getAccountNumber() << endl;


       



	}//end main