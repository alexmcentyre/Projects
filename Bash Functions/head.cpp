#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>

using namespace std;
/**
  This is the main method of the program, and this program takes arguments and outputs a certain number of lines of the file input arguments.
  @param argc is an integer value that represents the total number of arguments
  @paran argv is an array of pointers to char values
**/  
int main(int argc, char *argv[]){
  cout.setf(ios::unitbuf);
  int nbytes, lineCount = 0, numFiles = 0, count = 0, count2 = 0, numLines = 10, temp = 0, numArguments;
  char buffer[10000];
  string lines[100], flags = "";
  string lineStr = "", emptyStr = "", totalStr = "", number = "", file;
  int totalBytes = 0;
  vector<string> files;
  
  if(argc > 1){//if the total number of arguments is greater than 1, the second argument is stored within a string variable
    flags = argv[1];
  }
  
  if((argc > 1) && (flags == "-n")){//if a flag is entered then the following argument is stored within an integer variable
    number = argv[2];
    stringstream(number) >> numLines;
    numArguments = 3;
    numFiles = argc - 3;
  }else{
    numArguments = 1;
    numFiles = argc - 1;
  }
  
  temp = numArguments;
  if(numFiles == 0){//stores the file arguments within a vector of strings
    temp = 0;
    while(temp < 1){
      file = "-";
      files.push_back(file);
      temp++;
    }
    numFiles++;
  }else{
    while(count < numFiles){
      file = argv[temp];
      files.push_back(file);
      temp++;
      count++;
    }
  }

  temp = 0;
  while(temp < numFiles){//iterates through the string vector
    
    if(numFiles > 1){
      cout << "==> " << files[temp] << " <==" << endl;
    }
    totalBytes = 0;
    nbytes = 0;
    lineCount = 0;
    lineStr = "";
    if((argc == 1) || (files[temp] == "-")){//uses STDIN_FILENO if "-" is entered as an argument, or only one argument is entered
      while((nbytes = read(STDIN_FILENO, buffer, 10000)) > 0){
        totalBytes += nbytes;
        count2 = 0;
        lineStr = "";
        while(count2 < nbytes){
          lineStr += buffer[count2];
          if(buffer[count2] == '\n'){
            write(STDOUT_FILENO, lineStr.c_str(), nbytes);
            lineCount++;
          }
          if(lineCount == numLines){
              break;
          }
          count2++;
        }
        if(lineCount == numLines){
          break;
        }
      }
    }else{//uses a file from the vector of strings, and outputs a certain number of lines from it
      while((nbytes = read((open(files[temp].c_str(), O_RDONLY)), buffer, 10000)) > 0){
        totalBytes += nbytes;
        count2 = 0;
        while(count2 < nbytes){
          lineStr += buffer[count2];
          if(buffer[count2] == '\n'){
            lineCount++;
          }
          if(lineCount == numLines){
              break;
          }
          count2++;
        }
        if(lineCount == numLines){
          break;
        }
      }
      write(STDOUT_FILENO, lineStr.c_str(), lineStr.size());
    }
    temp++;
  }
  
  
  
  }
