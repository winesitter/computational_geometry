#ifndef POLYGON2_HULL_
#define POLYGON2_HULL_

#include <iostream>
#include <vector>
#include "polygon2/polygon.hpp"


/***********************************************************
* Definition of functions
***********************************************************/

/***********************************************************
* This function finds the rightmost lowest point in the set
* and swaps it to the front
***********************************************************/
void findLowest( std::vector<Vertex*> &vertices );

#endif
