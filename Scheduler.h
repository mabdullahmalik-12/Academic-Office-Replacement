#pragma once
#include <iostream>
#include "sections.h"
#include "Venue.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Scheduler {
    private:
    Section* sections[100];
    Venues* venues[100];
    int sectionCount;
    int venueCount;

    public:
     Scheduler(Section** s, int sc, Venues** v, int vc) {
        sectionCount = sc;
        venueCount = vc;

        for (int i = 0; i < sc; i++){
        sections[i] = s[i];
        }

        for (int i = 0; i < vc; i++){
        venues[i] = v[i];
        }
    }

    bool checkConflict(string venueID, string timeSlot) {
        ifstream file("ExamSchedule.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string sID, cID, vID, slot;
            getline(ss, sID,  '|');
            getline(ss, cID,  '|');
            getline(ss, vID,  '|');
            getline(ss, slot, '|');

            if (vID == venueID && slot == timeSlot) {
                file.close();
                return true;  
            }
        }
        file.close();
        return false;
    }

    string suggestNextSlot(string timeSlot) {
        string slots[] = {"08:00", "10:00", "12:00", "14:00", "16:00"};
        for (int i = 0; i < 5; i++) {
            if (slots[i] > timeSlot){
            return slots[i];
            }
        }
        return "09:00";  
    }

     void assignVenues() {
        ofstream file("ExamSchedule.txt", ios::app);
        if (!file.is_open()) {
            cout << "Error opening schedule file" << endl;
            return; 
        }

        for (int i = 0; i < sectionCount; i++) {
            string assignedVenue = "";
            string assignedSlot = sections[i]->getTimeSlot();

            for (int j = 0; j < venueCount; j++) {
                if (checkConflict(venues[j]->getRoomID(), assignedSlot)) {
                    cout << "Conflict at " << venues[j]->getRoomID()<< " at " << assignedSlot << endl;

                    assignedSlot = suggestNextSlot(assignedSlot);

                    cout << "Suggested new slot: " << assignedSlot << endl;
                } else {
                    assignedVenue = venues[j]->getRoomID();
                    break;
                }
            }

            if (assignedVenue.empty()) {
                cout << "No venue available for section: "<< sections[i]->getSectionID() << endl;
            } 
            
            else {
                file << sections[i]->getSectionID() << "|"<< sections[i]->getCourseID()  << "|"<< assignedVenue << "|"<< assignedSlot  << endl;
                cout << "Section " << sections[i]->getSectionID()<< " assigned to " << assignedVenue<< " at " << assignedSlot << endl;
            }
        }
        file.close();
    }
    

    
};
     