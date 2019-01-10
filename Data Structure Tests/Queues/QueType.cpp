
/*

  QueType.cpp

  Author: Alex McEntyre

  Date: 1/10/17

  Purpose: This program is meant to implement a generic ADT circular queue while practicing
  a good software engineering design approach.

 */

#include<iostream>
#include<string>

using namespace std;

class FullQueue{
};//FullQueue  

class EmptyQueue{
};//EmptyQueue  

template <class ItemType>
class QueType{

public: 
    QueType();
    // Class constructor.
    // Because there is a default constructor, the precondition 
    // that the queue has been initialized is omitted.
    
    QueType(int max);
    // Parameterized class constructor.
    
    ~QueType();
    // Class destructor.
    
    void MakeEmpty();
    // Function: Initializes the queue to an empty state.
    // Post: Queue is empty.
    
    bool IsEmpty() const;
    // Function: Determines whether the queue is empty.
    // Post: Function value = (queue is empty)
    
    bool IsFull() const;
    // Function: Determines whether the queue is full.
    // Post: Function value = (queue is full)
    
    void Enqueue(ItemType newItem);
    // Function: Adds newItem to the rear of the queue.
    // Post: If (queue is full) FullQueue exception is thrown
    //       else newItem is at rear of queue.
    
    void Dequeue(ItemType& item);
    // Function: Removes front item from the queue and returns it in item.
    // Post: If (queue is empty) EmptyQueue exception is thrown
    //       and item is undefined
    //       else front element has been removed from queue and
    //       item is a copy of removed element.
	
    int length();
    // Function: returns the number of items in the queue

private:
    int front;
    int rear;
    ItemType* items;
    int maxQue;

};//QueType



template<class ItemType>
QueType<ItemType>::QueType(){
  maxQue = 501;
  items = new ItemType[maxQue];
  front = rear = maxQue - 1;
}//QueType


template<class ItemType>
QueType<ItemType>::QueType(int max){
  maxQue = max + 1;
  items = new ItemType[maxQue];
  front = rear = maxQue - 1;
}//QueType(int)


template<class ItemType>
QueType<ItemType>::~QueType(){
  delete[] items;
}//~QueType


template<class ItemType>
void QueType<ItemType>::MakeEmpty(){
  front = rear = maxQue - 1;
}//makeEmpty


template<class ItemType>
bool QueType<ItemType>::IsEmpty() const{
  return (front == rear);
}//IsEmpty


template<class ItemType>
bool QueType<ItemType>::IsFull() const{
  return ((rear + 1) % maxQue == front);
}//IsFull


template<class ItemType>
void QueType<ItemType>::Enqueue(ItemType newItem){
  if(!IsFull()){
    rear = (rear + 1) % maxQue;
    items[rear] = newItem;
  }//if
  else{
    throw FullQueue();
  }//else
}//Enqueue


template<class ItemType>
void QueType<ItemType>::Dequeue(ItemType& item){
  if(!IsEmpty()){
    front = (front + 1) % maxQue;
    item = items[front];
  }//if
  else{
    throw EmptyQueue();
  }//else
}//Dequeue


template<class ItemType>
int QueType<ItemType>::length(){
  if(IsFull()){
    return maxQue - 1;
  }//if
  else if(IsEmpty()){
    return 0;
  }//else if 
     return (maxQue + (rear - front)) % maxQue;
  }//else 
}//length
