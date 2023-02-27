#include "visitor.h"
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <fstream>

using namespace std;

//Sets the Visitor's name and age.
void Visitor::setVisitorDetails(string name, int age)
{
	this->age = age;
	this->name = name;
}

/*Updates the Visitor log with the Visitor's information. Opens a file described by the visitor_file_name
string (char array) and then appends the information of the Visitor being pointed to*/
void Visitor :: updateFile(Visitor *visitorPtr, char visitor_file_name[50])
{
	/*YOUR CODE HERE*/
	//similar to staff.cpp
	//after file open 
	// fp << "VISITOR_ENTRY" << endl;
	//get name, age, inTime, outTime	

	ofstream fp;

	fp.open(visitor_file_name, ios_base::app | ios_base::out); //Opens the file to append to the end, if it exists. Otherwise, opens a new file
	if (fp.is_open()) //If the file opened successfully
	{
		fp << "VISITOR_ENTRY" << endl;
		fp << visitorPtr->getName() << endl;
		fp << visitorPtr->inTime << endl;
		fp << visitorPtr->outTime << endl;

	}
	else
	{
		cout << "unable to open the file." << endl;
		return;
	}
	fp.close();
}
