#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include <fstream>
#include <vector>
#include <cstdio>
#include <string>

// Libraries for using getopt
#include <stdio.h>
#include <unistd.h>

// Local file definitions
#include "polygon3/polygon3.hpp"


int main( void )
{
  Vertex3* v0 = new Vertex3(1);
  Vertex3* v1 = new Vertex3(2,1,2);

  std::cout << *v0 << std::endl;
  std::cout << *v1 << std::endl;

  Edge3* e0 = new Edge3(1, v0, v1);

  std::cout << *e0 << std::endl;


  delete v0;
  delete v1;
  delete e0;

  return 0;
}
