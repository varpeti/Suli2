#include <cstdlib>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

bool kockaharomszog;

void Init(){

    glViewport(0, 0, 400, 400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0., 100., 100., 0.);

}

void ReDraw( ) {
    glClearColor(0, 0, 0, 0); //háttérszín
    glClear(GL_COLOR_BUFFER_BIT);

    /*
    Rajzold ki az aktuális poligont
    */

    if (kockaharomszog) {
        //itt most egy kék négyszöget rajzolunk
        glColor3d( 0.0, 0.0, 1.0 );
        glBegin(GL_POLYGON);
            glVertex2d(10.0, 10.0);
            glVertex2d(10.0, 90.0);
            glVertex2d(90.0, 90.0);
            glVertex2d(90.0, 10.0);
        glEnd( );
    } else
    {
        //itt most egy zöld háromszöget rajzolunk
        glColor3d( 0.0, 1.0, 0.0 );
        glBegin(GL_TRIANGLES);
            glVertex2d(10.0, 10.0);
            glVertex2d(20.0, 100.0);
            glVertex2d(90.0, 30.0);
        glEnd( );
    }
   
    glFlush( ); //Azonnal jelenítse meg
}



//Az ablak átméretezésénél skálázza a képet is
void reshape(int w, int h) {
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,100,0.0,100);
}

void Keyboard(unsigned char key, int x, int y) {

    /* h esetén váltson háromszögre n esetén négyszögre*/

    switch(key) { 
        case 'h':
            kockaharomszog=false;
            break;
        case 'n':
            kockaharomszog=true;
            break;
        case 27: 
            exit(0); 
            break; 
        default: 
            std::cout << key << std::endl;
            break;
    }
    

    glutPostRedisplay(); //újra rajzolja ki az ablakot
}


int main(int argc, char* argv[])
{
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB );
    glutCreateWindow("Square_and_triangle");
    Init();
    kockaharomszog=false;

    glutKeyboardFunc( Keyboard );
    glutDisplayFunc( ReDraw );
    glutReshapeFunc(reshape);

    glutMainLoop();

}