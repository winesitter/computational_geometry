#ifndef POLYGON3_POLYGON_
#define POLYGON3_POLYGON_

#include <iostream>
#include <vector>
#include <array>

/***********************************************************
* This class defines the 3D vertex structure, which is used
* to represent a 3D polygon by means of a circular linked
* list
***********************************************************/
class Vertex3;

/***********************************************************
* This class defines the 3D edge structure, which is used
* to represent a 3D polygon by means of a circular linked
* list
***********************************************************/
class Edge3;

/***********************************************************
* This class defines the 3D face structure, which is used
* to represent a 3D polygon by means of a circular linked
* list
***********************************************************/
class Face3;


/***********************************************************
*
***********************************************************/
class Vertex3 {

  private:
    int      i;         // Vertex index in list
    int      x,y,z;     // Coordinates
    bool     onHull;    // True iff on convex hull
    bool     mark;      // True iff already processed

    Edge3*   duplicate; // Pointe to incident cone edge 
    Vertex3* next;
    Vertex3* prev;


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
    void setX( int x0 ){ x = x0; }
    void setY( int y0 ){ y = y0; }
    void setZ( int z0 ){ z = z0; }

    void setMark( bool doMark ){ mark = doMark; }
    void setOnHull( bool isOn ){ onHull = isOn; }
    void setDuplicate( Edge3* e){ duplicate = e; }
    void setNext( Vertex3* v ){ next = v; }
    void setPrev( Vertex3* v ){ prev = v; }

    /*------------------------------------------------------
    * Getter functions 
    ------------------------------------------------------*/
    int       getI( void ){ return i; }
    int       getX( void ){ return x; }
    int       getY( void ){ return y; }
    int       getZ( void ){ return z; }

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
      out << "Vertex " << v.getI() << ": ( " << v.getX() 
      << ", " << v.getY() << ", " << v.getZ() << " )"; 
      return out;
}

};

/***********************************************************
* 
***********************************************************/
class Edge3 {

  private:
    int                     i;           // edge index
    std::array<Vertex3*,3>  vertices;    // edge vertices
    std::array<Face3*,3>    adjfaces;    // adjacent faces
    Face3*                  newFace;     // Pointer to incident new face
    bool                    remove;      // Remove edge
    Edge3*                  next;        // next edge
    Edge3*                  prev;        // previous edge

  public:
    /*------------------------------------------------------
    * Constructor
    ------------------------------------------------------*/
    Edge3( int i = -1 ) : i(i)
    {
      for (int j = 0; j < 2; ++j) {
        vertices[j] = nullptr;
        adjfaces[j] = nullptr;
      }
      remove      = false;
      newFace     = nullptr;
      next = prev = nullptr;
    }

    /*------------------------------------------------------
    * Setter functions 
    ------------------------------------------------------*/
    void setI( int i0 ){ i = i0; }
    void setVert( int i0, Vertex3* v ){ vertices[i0] = v; }
    void setFace( int i0, Face3* f ){ adjfaces[i0] = f; }
    void setNewFace( Face3* f ){ newFace = f; }
    void setRemove( bool t ){ remove = t; }
    void setNext( Edge3* e ){ next = e; }
    void setPrev( Edge3* e ){ prev = e; }

    /*------------------------------------------------------
    * Getter functions 
    ------------------------------------------------------*/
    int       getI( void ){ return i; }
    Vertex3*  getVert( int i0 ){ return vertices[i0]; }
    Face3*    getFace( int i0 ){ return adjfaces[i0]; }
    Face3*    getNewFace( void ){ return newFace; }
    bool      getRemove( void ){ return remove; }
    Edge3*    getNext( void ){ return next; }
    Edge3*    getPrev( void ){ return prev; }

    /*------------------------------------------------------
    * Operators redefinition 
    ------------------------------------------------------*/
    friend std::ostream& operator<< (std::ostream& out, 
                                     Edge3& e) {
      out << "Edge " << e.getI() << ": V" 
        << e.getVert(0)->getI() << " -> V" 
        << e.getVert(1)->getI();
      return out;
}

};

/***********************************************************
*
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


/*==========================================================
| Function definition
==========================================================*/

/***********************************************************
* Check three vertices for collinearity
***********************************************************/
bool isCollinear3( Vertex3* a, Vertex3* b, Vertex3* c );

/***********************************************************
* Create double triangle as initial polytope  
*-----------------------------------------------------------
* 1) Find three noncollinear points (v0, v1, v2)
* 2) Create and link the two triangle faces f0 and f1
* 3) Find a fourht point v3, which is not coplanar with
*    (v0, v1, v2)
***********************************************************/
void initDoubleTriangle( Vertex3* verts );

#endif
