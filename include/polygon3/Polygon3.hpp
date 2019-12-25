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
* This class defines the 3D polygon 
***********************************************************/
class Polygon3;


/***********************************************************
* 
***********************************************************/
class Polygon3 {

  private: 
    int           nFaces;
    int           nEdges;
    int           nVertices;

    Face3*        fHead;    // Head of polygons face list
    Edge3*        eHead;    // Head of polygons edge list
    Vertex3*      vHead;    // Head of vertices list

  public:
    /*------------------------------------------------------
    * Constructor
    ------------------------------------------------------*/
    Polygon3( Vertex3 *verts );

    /*------------------------------------------------------
    * Setter functions 
    ------------------------------------------------------*/
    void      setEdgeHead( Edge3* e0){ eHead = e0; }
    void      setFaceHead( Face3* f0){ fHead = f0; }

    /*------------------------------------------------------
    * Getter functions 
    ------------------------------------------------------*/
    int       getNFaces( void ){ return nFaces; }
    int       getNEaces( void ){ return nEdges; }
    int       getNVertices( void ){ return nVertices; }

    int       incNFaces( void ){ return nFaces++; }
    int       incNEdges( void ){ return nEdges++; }
    int       incNVertices( void ){ return nVertices++; }

    Face3*    getFaceHead( void ){ return fHead; }
    Edge3*    getEdgeHead( void ){ return eHead; }
    Vertex3*  getVertexHead( void ){ return vHead; }

    /*------------------------------------------------------
    * Public functions
    ------------------------------------------------------*/

    /*******************************************************
    * Create double triangle as initial polytope  
    *-------------------------------------------------------
    * 1) Find three noncollinear points (v0, v1, v2)
    * 2) Create and link the two triangle faces f0 and f1
    * 3) Find a fourht point v3, which is not coplanar with
    *    (v0, v1, v2)
    *******************************************************/
    void initDoubleTriangle( void );

    /*******************************************************
    * Add new vertex to the current hull structure
    *-------------------------------------------------------
    * @param p - new vertex that will be added to the 
    *            convex hull of the polygon
    *******************************************************/
    bool addVertexToHull( Vertex3* p );

    /*******************************************************
    * Create double triangle as initial polytope  
    *-------------------------------------------------------
    * 
    *******************************************************/
    void constructHull( void ); 

    /*******************************************************
    * Clean faces which were created in the hull
    * construction process of the polygon
    *-------------------------------------------------------
    * 
    *******************************************************/
    void cleanHullFaces( void );

    /*******************************************************
    * Clean edges which were created in the hull
    * construction process of the polygon
    *-------------------------------------------------------
    * 
    *******************************************************/
    void cleanHullEdges( void );

    /*******************************************************
    * Clean vertices which were created in the hull
    * construction process of the polygon
    *-------------------------------------------------------
    * 
    *******************************************************/
    void cleanHullVertices( void );


};




/*==========================================================
| Function definition
==========================================================*/

/***********************************************************
* Check three vertices for collinearity
***********************************************************/
bool isCollinear3( Vertex3* a, Vertex3* b, Vertex3* c );


#endif
