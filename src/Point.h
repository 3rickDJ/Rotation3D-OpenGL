#pragma once
class Point {
  public:
    // coordenadas del punto
    float x;
    float y;
    float z;
    // constructores del punto
    Point();
    Point(float x, float y, float z);
    // graficar punto (x,y)
    void draw();
    void static Draw(int x, int y, int z);

    float static Norma(Point p1, Point p2);
    Point operator+(const Point &p2);
    void operator=(const Point &p2);
};
