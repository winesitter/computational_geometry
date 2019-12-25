#include <iostream>
#include <vector>

#include "polygon3/Polygon3.hpp"
#include "polygon3/Vertex3.hpp"
#include "polygon3/Face3.hpp"
#include "polygon3/Edge3.hpp"


/*----------------------------------------------------------
| Constructor definitions 
----------------------------------------------------------*/
Polygon3::Polygon3( Vertex3* vertices ) 
{
  nFaces = 0;
  nEdges = 0;
  nVertices = 0;

  // Set head of vertex list
  vHead = vertices;

  // init head of face and edge list
  fHead = nullptr;
  eHead = nullptr;

  // Create and set head for face list
  this->initDoubleTriangle();

  // Create convex hull
  std::cout << "\n\n C O N S T R U C T I N G    C O N V E X    H U L L \n\n" << std::endl;
  this->constructHull();

  std::cout << "=============\nFACE LIST\n=============" << std::endl;
  Face3* curFace = fHead;
  do {
    std::cout << *curFace << std::endl;
    curFace = curFace->getNext();
  } while ( curFace != fHead );

  std::cout << "=============\nEDGE LIST\n=============" << std::endl;
  Edge3* curEdge = eHead;
  do {
    std::cout << *curEdge << std::endl;
    curEdge = curEdge->getNext();
  } while ( curEdge != eHead );

  std::cout << "=============\nVERT LIST\n=============" << std::endl;
  Vertex3* curVert = vHead;
  do {
    std::cout << *curVert << std::endl;
    curVert = curVert->getNext();
  } while ( curVert != vHead );



}



/***********************************************************
* Create double triangle as initial polytope  
*-----------------------------------------------------------
* 1) Find three noncollinear points (v0, v1, v2)
* 2) Create and link the two triangle faces f0 and f1
* 3) Find a fourht point v3, which is not coplanar with
*    (v0, v1, v2)
***********************************************************/
void Polygon3::initDoubleTriangle( void )
{
  // Find three noncolinear points
  Vertex3* v0 = this->vHead;
  while ( v0->isCollinear( *v0->getNext(), *v0->getNext()->getNext() ) ) 
    if ( ( v0 = v0->getNext() ) == this->vHead ) {
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
  Face3* f0 = new Face3(this, v0, v1, v2);
  Face3* f1 = new Face3(this, f0);
  (void) f1;

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
  this->vHead = v3;

} /* initDoubleTriangle() */

/***********************************************************
* Add new vertex to the current hull structure
*-----------------------------------------------------------
*
* 
***********************************************************/
bool Polygon3::addVertexToHull( Vertex3* p )
{
  Face3* f = fHead;
  bool isVisible = false;

  // Mark all faces that are visible from new vertex v
  do {
    if ( f->volumeSign( p ) < 0 ) {
      f->setVisible( true );
      isVisible = true;
    }
    f = f->getNext();
  } while( f != fHead );

  // If no faces are visible from p, the p is inside hull
  if ( !isVisible ) {
    p->setOnHull(false);
    return false;
  }

  // Mark edges in interior of visible region for deletion
  // Errect a newface based on each border edge
  Edge3* e = eHead;
  do {
    Edge3* eTmp = e->getNext();

    // edge is interior: mark for deletion
    if (  e->getAdjFace(0)->isVisible() 
       && e->getAdjFace(1)->isVisible() ) {
      e->setRemove(true);

    // edge is on boundary: make a new face
    } else if (  e->getAdjFace(0)->isVisible() 
              || e->getAdjFace(1)->isVisible() ) {
      Face3* newFace = new Face3(this, e, p);
      e->setNewFace(newFace);
    }

    e = eTmp;

  } while ( e != eHead );

  return true;

}

/***********************************************************
* Create double triangle as initial polytope  
*-----------------------------------------------------------
*
* 
***********************************************************/
void Polygon3::constructHull( void ) 
{
  Vertex3* v = this->vHead;
  Vertex3* vnext = nullptr;

  do {
    vnext = v->getNext();
    if ( !v->getMark() ) {
      v->setMark( true );
      this->addVertexToHull( v );
      this->cleanHullEdges(); 
      this->cleanHullFaces(); 
      this->cleanHullVertices(); 
    }
    v = vnext;
  } while ( v != this->vHead );

}

/***********************************************************
* Clean faces which were created in the hull
* construction process of the polygon
*-----------------------------------------------------------
* 
***********************************************************/
void Polygon3::cleanHullFaces( void )
{
  Face3* curFace;
  while ( this->fHead && this->fHead->isVisible() ) {
    curFace = this->fHead;
    this->fHead = curFace->getNext();
    curFace->getNext()->setPrev(curFace->getPrev());
    curFace->getPrev()->setNext(curFace->getNext());
    delete curFace;
  }

  curFace = this->fHead->getNext();
  do {
    if ( curFace->isVisible() ) {
      Face3* tmpFace = curFace;
      curFace = curFace->getNext();
      tmpFace->getNext()->setPrev(tmpFace->getPrev());
      tmpFace->getPrev()->setNext(tmpFace->getNext());
      delete tmpFace;
    }
    else 
      curFace = curFace->getNext();
  } while ( curFace != this->fHead );


}

/***********************************************************
* Clean edges which were created in the hull
* construction process of the polygon
*-----------------------------------------------------------
* 
***********************************************************/
void Polygon3::cleanHullEdges( void )
{
  Edge3* curEdge;

  // Integrate the new_face into data structure
  curEdge = this->eHead;
  do {
    if ( curEdge->getNewFace() != nullptr ) {
      if ( curEdge->getAdjFace(0)->isVisible() )
        curEdge->setAdjFace(0, curEdge->getNewFace());
      else 
        curEdge->setAdjFace(1, curEdge->getNewFace());
      curEdge->setNewFace(nullptr);
    }
    curEdge = curEdge->getNext();
  } while( curEdge != this->eHead );

  // Delete any edges marked for deletion
  while ( this->eHead && this->eHead->getRemove() ) {
    curEdge = this->eHead;
    this->eHead = curEdge->getNext();
    curEdge->getNext()->setPrev(curEdge->getPrev());
    curEdge->getPrev()->setNext(curEdge->getNext());
    delete curEdge;
  }

  curEdge = this->eHead->getNext();
  do {
    if ( curEdge->getRemove() ) {
      Edge3* tmpEdge = curEdge;
      curEdge = curEdge->getNext();
      tmpEdge->getNext()->setPrev(tmpEdge->getPrev());
      tmpEdge->getPrev()->setNext(tmpEdge->getNext());
      delete tmpEdge;
    }
    else
      curEdge = curEdge->getNext();
  } while ( curEdge != this->eHead );

}

/***********************************************************
* Clean vertices which were created in the hull
* construction process of the polygon
*-----------------------------------------------------------
* 
***********************************************************/
void Polygon3::cleanHullVertices( void )
{
  // Mark all vertices incident to som undeleted edge as 
  // on the hull
  Edge3* curEdge = this->eHead;
  do {
    curEdge->getVert(0)->setOnHull(true);
    curEdge->getVert(1)->setOnHull(true);
    curEdge = curEdge->getNext();
  } while ( curEdge != this->eHead );

  // Delete all vertices that have been processed but are
  // not on the hull
  Vertex3* curVert;
  while (  this->vHead 
        && this->vHead->getMark() 
        && !this->vHead->getOnHull() ) {
    curVert = this->vHead;
    this->vHead = curVert->getNext();
    curVert->getNext()->setPrev(curVert->getPrev());
    curVert->getPrev()->setNext(curVert->getNext());
    delete curVert;
  }

  curVert = this->vHead->getNext();
  do {
    if ( curVert->getMark() && !curVert->getOnHull() ) {
      Vertex3* tmpVert = curVert;
      curVert = curVert->getNext();
      tmpVert->getNext()->setPrev(tmpVert->getPrev());
      tmpVert->getPrev()->setNext(tmpVert->getNext());
      delete tmpVert;
    }
    else 
      curVert = curVert->getNext();
  } while ( curVert != this->vHead );

  // Reset flags
  curVert = this->vHead;
  do {
    curVert->setDuplicate(nullptr);
    curVert->setOnHull(false);
    curVert = curVert->getNext();
  } while( curVert != this->vHead );

}
