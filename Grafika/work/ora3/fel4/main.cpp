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

struct Obj
{
    float x;
    float y;
    float z;

    float pos_x;
    float pos_y;
    float pos_z;

    int ang_x;
    int ang_y;
    int ang_z;

    bool yp2;

    Obj()
    {
        x=0;y=0;z=0;
        pos_x=0;pos_y=0;pos_z=0;
        ang_x=0;ang_y=0;ang_z=0;
        yp2=true;
    }

    void draw()
    {
        glTranslated(pos_x,pos_y,pos_z);
        glRotated(ang_x,1,0,0);
        glRotated(ang_y,0,1,0);
        glRotated(ang_z,0,0,1);

        glPushMatrix();
        if (yp2) glTranslated(0,y/2,0);
        glScalef (x,y,z);
        glutWireCube (1.0);
        glPopMatrix();
    }
};

Obj base;
Obj c1;
Obj t1;
Obj c2;
Obj t2;
Obj t3;
Obj kamera;

void init(void) 
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);

    // base;
    base.x          = 1;
    base.y          = 0.35;
    base.z          = 1;
    base.pos_x      = 3;    // w s
    base.pos_z      = 0;    // a d
    // c1;
    c1.x            = 0.35;
    c1.y            = 1;
    c1.z            = 0.35;
    c1.pos_y        = 0.35;
    c1.ang_y        = 0;    // r f
    // t1;
    t1.x            = 0.2;
    t1.y            = 0.5;  // t g
    t1.z            = 0.2;
    t1.pos_y        = 1;
    // c2;
    c2.x            = 0.3;
    c2.y            = 2.5;
    c2.z            = 0.3;
    c2.pos_y        = 0.5;  // t g
    c2.pos_x        = -0.05;
    c2.ang_z        = 80;   // z h
    c2.yp2          = false;
    // t2;
    t2.x            = 0.3;
    t2.y            = 2.5;  // u j
    t2.z            = 0.3;
    t2.pos_y        = 1.2;
    // t3;
    t3.x            = 0.3;
    t3.y            = 2.5;  // i k
    t3.z            = 0.3;
    t3.pos_y        = 2.5;  // u j
    // kamera
    kamera.x        = 0.35;
    kamera.y        = 1;    // i k 
    kamera.z        = 0.35;
    kamera.pos_y    = 2.15;
    kamera.pos_x    = -0.5;
    kamera.ang_z    = 30;   // o l
}

void ReDraw(void)
{
    glClear (GL_COLOR_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0,-2.0,-5.0);
    
    base.draw();
    c1.draw();
    t1.draw();
    c2.draw();
    t2.draw();
    t3.draw();
    kamera.draw();
    
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
    switch (key) 
    {
        case 'w': base.pos_z-=0.1;              break;
        case 's': base.pos_z+=0.1;              break;
        case 'a': base.pos_x-=0.1;              break;
        case 'd': base.pos_x+=0.1;              break;
        case 'r': c1.ang_y-=1;                  break;
        case 'f': c1.ang_y+=1;                  break;
        case 't': t1.y+=0.1; c2.pos_y+=0.1;     break;
        case 'g': t1.y-=0.1; c2.pos_y-=0.1;     break;
        case 'z': c2.ang_z-=1;                  break;
        case 'h': c2.ang_z+=1;                  break;
        case 'u': t2.y+=0.1; t3.pos_y+=0.1;     break;
        case 'j': t2.y-=0.1; t3.pos_y-=0.1;     break;
        case 'i': t3.y+=0.1; kamera.pos_y+=0.1; break;
        case 'k': t3.y-=0.1; kamera.pos_y-=0.1; break;
        case 'o': kamera.ang_z-=1;              break;
        case 'l': kamera.ang_z+=1;              break;
        case 27: exit(0);                       break;

    }

    glutPostRedisplay();
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (1200, 800); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(ReDraw); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

