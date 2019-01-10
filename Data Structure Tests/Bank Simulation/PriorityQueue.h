
/*

PriorityQueue.h

Author: Alex McEntyre

Date: 3/15/17

Purpose: This program is meant to implement a generic ADT priority queue while
practicing a good software engineering design approach

 */


#include <iostream>
#include <string>

class EmptyPriorityQueue{};
class FullPriorityQueue{};


template <class ItemType>
struct QueueNode{
  ItemType info;
  int priority;
  QueueNode<ItemType> * next;

};//QueueNode

template <class ItemType>
class PriorityQueue{

 public:
  
  PriorityQueue();
  ~PriorityQueue();
  void enqueue(ItemType item, int priority = 1);
  void dequeue(ItemType & item);
  ItemType peek();
  int peekPriority();
  void makeEmpty();
  int size();
  void printQueue();
  bool isEmpty() const;
  bool isFull() const;

 private:
  QueueNode<ItemType> * front;
  QueueNode<ItemType> * rear;

};//PriorityQueue
//functions
