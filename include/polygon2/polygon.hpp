#ifndef POLYGON2_POLYGON_
#define POLYGON2_POLYGON_

#include <iostream>
#include <vector>
#include "polygon2/globals.hpp"

/***********************************************************
* This class defines the vertex structure, which is used
* to represent a 2D polygon by means of a circular linked
* list
***********************************************************/
class Vertex {

  private:
    int      ind;          // Index
    int      x,y;          // Coordinates
    bool     ear;          // True iff an ear
    bool     remove;       // True iff should be removed
    Vertex*  next;
    Vertex*  prev;

  public: 
    /*******************************************************
    * Constructor
    *******************************************************/
    Vertex( int i,  int x0, int y0 ) 
    {
      ind     = i; 
      x       = x0;
      y       = y0; 
      ear     = false; 
      remove  = false;
      next    = NULL;
      prev    = NULL;
    }

    /*******************************************************
    * Setter functions 
    *******************************************************/
    void set_ind( int i ){ ind = i; }
    void set_x( int x0 ){ x = x0; }
    void set_y( int y0 ){ y = y0; }
    void set_ear( bool isEar ){ ear = isEar; }
    void set_rem( bool doRem ){ remove = doRem; }
    void set_next( Vertex* v ){ next = v; }
    void set_prev( Vertex* v ){ prev = v; }

    /*******************************************************
    * Getter functions 
    *******************************************************/
    int     get_ind( void ){ return ind; }
    int     get_x( void ){ return x; }
    int     get_y( void ){ return y; }
    bool    get_ear( void ){ return ear; }
    bool    get_rem( void ){ return remove; }
    Vertex* get_next( void ){ return next; }
    Vertex* get_prev( void ){ return prev; }

};

/***********************************************************
* A polygon class, defined by vertices
***********************************************************/
class Polygon {

  private:
    Vertex* head;
    int     nVerts;

  public:
    /*******************************************************
    * Constructor
    *******************************************************/
    Polygon( void ) 
    {
      head = NULL;
      nVerts = 0;
    }

    /*******************************************************
    * Getter functions
    *******************************************************/
    Vertex* get_head( void ){ return head; }
    int     get_nVerts( void ){ return nVerts; }

    void add_vertex( Vertex* v );
    void rem_vertex( Vertex* v );
    int  calc_area( void );
    void print_vertices( void );

};


/***********************************************************
* Definition of functions
***********************************************************/
/***********************************************************
* Function to calcualte twice the area of a triangle (a,b,c)
***********************************************************/
int area2( Vertex* a, Vertex* b, Vertex* c );

/***********************************************************
* Exclusive or: True if and only if exactly one argument 
*               is true
***********************************************************/
bool xOr( bool x, bool y );

/***********************************************************
* Function to check, weather Vertex c is located to the 
* left of a line segment, defined by Vertices a and b
***********************************************************/
bool isLeft( Vertex* a, Vertex* b, Vertex* c );

/***********************************************************
* Function to check, weather Vertex c is located to the 
* left of a line segment, defined by Vertices a and b
* or directly on it
***********************************************************/
bool isLeftOn( Vertex* a, Vertex* b, Vertex* c );

/***********************************************************
* Function to check, weather Vertex c is located on a 
* line segment, defined by Vertices a and b
***********************************************************/
bool isCollinear( Vertex* a, Vertex* b, Vertex* c );

/***********************************************************
* Check weather two line segments (a,b) and (c,d) 
* intersect.
***********************************************************/
bool doIntersectProperly( Vertex* a, Vertex* b, 
                          Vertex* c, Vertex* d );

/***********************************************************
* Check weather a vertex c is in between a line 
* segment (a,b)
***********************************************************/
bool isBetween( Vertex *a, Vertex* b, Vertex* c );

/***********************************************************
* Check weather two line segments (a,b) and (c,d)
* intersect.
***********************************************************/
bool doIntersect( Vertex* a, Vertex* b,
                  Vertex* c, Vertex* d );

/***********************************************************
* Check weather a line segment (a,b) is a diagonal 
* of a polygon p.
* It is not distinguished, if the diagonal is Interior 
* or Exterior to the polygon
* >> Part of isDiagonal()
***********************************************************/
bool isDiagonalIE( Vertex* a, Vertex* b, Polygon* p);

/***********************************************************
* Check if diagonal (a,b) is interior or exterior 
* to the incident edges of the diagonals starting point a
* >> Part of isDiagonal()
***********************************************************/
bool isInCone( Vertex* a, Vertex* b);

/***********************************************************
* Check weather a line segment (a,b) is a diagonal 
* of a polygon p.
***********************************************************/
bool isDiagonal( Vertex* a, Vertex* b, Polygon* p);

/***********************************************************
* Initialize the ear status for every vertex in the 
* polygon
***********************************************************/
void initEars( Polygon* p );

/***********************************************************
* Triangulate a polygon p
***********************************************************/
void triangulate( Polygon* p );

#endif
