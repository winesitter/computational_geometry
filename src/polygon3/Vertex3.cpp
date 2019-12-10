#include <iostream>
#include <vector>
#include "polygon3/Vertex3.hpp"

/*----------------------------------------------------------
| Operators redefinition 
----------------------------------------------------------*/
// Vertex addition
Vertex3 Vertex3::operator+( const Vertex3 &other) const {
  Vertex3 result;
  result.x = this->x + other.x;
  result.y = this->y + other.y;
  result.z = this->z + other.z;
  return result;
}

// Vertex subtraction
Vertex3 Vertex3::operator-( const Vertex3 &other) const {
  Vertex3 result;
  result.x = this->x - other.x;
  result.y = this->y - other.y;
  result.z = this->z - other.z;
  return result;
}

/***********************************************************
* Check this vertex for collinearity with two other vertices
*
* @param Vertex3* b, Vertex3* c - Vertices to check for 
*   collinearity
* @return true if collinear, false if not
***********************************************************/
bool Vertex3::isCollinear( const Vertex3 &b, 
                           const Vertex3 &c ) const {
  Vertex3 db = *this - b;
  Vertex3 dc = *this - c;

  return   (db.y * dc.z) - (db.z * dc.y) == 0 
        && (db.z * dc.x) - (db.x * dc.z) == 0
        && (db.x * dc.y) - (db.y * dc.x) == 0;
}
