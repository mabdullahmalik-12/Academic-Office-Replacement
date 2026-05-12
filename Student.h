#pragma once
#include "AcademicEntity.h"
using namespace std;


class Student : public AcademicEntity {
protected:
    float GPA;

public:

Student(float a = 0.0,string str = "0000", string b ="----", string c ="xyz@gmail.com"): AcademicEntity(str,b,c)
{
    GPA =a;
}
    virtual void viewTranscript() = 0;
};

class ScholarshipStudent: public Student{
private:
bool status;
public:
ScholarshipStudent(bool a = true, float val = 0.0,string str = "0000", string b ="----", string c ="xyz@gmail.com"): Student(val, str,b,c)
{
    status = a;
}
void displayProfile() override {
    cout << "Student Name: " << name << endl;
    cout << "Student ID: " << ID << endl;
    cout << "Student Email: " << email <<endl;
 };  
void viewTranscript() override { 
    cout << "Student Name: " << name <<endl;
    cout << "Student ID: " << ID <<endl;
    cout << "GPA: " << GPA <<endl;
    cout << "Student Status: "<< status << endl;
    //TODO: read enrolled courses and grades from file
};

};

class ExchangeStudent: public Student{

private:
bool Credits;

public:
ExchangeStudent(bool a = true, float val = 0.0,string str = "0000", string b ="----", string c ="xyz@gmail.com"): Student(val, str,b,c)
{
    Credits = a;
}

void displayProfile() override { 
    cout << "Student Name: " << name << endl;
    cout << "Student ID: " << ID << endl;
    cout << "Student Email: " << email <<endl;
};  
void viewTranscript() override { 
    cout << "Student Name: " << name <<endl;
    cout << "Student ID: " << ID <<endl;
    cout << "GPA: " <<GPA <<endl;
    if(Credits == true)
    cout << "Student Credits: Pass" << endl;
    else
    cout << "Student Credits: Fail" <<endl;
    //TODO: read enrolled courses and grades from file
};
};

class RegularStudent: public Student{
private:
char grade;
public:
RegularStudent(char a ='-', float val = 0.0,string str = "0000", string b ="----", string c ="xyz@gmail.com"): Student(val, str,b,c)
{
    grade = a;
}

void displayProfile() override {
    cout << "Student Name: " << name << endl;
    cout << "Student ID: " << ID << endl;
    cout << "Student Email: " << email <<endl;
 };  
void viewTranscript() override { 
    cout << "Student Name: " << name <<endl;
    cout << "Student ID: " << ID <<endl;
    cout << "GPA: " << GPA <<endl;
    //TODO: read enrolled courses and grades from file
};
};