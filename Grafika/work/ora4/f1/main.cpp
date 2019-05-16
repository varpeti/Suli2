#include <cstdlib>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int winSizeX=400;
int winSizeY=400;

int offSetX=0;
int offSetY=0;
int angle=0;

int sizeX=100;
int sizeY=100;

int radius=5;


double posX=sizeX/2;
double posY=sizeY/2;
double vx = 0.5;
double vy = 0.3;




GLUquadricObj *qobj;


void Init(){

	glViewport(0, 0, 400, 400);
    glMatrixMode(GL_MODELVIEW);    
    glLoadIdentity( );
    glMatrixMode(GL_PROJECTION);   
    glLoadIdentity( );
    gluOrtho2D(0., 100., 0., 100.); 
	
}


void ReDraw( ) { 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


    glClearColor(1.0, 1.0, 1.0, 0.0); //háttérszín
	glClear(GL_COLOR_BUFFER_BIT);
    

	int centerX=sizeX/2;
	int centerY=sizeY/2;

	glColor3d( 0.0, 0.0, 1.0 );  
	
	glTranslated(posX,posY,0);

	qobj = gluNewQuadric();
	gluDisk(qobj, 0,radius,30,30);
	
	glFlush( ); //Azonnal jelenítse meg
	glutSwapBuffers();
	
}




void Step() {
  /*Move the ball, and response for collision*/

    if ((posX+vx+radius/2)>sizeX or (posX+vx-radius/2)<0 ) {vx=-vx; std::cout << "utk \n";} 
    if ((posY+vy+radius/2)>sizeY or (posY+vy-radius/2)<0 ) {vy=-vy; std::cout << "utk \n";} 

    posX+=vx;
    posY+=vy;

  glutPostRedisplay();   //display scene
}



//Az ablak átméretezésénél skálázza a képet is
void reshape(int w, int h) {
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0,100,0.0,100,-1,1);
	
}



int main(int argc, char* argv[])
{
    glutInitWindowSize(winSizeX, winSizeY);
    glutInitWindowPosition(500, 100);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("MoveBall");
	Init();
    glutDisplayFunc(ReDraw);
	glutReshapeFunc(reshape);	
	
	glutIdleFunc(Step);

    glutMainLoop();

}






