#pragma once
#include <string>
using namespace std;

class AcademicEntity{

protected:
string ID;
string name;
string email;

public:
AcademicEntity(string a = "0000", string b ="----", string c ="xyz@gmail.com")
{
    ID= a;
    name =b;
    email = c;
}

virtual void displayProfile() =0;
};