/*
 * The MIT License
 *
 * Copyright (c) 2010 Paul Solt, PaulSolt@gmail.com 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "glut/GlutFramework.hpp"

namespace glutFramework {
	
  /*********************************************************
  * GlutFramework Class definition
  *********************************************************/
	const double GlutFramework::FRAME_TIME = 1.0 / GlutFramework::FPS * 1000.0; // Milliseconds
  int GlutFramework::FRAME = 0;
	GlutFramework *GlutFramework::instance = NULL;
	
  /*--------------------------------------------------------
  | Constructor
  --------------------------------------------------------*/
	GlutFramework::GlutFramework() { 
		elapsedTimeInSeconds = 0;
		frameTimeElapsed = 0;
		title = "GLUT Framework: Paul Solt 2010";
		eyeVector = Vector<float>(0.0, 0.0, -10.0); // move the eye position back
		position = 0.0f;
		direction = 1.0 / FRAME_TIME;
	}
	
  /*--------------------------------------------------------
  | Destructor
  --------------------------------------------------------*/
	GlutFramework::~GlutFramework() {
	}
	
  /*--------------------------------------------------------
  | startFramework will initialize framework and start 
  | the Glut run loop. It must be called after the 
  | GlutFramework class is created to start the 
  | application.
  --------------------------------------------------------*/
	void GlutFramework::startFramework(int argc, char *argv[]) {
		setInstance();	// Sets the instance to self, used in the callback wrapper functions
		
		// Initialize GLUT
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowPosition(WINDOW_X_POSITION, WINDOW_Y_POSITION);
		glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		glutCreateWindow(title.c_str()); 
		
		// Function callbacks with wrapper functions
		glutReshapeFunc(reshapeWrapper);
		glutMouseFunc(mouseButtonPressWrapper);
		glutMotionFunc(mouseMoveWrapper);
		//glutPassiveMotionFunc(mouseMoveWrapper);
		glutDisplayFunc(displayWrapper);
		glutKeyboardFunc(keyboardDownWrapper);
		glutKeyboardUpFunc(keyboardUpWrapper);
		glutSpecialFunc(specialKeyboardDownWrapper);
		glutSpecialUpFunc(specialKeyboardUpWrapper);
		
		init();						// Initialize
		glutIdleFunc(runWrapper); 	// The program run loop
		glutMainLoop();				// Start the main GLUT thread
	}
	
  /*--------------------------------------------------------
  | Any loading logic can be down in this method when 
  | the application starts. 
  --------------------------------------------------------*/
	void GlutFramework::load() {
		// Subclass and override this method
	}
	
  /*-------------------------------------------------------
  | The display function is called at a specified 
  | frames-per-second (FPS). Any animation drawing code 
  | can be run in the display method.
  |
  | @param dTime - the change in time (seconds)
  --------------------------------------------------------*/
	void GlutFramework::display(float dTime) {
		// Subclass and override this method
		
		std::cout << "GlutFramework Display: Frame: " << FRAME << ", dt(sec): " << dTime << ", Position: " << position << std::endl;
		++FRAME;
		
		// DEMO: Create a teapot and move it back and forth on the x-axis
		glTranslatef(position, 0.0f, 0.0f);
		glutSolidTeapot(2.5); 
		if(position > 4 && direction > 0) {
			direction = -1.0 / FRAME_TIME;
		} else if(position < -4 && direction < 0) {
			direction = 1.0 / FRAME_TIME;
		}		
		position += direction;
	}
	
  /*--------------------------------------------------------
  | Called when the window dimensions change.
  |
  | @param width - the width of the window in pixels
  | @param height - the height of the window in pixels
  --------------------------------------------------------*/
	void GlutFramework::reshape(int width, int height) {
		glViewport(0,0,(GLsizei)width,(GLsizei)height);
	}
	
  /*--------------------------------------------------------
  | Called when the mouse buttons are pressed.
  |
  | @param button - the mouse buttons
  | @param state - the state of the buttons
  | @param x - the x coordinate
  | @param y - the y coordinate
  --------------------------------------------------------*/
	void GlutFramework::mouseButtonPress(int button, int state, 
                                       int x, int y) {
    std::ignore = button;
    std::ignore = state;
		printf("MouseButtonPress: x: %d y: %d\n", x, y);
		
	}
	
  /*--------------------------------------------------------
  | Called when the mouse moves on the screen.
  |
  | @param x - the x coordinate
  | @param y - the y coordinate
  --------------------------------------------------------*/
	void GlutFramework::mouseMove(int x, int y) {
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
	void GlutFramework::keyboardDown( unsigned char key, int x, int y ) 
	{
		// Subclass and override this method
    std::ignore = x;
    std::ignore = y;
		printf( "KeyboardDown: %c = %d\n", key, (int)key );
		if (key==27) { //27 =- ESC key
			exit (0); 
		}
		
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
	void GlutFramework::keyboardUp( unsigned char key, int x, int y ) 
	{
		// Subclass and override this method
    std::ignore = x;
    std::ignore = y;
		printf( "KeyboardUp: %c \n", key );
		keyStates.keyUp( (int)key );
	}
	
  /*--------------------------------------------------------
  | The keyboard function is called when a special key 
  | is pressed down. (F1 keys, Home, Inser, Delete, 
  | Page Up/Down, End, arrow keys)
  | http://www.opengl.org/resources/libraries/glut/spec3/node54.html
  | 
  | @param key - the key press
  | @param x - the x coordinate of the mouse
  | @param y - the y coordinate of the mouse
  --------------------------------------------------------*/
	void GlutFramework::specialKeyboardDown( int key, int x, int y ) 
	{
		// Subclass and override this method
    std::ignore = x;
    std::ignore = y;
		printf( "SpecialKeyboardDown: %d\n", key );
	}
	
  /*--------------------------------------------------------
  | The keyboard function is called when a special key 
  | is released. (F1 keys, Home, Inser, Delete, 
  | Page Up/Down, End, arrow keys)
  | http://www.opengl.org/resources/libraries/glut/spec3/node54.html
  | 
  | @param key - the key press
  | @param x - the x coordinate of the mouse
  | @param y - the y coordinate of the mouse
  --------------------------------------------------------*/
	void GlutFramework::specialKeyboardUp( int key, int x, int y ) 
	{
		// Subclass and override this method	
    std::ignore = x;
    std::ignore = y;
		printf( "SpecialKeyboardUp: %d \n", key );
	}

	// ******************************
	// ** Graphics helper routines **
	// ******************************
	
  /*--------------------------------------------------------
  | Sets the intitial matricies that are used 
  | to setup OpenGL. 
  --------------------------------------------------------*/
	void GlutFramework::setDisplayMatricies() {
		/* Setup the projection and model view matricies */
		int width = glutGet( GLUT_WINDOW_WIDTH );
		int height = glutGet( GLUT_WINDOW_HEIGHT );
		float aspectRatio = width/height;
		glViewport( 0, 0, width, height );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective( 60, aspectRatio, 1, 500.0 );
		
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		gluLookAt(eyeVector.x, eyeVector.y, eyeVector.z,
				  centerVector.x, centerVector.y, centerVector.z,
				  upVector.x, upVector.y, upVector.z);
	}
	
  /*--------------------------------------------------------
  | Sets up basic lighting 
  --------------------------------------------------------*/
	void GlutFramework::setupLights() {
		GLfloat light1_position[] = { 0.0, 1.0, 1.0, 0.0 };
		GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
		GLfloat ambient_light[] = { 0.8, 0.8, 0.8, 1.0 };
		
		glLightfv( GL_LIGHT0, GL_POSITION, light1_position );
		glLightfv( GL_LIGHT0, GL_AMBIENT, ambient_light );
		glLightfv( GL_LIGHT0, GL_DIFFUSE, white_light );
		glLightfv( GL_LIGHT0, GL_SPECULAR, white_light );
		
		glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lmodel_ambient );
	}
	
  /*-------------------------------------------------------
  | A helper function that allows the camera position 
  | and orientation to be changed.
  |
  | @param eyeX, eyeY, eyeZ - 
  |   the vector describing the "eye" or camera position
  | @param centerX, centerY, centerZ - 
  |   the vector describing the "object" that the eye 
  |   is looking at
  | @param upX, upY, upZ - 
  |   the vector describing orientation. Normally (0,1,0)
  --------------------------------------------------------*/
	void GlutFramework::setLookAt(float eyeX, float eyeY, float eyeZ, 
                                float centerX, float centerY, float centerZ, 
                                float upX, float upY, float upZ) {
		
		eyeVector = Vector<float>(eyeX, eyeY, eyeZ);
		centerVector = Vector<float>(centerX, centerY, centerZ);
		upVector = Vector<float>(upX, upY, upZ);
	}
	
  /*-------------------------------------------------------
  | The position of the "eye" or camera in 3D space
  |
  | @return a 3D vector
  -------------------------------------------------------*/
	Vector<float> GlutFramework::getEyeVector() const {
		return eyeVector;
	}
	
  /*-------------------------------------------------------
  | The position that the "eye" or camera is looking at 
  | in 3D space
  | 
  | @return a 3D vector
  -------------------------------------------------------*/
	Vector<float> GlutFramework::getCenterVector() const {
		return centerVector;
	}
	
  /*-------------------------------------------------------
  | The up vector, used to determine orientation. 
  | Normally set to (0,1,0)
  | 
  | @return a 3D vector
  -------------------------------------------------------*/
	Vector<float> GlutFramework::getUpVector() const {
		return upVector;
	}
	
  /*-------------------------------------------------------
  | Sets the title of the window to a specific string. 
  | Invoke before startFramework()
  | 
  | @param title - the name of the window
  -------------------------------------------------------*/
	void GlutFramework::setTitle(std::string theTitle) {
		title = theTitle;
	}
	
  /*-------------------------------------------------------
  | Initializes GLUT and registers the callback 
  | functions. 
  -------------------------------------------------------*/
	void GlutFramework::init() {
		glClearColor(0.0, 0.0, 0.0, 1.0);
		
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		
		load();
	}
	
  /*-------------------------------------------------------
  | The instance will be set when the framework is 
  | started, this step is necessary to initialize the 
  | static instance that is used for the object 
  | oriented wrapper calls
  -------------------------------------------------------*/
	void GlutFramework::setInstance() {
		std::cout << "GlutFramework::setInstance()" << std::endl;
		instance = this;
	}
	
  /*-------------------------------------------------------
  | The run method is called by GLUT and contains the 
  | logic to set the framerate of the application. 
  -------------------------------------------------------*/
	void GlutFramework::run() {
		if(frameRateTimer.isStopped()) {	// The initial frame has the timer stopped, start it once
			frameRateTimer.start();
		}	
		
		frameRateTimer.stop();			// stop the timer and calculate time since last frame
		double milliseconds = frameRateTimer.getElapsedMilliseconds();
		frameTimeElapsed += milliseconds;
		
		if( frameTimeElapsed >= FRAME_TIME ) {	// If the time exceeds a certain "frame rate" then show the next frame
			glutPostRedisplay();
			frameTimeElapsed -= FRAME_TIME;		// remove a "frame" and start counting up again
		}
		frameRateTimer.start();			// start the timer
	}
	
  /*-------------------------------------------------------
  | The displayFramework() function sets up initial GLUT 
  | state and calculates the change in time between each 
  | frame. It calls the display(float) function which can
  | be subclassed.
  -------------------------------------------------------*/
	void GlutFramework::displayFramework() {
		if(displayTimer.isStopped()) {			// Start the timer on the initial frame
			displayTimer.start();
		}
		
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Clear once
		
		displayTimer.stop();		// Stop the timer and get the elapsed time in seconds
		elapsedTimeInSeconds = displayTimer.getElapsedSeconds(); // seconds
		
		setupLights();
		setDisplayMatricies();
		
		display(elapsedTimeInSeconds);
		
		glutSwapBuffers();
		displayTimer.start();		// reset the timer to calculate the time for the next frame
	}
	
	/**********************************************************
	* ~~ Static functions passed to Glut function callbacks ~~
	**********************************************************/
	void GlutFramework::displayWrapper() {
		instance->displayFramework(); 
	}
	
	void GlutFramework::reshapeWrapper(int width, int height) {
		instance->reshape(width, height);
	}
	
	void GlutFramework::runWrapper() {
		instance->run();
	}
	
	void GlutFramework::mouseButtonPressWrapper(int button, int state, int x, int y) {
		instance->mouseButtonPress(button, state, x, y);
	}
	
	void GlutFramework::mouseMoveWrapper(int x, int y) {
		instance->mouseMove(x, y);
	}
										 
	void GlutFramework::keyboardDownWrapper(unsigned char key, int x, int y) {
		instance->keyboardDown(key,x,y);
	}
	
	void GlutFramework::keyboardUpWrapper(unsigned char key, int x, int y) {
		instance->keyboardUp(key,x,y);
	}
	
	void GlutFramework::specialKeyboardDownWrapper(int key, int x, int y) {
		instance->specialKeyboardDown(key,x,y);
	}
	
	void GlutFramework::specialKeyboardUpWrapper(int key, int x, int y) {
		instance->specialKeyboardUp(key,x,y);
	}



  /*********************************************************
  * GlutFrameworkTri Sub-Class definition
  *********************************************************/

  /*-------------------------------------------------------
  | The display function is called at a specified 
  | frames-per-second (FPS). Any animation drawing code 
  | can be run in the display method.
  |
  | @param dTime - the change in time (seconds)
  --------------------------------------------------------*/
	void GlutFrameworkTri::display(float dTime) {

    (void) dTime;

		// DEMO: Create a teapot and move it 
    // back and forth on the y-axis
		glTranslatef(0.0f, position, 0.0f);
		glutSolidTeapot(2.5); 
		if(position > 4 && direction > 0) {
			direction = -1.0 / FRAME_TIME;
		} else if(position < -4 && direction < 0) {
			direction = 1.0 / FRAME_TIME;
		}		
		position += direction;
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
		// Subclass and override this method
    std::ignore = x;
    std::ignore = y;
		printf( "KeyboardDown: %c = %d\n", key, (int)key );

    // 27 = ESC , 113 = q 
		if( (key==27) || (key == 113) ){ 
			exit (0); 
		}
		
		keyStates.keyDown( (int)key );
	}
	
} // namespace

