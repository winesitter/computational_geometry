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
    int      i;         // Vertex index in list
    bool     onHull;    // True iff on convex hull
    bool     mark;      // True iff already processed

    Edge3*   duplicate; // Pointe to incident cone edge 
    Vertex3* next;
    Vertex3* prev;

  public:
    int      x,y,z;     // Coordinates


  public:
    /*------------------------------------------------------
    * Constructor
    ------------------------------------------------------*/
    Vertex3( int i = -1, int x = 0, int y = 0, int z = 0) 
            : i(i), x(x), y(y), z(z) 
    {
      onHull        = false;
      mark          = false;
      duplicate     = nullptr;
      next  = prev  = nullptr;
    }

    /*------------------------------------------------------
    * Setter functions 
    ------------------------------------------------------*/
    void setI( int i0 ){ i = i0; }
    void setMark( bool doMark ){ mark = doMark; }
    void setOnHull( bool isOn ){ onHull = isOn; }
    void setDuplicate( Edge3* e){ duplicate = e; }
    void setNext( Vertex3* v ){ next = v; }
    void setPrev( Vertex3* v ){ prev = v; }

    /*------------------------------------------------------
    * Getter functions 
    ------------------------------------------------------*/
    int       getI( void ){ return i; }
    bool      getMark( void ){ return mark; }
    bool      getOnHull( void ){ return onHull; }
    Edge3*    getDuplicate( void ){ return duplicate; }
    Vertex3*  getNext( void ){ return next; }
    Vertex3*  getPrev( void ){ return prev; }

    /*------------------------------------------------------
    * Operators redefinition 
    ------------------------------------------------------*/
    friend std::ostream& operator<<(std::ostream& out,   
                                    Vertex3& v) {
      out << "Vertex " << v.getI() << ": ( " << v.x 
      << ", " << v.y << ", " << v.z << " )"; 
      return out;
}

};

#endif
