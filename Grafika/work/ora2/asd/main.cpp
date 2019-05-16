#include <cstdlib>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define MAXARRAYSIZE 100
#define ORDER 3

//Töröttvonal egyes pontjainak x ill y koordinátáit tartalmazó tömb: (lehet máshogy is reprezentálni...)
int xcoord[MAXARRAYSIZE];
int ycoord[MAXARRAYSIZE];
int db=0;

GLUnurbsObj *theNurb;
GLfloat ctrlpoints[MAXARRAYSIZE/2][3];
GLfloat knots[MAXARRAYSIZE/2+ORDER];

int drawt=0;
bool draw=true;
enum PTNUM {morept, lesspt, eqpt};
PTNUM PTNUM1=eqpt;

//Ablakméret:
int wH=400;
int wW=400;

struct point{
    int x;
    int y;
};

class MyPoint{
public:
    double x;
    double y;
    MyPoint(double a, double b) : x(a), y(b){
    }
    MyPoint(){
    }

};

point points[MAXARRAYSIZE/2];
point temp_point[MAXARRAYSIZE/2];
MyPoint ctrlPoint[MAXARRAYSIZE/2];
//GLfloat *ctrlpoints[MAXARRAYSIZE/2][3];

double knotVector[MAXARRAYSIZE/2];

bool knot=false;

double L( int i, double tt ) {
    double Li = 1.0;
    for(int j = 0; j < db; j++) {
        if (i != j) Li *= (tt - knotVector[j]) / (knotVector[i] -knotVector[j]);
    }
    return Li;
}

float B(int i, float t) {
    GLfloat Bi = 1.0;
    for(int j = 1; j <= i; j++) Bi *= t * (db-j)/j;
    for(int j=i+1 ; j < db; j++) Bi *= (1-t);
    return Bi;
}

MyPoint CalcLagrangePoint (float t) {
    MyPoint actPT(0.0,0.0);

    for(int i = 0; i <db; i++){
        actPT.x+=ctrlPoint[i].x*L(i,t);
        actPT.y+=ctrlPoint[i].y*L(i,t);
    }
return actPT;
}

MyPoint CalcBezierPoint (float t) {
    MyPoint actPT(0.0,0.0);
    for(int i = 0; i < db; i++) {
        actPT.x+=ctrlPoint[i].x*B(i,t);
        actPT.y+=ctrlPoint[i].y*B(i,t);
    }
    return actPT;
}

void SajatInit() {

}

void drawL() {
    for(int i=0; i<db; i++)
    {
        knotVector[i]=(double)i / (double(db-1));
    }

    for(int i=0; i<db; i++)
    {
        MyPoint a(0,0);
        MyPoint b(0,0);

        a=CalcLagrangePoint(0);
        for(double j=0.01; j<=1; j+=0.01){
            b=a;
            a=CalcLagrangePoint(j);
            glBegin(GL_LINES);
                glVertex2d(b.x,b.y);
                glVertex2d(a.x,a.y);
            glEnd();
        }
    }
}

void drawB() {
    for(int i=0; i<db; i++)
    {
        knotVector[i]=(double)i / (double(db-1));
    }

    for(int i=0; i<db; i++)
    {
        MyPoint a(0,0);
        MyPoint b(0,0);

        a=CalcBezierPoint(0);
        for(double j=0.01; j<=1; j+=0.01){
            b=a;
            a=CalcBezierPoint(j);
            glBegin(GL_LINES);
                glVertex2d(b.x,b.y);
                glVertex2d(a.x,a.y);
            glEnd();
        }
    }
}

void drawBGL() {
    for(int i=0; i<db; i++){
        ctrlpoints[i][0]=ctrlPoint[i].x;
        ctrlpoints[i][1]=ctrlPoint[i].y;
        ctrlpoints[i][2]=0;
    }
//    glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, db+1, ctrlpoints);
  //  glEvalCoord1f(0);
}

void drawN() {

    for(int i=0; i<db; i++)
    {
        knots[i]=(float)i / (float(db+ORDER));
    }

    theNurb=gluNewNurbsRenderer();
    glEnable(GLU_SAMPLING_TOLERANCE);
    gluNurbsProperty(theNurb,GLU_SAMPLING_TOLERANCE, 25.0);
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);

    gluBeginCurve(theNurb);
        gluNurbsCurve(theNurb,db+ORDER, knots,3,&ctrlpoints[0][0], ORDER,GL_MAP1_VERTEX_3);
    gluEndCurve(theNurb);
}

//void glMap1{fd}(Glenum target, TYPE u1, TYPE u2, GLInt stride, GLInt order, const TYPE * points)

//Újrarajzolás
void ReDraw( ) {
    //Fehér háttér:
    glEnable(GL_MAP1_VERTEX_3);
    glClearColor(1.0, 1.0, 1.0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    if(draw){
    glColor3d(0.0, 0.0, 0.0);

    switch(drawt) {
    case 1:
        drawL();
        break;
    case 2:
        drawB();
        break;
    case 3:
        drawBGL();
        break;
    case 4:
        drawN();
        break;

    default:
        glBegin(GL_LINE_STRIP);
            for(int i=0; i<db; i++)
                glVertex2d(ctrlPoint[i].x, ctrlPoint[i].y);
        glEnd();


        glFlush( );
        break;
    }

        glPointSize(8);
        glColor3d(1.0,0.0,0.0);
        glBegin(GL_POINTS);
            for(int i=0; i<db; i++)
                glVertex2d(ctrlPoint[i].x, ctrlPoint[i].y);
        glEnd();
    }

    glFlush( );
}





//Egér mozgára aktiválódik, kurzorpozíció koordinátáit kapja bemenetnek
void Motion(int x, int y) {


}


void MouseFunction(int button, int state, int x,int y)
{

    //bal gomb lenyomására
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN /*&& ... */) {
            ctrlPoint[db].x=x;
        ctrlPoint[db].y=y;
        db++;
        //db++

    }

    //jobb gomb lenyomására/felengedésére (lásd 2.2 feladat)
    if (button == GLUT_RIGHT_BUTTON) {
        if  (state == GLUT_DOWN) {
            /*...*/
        } else {
            /*...*/
        }
    }

    //A képernyő újrarajzolása (azaz redraw hívása)
    glutPostRedisplay();
}






void Keyboard(unsigned char key, int x, int y) {

    switch(key) {
        case 'l':
            draw=true;
            drawt=1;
            PTNUM1=eqpt;
            break;
        case 'm':
            draw=true;
            drawt=0;
            PTNUM1=eqpt;
            break;
        case 'b':
            draw=true;
            drawt=2;
            PTNUM1=eqpt;
            break;
      /*  case 'v':
            draw=true;
            drawt=3;
            break;*/
        case 'h':
            draw=true;
            drawt=4;
            PTNUM1=eqpt;
            break;
        case 'j':
            draw=true;
            PTNUM1=lesspt;
            break;
        case 'n':
            draw=true;
            PTNUM1=morept;
            break;
        case 'c':
            draw=false;
            break;
        case 27:
            exit(0);
            break;
       default:
       break;
   }
    //A képernyő újrarajzolása (azaz redraw hívása)
    glutPostRedisplay();
}



//--------------------------
//  Keret (nem kell módosítani)

//Inicializálás
void Init(){
    glViewport(0, 0, wW, wH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0.0, wW, wH, 0.0);
    SajatInit();
}

//Ablak átméretezésekor a teljes képet skálázza
void reshape(int w, int h) {
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, wW, wH, 0.0);
    wW=w;
    wH=h;
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
    glutMainLoop();
}

