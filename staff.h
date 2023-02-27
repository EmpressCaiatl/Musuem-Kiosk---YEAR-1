#ifndef STAFF_H
#define STAFF_H

#include "person.h"

class Staff : public Person
{
public:
	void updateFile(Staff *ptr, char staff_file_name[50]);
	void setStaffDetails(string name); 
    string getName() const;
	int staffCount = 0;
};

#endif