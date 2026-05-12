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

void setID(string id)
{
    ID = id;
}

void setName(string inp)
{
    name = inp;
}

void setEmail(string Email)
{
    email = Email;
}

string getID()
{
    return ID;
}
string getName()
{
    return name;
}

string getEmail()
{
    return email;
}

virtual void displayProfile() =0;
};