
/*

  UnsortedList.cpp

  Author: Alex McEntyre

  Date: 1/25/17

  Purpose: This program is meant to implement a generic ADT UnsortedList while practicing a good
  software engineering design approach.

*/

//#include "UnsortedList.h"
#include <cstdlib>
#include <iostream>
#include <cstddef>
#include <stdexcept>

using namespace std;

template<class ItemType>
class UnsortedList{

private:
  ItemType * info;
  int MAX_ITEMS;
  int current_position;
  int length;
  int findItem(ItemType item);

public:
  UnsortedList();
  UnsortedList(int n);
  void makeEmpty();
  bool isEmpty();
  bool isFull();
  int getLength();
  ItemType getItem(ItemType item, bool & found);
  void putItem(ItemType item);
  void deleteItem(ItemType item);
  void resetList();
  ItemType getNextItem();
  void splitLists(ItemType item, UnsortedList & list1, UnsortedList & list2);

};//UnsortedList



template<class ItemType>
UnsortedList<ItemType>::UnsortedList(){
  MAX_ITEMS = 50;
  info = new ItemType[MAX_ITEMS];
  length = 0;
  current_position = 0;
}//UnsortedList

template<class ItemType>
UnsortedList<ItemType>::UnsortedList(int n){
  MAX_ITEMS = n;
  info = new ItemType[MAX_ITEMS];
  length = 0;
  current_position = 0;
}//UnsortedList(int num)

/*
Function: Initializes list to empty state
Preconditions: None
Postcondition: List is empty
 */
template<class ItemType>
void UnsortedList<ItemType>::makeEmpty(){
  /*
   for(int i = 0; i < MAX_ITEMS; i++){
    info[i] = NULL;
  }//for
  */
  info = new ItemType[MAX_ITEMS];
  length = 0;
  current_position = 0;
}//isEmpty

/*
Function: Determines whether the list is full
Precondition: List has been initialized
Postcondition: Function value = (list is empty)
 */
template<class ItemType>
bool UnsortedList<ItemType>::isEmpty(){
  if(info != NULL){
    return (length == 0);
  }//if
}//isEmpty
/*
Function: Determines whether the list is full
Precondition: List has been initialized
Postcondition: Function value = (list is full)
 */
template<class ItemType>
bool UnsortedList<ItemType>::isFull(){
  if(info != NULL){
    return (length == MAX_ITEMS);
  }//if
}//isFull

/*
Function: Determines the number of elements in list
Precondition: List has been initialized
Postcondition: Function value = number of elements in list
 */
template<class ItemType>
int UnsortedList<ItemType>::getLength(){
  if(info != NULL){
    return length;
  }//if  
}//getLength

/*
Function: Get list element whose key matches item's key (if present)
Preconditions: List has been initialized. Key member of item is initialized
Postconditions: If there is an element someItem whose key matches item's key, then found =
true and copy of someItem is returned; otherwise found = false and item is returned. List is
unchanged
 */
template<class ItemType>
ItemType UnsortedList<ItemType>::getItem(ItemType item, bool & found){
  if(info != NULL){
    for(int i = 0; i < length; i++){
      if(item == info[i]){
	found = true;
	ItemType temp = info[i];
	return temp;
      }//if
    }//for
    found = false;
    return item;
  }//if
  else{
    cout << "List not initialized" << endl;
  }//else
}//getItem

/*
Function: Puts item to list (adds new item at the end of list)
Preconditions: List has been initialized. List is not full
Postcondition: If item was not in the list then Item is in list, otherwise an exception is thrown
 */
template<class ItemType>
void UnsortedList<ItemType>::putItem(ItemType item){
  if((info != NULL) && (length != MAX_ITEMS)){
    bool temp = true;
    for(int i = 0; i < length; i++){
      if(info[i] == item){
	temp = false;
      }//if
    }//for
    if(temp){
      info[length] = item;
      length++;
    }//if
  }//if
  else{
    cout << "Unable to add item" << endl;
  }//else
}//putItem

/*
Function: Deletes the element whose key matches item's key
Preconditions: List has been initialized. Key member of item is initialized
Postcondition: If one element in list has a key matching item's key then no element in list has
a key matching item's key, otherwise an exception is thrown (displaying a message to the user
"Element is not found in the list")
 */
template<class ItemType>
void UnsortedList<ItemType>::deleteItem(ItemType item){
  if(info != NULL){
    bool found = false;
    int index = 0;
    for(int i = 0; i < length; i++){
      if(info[i] == item){
	found = true;
	index = i;
	break;
      }//if
    }//for
    if(found){
      for(int i = index; i < length; i++){
	if(i == (length - 1)){
	  ItemType fake;
	  info[i] = fake;
	}//if
	else{
	  info[i] = info[i + 1];
	}//else
      }//for
      length--;
    }//if
    else{
      cout << "Unable to delete item" << endl;
    }//else
  }//if
  else{
    cout << "Unable to delete item" << endl;
  }//else
}//deleteItem

/*
Function: Initializes current position for an iteration through the list
Precondition: List has been initialized
Postcondition: Current position is prior to list
 */
template<class ItemType>
void UnsortedList<ItemType>::resetList(){
  if(info != NULL){
    current_position = 0;
  }//if
}//resetList

/*
Function: Gets the next element in list
Preconditions: List has been initialized. Current position is defined. Element at current
position is not last in list
Postconditions: Current position is updated to next position. Returns a copy of element at
current position
 */
template<class ItemType>
ItemType UnsortedList<ItemType>::getNextItem(){
  if((info != NULL) && (current_position >= 0)){
    ItemType temp;
    if(current_position < length){
      temp = info[current_position];
      if(current_position < (length - 1)){
	current_position++;
      }//if
    }//if
    return temp;
  }//if
}//getNextItem

/*
Function: Divides list into two lists according to the key of item
Precondition: List has been initialized
Postcondition: If list is not empty: list1 contains all the items of list whose keys are less than
or equal to item's key; list2 contains all the items of list whose keys are greater than item's
key. If list was empty an exception is thrown displaying appropriate message to the user
 */
template<class ItemType>
void UnsortedList<ItemType>::splitLists(ItemType item, UnsortedList & list1, UnsortedList & list2){
  if(isEmpty()){
    cout << "List is empty" << endl;
  }//if
  else{
    for(int i = 0; i < length; i++){
      if(!(info[i] > item)){
	list1.putItem(info[i]);
      }//if
      else{
	list2.putItem(info[i]);
      }//else
    }//for
  }//else
}//splitLists

/*
Function: returns list index which contains list element whose key matches item's key (if present)
Preconditions: List has been initialized. Key member of item is initialized
Postconditions: If there is an element someItem whose key matches item's key, then its index is
returned, otherwise -1 is returned. List is unchanged
 */
template<class ItemType>
int UnsortedList<ItemType>::findItem(ItemType item){
  if((info != NULL) && (item != NULL)){
    for(int i = 0; i < length; i++){
      if(info[i] == item){
	return i;
      }//if
    }//for
    return -1;
  }//if
}//findItem
