#include <cstdlib>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "sstream"
#include "vector"
#include "time.h"
#include "math.h"
#include "iostream"

using namespace std;

int XX = 800;
int YY = 600;
bool teljes = false;

const double maximumsebesseg = 10;

struct Skoordinatak
{
    double x;
    double y;

    Skoordinatak (double ux, double uy) 
    {
        x=ux;
        y=uy;
    };

    Skoordinatak () 
    {};

};

void kor(Skoordinatak pozicio, double sugar)
{
    glTranslated(pozicio.x,pozicio.y,0);
    GLUquadricObj *qobj = gluNewQuadric();
    gluDisk(qobj, 0,sugar,30,30);
    glTranslated(-pozicio.x,-pozicio.y,0);
}

struct Sgolyo
{
    private:
    double sugar;
    Skoordinatak pozicio;
    Skoordinatak sebesseg;
    unsigned char R,G,B;

    public:
    Sgolyo (double usugar, Skoordinatak upozicio, Skoordinatak usebesseg) 
    {
        sugar = usugar;
        pozicio = upozicio;
        sebesseg = usebesseg;
        R = rand()%255;
        G = rand()%255;
        B = rand()%255;
    };

    void rajzol()
    {
        glColor3d(R/255.0, G/255.0, B/255.0);
        kor(pozicio,sugar);
    }

    void update(vector<Sgolyo> &labdak, double surlodas)
    {
        for (int i = 0; i < labdak.size(); i++) { // Megvizsgálom mindegyikkel, hogy ütközött-e
            double dx = labdak[i].pozicio.x - pozicio.x; // Vektort képzek
            double dy = labdak[i].pozicio.y - pozicio.y;
            double distance = sqrt(dx*dx + dy*dy); // távolság
            double minDist = labdak[i].sugar + sugar; // Legkisebb távolság hogy még nem ütközik
            if (distance < minDist) { // ütközött-e
                double angle = atan2(dy, dx); // ütközés szöge

                double targetX = pozicio.x + cos(angle) * minDist; // sebesség vektor számolás (előkészület)
                double targetY = pozicio.y + sin(angle) * minDist;

                double ax = (targetX - labdak[i].pozicio.x) * 0.9; // sebesség vektor számolás (befejezés)
                double ay = (targetY - labdak[i].pozicio.y) * 0.9; // A 0.9es szorzó azért van hogy szétjöjjenek ha egyberakjuk őket. (Ugyanakkor rugalmatlanabb lesz az ütközés) 

                sebesseg.x -= ax; // Sebességvektorok megváltozatása
                sebesseg.y -= ay;
                labdak[i].sebesseg.x += ax;
                labdak[i].sebesseg.y += ay;
            }
        }

        if (sebesseg.x>maximumsebesseg) sebesseg.x=maximumsebesseg; else if (sebesseg.x<-maximumsebesseg) sebesseg.x=-maximumsebesseg; // Ha túl gyorsak lennének (ami csak akkor lehet ha egyberakjuk őket)
        if (sebesseg.y>maximumsebesseg) sebesseg.y=maximumsebesseg; else if (sebesseg.y<-maximumsebesseg) sebesseg.y=-maximumsebesseg; // Maximum sebességre állítjuk őket

        pozicio.x+=sebesseg.x; // Mozgatás
        pozicio.y+=sebesseg.y;

        if (pozicio.x-sugar<0) { // Fallakkal való ütközés
            sebesseg.x=-sebesseg.x;
            pozicio.x=0+sugar;
        }
        if (pozicio.x+sugar>XX){
            sebesseg.x=-sebesseg.x;
            pozicio.x=XX-sugar;
        }
        if (pozicio.y-sugar<0) {
            sebesseg.y=-sebesseg.y;
            pozicio.y=0+sugar;
        }
        if (pozicio.y+sugar>YY){
            sebesseg.y=-sebesseg.y;
            pozicio.y=YY-sugar;
        }

        sebesseg.x/=surlodas;
        sebesseg.y/=surlodas;
        cout << surlodas << "   " << int(sebesseg.x*100)/100.0 << " " << int(sebesseg.y*100)/100.0 << endl;

    }
};

vector<Sgolyo> labdak;
double surlodas = 1;

void MouseFunction(int button, int state, int x,int y)
{
    //bal gomb lenyomására
    if (button == GLUT_LEFT_BUTTON) {
        if  (state == GLUT_DOWN) { //le
            Sgolyo labda(rand()%20+3,Skoordinatak(x,y),Skoordinatak((rand()%int(maximumsebesseg*200)-maximumsebesseg*100)/100.0,(rand()%int(maximumsebesseg*200)-maximumsebesseg*100)/100.0));
            // rand()%int(maximumsebesseg*200)-maximumsebesseg*100)/100.0) -nek az értékei ha maximumsebesseg=3: -3.00-tól +3.00-ig
            labdak.push_back(labda);
        } else { //fel 
        }
    }
}

void Init()
{
    glViewport(0, 0, XX, YY);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0.0, XX, YY, 0.0);
}

void ReDraw( ) { 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glClearColor(0.0, 0.0, 0.0, 0.0); //háttérszín
    glClear(GL_COLOR_BUFFER_BIT); 
    

    for (int i = 0; i < labdak.size(); ++i)
    {
        labdak[i].rajzol();
    }
    
    glFlush( ); //Azonnal jelenítse meg
    glutSwapBuffers();
    
}

void Step() 
{
    
    for (int i = 0; i < labdak.size(); ++i)
    {
        labdak[i].update(labdak, surlodas);
    }

  glutPostRedisplay();   //display scene
}

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
    srand (time(NULL));

    glutInitWindowSize(XX, YY);
    glutInitWindowPosition(500, 100);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("Utkozes");
    Init();
    glutDisplayFunc(ReDraw);
    glutMouseFunc(MouseFunction);
    glutReshapeFunc(reshape);   
    
    glutIdleFunc(Step);

    glutMainLoop();
    
    return 0;
}