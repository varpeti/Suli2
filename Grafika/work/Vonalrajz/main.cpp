#include <cstdlib>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


#define MAXARRAYSIZE 100
int xcoord[MAXARRAYSIZE];
int ycoord[MAXARRAYSIZE];

int wW;
int wH;

int actpoint;
int vastagsag=1;
int xx;
int yy;
int sipple;


void Init(){

	actpoint=-1;
	glViewport(0, 0, wW, wH);
    glMatrixMode(GL_MODELVIEW);    
    glLoadIdentity( );
    glMatrixMode(GL_PROJECTION);   
    glLoadIdentity( );
	gluOrtho2D(0.0, wW, wH, 0.0); 
	
	glLineStipple(1,0x3F07);
	sipple=0;
}

void ReDraw( ) { 
    glClearColor(1.0, 1.0, 1.0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    

	glColor3f(0.0,0.0,0.0);
	glLineWidth(vastagsag);

	if (sipple)
		glEnable(GL_LINE_STIPPLE);
	else
		glDisable(GL_LINE_STIPPLE);

	glBegin(GL_LINE_STRIP);
		for (int i=0;i<=actpoint;i++) {
			glVertex2i(xcoord[i],ycoord[i]);
		}
	glEnd( );
	
	glFlush( );
}


void reshape(int w, int h) {
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, wW, wH, 0.0); 
	wH=h;
}




int actMovePt=-1; //nincs aktuálisan mozgatandó pont
int isRighButtonPressed=0;
int movePoint=0;
int movePointOffsetX=0;
int movePointOffsetY=0;


//-1 ha nincs adott távnál közelebbi pont
int distThresh2=1000;
int ChooseClosestPoint(int x, int y) {
	int mindist2=wW*wW+wH*wH;
	int minind=-1;
	for (int i=0;i<=actpoint;i++) {
		int actDist2=(xcoord[i]-x)*(xcoord[i]-x)+(ycoord[i]-y)*(ycoord[i]-y);
		if (actDist2<distThresh2 && actDist2<mindist2) {
			mindist2=	actDist2;
			minind=i;
		}
	}

	printf("Mindist2: %d Minind: %d",mindist2,minind);

	return minind;
}

void Motion(int x, int y) {
	if (isRighButtonPressed && actMovePt>=0) {
		xcoord[actMovePt]=x+movePointOffsetX;
		ycoord[actMovePt]=y+movePointOffsetY;
		glutPostRedisplay();
	}
}


void MouseFunction(int button, int state, int x,int y) 
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && actpoint<MAXARRAYSIZE-1) {
		
		actpoint++;
		printf("actpoint: %d, x: %d, y: %d\n",actpoint, x,y);	
		xcoord[actpoint]=x;
		ycoord[actpoint]=y;
	}

	if (button == GLUT_RIGHT_BUTTON) {
		if  (state == GLUT_DOWN) {
			isRighButtonPressed=true;
			actMovePt=ChooseClosestPoint(x,y);
		} else {
			isRighButtonPressed=false;
			actMovePt=-1;
		}
	}

	glutPostRedisplay();
}






void Keyboard(unsigned char key, int x, int y) {
  
	switch(key) { 
		case 'c':
			actpoint=-1;
			break;
		case '1':
			vastagsag=1;
			break;
		case '2':
			vastagsag=2;
			break;
		case '3':
			vastagsag=3;
			break;
		case '4':
			vastagsag=4;
			break;
		case '5':
			vastagsag=5;
			break;
		case '6':
			vastagsag=6;
			break;
		case '7':
			vastagsag=7;
			break;
		case '8':
			vastagsag=8;
			break;
		case '9':
			vastagsag=9;
			break;
		case 's':
			sipple=(sipple+1)%2;
			break;
		case 27: 
			exit(0); 
			break; 
	   default: 
       break; 
   } 
	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	wW=400;
	wH=400;
    glutInitWindowSize(wW, wH);
    glutInitWindowPosition(100, 100);
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB );
    glutCreateWindow("DrawLine");
	Init();

    glutKeyboardFunc( Keyboard );
    glutDisplayFunc( ReDraw );
	glutMouseFunc(MouseFunction);
	glutMotionFunc(Motion);

	glutReshapeFunc(reshape);	
	// transzformáció
    glutMainLoop();

}