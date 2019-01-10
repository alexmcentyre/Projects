#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main(){

  char holder [1024];

  getcwd(holder, 1024);

  cout << holder << endl;

  return EXIT_SUCCESS;
}//main
