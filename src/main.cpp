
#include "3D_bib.h"
#include "Piramid.h"
#include <GL/glut.h>
#include <iostream>



//Variables dimensiones de la pantalla
int WIDTH=500;
int HEIGTH=500;
//Variables para establecer los valores de gluPerspective
float FOVY=60.0;
float ZNEAR=0.01;
float ZFAR=100.0;
//Variables para definir la posicion del observador
//gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z)
float EYE_X=10.0;
float EYE_Y=5.0;
float EYE_Z=10.0;
float CENTER_X=0;
float CENTER_Y=0;
float CENTER_Z=0;
float UP_X=0;
float UP_Y=1;
float UP_Z=0;
//Variables para dibujar los ejes del sistema
float X_MIN=-20;
float X_MAX=20;
float Y_MIN=-20;
float Y_MAX=20;
float Z_MIN=-100;
float Z_MAX=20;

//Se declara el objeto para utilizar las operaciones 3D
Operaciones3D op3D;
Piramid P1 = Piramid(&op3D);
Piramid P2 = Piramid(&op3D);
Piramid P3 = Piramid(&op3D);

/* float Theta=0; */
//Variables para la definicion de objetos
/* float points[5][3]={{0,0,2},{2,0,2},{2,0,0},{0,0,0},{1,1.5,1}}; */


void drawAxis()
{
     glShadeModel(GL_SMOOTH);
     glLineWidth(3.0);
     //X axis in red
     glBegin(GL_LINES);
       glColor3f(1.0f,0.0f,0.0f);
       glVertex3f(X_MIN,0.0,0.0);
       glColor3f(0.5f,0.0f,0.0f);
       glVertex3f(X_MAX,0.0,0.0);
     glEnd();
     //Y axis in green
     glColor3f(0.0f,1.0f,0.0f);
     glBegin(GL_LINES);
       glColor3f(0.0f,1.0f,0.0f);
       glVertex3f(0.0,Y_MIN,0.0);
       glColor3f(0.0f,0.5f,0.0f);
       glVertex3f(0.0,Y_MAX,0.0);
     glEnd();
     //Z axis in blue
     glBegin(GL_LINES);
       glColor3f(0.0f,0.0f,1.0f);
       glVertex3f(0.0,0.0,Z_MIN);
       glColor3f(0.0f,0.0f,0.5f);
       glVertex3f(0.0,0.0,Z_MAX);
     glEnd();
     glLineWidth(1.0);
 }

/////////////////////////////////////////////////////////////////////////////
//funciones de objetos
/////////////////////////////////////////////////////////////////////////////


//funciones callbacks
void idle(void)
{

  glutPostRedisplay();
 }

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
}

static void keys(unsigned char key, int x, int y)
{
    switch(key){
                case 'u':
                     P1.Deg+=5;
                     break;
                case 'U':
                    P1.Deg+=-5;
                     /* Theta=-6; */
                     break;
                case 'h':
                    P2.Deg+=0.1;
                    break;
                case 'H':
                    P2.Deg-=0.1;
                    break;
                default:
                     /* Theta = 0; */
                     break;
    }
    glutPostRedisplay();
}
//--------------------------------------------------------------------------

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();
    glColor3f(1.0f,1.0f,1.0f);
    //se rota la piramide Theta grados con respecto al eje de rotacion
    //a una distancia definida por el usuario
    //RotacionPiramide('X',Theta,0,0);
    //RotacionPiramide('Z',Theta,0,0);
    /* RotacionPiramide(Theta, P1, P2); */
    /* ImprimePiramide(); */
    op3D.push();
    op3D.rotateY(op3D.DegToRad(P1.Deg));
    P1.ImprimePiramide();
    op3D.push();
    op3D.translate(P2.vT);
    op3D.rotateY(P2.Deg);
    P2.ImprimePiramide();
    op3D.push();
    op3D.translate(P3.vT);
    P3.ImprimePiramide();
    op3D.pop();
    op3D.pop();
    op3D.pop();



    glutSwapBuffers();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY, (GLfloat)WIDTH/HEIGTH, ZNEAR, ZFAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z);
    glClearColor(0,0,0,0);
    op3D.LoadIdentity(op3D.A);
    op3D.push();
    P1.setDeltaDeg(0);
    P1.setPoints({0,0,2},{2,0,2},{2,0,0},{0,0,0},{1,1.5,1});
    P2.setVectorTranslation({2,2,0});
    P2.setDeltaDeg(0);
    P2.setPoints({0,0,2},{2,0,2},{2,0,0},{0,0,0},{1,1.5,1});
    P3.setVectorTranslation({5,-5,5});
    P3.setPoints({0,0,2},{2,0,2},{2,0,0},{0,0,0},{1,1.5,1});

    /* Theta=1; */
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGTH);
    glutCreateWindow("Triangulo a color");
    init();
    glutDisplayFunc(display);
    //glutIdleFunc(idle);
    glutKeyboardFunc(keys);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
