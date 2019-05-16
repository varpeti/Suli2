#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



GLfloat mat_ambient1[]   = { 1.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient2[]   = { 0.0, 1.0, 0.0, 1.0 };
GLfloat mat_ambient3[]   = { 0.0, 0.0, 1.0, 1.0 };
GLfloat mat_diffuse[]    = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[]   = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[]  = { 200.0              };
GLfloat light_position[] = { 2.0, 2.0, 2.0, 0.0 };

void redraw(void)
{

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
    glTranslated(0.0, 0.0, -10);
    glutSolidCube(10);
    glTranslated(0.0, 0.0, 10);

    glRotated(20,1,0.3,0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
    glTranslated(0.0, -6.0, 0.0);
    glutSolidCube(10);
    glTranslated(0.0, 6.0, 0.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
    glTranslated(0.0, -0.5, -1.0);
    glutSolidTeapot(1.0);
    glTranslated(0.0, 0.5, 1.0);
    glRotated(-20,1,0.3,0.0);

    glFlush();
}

void init()
{
    redraw();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) 
    {
        case 27:
            exit(0);
            break;
        case 'a':
            light_position[0]+=1;
            break;
        case 'd':
            light_position[0]-=1;
            break;
        case 'w':
            light_position[1]+=1;
            break;
        case 's':
            light_position[1]-=1;
            break;
        case 'q':
            light_position[2]+=1;
            break;
        case 'e':
            light_position[2]-=1;
            break;
    }
    redraw();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
