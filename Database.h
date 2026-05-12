#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include "Student.h"
#include "Teachers.h"
#include "Courses.h"
#include "sections.h"
#include "Venue.h"
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
DataBase(string sf = "Students.txt", string tf = "Teachers.txt", string cf = "Courses.txt", string secf = "sections.txt", string vf = "Venues.txt", string scf = "StudentCourses.txt", string tcf = "TeacherCourses.txt")
{
    studentsFile = sf;
    teachersFile = tf;
    coursesFile = cf;
    sectionsFile = secf;
    venuesFile = vf;
    studentCoursesFile = scf;
    teacherCoursesFile = tcf;
    studentCount = 0;
    teacherCount = 0;
    courseCount = 0;
    sectionCount = 0;
    venueCount = 0;
}

void saveStudent(Student* s)
{
    ofstream file(studentsFile, ios::app);
    if(!file.is_open()) { cout << "Error opening students file." << endl; return; }
    file << s->getID() << "|" << s->getName() << "|" << s->getEmail() << "|" << s->getType() << "|" << s->getGPA() << endl;
    file.close();
}

void loadStudents()
{
    studentCount = 0;
    ifstream file(studentsFile);
    if(!file.is_open()) { cout << "Error opening students file." << endl; return; }
    string line;
    while(getline(file, line))
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string id, name, email, type, gpaStr;
        getline(ss, id,     '|');
        getline(ss, name,   '|');
        getline(ss, email,  '|');
        getline(ss, type,   '|');
        getline(ss, gpaStr, '|');
        if(id.empty()) continue;
        float gpa = 0.0;
        try { gpa = stof(gpaStr); } catch(...) { gpa = 0.0; }
        if(type == "Regular")
            students[studentCount++] = new RegularStudent('-', gpa, id, name, email);
        else if(type == "Scholarship")
            students[studentCount++] = new ScholarshipStudent(true, gpa, id, name, email);
        else if(type == "Exchange")
            students[studentCount++] = new ExchangeStudent(true, gpa, id, name, email);
    }
    file.close();
}

void updateStudentGPA(string studentID, float newGPA)
{
    loadStudents();
    ofstream file(studentsFile, ios::trunc);
    if(!file.is_open()) { cout << "Error opening students file." << endl; return; }
    for(int i = 0; i < studentCount; i++)
    {
        if(students[i]->getID() == studentID) students[i]->setGPA(newGPA);
        file << students[i]->getID() << "|" << students[i]->getName() << "|" << students[i]->getEmail() << "|" << students[i]->getType() << "|" << students[i]->getGPA() << endl;
    }
    file.close();
}

void saveTeacher(Teachers* t)
{
    ofstream file(teachersFile, ios::app);
    if(!file.is_open()) { cout << "Error opening teachers file." << endl; return; }
    file << t->getID() << "|" << t->getName() << "|" << t->getEmail() << "|" << t->getAverageFeedback() << endl;
    file.close();
}

void loadTeachers()
{
    teacherCount = 0;
    ifstream file(teachersFile);
    if(!file.is_open()) { cout << "Error opening teachers file." << endl; return; }
    string line;
    while(getline(file, line))
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string id, name, email, avgStr;
        getline(ss, id,     '|');
        getline(ss, name,   '|');
        getline(ss, email,  '|');
        getline(ss, avgStr, '|');
        if(id.empty()) continue;
        float avg = 0.0;
        try { avg = stof(avgStr); } catch(...) { avg = 0.0; }
        teachers[teacherCount] = new Teachers(id, name, email);
        teachers[teacherCount]->setAverageFeedback(avg);
        teacherCount++;
    }
    file.close();
}

void updateTeacherFeedback(string teacherID, float newAvg)
{
    loadTeachers();
    ofstream file(teachersFile, ios::trunc);
    if(!file.is_open()) { cout << "Error opening teachers file." << endl; return; }
    for(int i = 0; i < teacherCount; i++)
    {
        if(teachers[i]->getID() == teacherID) teachers[i]->setAverageFeedback(newAvg);
        file << teachers[i]->getID() << "|" << teachers[i]->getName() << "|" << teachers[i]->getEmail() << "|" << teachers[i]->getAverageFeedback() << endl;
    }
    file.close();
}

void saveCourses(Courses* c)
{
    ofstream file(coursesFile, ios::app);
    if(!file.is_open()) { cout << "Error opening courses file." << endl; return; }
    file << c->getCourseCode() << "|" << c->getCourseName() << "|" << c->getTeacherID() << "|" << c->getCourseType() << endl;
    file.close();
}

void loadCourses()
{
    courseCount = 0;
    ifstream file(coursesFile);
    if(!file.is_open()) { cout << "Error opening courses file." << endl; return; }
    string line;
    while(getline(file, line))
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string code, name, teachID, type;
        getline(ss, code,    '|');
        getline(ss, name,    '|');
        getline(ss, teachID, '|');
        getline(ss, type,    '|');
        if(code.empty()) continue;
        if(type == "Core")
            courses[courseCount++] = new CoreCourse(code, name);
        else if(type == "Elective")
            courses[courseCount++] = new ElectiveCourse(0.0, 0.0, "00:00", "----", code, name);
        else if(type == "Lab")
            courses[courseCount++] = new LabCourse(0.0, "00:00", "----", code, name);
        else
            continue;
        courses[courseCount - 1]->setTeacherID(teachID);
    }
    file.close();
}

void saveSection(Section* s)
{
    ofstream file(sectionsFile, ios::app);
    if(!file.is_open()) { cout << "Error opening sections file." << endl; return; }
    file << s->getSectionID() << "|" << s->getCourseID() << "|" << s->getTeacherID() << "|" << s->getVenueID() << "|" << s->getTimeSlot() << endl;
    file.close();
}

void loadSection()
{
    sectionCount = 0;
    ifstream file(sectionsFile);
    if(!file.is_open()) { cout << "Error opening sections file." << endl; return; }
    string line;
    while(getline(file, line))
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string sID, cID, tID, vID, slot;
        getline(ss, sID,  '|');
        getline(ss, cID,  '|');
        getline(ss, tID,  '|');
        getline(ss, vID,  '|');
        getline(ss, slot, '|');
        if(sID.empty()) continue;
        sections[sectionCount++] = new Section(sID, cID, tID, vID, slot);
    }
    file.close();
}

void saveVenue(Venues* v)
{
    ofstream file(venuesFile, ios::app);
    if(!file.is_open()) { cout << "Error opening venues file." << endl; return; }
    file << v->getRoomID() << "|" << v->getCapacity() << "|" << v->getHasComp() << endl;
    file.close();
}

void loadVenues()
{
    venueCount = 0;
    ifstream file(venuesFile);
    if(!file.is_open()) { cout << "Error opening venues file." << endl; return; }
    string line;
    while(getline(file, line))
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string rID, capStr, compStr;
        getline(ss, rID,     '|');
        getline(ss, capStr,  '|');
        getline(ss, compStr, '|');
        if(rID.empty()) continue;
        int cap = 0;
        try { cap = stoi(capStr); } catch(...) { cap = 0; }
        venues[venueCount++] = new Venues(rID, cap, compStr == "1");
    }
    file.close();
}

void saveStudentCourse(string studentID, string courseID, float grade)
{
    ofstream file(studentCoursesFile, ios::app);
    if(!file.is_open()) { cout << "Error opening student courses file." << endl; return; }
    file << studentID << "|" << courseID << "|" << grade << endl;
    file.close();
}

void loadStudentCourses(string studentID)
{
    ifstream file(studentCoursesFile);
    if(!file.is_open()) { cout << "No course records found." << endl; return; }
    bool found = false;
    string line;
    cout << "-------------------------" << endl;
    cout << "  Enrolled Courses" << endl;
    cout << "-------------------------" << endl;
    while(getline(file, line))
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string sID, cID, gradeStr;
        getline(ss, sID,      '|');
        getline(ss, cID,      '|');
        getline(ss, gradeStr, '|');
        if(sID == studentID)
        {
            cout << "Course : " << cID << endl;
            cout << "Grade  : " << (gradeStr == "0" || gradeStr == "0.000000" ? "Not graded yet" : gradeStr) << endl;
            cout << endl;
            found = true;
        }
    }
    if(!found) cout << "No courses enrolled yet." << endl;
    file.close();
}

void updateStudentGrade(string studentID, string courseID, float grade)
{
    ifstream file(studentCoursesFile);
    if(!file.is_open()) { cout << "Error opening student courses file." << endl; return; }
    string lines[500];
    int count = 0;
    string line;
    while(getline(file, line))
        if(!line.empty()) lines[count++] = line;
    file.close();
    ofstream out(studentCoursesFile, ios::trunc);
    for(int i = 0; i < count; i++)
    {
        stringstream ss(lines[i]);
        string sID, cID, gradeStr;
        getline(ss, sID,      '|');
        getline(ss, cID,      '|');
        getline(ss, gradeStr, '|');
        if(sID == studentID && cID == courseID)
            out << sID << "|" << cID << "|" << grade << endl;
        else
            out << lines[i] << endl;
    }
    out.close();
}

void saveTeacherCourse(string teacherID, string courseID)
{
    ofstream file(teacherCoursesFile, ios::app);
    if(!file.is_open()) { cout << "Error opening teacher courses file." << endl; return; }
    file << teacherID << "|" << courseID << endl;
    file.close();
}

void loadTeacherCourses(string teacherID)
{
    ifstream file(teacherCoursesFile);
    if(!file.is_open()) { cout << "No course records found." << endl; return; }
    bool found = false;
    string line;
    cout << "-------------------------" << endl;
    cout << "  Assigned Courses" << endl;
    cout << "-------------------------" << endl;
    while(getline(file, line))
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string tID, cID;
        getline(ss, tID, '|');
        getline(ss, cID, '|');
        if(tID == teacherID)
        {
            cout << "Course: " << cID << endl;
            found = true;
        }
    }
    if(!found) cout << "No courses assigned yet." << endl;
    file.close();
}

void saveWeightages(string courseType, int Exam = 50, int Quiz = 30, int Assignment = 20)
{
    ofstream file("Weightages.txt", ios::app);
    if(!file.is_open()) { cout << "Error opening weightages file." << endl; return; }
    file << courseType << "|" << Exam << "|" << Quiz << "|" << Assignment << endl;
    file.close();
}

void loadWeightages()
{
    ifstream file("Weightages.txt");
    if(!file.is_open()) { cout << "No weightages file found." << endl; return; }
    string line;
    cout << "-------------------------" << endl;
    cout << "  Course Weightages" << endl;
    cout << "-------------------------" << endl;
    while(getline(file, line))
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string type, examStr, quizStr, assignStr;
        getline(ss, type,      '|');
        getline(ss, examStr,   '|');
        getline(ss, quizStr,   '|');
        getline(ss, assignStr, '|');
        cout << "Type       : " << type << endl;
        cout << "Exam       : " << examStr << "%" << endl;
        cout << "Quiz       : " << quizStr << "%" << endl;
        cout << "Assignment : " << assignStr << "%" << endl;
        cout << endl;
    }
    file.close();
}

Student*  getStudent(int i)  { return students[i]; }
Teachers* getTeachers(int i) { return teachers[i]; }
Courses*  getCourses(int i)  { return courses[i]; }
Section*  getSection(int i)  { return sections[i]; }
Venues*   getVenues(int i)   { return venues[i]; }

int getStudentCount()  { return studentCount; }
int getTeacherCount()  { return teacherCount; }
int getCoursesCount()  { return courseCount; }
int getSectionCount()  { return sectionCount; }
int getVenueCount()    { return venueCount; }

Section** getSections()  { return sections; }
Venues**  getVenuesArr() { return venues; }

bool studentExists(string id)
{
    loadStudents();
    for(int i = 0; i < studentCount; i++)
        if(students[i]->getID() == id) return true;
    return false;
}

bool teacherExists(string id)
{
    loadTeachers();
    for(int i = 0; i < teacherCount; i++)
        if(teachers[i]->getID() == id) return true;
    return false;
}

bool courseExists(string code)
{
    loadCourses();
    for(int i = 0; i < courseCount; i++)
        if(courses[i]->getCourseCode() == code) return true;
    return false;
}

bool isStudentRegistered(string studentID, string courseID)
{
    ifstream file(studentCoursesFile);
    if(!file.is_open()) return false;
    string line;
    while(getline(file, line))
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string sID, cID, grade;
        getline(ss, sID,   '|');
        getline(ss, cID,   '|');
        getline(ss, grade, '|');
        if(sID == studentID && cID == courseID) { file.close(); return true; }
    }
    file.close();
    return false;
}
};
