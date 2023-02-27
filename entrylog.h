#ifndef ENTRYLOG_H
#define ENTRYLOG_H

#include "staff.h"
#include "visitor.h"
#include <time.h>
#include <fstream>

using namespace std;

/*EntryLog class that logs information about People, whether they are Visitors or Staff
This should manage files based on what is called in main*/
class EntryLog
{
  //Staff variables

  Staff *headptr_staff; //Array of all of the Staff currently in the museum. This is dynamically allocated, hence the pointer.
  int staff_index; //Current index to insert into Staff array
  string staff_password; //Password for Staff log in
  char staff_file_name[50]; //File name to write Staff info to. This is a string done as a char array.

  //Visitor variables

  Visitor *headptr_visitor; //Pointer to an array of all of the Visitors currently in the museum. 
  int visitor_index; //Current index to insert into Visitor array
  char visitor_file_name[50];
  int age; //Temp age of the Visitor for reading in before giving to the Visitor constructor
  char vote; //While visitor-out selection of choice as vote 

  //Admin variables

  string admin_password; //Admin password for logging in as admin
  string admin_username; //Admin username for logging in as admin
  string tempName; //identifier for name verification of admin

  //identifiers in common for entries in and out (reusable variables?)
  bool found;
  string tempPass; //identifier for staff password verification
  string name; //identifier for staff name and visitor name

  public:
    Review winCount; //Keeps track of Visitor's favorite room from their visit

    EntryLog(); //default constructor
    ~EntryLog(); //destructor- To deallocate memory heap
    
    //Main functions
    void visitorIn(); //fuction for visitor-in
    void visitorOut(); //fuction for visitor-out
    void staffIn(); //fuction for staff-in
    void staffOut(); //fuction for staff-out
    bool exitMain(); //fuction for admin-exit
};

#endif
