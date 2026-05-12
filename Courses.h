#pragma once
#include <string>
using namespace std;

class Courses{
protected:
string coursecode;
string courseName;
string file_path;

public:

Courses(string a = "0000", string b= "abcd", string c="nopath")
{
    coursecode = a;
    courseName = b;
    file_path = c;
}

virtual float calculateFinalGrade() = 0;
virtual float examDuration()=0;

string getCourseCode()          
{
return coursecode; 
}

string getCourseName()          
{
return courseName; 
}

void setCourseCode(string c)  
{
coursecode = c; 
}

void setCourseName(string n)  
{
courseName = n; 
}

virtual string getCourseType() =0;
};