#include <iostream>
#include <algorithm>

#include "polygon2/hull.hpp"
#include "polygon2/polygon.hpp"

/***********************************************************
* This function finds the rightmost lowest point in the set
* and swaps it to the front
***********************************************************/
void findLowest( std::vector<Vertex*> &vertices ) 
{
  int m = 0;
  int nVerts = vertices.size();

  for ( int i = 1; i < nVerts; ++i ) {
    if ( (vertices[i]->get_y()  < vertices[m]->get_y()) ||
       ( (vertices[i]->get_y() == vertices[m]->get_y()) &&
         (vertices[i]->get_x()  > vertices[m]->get_x())) )
       m = i;
  }

  // Swap vertices
  std::swap(vertices[0], vertices[m]);

}

