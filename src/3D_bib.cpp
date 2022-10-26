
#include "3D_bib.h"

Operaciones3D::Operaciones3D() {
    // Variables para operaciones trigonometricas
    pi = 3.14159265359;
    LoadIdentity(A);
}

// recordar que (pi/180 = r/g) donde "r" son radianes y "g" grados
// se aplica la formula r
float Operaciones3D::RadToDeg(float r) { return ((180 * r) / pi); }

float Operaciones3D::DegToRad(float g) { return ((g * pi) / 180); }

void Operaciones3D::LoadIdentity(float M[][4]) {
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (i == j)
                M[i][j] = 1;
            else
                M[i][j] = 0;
}

void Operaciones3D::translate(float x, float y, float z) {
    LoadIdentity(T);
    T[0][3] = x;
    T[1][3] = y;
    T[2][3] = z;
}
void Operaciones3D::translate(Point vT) {
    LoadIdentity(T);
    T[0][3] = vT.x;
    T[1][3] = vT.y;
    T[2][3] = vT.z;
}

void Operaciones3D::rotateX(float deg) {
    LoadIdentity(R);
    R[1][1] = cos(deg);
    R[1][2] = -1 * sin(deg);
    R[2][1] = sin(deg);
    R[2][2] = cos(deg);
}

void Operaciones3D::rotateY(float deg) {
    LoadIdentity(R);
    R[0][0] = cos(deg);
    R[0][2] = sin(deg);
    R[2][0] = -1 * sin(deg);
    R[2][2] = cos(deg);
}

void Operaciones3D::rotateZ(float deg) {
    LoadIdentity(R);
    R[0][0] = cos(deg);
    R[0][1] = -1 * sin(deg);
    R[1][0] = sin(deg);
    R[1][1] = cos(deg);
}

void Operaciones3D::MultM(float M1[][4], float M2[][4], float Res[][4]) {
    float tmp[4][4];
    int i, j, k;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++) {
            tmp[i][j] = 0;
            for (k = 0; k < 4; k++)
                tmp[i][j] += M1[i][k] * M2[k][j];
        }
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            Res[i][j] = tmp[i][j];
}

// multiplica la matriz m por el punto p y regresa el resultado en el punto p
void Operaciones3D::MatPoint(float m[][4], float p[3]) {
    float tmp[4];
    int i, j;
    for (i = 0; i < 3; i++) {
        tmp[i] = p[i];
        p[i] = 0;
    }
    tmp[3] = 1;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 4; j++)
            p[i] += m[i][j] * tmp[j];
}
void Operaciones3D::MatPoint(float m[][4], Point pointOri, Point *pointTrans) {
    float tmp[4], result[4];
    int i, j;
    for (i = 0; i < 3; i++) {
        result[i] = 0;
    }
    tmp[0] = pointOri.x;
    tmp[1] = pointOri.y;
    tmp[2] = pointOri.z;
    tmp[3] = 1;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 4; j++)
            result[i] += m[i][j] * tmp[j];
    pointTrans->x = result[0];
    pointTrans->y = result[1];
    pointTrans->z = result[2];
}

// multiplica la matriz m por cada punto del objeto definido por la matriz p de
// size x 3
void Operaciones3D::MatObject(float m[][4], int size, float p[][3]) {
    int i;
    for (i = 0; i < size; i++)
        MatPoint(m, p[i]);
}
void Operaciones3D::MatObject(float m[][4], int size, Point points[],
                              Point pointTrans[]) {
    int i;
    for (i = 0; i < size; i++)
        MatPoint(m, points[i], &pointTrans[i]);
}

// rotacion paralela a uno de los ejes
// theta: angulo de rotacion;
// distA,distB: vector (distA,distB) que separa al eje de rotacion del objeto
// con respecto a uno de los ejes del sistema cartesiano. Si el eje es:
// X: (distA,distB) es el vector (0,distA,distB)
// Y: (distA,distB) es el vector (distA,0,distB)
// Z: (distA,distB) es el vector (distA,distB,0)
void Operaciones3D::RotacionParalela(char eje, float theta, float distA,
                                     float distB) {
    switch (eje) {
    case 'X': // rotacion paralela en "X"
        translate(0, -distA, -distB);
        rotateX(DegToRad(theta));
        MultM(R, T, A);
        translate(0, distA, distB);
        MultM(T, A, A);
        break;
    case 'Y': // rotacion paralela en "Y"
        translate(-distA, 0, -distB);
        rotateY(DegToRad(theta));
        MultM(R, T, A);
        translate(distA, 0, distB);
        MultM(T, A, A);

        break;
    case 'Z': // rotacion paralela en "Z"
        translate(0, -distA, -distB);
        rotateZ(DegToRad(theta));
        MultM(R, T, A);
        translate(0, distA, distB);
        MultM(T, A, A);
        break;
    }
}

void Operaciones3D::RotacionLibre(float theta, float p1[3], float p2[3]) {
    // 1. Calcular el vector unitario
    // (a,b,c)
    // ...
    float vUnit[3];
    float vNorma = 0;
    for (int i = 0; i < 3; i++) {
        vUnit[i] = p2[i] - p1[i];
        vNorma += vUnit[i] * vUnit[i];
    }
    vNorma = sqrt(vNorma);
    for (int i = 0; i < 3; i++) {
        vUnit[i] = vUnit[i] / vNorma;
    }

    // 2. Calcular matriz de rotaci'on con respecto a "x" del angulo "beta"
    /* float Rx[4][4]; */
    /* float cosine; */
    /* float sine; */
    /* LoadIdentity(RxTheta); */
    /* cosine = std::cos(DegToRad(theta)); */
    /* cosine = std::cos(DegToRad(theta)); */
    /* RxTheta[1][1] = cosine; */
    /* RxTheta[1][2] = -sine; */
    /* RxTheta[2][1] = sine; */
    /* RxTheta[2][2] = cosine; */
    // 2.1 d= sqrt(b^2+c^2)
    float d = sqrt((vUnit[1] * vUnit[1]) + (vUnit[2] * vUnit[2]));
    if (d != 0) {
        // 2.2 Calcular R_x(alpha)
        float RxAlpha[4][4];
        float a, b, c;
        a = vUnit[0];
        b = vUnit[1];
        c = vUnit[2];
        LoadIdentity(RxAlpha);
        RxAlpha[1][1] = c / d;
        RxAlpha[1][2] = -b / d;
        RxAlpha[2][1] = b / d;
        RxAlpha[2][2] = c / d;

        // 3. Calcular matriz de rotacion con respecto "y" del angulo "Beta"
        // R_y(beta)
        float RyBeta[4][4];
        LoadIdentity(RyBeta);
        RyBeta[0][0] = d;
        RyBeta[0][2] = -a;
        RyBeta[2][0] = a;
        RyBeta[2][2] = d;

        // 4. Calcular matriz de rotacion con el angulo theta con respecto al
        // eje "Z" R_z(theta)
        rotateZ(DegToRad(theta));
        // 5. Def Matriz R_y^(-1) (Beta)
        float RyBetaT[4][4];
        LoadIdentity(RyBetaT);
        RyBetaT[0][0] = d;
        RyBetaT[0][2] = a;
        RyBetaT[2][0] = -a;
        RyBetaT[2][2] = d;
        // 6. Def matriz R_x^(-1) (alpha)
        float RxAlphaT[4][4];
        LoadIdentity(RxAlphaT);
        RxAlphaT[1][1] = c / d;
        RxAlphaT[1][2] = b / d;
        RxAlphaT[2][1] = -b / d;
        RxAlphaT[2][2] = c / d;
        // 7. Calcular la matriz de traslacion inversa T'
        translate(-p1[0], -p1[1], -p1[2]);
        // mover a origen
        // multiplicar rotaciones
        MultM(RxAlpha, T, A);
        MultM(RyBeta, A, A);
        MultM(R, A, A);
        MultM(RyBetaT, A, A);
        MultM(RxAlphaT, A, A);
        // regresar a lugar original
        translate(p1[0], p1[1], p1[2]);
        MultM(T, A, A);
    } else {
        rotateX(DegToRad(theta));
        translate(-p1[0], -p1[1], -p1[2]);
        MultM(R, T, A);
        translate(p1[0], p1[1], p1[2]);
        MultM(T, A, A);
    }
}
void Operaciones3D::push() {
    Matrix *pointerMatrix = new Matrix();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            pointerMatrix->M[i][j] = A[i][j];
        }
    }
    pila.push(pointerMatrix);
}
void Operaciones3D::pop() {
    Matrix *pointerMatrix = pila.top();
    pila.pop();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            A[i][j] = pointerMatrix->M[i][j];
        }
    }
    delete pointerMatrix;
}
