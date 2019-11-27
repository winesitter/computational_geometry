#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

#include "polygon2/hull.hpp"
#include "polygon2/polygon.hpp"


/***********************************************************
* Reference vertex for sorting 
***********************************************************/
static Vertex* p0 = NULL;

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

/***********************************************************
* Set starting vertex for sorting
***********************************************************/
void setRefVertex(Vertex* pRef)
{
  p0 = pRef;
}

/***********************************************************
* Comparison function for sort of convex hull
***********************************************************/
bool hullCompare(Vertex* pi, Vertex* pj) 
{
  // Implement error if p0 == NULL

  int a = area2(p0, pi, pj);

  if ( a > 0 ) {
    return true;
  }
  else if ( a < 0 ) {
    return false;
  }
  else { // Collinear with p0 

    int x = abs( pi->get_x() - p0->get_x() ) - abs( pj->get_x() - p0->get_x() );
    int y = abs( pi->get_y() - p0->get_y() ) - abs( pj->get_y() - p0->get_y() );

    if ( (x < 0) || (y < 0) ) {
      pi->set_rem(true);
      return true;
    }
    else if ( (x > 0) || (y > 0) ) {
      pj->set_rem(true);
      return false;
    }
    else { // points are coincident 
      if ( pi->get_ind() > pj->get_ind() )
        pj->set_rem(true);
      else
        pi->set_rem(true);


      return true;
    }
  }

  return true;
}


/***********************************************************
* Graham's Scan algorithm
***********************************************************/
Polygon* hullGraham( std::vector<Vertex*> &vertices )
{
  // Reduce vertices to convex hull
  findLowest(vertices);

  // Sort vertices according to angle
  setRefVertex(vertices[0]);
  std::sort(vertices.begin()+1, 
            vertices.end(), 
            hullCompare );

  // Remove vertices that are not needed
  int nVerts = vertices.size();
  for ( int i = nVerts-1; i > 0; --i )
    if ( vertices[i]->get_rem() )
      vertices.erase(vertices.begin() + i);

  // Initialize polygon
  Polygon* hull = new Polygon();
  hull->add_vertex(vertices[0]);
  hull->add_vertex(vertices[1]);

  // Do graham's scan
  int i = 2;
  nVerts = vertices.size();

  while ( i < nVerts ) {
    Vertex* p2 = hull->get_head()->get_prev();
    Vertex* p1 = p2->get_prev();

    if ( isLeft( p1, p2, vertices[i] ) ) {
      hull->add_vertex(vertices[i]);
      i++;
    }
    else 
      hull->rem_vertex(p2);
  }

  return hull;

}
