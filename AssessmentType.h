#pragma once
#include "Assessment.h"
using namespace std;

class Exam: public Assessment{
private:
float examScore;

public:
Exam( float weightage, float raw,float a =0.0): Assessment(weightage, raw)
{
    examScore = a;
}

float finalScoreCalculator() override {
    return (examScore/(float)100.0)* weightage;
};
};

class Quiz: public Assessment{
private:
float quizScore;

public:
Quiz(float a =0.0, float weightage, float raw): Assessment(weightage, raw)
{
    quizScore =a ;
}

float finalScoreCalculator() override {
    return (quizScore/(float)100.0)* weightage;
};
};

class Assignment: public Assessment{
private:
float AssignmentScore;

public:
Assignment(float a, float weightage, float raw): Assessment(weightage, raw)
{
    AssignmentScore =a;
}

float finalScoreCalculator() override {

    return (AssignmentScore/(float)100.0)* weightage;
};
};
