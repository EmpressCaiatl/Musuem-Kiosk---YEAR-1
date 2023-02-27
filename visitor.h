#ifndef VISITOR_H
#define VISITOR_H

#include "person.h"
/* Visitor class */
class Visitor : public Person
{
	public:
		void setVisitorDetails(string name, int age); //Sets the name and the age of the visitor. Make sure to use "this" to distinguish parameters
		string getName() const { return name; }
		
		int age; //identifier for visitors age
		int getAge() const { return age; }

	    int visitorCount = 0;

		void updateFile(Visitor*, char visitor_file_name[50]);
};

/*Class that holds all of the Visitors' favorite rooms. Every time a Visitor votes for a specific room
as their favorite, it will be counted here.*/
class Review
{
public:
	int art_room;
	int science_room;
	int historic_object;

    Review()
    {
		//Initialize all rooms to have 0 votes as someone's favorite
    	art_room = 0;
    	science_room = 0;
    	historic_object = 0;
    }
};

#endif