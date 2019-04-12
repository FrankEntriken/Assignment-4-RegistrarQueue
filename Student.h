/*
Grady Lynch and Frank Entriken
Student ID: 2297574 and 2298368
Emails: grlynch@chapman.edu and entriken@chapman.edu
CPSC 350-01
Assignment 4 - Registrar’s Office Simulation
*/

#include <iostream>
#include <string>

using namespace std;

class Student
{
  public:
    Student();
    Student(int arrive, int needed, int wait, int window);
    ~Student();

    int timeArrived;
    int timeNeeded;
    int waitTime;
    int windowNumber;

    int getTimeArrived();
    int getTimeNeeded();
    void toString();
};
