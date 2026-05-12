#pragma once
#include <string>
#include <iostream>
#include "Venue.h"
using namespace std;

class Section{
protected:
string sectionID;
string courseID;
string teacherID;
string venueID;
string timeSlot;

public:
Section(string sID=" ", string cID= " ", string tID= " ", string vID= " ", string TS =" ")
{
    sectionID = sID;
    courseID = cID;
    teacherID = tID;
    venueID = vID;
    timeSlot = TS;
}

void DisplaySection()
{
    cout << "Section ID: " << sectionID << endl;
    cout << "Course ID: " << courseID << endl;
    cout << "Teacher ID: " << teacherID << endl;
    cout << "Venue ID: " << venueID << endl;
    cout << "Time Slot: " << timeSlot << endl<<endl;
}


string getSectionID()           
{
return sectionID; 
}

string getCourseID()            
{ 
return courseID; 
}

string getTeacherID()           
{ 
return teacherID; 
}

string getVenueID()             
{ 
return venueID; 
}

string getTimeSlot()            
{ 
return timeSlot; 
}

void   setSectionID(string s)   
{ 
sectionID = s; 
}

void   setCourseID(string c)    
{ 
courseID = c; 
}

void   setTeacherID(string t)   
{ 
teacherID = t; 
}

void   setVenueID(string v)     
{ 
venueID = v; 
}

void   setTimeSlot(string t)    
{ 
timeSlot = t; 
}

};