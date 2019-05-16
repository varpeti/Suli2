#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int ambient = 0;
int shininess = 0;
int diffuse = 0;
int specular = 0;
int emission = 0;
int obj = 0;
int light_controll = 0;

GLfloat no_mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
GLfloat no_mat_diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat no_mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat no_shininess[] = { 0.0 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat no_mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };
GLfloat light_position[] = { 2.0, 2.0, 2.0, 0.0 };

void redraw(void)
{

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    switch (ambient) 
    {
        case 0:
            glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat_ambient);
            break;
        case 1:
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
            break;
        case 2:
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
            break;
    }
    switch (specular) 
    {
        case 0:
            glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat_specular);
            break;
        case 1:
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            break;
    }
    switch (diffuse) 
    {
        case 0:
            glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat_diffuse);
            break;
        case 1:
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
            break;
    }
    switch (shininess) 
    {
        case 0:
            glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
            break;
        case 1:
            glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
            break;
        case 2:
            glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
            break;
    }

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (obj) 
    {
        case 0:
            glutSolidSphere(1.0, 40, 32);
            break;
        case 1:
            glutSolidTorus(0.275, 0.85, 16, 30);
            break;
        case 2:
            glTranslated(-1.2, 0.0, 0.0);
                glutSolidSphere(1.0, 40, 32);
            glTranslated(2.4, 0.0, 0.0);
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
                glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat_diffuse);
                glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
                glutSolidSphere(1.0, 40, 32);
            glTranslated(-1.2, 0.0, 0.0);
            break;
    }

    glTranslated(light_position[0], light_position[1], light_position[2]);
        glutWireCube(.1);
    glTranslated(-light_position[0], -light_position[1], -light_position[2]);

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
        case 'q':
            ambient++;
            if (ambient > 2)
                ambient = 0;
            break;
        case 'w':
            shininess++;
            if (shininess > 2)
                shininess = 0;
            break;
        case 'e':
            diffuse++;
            if (diffuse > 1)
                diffuse = 0;
            break;
        case 'r':
            specular++;
            if (specular > 1)
                specular = 0;
            break;
        case 't':
            emission++;
            if (emission > 1)
                emission = 0;
            break;
        case 'z':
            obj++;
            if (obj > 2)
                obj = 0;
            break;
        case 'a':
            if (light_controll == 1) 
            {
                light_controll = 0;
            }
            else if (light_controll == 0)
            {
                light_position[0] = 0.0;
                light_position[1] = 0.0;
                light_position[2] = 0.0;
                light_controll = 1;
            }

            break;
    }
    redraw();
}

int time = 0;

void step()
{
    time++;
    if (light_controll != 0) return;
    light_position[0] = sin(time / 7570.0) * 20;
    light_position[1] = cos(time / 7610.0) * 20;
    light_position[2] = sin(time / 9070.0) * 20;
    redraw();
}

void MouseFunction(int x, int y)
{
    if (light_controll != 1) return;
    light_position[2] = (x-250)/1000.0;
    light_position[1] = (250-y)/100.0;
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
    glutMotionFunc(MouseFunction);
    glutIdleFunc(step);
    glutMainLoop();
    return 0;
}
