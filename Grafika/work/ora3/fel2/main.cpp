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

int winSizeX=480;
int winSizeY=400;


int sizeX=240;
int sizeY=200;


void Init(){

    glViewport(0, 0, winSizeX, winSizeY);
    glMatrixMode(GL_MODELVIEW);    
    glLoadIdentity( );
    glMatrixMode(GL_PROJECTION);   
    glLoadIdentity( );
    gluOrtho2D(0., (GLfloat)sizeX, 0., (GLfloat)sizeY); 
    
}

int centerX=sizeX/2;
int centerY=30;

int ed=0;
int rf=0;
int tg=25;

int segmentSizeX=18;
int segmentSizeY=40;


void drawSegment() {
    
    glBegin( GL_LINE_LOOP );
        glVertex2d(-segmentSizeX/2, 0);
        glVertex2d(-segmentSizeX/2, segmentSizeY);
        glVertex2d(segmentSizeX/2, segmentSizeY);
        glVertex2d(segmentSizeX/2, 0);
    glEnd();
}




void ReDraw( ) { 
    glClearColor(1.0, 1.0, 1.0, 0.0); //háttérszín
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    glLineWidth(2);

        

    glMatrixMode(GL_MODELVIEW);    
    glLoadIdentity( );


    glTranslatef(centerX,centerY,0);//Uj origóba mozgatjuk

    glColor3f(0.0,0.0,0.0);

    drawSegment();

    glTranslatef(0,segmentSizeY,0);
    glRotated(ed,0,0,1); 
    drawSegment();

    glTranslatef(0,segmentSizeY,0);
    glRotated(rf,0,0,1); 
    drawSegment();

    glTranslatef(0,segmentSizeY,0);
    glRotated(tg,0,0,1);
    drawSegment();
    glRotated(-2*tg,0,0,1);
    drawSegment();

    glutSwapBuffers();

}



//Az ablak átméretezésénél skálázza a képet is
void reshape(int w, int h) {
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0., (GLfloat)sizeX, 0., (GLfloat)sizeY); 

}

int anglestep=5;


void Keyboard(unsigned char key, int x, int y) {

    
    switch(key) {
    
        case 'e': ed+=1; break;
        case 'd': ed-=1; break;
        case 'r': rf+=1; break;
        case 'f': rf-=1; break;
        case 't': tg+=1; break;
        case 'g': tg-=1; break;
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
    glutCreateWindow("Transform-RobotArm2D");
    Init();

    glutKeyboardFunc( Keyboard );
    glutDisplayFunc( ReDraw );
    glutReshapeFunc(reshape);   
    
    glutMainLoop();

}

