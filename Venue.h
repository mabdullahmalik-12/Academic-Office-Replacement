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

};