
/*

PriorityQueue.cpp

Author: Alex McEntyre

Date: 3/15/17

Purpose: This program is meant to implement a generic ADT priority queue while practicing
a good software engineering design approach.

 */
#include "PriorityQueue.h"

using namespace std;

/*
Default constructor for a priority queue
 */
template<class ItemType>
PriorityQueue<ItemType>::PriorityQueue(){
  front = NULL;
  rear = NULL;
}//PriorityQueue

/*
Destructor for priority queue
 */
template<class ItemType>
PriorityQueue<ItemType>::~PriorityQueue(){
  makeEmpty();
}//~PriorityQueue

/*
Function: Adds item to the queue in the correct position based on its priority

Postcondition: If (queue is full) FullPriorityQueue exception is thrown
-else item is placed in the queue at the correct position

Parameters:
   ItemType item - item to be enqueued
   int priority - priority of the item
 */
template<class ItemType>
void PriorityQueue<ItemType>::enqueue(ItemType item, int priority){
  if(isFull()){
    throw FullPriorityQueue();
  }//if
  else{
    QueueNode<ItemType> * newNode;
    newNode = new QueueNode<ItemType>;
    newNode -> info = item;
    newNode -> priority = priority;

    if(isEmpty()){
      newNode -> next = NULL;
      front = rear = newNode;
    }//if
    else{
      QueueNode<ItemType> * temp;
      QueueNode<ItemType> * holder;
      temp = front;
      holder = front;
      bool found = false;

      if(priority < temp -> priority){
	newNode -> next = temp;
	front = newNode;
      }//if
      else{
	while(temp != NULL){
	  if(priority < temp -> priority){
	    newNode -> next = temp;
	    holder -> next = newNode;
	    found = true;
	    break;
	  }//if
	  holder = temp;
	  temp = temp -> next;
	}//while
	if(!found){
	  newNode -> next = NULL;
	  rear -> next = newNode;
	  rear = newNode;
	}//if
      }//else
    }//else
  }//else
}//enqueue

/*
Function: Removes front item from the queue and returns it in item

Postcondition: If (queue is empty) EmptyPriorityQueue exception is thrown and item is undefined
-else front element has been removed from queue and item is a copy of removed element

Parameters:
   ItemType & item - will be a copy of the removed element
 */
template<class ItemType>
void PriorityQueue<ItemType>::dequeue(ItemType & item){
  if(isEmpty()){
    throw EmptyPriorityQueue();
  }//if
  else{
    QueueNode<ItemType> * temp;
    temp = front;
    ItemType rItem;
    rItem = front -> info;
    front = front -> next;
    if(front == NULL){
      rear = NULL;
    }//if
    delete temp;
    item = rItem;
  }//else
}//dequeue

/*
Function: returns the value of the most urgent item in the queue without removing it
from the queue

Postcondition: If (queue is empty) EmptyPriorityQueue exception is thrown 
-else the front item is returned 
*/
template<class ItemType>
ItemType PriorityQueue<ItemType>::peek(){
  if(isEmpty()){
    throw EmptyPriorityQueue();
  }//if
  else{
    ItemType item;
    item = front -> info;
    return item;
  }//else
}//peek

/*
Function: Returns the priority of the most urgent item in the queue without removing it
from the queue

Postcondition: If (queue is empty) EmptyPriorityQueue exception is thrown
-else the priority of the front item is returned
 */
template<class ItemType>
int PriorityQueue<ItemType>::peekPriority(){
  if(isEmpty()){
    throw EmptyPriorityQueue();
  }//if
  else{
    int temp;
    temp = front -> priority;
    return temp;
  }//else
}//peekPriority

/*
Function: removes all elements from the queue

Postcondition: queue is empty
 */
template<class ItemType>
void PriorityQueue<ItemType>::makeEmpty(){
  QueueNode<ItemType> * temp;
  while(front != NULL){
    temp = front;
    front = front -> next;
    delete temp;
  }//while
  rear = NULL;
}//makeEmpty

/*
Function: returns the number of elements currently in the queue
 */
template<class ItemType>
int PriorityQueue<ItemType>::size(){
  QueueNode<ItemType> * temp;
  temp = front;
  int count = 0;
  while(temp != NULL){
    ++count;
    temp = temp -> next;
  }//while
  return count;
}//size

/*
Function: prints queue items ordered from front to rear
 */
template<class ItemType>
void PriorityQueue<ItemType>::printQueue(){
  QueueNode<ItemType> * temp;
  temp = front;
  while(temp != NULL){
    cout << temp -> info << " ";
    temp = temp -> next;
  }//while
}//printQueue

/*
Function: Determines whether the queue is empty

Postcondition: Function value = (queue is empty)
 */
template<class ItemType>
bool PriorityQueue<ItemType>::isEmpty() const{
  return (front == NULL);
}//isEmpty

/*
Function: Determines whether the queue is full

Postcondition: Function value = (queue is full)
 */
template<class ItemType>
bool PriorityQueue<ItemType>::isFull() const{
  QueueNode<ItemType> * test;
  try{
    test = new QueueNode<ItemType>;
    delete test;
    return false;
  }//try
  catch(bad_alloc exception){
    return true;
  }//catch
}//isFull
