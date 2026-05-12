#pragma once
using namespace std;


class Assessment{
protected:
float weightage;
float rawscore;

public:
Assessment(float a = 0.0, float b =0.0)
{
    weightage =a;
    rawscore =b;
}

virtual float finalScoreCalculator() =0;
};