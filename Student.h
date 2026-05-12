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

    void setGPA(float a)
    {
        GPA =a;
    }

    float getGPA()
    {
        return GPA;
    }

   virtual string getType() =0;
   virtual void calculateGPA()=0;
};

class ScholarshipStudent: public Student{
private:
bool status;
string file_path;
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
    if(status = true)
    cout << "Student Scholarship Status : Active" << endl;
    else
    cout << "Student Scholarship Status: Probation" <<endl;
    //TODO: read enrolled courses and grades from file
};

void setStatus(bool stat)
{
    status = stat;
}

bool getStatus()
{
    return status;
}

string getType() override
{
    return "Scholarship";
}

string getFilePath() {
    return file_path; 
}

void calculateGPA() override{

    if (GPA <(float)2.8)
    {
        status= false;
       cout << "Warning: " << name << " is on Probation! GPA " << GPA << " is below minimum GPA of 2.8" << endl;
    }

     else
    {
        status = true;
        cout << name << " is in good standing. GPA: " << GPA << endl;
    }
}
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

void setCredits(bool cred)
{
    Credits = cred;
}

bool getCredits()
{
    return Credits;
}

string getType() override
{
    return "Exchange";
}

void calculateGPA() override {
cout << "Exchange students use Pass/Fail only" << endl;
}
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

void setGrade(char g)
{
    grade = g;
}

char getGrade()
{
    return grade;
}

string getType() override
{
    return "Regular";
}

void calculateGPA() override {
    cout << "GPA: " << GPA << endl;
}
};