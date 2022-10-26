#pragma once
//#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stack>
#include "Point.h"
#include "Matrix.h"
using namespace std;

class Operaciones3D{
      public:
        //Variables para matrices de rotacion y traslación
        float T[4][4], R[4][4], A[4][4];
        stack< Matrix *> pila;
        //Variables para operaciones trigonometricas
        float pi;
        Operaciones3D();

        //Transformacion de grados a radianes
        //recordar que (pi/180 = r/g) donde "r" son radianes y "g" grados
        //se aplica la formula r
        float RadToDeg(float r);
        float DegToRad(float g);
        //Funcion para cargar la matriz identidad en la matriz que se recibe como parametro
        void LoadIdentity(float M[][4]);
        //Funcion que carga el vector de traslacion en la matriz T
        void translate(float x, float y, float z);
        void translate(Point p);
        //Funcion que define la matriz de rotacion con rspecto al eje X
        void rotateX(float deg);
        //Funcion que define la matriz de rotacion con rspecto al eje Y
        void rotateY(float deg);
        //Funcion que define la matriz de rotacion con rspecto al eje Z
        void rotateZ(float deg);
        //Funcion que multiplica la matriz M1 con la matriz M2, donde el resultado es Res
        void MultM(float M1[][4], float M2[][4], float Res[][4]);
        //multiplica la matriz m por el punto p y regresa el resultado en el punto p
        void MatPoint(float m[][4], float p[3]);
        void MatPoint(float m[][4], Point pointOri, Point* pointTrans);
        //multiplica la matriz m por cada punto del objeto definido por la matriz p de size x 3
        void MatObject(float m[][4], int size, float p[][3]);
        void MatObject(float m[][4], int size, Point points[], Point pointTrans[]);
        //Rotacion paralela a uno de los ejes
        //eje: eje de referencia
        //theta: angulo de rotacion
        //(distA,distB): distancia del eje de rotacion al eje refrencia del sistema
        //La matriz resultante queda almacenada en la matriz A
        void RotacionParalela(char eje, float theta, float distA, float distB);
        //Rotacion libre a partir del eje de rotacion definido por los puntos
        //p1 y p2 y theta grados en sentido contrario a las manecillas del reloj
        //La matriz resultante queda almacenada en la matriz A
        void RotacionLibre(float theta, float p1[3], float p2[3]);
        void push();
        void pop();
};
