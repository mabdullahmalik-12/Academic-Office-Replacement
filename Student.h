#pragma once
#include "AcademicEntity.h"
using namespace std;


class Student : public AcademicEntity {
protected:
    float GPA;

public:

Student(float a = 0.0)
{
    GPA =a;
}
    virtual void viewTranscript() = 0;
};

class ScholarshipStudent: public Student{
private:
bool status;
public:
ScholarshipStudent(bool a = true)
{
    status = a;
}
void displayProfile() override { };  
void viewTranscript() override { };
};

class ExchangeStudent: public Student{

private:
bool Credits;

public:
ExchangeStudent(bool a = true)
{
    Credits = a;
}

void displayProfile() override { };  
void viewTranscript() override { };
};

class RegularStudent: public Student{
private:
char grade;

public:
RegularStudent(char a ='-')
{
    grade = a;
}

void displayProfile() override { };  
void viewTranscript() override { };
};