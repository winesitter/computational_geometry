#ifndef POLYGON3_EDGE_
#define POLYGON3_EDGE_

#include "polygon3/Polygon3.hpp"
#include "polygon3/Vertex3.hpp"

/***********************************************************
* This class defines the 3D edge structure, which is used
* to represent a 3D polygon by means of a circular linked
* list
***********************************************************/
class Edge3 {

  private:
    int                     index;       // edge index
    std::array<Vertex3*,2>  vertices;    // edge vertices
    std::array<Face3*,2>    adjfaces;    // adjacent faces
    Face3*                  newFace;     // Pointer to incident new face
    bool                    remove;      // Remove edge
    Edge3*                  next;        // next edge
    Edge3*                  prev;        // previous edge
    Polygon3*               poly;        // Polygon parent

  public:
    /*------------------------------------------------------
    * Constructor
    ------------------------------------------------------*/
    // Create edge from vertices
    Edge3( Polygon3* poly, Vertex3 *v0, Vertex3 *v1 );

    /*------------------------------------------------------
    * Setter functions 
    ------------------------------------------------------*/
    void setInd( int i0 ){ index = i0; }
    void setVert( int i0, Vertex3* v ){ vertices[i0] = v; }
    void setAdjFace( int i0, Face3* f ){ adjfaces[i0] = f; }
    void setNewFace( Face3* f ){ newFace = f; }
    void setRemove( bool t ){ remove = t; }
    void setNext( Edge3* e ){ next = e; }
    void setPrev( Edge3* e ){ prev = e; }

    /*------------------------------------------------------
    * Getter functions 
    ------------------------------------------------------*/
    int       getInd( void ){ return index; }
    Vertex3*  getVert( int i0 ){ return vertices[i0]; }
    Face3*    getAdjFace( int i0 ){ return adjfaces[i0]; }
    Face3*    getNewFace( void ){ return newFace; }
    bool      getRemove( void ){ return remove; }
    Edge3*    getNext( void ){ return next; }
    Edge3*    getPrev( void ){ return prev; }

    /*------------------------------------------------------
    * Operators redefinition 
    ------------------------------------------------------*/
    friend std::ostream& operator<< (std::ostream& out, 
                                     Edge3& e) {
      out << "Edge " << e.getInd() << ": V" 
        << e.getVert(0)->getInd() << " -> V" 
        << e.getVert(1)->getInd();
      return out;
}

};


#endif
