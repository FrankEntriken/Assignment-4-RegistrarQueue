/*
Grady Lynch and Frank Entriken
Student ID: 2271425 and Student ID: 2274813
Student Emails: grlynch@chapman.edu entriken@chapman.edu
CPSC 350-02
Assignment 4 - Registrar’s Office Simulation
*/

#include <iostream>
#include "Process.h"

using namespace std;

int main()
{
  cout << endl;
  cout << "Please enter the name of the file that you would like to use for the simulation." << endl;
  string fileName;
  getline(cin, fileName);
  cout << endl;

  Process p;

  p.readFile(fileName);

  p.runSim();

}
