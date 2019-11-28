#include <iostream>
#include <vector>

#include "polygon3/polygon3.hpp"

/***********************************************************
* Check three vertices for collinearity
***********************************************************/
bool isCollinear3( Vertex3* a, Vertex3* b, Vertex3* c )
{
  return 
    ( c->getZ() - a->getZ() )*( b->getY() - a->getY() )-
    ( b->getZ() - a->getZ() )*( c->getY() - a->getY() )== 0
  &&( b->getZ() - a->getZ() )*( c->getX() - a->getX() )-
    ( b->getX() - a->getX() )*( c->getZ() - a->getZ() )== 0
  &&( b->getX() - a->getX() )*( c->getY() - a->getY() )-
    ( b->getY() - a->getY() )*( c->getX() - a->getX() )== 0;
}


/***********************************************************
* Create double triangle as initial polytope  
*-----------------------------------------------------------
* 1) Find three noncollinear points (v0, v1, v2)
* 2) Create and link the two triangle faces f0 and f1
* 3) Find a fourht point v3, which is not coplanar with
*    (v0, v1, v2)
***********************************************************/
void initDoubleTriangle( std::vector<Vertex3*>& verts )
{
  (void) verts;
  /*
  Vertex3* v0, v1, v2, v3, t;
  Face3*   f0, f1;
  Edge3*   e0, e1, e2, s;
  int      vol;

  // Find three noncolinear points
  v0 = verts[0]; 

  */

  //while ( isCollinear3( v0, v0->next, v0->next->next )


} /* initDoubleTriangle() */
