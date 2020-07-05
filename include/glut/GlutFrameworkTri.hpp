#ifndef GLUT_FRAMEWORKTRI_H
#define GLUT_FRAMEWORKTRI_H

#include "glut/GlutFramework.hpp"

#include "polygon3/Polygon3.hpp"
#include "polygon3/Face3.hpp"
#include "polygon3/Edge3.hpp"
#include "polygon3/Vertex3.hpp"


namespace glutFramework {

  /*********************************************************
  * Derive sub-class for framework of application
  *********************************************************/
	class GlutFrameworkTri : public GlutFramework {

  /*-------------------------------------------------------
  | Public attributes
  -------------------------------------------------------*/
  private:
    Polygon3*       polygon;
    float           rotation;
    Vector<float>   rotVector;
    Vector<float>   transVector;

  /*-------------------------------------------------------
  | Public methods
  -------------------------------------------------------*/
  public:
    /*-----------------------------------------------------
    | Constructor and destructor methods
    -----------------------------------------------------*/
		GlutFrameworkTri(Polygon3* p);

    /*-----------------------------------------------------
		| The display function is called at a specified 
    | frames-per-second (FPS). Any animation drawing code 
    | can be run in the display method.
    |
		| @param dTime - the change in time (seconds)
    -----------------------------------------------------*/
		virtual void display(float dTime);

    /*-----------------------------------------------------
		| Called when the mouse buttons are pressed.
    |
		| @param button - the mouse buttons
		| @param state - the state of the buttons
		| @param x - the x coordinate
		| @param y - the y coordinate
    -----------------------------------------------------*/
		virtual void mouseButtonPress(int button, int state, 
                                  int x, int y);

    /*-----------------------------------------------------
		| Called when the mouse moves on the screen.
    |
		| @param x - the x coordinate
		| @param y - the y coordinate
    -----------------------------------------------------*/
		virtual void mouseMove(int x, int y);

    /*-----------------------------------------------------
		| The keyboard function is called when a standard key 
    | is pressed down.
    |
		| @param key - the key press
		| @param x - the x coordinate of the mouse
		| @param y - the y coordinate of the mouse
    -----------------------------------------------------*/
		virtual void keyboardDown( unsigned char key, 
                               int x, int y );

    /*-----------------------------------------------------
		| The keyboard function is called when a standard key 
    | is "unpressed".
    |
		| @param key - the key press
		| @param x - the x coordinate of the mouse
		| @param y - the y coordinate of the mouse
    -----------------------------------------------------*/
		virtual void keyboardUp( unsigned char key, 
                             int x, int y );

    /*-----------------------------------------------------
		| The keyboard function is called when a standard key 
    | is "unpressed".
    | Function to draw a list of vertices.
    |
    | @param *v - linked list of vertices
    -----------------------------------------------------*/
    virtual void drawPolyVertices( Vertex3* v );

    /*-----------------------------------------------------
    | Function to draw meshgrid.
    -----------------------------------------------------*/
    virtual void drawMeshgrid( void );

    /*-----------------------------------------------------
    | Function to draw all polygon faces
    -----------------------------------------------------*/
    virtual void drawPolyFaces( Polygon3* p );

  };

} // namespace

#endif
