#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

using namespace std;

// #define NAME_LEN				100

/* Person base class. Visitor and Staff will inherit from this */
class Person
{
	public:
		string name;
		char inTime[100]; //for inTime info
		char outTime[100]; //for outTime info
		bool checkInOut = false;

		Person() { string name = ""; }
};

/*MenuPrint class to print the menu. Just holds the print_menu function*/
class MenuPrint
{
	public:

		/*Displays user options for the museum. If you'd like, you can modify this to 
		do error checking and return the user's choice as an int*/
		void printMenu()
		{
			/* Show Menu */
			cout << endl;
			cout << "Welcome to Museum" << endl;
			cout << " 1. Visitor In" << endl;
			cout << " 2. Visitor Out" << endl;
			cout << " 3. Staff In" << endl;
			cout << " 4. Staff out" << endl;
			cout << " 5. Exit" << endl;
		}
};

#endif /* PERSON_H */