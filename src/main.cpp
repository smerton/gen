// A simple mesh generator for DG problem input

// Author S. R. Merton

#include <iostream>
#include "input.h"

using namespace std;


// main function starts here

int main(){

  cout<<"main(): Starting up main loop..."<<endl;

// initialise a new input from file

  Input I((char*)"input.gen");

  cout<<"Normal termination."<<endl;

  return 0;
}
