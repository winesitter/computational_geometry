#include <iostream>
#include <vector>

#include "polygon3/Polygon3.hpp"
#include "polygon3/Vertex3.hpp"

/***********************************************************
* Check three vertices for collinearity
***********************************************************/
bool isCollinear3( Vertex3* a, Vertex3* b, Vertex3* c )
{
  return 
    ( c->z - a->z )*( b->y - a->y )-
    ( b->z - a->z )*( c->y - a->y )== 0
  &&( b->z - a->z )*( c->x - a->x )-
    ( b->x - a->x )*( c->z - a->z )== 0
  &&( b->x - a->x )*( c->y - a->y )-
    ( b->y - a->y )*( c->x - a->x )== 0;
}


/***********************************************************
* Create double triangle as initial polytope  
*-----------------------------------------------------------
* 1) Find three noncollinear points (v0, v1, v2)
* 2) Create and link the two triangle faces f0 and f1
* 3) Find a fourht point v3, which is not coplanar with
*    (v0, v1, v2)
***********************************************************/
void initDoubleTriangle( Vertex3* verts )
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
