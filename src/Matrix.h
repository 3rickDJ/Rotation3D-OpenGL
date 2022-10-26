#pragma once
class Matrix {
  public:
    float M[4][4]{};
    Matrix();
    void operator=(const Matrix &m2);
    void operator=(const float m2[][4]);
    void copyMatrix(float Dest[][4]);
};
