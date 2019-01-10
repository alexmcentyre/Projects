
#include <ios>
#include <iostream>
#include <cstdlib>

using namespace std;

extern const char ** environ;

/*
This main function prints out all of the environmental
variables that are set.
 */
int main(const int argc, const char * argv []){
  cout.setf(ios::unitbuf);

  for(const char ** env = environ; *env != nullptr; ++env){
    cout << *env << endl;
  }//for

  return EXIT_SUCCESS;
}//main
