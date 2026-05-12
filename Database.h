#pragma once
#include <fstream>
#include <string>
#include "Student.h"
#include "Teachers.h"
#include "Courses.h"
#include "sections.h"
#include "Venue.h"
using namespace std;


class DataBase{
protected:
string studentsFile;
string teachersFile;
string coursesFile;
string sectionsFile;
string venuesFile;
string studentCoursesFile;
string teacherCoursesFile;
public:
DataBase( string sf = "Students.txt",string tf = "Teachers.txt",string cf = "Courses.txt",string secf = "sections.txt",string vf = "Venues.txt", string scf  = "StudentCourses.txt",string tcf  = "TeacherCourses.txt")
{
    studentsFile = sf;
    teachersFile = tf;
    coursesFile = cf;
    sectionsFile = secf;
    venuesFile = vf;
    studentCoursesFile = scf;
    teacherCoursesFile = tcf;
};

void saveStudent(Student * s)
{
ofstream file("Students.txt", ios::app);

    if(!file.is_open())
    {
        cout << "Error in opening student file" <<endl;
        return;
    }

    file << s->getID() << "|" << s->getName() << "|" << s->getType() << "|" << s->getGPA() << endl;
    file.close();
};

void loadStudents(){

};

void saveTeacher(Teachers* t)
{
ofstream file("Teachers.txt", ios::app);

    if(!file.is_open())
    {
        cout << "Error in opening student file" <<endl;
        return;
    }

file << t->getID() << "|" << t->getName() << "|" << t->getAverageFeedback() << endl;
file.close();
};
void loadTeachers(){

};

void saveCourses(Courses*c)
{
    ofstream file("Courses.txt", ios::app);

    if(!file.is_open())
    {
        cout << "Error in opening student file" <<endl;
        return;
    }

    file << c->getCourseCode() << "|" << c->getCourseName() << "|" << c->getCourseType()<< "|"; //Add teacherID by searching ;
};
void loadCourses();


void saveSection(Section* s)
{
    ofstream file("Courses.txt", ios::app);

    if(!file.is_open())
    {
        cout << "Error in opening student file" <<endl;
        return;
    }
};
void loadSection(){

};

void saveVenue(Venues* v)
{
    ofstream file("Courses.txt", ios::app);

    if(!file.is_open())
    {
        cout << "Error in opening student file" <<endl;
        return;
    }
};
void loadVenues()
{

};

void saveStudentCourse(string studentID, string courseID, float grade)
{
    ofstream file("Courses.txt", ios::app);

    if(!file.is_open())
    {
        cout << "Error in opening student file" <<endl;
        return;
    }
};
void loadStudentCourses(string studentID)
{

};

void saveTeacherCourse(string teacherID, string courseID)
{
    ofstream file("Courses.txt", ios::app);

    if(!file.is_open())
    {
        cout << "Error in opening student file" <<endl;
        return;
    }
};
void loadTeacherCourses(string teacherID)
{

};

};