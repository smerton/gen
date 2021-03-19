// A simple mesh generator for DG problem input

// Author S. R. Merton

#include <iostream>
#include "input.h"

void Output(char*s,Input*I);

using namespace std;

// main function starts here

int main(){

  cout<<"main(): Starting up main loop..."<<endl;

// initialise a new input from file

  Input I((char*)"input.gen");

// write the mesh file

  Output((char*) "input.mesh",&I);

  cout<<"Normal termination."<<endl;

  return 0;
}
