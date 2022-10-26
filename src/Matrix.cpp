#include "Matrix.h"

Matrix::Matrix(){
    for (int i = 0; i <4; i++){
        for (int j = 0; j <4; j++){
            M[i][j]=0;
        }
    }
}
void Matrix::operator=(const Matrix &m2) {
    for (int i = 0; i <4; i++){
        for (int j = 0; j <4; j++){
            this->M[i][j]=m2.M[i][j];
        }
    }
}
void Matrix::operator=(const float m2[][4]) {
    for (int i = 0; i <4; i++){
        for (int j = 0; j <4; j++){
            M[i][j]=m2[i][j];
        }
    }
}
void Matrix::copyMatrix(float Dest[][4]) {
    for (int i = 0; i <4; i++){
        for (int j = 0; j <4; j++){
            Dest[i][j]=M[i][j];
        }
    }
}
