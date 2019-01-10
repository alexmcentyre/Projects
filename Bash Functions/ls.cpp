#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <vector>
#include <string>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <cstddef>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;
/**
  This global method takes a string representation of a file name and returns the file type of the file.
  @param file a string variable representing a file name
**/
string fileTypeTester(string file){
  struct stat temp;
  string fileType;
  
  if(stat(file.c_str(), &temp) == -1){
    cout << "stat failure" << endl;
    exit(EXIT_FAILURE);
  }
    switch(temp.st_mode & S_IFMT){
      case S_IFBLK:
        fileType  = "block special file";
        break;
      case S_IFCHR:
        fileType = "character special file";
        break;
      case S_IFDIR:
        fileType = "directory";
        break;
      case S_IFIFO:
        fileType = "FIFO/pipe";
        break;
      case S_IFLNK:
        fileType = "symlink";
        break;
      case S_IFREG:
        fileType = "regular file";
        break;
      case S_IFSOCK:
        fileType = "socket";
        break;
      default:
        fileType = "unknown?!?!";
        break;
    }
  return fileType;
}
/**
  This global method takes a string that represents the name of a symbolic link, and returns the name of the file that it points to
  @param symLinkName a string variable that represents the name of a symbolic link
**/
string symLinkTester(string symLinkName){
  char buffer[100];
  unsigned int size = 100;
  if((readlink(symLinkName.c_str(), buffer, size)) == -1){
    exit(EXIT_SUCCESS);
  }
  string fileName(buffer);
  
  return fileName;
}
/**
  This global method takes a vector of strings that represent files entered into the program. It then sorts out the files within the string vector that
  are not hidden, and it stores them within a new vector. The new vector is then returned.
  @param arguments a vector of strings that represents files entered into the program
  @param flag a boolean value that represents whether or not flags were used
**/
vector<string> nonHiddenFiles(vector<string> arguments, bool flag){
  unsigned int count = 0;
  string nHFiles = "", file;
  vector<string> allFiles;
  
  while(count < arguments.size()){
    file = arguments[count];
    if((file.at(2) == '/')||(file.at(1) == '/')){
      allFiles.push_back(file);
      count++;
    }else if(file.at(0) == '.'){
      count++;
    }else{
      allFiles.push_back(file);
      count++;
    }
  }
  return allFiles;
}
/**
  This method takes a string, that represents a directory name, opens that directory, and stores the names of the files in that directory into a new vector.
  It then returns this new vector.
  @param dirName a string variable that represents a directory name
  @param flag a boolean variable that represents whether or not flags were used
  @param flags a string variable that that holds the flags entered into the program
**/
vector<string> iterateDirectory(string dirName, bool flag, string flags){
  string fileName = "";
  struct dirent *singleFile;
  DIR *directory = opendir(dirName.c_str());
  vector<string> contents;
  
  while((singleFile = readdir(directory)) != NULL){
    if(flag){
      if((flags == "-l")){
        fileName = singleFile->d_name;
        if(fileName.at(0) == '.'){
          //do nothing
        }else{
          contents.push_back(fileName);
        }
      }
      if((flags == "-a")||(flags == "-al")||(flags == "la")){
        fileName = singleFile->d_name;
        contents.push_back(fileName);
      }
    }else{
      fileName = singleFile->d_name;
      if(fileName.at(0) == '.'){
        //do nothing
      }else{
        contents.push_back(fileName);
      }
    }
  }
  if((closedir(directory)) == -1){
    cout << "Problem closing directory" << endl;
    exit(EXIT_SUCCESS);
  }
  return contents;
}
/**
  This global method takes a string, a filename, and prints the filename, along with other things, to the console.
  @param fileName a string variable that represents a file name
  @param flag a boolean variable that represents whether or not flags were used
  @param flags a string variable that that holds the flags entered into the program
**/
void longFormat(string fileName, bool flag, string flags){
  string fileType, name, gName, login = getlogin(), checker, finalStr = "", symPointsTo = "", dir, dirContents = "", dirLF = "";
  struct stat temp;
  struct passwd * something;
  struct group * something2;
  
  if(fileName == "-"){
    if(fstat(STDIN_FILENO, &temp) == -1){
      perror("stat");
      exit(EXIT_FAILURE);
    }
  }else{
    if(stat(fileName.c_str(), &temp) == -1){
      perror("stat");
      exit(EXIT_FAILURE);
    }
  }
  string aStuff = "";
  
  something = getpwuid(temp.st_uid);
  name = something->pw_name;

  something2 = getgrgid(temp.st_gid);
  gName = something2->gr_name;
  
    switch(temp.st_mode & S_IFMT){
      case S_IFBLK:
        fileType  =  "block special file";
        aStuff += 'b';
        break;
      case S_IFCHR:
        fileType = "character special file";
        aStuff += 's';
        break;
      case S_IFDIR:
        fileType = "directory";
        //here too
        aStuff += 'd';
        break;
      case S_IFIFO:
        fileType = "FIFO/pipe";
        aStuff += 'p';
        break;
      case S_IFLNK:
        fileType = "symlink";
        fileName += " -> " + symLinkTester(fileName);
        aStuff += 's';
        break;
      case S_IFREG:
        fileType = "regular file";
        aStuff += '-';
        break;
      case S_IFSOCK:
        fileType = "socket";
        break;
      default:
        fileType = "unknown?!?!";
        break;
    }
    
    mode_t perms = temp.st_mode & 07777;
    aStuff += (perms & S_IRUSR) ? 'r': '-';
    aStuff += (perms & S_IWUSR) ? 'w': '-';
    aStuff += (perms & S_IXUSR) ? 'x': '-';
    aStuff += (perms & S_IRGRP) ? 'r': '-';
    aStuff += (perms & S_IWGRP) ? 'w': '-';
    aStuff += (perms & S_IXGRP) ? 'x': '-';
    aStuff += (perms & S_IROTH) ? 'r': '-';
    aStuff += (perms & S_IWOTH) ? 'w': '-';
    aStuff += (perms & S_IXOTH) ? 'x': '-';
    
    const time_t  timerA = temp.st_atime;
    
    int numLinks = temp.st_nlink;
    string time = ctime(&timerA);
    time = time.substr(4, 12);
    
    cout << aStuff << ". " << setw(2) << right << to_string(numLinks) << " " << name << " " << gName << setw(8) << right << to_string(temp.st_size) << " ";
    cout << left << time << " ";
    

}
/**
  This global method determines whether or not flags were used
  @param argv an array of pointers to chars
  @param argc an integer value representing the number of total arguments entered into the program
  @param flag a boolean variable that represents whether or not flags were used
**/
string flagTester(char *argv[], int argc, bool flag){
  string flags = "";
  
  if(argc < 2){
    flag = false;
    return flags;
  }else{
    flags = argv[1];
  }
  return flags;
}
/**
  This global method takes a vector of strings that represents files, and it prints those files to the console
  @param allFiles a vector of strings that represent a file name
  @param flag a boolean variable that represents whether or not flags were used
  @param flags a string variable that that holds the flags entered into the program
**/
void fileVectorOutput(vector<string> allFiles, bool flag, string flags){
  unsigned int count = 0, tabCount = 0;
  string file = "";
  
  while(count < allFiles.size()){//printing file names in allFiles vector name
    file = allFiles[count];
    if(flag && ((flags == "-l")||(flags == "-al")||(flags == "-la"))){
      longFormat(file, flag, flags);
      if(count == allFiles.size()-1){
        cout << file;
      }else{
        cout << file << endl;
      }
    }else{
      cout << file << '\t';
      tabCount++;
      if(tabCount == 9){
        tabCount = 0;
        cout << endl;
      }
    }
    count++;
  }
}
/**
  This global method takes a vector that represents all arguments entered into the program, except flags and the executable, and sorts those arguments into one of
  two vectors, a vector for directories and a vector of files. 
  @param allFiles a vector of strings that represent file names
  @param allDirectories a vector of strings that represent directory names
  @param allArguments a vector of strings that represent all arguments entered into the program
**/
void sortingFiles(vector<string> &allFiles, vector<string> &allDirectories, vector<string> allArguments){
  string file = "", fileType = "";
  unsigned int temper = 0;
  
  while(temper < allArguments.size()){ //seperating files and directories
    file = allArguments[temper];
    fileType = fileTypeTester(file);
    if(fileType == "directory"){
      allDirectories.push_back(file);
    }else{
      allFiles.push_back(file);
    }
    temper++;
  }
}
/**
  This global method takes a string that represents a directory name and it iterates through the files in that directory and adds up all of the block sizes
  @param directoryName a string that represents a directory name
  @param flag a boolean variable that represents whether or not flags were used
  @param flags a string variable that that holds the flags entered into the program
**/
int totalBlkSize(string directoryName, bool flag, string flags){
  struct stat temp;
  unsigned int blkSize = 0, dirFilesCount = 0;
  string directory = "", directoryFile = "", tempFilePath = "";
  vector<string> directoryFiles;

  directoryFiles = iterateDirectory(directoryName, flag, flags);
  while(dirFilesCount < directoryFiles.size()){
    directoryFile = directoryFiles[dirFilesCount];
    tempFilePath = directoryName + "/" + directoryFile;
    
    if(directoryFile == "-"){
      if(fstat(STDIN_FILENO, &temp) == -1){
      perror("stat");
      exit(EXIT_FAILURE);
      }
    }else{
      if(stat(tempFilePath.c_str(), &temp) == -1){
        perror("stat");
        exit(EXIT_FAILURE);
      }
    }
    blkSize += temp.st_blocks;
    dirFilesCount++;
  }
  blkSize /= 2;
  return blkSize;
}
/**
  This global method takes a vector of strings that represent directory names and it prints out the files of each directory to the console
  @param allDirectories a vector of strings that represent directory names
  @param flag a boolean variable that represents whether or not flags were used
  @param flags a string variable that that holds the flags entered into the program
**/
void sortingDirectories(vector<string> &allDirectories, bool flag, string flags){

  unsigned int temper = 0, fileCount = 0, blkSize;
  vector<string> directoryFiles;
  string file = "", tempfile = "", appenedFile = "", directoryName = "";
  
  while(temper < allDirectories.size()){
    if(allDirectories.size() == 1){
      //do nothing
    }else{
      cout << allDirectories[temper] << ":" << endl;    
    }
    directoryName = allDirectories[temper];
    if(flag && ((flags == "-l")||(flags == "-la")||(flags == "-al"))){
      blkSize = totalBlkSize(directoryName, flag, flags);
      cout << "total " << blkSize << endl;
    }
    directoryFiles = iterateDirectory(directoryName, flag, flags);
    sort(directoryFiles.begin(), directoryFiles.end());
    fileCount = 0;
    blkSize = 0;
    while(fileCount < directoryFiles.size()){
      file = directoryFiles[fileCount];
      if(flag && ((flags == "-l")||(flags == "-al")||(flags == "-la"))){
        appenedFile = directoryName + "/" +file;
        longFormat(appenedFile, flag, flags);
        if(fileTypeTester(appenedFile) == "symlink"){
          file += " -> " + symLinkTester(file);
        }
        cout << left << file << endl;
      }else{
        cout << file << "  ";
      }
      fileCount++;
    }
    if(temper == allDirectories.size()-1){
      //do nothing
    }else{
      cout << endl;
    }
    temper++;
  }
}
/**
  The main method takes arguments from the console and runs the program
  @param argv an array of pointers to chars
  @param argc an integer value representing the number of total arguments entered into the program
**/
int main(int argc, char *argv[]){
  cout.setf(ios::unitbuf);
  bool flag = false;
  string flags, file, fileType, naked = ".";
  int count = 0, index = 0, temp, temp2, flagN;
  vector <string> allFiles, allDirectories, directoryFiles, allArguments;
  flags = flagTester(argv, argc, flag);

  if((flags == "-a")||(flags == "-l")||(flags == "-al")||(flags == "-la")){
    flag = true;
  }

  if(flags == "-a"){
    flagN = 1;
  }else if(flags == "-l"){
    flagN = 2;
  }else if((flags == "-al")||(flags == "-la")){
    flagN = 3;
  }else{
    flagN = 0;
  }
  
  if(((argc == 1)&&(flag == false)) || ((argc == 2)&&(flag == true))){
    allDirectories.push_back(naked);
    sortingDirectories(allDirectories, flag, flags);
    cout << '\n';
    exit(EXIT_SUCCESS);
  }

  if(flag && (argc > 1)){
    count = 3;
    index = 2;
  }else{
    count = 2;
    index = 1;
  }

  temp = count, temp2 = index;

  while(temp <= argc){
    file = argv[temp2];
    allArguments.push_back(file);
    temp2++;
    temp++;
  }
  
  index = 0;
  file = "";
    
    switch(flagN){
      case 1:
          sortingFiles(allFiles, allDirectories, allArguments);
          
          sort(allFiles.begin(), allFiles.end());
          sort(allDirectories.begin(), allDirectories.end());
          
          fileVectorOutput(allFiles, flag, flags);
          if(allDirectories.size() == 0){
            cout << endl;
          }else{
            cout << '\n';
          }
          sortingDirectories(allDirectories, flag, flags);
        break;
      case 2:
          allArguments = nonHiddenFiles(allArguments, flag);
          sortingFiles(allFiles, allDirectories, allArguments);
          
          sort(allFiles.begin(), allFiles.end());
          sort(allDirectories.begin(), allDirectories.end());
          
          if(allFiles.size() != 0){
            fileVectorOutput(allFiles, flag, flags);
          }
          
          if(allDirectories.size() == 0){
            cout << endl;
          }else if(allDirectories.size() == 1){
            //do nothing
          }else{
            cout << '\n';
          }
          sortingDirectories(allDirectories, flag, flags);
      
        break;
      case 3:
          sortingFiles(allFiles, allDirectories, allArguments);
          
          sort(allFiles.begin(), allFiles.end());
          sort(allDirectories.begin(), allDirectories.end());
          
          fileVectorOutput(allFiles, flag, flags);
          if(allDirectories.size() == 0){
            cout << endl;
          }else{
            cout << '\n';
          }
          sortingDirectories(allDirectories, flag, flags);
        break;
      case 0:
      default:
          allArguments = nonHiddenFiles(allArguments, flag);
          sortingFiles(allFiles, allDirectories, allArguments);
          
          sort(allFiles.begin(), allFiles.end());
          sort(allDirectories.begin(), allDirectories.end());
          
          fileVectorOutput(allFiles, flag, flags);
          if((allDirectories.size() == 0)){
            cout << endl;
          }else{
            cout << '\n';
          }
          sortingDirectories(allDirectories, flag, flags);
          
        break;
    }
}
