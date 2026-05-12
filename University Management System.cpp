#include <iostream>
#include <fstream>
#include <sstream>
#include "Database.h"
#include "Scheduler.h"
using namespace std;

DataBase db;

void studentMenu()
{
    int choice;
    cout << "=========================" << endl;
    cout << "      STUDENT MENU       " << endl;
    cout << "=========================" << endl;
    cout << "1. View Profile" << endl;
    cout << "2. View Transcript" << endl;
    cout << "3. Give Teacher Feedback" << endl;
    cout << "0. Back" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    cout << endl;

    if(choice == 1)
    {
        string id;
        cout << "Enter Student ID: ";
        cin >> id;
        cout << endl;
        db.loadStudents();
        bool found = false;
        for(int i = 0; i < db.getStudentCount(); i++)
        {
            if(db.getStudent(i)->getID() == id)
            {
                db.getStudent(i)->displayProfile();
                found = true;
                break;
            }
        }
        if(!found) cout << "Error: Student with ID '" << id << "' not found." << endl;
    }

    else if(choice == 2)
    {
        string id;
        cout << "Enter Student ID: ";
        cin >> id;
        cout << endl;
        db.loadStudents();
        bool found = false;
        for(int i = 0; i < db.getStudentCount(); i++)
        {
            if(db.getStudent(i)->getID() == id)
            {
                db.getStudent(i)->viewTranscript();
                db.loadStudentCourses(id);
                found = true;
                break;
            }
        }
        if(!found) cout << "Error: Student with ID '" << id << "' not found." << endl;
    }

    else if(choice == 3)
    {
        string teacherID;
        int rating;
        string comment;
        cout << "Enter Teacher ID: ";
        cin >> teacherID;

        if(!db.teacherExists(teacherID))
        {
            cout << "Error: Teacher with ID '" << teacherID << "' not found." << endl;
            return;
        }

        cout << "Enter Rating (1-5): ";
        cin >> rating;
        if(rating < 1 || rating > 5)
        {
            cout << "Error: Rating must be between 1 and 5." << endl;
            return;
        }

        cout << "Enter Comment: ";
        cin.ignore();
        getline(cin, comment);
        cout << endl;

        db.loadTeachers();
        for(int i = 0; i < db.getTeacherCount(); i++)
        {
            if(db.getTeachers(i)->getID() == teacherID)
            {
                db.getTeachers(i)->AddRating(rating);
                db.getTeachers(i)->AddComment(comment);
                float newAvg = db.getTeachers(i)->AverageFeedbackCalc();
                db.updateTeacherFeedback(teacherID, newAvg);
                cout << "Feedback added successfully." << endl;
                cout << "New Average Rating: " << newAvg << " / 5" << endl;
                break;
            }
        }
    }

    else if(choice == 0)
        cout << "Returning to main menu." << endl;

    else
        cout << "Invalid choice. Please try again." << endl;
}

void teacherMenu()
{
    int choice;
    cout << "=========================" << endl;
    cout << "      TEACHER MENU       " << endl;
    cout << "=========================" << endl;
    cout << "1. View Profile" << endl;
    cout << "2. Enter Student Marks" << endl;
    cout << "3. Update Student Grade" << endl;
    cout << "0. Back" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    cout << endl;

    if(choice == 1)
    {
        string id;
        cout << "Enter Teacher ID: ";
        cin >> id;
        cout << endl;
        if(!db.teacherExists(id))
        {
            cout << "Error: Teacher with ID '" << id << "' not found." << endl;
            return;
        }
        db.loadTeachers();
        for(int i = 0; i < db.getTeacherCount(); i++)
        {
            if(db.getTeachers(i)->getID() == id)
            {
                db.getTeachers(i)->displayProfile();
                db.loadTeacherCourses(id);
                break;
            }
        }
    }

    else if(choice == 2)
    {
        string courseCode, studentID;
        float score, weightage, maxScore;
        int type;

        cout << "Enter Course Code: ";
        cin >> courseCode;
        if(!db.courseExists(courseCode))
        {
            cout << "Error: Course '" << courseCode << "' not found." << endl;
            return;
        }

        cout << "Enter Student ID: ";
        cin >> studentID;
        if(!db.studentExists(studentID))
        {
            cout << "Error: Student '" << studentID << "' not found." << endl;
            return;
        }

        if(!db.isStudentRegistered(studentID, courseCode))
        {
            cout << "Error: Student '" << studentID << "' is not registered in course '" << courseCode << "'." << endl;
            return;
        }

        cout << "Enter Weightage (%): ";
        cin >> weightage;
        cout << "Enter Score: ";
        cin >> score;
        cout << "Enter Max Score: ";
        cin >> maxScore;

        if(score > maxScore)
        {
            cout << "Error: Score cannot be greater than max score." << endl;
            return;
        }

        cout << "Assessment Type" << endl;
        cout << "1. Exam" << endl;
        cout << "2. Quiz" << endl;
        cout << "3. Assignment" << endl;
        cout << "Enter choice: ";
        cin >> type;
        cout << endl;

        db.loadCourses();
        for(int i = 0; i < db.getCoursesCount(); i++)
        {
            if(db.getCourses(i)->getCourseCode() == courseCode)
            {
                Assessment* a;
                if(type == 1)
                    a = new Exam(weightage, maxScore, score);
                else if(type == 2)
                    a = new Quiz(weightage, maxScore, score);
                else
                    a = new Assignment(score, weightage, maxScore);

                db.getCourses(i)->addAssessment(a);
                float finalGrade = db.getCourses(i)->calculateFinalGrade();

                // update grade in StudentCourses.txt
                db.updateStudentGrade(studentID, courseCode, finalGrade);

                cout << "Marks entered successfully." << endl;
                cout << "Final Grade for " << studentID << " in " << courseCode << ": " << finalGrade << endl;
                break;
            }
        }
    }

    else if(choice == 3)
    {
        string studentID, courseCode;
        float grade;
        cout << "Enter Student ID: ";
        cin >> studentID;
        if(!db.studentExists(studentID))
        {
            cout << "Error: Student '" << studentID << "' not found." << endl;
            return;
        }
        cout << "Enter Course Code: ";
        cin >> courseCode;
        if(!db.isStudentRegistered(studentID, courseCode))
        {
            cout << "Error: Student is not registered in this course." << endl;
            return;
        }
        cout << "Enter New Grade: ";
        cin >> grade;
        db.updateStudentGrade(studentID, courseCode, grade);
        cout << "Grade updated successfully." << endl;
    }

    else if(choice == 0)
        cout << "Returning to main menu." << endl;

    else
        cout << "Invalid choice. Please try again." << endl;
}

void adminMenu()
{
    int password;
    cout << "Enter Admin Password: ";
    cin >> password;
    cout << endl;

    if(password != 1111)
    {
        cout << "Error: Wrong password. Access denied." << endl;
        return;
    }

    int choice;
    while(true)
    {
        cout << "=========================" << endl;
        cout << "       ADMIN MENU        " << endl;
        cout << "=========================" << endl;
        cout << "1.  Add Student" << endl;
        cout << "2.  Add Teacher" << endl;
        cout << "3.  Add Course" << endl;
        cout << "4.  Add Venue" << endl;
        cout << "5.  Add Section" << endl;
        cout << "6.  Set Weightages" << endl;
        cout << "7.  View Weightages" << endl;
        cout << "8.  Run Scheduler" << endl;
        cout << "9.  Register Student for Course" << endl;
        cout << "10. View All Students" << endl;
        cout << "11. View All Courses" << endl;
        cout << "12. View All Sections" << endl;
        cout << "13. View All Venues" << endl;
        cout << "0.  Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;

        if(choice == 0)
        {
            cout << "Returning to main menu." << endl;
            break;
        }

        else if(choice == 1)
        {
            string id, name, email;
            int type;
            cout << "Enter Student ID: ";
            cin >> id;

            if(db.studentExists(id))
            {
                cout << "Error: Student with ID '" << id << "' already exists." << endl;
                cout << endl;
                continue;
            }

            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Email: ";
            cin >> email;
            cout << "Student Type" << endl;
            cout << "1. Regular" << endl;
            cout << "2. Scholarship" << endl;
            cout << "3. Exchange" << endl;
            cout << "Enter choice: ";
            cin >> type;
            cout << endl;

            if(type < 1 || type > 3) { cout << "Invalid type." << endl; continue; }

            Student* s;
            if(type == 1)
                s = new RegularStudent('-', 0.0, id, name, email);
            else if(type == 2)
                s = new ScholarshipStudent(true, 0.0, id, name, email);
            else
                s = new ExchangeStudent(true, 0.0, id, name, email);

            db.saveStudent(s);
            cout << "Student '" << name << "' added successfully." << endl;
            delete s;
        }

        else if(choice == 2)
        {
            string id, name, email;
            cout << "Enter Teacher ID: ";
            cin >> id;

            if(db.teacherExists(id))
            {
                cout << "Error: Teacher with ID '" << id << "' already exists." << endl;
                cout << endl;
                continue;
            }

            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Email: ";
            cin >> email;
            cout << endl;

            Teachers* t = new Teachers(id, name, email);
            db.saveTeacher(t);
            cout << "Teacher '" << name << "' added successfully." << endl;
            delete t;
        }

        else if(choice == 3)
        {
            string code, name, teacherID;
            int type;
            cout << "Enter Course Code: ";
            cin >> code;

            if(db.courseExists(code))
            {
                cout << "Error: Course '" << code << "' already exists." << endl;
                cout << endl;
                continue;
            }

            cout << "Enter Course Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Teacher ID: ";
            cin >> teacherID;

            if(!db.teacherExists(teacherID))
            {
                cout << "Error: Teacher '" << teacherID << "' not found. Add the teacher first." << endl;
                cout << endl;
                continue;
            }

            cout << "Course Type" << endl;
            cout << "1. Core" << endl;
            cout << "2. Elective" << endl;
            cout << "3. Lab" << endl;
            cout << "Enter choice: ";
            cin >> type;
            cout << endl;

            if(type < 1 || type > 3) { cout << "Invalid type." << endl; continue; }

            Courses* c;
            if(type == 1)
                c = new CoreCourse(code, name);
            else if(type == 2)
                c = new ElectiveCourse(0.0, 0.0, "00:00", "----", code, name);
            else
                c = new LabCourse(0.0, "00:00", "----", code, name);

            c->setTeacherID(teacherID);
            db.saveCourses(c);
            db.saveTeacherCourse(teacherID, code);
            cout << "Course '" << name << "' added successfully." << endl;
            delete c;
        }

        else if(choice == 4)
        {
            string roomID;
            int capacity, hasComp;
            cout << "Enter Room ID: ";
            cin >> roomID;
            cout << "Enter Capacity: ";
            cin >> capacity;
            if(capacity <= 0) { cout << "Error: Capacity must be greater than 0." << endl; continue; }
            cout << "Has Computers (1 = Yes, 0 = No): ";
            cin >> hasComp;
            cout << endl;

            Venues* v = new Venues(roomID, capacity, hasComp == 1);
            db.saveVenue(v);
            cout << "Venue '" << roomID << "' added successfully." << endl;
            delete v;
        }

        else if(choice == 5)
        {
            string sID, cID, tID, vID, slot;
            cout << "Enter Section ID: ";
            cin >> sID;
            cout << "Enter Course ID: ";
            cin >> cID;

            if(!db.courseExists(cID))
            {
                cout << "Error: Course '" << cID << "' not found." << endl;
                cout << endl;
                continue;
            }

            cout << "Enter Teacher ID: ";
            cin >> tID;

            if(!db.teacherExists(tID))
            {
                cout << "Error: Teacher '" << tID << "' not found." << endl;
                cout << endl;
                continue;
            }

            cout << "Enter Venue ID: ";
            cin >> vID;
            cout << "Enter Time Slot (e.g. 08:00): ";
            cin.ignore();
            getline(cin, slot);
            cout << endl;

            Section* s = new Section(sID, cID, tID, vID, slot);
            db.saveSection(s);
            cout << "Section '" << sID << "' added successfully." << endl;
            delete s;
        }

        else if(choice == 6)
        {
            string type;
            int exam, quiz, assignment;
            cout << "Course Type (Core / Elective / Lab): ";
            cin >> type;
            if(type != "Core" && type != "Elective" && type != "Lab")
            {
                cout << "Error: Invalid course type. Use Core, Elective, or Lab." << endl;
                continue;
            }
            cout << "Exam %: ";
            cin >> exam;
            cout << "Quiz %: ";
            cin >> quiz;
            cout << "Assignment %: ";
            cin >> assignment;
            if(exam + quiz + assignment != 100)
            {
                cout << "Warning: Weightages do not add up to 100%." << endl;
            }
            cout << endl;
            db.saveWeightages(type, exam, quiz, assignment);
            cout << "Weightages saved successfully." << endl;
        }

        else if(choice == 7)
        {
            db.loadWeightages();
        }

        else if(choice == 8)
        {
            db.loadSection();
            db.loadVenues();
            if(db.getSectionCount() == 0)
            {
                cout << "Error: No sections found. Add sections first." << endl;
                cout << endl;
                continue;
            }
            if(db.getVenueCount() == 0)
            {
                cout << "Error: No venues found. Add venues first." << endl;
                cout << endl;
                continue;
            }
            Scheduler scheduler(db.getSections(), db.getSectionCount(), db.getVenuesArr(), db.getVenueCount());
            scheduler.assignVenues();
            cout << "Scheduler completed. Check ExamSchedule.txt." << endl;
        }

        else if(choice == 9)
        {
            string studentID, courseCode;
            cout << "Enter Student ID: ";
            cin >> studentID;

            if(!db.studentExists(studentID))
            {
                cout << "Error: Student '" << studentID << "' not found." << endl;
                cout << endl;
                continue;
            }

            cout << "Enter Course Code: ";
            cin >> courseCode;
            cout << endl;

            if(!db.courseExists(courseCode))
            {
                cout << "Error: Course '" << courseCode << "' not found." << endl;
                cout << endl;
                continue;
            }

            if(db.isStudentRegistered(studentID, courseCode))
            {
                cout << "Error: Student '" << studentID << "' is already registered in course '" << courseCode << "'." << endl;
            }
            else
            {
                db.saveStudentCourse(studentID, courseCode, 0.0);
                cout << "Student '" << studentID << "' registered in course '" << courseCode << "' successfully." << endl;
            }
        }

        else if(choice == 10)
        {
            db.loadStudents();
            if(db.getStudentCount() == 0)
                cout << "No students found." << endl;
            else
            {
                cout << "=========================" << endl;
                cout << "      ALL STUDENTS       " << endl;
                cout << "=========================" << endl;
                for(int i = 0; i < db.getStudentCount(); i++)
                {
                    db.getStudent(i)->displayProfile();
                    cout << endl;
                }
                cout << "Total: " << db.getStudentCount() << " student(s)." << endl;
            }
        }

        else if(choice == 11)
        {
            db.loadCourses();
            if(db.getCoursesCount() == 0)
                cout << "No courses found." << endl;
            else
            {
                cout << "=========================" << endl;
                cout << "      ALL COURSES        " << endl;
                cout << "=========================" << endl;
                for(int i = 0; i < db.getCoursesCount(); i++)
                {
                    cout << "Code    : " << db.getCourses(i)->getCourseCode() << endl;
                    cout << "Name    : " << db.getCourses(i)->getCourseName() << endl;
                    cout << "Type    : " << db.getCourses(i)->getCourseType() << endl;
                    cout << "Teacher : " << db.getCourses(i)->getTeacherID() << endl;
                    cout << endl;
                }
                cout << "Total: " << db.getCoursesCount() << " course(s)." << endl;
            }
        }

        else if(choice == 12)
        {
            db.loadSection();
            if(db.getSectionCount() == 0)
                cout << "No sections found." << endl;
            else
            {
                cout << "=========================" << endl;
                cout << "      ALL SECTIONS       " << endl;
                cout << "=========================" << endl;
                for(int i = 0; i < db.getSectionCount(); i++)
                    db.getSection(i)->DisplaySection();
                cout << "Total: " << db.getSectionCount() << " section(s)." << endl;
            }
        }

        else if(choice == 13)
        {
            db.loadVenues();
            if(db.getVenueCount() == 0)
                cout << "No venues found." << endl;
            else
            {
                cout << "=========================" << endl;
                cout << "       ALL VENUES        " << endl;
                cout << "=========================" << endl;
                for(int i = 0; i < db.getVenueCount(); i++)
                {
                    cout << "Room ID   : " << db.getVenues(i)->getRoomID() << endl;
                    cout << "Capacity  : " << db.getVenues(i)->getCapacity() << endl;
                    cout << "Computers : " << (db.getVenues(i)->getHasComp() ? "Yes" : "No") << endl;
                    cout << endl;
                }
                cout << "Total: " << db.getVenueCount() << " venue(s)." << endl;
            }
        }

        else
            cout << "Invalid choice. Please try again." << endl;

        cout << endl;
    }
}

int main()
{
    int role;
    while(true)
    {
        cout << "========================================" << endl;
        cout << "   FAST UNIVERSITY ACADEMIC SYSTEM      " << endl;
        cout << "========================================" << endl;
        cout << "1. Student" << endl;
        cout << "2. Teacher" << endl;
        cout << "3. Admin" << endl;
        cout << "0. Exit" << endl;
        cout << "Select Role: ";
        cin >> role;
        cout << endl;

        if(role == 0)
        {
            cout << "Goodbye!" << endl;
            break;
        }
        else if(role == 1)
            studentMenu();
        else if(role == 2)
            teacherMenu();
        else if(role == 3)
            adminMenu();
        else
            cout << "Invalid choice. Please select 0-3." << endl;

        cout << endl;
    }
    return 0;
}
