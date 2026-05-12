#pragma once
#include "Courses.h"
#include "AssessmentType.h"
#include "Assessment.h"
using namespace std;

class CoreCourse: public Courses{
private:
float weightage;
string timeSlot;
string venue;
public:

CoreCourse(string code = "0000", string name = "----", string path = "no_path", float a =0.0, string c ="00:00", string d = "----"): Courses(code, name, path)
{
    weightage = a;
    timeSlot = c;
    venue= d;
    assessmentcount = 0;
}

float calculateFinalGrade() override{

    float total =0.0;
    for(int i =0; i < assessmentcount;i++)
    {
        total += assessments[i]->finalScoreCalculator();
    }

    return total;
};


float examDuration() override { return 180;}
string getCourseType() override
{
    return "Core";
}
};

class ElectiveCourse: public Courses{
private:
float weightage;
float finalprojectscore;
string timeSlot;
string venue;
public:

ElectiveCourse(float a =0.0, float c = 0, string d= "00:00", string e = "----", string code = "0000", string name = "----", string path = "no_path"): Courses(code, name, path)
{
    weightage = a;
    finalprojectscore = c;
    timeSlot = d;
    venue =e;
    
}

float calculateFinalGrade() override{

    float total =0.0;
    for(int i =0; i < assessmentcount;i++)
    {
        total += assessments[i]->finalScoreCalculator();
    }

    return total;
};


float examDuration() override {return 180;};

string getCourseType() override
{
    return "Elective";
}
};

class LabCourse: public Courses{
private:
float weightage;
string venue;
string timeSlot;
public:

LabCourse(float a =0.0, string c ="00:00", string d="----", string code = "0000", string name = "----", string path = "no_path"): Courses(code, name, path)
{
    
    weightage = a;
    timeSlot= c;
    venue = d;
    
}


float calculateFinalGrade() override{

    float total =0.0;
    for(int i =0; i < assessmentcount;i++)
    {
        total += assessments[i]->finalScoreCalculator();
    }

    return total;
};


float examDuration() override {return 180;};

string getCourseType() override
{
    return "Lab";
}
};