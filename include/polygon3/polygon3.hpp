#ifndef POLYGON3_POLYGON_
#define POLYGON3_POLYGON_

#include <iostream>
#include <vector>

/***********************************************************
* This class defines the 3D vertex structure, which is used
* to represent a 3D polygon by means of a circular linked
* list
***********************************************************/
class Vertex3 {

  private:
    int     i;        // Vertex index in list
    int     x,y,z;    // Coordinates
    bool    remove;   // True iff should be removed

    Vertex3* next;
    Vertex3* prev;


  public:
    /*******************************************************
    * Constructor
    *******************************************************/
    Vertex3( int i = -1, int x = 0, int y = 0, int z = 0) 
            : i(i), x(x), y(y), z(z) 
    {
      remove = false;
      next   = nullptr;
      prev   = nullptr;
    }

    /*******************************************************
    * Setter functions 
    *******************************************************/
    void setI( int i0 ){ i = i0; }
    void setX( int x0 ){ x = x0; }
    void setY( int y0 ){ y = y0; }
    void setZ( int z0 ){ z = z0; }

    void setRem( bool doRem ){ remove = doRem; }
    void setNext( Vertex3* v ){ next = v; }
    void setPrev( Vertex3* v ){ prev = v; }

    /*******************************************************
    * Getter functions 
    *******************************************************/
    int       getI( void ){ return i; }
    int       getX( void ){ return x; }
    int       getY( void ){ return y; }
    int       getZ( void ){ return z; }

    bool      getRem( void ){ return remove; }
    Vertex3* getNext( void ){ return next; }
    Vertex3* getPrev( void ){ return prev; }
};

/***********************************************************
* This class defines the 3D edge structure, which is used
* to represent a 3D polygon by means of a circular linked
* list
***********************************************************/
class Edge3 {

  private:
    int         i;              // edge index
    Vertex3*    v0;             // startvertex
    Vertex3*    v1;             // endvertex
    //Face3*      adjfaces[2];  // adjacent faces
    Edge3*      next;           // next edge
    Edge3*      prev;           // previous edge

  public:
    /*******************************************************
    * Constructor
    *******************************************************/
    Edge3( int i = -1 , 
           Vertex3* v0 = nullptr, 
           Vertex3* v1 = nullptr) 
         : i(i), v0(v0), v1(v1)
    {
      //adjfaces[0] = nullptr;
      //adjfaces[1] = nullptr;
      next        = nullptr;
      prev        = nullptr;
    }

    /*******************************************************
    * Setter functions 
    *******************************************************/
    void setI( int i0 ){ i = i0; }
    void setV0( Vertex3* v ){ v0 = v; }
    void setV1( Vertex3* v ){ v1 = v; }
    void setNext( Edge3* e ){ next = e; }
    void setPrev( Edge3* e ){ prev = e; }

    /*******************************************************
    * Getter functions 
    *******************************************************/
    int       getI( void ){ return i; }
    Vertex3*  getV0( void ){ return v0; }
    Vertex3*  getV1( void ){ return v1; }
    Edge3*    getNext( void ){ return next; }
    Edge3*    getPrev( void ){ return prev; }

};


/*==========================================================
| OPERATOR DEFINITIONS
==========================================================*/

/***********************************************************
* Vertex3 - ostream operator definition
***********************************************************/
std::ostream& operator<< (std::ostream& out, Vertex3& v) {
  out << "Vertex " << v.getI() << ": ( " << v.getX() 
  << ", " << v.getY() << ", " << v.getZ() << " )"; 
  return out;
}

/***********************************************************
* Edge2 - ostream operator definition
***********************************************************/
std::ostream& operator<< (std::ostream& out, Edge3& e) {
  out << "Edge " << e.getI() << ": V" << e.getV0()->getI() 
  << " -> V" << e.getV1()->getI();
  return out;
}

#endif
