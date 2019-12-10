#ifndef POLYGON3_VERTEX3_
#define POLYGON3_VERTEX3_

#include "polygon3/Polygon3.hpp"

/***********************************************************
* This class defines the 3D vertex structure, which is used
* to represent a 3D polygon by means of a circular linked
* list
***********************************************************/
class Vertex3 {

  private:
    int      index;     // Vertex index in list
    bool     onHull;    // True iff on convex hull
    bool     mark;      // True iff already processed

    Edge3*   duplicate; // Pointe to incident cone edge 
    Vertex3* next;
    Vertex3* prev;

  public:
    int      x,y,z;     // Coordinates


  public:
    /*------------------------------------------------------
    | Constructor
    ------------------------------------------------------*/
    Vertex3( int i = -1, int x = 0, int y = 0, int z = 0) 
            : index(i), x(x), y(y), z(z) 
    {
      onHull        = false;
      mark          = false;
      duplicate     = nullptr;
      next  = prev  = nullptr;
    }

    /*------------------------------------------------------
    | Setter functions 
    ------------------------------------------------------*/
    void setI( int i0 ){ index = i0; }
    void setMark( bool doMark ){ mark = doMark; }
    void setOnHull( bool isOn ){ onHull = isOn; }
    void setDuplicate( Edge3* e){ duplicate = e; }
    void setNext( Vertex3* v ){ next = v; }
    void setPrev( Vertex3* v ){ prev = v; }

    /*------------------------------------------------------
    | Getter functions 
    ------------------------------------------------------*/
    int       getInd( void ){ return index; }
    bool      getMark( void ){ return mark; }
    bool      getOnHull( void ){ return onHull; }
    Edge3*    getDuplicate( void ){ return duplicate; }
    Vertex3*  getNext( void ){ return next; }
    Vertex3*  getPrev( void ){ return prev; }

    /*------------------------------------------------------
    | Operators redefinition 
    ------------------------------------------------------*/
    // Vertex addition
    Vertex3 operator+( const Vertex3 &other) const;
    // Vertex subtraction
    Vertex3 operator-( const Vertex3 &other) const;
    // Vertex stream output
    friend std::ostream& operator<<(std::ostream& out,   
                                    Vertex3& v) {
      out << "Vertex " << v.getInd() << ": ( " << v.x 
      << ", " << v.y << ", " << v.z << " )"; 
      return out;
    }

    /*------------------------------------------------------
    | Public functions
    ------------------------------------------------------*/

    /*********************************************************
    * Check this vertex for collinearity with two 
    * other vertices
    *
    * @param Vertex3* b, Vertex3* c - Vertices to check for 
    *   collinearity
    * @return true if collinear, false if not
    *********************************************************/
    bool isCollinear( const Vertex3 &b, 
                      const Vertex3 &c ) const;

};

#endif
