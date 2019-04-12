/*
Grady Lynch and Frank Entriken
Student ID: 2297574 and 2298368
Emails: grlynch@chapman.edu and entriken@chapman.edu
CPSC 350-01
Assignment 4 - Registrar’s Office Simulation
*/

#include <iostream>
#include "Process.h"
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

Process::Process() //constructor
{
  myList = new DoublyLinkedList<Student*>();
  numberOfWindows = 0;
  numberOfStudents = 0;
}

Process::~Process() // deconstructor
{

}

void Process::readFile(string fileName)
{
  // this function takes in the name of the users text file and reads through it, storing its information.

  int lineNumber = 0;
	string line;
	ifstream myfile (fileName);
  int counter = 1;
  int studentsCounter;
  int time;

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      lineNumber ++;

			if(lineNumber == 1)
      {
        numberOfWindows = stoi(line);
      }
      else
      {
        if(counter == 1)
        {
          time = stoi(line);
          counter++;
        }
        else if(counter == 2)
        {
          studentsCounter = stoi(line);
          counter++;
        }
        else if(counter == 3)
        {
          if(studentsCounter > 0)
          {
            myList->insertBack(new Student(time, stoi(line), 0, -1));
            numberOfStudents++;
            studentsCounter--;
            if(studentsCounter == 0)
              counter = 1;
          }
        }
      }
		}
		myfile.close();
	}
}

void Process::runSim()
{
  //Runs the simulation of the registrars office using a while loop and clock ticks
  int clock = 0;
  Window windows[numberOfWindows];
  Student studentsAtWindows[numberOfWindows];
  int myArraySize = 0;
  int firstOpenWindow = 1;
  DoublyLinkedList<Student*> *finishedStudents = new DoublyLinkedList<Student*>();
  Queue<Student*> *studentsInLine = new Queue<Student*>();
  ListNode<Student*> *curr;

  while(finishedStudents->getSize() != numberOfStudents) //While the list of finished students does not equal the total number of students
  {
    //Iterate through all students from text file and add ones with the corresponding arrival time to the line/queue
    curr = myList->front;
    while(curr != NULL)
    {
      if(curr->data->timeArrived == clock)
      {
        studentsInLine->insert(curr->data);
      }
      curr = curr->next;
    }

    //Assign students to open windows
    while(myArraySize < numberOfWindows && !studentsInLine->isEmpty()) //While the windows arent full and the line is not empty
    {
      //Find the first open window
      for(int i = numberOfWindows - 1; i > -1; i--)
      {
        if(!windows[i].occupied)
        {
          firstOpenWindow = i;
        }
      }

      //Assign first student in line to the first open window
      Student *temp = studentsInLine->remove();
      studentsAtWindows[firstOpenWindow] = Student(temp->timeArrived, temp->timeNeeded, temp->waitTime, temp->windowNumber);
      studentsAtWindows[firstOpenWindow].windowNumber = firstOpenWindow;
      windows[firstOpenWindow].occupied = true;
      myArraySize++;
    }

    //Update idle time for students
    curr = myList->front;
    while(curr != NULL)
    {
      if(curr->data->windowNumber == -1 && curr->data->timeArrived <= clock)
      {
        curr->data->waitTime++;
      }
      curr = curr->next;
    }

    //Update idle time for windows
    for(int i = 0; i < numberOfWindows; i++)
    {
      if(!windows[i].occupied)
        windows[i].idleTime++;
    }

    //Update time students need at windows and allow students who are finished to leave
    Student *temp;
    for(int i = 0; i < numberOfWindows; i++)
    {
      if(studentsAtWindows[i].timeNeeded == 0 && windows[i].occupied)
      {
        temp = new Student(studentsAtWindows[i].timeArrived, studentsAtWindows[i].timeNeeded, studentsAtWindows[i].waitTime, studentsAtWindows[i].windowNumber);
        finishedStudents->insertBack(temp);
        windows[i].occupied = false;
        myArraySize--;
      }
      else if(windows[i].occupied && studentsAtWindows[i].timeNeeded != 0)
      {
        studentsAtWindows[i].timeNeeded--;
      }
    }

    clock++;
  }


  //Calculate output
  //main values to be printed to the console
  double meanStudentWait;
  int medianStudentWait;
  int longestStudentWait = 0;
  int numberOfStudentsWaitingOver10min = 0;
  double meanWindowIdleTime;
  int longestWindowIdleTime = 0;
  int numberOfWindowsIdleOver5min = 0;

  //Auxillary variables
  double totalStudentWait = 0;
  double totalWindowIdleTime = 0;
  int waitTimes[numberOfStudents];

  //Total student wait time, longest student wait time, and number of students waiting over 10 min calculations
  curr = finishedStudents->front;
  while(curr != NULL)
  {
    totalStudentWait += curr->data->waitTime;

    if(curr->data->waitTime > longestStudentWait)
      longestStudentWait = curr->data->waitTime;

    if(curr->data->waitTime > 10)
      numberOfStudentsWaitingOver10min++;

    curr = curr->next;
  }

  //Total window idle time, longest window idle time, and number of windows idle over 5 min calculations
  for(int i = 0; i < numberOfWindows; i++)
  {
    totalWindowIdleTime += windows[i].idleTime;

    if(windows[i].idleTime > longestWindowIdleTime)
      longestWindowIdleTime = windows[i].idleTime;

    if(windows[i].idleTime > 10)
      numberOfWindowsIdleOver5min++;
  }

  //Mean student wait calculation
  meanStudentWait = totalStudentWait / numberOfStudents;

  //Mean window idle time calculation
  meanWindowIdleTime = totalWindowIdleTime / numberOfWindows;

  //Median student wait time calculation
  curr = finishedStudents->front;
  int counter = 0;
  while(curr != NULL)
  {
    waitTimes[counter] = curr->data->waitTime;

    curr = curr->next;
    counter++;
  }

  sort(waitTimes, waitTimes + numberOfStudents); //cplusplus.com

  //if odd
  if(numberOfStudents % 2 != 0)
  {
    medianStudentWait = waitTimes[(numberOfStudents - 1) / 2];
  }

  //if even
  else
  {
    medianStudentWait = (waitTimes[numberOfStudents / 2] + waitTimes[numberOfStudents / 2 - 1]) / 2;
  }

  //Output metrics to terminal
  cout << endl;
  cout << "         --------------- Simulation Metrics ---------------" << endl;
  cout << endl;
  cout << endl;
  cout << "         Mean student wait time:                       " << meanStudentWait << endl;
  cout << endl;
  cout << "         Median student wait time:                     " << medianStudentWait << endl;
  cout << endl;
  cout << "         Longest student wait time:                    " << longestStudentWait << endl;
  cout << endl;
  cout << "         Number of students who waited over 10 min:    " << numberOfStudentsWaitingOver10min << endl;
  cout << endl;
  cout << "         Mean window idle time:                        " << meanWindowIdleTime << endl;
  cout << endl;
  cout << "         Longest window idle time:                     " << longestWindowIdleTime << endl;
  cout << endl;
  cout << "         Number of windows idle more than 5 min:       " << numberOfWindowsIdleOver5min << endl;
  cout << endl;
  cout << endl;
  cout << "         --------------------------------------------------" << endl;
  cout << endl;
}
