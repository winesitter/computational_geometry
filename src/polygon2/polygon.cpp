#include <iostream>
#include "polygon2/polygon.hpp"



/***********************************************************
* Function to calcualte twice the area of a triangle (a,b,c)
***********************************************************/
static inline int area2( Vertex* a, Vertex* b, Vertex* c )
{
  return 
    (b->get_x() - a->get_x()) * (c->get_y() - a->get_y()) - 
    (c->get_x() - a->get_x()) * (b->get_y() - a->get_y());
}

/***********************************************************
* Function to check, weather Vertex c is located to the 
* left of a line segment, defined by Vertices a and b
***********************************************************/
bool isLeft( Vertex* a, Vertex* b, Vertex* c )
{
  return area2( a, b, c ) > 0;
}

/***********************************************************
* Function to check, weather Vertex c is located to the 
* left of a line segment, defined by Vertices a and b
* or directly on it
***********************************************************/
bool isLeftOn( Vertex* a, Vertex* b, Vertex* c )
{
  return area2( a, b, c ) >= 0;
}

/***********************************************************
* Function to check, weather Vertex c is located on a 
* line segment, defined by Vertices a and b
***********************************************************/
bool isCollinear( Vertex* a, Vertex* b, Vertex* c )
{
  return area2( a, b, c ) == 0;
}

/***********************************************************
* Exclusive or: True if and only if exactly one argument 
*               is true
***********************************************************/
bool xOr( bool x, bool y )
{
  return !x ^ !y;
}

/***********************************************************
* Check weather two line segments (a,b) and (c,d) 
* intersect.
***********************************************************/
bool doIntersectProperly( Vertex* a, Vertex* b, 
                          Vertex* c, Vertex* d )
{
  // Eliminate improper cases
  if (
      isCollinear(a,b,c) || isCollinear(a,b,d) ||
      isCollinear(c,d,a) || isCollinear(c,d,b)
     )
    return false;

  return 
       xOr( isLeft(a,b,c), isLeft(a,b,d) )
    && xOr( isLeft(c,d,a), isLeft(c,d,b) );
}

/***********************************************************
* Check weather a vertex c is in between a line 
* segment (a,b)
***********************************************************/
bool isBetween( Vertex *a, Vertex* b, Vertex* c )
{
  if ( !isCollinear( a, b, c ) )
    return false;

  // If (a,b) not vertical, check betweenness on x,
  // else on y
  if ( a->get_x() != b->get_x() )
    return (  (a->get_x() <= c->get_x()) 
           && (c->get_x() <= b->get_x()) ) ||
           (  (a->get_x() >= c->get_x()) 
           && (c->get_x() >= b->get_x()) );
  else
    return (  (a->get_y() <= c->get_y()) 
           && (c->get_y() <= b->get_y()) ) ||
           (  (a->get_y() >= c->get_y()) 
           && (c->get_y() >= b->get_y()) );

}

/***********************************************************
* Check weather two line segments (a,b) and (c,d)
* intersect.
***********************************************************/
bool doIntersect( Vertex* a, Vertex* b,
                  Vertex* c, Vertex* d )
{
  if      ( doIntersectProperly( a, b, c, d ) )
    return true;
  else if (   isBetween( a, b, c )
           || isBetween( a, b, d ) 
           || isBetween( c, d, a ) 
           || isBetween( c, d, b ) 
          )
    return true;
  else
    return false;
}

/***********************************************************
* Check weather a line segment (a,b) is a diagonal 
* of a polygon p.
* It is not distinguished, if the diagonal is Interior 
* or Exterior to the polygon
* >> Part of isDiagonal()
***********************************************************/
bool isDiagonalIE( Vertex* a, Vertex* b, Polygon* p)
{
  Vertex* c  = p->get_head();
  Vertex* c1 = NULL;

  do {
    c1 = c->get_next();

    if (    ( c != a ) && ( c1 != a )
         && ( c != b ) && ( c1 != b )
         && doIntersect( a, b, c, c1 )
       )
      return false;

    c  = c->get_next();

  } while ( c != p->get_head() );

  return true;
}

/***********************************************************
* Check if diagonal (a,b) is interior or exterior 
* to the incident edges of the diagonals starting point a
* >> Part of isDiagonal()
***********************************************************/
bool isInCone( Vertex* a, Vertex* b)
{
  Vertex* a0 = a->get_prev(); // a-
  Vertex* a1 = a->get_next(); // a+

  // If a is convex vertex:
  if ( isLeftOn( a, a1, a0 ) )
    return ( isLeft( a, b, a0 ) && isLeft( b, a, a1 ) );

  // Else is a reflex vertex:
  return  !( isLeft( a, b, a1 ) && isLeft( b, a, a0 ) );

}

/***********************************************************
* Check weather a line segment (a,b) is a diagonal 
* of a polygon p.
***********************************************************/
bool isDiagonal( Vertex* a, Vertex* b, Polygon* p)
{
  return (  isInCone( a, b ) && isInCone( b, a ) 
         && isDiagonalIE( a, b, p ) );
}

/***********************************************************
* Initialize the ear status for every vertex in the 
* polygon
***********************************************************/
void initEars( Polygon* p )
{
  Vertex *v0 = NULL, *v1 = NULL, *v2 = NULL;

  // Init v->ear for every vertex
  v1 = p->get_head();

  do {
    v2 = v1->get_next();
    v0 = v1->get_prev();

    v1->set_ear( isDiagonal( v0, v2 , p) );
    v1 = v1->get_next();

  } while ( v1 != p->get_head() );

}

/***********************************************************
* Triangulate a polygon p
***********************************************************/
void triangulate( Polygon* p )
{
  Vertex *v0 = NULL, *v1 = NULL, *v2 = NULL;
  Vertex *v3 = NULL, *v4 = NULL;

  int n = p->get_nVerts();

  initEars( p );

  // Eachstep of outer loop removes one ear
  while ( n > 3 ) {

    // Inner loop searches for one ear
    v2 = p->get_head();

    do {

      if ( v2->get_ear() ) {
        // Ear found. Fill variables
        v3 = v2->get_next(); v4 = v3->get_next();
        v1 = v2->get_prev(); v0 = v1->get_prev();

        // (v1,v3) is a diagonal 
        // create triangle (v1,v2,v3)
        std::cout << v1->get_ind() << " " 
          << v2->get_ind() << " "
          << v3->get_ind() << std::endl;

        // Update earity of diagonal endpoints
        v1->set_ear( isDiagonal( v0, v3, p ) );
        v3->set_ear( isDiagonal( v1, v4, p ) );

        // Cut off the ear v2
        p->rem_vertex( v2 );
        --n;

        // Ear found -> look for new one
        break;

      } // End of if ear found

      v2 = v2->get_next();

    } while ( v2 != p->get_head() );

  } // End of while ( n > 3 )

  v2 = p->get_head();
  v3 = v2->get_next();
  v1 = v2->get_prev();
  std::cout << v1->get_ind() << " " 
    << v2->get_ind() << " "
    << v3->get_ind() << std::endl;
}


/*----------------------------------------------------------
| Polygon class functions
----------------------------------------------------------*/

/***********************************************************
* 
***********************************************************/
void Polygon::add_vertex(Vertex* v) 
{
  if ( head ) {
    v->set_next(head);
    v->set_prev(head->get_prev());
    head->set_prev(v);
    v->get_prev()->set_next(v);

  }
  else {
    head = v;
    head->set_next(v);
    head->set_prev(v);
  }

  // Increment vertex counter
  ++nVerts;
} 

/***********************************************************
* Need check if vertex is part of polygon 
* -> Implement polygon as parent
***********************************************************/
void Polygon::rem_vertex(Vertex* v) 
{
  Vertex *prev = v->get_prev();
  Vertex *next = v->get_next();

  // Remove v from list
  prev->set_next(next);
  next->set_prev(prev);

  // If v is current head -> set next as head
  //if ( v == head )
  head = next;

  // Isolate v
  v->set_next(NULL);
  v->set_prev(NULL);

  // Decrease vertex counter
  --nVerts;
}

/***********************************************************
* 
***********************************************************/
void Polygon::print_vertices( void ) {
  Vertex* v = head;
  if ( head ) {
    do {
      std::cout << "Vertex " << v->get_ind() << ": (" 
        << v->get_x() << ", " << v->get_y() 
        << ") " << std::endl;
      v = v->get_next();
    } while ( v != head );
  }
}

/***********************************************************
* 
***********************************************************/
int Polygon::calc_area( void ) {

  int sum = 0;

  Vertex* p = head;
  Vertex* a = head->get_next();

  do {
    sum += area2( p, a, a->get_next() );
    a = a->get_next();
  } while (a->get_next() != head );

  return sum;
}


