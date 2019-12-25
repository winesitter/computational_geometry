#ifndef POLYGON3_FACE3_
#define POLYGON3_FACE3_

#include "polygon3/Polygon3.hpp"
#include "polygon3/Edge3.hpp"
#include "polygon3/Vertex3.hpp"

/***********************************************************
* This class defines the 3D face structure, which is used
* to represent a 3D polygon by means of a circular linked
* list
***********************************************************/
class Face3 {

  private:
    int                     index;      // Face index
    std::array<Edge3*,3>    edges;      // edges of face
    std::array<Vertex3*,3>  vertices;   // vertices of face
    bool                    visible;    // is visible
    Face3*                  next;       // next face
    Face3*                  prev;       // previous face
    Polygon3*               poly;       // Polygon parent

  public:
    /*------------------------------------------------------
    * Constructor
    ------------------------------------------------------*/
    // Create face from vertices
    Face3( Polygon3* poly0, Vertex3 *v0, Vertex3 *v1, Vertex3 *v2 );

    // Create twin face 
    Face3( Polygon3* poly0, Face3 *f0 );

    // Create face from edge and vertex
    Face3( Polygon3* poly0, Edge3 *e0, Vertex3* v0);

    /*------------------------------------------------------
    * Setter functions 
    ------------------------------------------------------*/
    void setInd( int i0 ){ index = i0; }
    void setVert( int i0, Vertex3* v ){ vertices[i0] = v; }
    void setEdge( int i0, Edge3* e ){ edges[i0] = e; }
    void setVisible( bool v ){ visible = v; }
    void setNext( Face3* f ){ next = f; }
    void setPrev( Face3* f ){ prev = f; }

    /*------------------------------------------------------
    * Getter functions 
    ------------------------------------------------------*/
    int       getInd( void ){ return index; }
    Vertex3*  getVert( int i0 ){ return vertices[i0]; }
    Edge3*    getEdge( int i0 ){ return edges[i0]; }
    bool      isVisible( void ){ return visible; }
    Face3*    getNext( void ){ return next; }
    Face3*    getPrev( void ){ return prev; }

    /*------------------------------------------------------
    * Operators redefinition 
    ------------------------------------------------------*/
    friend std::ostream& operator<< (std::ostream& out, 
                                     Face3& f) {
      out << "Face " << f.getInd() << "\n Vertices: V" 
        << f.getVert(0)->getInd() << " -> V" 
        << f.getVert(1)->getInd() << " -> V" 
        << f.getVert(2)->getInd() << "\n Edges: "
        << *f.getEdge(0) << " -> " << *f.getEdge(1)
        << " -> " << *f.getEdge(2);

      return out;
    }

    /*------------------------------------------------------
    * Public functions
    ------------------------------------------------------*/
    int volumeSign( Vertex3* p );

};

#endif
