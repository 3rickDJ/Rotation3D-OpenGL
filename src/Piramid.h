#pragma once
#include "3D_bib.h"
#include "Point.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
class Piramid {
  private:
    void ImprimeMallaPiramide(int k);
    // puntos de la figura
    Point points[5];
    Point pointsOri[5];
    // degree base

  public:
    //0:= niguna animacion, 1:=rotacion, 2:= traslacion
    int animation;
    float Deg;
    // delta degree ratio of change
    float deltaDeg;
    // vector of translation
    Point vT;
    // delta vector of translation
    Point deltaT;
    // reference to Global matrix
    Operaciones3D *op3d;
    Piramid();
    Piramid(Operaciones3D *op3d);
    void setVectorTranslation(Point vT);
    void setDeltaTranslation(Point deltaT);
    void setDeg(float deg);
    void setDeltaDeg(float deltaDeg);
    void setPoints(Point points[5]);
    void setPoints(Point p1, Point p2, Point p3, Point p4, Point p5);
    void ImprimePiramide();
    void updateFrame();
};
