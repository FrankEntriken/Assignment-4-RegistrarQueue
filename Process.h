/*
Grady Lynch and Frank Entriken
Student ID: 2297574 and 2298368
Emails: grlynch@chapman.edu and entriken@chapman.edu
CPSC 350-01
Assignment 4 - Registrar’s Office Simulation
*/

#include <iostream>
#include <string>
#include <fstream>
#include "Queue.h"
#include "Student.h"
#include "Window.h"

using namespace std;

class Process
{
  public:
    DoublyLinkedList<Student*> *myList;
    int numberOfWindows;
    int numberOfStudents;


    Process();
    ~Process();
    void readFile(string fileName);
    void runSim();
};
