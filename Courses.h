#pragma once
#include <string>
#include "Assessment.h"
using namespace std;

class Courses{
protected:
string coursecode;
string courseName;
string file_path;
string teacherID;
Assessment* assessments[3];
int assessmentcount;
int enrolledStudents;
int maxCapacity;
public:

Courses(string a = "0000", string b= "abcd", string c="nopath", string d ="0000")
{
    coursecode = a;
    courseName = b;
    file_path = c;
    teacherID = d;
    assessmentcount =0;
    enrolledStudents =0;
    maxCapacity =0;
}

virtual float calculateFinalGrade() = 0;
virtual float examDuration()=0;
virtual string getCourseType() = 0;
void addAssessment(Assessment* a)
{
   if(assessmentcount < 10)
    {
        assessments[assessmentcount] = a;
        assessmentcount++;
    }
    else
    cout << "Assessment limit reached for this course." << endl;
};

bool registerStudent()
{
    if(enrolledStudents >= maxCapacity)
    {
        cout << "Error: Course '" << coursecode << "' is full. Capacity: " << maxCapacity << endl;
        return false;
    }
    enrolledStudents++;
    return true;
}

void setEnrolledStudents(int n) {
    enrolledStudents = n; 
}
int getEnrolledStudents() {
    return enrolledStudents; 
}
int getMaxCapacity() {
    return maxCapacity; 
}
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

bool registerStudent(string studentID)
{
    if(enrolledStudents >= maxCapacity)
    {
        cout << "Course is Full" << endl;
        return false;
    }

    return true;
}

void setMaxCapacity(int c) {
    maxCapacity = c; 
}

};