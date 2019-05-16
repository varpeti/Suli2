/*
 * File:   main_stepByStep.cpp
 * Author: polpe
 *
 * Created on February 10, 2014, 3:24 PM
 */

#include <cstdlib>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int winSizeX=400;
int winSizeY=400;

int offSetX=0;
int offSetY=0;
double angle=0;
float scale=1.0;

int sizeX=200;
int sizeY=200;


void Init(){
	glViewport(0, 0, 400, 400);
	glMatrixMode(GL_MODELVIEW);    
    	glLoadIdentity( );
	glMatrixMode(GL_PROJECTION);   
	glLoadIdentity( );
	gluOrtho2D(0., (GLfloat)sizeX, 0., (GLfloat)sizeY); 
}




int centerX=sizeX/2;
int centerY=sizeY/2;


int headsizeX=20;
int headsizeY=20;



void drawHead() {

	glColor3d( 0.0, 0.0, 1.0 );  
	glBegin(GL_POLYGON);
		glVertex2d(-headsizeX/2, -headsizeY/2);
		glVertex2d(-headsizeX/2, +headsizeY/2);
		glVertex2d(+headsizeX/2, +headsizeY/2);
		glVertex2d(+headsizeX/2, -headsizeY/2);
	glEnd( );
	
	glColor3d( 1.0, 0.0, 0.0 );  
	int eyeHalfSize=2;
	glBegin(GL_POLYGON);
		glVertex2d(-headsizeX/4-eyeHalfSize, headsizeY/4-eyeHalfSize);
		glVertex2d(-headsizeX/4-eyeHalfSize, headsizeY/4+eyeHalfSize);
		glVertex2d(-headsizeX/4+eyeHalfSize, headsizeY/4+eyeHalfSize);
		glVertex2d(-headsizeX/4+eyeHalfSize, headsizeY/4-eyeHalfSize);
	glEnd( );

	glBegin(GL_POLYGON);
		glVertex2d(headsizeX/4-eyeHalfSize, headsizeY/4-eyeHalfSize);
		glVertex2d(headsizeX/4-eyeHalfSize, headsizeY/4+eyeHalfSize);
		glVertex2d(headsizeX/4+eyeHalfSize, headsizeY/4+eyeHalfSize);
		glVertex2d(headsizeX/4+eyeHalfSize, headsizeY/4-eyeHalfSize);
	glEnd( );

	int szajhossz=headsizeX*0.8;

	glBegin(GL_POLYGON);
		glVertex2d(-szajhossz/2, -headsizeY/4-eyeHalfSize);
		glVertex2d(-szajhossz/2, -headsizeY/4+eyeHalfSize);
		glVertex2d(szajhossz/2, -headsizeY/4+eyeHalfSize);
		glVertex2d(szajhossz/2, -headsizeY/4-eyeHalfSize);
	glEnd( );

}






void ReDraw( ) { 
    glClearColor(1.0, 1.0, 1.0, 0.0); //háttérszín
    glClear(GL_COLOR_BUFFER_BIT);
    
	//Mindig az egység transtformációból indulunk - különben trnaszformációkat kompozitálná!
	glMatrixMode(GL_MODELVIEW);    
    glLoadIdentity( );


	//Mozgassuk a fejet a képernyõ középpontjába!
	glTranslated(centerX,centerY,0);
	glRotated(angle,0,0,1);
	glScalef(scale,scale,0);

	drawHead();

	glutSwapBuffers();

}



//Az ablak átméretezésénél skálázza a képet is
void reshape(int w, int h) {
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0., (GLfloat)sizeX, 0., (GLfloat)sizeY); 
}




void Keyboard(unsigned char key, int x, int y) {

	
	switch(key) {
		case 'w': centerY+=1; break;
		case 'a': centerX-=1; break;
		case 's': centerY-=1; break;
		case 'd': centerX+=1; break;
		case 'r': angle+=1.0; break;
		case 'f': angle-=1.0; break;
		case 'x': scale*=1.1; break;
		case 'y': scale*=0.9; break;
		case 27 : exit(0);
	}
	

	glutPostRedisplay(); //újra rajzolja ki az ablakot
}


int main(int argc, char* argv[])
{
    glutInitWindowSize(winSizeX, winSizeY);
    glutInitWindowPosition(100, 100);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("Transform");
	Init();

    glutKeyboardFunc( Keyboard );
    glutDisplayFunc( ReDraw );
	glutReshapeFunc(reshape);	
	
    glutMainLoop();

}




