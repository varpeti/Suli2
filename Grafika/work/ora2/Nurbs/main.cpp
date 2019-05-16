/*
 * File:  main.cpp
 * Author: Vp
 */

#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "env.hpp"

  //-----------------//
 //Globális változók//
//-----------------//

//Vonal vector
std::vector<Skoord*> vonal;
//Tárolja h le van e nyomva
bool blent;
bool jlent;
//Kövi vastagsága
unsigned int vastag;
//Arrébb mozgatandó pont
Skoord * arrab;

//Ablakméret:
int XX=800;
int YY=600;

  //----------//
 //Függvények//
//----------//

//Megkersesi a vonal pontjai között melyik van a legközelebb, és vissza adja
Skoord* getClosestPoint(Skoord c)
{
    if (vonal.size()<1) return nullptr;
    double mint = *vonal[0]|c;
    double mini = 0;
    for (int i = 0; i < vonal.size(); ++i)
    {
        double tav = *vonal[i]|c;
        if (tav<mint) {mint=tav; mini=i;}
    }

    return vonal[mini];
}

void drawNurbs(const std::vector<Skoord*> &pontok)
{
    const int ORDER = 3;
    GLfloat knots[pontok.size()+ORDER];
    GLfloat ctrlpoints[pontok.size()*2][3];

    for(int i=0; i<pontok.size()+ORDER; i++)
    {
        knots[i]=(float)i / (float(pontok.size()+ORDER));
        if (i<pontok.size())
        {
            ctrlpoints[i][0]=pontok[i]->x;
            ctrlpoints[i][1]=pontok[i]->y;
            ctrlpoints[i][2]=0;
        }
    }

    GLUnurbsObj *theNurb=gluNewNurbsRenderer();
    glEnable(GLU_SAMPLING_TOLERANCE);
    gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);

    gluBeginCurve(theNurb);
        gluNurbsCurve(theNurb,pontok.size()+ORDER, knots,3,&ctrlpoints[0][0], ORDER, GL_MAP1_VERTEX_3);
    gluEndCurve(theNurb);
}

  //------------------//
 //Esemeny függvények//
//------------------//

void SajatInit() {
    vastag = 2;
    arrab = nullptr;
}

//Újrarajzolás
void ReDraw( ) {
    glClearColor(0.0, 0.0, 0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(1, 1, 1);
    drawNurbs(vonal);

    for (int i = 0; i < vonal.size(); ++i)
    {
        glColor3d(1, 0, 0);
        glBegin(GL_POLYGON);
            glVertex2d(vonal[i]->x-5, vonal[i]->y-5);
            glVertex2d(vonal[i]->x+5, vonal[i]->y-5);
            glVertex2d(vonal[i]->x+5, vonal[i]->y+5);
            glVertex2d(vonal[i]->x-5, vonal[i]->y+5);
        glEnd();
    }

    glFlush();
}

//Egér mozgásra aktiválódik, kurzorpozíció koordinátáit kapja bemenetnek
void Motion(int x, int y) {
    if (jlent && arrab!=nullptr)
    {
        arrab->x = x;
        arrab->y = y;
        glutPostRedisplay();
    }
    
}

void MouseFunction(int button, int state, int x,int y)
{

    //bal gomb lenyomására
    if (button == GLUT_LEFT_BUTTON) {
        if  (state == GLUT_DOWN) { //le
            vonal.push_back( new Skoord(x,y) );
        } else { //fel 
        }
    }

    //jobb gomb lenyomására/felengedésére (lásd 2.2 feladat)
    if (button == GLUT_RIGHT_BUTTON) {
        if  (state == GLUT_DOWN) { //le
            arrab = getClosestPoint(Skoord(x,y));
            jlent=true;
        } else { //fel
            arrab=nullptr;
            jlent=false;
        }
    }

    //A képernyő újrarajzolása (azaz redraw hívása)
    glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {

    switch(key) {
        case 'c':
            vonal.clear();
            break;
         case 'z':
            if (vonal.size()>0) vonal.pop_back();
            break;
        case 27:
            exit(0);
            break;
       default:
            break;
    }
    if (key>48 and key<60) vastag=key-48;

    //A képernyő újrarajzolása (azaz redraw hívása)
    glutPostRedisplay();
}

  //-----//
 //Keret//
//-----//

//Inicializálás
void Init(){
    glViewport(0, 0, XX, YY);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0.0, XX, YY, 0.0);
    SajatInit();
}

//Ablak átméretezésekor a teljes képet skálázza
void reshape(int w, int h) {
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w, h, 0.0);
    XX=w;
    YY=h;
}

int main(int argc, char* argv[])
{
    glutInitWindowSize(XX, YY);
    glutInitWindowPosition(100, 100);
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB );
    glutCreateWindow("DrawLine by Vp");
    Init();

    glutKeyboardFunc( Keyboard );
    glutDisplayFunc( ReDraw );
    glutMouseFunc(MouseFunction);
    glutMotionFunc(Motion);
    glutReshapeFunc(reshape);
    glutMainLoop();
}

