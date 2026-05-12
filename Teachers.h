#pragma once
#include <iostream>
# include <string>
#include "AcademicEntity.h"
using namespace std;


class Teachers: public AcademicEntity{
private:
int* ratings;          
int ratingCount;       
char** comments;       
int commentCount;      
int* assignedCourseIDs; 
int courseCount;       
float averageFeedback; 
string file_path;  
public:
Teachers(string id, string n, string e, int rating=10, int commentnum=10, int course=2, string path="Teachers.txt"): AcademicEntity(id, n,e)
{
    ratingCount = 0;
    ratings = new int[rating];
    commentCount = 0;
    comments = new char*[commentnum];

    for(int i =0; i <commentnum;i++)
    {
        comments[i] = new char[150];
    }

    courseCount = 0;
    assignedCourseIDs = new int[course];

    averageFeedback = 0.0;
    file_path= path;

}

~Teachers()
{
    delete[] ratings;
    
    for(int i = 0; i < commentCount; i++)
    {
        delete[] comments[i];
    }
    delete[] comments;
    
    delete[] assignedCourseIDs;
}

void displayProfile() override
{
    cout << "Teacher: " << name << endl;
    cout << "Teacher ID: " <<ID << endl;
    cout << "Teacher Email: " << email <<endl;
    cout << "Average Feedback: " <<averageFeedback << endl;
    // TODO: read assigned courses from file and display
}

float AverageFeedbackCalc()
{
    if (ratingCount == 0) return 0.0;
    float sum =0.0;
    for (int i =0; i < ratingCount;i++)
    {
        sum+= ratings[i];
    }

    averageFeedback = sum/ (float) ratingCount;
    return averageFeedback;
}

void AddRating(int r)
{
    ratings[ratingCount] = r;
    ratingCount++;

}

void AddComment(string comment)
{
    int commentsize =0;

    for(int i =0; comment[i] != '\0';i++)
    {
        commentsize++;
    }

    for(int i =0; i < commentsize;i++)
    {
        comments[commentCount][i] = comment[i];
    }

    comments[commentCount][commentsize] = '\0';
    commentCount++;
};

float getAverageFeedback()        
{ 
return averageFeedback;
};

void  setAverageFeedback(float f)
{
averageFeedback = f; 
};


};