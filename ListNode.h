/*
Grady Lynch and Frank Entriken
Student ID: 2297574 and 2298368
Emails: grlynch@chapman.edu and entriken@chapman.edu
CPSC 350-01
Assignment 4 - Registrar’s Office Simulation
*/

#include <iostream>

using namespace std;

template <class T>
class ListNode
{
  public:
    T data;
    ListNode *next; //pointer to next
    ListNode *prev; //pointer to previous

    ListNode()
    {

    }
    ListNode(T d)
    {
      data = d;
      next = NULL;
      prev = NULL;
    }
    ~ListNode()
    {

    }
};
