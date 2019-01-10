#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string>
#include <cstdlib>

using namespace std;
/**
  The main method takes arguments from the console and outputs a certain date
  @param argc an integer value that represents a number of arguments
  @param argv an array of pointers to chars 
**/
int main(int argc, char * argv[]){
  cout.setf(ios::unitbuf);
  const char * argvPtr;
  const char * holderPtr;
  string realDate = "";
  string format = "", holderS = "";
  char date[10000];
  struct tm *timeInfo;
  time_t timeMeat;
  time(&timeMeat);
  timeInfo = localtime(&timeMeat);
  unsigned int count = 0, size = 0;
  
  switch(argc){
    case 1:
      size = strftime(date, 80, "%a %b %d %T %Z %Y", timeInfo);
      while(count < size){
        realDate += date[count];
        count++;
      }
      cout << realDate << endl;
      break;
    case 2:
      if(!(*argv[1] == '+')){
        cout << "Improper argument syntax" << endl;
        exit(EXIT_SUCCESS);
      }else{
        holderS = argv[1];
        holderS = holderS.substr(1, string::npos);
        holderPtr = holderS.c_str();
        size = holderS.length();
        
        while(count < size){
          if((holderPtr[count] == '%')&&(count !=0)){
            format += " ";
            format += holderPtr[count];
          }else{
            format += holderPtr[count];
          }
          count++;
        }
        argvPtr = format.c_str();
      }
      
      size = strftime(date, 10000, argvPtr, timeInfo);
      count = 0;
      while(count < size){
        realDate += date[count];
        count++;
      }
      cout << realDate << endl;
      
      break;
    default:
      
      break;
  }

}
