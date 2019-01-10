
/*

Stud.cpp

Author: Alex McEntyre

Date: 1/25/17

Purpose: This program is meant to implement a generic ADT UnsortedList while practicing a good
software engineering design approach.

 */


#include "Stud.h"

#include <cstdlib>
#include <iostream>

using namespace std;

Stud::Stud(){
  id = 0;
  name = "";
  major = "";
}//Stud

Stud::Stud(int i, string n, string m){
  id = i;
  name = n;
  major = m;
}//Stud

int Stud::getID() const{
  return id;
}//getID

string Stud::getName() const{
  return name;
}//getName

string Stud::getMajor() const{
  return major;
}//getMajor

void Stud::setID(int i){
  id = i;
}//setID

void Stud::setName(string s){
  name = s;
}//setName

void Stud::setMajor(string s){
  major = s;
}//setMajor

bool Stud::operator==(const Stud & s){
  if(id == s.id){
    return true;
  }//if
  else{
    return false;
  }//else
}//operator==

bool Stud::operator>(Stud s){
  if(id > s.id){
    return true;
  }//if
  else{
    return false;
  }//else
}//operator>

ostream & operator<<(ostream & os, const Stud & s){
  os << "ID: " << s.getID() << "\tName: " << s.getName() << "\t\tMajor: " << s.getMajor();
  return os;
}//operator<<
