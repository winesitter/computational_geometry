#include <iostream>
#include <vector>
#include "polygon3/Face3.hpp"
#include "polygon3/Edge3.hpp"
#include "polygon3/Polygon3.hpp"

/*----------------------------------------------------------
| Constructor definitions 
----------------------------------------------------------*/

/*----------------------------------------------------------
| Edge Constructor with vertices
| @param ind - edge index in list
| @param v0, v1 - vertices defining edge
| @param poly - edge polygon parent
----------------------------------------------------------*/
Edge3::Edge3( Polygon3* poly0, Vertex3 *v0, Vertex3 *v1 )
{
  // Set polygon parent
  poly = poly0;

  // set index
  index = poly->incNEdges();

  // set vertices
  vertices[0] = v0;
  vertices[1] = v1;

  // Init edge structure
  for (int j = 0; j < 2; ++j)
    adjfaces[j] = nullptr;

  remove      = false;
  newFace     = nullptr;

  // Set neighbor edges in list of polygon
  Edge3* e0 = poly->getEdgeHead();
  if ( e0 == nullptr ) {
    prev = this;
    next = this;
    poly->setEdgeHead( this );
  } else { 
    next = e0->getNext();
    prev = e0;
    prev->setNext(this);
    next->setPrev(this);
  }

}
