#include <iostream>
#include <vector>
#include "polygon3/Face3.hpp"
#include "polygon3/Edge3.hpp"

// Global edge counter
int NEDGES = 0;

/*----------------------------------------------------------
| Constructor definitions 
----------------------------------------------------------*/
// Create empty edge
Edge3::Edge3() {
  index = NEDGES++;

  for (int j = 0; j < 2; ++j) {
    vertices[j] = nullptr;
    adjfaces[j] = nullptr;
  }
  remove      = false;
  newFace     = nullptr;
  next = prev = nullptr;
}

// Create edge from vertices
Edge3::Edge3( Vertex3 *v0, Vertex3 *v1 ) {
  index = NEDGES++;

  vertices[0] = v0;
  vertices[1] = v1;

  remove      = false;
  newFace     = nullptr;
  next = prev = nullptr;
}
