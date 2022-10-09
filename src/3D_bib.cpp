#include "3D_bib.h"

Operaciones3D::Operaciones3D()
{
        //Variables para operaciones trigonometricas
        pi = 3.14159265359;
        LoadIdentity(A);
}


//recordar que (pi/180 = r/g) donde "r" son radianes y "g" grados
//se aplica la formula r
float Operaciones3D::RadToDeg(float r)
{
      return ((180*r)/pi);
}

float Operaciones3D::DegToRad(float g)
{
      return ((g*pi)/180);
}

void Operaciones3D::LoadIdentity(float M[][4])
{
  int i,j;
  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      if(i==j)
         M[i][j]=1;
      else
         M[i][j]=0;
 }

void Operaciones3D::translate(float x, float y, float z)
{
  LoadIdentity(T);
  T[0][3]=x;
  T[1][3]=y;
  T[2][3]=z;
 }

void Operaciones3D::rotateX(float deg)
{
  LoadIdentity(R);
  R[1][1] = cos(deg);
  R[1][2] = -1*sin(deg);
  R[2][1] = sin(deg);
  R[2][2] = cos(deg);
 }

void Operaciones3D::rotateY(float deg)
{
  LoadIdentity(R);
  R[0][0] = cos(deg);
  R[0][2] = sin(deg);
  R[2][0] = -1*sin(deg);
  R[2][2] = cos(deg);
 }

void Operaciones3D::rotateZ(float deg)
{
  LoadIdentity(R);
  R[0][0] = cos(deg);
  R[0][1] = -1*sin(deg);
  R[1][0] = sin(deg);
  R[1][1] = cos(deg);
 }

void Operaciones3D::MultM(float M1[][4], float M2[][4], float Res[][4])
{
  float tmp[4][4];
  int i,j,k;
  for(i=0; i<4;i++)
     for(j=0;j<4;j++){
        tmp[i][j]=0;
        for(k=0;k<4;k++)
           tmp[i][j]+=M1[i][k]*M2[k][j];
     }
  for(i=0;i<4;i++)
     for(j=0;j<4;j++)
        Res[i][j] = tmp[i][j];
}

//multiplica la matriz m por el punto p y regresa el resultado en el punto p
void Operaciones3D::MatPoint(float m[][4], float p[3])
{
  float tmp[4];
  int i,j;
  for(i=0; i<3; i++)
    { tmp[i] = p[i];
      p[i] = 0;
    }
  tmp[3]=1;
  for(i=0;i<3;i++)
    for(j=0;j<4;j++)
        p[i] += m[i][j]*tmp[j];
}

//multiplica la matriz m por cada punto del objeto definido por la matriz p de size x 3
void Operaciones3D::MatObject(float m[][4], int size, float p[][3])
{
     int i;
     for(i=0; i<size; i++)
       MatPoint(m,p[i]);
}

//rotacion paralela a uno de los ejes
//theta: angulo de rotacion;
//distA,distB: vector (distA,distB) que separa al eje de rotacion del objeto
//con respecto a uno de los ejes del sistema cartesiano. Si el eje es:
//X: (distA,distB) es el vector (0,distA,distB)
//Y: (distA,distB) es el vector (distA,0,distB)
//Z: (distA,distB) es el vector (distA,distB,0)
void Operaciones3D::RotacionParalela(char eje, float theta, float distA, float distB)
{
     switch(eje){
        case 'X'://rotacion paralela en "X"

             break;
        case 'Y'://rotacion paralela en "Y"

             break;
        case 'Z'://rotacion paralela en "Z"

             break;
     }
}

void Operaciones3D::RotacionLibre(float theta, float p1[3], float p2[3])
{
//...
}
