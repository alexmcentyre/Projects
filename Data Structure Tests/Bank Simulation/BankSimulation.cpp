
/*

BankSimulation.cpp

Author: Alex McEntyre

Date: 3/15/17

Purpose: The purpose of this program is to implement a simulator for customers
entering and leaving a bank using a good software engineering design approach.

*/

#include "Customer.cpp"
#include "QueueType.cpp"
#include "PriorityQueue.cpp"
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main(){

  QueueType<Customer> waitQueue;
  int numTellers;
  string command;
  ifstream file;
  file.open("input.txt");

  while(file >> command){
   
    if(command == "numTellers"){
      file >> numTellers;
    }//if
    else{
      string trash;
      int a, s;
      file >> trash;
      file >> a;
      file >> trash;
      file >> s;
      Customer temp(command, a, s);
      //cout << temp;
      waitQueue.Enqueue(temp);
    }//else
  }//while
  file.close();

 
  PriorityQueue<Customer> bankQueue;
  int wait = 0;
  while((bankQueue.size() < numTellers) && (!waitQueue.IsEmpty())){
    Customer temp;
    waitQueue.Dequeue(temp);
    bankQueue.enqueue(temp, (temp.getArrival() + temp.getService()));
  }//while

  while((!bankQueue.isEmpty()) || (!waitQueue.IsEmpty())){
    if((bankQueue.size() < numTellers) && (!waitQueue.IsEmpty())){
      Customer temp;
      waitQueue.Dequeue(temp);
      temp.setWait(wait);
      bankQueue.enqueue(temp, (temp.getArrival() + temp.getService() + temp.getWait()));
    }//if
    else{
      Customer temp;
      bankQueue.dequeue(temp);
      if(!waitQueue.IsEmpty()){
	Customer trash;
	trash = waitQueue.peek();
	//trash.setWait((temp.getArrival() + temp.getService() + temp.getWait()) - trash.getArrival());
	//waitQueue.peek() = trash;
	//cout << "changed wait to: " << trash.getWait() << endl;     
	wait = temp.getArrival() + temp.getService() + temp.getWait() - trash.getArrival();
      }//if
      cout << temp;
    }//else
  }//while

  return EXIT_SUCCESS;
}//main
