
#include "Matrix.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main(){

  Matrix p({{1,2},{2,3}});
  Matrix q = p.add(p);
  Matrix r = p + p;


  cout << q << endl;
  cout << r << endl;
  return EXIT_SUCCESS;
}//main
