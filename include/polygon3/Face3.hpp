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
    int                     i;          // Face index
    std::array<Edge3*,3>    edges;      // edges of face
    std::array<Vertex3*,3>  vertices;   // vertices of face
    bool                    visible;    // is visible
    Face3*                  next;       // next face
    Face3*                  prev;       // previous face

  public:
    /*------------------------------------------------------
    * Constructor
    ------------------------------------------------------*/
    Face3( int i = -1 ) : i(i)
    {
      for (int j = 0; j < 2; ++j) {
        edges[j]    = nullptr;
        vertices[j] = nullptr;
      }
      visible = false;
      next = prev = nullptr;
    }

    /*------------------------------------------------------
    * Setter functions 
    ------------------------------------------------------*/
    void setI( int i0 ){ i = i0; }
    void setVert( int i0, Vertex3* v ){ vertices[i0] = v; }
    void setEdge( int i0, Edge3* e ){ edges[i0] = e; }
    void setVisible( bool v ){ visible = v; }
    void setNext( Face3* f ){ next = f; }
    void setPrev( Face3* f ){ prev = f; }

    /*------------------------------------------------------
    * Getter functions 
    ------------------------------------------------------*/
    int       getI( void ){ return i; }
    Vertex3*  getVert( int i0 ){ return vertices[i0]; }
    Edge3*    getEdge( int i0 ){ return edges[i0]; }
    bool      getVisible( void ){ return visible; }
    Face3*    getNext( void ){ return next; }
    Face3*    getPrev( void ){ return prev; }

    /*------------------------------------------------------
    * Operators redefinition 
    ------------------------------------------------------*/
    friend std::ostream& operator<< (std::ostream& out, 
                                     Face3& f) {
      out << "Face " << f.getI() << ": V" 
        << f.getVert(0)->getI() << " -> V" 
        << f.getVert(1)->getI() << " -> V" 
        << f.getVert(2)->getI();
      return out;
    }

};

#endif
