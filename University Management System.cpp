#include <iostream>
using namespace std;

class AcademicEntity{

protected:
string ID;
string name;
string email;

public:
virtual void displayProfile() =0;
};

class ScholarshipStudent: public AcademicEntity{
private:
float GPA;

public:

};

class ExchangeStudent: public AcademicEntity{

private:
bool Credits;

public:

};

class RegularStudent{
private:
char grade;

public:


};


class Courses{
protected:
string coursecode;
string courseName;
string file_path;

public:



};

class CoreCourse: public Courses{
private:
float weightage;
float examscore;
string timeSlot;

public:


};

class ElectiveCourse: public Courses{
private:
float weightage;
float Assignmentscore;
float finalprojectscore;
float timeSlot;

public:

};

class LabCourse: public Courses{
private:
float weightage;
float assessmentscore;
string venue;

public:

};

int main()
{

}