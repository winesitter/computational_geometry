#include <iostream>
#include <vector>
#include "polygon3/Face3.hpp"
#include "polygon3/Edge3.hpp"

// Global face counter
int NFACES = 0;


/*----------------------------------------------------------
| Constructor definitions 
----------------------------------------------------------*/
// Create empty face 
Face3::Face3() {
  // Set face index
  index = NFACES++;

  for (int j = 0; j < 2; ++j) {
    edges[j]    = nullptr;
    vertices[j] = nullptr;
  }
  visible = false;
  next = prev = nullptr;
}

// Create face from vertices
Face3::Face3( Vertex3 *v0, Vertex3* v1, Vertex3 *v2) {
  // Set face index
  index = NFACES++;

  // Create edges of initial triangle
  edges[0] = new Edge3( v0, v1 ); 
  edges[1] = new Edge3( v1, v2 );
  edges[2] = new Edge3( v2, v0 );

  edges[0]->setFace(0, this);
  edges[1]->setFace(0, this);
  edges[2]->setFace(0, this);

  vertices[0] = v0, vertices[1] = v1, vertices[2] = v2;
  
}

// Create twin face 
Face3::Face3( Face3 *f0 ){
  // Set face index
  index = NFACES++;

  vertices[0] = f0->getVert(2);
  vertices[1] = f0->getVert(1);
  vertices[2] = f0->getVert(0);
  
  edges[0] = f0->getEdge(1);
  edges[1] = f0->getEdge(0);
  edges[2] = f0->getEdge(2);

  edges[0]->setFace(1, this);
  edges[1]->setFace(1, this);
  edges[2]->setFace(1, this);
}


/*----------------------------------------------------------
| Public functions
----------------------------------------------------------*/
int Face3::volumeSign( Vertex3* p ) {
  Vertex3 a = *this->getVert(0) - *p;
  Vertex3 b = *this->getVert(1) - *p;
  Vertex3 c = *this->getVert(2) - *p;

  double vol = a.x * ( b.y * c.z - b.z * c.y )
             + a.y * ( b.z * c.x - b.x * c.z )
             + a.z * ( b.x * c.y - b.y * c.x );

  if      ( vol > 0.5 )   return  1; 
  else if ( vol <-0.5 )   return -1;
  else                    return  0;



}
