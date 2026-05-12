#include <iostream>
#include "Database.h"
using namespace std;

DataBase db;

void studentMenu() {
    int choice;
    cout << "=== STUDENT MENU ===" << endl;
    cout << "1. View Profile" << endl;
    cout << "2. View Transcript" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        string id;
        cout << "Enter Student ID: ";
        cin >> id;
        db.loadStudents();
        for (int i = 0; i < db.getStudentCount(); i++) {
            if (db.getStudent(i)->getID() == id) {
                db.getStudent(i)->displayProfile();
                break;
            }
        }
    }
    else if (choice == 2) {
        string id;
        cout << "Enter Student ID: ";
        cin >> id;
        db.loadStudentCourses(id);
    }
}

void teacherMenu() {
    int choice;
    cout << "=== TEACHER MENU ===" << endl;
    cout << "1. View Profile" << endl;
    cout << "2. Add Feedback" << endl;
    cout << "3. Enter Marks" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        string id;
        cout << "Enter Teacher ID: ";
        cin >> id;
        db.loadTeachers();
        for (int i = 0; i < db.getTeacherCount(); i++) {
            if (db.getTeachers(i)->getID() == id) {
                db.getTeachers(i)->displayProfile();
                break;
            }
        }
    }
    else if (choice == 2) {
        string id;
        int rating;
        string comment;
        cout << "Enter Teacher ID: ";
        cin >> id;
        cout << "Enter Rating (1-5): ";
        cin >> rating;
        cout << "Enter Comment: ";
        cin.ignore();
        getline(cin, comment);
        db.loadTeachers();
        for (int i = 0; i < db.getTeacherCount(); i++) {
            if (db.getTeachers(i)->getID() == id) {
                db.getTeachers(i)->AddRating(rating);
                db.getTeachers(i)->AddComment(comment);
                db.getTeachers(i)->AverageFeedbackCalc();
                db.saveTeacher(db.getTeachers(i));
                cout << "Feedback added successfully" << endl;
                break;
            }
        }
    }
    else if (choice == 3) {
        string courseCode;
        float score, weightage, maxScore;
        int type;
        cout << "Enter Course Code: ";
        cin >> courseCode;
        cout << "Enter Weightage: ";
        cin >> weightage;
        cout << "Enter Score: ";
        cin >> score;
        cout << "Enter Max Score: ";
        cin >> maxScore;
        cout << "Assessment Type [1]Exam [2]Quiz [3]Assignment: ";
        cin >> type;

        db.loadCourses();
        for (int i = 0; i < db.getCoursesCount(); i++) {
            if (db.getCourses(i)->getCourseCode() == courseCode) {
                Assessment* a;
                if (type == 1) a = new Exam(weightage, maxScore, score);
                else if (type == 2) a = new Quiz(weightage, maxScore, score);
                else a = new Assignment(score, weightage, maxScore);
                // db.getCourses(i)->addAssessment(a);
                cout << "Final Grade: " << db.getCourses(i)->calculateFinalGrade() << endl;
                break;
            }
        }
    }
}

void adminMenu() {
    int choice;
    cout << "=== ADMIN MENU ===" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Add Teacher" << endl;
    cout << "3. Add Course" << endl;
    cout << "4. Add Venue" << endl;
    cout << "5. Add Section" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        string id, name, email;
        int type;
        cout << "Enter ID: ";    cin >> id;
        cout << "Enter Name: ";  cin.ignore(); getline(cin, name);
        cout << "Enter Email: "; cin >> email;
        cout << "Type [1]Regular [2]Scholarship [3]Exchange: ";
        cin >> type;
        Student* s;
        if (type == 1) s = new RegularStudent('-', 0.0, id, name, email);
        else if (type == 2) s = new ScholarshipStudent(true, 0.0, id, name, email);
        else s = new ExchangeStudent(true, 0.0, id, name, email);
        db.saveStudent(s);
        cout << "Student added successfully" << endl;
        delete s;
    }
    else if (choice == 2) {
        string id, name, email;
        cout << "Enter ID: ";    cin >> id;
        cout << "Enter Name: ";  cin.ignore(); getline(cin, name);
        cout << "Enter Email: "; cin >> email;
        Teachers* t = new Teachers(id, name, email);
        db.saveTeacher(t);
        cout << "Teacher added successfully" << endl;
        delete t;
    }
    else if (choice == 3) {
        string code, name, teacherID;
        int type;
        cout << "Enter Course Code: ";  cin >> code;
        cout << "Enter Course Name: ";  cin.ignore(); getline(cin, name);
        cout << "Enter Teacher ID: ";   cin >> teacherID;
        cout << "Type [1]Core [2]Elective [3]Lab: "; cin >> type;
        Courses* c;
        if (type == 1) c = new CoreCourse(code, name);
        else if (type == 2) c = new ElectiveCourse(0.0, 0.0, "00:00", "----", code, name);
        else c = new LabCourse(0.0, "00:00", "----", code, name);
        c->setTeacherID(teacherID);
        db.saveCourses(c);
        db.saveTeacherCourse(teacherID, code);
        cout << "Course added successfully" << endl;
        delete c;
    }
    else if (choice == 4) {
        string roomID;
        int capacity;
        int hasComp;
        cout << "Enter Room ID: ";    cin >> roomID;
        cout << "Enter Capacity: ";   cin >> capacity;
        cout << "Has Computers [1]Yes [0]No: "; cin >> hasComp;
        Venues* v = new Venues(roomID, capacity, hasComp == 1);
        db.saveVenue(v);
        cout << "Venue added successfully" << endl;
        delete v;
    }
    else if (choice == 5) {
        string sID, cID, tID, vID, slot;
        cout << "Enter Section ID: ";  cin >> sID;
        cout << "Enter Course ID: ";   cin >> cID;
        cout << "Enter Teacher ID: ";  cin >> tID;
        cout << "Enter Venue ID: ";    cin >> vID;
        cout << "Enter Time Slot: ";   cin.ignore(); getline(cin, slot);
        Section* s = new Section(sID, cID, tID, vID, slot);
        db.saveSection(s);
        cout << "Section added successfully" << endl;
        delete s;
    }
}

int main() {
    int role;
    while (true) {
        cout << "\n=== FAST UNIVERSITY ACADEMIC SYSTEM ===" << endl;
        cout << "1. Student" << endl;
        cout << "2. Teacher" << endl;
        cout << "3. Admin" << endl;
        cout << "0. Exit" << endl;
        cout << "Select Role: ";
        cin >> role;

        if (role == 0) break;
        else if (role == 1) studentMenu();
        else if (role == 2) teacherMenu();
        else if (role == 3) adminMenu();
    }
    return 0;
}