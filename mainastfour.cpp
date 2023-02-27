#include<iostream>
#include<string>
#include<sstream>
#include<fstream> 

#include <fcntl.h>
#include <unistd.h>
#include "entrylog.h"
#include "visitor.h"
#include "staff.h"
#include "person.h"

using namespace std;

int main()
{
	bool exit = false;
	int choice = 0;
	
    EntryLog entry;
    MenuPrint menu;

	while (!exit)
	{
        menu.printMenu(); //Display the menu for the user

        cout << "Enter your choice:" << endl;
		
		cin >> choice;

		/*YOUR CODE HERE*/
        //Check for input validation. Make sure the read was good and potentially check if choice is
		//on the interval [1, 5]

		//checks choice on interval, clears the input if its not within the right bounds
		if (choice < 1 || choice > 5) {

			cin.clear();

		}

		//checks if the read in failed, will clear input and ignore until a new line to ensure a good read
		if (cin.fail()) {

			cout << "Invalid choice. Try again" << endl;
			cin.clear();
			cin.ignore('\n');
			continue;

		}
					
		switch (choice) //Handle the user selection
		{
			case 1:
				entry.visitorIn(); //Sign the Visitor in
				break;
			case 2:
				entry.visitorOut(); //Sign the Visitor out
				break;
			case 3:
				entry.staffIn(); //Sign the Staff in
				break;
			case 4:
				entry.staffOut(); //Sign the Staff out
				break;
			case 5:
				exit = entry.exitMain(); //call the exit_main, which is accessible by only admins
				break;
			default:
				cout << "Wrong Option! Please choose it again...!";
		}

	}

	/*YOUR CODE HERE*/
    //logic to output wincount based on voting from visitors during visitor-out 
	
	//checks if art is larger first
	if (entry.winCount.art_room > entry.winCount.historic_object) {

		//checks art compared to science
		if (entry.winCount.art_room > entry.winCount.science_room) {

			cout << " ART_ROOM is the winner today!" << endl;

		}
		else {

			cout << "SCIENCE_ROOM is the winner today!" << endl;

		}

	}
	else {

		//checks historic compared to science
		if (entry.winCount.historic_object > entry.winCount.science_room) {

			cout << "HISTORIC_OBJECT is the winner today!" << endl;

		}
		else {

			cout << "SCIENCE_ROOM is the winner today!" << endl;

		}

	}

	cout << "\nExiting the software, bye! bye!\n";
	return 0;
}



