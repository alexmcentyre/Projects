
/*

Customer.cpp

Author: Alex McEntyre

Date: 3/15/17

Purpose: The purpose of this program is to implement a simulator for customers
entering and leaving a bank using a good software engineering design approach.

*/

#include "Customer.h"
#include <string>
#include <iostream>

/*
Default constructor for Customer
 */
Customer::Customer(){
  name = "";
  arrival = 0;
  service = 0;
  wait = 0;
}//Customer

/*
Constructor for Customer which allows the user to specify values

Parameters:
   string n - Name of customer
   int a - Time of arrival
   int s - Service time
 */
Customer::Customer(string n, int a, int s){
  name = n;
  arrival = a;
  service = s;
  wait = 0;
}//Customer

/*
Destructor for Customer
 */
Customer::~Customer(){
  name = "";
  arrival = 0;
  service = 0;
  wait = 0;
}//~Customer

/*
Returns the name of the customer
 */
string Customer::getName(){
  return name;
}//getName

/*
Returns the time of arrival for the customer
 */
int Customer::getArrival(){
  return arrival;
}//getArrival

/*
Returns the service time of the customer
 */
int Customer::getService(){
  return service;
}//getService

/*
Returns the wait time of the customer
 */
int Customer:: getWait(){
  return wait;
}//getWait

/*
Sets the name of the customer to a specific string

Postcondition: name equals string parameter

Parameters:
   string n - new name of customer
 */
void Customer::setName(string n){
  name = n;
}//setName

/*
Sets the arrival time of the customer to an int

Postcondition: arrival equals int parameter

Parameters:
   int a - new arrival time
 */
void Customer::setArrival(int a){
  arrival = a;
}//setArrival

/*
Sets the service time of the customer to an int

Postcondition: service equals int parameter

Parameters:
   int s - new service time
 */
void Customer::setService(int s){
  service = s;
}//setService

/*
Sets the wait time of the customer to an int

Postcondition: wait equals int parameter

Parameters:
   int w - new wait time
 */
void Customer::setWait(int w){
  wait = w;
}//setWait

/*
This function overloads the << operator to allow Customer objects to be printed
to standard output using cout

Parameters:
   ostream & os - output stream (cout)
   Customer & c - customer to be printed
 */
ostream & operator<<(ostream & os, Customer & c){
  os << c.getName() << "  " << c.getWait() << " wait  service " << (c.getService() + c.getArrival() + c.getWait()) << endl;
  return os;
}//operator<<
