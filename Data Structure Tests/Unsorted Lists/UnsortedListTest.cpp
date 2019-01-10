
/*

UnsortedListTest.cpp

Author: Alex McEntyre

Date: 1/25/17

Purpose: This program is meant to implement a generic ADT UnsortedList while practicing a good
software engineering design approach.

 */

#include "UnsortedList.cpp"
#include "Stud.h"
#include "Stud.cpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template<class ItemType>
void printList(UnsortedList<ItemType> list){
    list.resetList();
    for(int i = 0; i < list.getLength(); i++){
      cout << list.getNextItem() << endl;
    }//for
    list.resetList();
    cout << endl;
}//printList

int main(){

  /*
  cout << "*TESTING INTEGER LISTS*" << endl;
  cout << endl;
  cout << endl;


  
  //TEST CASE 1 
  cout << "TEST CASE 1" << endl;

  UnsortedList<int> temp1(5);
  temp1.putItem(1);
  temp1.putItem(2);
  temp1.putItem(3);
  temp1.putItem(4);
  temp1.putItem(5);

  printList(temp1);
  temp1.putItem(6);

  temp1.deleteItem(4);
  printList(temp1);

  temp1.makeEmpty();
  printList(temp1);

  temp1.deleteItem(4);

  
  /////////////////////////////////////////////////////////////
  

  //TEST CASE 2
  cout << endl;
  cout << endl;
  cout << "TEST CASE 2" << endl;

  UnsortedList<int> temp2(1);

  cout << "Empty: " << temp2.isEmpty() << endl;
  cout << "Full: " << temp2.isFull() << endl;
  cout << endl;

  temp2.putItem(0);

  cout << "Empty: " << temp2.isEmpty() << endl;
  cout << "Full: " << temp2.isFull() << endl;

///////////////////////////////////////////////////////////////


    //TEST CASE 3
  cout << endl;
  cout << endl;
  cout << "TEST CASE 3" << endl;

  UnsortedList<int> temp3(5);
  UnsortedList<int> list1;
  UnsortedList<int> list2;

  temp3.putItem(1);
  temp3.putItem(2);
  temp3.putItem(3);
  temp3.putItem(4);
  temp3.putItem(5);

  printList(temp3);

  temp3.splitLists(3, list1, list2);
  printList(list1);
  printList(list2);

//////////////////////////////////////////////////////////////

  //TEST CASE 4
  cout << endl;
  cout << "TEST CASE 4" << endl;

  UnsortedList<int> temp4(3);

  temp4.putItem(1);
  temp4.putItem(2);
  temp4.putItem(3);
  printList(temp4);

  cout << "Length: " << temp4.getLength() << endl;
  cout << "Next Item: " << temp4.getNextItem() << endl;
  cout << "Next Item: " << temp4.getNextItem() << endl;
  cout << "Next Item: " << temp4.getNextItem() << endl;
  cout << "Next Item: " << temp4.getNextItem() << endl;
  cout << endl;

  cout << "List reset" << endl;
  temp4.resetList();
  cout << "Next Item: " << temp4.getNextItem() << endl;

//////////////////////////////////////////////////////////////////

  //TEST CASE 5
  cout << endl;
  cout << endl;
  cout << "TEST CASE 5" << endl;

  UnsortedList<int> temp5(3);
  bool found;

  temp5.putItem(1);
  temp5.putItem(2);
  temp5.putItem(3);
  printList(temp5);

  cout << "Find 2: " << temp5.getItem(2, found) << endl;
  cout << "found = " << found << endl;
  cout << endl;

  cout << "Find 5: " << temp5.getItem(5, found) << endl;
  cout << "found = " << found << endl;
  cout << endl;

/////////////////////////////////////////////////////////////////
*/




/////////////////////////////////////////////////////////////////

  cout << "*TESTING STUDENT LISTS*" << endl;
  cout << endl;
  cout << endl;

  UnsortedList<Stud> sList(20);

  //TEST CASE 1

  cout << "TEST CASE 1" << endl;
  cout << endl;

  ifstream file;
  file.open("stud.dat");
  for(int i = 0; i < 20; i++){
    int id;
    string name, major;
    file >> id;
    file >> name;
    file >> major;
    Stud temp(id, name, major);
    sList.putItem(temp);
  }//for
  file.close();

  printList(sList);
  cout << "Full?: " << sList.isFull() << endl;
  Stud fake(1, "a", "b");
  sList.putItem(fake);
  cout << endl;

  Stud del(1000, "a", "b");
  sList.deleteItem(del);
  del.setID(1009);
  sList.deleteItem(del);
  del.setID(1019);
  sList.deleteItem(del);
  printList(sList);

  //////////////////////////////////////////////////////////////


  //TEST CASE 2

  cout << "TEST CASE 2" << endl;
  cout << endl;

  cout << "Length = " << sList.getLength() << endl;
  cout << "Deleting a student" << endl;
  del.setID(1001);
  sList.deleteItem(del);
  cout << "New length = " << sList.getLength() << endl;
  cout << endl;
  //////////////////////////////////////////////////////////////


  //TEST CASE 3

  cout << "TEST CASE 3" << endl;
  cout << endl;

  cout << "Next Item: " << endl << sList.getNextItem() << endl;
  cout << "Next Item: " << endl << sList.getNextItem() << endl;
  cout << "Next Item: " << endl << sList.getNextItem() << endl;
  cout << endl;
  cout << "Resetting list" << endl;
  sList.resetList();
  cout << endl;
  cout << "Next Item: " << endl << sList.getNextItem() << endl;
  /////////////////////////////////////////////////////////////////////////


  //TEST CASE 4
  cout << endl;
  cout << "TEST CASE 4" << endl;
  cout << endl;

  bool got;
  cout << "Getting item with ID 1013" << endl;
  del.setID(1013);
  cout << sList.getItem(del, got) << endl;
  cout << "Found?: " << got << endl;
  cout << endl;

  cout << "Getting item that's not in list (ID 2000)" << endl;
  del.setID(2000);
  cout << sList.getItem(del, got) << endl;
  cout << "Found?: " << got << endl;
  /////////////////////////////////////////////////////////////////////////

  //TEST CASE 5
  cout << endl;
  cout << "TEST CASE 5" << endl;
  cout << endl;

  UnsortedList<Stud> split1(20);
  UnsortedList<Stud> split2(20);

  cout << "Splitting this list at ID 1013: " << endl;
  printList(sList);

  del.setID(1013);
  sList.splitLists(del, split1, split2);
  cout << "List 1:" << endl;
  printList(split1);
  cout << "List 2:" << endl;
  printList(split2);
  /////////////////////////////////////////////////////////////////

  //TEST CASE 6

  cout << endl;
  cout << "TEST CASE 6" << endl;
  cout << endl;

  UnsortedList<Stud> empty(20);

  cout << "Attempting to split an empty list" << endl;
  cout << endl;
  empty.splitLists(del, split1, split2);
  cout << endl;
  ////////////////////////////////////////////////////////////////


  //TEST CASE 7
  cout << endl;
  cout << "TEST CASE 7" << endl;
  cout << endl;

  del.setID(2016);
  cout << "Attempting to delete a Student not in the list" << endl;
  cout << endl;
  sList.deleteItem(del);
  cout << endl;
  //////////////////////////////////////////////////////////////////////

  //TEST CASE 8
  cout << endl;
  cout << "TEST CASE 8" << endl;
  cout << endl;

  cout << "Emptying the list" << endl;
  sList.makeEmpty();
  cout << endl;
  cout << "Printing list: " << endl;
  printList(sList);

  cout << "Is the list full?: " << sList.isFull() << endl;
  cout << endl;
  ///////////////////////////////////////////////////////////////////////////////

  //TEST CASE 9
  cout << endl;
  cout << "TEST CASE 9" << endl;
  cout << endl;

  cout << "Attempting to delete from an empty list" << endl;
  cout << endl;

  sList.deleteItem(del);
  cout << endl;
  ///////////////////////////////////////////////////////////////////////////

  //TEST CASE 10
  cout << endl;
  cout << "TEST CASE 10" << endl;
  cout << endl;

  cout << "Getting next item of an empty list:" << endl;
  cout << sList.getNextItem() << endl;
  cout << endl;






  return EXIT_SUCCESS;
}//main
