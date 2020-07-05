#include "glut/GlutFrameworkTri.hpp"

namespace glutFramework {

  /*********************************************************
  * GlutFrameworkTri Sub-Class definition
  *********************************************************/

  /*--------------------------------------------------------
  | Constructor
  --------------------------------------------------------*/
	GlutFrameworkTri::GlutFrameworkTri( Polygon3* p ) : GlutFramework(){ 

    polygon = p;

		elapsedTimeInSeconds = 0;
		frameTimeElapsed = 0;
		title = "3D Triangulator - Florian Setzwein";

    // move the eye position back
		eyeVector   = Vector<float>(0.0f, 0.0f, -10.0f); 
    rotVector   = Vector<float>(0.0f, 0.0f, 0.0f);
    transVector = Vector<float>(0.0f, 0.0f, 0.0f);

    rotation = 0.0f;
		position = 0.0f;
		direction = 1.0 / FRAME_TIME;
	}

  /*-------------------------------------------------------
  | The display function is called at a specified 
  | frames-per-second (FPS). Any animation drawing code 
  | can be run in the display method.
  |
  | @param dTime - the change in time (seconds)
  --------------------------------------------------------*/
	void GlutFrameworkTri::display(float dTime) {

    (void) dTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Apply geometric transformation on visible bodies
    glRotatef(rotVector.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotVector.y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotVector.z, 0.0f, 0.0f, 1.0f);

    glTranslatef(transVector.x, transVector.y, transVector.z);

    // Draw stuff
    drawMeshgrid();
    drawPolyVertices(this->polygon->getVertexHead());
    drawPolyFaces(this->polygon);

	}

  /*--------------------------------------------------------
  | Called when the mouse buttons are pressed.
  |
  | @param button - the mouse buttons
  | @param state - the state of the buttons
  | @param x - the x coordinate
  | @param y - the y coordinate
  --------------------------------------------------------*/
	void GlutFrameworkTri::mouseButtonPress(int button, int state, 
                                       int x, int y) {
    //std::ignore = button;
    std::ignore = state;

    if (button == 0)
      printf("LeftMouseButtonPress: x: %d y: %d\n", x, y);
		
	}

  /*--------------------------------------------------------
  | Called when the mouse moves on the screen.
  |
  | @param x - the x coordinate
  | @param y - the y coordinate
  --------------------------------------------------------*/
	void GlutFrameworkTri::mouseMove(int x, int y) {
		printf("MouseMove: x: %d y: %d\n", x, y);
	}

  /*--------------------------------------------------------
  | The keyboard function is called when a standard key 
  | is pressed down.
  |
  | @param key - the key press
  | @param x - the x coordinate of the mouse
  | @param y - the y coordinate of the mouse
  --------------------------------------------------------*/
	void GlutFrameworkTri::keyboardDown( unsigned char key, 
                                       int x, int y ) 
	{
    std::ignore = x;
    std::ignore = y;

    /*-----------------------------------------------------
    | ESC (27) or q (113) to exit 
    -----------------------------------------------------*/
		if( key ==  27 ) { exit (0);	}
		if( key == 'q' ) { exit (0);	}

    /*-----------------------------------------------------
    | Movement of center vector
    | w (119) to center up
    | s (115) to center down
    | d (100) to center right
    | a (97) to center left
    -----------------------------------------------------*/
    if ( key == 'i' ) { transVector.y -= 10. / FRAME_TIME; }
    if ( key == 'n' ) { transVector.y += 10. / FRAME_TIME; }
    if ( key == 'l' ) { transVector.x -= 10. / FRAME_TIME; }
    if ( key == 'h' ) { transVector.x += 10. / FRAME_TIME; }
    if ( key == 'j' ) { transVector.z -= 10. / FRAME_TIME; }
    if ( key == 'k' ) { transVector.z += 10. / FRAME_TIME; }

    if ( key == 'w' ) { rotVector.x += 30.0  / FRAME_TIME; }
    if ( key == 's' ) { rotVector.x -= 30.0  / FRAME_TIME; }
    if ( key == 'a' ) { rotVector.y += 30.0  / FRAME_TIME; }
    if ( key == 'd' ) { rotVector.y -= 30.0  / FRAME_TIME; }

    //if (rotation >= 360) { rotation = 0.0; }

    /*-----------------------------------------------------
    | Movement of eye vector
    | + (43) zoom in 
    | - (45) zoom out 
    -----------------------------------------------------*/
    if ( key == 43 ) 
      eyeVector.z -= 2. / FRAME_TIME;
    if ( key == 45 ) 
      eyeVector.z += 2. / FRAME_TIME;
    
		keyStates.keyDown( (int)key );
	}

  /*--------------------------------------------------------
  | The keyboard function is called when a standard key 
  | is "unpressed".
  |
  | @param key - the key press
  | @param x - the x coordinate of the mouse
  | @param y - the y coordinate of the mouse
  --------------------------------------------------------*/
	void GlutFrameworkTri::keyboardUp( unsigned char key, 
                                     int x, int y ) 
	{
		// Subclass and override this method
    std::ignore = x;
    std::ignore = y;
		keyStates.keyUp( (int)key );
	}

  /*-------------------------------------------------------
  | Function to draw a list of vertices.
  |
  | @param *v - linked list of vertices
  -------------------------------------------------------*/ 
  void GlutFrameworkTri::drawPolyVertices( Vertex3* v )
  {
    // Draw vertices
    Vertex3* head = v;
    Vertex3* cur = head;

    do {
      glPushMatrix();
      glColor3f(1.0,1.0,1.0);
      glTranslatef(cur->x, cur->y, cur->z);
      glutSolidCube(0.1);
      glPopMatrix();
      cur = cur->getNext();
    } while( cur != head) ;

  }

  /*-------------------------------------------------------
  | Function to draw meshgrid.
  -------------------------------------------------------*/
  void GlutFrameworkTri::drawMeshgrid( void )
  {
    for (float i = 0.0; i < 40.0; i += 1.0) {
      glPushMatrix();
      if ( i < 20.0 ) { 
        glTranslatef(0.0, 0.0, i); 
      }
      if ( i>= 20.0 ) { 
        glTranslatef(i-20.0, 0.0, 0.0); 
        glRotatef(-90.0, 0.0, 1.0, 0.0); 
      }

      glBegin( GL_LINES );
      glColor3f(1.0f, 1.0f, 1.0f);
      glLineWidth(1);
      glVertex3f(0.0, -0.1, 0.0);
      glVertex3f(19.0, -0.1, 0.0);
      glEnd();
      glPopMatrix();
    }
  }

  /*-------------------------------------------------------
  | Function to draw triangular polygon faces.
  |
  | @param *p - linked list of vertices
  -------------------------------------------------------*/ 
  void GlutFrameworkTri::drawPolyFaces( Polygon3* p )
  {
    // Draw vertices
    Face3* curFace = p->getFaceHead();

    glBegin(GL_TRIANGLES);
    do {
      glColor4f(1.0,1.0,1.0,0.2);
      glVertex3f(curFace->getVert(0)->x,
                 curFace->getVert(0)->y,
                 curFace->getVert(0)->z);
      glVertex3f(curFace->getVert(1)->x,
                 curFace->getVert(1)->y,
                 curFace->getVert(1)->z);
      glVertex3f(curFace->getVert(2)->x,
                 curFace->getVert(2)->y,
                 curFace->getVert(2)->z);

      curFace = curFace->getNext();
    } while (curFace != p->getFaceHead());
    glEnd();


  }

} // namespace
