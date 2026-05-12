#pragma once
#include <fstream>
#include <string>
#include "Student.h"
#include "Teachers.h"
#include "Courses.h"
#include "sections.h"
#include "Venue.h"
#include <sstream>
#include <fstream>
#include "CourseType.h"
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
Student* students[100];
int studentCount;
Teachers* teachers[100];
int teacherCount;
Courses* courses[100];
int courseCount;
Section* sections[100];
int sectionCount;
Venues* venues[100];
int venueCount;
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
    studentCount =0;
    teacherCount =0;
    courseCount =0;
    sectionCount =0;
    venueCount =0;
};

void saveStudent(Student * s)
{
ofstream file("Students.txt", ios::app);

    if(!file.is_open())
    {
        cout << "Error in opening student file" <<endl;
        return;
    }

    file << s->getID() << "|" << s->getName() << "|" << s->getEmail() << "|" << s->getType() << "|" << s->getGPA() << endl;
    file.close();
};
void loadStudents(){
ifstream file("Students.txt");
    if (!file.is_open()) {
        cout << "Error opening students file" << endl;
        return;
    }

string line;
while(getline(file,line))
{
    stringstream ss(line);
    string id, name, email,type, GPA;

    getline(ss, id, '|');
    getline(ss, name, '|');
    getline(ss, email, '|');
    getline(ss, type, '|');
    getline(ss, GPA, '|');

    float gpa = stof(GPA);

    if (type == "Regular")
            students[studentCount++] = new RegularStudent('-', gpa, id, name, email);
        else if (type == "Scholarship")
            students[studentCount++] = new ScholarshipStudent(true, gpa, id, name, email);
        else if (type == "Exchange")
            students[studentCount++] = new ExchangeStudent(true, gpa, id, name, email);

}

file.close();
};

void saveTeacher(Teachers* t)
{
ofstream file("Teachers.txt", ios::app);

    if(!file.is_open())
    {
        cout << "Error in opening student file" <<endl;
        return;
    }

file << t->getID() << "|" << t->getName() << "|"<< t->getEmail() << "|"  << t->getAverageFeedback() << endl;
file.close();
};
void loadTeachers(){
ifstream file("Teachers.txt");
    if (!file.is_open()) {
        cout << "Error opening teachers file" << endl;
        return;
    }

string line;
while(getline(file,line))
{
    stringstream ss(line);
    string id, name, email, avgStr;

    getline(ss, id,     '|');
    getline(ss, name,   '|');
    getline(ss, email,  '|');
    getline(ss, avgStr, '|');

    teachers[teacherCount] = new Teachers(id, name, email);
    teachers[teacherCount]->setAverageFeedback(stof(avgStr));
    teacherCount++;
}
file.close();
};

void saveCourses(Courses*c)
{
    ofstream file("Courses.txt", ios::app);

    if(!file.is_open())
    {
        cout << "Error in opening courses file" <<endl;
        return;
    }

    file << c->getCourseCode() << "|" << c->getCourseName() << "|" << c->getTeacherID() << "|" << c->getCourseType()<< endl;
};
void loadCourses()
{
    ifstream file("Courses.txt");
    if (!file.is_open()) {
        cout << "Error opening courses file" << endl;
        return;
    }

string line;
while(getline(file,line))
{
    stringstream ss(line);
    string code, name, teachID, type;

    getline(ss, code, '|');
    getline(ss, name, '|');
    getline(ss, teachID, '|');
    getline(ss, type, '|');


    if (type == "Core")
            courses[courseCount++] = new CoreCourse(code, name);
        else if (type == "Elective")
            courses[courseCount++] = new ElectiveCourse(0.0, 0.0, "00:00", "----", code, name);
        else if (type == "Lab")
            courses[courseCount++] = new LabCourse(0.0, "00:00", "----", code, name);
        courses[courseCount-1]->setTeacherID(teachID);

}

file.close();
};

void saveSection(Section* s)
{
    ofstream file("Section.txt", ios::app);

    if(!file.is_open())
    {
        cout << "Error in opening sections file" <<endl;
        return;
    }

    file << s->getSectionID() << "|" << s->getCourseID() << "|"<< s->getTeacherID() << "|" << s->getVenueID() << "|"<< s->getTimeSlot() << endl;
    file.close();
};
void loadSection(){
ifstream file(sectionsFile);
    if (!file.is_open()) { cout << "Error opening sections file" << endl; return; }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string sID, cID, tID, vID, slot;

        getline(ss, sID,  '|');
        getline(ss, cID,  '|');
        getline(ss, tID,  '|');
        getline(ss, vID,  '|');
        getline(ss, slot, '|');

        sections[sectionCount++] = new Section(sID, cID, tID, vID, slot);
    }
    file.close();
};

void saveVenue(Venues* v)
{
    ofstream file("Venues.txt", ios::app);

    if(!file.is_open())
    {
        cout << "Error in opening venues file" <<endl;
        return;
    }

    file << v->getRoomID() << "|" << v->getCapacity() << "|"<< v->getHasComp() << endl;
    file.close();
};
void loadVenues()
{
    ifstream file(venuesFile);
    if (!file.is_open()) { cout << "Error opening venues file" << endl; return; }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string rID, capStr, compStr;
        getline(ss, rID,     '|');
        getline(ss, capStr,  '|');
        getline(ss, compStr, '|');
        venues[venueCount++] = new Venues(rID, stoi(capStr), compStr == "1");
    }
    file.close();
};

void saveStudentCourse(string studentID, string courseID, float grade)
{
    ofstream file("StudentCourses.txt", ios::app);

    if(!file.is_open())
    {
        cout << "Error in opening studentcourses file" <<endl;
        return;
    }

    file << studentID << "|" << courseID << "|" << grade << endl;
    file.close();
};
void loadStudentCourses(string studentID)
{
ifstream file(studentCoursesFile);
    if (!file.is_open()) { cout << "Error opening student courses file" << endl; return; }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string sID, cID, gradeStr;
        getline(ss, sID,     '|');
        getline(ss, cID,     '|');
        getline(ss, gradeStr,'|');
        if (sID == studentID)
        cout << "Course: " << cID << " | Grade: " << gradeStr << endl;
    }
    file.close();
};

void saveTeacherCourse(string teacherID, string courseID)
{
    ofstream file("teacherCourses.txt", ios::app);

    if(!file.is_open())
    {
        cout << "Error in opening teachercourses file" <<endl;
        return;
    }

    file << teacherID << "|" << courseID << endl;
    file.close();
};
void loadTeacherCourses(string teacherID)
{
 ifstream file(teacherCoursesFile);
    if (!file.is_open()) { cout << "Error opening teacher courses file" << endl; return; }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string tID, cID;
        getline(ss, tID, '|');
        getline(ss, cID, '|');
        if (tID == teacherID)
            cout << "Course: " << cID << endl;
    }
    file.close();
};

Student* getStudent(int i){
    return students[i];
}

Teachers* getTeachers(int i){
    return teachers[i];
}

Courses* getCourses(int i){
    return courses[i];
}

Section* getSection(int i){
    return sections[i];
}

Venues* getVenues(int i)
{
    return venues[i];
}

int getStudentCount()
{
    return studentCount;
}

int getTeacherCount()
{
    return teacherCount;
}

int getCoursesCount()
{
    return courseCount;
}

int getSectionCount()
{
    return sectionCount;
}

int getVenueCount()
{
    return venueCount;
}
};