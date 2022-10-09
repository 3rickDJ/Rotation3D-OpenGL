
#include "3D_bib.h"
#include <GL/glut.h>



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
Operaciones3D Op3D;

float Theta=0;
//Variables para la definicion de objetos
float P1[3]={0.0,0.0,0.0};
float P2[3]={5.0,5.0,-3.0};
float points[5][3]={{0,0,2},{2,0,2},{2,0,0},{0,0,0},{1,1.5,1}};


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
float Norma(float p1[3], float p2[3])
{
      float n=0;
      int i;
      for(i=0;i<3;i++)
        n += pow(p2[i]-p1[i],2);
      return(sqrt(n));
}

void ImprimeMallaPiramide(int k)
{
     int i,j;
     float U[3],d,norma;
     for(i=0;i<3;i++)
     {
        norma = Norma(points[i],points[i+1]);
        d = norma/(float)k;
        U[0] = (points[i+1][0]-points[i][0])/norma;
        U[1] = (points[i+1][1]-points[i][1])/norma;
        U[2] = (points[i+1][2]-points[i][2])/norma;
        for(j = 1; j < k; j++)
        {
           glBegin(GL_LINES);
             glVertex3f(points[4][0],points[4][1],points[4][2]);
             glVertex3f(points[i][0]+U[0]*d*j,points[i][1]+U[1]*d*j,points[i][2]+U[2]*d*j);
           glEnd();
        }
     }
     norma = Norma(points[i],points[0]);
     d = norma /(float)k;
     U[0] = (points[0][0]-points[i][0])/norma;
     U[1] = (points[0][1]-points[i][1])/norma;
     U[2] = (points[0][2]-points[i][2])/norma;
     for(j = 1; j < k; j++)
        {
           glBegin(GL_LINES);
             glVertex3f(points[4][0],points[4][1],points[4][2]);
             glVertex3f(points[i][0]+U[0]*d*j,points[i][1]+U[1]*d*j,points[i][2]+U[2]*d*j);
           glEnd();
        }

}

void ImprimePiramide()
{   int i;
    glBegin(GL_LINE_LOOP);
      for(i=0;i<4;i++)
        glVertex3f(points[i][0],points[i][1],points[i][2]);
    glEnd();
    glBegin(GL_LINES);
      for(i=0;i<4;i++){
        glVertex3f(points[4][0],points[4][1],points[4][2]);
        glVertex3f(points[i][0],points[i][1],points[i][2]);
        }
    glEnd();
    ImprimeMallaPiramide(20);
 }


//Rotacion paralela
//rota a la piramide theta grados, donde el eje de rotacion se encuentra
//a una distancia distA-distB del eje seleccionado (ejeXYZ)
void RotacionPiramide(char ejeXYZ, float theta, float distA, float distB)
{
     //se prepara la matriz de operaciones A: T^(-1)R(T)
     Op3D.RotacionParalela(ejeXYZ,theta,distA,distB);
     //se aplica A a cada punto de la piramide
     Op3D.MatObject(Op3D.A,5,points);
}

//Rotacion libre
void RotacionPiramide(float theta, float p1[3], float p2[3])
{
     //se imprime el eje de rotacion
     glColor3f(1.0,1.0,1.0);
     glBegin(GL_LINES);
       glVertex3f(p1[0],p1[1],p1[2]);
       glVertex3f(p2[0],p2[1],p2[2]);
     glEnd();
     glColor3f(1.0,1.0,1.0);
     //se prepara la matriz de operaciones A
     Op3D.RotacionLibre(theta, p1, p2);
     //Se aplica A a cada punto de la piramide
     Op3D.MatObject(Op3D.A,5,points);
}

//-------------------------------------------------------------------------
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
                     Theta=1;
                     break;
                case 'd':
                     Theta=-1;
                     break;
                default:
                     Theta = 0;
                     break;
    }
    glutPostRedisplay();
}
//--------------------------------------------------------------------------

void display()
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();
    glColor3f(1.0f,1.0f,1.0f);
    //se rota la piramide Theta grados con respecto al eje de rotacion
    //a una distancia definida por el usuario
    //RotacionPiramide('X',Theta,0,0);
    /* RotacionPiramide('Z',Theta,0,0); */
    RotacionPiramide(Theta, P1, P2);
    ImprimePiramide();
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
    Theta=1;
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
