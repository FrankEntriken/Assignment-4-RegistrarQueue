/*
Grady Lynch and Frank Entriken
Student ID: 2297574 and 2298368
Emails: grlynch@chapman.edu and entriken@chapman.edu
CPSC 350-01
Assignment 4 - Registrar’s Office Simulation
*/

#include <iostream>
#include <string>
#include "Student.h"

using namespace std;

Student::Student()
{
  timeArrived = 0;
  timeNeeded = 0;
  waitTime = 0;
  windowNumber = 5;
}

Student::Student(int arrive, int needed, int wait, int window)
{
  timeArrived = arrive;
  timeNeeded = needed;
  waitTime = wait;
  windowNumber = window;
}

Student::~Student()
{
  //do stuff here
}

int Student::getTimeArrived()
{
  return timeArrived;
}

int Student::getTimeNeeded()
{
  return timeNeeded;
}

void Student::toString()
{
  cout << "arrival: " << timeArrived << "  needed: " << timeNeeded << endl;
}
