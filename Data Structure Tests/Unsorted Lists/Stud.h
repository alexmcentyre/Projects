
/*

Stud.h

Author: Alex McEntyre

Date: 1/25/17

Purpose: This program is meant to implement a generic ADT UnsortedList while practicing a good
software engineering design approach.

 */

#ifndef STUD_H
#define STUD_H

#include <cstdlib>
#include <iostream>

using namespace std;

class Stud{
 private:
  int id;
  string name, major;

 public:
  Stud();
  Stud(int i, string n, string m);
  int getID() const;
  string getName() const;
  string getMajor() const;
  void setID(int i);
  void setName(string s);
  void setMajor(string s);
  bool operator==(const Stud & s1);
  bool operator>(Stud s);
};//Stud

ostream & operator<<(ostream & os, const Stud & s);
#endif
