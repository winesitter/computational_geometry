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
