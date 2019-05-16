#include <cstdlib>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

unsigned int objID = 7;

void Init(){

	GLfloat light_position[] = {0.0, 0.0, -1.0, 1.0 };

	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
	glEnable(GL_LIGHT0);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
}



void ReDraw( ) {

	glEnable(GL_LIGHTING);
	glClearColor (1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glRotatef(-20, 1.0, 0.0, 0.0);
	glRotatef(30, 0.0, 1.0, 0.0);

	float GreenSurface[]={1.0,0.0,0.0,1.0};
	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,GreenSurface);

	/*
	Ide kell írni a GLUT rajzoló primitíveket
	*/
    switch(objID) {
        case 0: glutSolidTeapot(0.5); break;
        case 1: glutWireTeapot(0.5); break;
        case 2: glutSolidCube(1); break;
        case 3: glutWireCube(1); break;
    }

	glutSwapBuffers();
}


void reshape(int w, int h) {
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,100,0.0,100);
}





void MenuFunc(int menuItemIndex) {


	/*Itt ki kell egészíteni az egyes eseteket!!!*/
	objID=menuItemIndex;
    if (objID==4) exit(0);

	glutPostRedisplay();

}
int main(int argc, char* argv[])
{
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH );
    glutCreateWindow("MenuDraw");

	Init();

    glutDisplayFunc( ReDraw );



	/*
	Ide kell implementálni a menü létrehozását
	*/

    int submenu=glutCreateMenu(MenuFunc);
    glutAddMenuEntry("Tömör teáskanna",0);
    glutAddMenuEntry("Drótváz teáskanna",1);
    glutAddMenuEntry("Tömör kocka",2);
    glutAddMenuEntry("Drótváz kocka",3);
    glutCreateMenu(MenuFunc);
    glutAddSubMenu("Alakzat",submenu);
    glutAddMenuEntry("Exit",4);
    glutAddMenuEntry("About",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();

}