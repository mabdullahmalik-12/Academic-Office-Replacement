#pragma once
#include "Courses.h"
#include "AssessmentType.h"
#include "Assessment.h"
using namespace std;

class CoreCourse: public Courses{
private:
float weightage;
float examscore;
string timeSlot;
string venue;
Assessment* ptr;

public:

CoreCourse(float a =0.0, float b= 0, string c ="00:00", string d = "----",Assessment* pointer,  string code = "0000", string name = "----", string path = "no_path"): Courses(code, name, path)
{
    weightage = a;
    examscore = b;
    timeSlot = c;
    venue= d;
    *ptr = *pointer;
}

float calculateFinalGrade() override{};
float examDuration() override {};
};

class ElectiveCourse: public Courses{
private:
float weightage;
float Assignmentscore;
float finalprojectscore;
string timeSlot;
string venue;
Assessment* ptr;
public:

ElectiveCourse(float a =0.0, float b= 0, float c = 0, string d= "00:00", string e = "----",Assessment* pointer, string code = "0000", string name = "----", string path = "no_path"): Courses(code, name, path)
{
    weightage = a;
    Assignmentscore = b;
    finalprojectscore = c;
    timeSlot = d;
    venue =e;
    
}

float calculateFinalGrade() override{};
float examDuration() override {};
};

class LabCourse: public Courses{
private:
float weightage;
float assessmentscore;
string venue;
string timeSlot;
Assessment* ptr;

public:

LabCourse(float a =0.0, float b= 0, string c ="00:00", string d="----", string code = "0000", string name = "----", string path = "no_path"): Courses(code, name, path)
{
    
    weightage = a;
    assessmentscore = b;
    timeSlot= c;
    venue = d;
    
}

float calculateFinalGrade() override{};
float examDuration() override {};
};