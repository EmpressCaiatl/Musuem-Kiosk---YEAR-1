#include <iostream>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include "staff.h"
using namespace std;

//Sets the staff's name
void Staff::setStaffDetails(string name) { this->name = name; } /*this refers to the current class variable name*/

string Staff::getName() const { return name; }

//Opens the file given by the staff_file_name string (char array) and appends staff info to the end of it
void Staff :: updateFile(Staff* staffPtr, char staff_file_name[50])
{
	ofstream fp;

    fp.open(staff_file_name, ios_base::app|ios_base::out); //Opens the file to append to the end, if it exists. Otherwise, opens a new file
	if (fp.is_open()) //If the file opened successfully
  	{
		fp << "STAFF_ENTRY" << endl;
		
		/*YOUR CODE HERE*/
		//get name, inTime, outTime

		fp << staffPtr->getName() << endl;
		fp << staffPtr->inTime << endl;
		fp << staffPtr->outTime << endl;

	}
	else
	{
		cout << "unable to open the file." << endl;
		return;
	}
	fp.close();

}
