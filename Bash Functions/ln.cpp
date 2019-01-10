#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <unistd.h>

using namespace std;
/**
  The main method takes arguments from the console and outputs a certain date
  @param argc an integer value that represents a number of arguments
  @param argv an array of pointers to chars 
**/
int main(int argc, char * argv[]){
  cout.setf(ios::unitbuf);
  int checked;
  string check;

  if(argc < 3){
    cout << "More arguments required" << endl;
    exit(EXIT_SUCCESS);
  }
  
  switch(argc){
    case 3:
      if((checked = link(argv[1], argv[2])) == -1){
        cout << "Link Failed" << endl;
        exit(EXIT_SUCCESS);
      }
      break;
    case 4:
      check = argv[1];
      if(check != "-s"){
        cout << "Second argument is improper" << endl;
        exit(EXIT_SUCCESS);
      }
      if((checked = symlink(argv[2], argv[3])) == -1){
        cout << "Link Failed" << endl;
        exit(EXIT_SUCCESS);
      }
      break;
    default:
      break;
  
  }

}
