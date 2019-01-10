
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <vector>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string>
#include <fcntl.h>

using namespace std;

bool startPipe;
bool outPipe;
string outStr;
string inStr;
bool reOutT;
bool reOutA;
bool reIn;
bool background;
bool isJob;
int jobCount;


//struct to hold process info
struct process{
  int argCount = 0;
  pid_t processID;
  pid_t groupID;
  vector<string> args;
};//process

//job struct to hold a vector of processes
struct job{
  vector<process> processes;
  pid_t jobID;
  string jobInput;
  string status = "Running";
};//job

vector<job> jobs;

vector<char *> make_cstrvector(vector<string> & strvector);
void dl_cstrvector(vector<char *> & cstrvector);
void vector_exec(vector<string> argv);
void nope_out(const string & sc_name);
void close_pipe(int pipefd[2]);
void close_fd(int fd);
void update_status(const string & status, pid_t target);
void print_jobID(pid_t target);
void print_jobInput(pid_t target);

void builtin_help();
void builtin_exit(const string status);
void builtin_cd(const string pname);
void builtin_jobs();
void builtin_export(vector<string> argLine);
void builtin_fg(vector<string> argLine);
void builtin_bg(vector<string> argLine);

/*
  This function creates pipes and uses fork to execute jobs.
 */
void execute(vector<process>  & processLine){  //This was (vector<string> argLine)
  pid_t pid, pgid;
  //pid_t wpid;
  int status = 0;
  int pipefd[1024][2];


  for(unsigned int i = 0; (i < processLine.size()) && (i < 20); i++){
    //if i mod 2 equals 1 make new pipe

    if(startPipe){
      if(pipe(pipefd[i]) == -1){
	nope_out("pipe");
      }//if
    }//if

    string check = processLine[i].args[0];

    if(check == "help"){
      builtin_help();
    }//if
    else if(check == "exit"){
      if(processLine[i].args.size() > 1){
	builtin_exit(processLine[i].args[1]);
      }//if
      else{
	builtin_exit("\0");
      }//else
    }//else if
    else if(check == "cd"){
      if(processLine[i].args.size() > 1){
	builtin_cd(processLine[i].args[1]);
      }//if
      else{
	builtin_cd(getenv("HOME"));
      }//else
    }//else if
    else if(check == "jobs"){
      builtin_jobs();      
    }//else if
    else if(check == "export"){
      builtin_export(processLine[i].args);
    }//else if
    else if(check == "fg"){
      builtin_fg(processLine[i].args);
    }//else if
    else if(check == "bg"){
      builtin_bg(processLine[i].args);
    }//else if
    ///////////////////////////////////////////////////////////////

    else{
      isJob = true;
      //cout << getpgrp() << endl;
      if((pid = fork()) == -1){
	nope_out("fork");
      }//if
      
      else if(pid == 0){
	
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	

	if(reIn){
	  int in;
	  if((in = open(inStr.c_str(), O_RDONLY)) == -1){
	    nope_out("open");
	  }//if
	  else{
	    dup2(in, STDIN_FILENO);
	    close_fd(in);
	  }//else 
	}//if


	if(startPipe){
	  if(i == 0){
	    if(dup2(pipefd[i][1], STDOUT_FILENO) == -1){
	      nope_out("dup2");
	    }//if
	    close_pipe(pipefd[i]);
	  }//if
	  else if(i > 0){
	    if(dup2(pipefd[i - 1][0], STDIN_FILENO) == -1){
	      nope_out("dup2");
	    }//if
	    if(i < (processLine.size() - 1)){
	      if(dup2(pipefd[i][1], STDOUT_FILENO) == -1){
		nope_out("dup2");
	      }//if
	    }//if
	    close_pipe(pipefd[i - 1]);
	    if(i < (processLine.size() - 1)){
	      close_pipe(pipefd[i]);
	    }//if
	  }//if
	}//if start pipe

	if(reOutT){
	  int out;
	  if((out = open(outStr.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1){
	    nope_out("open");
	  }//if
	  else{
	    dup2(out, STDOUT_FILENO);
	    close_fd(out);
	  }//else
	}//if
	else if(reOutA){
	  int out;
	  if((out = open(outStr.c_str(), O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1){
	    nope_out("open");
	  }//if
	  else{
	    dup2(out, STDOUT_FILENO);
	    close_fd(out);
	  }//else
	}//else if

	vector_exec(processLine[i].args); ////////////////////////////// EXECUTING
	//isJob = true;
      }//else if
      

      if(i == 0){
	//cout << "pid: " << pid << endl;
	if((pgid = getpgid(pid)) == -1){
	  nope_out("getpgid");
	}//if
	else if(pgid != 0){
	  processLine[i].groupID = pid;
	}//else if
	else{
	  setpgid(pid, pid);
	  processLine[i].groupID = pid;
	}//else
	//cout << "pgid = " << pgid << endl;
      }//if
      else{
	setpgid(pid, processLine[0].groupID);
	processLine[i].groupID = processLine[0].groupID;
      }//else

      processLine[i].processID = pid;
 
      //cout << "getting group ID: " << getpgid(pid) << endl;
      //cout << "stored group ID: " << processLine[i].groupID << endl;

      outPipe = !outPipe;
      
      if((startPipe) && (i > 0) && (processLine[i].argCount > 0)){
	close_pipe(pipefd[i - 1]);
      }//if
    }//else

  }//for


  if(!background){
    waitpid(pid, &status, 0);
      if(WIFEXITED(status)){
	jobs[jobCount].status = "Exited";
	//cout << "Exited (" << WEXITSTATUS(status) << ")" << endl;
      }//if
      if(WIFSIGNALED(status)){
	jobs[jobCount].status = "Terminated";
	//cout << "Signaled" << endl;
      }//if        
      if(WIFSTOPPED(status)){
	jobs[jobCount].status = "Stopped";
	//cout << "Stop" << endl;
      }//if
      if(WIFCONTINUED(status)){
	cout << "Continued" << endl;
	//jobs[jobCount].status = "Continued";
      }//if
  }//if
  
}//execute  ///////////////////////////////////////////////////////////////////////////////////////////////////


int main(){
  //set output to unbuffered
  cout.setf(ios::unitbuf);

  //vector<job> jobs;
  jobCount = 0;
  int processCount;

  //infinite loop that reads a line of input from the user
  for(;;){
    startPipe = false;
    outPipe = true;
    background = false;

    //signals
    signal(SIGINT, SIG_IGN);      /////////////////////  UNCOMMENT THIS ////////////////
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    pid_t wpid;
    int status;
  
    while((wpid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0){
      //cout << "change detected" << endl;
      if(WIFEXITED(status)){
	update_status("Exited", wpid);
	print_jobID(wpid);
	cout << "\tExited (" << WEXITSTATUS(status) << ")\t";
	print_jobInput(wpid);
	cout << endl;
	}//if
	if(WIFSIGNALED(status)){
	  update_status("Terminated", wpid);
	  print_jobID(wpid);
	  cout << "\tTerminated\t" << endl;
	}//if
	if(WIFSTOPPED(status)){
	  update_status("Stopped", wpid);
	  print_jobID(wpid);
	  cout << "\tStopped\t" << endl;
	}//if
	if(WIFCONTINUED(status)){
	  update_status("Continued", wpid);
	  print_jobID(wpid);
	  cout << "\tContinued\t" << endl;
	}//if
    }//while


    int pipeCount = 0;
    processCount = 0;

    string errStr;

    reOutT = false;
    reOutA = false;
    isJob = false;

    cin.clear();
    fflush(stdin);

    char prompt[1024];
    getcwd(prompt, 1024);
    bool home = false;
    string checker = "";
    int pos = 0;
    for(int i = 0; prompt[i] != '\0'; i++){
      checker += prompt[i];
      if(checker == getenv("HOME")){
	home = true;
	pos = i + 1;
	break;
      }//if
    }//for
    string print = "";
    for(int i = pos; prompt[i] != '\0'; i++){
      print += prompt[i];
    }//for
    cout << "1730sh:";
    if(home){
      cout << "~";
    }//if
    cout << print << "$ ";


    string input;
    getline(cin, input);    
    string tempInput = input;

    char * temp; 
    temp = strtok(&input[0], " ");

    char * parse[1024];
    int counter = 0;
    while(temp != NULL){
      parse[counter] = temp;
      temp = strtok(NULL, " ");
      counter++;
    }//while

    job myJob;
    jobs.push_back(myJob);

    jobs[jobCount].jobInput = tempInput;   ///////////////////////// jobs builtin

    counter = 0;
    process process1;
    jobs[jobCount].processes.push_back(process1);

    //loops through the parsed input
    while(parse[counter] != NULL){
      string check = parse[counter];

      //marks a new process
      if(check == "|"){
	process process1;
	jobs[jobCount].processes.push_back(process1);
	pipeCount++;
	startPipe = true;
      }//if

      //redirects input
      else if(check == "<"){
	counter++;
	if(parse[counter] != NULL){
	  inStr = parse[counter];
	  reIn = true;
 	}//if
      }//else if

      else if(check == "e>"){ // truncate
	counter++;
	if(parse[counter] != NULL){
	  errStr = parse[counter];
	  
	  int error;
	  if((error = open(parse[counter], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1){
	    nope_out("open");
	  }//if
	  else{
	    dup2(error, STDERR_FILENO);
	    close_fd(error);
	  }//else
	}//if
      }//else if

      //redirects error
      else if(check == "e>>"){ // append
	counter++;
	if(parse[counter] != NULL){
	  errStr = parse[counter];

	  int error;
	  if((error = open(parse[counter], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1){
	    nope_out("open");
	  }//if
	  else{
	    dup2(error, STDERR_FILENO);
	    close_fd(error);
	  }//else
	}//if
      }//else if
      
      //redirects output
      else if(check == ">"){ // truncate
	counter++;
	if(parse[counter] != NULL){
	  
	  reOutT = true;

	  outStr = parse[counter];
	}//if
      }//else if

      //redirects output
      else if(check == ">>"){ // append
	counter++;
	if(parse[counter] != NULL){

	  reOutA = true;

	  outStr = parse[counter];
	}//if
      }//else if

      else if(check == "&"){
	background = true;
	//cout << "background detected" << endl;
      }//else if

      //else the element is a process argument
      else{
	jobs[jobCount].processes[pipeCount].args.push_back(check);
	jobs[jobCount].processes[pipeCount].argCount++;
       
      }//else

      counter++;
    }//while

    processCount = pipeCount + 1;

    //clear out the parse array
    for(int i = 0; i < 1024; i++){
      parse[i] = nullptr;
    }//for

   
    /////////////////////////////////////////////////////////////////////////////
    if(jobs[jobCount].processes[0].argCount != 0){
      execute(jobs[jobCount].processes);
    }//if
    ////////////////////////////////////////////////////////////////////////////

    jobs[jobCount].jobID = jobs[jobCount].processes[0].groupID;
    //cout << "jobID: " << jobs[jobCount].jobID << endl;

    if(processCount == -1);

    if(isJob){
      jobCount++;
    }//if
    else{
      jobs.erase(jobs.begin() + jobCount);
    }//else
  }//for

  return EXIT_SUCCESS;
}//main

/*
This function makes a vector of c strings
 */
vector<char *> make_cstrvector(vector<string> & strvector){
  vector<char *> cstrvector;

  for(unsigned int i = 0; i < strvector.size(); ++i){
    cstrvector.push_back(new char [strvector.at(i).size() + 1]);
    strcpy(cstrvector.at(i), strvector.at(i).c_str());
  }//for

  cstrvector.push_back(nullptr);
  return cstrvector;
}//make_cstrvector

/*
This function deletes created vectors to avoid leaks
 */
void dl_cstrvector(vector<char *> & cstrvector){
  for(unsigned int i = 0; i < cstrvector.size(); ++i){
    delete[] cstrvector.at(i);
  }//for
}//dl_cstrvector

/*
This is a function that converts a vector into an array
that can be passed into exec
 */
void vector_exec(vector<string> argv){
  vector<char *> cargv = make_cstrvector(argv);

  char * temp[1024];
  for(int i = 0; i < 1024; ++i){
    temp[i] = nullptr;
  }//for                                                                                         
  copy(cargv.begin(), cargv.end(), temp);

  execvp(*temp, temp);
  jobs.erase(jobs.begin() + jobCount);
  perror("-1730sh");
  dl_cstrvector(cargv);

  exit(EXIT_FAILURE);
}//vector_exec

/*
This is a function to perform the builtin command help
 */
void builtin_help(){
  cout << "Builtin Commands:" << endl;
  cout << "exit [N] \t\t -Exits the shell with status N" << endl;
  cout << "cd [PATH] \t\t -Changes the current directory to PATH" << endl;
  cout << "help \t\t\t -Displays helpful information about builtin commands" << endl;
  cout << "jobs \t\t\t -Lists current jobs" << endl;
  cout << "export NAME[=WORD] \t -NAME is automatically included in the environment of subsequently executed jobs" << endl;
  cout << "fg JID \t\t\t -Resume job JID in the foreground, and make it the current job" << endl;
  cout << "bg JID \t\t\t -Resume the stopped job JID in the background, as if it had been started with &" << endl;
  //jobs.erase(jobs.begin() + jobCount);
}//builtin_help

/*
This is a function to perform the builtin command exit
 */
void builtin_exit(const string status){
  //jobs.erase(jobs.begin() + jobCount);
  if(status != "\0"){
    stringstream convert;
    int temp;
    convert << status;
    if(convert >> temp){
      exit(temp);
    }//if
    else{
      exit(0);
    }//else
  }//if
  else{
    exit(0);
  }//else

}//builtin_exit

/*
This is a function to execute the builtin command cd
 */
void builtin_cd(const string pname){
  const char * pathname = pname.c_str();
  if(chdir(pathname) != 0){
    perror("chdir");
  }//if
  //jobs.erase(jobs.begin() + jobCount);
}//builtin_cd

/*
  Displays a list of all jobs
 */
void builtin_jobs(){
  if(jobCount > 0){
    cout << "JID\tSTATUS\t\tCOMMAND" << endl;
    for(int i = 0; i < jobCount; i++){
      stringstream convert;
      convert << jobs[i].jobID;
      string print;
      convert >> print;
      print += "\t";
      print += jobs[i].status;
      print += "\t\t";
      print += jobs[i].jobInput;
      cout << print << endl;
    }//for  
  }//if
  //jobs.erase(jobs.begin() + jobCount);
}//void

/*
  Adds a variable to the list of environment variables
  for subsequent jobs
 */
void builtin_export(vector<string> argLine){
  string input = "";
  if(argLine.size() > 1){
    input += argLine[1];
  }//if
  char * temp = new char[input.length() + 1];
  string fake = strdup(input.c_str());
  strcpy(temp, fake.c_str());    //possible mem leak?  
  if(putenv(temp) != 0){
    nope_out("putenv");
  }//if
  delete[] temp;
  //free(fake);
  //jobs.erase(jobs.begin() + jobCount);
}//export

/*
  Resumes a stopped job in the foreground
 */
void builtin_fg(vector<string> argLine){
  pid_t jID;
  if(argLine.size() > 1){
    stringstream convert;
    convert << argLine[1];
    convert >> jID;
  }//if
  int jobHolder;
  for(int i = 0; i < jobCount; i++){
    if(jobs[i].jobID == jID){
      jobHolder = i;
    }//if
  }//for 

  int pos;
  for(unsigned int i = 0; i < jobs[jobHolder].processes.size(); i++){
    if(kill(jobs[jobHolder].processes[i].processID, SIGCONT) == -1){
      nope_out("kill");
    }//if
    pos = i;
  }//for
  int status;

  waitpid(jobs[jobHolder].processes[pos].processID, &status, 0);
  if(WIFEXITED(status)){
    jobs[jobCount].status = "Exited";
    //cout << "Exited (" << WEXITSTATUS(status) << ")" << endl;       
  }//if
  if(WIFSIGNALED(status)){
    jobs[jobCount].status = "Terminated";
    //cout << "Signaled" << endl;       
  }//if
  if(WIFSTOPPED(status)){
    jobs[jobCount].status = "Stopped";
    //cout << "Stop" << endl;       
  }//if
  if(WIFCONTINUED(status)){
    cout << "Continued" << endl;
    //jobs[jobCount].status = "Continued";      
  }//if    
 
}//builtin_fg

/*
  Resumes a stopped job in the background
 */
void builtin_bg(vector<string> argLine){
  pid_t jID;
  if(argLine.size() > 1){
    stringstream convert;
    convert << argLine[1];
    convert >> jID;
  }//if
  int jobHolder;
  for(int i = 0; i < jobCount; i++){
    if(jobs[i].jobID == jID){
      jobHolder = i;
    }//if
  }//for
  for(unsigned int i = 0; i < jobs[jobHolder].processes.size(); i++){
    if(kill(jobs[jobHolder].processes[i].processID, SIGCONT) == -1){
      nope_out("kill");
    }//if
  }//for
  int status;
  pid_t wpid;
  while((wpid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0){
    if(WIFEXITED(status)){
      update_status("Exited", wpid);
      print_jobID(wpid);
      cout << "\tExited (" << WEXITSTATUS(status) << ")\t";
      print_jobInput(wpid);
      cout << endl;
    }//if
    if(WIFSIGNALED(status)){
      update_status("Terminated", wpid);
      print_jobID(wpid);
      cout << "\tTerminated\t" << endl;
    }//if
    if(WIFSTOPPED(status)){
      update_status("Stopped", wpid);
      print_jobID(wpid);
      cout << "\tStopped\t" << endl;
    }//if
    if(WIFCONTINUED(status)){
      update_status("Continued", wpid);
      print_jobID(wpid);
      cout << "\tContinued\t" << endl;
    }//if
  }//while
}//builtin_bg

/*
  Uses perror to display an error then exits the program
 */
void nope_out(const string & sc_name){
  perror(sc_name.c_str());
  exit(EXIT_FAILURE);
}//nope_out

/*
  Attempts to close both ends of a pipe
 */
void close_pipe(int pipefd[2]){
  if(close(pipefd[0]) == -1) nope_out("close");
  if(close(pipefd[1]) == -1) nope_out("close");
}//close_pipe

/*
  Attempts to close a single file descriptor
 */
void close_fd(int fd){
  if(close(fd) == -1){
    nope_out("close");
  }//if
}//close_fd

/*
  Updates the status of a job
 */
void update_status(const string & status, pid_t target){
  for(int i = 0; i < jobCount; i++){
    for(unsigned int j = 0; j < jobs[i].processes.size(); j++){
      if(jobs[i].processes[j].processID == target){
	jobs[i].status = status;
      }//if
    }//for
  }//for
}//update_status

/*
  Prints the ID that was given to a job
 */
void print_jobID(pid_t target){
  for(int i = 0; i < jobCount; i++){
    for(unsigned int j = 0; j < jobs[i].processes.size(); j++){
      if(jobs[i].processes[j].processID == target){
	cout << jobs[i].jobID;
      }//if
    }//for
  }//for
}//print_jobID

/*
  Prints the input that was given for a job
 */
void print_jobInput(pid_t target){
  for(int i = 0; i < jobCount; i++){
    for(unsigned int j = 0; j < jobs[i].processes.size(); j++){
      if(jobs[i].processes[j].processID == target){
	cout << jobs[i].jobInput;
      }//if
    }//for
  }//for
}//print_jobInput

