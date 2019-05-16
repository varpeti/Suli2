/*
 * File:  main.cpp
 * Author: Vp
 * Date: 17.02.21 (big endian)
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
std::vector<Svonal*> vonalak;
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

//Megkersesi a vonalak végei között melyik van a legközelebb, és vissza adja
Skoord* getClosestPoint(Skoord c)
{
    if (vonalak.size()<1) return nullptr;
    double mint = vonalak[0]->a|c;
    double mini = 0;
    bool   mina = true;
    for (int i = 0; i < vonalak.size(); ++i)
    {
        double tav = vonalak[i]->a|c;
        if (tav<mint) {mint=tav; mini=i; mina=true;}
        tav = vonalak[i]->b|c;
        if (tav<mint) {mint=tav; mini=i; mina=false;}
    }

    return mina ? vonalak[mini]->getAp() : vonalak[mini]->getBp();
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

    for (int i = 0; i < vonalak.size(); ++i)
    {
        glLineWidth(vonalak[i]->meret);
        glColor3d(vonalak[i]->szin.rr/255.0, vonalak[i]->szin.gg/255.0, vonalak[i]->szin.bb/255.0);
        glBegin(GL_LINES);
            glVertex2d(vonalak[i]->a.x, vonalak[i]->a.y);
            glVertex2d(vonalak[i]->b.x, vonalak[i]->b.y);
        glEnd();
    }

    glFlush();
}

//Egér mozgára aktiválódik, kurzorpozíció koordinátáit kapja bemenetnek
void Motion(int x, int y) {
    if (blent)
    {
        vonalak[vonalak.size()-1]->b = Skoord(x,y);
        glutPostRedisplay();
    }
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
            vonalak.push_back( new Svonal(Skoord(x,y),Skoord(x,y),vastag,Sszin(rand()%256,rand()%256,rand()%256)) );
            blent=true;
        } else { //fel
            vonalak[vonalak.size()-1]->b = Skoord(x,y);
            blent=false;
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
            vonalak.clear();
            break;
         case 'z':
            if (vonalak.size()>0) vonalak.pop_back();
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

