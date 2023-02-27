#include "entrylog.h"
#include "visitor.h"
#include "staff.h"
#include "person.h"
#include<string>
#include<sstream>
#include<fstream> 
#include<iostream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

//Function to check a Visitor in and log it in the Visitor log.
void EntryLog::visitorIn() //visitor.h
{
	//Allocate a new Visitor instance and keep a pointer to it
	Visitor* temp = new Visitor;

	// Get the required details from visitor 
	//Get the name and age, and handle errors (input failure or age being negative)

	cout << "Please enter the visitor name: ";
	cin >> temp->name;

	cout << "Please enter the visitor age: ";
	cin >> temp->age;

	//Check for bad number
	bool checkNeg = true;
	while (checkNeg) {

		if (temp->age < 0) {

			cout << "Error: Number must be 0 and above";
			cin >> temp->age;
		}
		else {

			checkNeg = false;
		}
	}
	
	//Check for failed input
	bool checkAge = true;
	while (checkAge) {

		if (cin.fail()) {

			cout << "Error: A number must be entered: ";
			cin >> temp->age;
		}
		else {
			checkAge = false;
		}
	}

	//Get the time 
	time_t now = time(0); //Gets the current time, in miliseconds, and stores it in a time_t type (very big integer)
	char* dt = ctime(&now);

	snprintf(temp->inTime, 100, "%s", dt); //print inTime of visitor
	

	/*Set the visitor details from temp name, age and delete temp
	(could also do this with an equal and don't delete pointer; less overhead)*/
	headptr_visitor[visitor_index].setVisitorDetails(temp->getName(), temp->getAge());

	//sets the fact that there is somebody inside the museum to true
	headptr_visitor[visitor_index].checkInOut = true;

    strcpy(headptr_visitor[visitor_index].inTime, temp->inTime);
	visitor_index++;
	headptr_visitor->visitorCount++;
	delete temp;

	//code to show the entered name and age after each entry

	for (int i = 0; i < visitor_index; i++) {
		
		//checks if that visitor in the array is blank (aka deleted), displays if array is not empty
		if (headptr_visitor[i].getName() != " ") {
			cout << "visitor-" << i + 1 << " " << headptr_visitor[i].getName() << '\t' << "visitor-" << i + 1 << " age: " << headptr_visitor[i].getAge() << endl;
		}
	}
}

/*Checks a Visitor out, prompting for their name and then searching through the array pointer to
by headptr_visitor to find them. Asks the user for their favorite exhibit and records it in the Review.
Also writes to the Visitor log*/
void EntryLog::visitorOut()
{
	
	//Get the time 
	time_t now = time(0); 
	char* dt = ctime(&now);

	//prompt for name
	string inputName;
	cout << "Please enter the visitor name: ";
	cin >> inputName;

	int databaseLoc = 0;   //variable for the location of the visitor in the database
	bool searching = false;
	//loops for checking the if the name is located in the array
	for (int j = 0; j < visitor_index; j++) {

		if (inputName == headptr_visitor[j].getName() && headptr_visitor[j].checkInOut != false) {

			databaseLoc = j;
			//when visitor checks out, they are not inside so bool turns false
			headptr_visitor[j].checkInOut = false;
			searching = true;
		}
	
	}
		
	if (!searching) {

		cout << "Err: Entered visitor name is not found in the visitor-in list. Try again!" << endl;
		return;
	}
	// Update the file 
	// else get the outTime and update it in the file of visitor

	headptr_visitor[databaseLoc].updateFile(&headptr_visitor[databaseLoc], visitor_file_name);

	//Erase the details/data of the visitor and free up that space in headptr_visitor. 
	//Consider setting to NULL or adding a count variable to EntryLog to tell when Visitor array is empty
	//setvisitordetails("", 0)

	//************
	//headptr_visitor[databaseLoc].setVisitorDetails("", 0); erases the visitor based on the location found above

	//code for feedback/voting after visitor_out
	char vote;

	cout << "Please give the votes for below rooms/objects:" << endl;
	cout << "Do you like the Art Rooms (y/n): ";
	cin >> vote;

	//if the user answers yes, it updates incraments the room they said yes to
	if (vote == 'y') {

		winCount.art_room++;

	}
	cout << "Do you like the Science Rooms (y/n): ";
	cin >> vote;

	if (vote == 'y') {

		winCount.science_room++;

	}
	cout << "Do you like Historic Object Rooms (y/n): ";
	cin >> vote;

	if (vote == 'y') {
				
		winCount.historic_object++;

	}
	cout << "** Thank you for coming! **" << endl << endl;
}

/*Checks a staff member in and records it in the Staff log*/
void EntryLog::staffIn()
{
	//Calculate the time- get the current time from your system
	time_t now = time(0);
	char* dt = ctime(&now);

	//use operator new to allocate a new variable
    
	Staff *temp_staff = new Staff;
	
  	// Get the required details from staff
	//details- name

	cout << "Please enter the staff name: ";
	cin >> temp_staff->name;
	
	// Prompt to enter the staff password and compare it */

	string staffP;
	cout << "Enter the staff password: ";
	cin >> staffP;

	if (staffP != staff_password) {

		cout << "Wrong Staff Password!!! Data entry incomplete..." << endl;
		return;

	}

	//prints inTime of staff   

	snprintf(temp_staff->inTime, 100, "%s", dt); //print inTime of visitor

    //setStaffDetails( )
    //copy inTime
    //increment staff index
    //delete temp

	headptr_staff[staff_index].setStaffDetails(temp_staff->getName());

	headptr_staff[staff_index].checkInOut = true;

	strcpy(headptr_staff[staff_index].inTime, temp_staff->inTime);
	staff_index++;
	headptr_staff->staffCount++;
	delete temp_staff;

    //code to show the entered staff name after each entry

	for (int i = 0; i < staff_index; i++) {

		//checks if that staff in the array is blank (aka deleted), displays if array is not empty
		if (headptr_staff[i].getName() != " ") {

			cout << "Staff-" << i + 1 << " " << headptr_staff[i].getName() << endl;

		}
	}

}

/*Checks a staff member out and records it in the Staff log*/
void EntryLog::staffOut()
{
	// Calculate the time- get the current time from your system
	time_t now = time(0);
    char* dt = ctime(&now);
	
    //Prompt to enter the name 
    // find the staff entry from database based on staff name 
	//Staff entry is not found in database entry, so return it with err logs

	string staffName;

	cout << "Please enter the staff name : ";
	cin >> staffName;

	int databaseLoc = 0;   //variable for the location of the staff in the database
	bool searching = false;

	for (int j = 0; j < staff_index; j++) {

		if (staffName == headptr_staff[j].getName() && headptr_staff[j].checkInOut != false) {

			databaseLoc = j;
			headptr_staff[j].checkInOut = false;
			searching = true;
		}
		
	}
	
	if (!searching) {

		cout << "Err: Entered staff name is not found in the staff-in list. Try again!" << endl;
		return;
	}

	//prompt to enter the password and compare it with staff_password

	string staffP;
	cout << "Please enter the staff password: ";
	cin >> staffP;

	if (staffP != staff_password) {

		cout << "Wrong Staff Password!!! Data entry incomplete..." << endl;
		return;

	}

	// pointer to the string buffer to write the outTime -----come back to this idk if this is right

	snprintf(headptr_staff[databaseLoc].outTime, 100, "%s", dt); //print outTime of visitor

	// update the file 
	headptr_staff[databaseLoc].updateFile(&headptr_staff[databaseLoc], staff_file_name);

    // Erase the details/data of the staff and free up that space in headptr_staff. 
	// set the staffdetails ("")
	headptr_staff[databaseLoc].setStaffDetails("");
}

/*Exits from the program, but only if all visitor are gone. Check the headptr_visitor to see if Visitors 
are still in the museum. If it is safe to close, displays the Staff that are still inside and returns true*/
bool EntryLog::exitMain()
{
	//Prompt the admin username and compare it with given admin username- 
	// if false reprompt menu and enter your choice

	string adminU;
	cout << "Please enter the admin username: ";
	cin >> adminU;

	//check username
	if (adminU != admin_username) {

		cout << "Wrong Admin Username!!!" << endl;
		return false;
	}
	
	string adminP;
	cout << "Please enter the admin password: ";
	cin >> adminP;

	//check password
	if (adminP != admin_password) {

		cout << "Wrong Admin Password!!!" << endl;
		return false;

	}
	
	bool insideVisitor = false;
	
	//show the details of visitors, who are still-in 
	//Reprompt menu if all the visitors are not out- Should not exit program until all visitors are out
	
	//check if visitor is still inside
	for (int k = 0; k < headptr_visitor->visitorCount; k++) {

		if (headptr_visitor[k].checkInOut == true) {

			cout << "Visitor (" << headptr_visitor[k].getName() << ", " << headptr_visitor[k].getAge() << ") is inside" << endl;

			insideVisitor = true;
		}

	}

	bool insideStaff = false;

	//show the details of staff, who are still-in 
	//Even the staff is in, there should not be any restriction to exit the program 
	

	//checks if staff is still inside
	for (int k = 0; k < headptr_staff->staffCount; k++) {

		if (headptr_staff[k].checkInOut == true) {

			cout << "Staff (" << headptr_staff[k].getName() << ") is inside" << endl;

			insideStaff = true;

		}
	}

	if (insideVisitor) {

		return false;

	}

	return true;
}

/*Default constructor for the EntryLog class. Sets default passwords and usernames. Allocates arrays 
for both Staff and Visitors*/
EntryLog::EntryLog(){ 
	headptr_staff= new Staff[100];
	staff_index = 0;
	admin_password = "welcome123";
	admin_username = "admin";
	staff_password = "staff123";
	strcpy(visitor_file_name,"visitor_log");
	strcpy(staff_file_name,"staff_log");
	headptr_visitor = new Visitor[100] ;
	visitor_index = 0;

	
	string tempPass="";
	string tempName="";
	bool found=false;

}

EntryLog::~EntryLog()
{
	//destructor
	// use delete operator to deallocate heap memory for headptr_visitor and headptr_staff

	// That is, use the delete[] operator to deallocate the Visitor and Staff arrays being
	//pointed to by headptr_visitor and headptr_staff
		
	delete[] headptr_visitor;
	delete[] headptr_staff;


}
