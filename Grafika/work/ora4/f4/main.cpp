#include <cstdlib>
#include <iostream>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define MAXPTNUM 100


double knotVector[MAXPTNUM];
GLfloat ctrlpoints[MAXPTNUM][3];

int	sizeX;
int	sizeY;

int ptnum;

bool animate=false;


double lpx = 0;
double lpy = 0;
double px = 0;
double py = 0;
int vx = 0;

double t_par=0;
double felosztas=1000;
void init(void)
{


   glClearColor(1.0, 1.0, 1.0, 1.0);
   glShadeModel(GL_FLAT);

   glEnable(GL_MAP1_VERTEX_3);

   glViewport(0, 0, (GLsizei) sizeX, (GLsizei) sizeY);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

  gluOrtho2D(0,sizeX,sizeY,0);

   ptnum=0;
}

double L( int i, double tt ) {
	double Li = 1.0;
	for(int j = 0; j < ptnum; j++) {
		if (i != j) Li *= (tt - knotVector[j]) / (knotVector[i] -knotVector[j]);
	}
	return Li;
}


void keyboard(unsigned char key, int x, int y)
{
	switch(key) {

		case 's':
			animate=true;
			/*init animation*/
			break;

		case 'd':
			animate=false;
		break;


	}
}


void DrawLagrangePoint(float t) {

	GLfloat ptx=0; GLfloat pty=0;
      for(int i = 0; i < ptnum; i++) {
		double lit= L(i,t);
		ptx+=ctrlpoints[i][0]*L(i,t);
		pty+=(ctrlpoints[i][1])*L(i,t);
	}
	glVertex2f(ptx,pty);
}

void CalcLagrangePoint(float t, double *xcoord,double *ycoord) {
	GLfloat ptx=0; GLfloat pty=0;
      for(int i = 0; i < ptnum; i++) {
		double lit= L(i,t);
		ptx+=ctrlpoints[i][0]*L(i,t);
		pty+=(ctrlpoints[i][1])*L(i,t);
	}
	*xcoord=ptx;
	*ycoord=pty;
}

int actMovePt=-1;
int isRighButtonPressed=0;
int movePoint=0;
int movePointOffsetX=0;
int movePointOffsetY=0;


int distThresh2=1000;
int ChooseClosestPoint(int x, int y) {
	int mindist2=sizeX*sizeX+sizeY*sizeY;
	int minind=-1;
	for (int i=0;i<=ptnum;i++) {
		int actDist2=(ctrlpoints[i][0]-x)*(ctrlpoints[i][0]-x)+(ctrlpoints[i][1]-y)*(ctrlpoints[i][1]-y);
		if (actDist2<distThresh2 && actDist2<mindist2) {
			mindist2=	actDist2;
			minind=i;
		}
	}

	return minind;
}

void Motion(int x, int y) {
	if (isRighButtonPressed && actMovePt>=0) {
		ctrlpoints[actMovePt][0]=x+movePointOffsetX;
		ctrlpoints[actMovePt][1]=y+movePointOffsetY;
		glutPostRedisplay();
	}
}

void MouseFunction(int button, int state, int x,int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		ptnum++;
		ctrlpoints[ptnum-1][0]=x;
		ctrlpoints[ptnum-1][1]=y;
		ctrlpoints[ptnum-1][2]=0;


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


void Step() {
	if (animate) {

        if (vx<999) {
            vx++;
            lpx=px;
            lpy=py;
        }else animate=false;
        CalcLagrangePoint(((float)vx)/((float)(1000-1)),&px,&py);
        


		/*Step the animation before rendering the new scene*/
		glutPostRedisplay();
	}
}


void display(void)
{
   int i;



   for (int i=0;i<ptnum;i++) {
		knotVector[i]=(double)i/(double(ptnum-1));
   }

   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0, 0.0, 0.0);


   int beosztas=100;

   if (ptnum>=2) {
	glBegin(GL_LINE_STRIP);
	for (int i=0;i<beosztas;i++) {
		DrawLagrangePoint(((float)i)/((float)(beosztas-1)));
	}
	glEnd();
   }


   if (animate) {

		/*Draw car in correct position*/
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        int e = 0;
        if      (lpx<=px and lpy>=py) { e=2*M_PI;}
        else if (lpx>=px and lpy>=py) { e=1*M_PI;}
        else if (lpx>=px and lpy<=py) { e=1*M_PI;}
        int szog = (atan((lpy-py)/(lpx-px))+e)/M_PI*180;
        std::cout << szog << "\n";
        glTranslated(px,py,0);
        glRotated(szog,0,0,1);

        glBegin(GL_POLYGON);
            glVertex2d(-5, -5);
            glVertex2d(+7, -5);
            glVertex2d(+7, +5);
            glVertex2d(-5, +5);
        glEnd();

        glRotated(-szog,0,0,1);
        glTranslated(-px,-py,0);
        


   }
   else {
	glPointSize(8.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (i = 0; i < ptnum; i++)  {
		glVertex3fv(&ctrlpoints[i][0]);

	}
	glEnd();
   }

   glFlush();
	glutSwapBuffers();
}




int main(int argc, char* argv[])
{
	sizeX=500;
	sizeY=500;

   glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowSize (sizeX, sizeY);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutMouseFunc(MouseFunction);
   glutMotionFunc(Motion);
   glutKeyboardFunc (keyboard);
   glutIdleFunc(Step);
   glutMainLoop();
   return 0;
}



