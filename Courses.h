#pragma once
#include <string>
using namespace std;

class Courses{
protected:
string coursecode;
string courseName;
string file_path;
string teacherID;
public:

Courses(string a = "0000", string b= "abcd", string c="nopath", string d ="0000")
{
    coursecode = a;
    courseName = b;
    file_path = c;
    teacherID = d;
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

string getTeacherID()
{
    return teacherID;
}

void setTeacherID(string a)
{
    teacherID =a;
}
virtual string getCourseType() =0;
};