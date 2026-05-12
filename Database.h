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

};
void loadStudents(){

};

void saveTeacher(Teachers* t)
{

};
void loadTeachers(){

};

void saveCourses(Courses*c)
{

};
void loadCourses();


void saveSection(Section* s)
{

};
void loadSection(){

};

void saveVenue(Venues* v)
{

};
void loadVenues()
{

};

void saveStudentCourse(string studentID, string courseID, float grade)
{

};
void loadStudentCourses(string studentID)
{

};

void saveTeacherCourse(string teacherID, string courseID)
{

};
void loadTeacherCourses(string teacherID)
{
    
};

};