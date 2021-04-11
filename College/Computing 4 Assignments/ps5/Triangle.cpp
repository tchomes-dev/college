#include "Triangle.h"

Triangle::Triangle(int N, double L, double centerX, double centerY) {
    this->length = L;
    this->height = length * (double)cosf(M_PI / 6);
    triangle.setRadius(length);
    triangle.setPointCount(3);

}