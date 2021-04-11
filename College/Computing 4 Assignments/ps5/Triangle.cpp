#include "Triangle.h"

Triangle::Triangle(double L, sf::Vector2f center) {
    this->length = L;
    this->height = length * (double)cosf(M_PI / 6);
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(center.x - (length / 2), center.y - (height / 3)));
    triangle.setPoint(1, sf::Vector2f(center.x + (length / 2), center.y - (height / 3)));
    triangle.setPoint(2, sf::Vector2f(center.x, center.y + (height * (float)(2 / 3))));
}

void Triangle::fTree(int N, sf::Vector2f absCenter) {

}