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


/***********************************************************
* Iterate through all lines of a file and put them into 
* a given vector 
***********************************************************/
static bool getFileContent(const std::string fileName, 
                           std::vector<std::string> & vecOfStrs)
{
  // Open the file
  std::ifstream in(fileName.c_str());

  if(!in) {
    std::cerr << "Cannot open the file : " 
      << fileName << std::endl;
    return false;
  }

  std::string str;

  // Read the next line from the file until it reaches end
  while ( std::getline(in, str) ) {
    // Line contains string of length > 0 then save it 
    if ( str.size() > 0 )
      vecOfStrs.push_back(str);
  }

  // close the file
  in.close();
  return true;
}


/***********************************************************
* Create vector of vertices from input data 
***********************************************************/
static bool getVertexVector(std::vector<std::string> &vecOfStrs,
                            std::vector<Vertex3*> &vecOfVerts)
{
  int x,y,z;
  int iVert = 0;

  // Print vector contents
  for (std::string & line : vecOfStrs) {
    // Convert to integer 
    if (sscanf(line.c_str(), "%d %d %d", &x, &y, &z) != 3) {
      std::cout << "Can not convert line " << iVert 
        << std::endl;
      std::cout << "Need format x y z for every vertex" 
        << std::endl;
      return false;
    }

    // Add vertex to vertex vector
    Vertex3* newVert = new Vertex3(iVert, x, y, z);
    vecOfVerts.push_back(newVert);
    
    ++iVert;
  }

  return true;

}

/***********************************************************
* Arrange vertext structure in terms of a linked list
* and return pointer to head of linked list
***********************************************************/
static Vertex3* initVertices(std::vector<std::string> &vecOfStrs)
{
  int x,y,z;
  int iVert = 0;

  Vertex3* vertices;

  // Print vector contents
  for (std::string & line : vecOfStrs) {

    // Convert to integer 
    if (sscanf(line.c_str(), "%d %d %d", &x, &y, &z) != 3) {
      std::cout << "Can not convert line " << iVert 
        << std::endl;
      std::cout << "Need format x y z for every vertex" 
        << std::endl;
      return false;
    }

    // Add vertex to vertex vector
    Vertex3* newVert = new Vertex3(iVert, x, y, z);

  }

  return vertices;

} /* initVertices() *>7


int main( int argc, char *argv[] )
{
  // Check for arguments
  if (argc < 2)
  {
    std::cout << "Need vertex file!" << std::endl;
    exit(1);
  }

  // Get name of vertex file
  std::string vertexFile = argv[1];

  // Init string vector, vertex vector and filename
  std::vector<std::string> vecOfStrs;
  std::vector<Vertex3*> vecOfVerts; 
  std::string fileName = static_cast<std::string>(vertexFile);

  // Get the contents of input file
  if ( !getFileContent(fileName, vecOfStrs) )
    exit(1);

  // Create vector of all vertices
  if ( !getVertexVector(vecOfStrs, vecOfVerts) )
    exit(1);

  // Process vertex data
  for (Vertex3* v : vecOfVerts) {
    std::cout << *v << std::endl;
  }
  initDoubleTriangle(vecOfVerts);

  // free data
  for (Vertex3* v : vecOfVerts) 
    delete v;



  return 0;
}
