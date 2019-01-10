
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

void rDir(const char * dir, mode_t m);

/*
The main function takes command line arguments from the user
which are checked with if and else statements to determine what
the user wishes to do.

Parameters:
const int argc (number of arguments)
const char * argv [] (array of arguments) 
 */
int main(const int argc, const char * argv []){
  cout.setf(ios::unitbuf);

  mode_t mode = 0755;
  bool flagP = false;
  umask(0);  

  //this loops through the command line arguments
  for(int i = 1; i < argc; ++i){
    string check = argv[i];

    if(check == "-m"){
      if(i < argc - 1){
	++i;
	string temp = argv[i];
	mode = stol(temp, nullptr, 8);
      }//if
    }//if

    else if(check == "-p"){
      flagP = true;
    }//if

    else if((check == "-pm") || (check == "-mp")){
      flagP = true;
      if(i < argc - 1){
	++i;
	string temp = argv[i];
	mode = stol(temp, nullptr, 8);
      }//if
    }//else if

    else{
      if(mkdir(argv[i], mode) == -1){
	if(!flagP){
	  string output = argv[0];
	  output += ": cannot create directory `";
	  output += argv[i];
	  output += "'";
	  perror(output.c_str());
	  exit(EXIT_FAILURE);
	}//if
	else{
	  rDir(argv[i], mode);
	}//else
      }//if
    }//else
  }//for


  return EXIT_SUCCESS;
}//main


/*
This function is used to create intermediate directories
when the user wishes to create a directory inside of one that
does not exist. The full pathname broken up to determine which
directories need to be made. Intermediate directories are created
with the mode 0755.

Parameters:
const char * dir (the full pathname)
mode_t m (the mode of the lowest directory created)

 */
void rDir(const char * dir, mode_t m){
  
  char temp[1024];
  stringstream convert;
  convert << dir;
  convert >> temp;

  string fake = "";
  for(unsigned int i = 0; i < sizeof(temp); i ++){
    char check = temp[i];
    if((check != '/') && (check != '\0')){
      fake += check;
    }//if

    else if(check == '\0'){
      mkdir(fake.c_str(), m);
      i = sizeof(temp);
    }//else

    else{
      mkdir(fake.c_str(), 0755);
      fake += check;
    }//else
  }//for

}//rDir
