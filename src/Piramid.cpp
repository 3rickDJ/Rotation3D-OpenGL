#include "Piramid.h"
#include <GL/glut.h>
// public
Piramid::Piramid() {
    for (int i = 0; i < 5; i++) {
        points[i] = {0, 0, 0};
    }
    // degree base
    Deg = 0;
    // delta degree ratio of change
    deltaDeg = 0;
    // vector of translation
    vT = {0, 0, 0};
    // delta vector of translation
    deltaT = {0, 0, 0};
    // reference to Global matrix
    op3d = nullptr;
}
Piramid::Piramid(Operaciones3D *op3d) {
    for (int i = 0; i < 5; i++) {
        points[i] = {0, 0, 0};
        pointsOri[i] = {0, 0, 0};
    }
    // degree base
    Deg = 0;
    // delta degree ratio of change
    deltaDeg = 0;
    // vector of translation
    vT = {0, 0, 0};
    // delta vector of translation
    deltaT = {0, 0, 0};
    // reference to Global matrix
    this->op3d = op3d;
}
void Piramid::setVectorTranslation(Point vT) { this->vT = vT; }
void Piramid::setDeltaTranslation(Point deltaT) { this->deltaT = deltaT; }
void Piramid::setDeg(float deg) { this->Deg = deg; }
void Piramid::setDeltaDeg(float deltaDeg) { this->deltaDeg = deltaDeg; }
void Piramid::setPoints(Point points[5]) {
    for (int i = 0; i < 5; i++) {
        this->points[i] = points[i];
        pointsOri[i] = points[i];
    }
}
void Piramid::setPoints(Point p1, Point p2, Point p3, Point p4, Point p5) {
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
    points[4] = p5;
    pointsOri[0] = p1;
    pointsOri[1] = p2;
    pointsOri[2] = p3;
    pointsOri[3] = p4;
    pointsOri[4] = p5;

}
void Piramid::ImprimePiramide() {
    /* op3d->translate(vT); */
    /* vT = vT + deltaT; */
    /* op3d->rotateY(Deg); */
    /* Deg = Deg + deltaDeg; */
    /* op3d->MultM(op3d->T,op3d->A,op3d->A); */
    /* op3d->MultM(op3d->R,op3d->A,op3d->A); */
    op3d->MultM(op3d->R, op3d->A,op3d->A);
    op3d->LoadIdentity(op3d->R);
    op3d->MultM(op3d->T, op3d->A,op3d->A);
    op3d->LoadIdentity(op3d->T);
    op3d->MatObject(op3d->A, 5, pointsOri, points);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++) {
        glVertex3f(points[i].x, points[i].y, points[i].z);
    }
    glEnd();
    glBegin(GL_LINES);
    for (int i = 0; i < 4; i++) {
        glVertex3f(points[4].x, points[4].y, points[4].z);
        glVertex3f(points[i].x, points[i].y, points[i].z);
    }
    glEnd();
    ImprimeMallaPiramide(20);
    //updateFrame();
}
// privat{}
void Piramid::ImprimeMallaPiramide(int k) {
    int i, j;
    float d, norma;
    Point U;
    for (i = 0; i < 3; i++) {
        norma = Point::Norma(points[i], points[i + 1]);
        d = norma / (float)k;
        U.x = (points[i + 1].x - points[i].x) / norma;
        U.y = (points[i + 1].y - points[i].y) / norma;
        U.z = (points[i + 1].z - points[i].z) / norma;
        for (j = 1; j < k; j++) {
            glBegin(GL_LINES);
            glVertex3f(points[4].x, points[4].y, points[4].z);
            glVertex3f(points[i].x + U.x * d * j, points[i].y + U.y * d * j,
                       points[i].z + U.z * d * j);
            glEnd();
        }
    }
    norma = Point::Norma(points[i], points[0]);
    d = norma / (float)k;
    U.x = (points[0].x - points[i].x) / norma;
    U.y = (points[0].y - points[i].y) / norma;
    U.z = (points[0].z - points[i].z) / norma;
    for (j = 1; j < k; j++) {
        glBegin(GL_LINES);
        glVertex3f(points[4].x, points[4].y, points[4].z);
        glVertex3f(points[i].x + U.x * d * j, points[i].y + U.y * d * j,
                   points[i].z + U.z * d * j);
        glEnd();
    }
}
void Piramid::updateFrame() {
    op3d->translate(vT);
    vT = vT + deltaT;
    op3d->rotateY(Deg);
    Deg = Deg + deltaDeg;
}
