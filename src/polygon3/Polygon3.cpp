#include <iostream>
#include <vector>

#include "polygon3/Polygon3.hpp"
#include "polygon3/Vertex3.hpp"
#include "polygon3/Face3.hpp"
#include "polygon3/Edge3.hpp"

/***********************************************************
* Create double triangle as initial polytope  
*-----------------------------------------------------------
* 1) Find three noncollinear points (v0, v1, v2)
* 2) Create and link the two triangle faces f0 and f1
* 3) Find a fourht point v3, which is not coplanar with
*    (v0, v1, v2)
***********************************************************/
void initDoubleTriangle( Vertex3* vertices )
{
  //Vertex3* v0, v1, v2; //, v3, t;
  //Face3*   f0, f1;
  //Edge3*   e0, e1, e2, s;
  //int      vol;

  // Find three noncolinear points
  Vertex3* v0 = vertices;
  while ( v0->isCollinear( *v0->getNext(), *v0->getNext()->getNext() ) ) 
    if ( ( v0 = v0->getNext() ) == vertices ) {
      std::cout << "[ERROR] initDoubleTriangle: All points are collinear!" << std::endl;
      exit(0);
    }

  Vertex3* v1 = v0->getNext();
  Vertex3* v2 = v1->getNext();

  // Mark these vertices as processed
  v0->setMark(true);
  v1->setMark(true);
  v2->setMark(true);

  // Create two twin faces
  Face3* f0 = new Face3(v0, v1, v2);
  Face3* f1 = new Face3(f0);

  std::cout << *f0 << std::endl;
  std::cout << *f1 << std::endl;

  // Find fourth, noncoplanar point to form tetrahedron
  Vertex3* v3 = v2->getNext();

  int vol = f0->volumeSign( v3 );

  while ( !vol ) {
    if ( ( v3 = v3->getNext() ) == v0 ) {
      std::cout << "[ERROR] initDoubleTriangle(): All points are coplanar!" << std::endl;
      exit(0);
    }
    vol = f0->volumeSign( v3 );
  }

  // Insure that v3 will be the first added
  vertices = v3;

  std::cout << *v0 << std::endl;
  std::cout << *v1 << std::endl;
  std::cout << *v2 << std::endl;
  std::cout << *v3 << std::endl;

} /* initDoubleTriangle() */
