#include <stdio.h>
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <GL/glut.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <math.h>
#include <iostream>
/* display function - GLUT display callback function
 *		clears the screen, draws a square, and displays it
 */
int flag = 0;
float window_width = 300.0f;
float window_height = 300.0f;
int formerX = -1;
int formerY = -1;
int cSwitch = 1;


float cMXSX(float x){
  return ((float)x)/window_width*2.0f - 1.0f;
}
float cMYSY(float y){
  return 1.0f - ((float)y)/window_height*2.0f;
}

float getRadius(int initX, int initY, int x, int y){
  return
  	sqrt((y-initY)*(y-initY) + (x-initX)*(x-initX));
}

void drawPoint(int x, int y){
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex2f((x - glutGet(GLUT_WINDOW_WIDTH)/2.0 )/(glutGet(GLUT_WINDOW_WIDTH)/2.0),
		-(y - glutGet(GLUT_WINDOW_HEIGHT)/2.0 )/(glutGet(GLUT_WINDOW_HEIGHT)/2.0));
		glEnd();
		glFlush();
	}

//draws a Line using bresenhams's Algorithm

void drawLine (int x0, int y0, int x1, int y1) {
								//adds exception for the case of vertical lines
	if (x0==x1) {
		if (y0<y1){
		while (y0<y1) {
			drawPoint(x0,y0+1);
			y0=y0+1; }}
		else if (y1<y0) {
			while (y1<y0) {
			drawPoint(x0,y1+1);
			y1=y1+1; }}}

	else {
	 glPointSize(5);
     glBegin(GL_POINTS);

     float deltax = x1 - x0;
     float deltay = y1 - y0;
     float error = 0.0f;
     float deltaerr = abs (deltay / deltax);
     int y = y0;

     bool checkifIncrease = (x1 >= x0)? true:false;
  for(int x = x0; (checkifIncrease)? (x < x1):(x > x1); (checkifIncrease)? (x++):(x--)) {
  		glVertex2f((x - glutGet(GLUT_WINDOW_WIDTH)/2.0 )/(glutGet(GLUT_WINDOW_WIDTH)/2.0),
		-(y - glutGet(GLUT_WINDOW_HEIGHT)/2.0 )/(glutGet(GLUT_WINDOW_HEIGHT)/2.0));

         error = error + deltaerr;
         while (error >= 0.5) {
             glVertex2f((x - glutGet(GLUT_WINDOW_WIDTH)/2.0 )/(glutGet(GLUT_WINDOW_WIDTH)/2.0),
		-(y - glutGet(GLUT_WINDOW_HEIGHT)/2.0 )/(glutGet(GLUT_WINDOW_HEIGHT)/2.0));
             y = y + (y1-y0)/abs(y1-y0);

                error = error - 1.0f ;}
        }
        glEnd ();
        glFlush();}




}

//draws a Rectangle given two corners
void drawRectangle(int x1, int y1, int x0, int y0 ) {


	drawLine (x0, y0, x1, y0);
	drawLine (x0, y0, x0, y1);
	drawLine (x1, y0, x1, y1);
	drawLine (x0, y1, x1, y1);

	if (y0<y1) {
	while (y0<y1) {

		drawPoint(x0,y0);
		drawPoint(x1,y0);
		y0=y0+1;
	}}

	else if (y1<y0) {
		while (y1<y0) {

		drawPoint(x0,y1);
		drawPoint(x1,y1);
		y1=y1+1;
	}}
}
void drawCircle(int toX, int toY){
  glPointSize(5);
  glBegin(GL_POINTS);

  int radius = getRadius(formerX, formerY, toX, toY); // get the radius
  int x0 = formerX;
  int y0 = formerY;
  int x = radius;
  int y = 0;
  int checkAfter2 = 1 - x;

  while(y <= x){
    glVertex2f(cMXSX((float)x + x0), cMYSY((float)(y+y0)));
    glVertex2f(cMXSX((float)y + x0), cMYSY((float)(x+y0)));
    glVertex2f(cMXSX((float)-x + x0), cMYSY((float)(y+y0)));
    glVertex2f(cMXSX((float)-y + x0), cMYSY((float)(x+y0)));
    glVertex2f(cMXSX((float)-x + x0), cMYSY((float)(-y+y0)));
    glVertex2f(cMXSX((float)-y + x0), cMYSY((float)(-x+y0)));
    glVertex2f(cMXSX((float)x + x0), cMYSY((float)(-y+y0)));
    glVertex2f(cMXSX((float)y + x0), cMYSY((float)(-x+y0)));
    y++;
    if(checkAfter2<=0)
      checkAfter2 += 2 * y + 1;
    else{
       x--;
       checkAfter2 += 2 * (y-x) + 1;
    }
  }// end while
  glEnd();
  glFlush();

  //restore the x and y values from prevous
  formerX = -1;
  formerY = -1;
}// end function
void display(void)
{glFlush();
}

//clears screen after selecting and clicking the screen
void clearScreen(){
  glColor3f(0.0f, 0.0f, 0.0f);
  glPointSize(1);
  glBegin(GL_POINTS);
    for(int x = 0; x < window_width; x++){
      for(int y = 0; y < window_height; y++){
        glVertex2f(cMXSX((float)x), cMYSY((float)y));
      }
    }
  glEnd();
  glFlush();
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 27: //escape key with fall through
		case 'q':
			exit(0);
			break;

		case 'a':
			glColor3f(0.0f, 0.0f,1.0f);
			break;

		case 'd':
			glColor3f(1.0f, 0.0f,0.0f);
			break;

		default:
			break;
	}
}

void special(int key, int x, int y){
	switch(key){
		case GLUT_KEY_LEFT:
			glColor3f(0.0f, 0.0f,1.0f);
			flag = 0;
			break;

		case GLUT_KEY_RIGHT:
			glColor3f(1.0f, 0.0f,0.0f);
			flag = 1;
			break;

		default:
			break;
	}
}

void reshape(int w, int h){
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluOrtho2D(0, w, 0, h);

	//glMatrixMode(GL_MODELVIEW);
	//glViewport(0, 0, w, h);
}

bool z = true;
void mouse(int btn, int state, int x, int y){
	/* printf("mouse: %i,%i\n", x, y); */
	switch(btn){

		case GLUT_LEFT_BUTTON:
			if(state==GLUT_DOWN){

				switch(cSwitch) {

				case 5:
					drawPoint(x,y);
					break;
				case 6:

					if (z==true) {

					formerX = x;
					formerY = y;


					z=false; }
					else {
					drawLine(x,y,formerX,formerY);
					z=true;
					}
					break;
				case 7:
					if (z==true) {

					formerX = x;
					formerY = y;


					z=false; }
					else {
					drawRectangle(x,y,formerX,formerY);
					z=true;
					}
					break;
				case 8:
					if(formerX == -1 && formerY == -1){
        			formerX = x;
        			formerY = y;
        			break;
      }
					drawCircle(x,y);
					break;

				case 1:
				 break;


				}}

			break;

	}



}

void motion(int x,int y){
	/* printf("motion: %i,%i\n", x, y); */
	drawPoint(x,y);   //continuously draw points by clicking and dragging
}

/* void passive(int x,int y){ */
/* 	printf("passive: %i,%i\n", x, y); */
/* } */

void timerRedisplay(int value){
	glutTimerFunc(32, timerRedisplay, 0);
	display();
}

void randColour(int value){
	/* printf("menu action\n"); */
	switch(value){
		case 0:
			glColor3f(1.0f, 0.0f,0.0f); //Red
			break;

		case 1:
			glColor3f(0.0f, 1.0f,0.0f); //Green
			break;

		case 2:
			glColor3f(0.0f, 0.0f,1.0f); //Blue
			break;

		case 3:
			glColor3f(0.8f, 0.0f,1.0f); //Purple
			break;

		case 4:
			glColor3f(1.0f, 1.0f,0.1f); //Yellow
			break;
	}
}


void menu(int value){
	/* printf("menu action\n"); */
	switch(value){
		case 0:
			glColor3f(1.0f, 0.0f,0.0f); //Red
			break;

		case 1:
			glColor3f(0.0f, 1.0f,0.0f); //Green
			break;

		case 2:
			glColor3f(0.0f, 0.0f,1.0f); //Blue
			break;

		case 3:
			glColor3f(0.8f, 0.0f,1.0f); //Purple
			break;

		case 4:
			glColor3f(1.0f, 1.0f,0.1f); //Yellow
			break;

		case 5:
			cSwitch=5;//Point
			break;
		case 6:
			cSwitch=6;//line
			break;

		case 7:
			cSwitch=7;//Rectangle
			break;

		case 8:
			cSwitch=8;//Circle
			break;
		case 9:
			clearScreen();
			break;
		case 10:	//exit program
			exit(0);
			break;
		case 11:
			randColour(rand()%4+0);
			break;


	}
}

//inits
void glutCallbacks(){
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	/* glutPassiveMotionFunc(passive); */
}
//creates the menus
void initMenu(){

         int submenu1, submenu2;

         submenu1 = glutCreateMenu(menu);
         glutAddMenuEntry("Red", 0);
         glutAddMenuEntry("Green", 1);
         glutAddMenuEntry("Blue", 2);
         glutAddMenuEntry("Purple", 3);
         glutAddMenuEntry("Yellow", 4);
         glutAddMenuEntry ("Random Colour",11);
         submenu2 = glutCreateMenu(menu);
         glutAddMenuEntry("Point", 5);
         glutAddMenuEntry("Line", 6);
         glutAddMenuEntry("Rectangle", 7);
         glutAddMenuEntry("Circle", 8);
         glutCreateMenu(menu);
         glutAddSubMenu("Colours", submenu1);
         glutAddSubMenu("Shape", submenu2);
         glutAddMenuEntry("clearScreen", 9);
         glutAddMenuEntry("exit", 10);
         glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//main
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	glutCreateWindow("square");	//creates the window
    clearScreen(); //initalize a cleared screen
	//register callbacks
	glutCallbacks();
	initMenu(); //initialize menu

	//timerRedisplay(10);

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}
