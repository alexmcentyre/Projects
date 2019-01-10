

#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <cerrno>
#include <stdio.h>
#include <clocale>
#include <cstring>
#include <cwchar>

using namespace std;

int countBytes(const int fd);
int countLines(const int fd);
int countChars(const int fd);
int countWords(const int fd);
void sInput();

int totalBytes = 0;
int totalLines = 0;
int totalChars = 0;
int totalWords = 0;

bool flagC = false;
bool flagL = false;
bool flagM = false;
bool flagW = false;

string filename = "";

const size_t BUFFSIZE = 1024;

/*
The main function reads command line arguments
and sets flags appropriately. Any file names the
user gives are used.

Parameters:
const int argc (number of arguments)
char * argv [] (array of arguments)
 */
int main(const int argc, char * argv []){
  cout.setf(ios::unitbuf);
  wcout.setf(ios::unitbuf);
  setlocale(LC_ALL, "en_US.utf8");

  int files = 0;

  int opt;

  while((opt = getopt(argc, argv, "clmw")) != -1){
    switch(opt){
    case 'c':
      flagC = true;
      break;
    case 'l':
      flagL = true;
      break;
    case 'm':
      flagM = true;
      break;
    case 'w':
      flagW = true;
      break;
    default:
      exit(EXIT_FAILURE);
    }//switch
  }//while

  if((!flagC) && (!flagL) && (!flagM) && (!flagW)){
    flagC = true;
    flagL = true;
    flagW = true;
  }//if

  for(int i = optind; i < argc; i++){
    int fd;
    bool go = true;

    filename = argv[i];
    
    if(filename == "-"){
      go = false;
      files += 1;
      sInput();
    }//if

    else if((fd = open(argv[i], O_RDONLY)) == -1){
      string p = argv[0];
      p += ": ";
      p += argv[i];
      perror(p.c_str());
      go = false;
    }//if

    if(go){

      cout << " ";
      
      if(flagL){
	lseek(fd, 0, SEEK_SET);
	cout << countLines(fd) << "   ";
      }//if
      
      if(flagW){
	lseek(fd, 0, SEEK_SET);
	cout << countWords(fd) << "   ";
      }//if
      
      if(flagC){
	lseek(fd, 0, SEEK_SET);
	cout << countBytes(fd) << "   ";      
      }//if
      
      if(flagM){
	lseek(fd, 0, SEEK_SET);
	cout << countChars(fd) << "   ";     
      }//if
      
      cout << filename << endl;
      
      if(close(fd) == -1){
	perror(filename.c_str());
      }//if
    }//if go
    files++;
  }//for  
  
  if(filename == ""){
    files += 1;
    sInput();
  }//if

  if(files > 1){
    cout << " ";
    if(flagL)
      cout << totalLines << "   ";
    if(flagW)
      cout << totalWords << "   ";
    if(flagC)
      cout << totalBytes << "   ";
    if(flagM)
      cout << totalChars << "   ";
    cout << "total" << endl;
  }//if
  
  return EXIT_SUCCESS;

}//main


/*
This function counts the number of bytes in a file.

Parameters:
const int fd (file descriptor)
 */
int countBytes(const int fd){
  char buffer[1];
  int temp, counter = 0;
  while((temp = read(fd, buffer, sizeof(buffer))) > 0){
    counter += temp;
  }//while
  totalBytes += counter;
  return counter;
}//countBytes


/*
This function counts the number of lines in a file.

Parameters:
const int fd (file descriptor)
 */
int countLines(const int fd){
  char buffer[1];
  int counter = 0;
  while(read(fd, buffer, sizeof(buffer)) > 0){
    if(buffer[0] == '\n'){
      counter++;
    }//if
  }//while
  totalLines += counter;
  return counter;
}//countLines


/*
This function counts the number of characters in a file.

Parameters:
const int fd (file descriptor)
 */
int countChars(const int fd){
  size_t numChars = 0;
  size_t numBytes = 0;
  char buffer[BUFFSIZE];
  while((numBytes = read(fd, buffer, BUFFSIZE)) > 0){
    mbstate_t state = mbstate_t();
    size_t len = 0;
    wchar_t wc = '\0';
    size_t sum = 0;
    while((len = mbrtowc(&wc, buffer+sum, numBytes-sum, &state)) > 0){
      if(len == (size_t) -2){
	break;
      }//if
      sum += len;
      numChars += 1;
    }//while
    if(sum < numBytes){
      lseek(fd, sum-numBytes, SEEK_CUR);
    }//if
    /*
    char * ptr = buffer;
    const char * end = ptr + strlen(ptr);
    int length;
    wchar_t wc = '\0';
    while((length = mbrtowc(&wc, ptr, end-ptr, &state)) > 0){
      ptr += length;
      counter += 1;
      if(ptr > end){
	break;
      }//if
    }//while
    */
  }//while
    
  totalChars += numChars;
  return numChars;
}//countChars


/*
This function counts the number of words in a file.

Parameters:
const int fd (file descriptor)
 */
int countWords(const int fd){
  char buffer[1];
  int counter = 0;
  bool flip = true;

  while(read(fd, buffer, sizeof(buffer)) > 0){
    if((buffer[0] != ' ') && (buffer[0] != '\n')){
      counter++;
      break;
    }//if
  }//while
  while(read(fd, buffer, sizeof(buffer)) > 0){
    if((buffer[0] == ' ') || (buffer[0] == '\n')){
      flip = false;
    }//if 
    if((buffer[0] != ' ') && (buffer[0] != '\n')){
      if(!flip){
	counter++;
      }//if
      flip = true;
    }//if
  }//while
  totalWords += counter;
  return counter;
}//countWords


/*
This function allows the user to type to standard input.
While they are doing this the function counts the number
of bytes, lines, chars, and words that they input.
 */
void sInput(){

  char buffer[BUFFSIZE];  

  unsigned int nBytes, byteCount = 0;

  int lineCount = 0;

  int wordCount = 0;
  bool wordFlip = false;

  size_t numChars = 0;
  size_t numBytes = 0;
  //int charCount;

  while((nBytes = read(STDIN_FILENO, buffer, BUFFSIZE)) > 0){
    numBytes = nBytes;
    //bytes
    if(flagC){
      byteCount += nBytes;
    }//if

    //lines
    if(flagL){
      lineCount++;
    }//if

    //words
    if(flagW){
      for(unsigned int i = 0; i < nBytes; i++){
	if((buffer[0] != ' ') && (buffer[0] != '\0')){
	  wordCount += 1;
	  wordFlip = true;
	  break;
	}//if
      }//for
      for(unsigned int i = 0; i < nBytes; i++){
	if((buffer[i] == ' ') && (buffer[i] != '\0')){
	  wordFlip = false;
	}//if
	if((buffer[i] != ' ') && (buffer[i] != '\0')){
	  if(!wordFlip){
	    wordCount += 1;
	  }//if
	  wordFlip = true;
	}//if
      }//for
    }//if


    //chars
    if(flagM){

      
      mbstate_t state = mbstate_t();
      size_t len = 0;
      wchar_t wc = '\0';
      size_t sum = 0;
      while((len = mbrtowc(&wc, buffer+sum, numBytes-sum, &state)) > 0){
	if(len == (size_t) -2){
	  break;
	}//if
	sum += len;
	numChars += 1;
      }//while
      if(sum < numBytes){
	lseek(STDIN_FILENO, sum-numBytes, SEEK_CUR);
      }//if
      

      /*
      mbstate_t state = mbstate_t();
      char * ptr = buffer;
      const char * end = ptr + strlen(ptr);
      int length;
      wchar_t wc = '\0';
      while((length = mbrtowc(&wc, ptr, end-ptr, &state)) > 0){
	ptr += length;
	charCount += 1;
	if(ptr > end){
	  break;
	}//if
      }//while
      */

    }//if

  }//while

  cout << " ";

  totalLines += lineCount;
  if(flagL){
    cout << lineCount << "   ";
  }//if

  totalWords += wordCount;
  if(flagW){
    cout << wordCount << "   ";
  }//if

  totalBytes += byteCount;
  if(flagC){
    cout << byteCount << "   ";
  }//if

  totalChars += numChars;
  if(flagM){
    cout << numChars << "   ";
  }//if

  cout << filename << endl;
}//sInput
