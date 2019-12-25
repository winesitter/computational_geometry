#include <iostream>
#include <vector>
#include "polygon3/Face3.hpp"
#include "polygon3/Edge3.hpp"


/*----------------------------------------------------------
| Constructor definitions 
----------------------------------------------------------*/

/*----------------------------------------------------------
| Face Constructor
| @param poly - Polygon parent
| @param v0, v1, v2 - vertices defining the face
----------------------------------------------------------*/
Face3::Face3( Polygon3* poly0,
              Vertex3* v0, Vertex3* v1, Vertex3* v2 )
{

  // Set polygon parent
  poly = poly0;

  // Set face index
  index = poly->incNFaces();

  // Set face properties
  visible = false;

  // Set neighbor face in list
  Face3* f0 = poly->getFaceHead();
  if ( f0 == nullptr ) { 
    prev = this;
    next = this;
    poly->setFaceHead( this );
  } else {
    next = f0->getNext();
    prev = f0;
    prev->setNext(this);
    next->setPrev(this);
  }

  // Set vertices
  vertices[0] = v0, vertices[1] = v1, vertices[2] = v2;

  // Create edges of initial triangle
  edges[0] = new Edge3( poly, v0, v1 ); 
  edges[1] = new Edge3( poly, v1, v2 );
  edges[2] = new Edge3( poly, v2, v0 );

  // Set face adjacent to edges
  edges[0]->setAdjFace(0, this);
  edges[1]->setAdjFace(0, this);
  edges[2]->setAdjFace(0, this);
  
}

/*----------------------------------------------------------
| Face Constructor 
| @param poly - Polygon parent
| @param f0 - head of face list
----------------------------------------------------------*/
Face3::Face3( Polygon3* poly0, Face3 *f0 )
{
  // Set polygon parent
  poly = poly0;

  // Set face index
  index = poly->incNFaces();
  
  // Set face properties
  visible = false;

  // Set neighbor face in list
  Face3* fHead = poly->getFaceHead();
  if ( fHead == nullptr ) { 
    prev = this;
    next = this;
    poly->setFaceHead( this );
  } else {
    next = fHead->getNext();
    prev = fHead;
    prev->setNext(this);
    next->setPrev(this);
  }

  // Set vertices
  vertices[0] = f0->getVert(2);
  vertices[1] = f0->getVert(1);
  vertices[2] = f0->getVert(0);
  
  // Set edges
  edges[0] = f0->getEdge(1);
  edges[1] = f0->getEdge(0);
  edges[2] = f0->getEdge(2);

  // Set face adjacent to edges
  edges[0]->setAdjFace(1, this);
  edges[1]->setAdjFace(1, this);
  edges[2]->setAdjFace(1, this);
}

/*----------------------------------------------------------
| Face Constructor 
| -> Create face from edge and vertex
| @param poly - Polygon parent
| @param f0 - head of face list
----------------------------------------------------------*/
Face3::Face3( Polygon3* poly0, Edge3* e0, Vertex3* v0)
{

  // Set polygon parent
  poly = poly0;

  // Set face index
  index = poly->incNFaces();

  // Set face properties
  visible = false;

  // Set neighbor face in list
  Face3* fHead = poly->getFaceHead();
  if ( fHead == nullptr ) { 
    prev = this;
    next = this;
    poly->setFaceHead( this );
  } else {
    next = fHead->getNext();
    prev = fHead;
    prev->setNext(this);
    next->setPrev(this);
  }

  // First edge of new face is presceding edge
  edges[0] = e0;

  // Make two new edges if they don't already exist
  for (int i = 0; i < 2; ++i ) {
    // Copy new edge from duplicate 
    edges[i+1] = e0->getVert(i)->getDuplicate();

    // if no duplicate exists, create new edge
    if ( edges[i+1] == nullptr ) {
      edges[i+1] = new Edge3(poly, e0->getVert(i), v0);
      e0->getVert(i)->setDuplicate( edges[i+1] );
    }
  }


  // Arange vertices to make face CCW
  Face3* faceVis;
  
  if ( e0->getAdjFace(0)->isVisible() )
    faceVis = e0->getAdjFace(0);
  else
    faceVis = e0->getAdjFace(1);

  // Set vertices[0] & [1] of current face to have the 
  // same orientation as do the corresponding vertices 
  // of faceVis
  int i;
  for (i = 0; faceVis->getVert(i) != e0->getVert(0); ++i)
    ;

  // Orient face the same as faceVis
  if ( faceVis->getVert( (i+1) % 3 ) != e0->getVert(1) ) {
    vertices[0] = e0->getVert(1);
    vertices[1] = e0->getVert(0);
  } else {
    vertices[0] = e0->getVert(0);
    vertices[1] = e0->getVert(1);
    Edge3* tmp = edges[1];
    edges[1] = edges[2];
    edges[2] = tmp;
  }
  vertices[2] = v0;
 

  // Set adjacent face pointers for edges
  for ( int i = 0; i < 2; i++ ) {
    for ( int j = 0; j < 2; j++ ) {
      // Only one nullptr link should be set to new face
      if ( edges[i+1]->getAdjFace(j) == nullptr ) {
        edges[i+1]->setAdjFace(j, this);
        break;
      }
    }
  }

}

/*----------------------------------------------------------
| Public functions
----------------------------------------------------------*/
int Face3::volumeSign( Vertex3* p ) 
{
  Vertex3 a = *this->getVert(0) - *p;
  Vertex3 b = *this->getVert(1) - *p;
  Vertex3 c = *this->getVert(2) - *p;

  double ax, ay, az, bx, by, bz, cx, cy, cz;
  double vol;

  ax = static_cast<double>(a.x); 
  ay = static_cast<double>(a.y); 
  az = static_cast<double>(a.z); 

  bx = static_cast<double>(b.x); 
  by = static_cast<double>(b.y); 
  bz = static_cast<double>(b.z); 

  cx = static_cast<double>(c.x); 
  cy = static_cast<double>(c.y); 
  cz = static_cast<double>(c.z); 

  vol = ax * ( by * cz - bz * cy )
      + ay * ( bz * cx - bx * cz )
      + az * ( bx * cy - by * cx );

  if      ( vol > 0.5 )   return  1; 
  else if ( vol <-0.5 )   return -1;
  else                    return  0;



}
