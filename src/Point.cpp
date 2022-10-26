#include "Point.h"
#include <GL/glut.h>
#include <math.h>

Point::Point() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point::Point(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
float Point::Norma(Point p1, Point p2) {
    float n = 0;
    n += pow(p2.x - p1.x, 2);
    n += pow(p2.y - p1.y, 2);
    n += pow(p2.z - p1.z, 2);
    return n;
}
Point Point::operator+(const Point &p2) {
    Point P;
    P.x = this->x + p2.x;
    P.y = this->y + p2.y;
    P.z = this->z + p2.z;
    return P;
}
void Point::operator=(const Point &p2) {
    x = p2.x;
    y = p2.y;
    z = p2.z;
}
