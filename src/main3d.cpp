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
#include "glut/GlutFramework.hpp"




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
* Arrange vertext structure in terms of a linked list
* and return pointer to head of linked list
***********************************************************/
static Vertex3* initVertexList(std::vector<std::string> &vecOfStrs)
{
  int x,y,z;
  int iVert = 0;
  int nVerts = static_cast<int>(vecOfStrs.size());

  Vertex3* prev = nullptr;
  Vertex3* head = nullptr;

  while (iVert < nVerts)
  {
    // Convert data to integer 
    if (sscanf(vecOfStrs[iVert].c_str(), "%d %d %d", &x, &y, &z) != 3) {
      std::cout << "Can not convert line " << iVert 
        << std::endl;
      std::cout << "Need format x y z for every vertex" 
        << std::endl;
      exit(1);
    }

    // Create new vertex
    Vertex3* next = new Vertex3(iVert, x, y, z);

    // Output for user
    std::cout << "Create new " << *next << std::endl;

    // Initialize head of list
    if (prev == nullptr)
      head = next;
    // create links for list
    else {
      prev->setNext(next);
      next->setPrev(prev);
    }

    // store last vertex
    prev = next;
    ++iVert;
  }

  // close circular doubly linked list of vertices
  head->setPrev(prev);
  prev->setNext(head);

  return head;

} /* initVertexList() */

/***********************************************************
* Free data behind of the doubly linked vertex list
***********************************************************/
static void freeVertexList(Vertex3* head)
{
  Vertex3* cur  = head->getNext();
  Vertex3* next = cur->getNext();
  do {
    delete cur;
    cur = next;
    next = cur->getNext();
  } while( cur != head);

  delete cur;

} /* freeVertexList() */


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

  // Read vertex data from text file and store in list
  Vertex3* vHead = initVertexList(vecOfStrs);

  // Initialzize hull
  initDoubleTriangle(vHead);

  // free vertex data
  freeVertexList(vHead);

  // Render data
  glutFramework::GlutFrameworkTri framework;
  framework.setLookAt(0.0, 2.0, 10.0, 
                      0.0, 2.0, 0.0, 
                      0.0, 1.0, 0.0);
  framework.startFramework(argc, argv);
  // No code below startFramework() will get executed

  return 0;
}
