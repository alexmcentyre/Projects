
/*

Customer.h

Author: Alex McEntyre

Date: 3/15/17

Purpose: The purpose of this program is to implement a simulator for customers
entering and leaving a bank using a good software engineering design approach.

*/

#include <string>
#include <iostream>

using namespace std;

class Customer{

 private:
  
  string name;
  int arrival;
  int service;
  int wait;

 public:

  Customer();
  Customer(string n, int a, int s);
  ~Customer();
  string getName();
  int getArrival();
  int getService();
  int getWait();
  void setName(string n);
  void setArrival(int a);
  void setService(int s);
  void setWait(int w);

};//Customer

ostream & operator<<(ostream & os, Customer & c);
