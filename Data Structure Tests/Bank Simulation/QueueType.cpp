
/*

QueueType.cpp

Author: Alex McEntyre

Date: 3/15/17

Purpose: The purpose of this program is to implement a simulator for customers
entering and leaving a bank using a good software engineering design approach.

*/

#include "QueueType.h"

using namespace std;

/*
Class constructor
-Because there is a default constructor, the preconditin that the queue has been initialized
is omitted
 */
template<class ItemType>
QueueType<ItemType>::QueueType(){
  maxQueue = 501;
  items = new ItemType[maxQueue];
  front = rear = maxQueue - 1;
}//QueueType

/*
Parameterized class constructor

Parameters:
   int max - maximum size of the queue
 */
template<class ItemType>
QueueType<ItemType>::QueueType(int max){
  maxQueue = max + 1;
  items = new ItemType[maxQueue];
  front = rear = maxQueue - 1;
}//QueueType(int)

/*
Class destructor
 */
template<class ItemType>
QueueType<ItemType>::~QueueType(){
  delete[] items;
}//~QueueType

/*
Function: initializes the queue to an empty state

Postcondition: the queue is empty
 */
template<class ItemType>
void QueueType<ItemType>::MakeEmpty(){
  front = rear = maxQueue - 1;
}//MakeEmpty

/*
Function: Determines whether the queue is empty

Postcondition: Function value = (queue is empty)
 */
template<class ItemType>
bool QueueType<ItemType>::IsEmpty() const{
  return (front == rear);
}//IsEmpty

/*
Function: Determines whether the queue is full

Postcondition: Function value = (queue is full)
 */
template<class ItemType>
bool QueueType<ItemType>::IsFull() const{
  return ((rear + 1) % maxQueue == front);
}//IsFull

/*
Function: Adds newItem to the rear of the queue

Postcondition: If (queue is full) FullQueue exception is thrown
-else newItem is at rear of queue

Parameters:
   ItemType newItem - Item to be enqueued
 */
template<class ItemType>
void QueueType<ItemType>::Enqueue(ItemType newItem){
  if(!IsFull()){
    rear = (rear + 1) % maxQueue;
    items[rear] = newItem;
  }//if
  else{
    throw FullQueue();
  }//else
}//Enqueue

/*
Function: Removes front item from the queue and returns it in item

Postcondition: If (queue is empty) EmptyQueue exception is thrown and item is
undefined else front element has been removed from queue and item is a copy of
removed element

Parameters:
   ItemType & item - copy of the element removed
 */
template<class ItemType>
void QueueType<ItemType>::Dequeue(ItemType & item){
  if(!IsEmpty()){
    front = (front + 1) % maxQueue;
    item = items[front];
  }//if
  else{
    throw EmptyQueue();
  }//else
}//Dequeue

/*
Function: Returns the number of items in the queue
 */
template<class ItemType>
int QueueType<ItemType>::length(){
  if(IsFull()){
    return maxQueue - 1;
  }//if
  else if(IsEmpty()){
    return 0;
  }//else if
  else{
    return (maxQueue + (rear - front)) % maxQueue;
  }//else
}//length

/*
Function: Returns the item at the front of the queue without removing it from the queue
 */
template<class ItemType>
ItemType QueueType<ItemType>::peek(){
  ItemType temp;
  temp = items[(front + 1) % maxQueue];
  return temp;
}//peek
