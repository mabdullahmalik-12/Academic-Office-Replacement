#pragma once
#include <string>
#include <iostream>
using namespace std;

class Venues{
protected:
string roomID;
int Capacity;
bool hasComp;

public:
Venues(string ID = 0, int cap= 50, bool comp = true)
{
    roomID = ID;
    Capacity = cap;
    hasComp = comp;
}

~Venues()
{

}

void displayVenue()
{
    //TODO: read venue from the file 
}

void setroomID(string id)
{
    roomID = id;
}

void setCapacity(int cap)
{
    Capacity = cap;
}

void setComputers(bool a)
{
    hasComp =a;
}

string getRoomID()          
{
return roomID; 
}

int    getCapacity()        
{
return Capacity; 
}

bool   getHasComp()         
{
return hasComp; 
}


};