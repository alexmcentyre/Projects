
/*

QueueType.h

Author: Alex McEntyre

Date: 3/15/17

Purpose: The purpose of this program is to implement a simulator for customers
entering and leaving a bank using a good software engineering design approach.

*/

class FullQueue{};
class EmptyQueue{};

template <class ItemType>
class QueueType{

 public:

  QueueType();
  QueueType(int max);
  ~QueueType();
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  void Enqueue(ItemType newItem);
  void Dequeue(ItemType & item);
  int length();
  ItemType peek();

 private:

  int front;
  int rear;
  ItemType * items;
  int maxQueue;

};//QueueType
