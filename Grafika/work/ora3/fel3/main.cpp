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

int angle_joint1 = 0;
int angle_joint2 = 0;
int base_angle=0;

void init(void) 
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void drawSegment() {

    glPushMatrix();
    glTranslated(0,0.7,0);
    glScalef (0.5, 1.4, 0.5);
    glutWireCube (1.0);
    glPopMatrix();

}
void ReDraw(void)
{
    glClear (GL_COLOR_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslated(0,-2.0,0);
    glTranslatef (0.0, 0.0, -5.0);
    glRotated(base_angle,0,1,0);

    drawSegment();

    glTranslatef(0,1.4,0);
    glRotated(angle_joint1,0,0,1); 
    drawSegment();

    glTranslatef(0,1.4,0);
    glRotated(angle_joint2,0,0,1); 
    drawSegment();
    
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 'w': angle_joint1+=1; break;
        case 's': angle_joint1-=1; break;
        case 'e': angle_joint2+=1; break;
        case 'd': angle_joint2-=1; break;
        case 'r': base_angle+=1; break;
        case 'f': base_angle-=1; break;
        case 27: exit(0); break;
    }

    glutPostRedisplay();
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (600, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(ReDraw); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

