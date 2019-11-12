#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include <fstream>
#include <vector>
#include <cstdio>
#include <string>
#include "polygon2/polygon.hpp"
#include "polygon2/hull.hpp"


/***********************************************************
* Iterate through all lines of a file and put them into 
* a given vector 
***********************************************************/
bool getFileContent(const std::string fileName, 
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
bool getVertexVector(std::vector<std::string> &vecOfStrs,
                     std::vector<Vertex*> &vecOfVerts)
{
  int x,y;
  int iVert = 0;

  // Print vector contents
  for (std::string & line : vecOfStrs) {
    // Convert to integer 
    if (sscanf(line.c_str(), "%d %d", &x, &y) != 2) {
      std::cout << "Can not convert line " << iVert 
        << std::endl;
      std::cout << "Need format x y for every vertex" 
        << std::endl;
      return false;
    }

    // Add vertex to vertex vector
    Vertex* newVert = new Vertex(iVert, x, y);
    vecOfVerts.push_back(newVert);
    
    ++iVert;
  }

  return true;

}



int main(int argc, char *argv[]) 
{
  // Check for arguments
  if (argc < 2)
  {
    std::cout << "\ntriangulate <vertexCoords.vert> \n" << std::endl;
    exit(1);
  }

  // Init string vector, vertex vector and filename
  std::vector<std::string> vecOfStrs;
  std::vector<Vertex*> vecOfVerts; 
  std::string fileName = static_cast<std::string>(argv[1]);

  // Get the contents of input file
  if ( !getFileContent(fileName, vecOfStrs) )
    exit(1);

  if ( !getVertexVector(vecOfStrs, vecOfVerts) )
    exit(1);

  // Reduce vertices to convex hull
  findLowest(vecOfVerts);

  // Initialize polygon
  Polygon* poly = new Polygon();
  for (Vertex* v : vecOfVerts) {
    poly->add_vertex(v);
  }

  std::cout << "Vertices: " << std::endl;
  poly->print_vertices();

  // Triangulate convex hull
  //triangulate( poly );

  return 0;
}
