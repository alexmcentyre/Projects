
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sstream>
#include <sys/stat.h>

using namespace std;

char type(const char * name);

/*
This main function uses command line arguments to print the
contents of a file to the end, starting at a point given by the
user. This starting point can be a number of lines from the end
or a number of bytes from the end of the file. If the -f flag is
used then then an if statement is triggered which continues to read
the file for contents that may become available. If no file is given
or the file name is "-" then the program goes to standard input.

Parameters:
const int argc (number of arguments)
const char * argv [] (array of arguments) 
 */

int main(const int argc, const char * argv []){
  cout.setf(ios::unitbuf);

  const char * filename = "-";
  bool flagF = false;
  int bytes = -1;
  int lines = -1;

  //loops through the command line arguments
  for(int i = 1; i < argc; ++i){
    string check = argv[i];
    if(check == "-f"){
      flagF = true;
    }//if

    else if(check == "-c"){
      if(i < (argc - 1)){
	stringstream temp;
	temp << argv[i + 1];
	temp >> bytes;
      }//if
    }//if

    else if(check == "-n"){
      if(i < (argc - 1)){
	stringstream temp;
	temp << argv[i + 1];
	temp >> lines;
      }//if
    }//if

    else{
      filename = argv[i];
    }//else
  }//for

  //This block of code is used when standard input is necessary
  string check = filename;
  if(check == "-"){
    char buffer[1024][1024];
    int count = 0;
    while(read(STDIN_FILENO, buffer[count], sizeof(buffer[count])) > 0){
      count++;
    }//while
    int i = 0;
    while(i < count){
      write(STDIN_FILENO, buffer[i], sizeof(buffer[i]));
      i++;
    }//while  

  }//if


  else{
    
    //error if the file cannot be opened
    string print = argv[0];
    print += ": cannot open `";
    print += filename;
    print += "' for reading";
    int fd;
    if((fd = open(filename, O_RDONLY)) == -1){
      perror(print.c_str());
      return EXIT_FAILURE;
    }//if
    
    
    unsigned char buffer[1];
    
    if((bytes == -1) && (lines == -1)){
      lines = 10;
    }//if
    
    if((bytes != -1) && (lines == -1)){
      lseek(fd, -bytes, SEEK_END);
    }//if
    
    else if(lines != -1){
      int count = 0;
      int hold = -1;
      bool loop = true;
      lseek(fd, -1, SEEK_END);
      while((read(fd, buffer, sizeof(buffer)) > 0) && (loop)){
	if(buffer[0] == '\n'){
	  count++;
	}//if
	if(count == (lines + 1)){
	  hold = lseek(fd, 0, SEEK_CUR);
	  loop = false;
	}//if
	if(lseek(fd, -2, SEEK_CUR) == -1){
	  loop = false;
	  hold = 0;
	}//if
      }//while
      
      lseek(fd, hold, SEEK_SET);
    }//else if
        
    while(read(fd, buffer, sizeof(buffer)) > 0){
      write(STDOUT_FILENO, buffer, sizeof(buffer));
    }//while


    /*
      If the -f flag was used and the file is either
      regular or a fifo then the program continues to read
      the file for more contents that may become available
     */
    if((flagF) && (type(filename) == '1')){
      char buffer[1];
      while(true){
	if(read(fd, buffer, sizeof(buffer)) > 0){
	  write(STDOUT_FILENO, buffer, sizeof(buffer));
	}//if
      }//while

    }//if

    //attempt to close the file
    if(close(fd) == -1){
      perror("./tail");
    }//if
    
  }//else
  
  return EXIT_SUCCESS;
}//main


/*
This function is used to determine if a file is regular, a fifo, or
other. Different chars are returned to make checking easy. Stat is used.

Parameters:
const char * name (the name of the file)

 */
char type(const char * name){
  struct stat mem;

  if(stat(name, &mem) == -1){
    return '0';
  }//if

  if((S_ISREG(mem.st_mode)) || (S_ISFIFO(mem.st_mode))){
    return '1';
  }//if

  else{
    return '0';
  }//else
}//type
