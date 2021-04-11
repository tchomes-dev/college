#include "Triangle.h"

Triangle::Triangle(double L, sf::Vector2f center) {
    this->length = L;
    this->height = L * sqrt(3)/2;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(center.x - (length / 2), center.y - (height / 3)));
    triangle.setPoint(1, sf::Vector2f(center.x + (length / 2), center.y - (height / 3)));
    triangle.setPoint(2, sf::Vector2f(center.x, center.y + (2 * height) / 3));
}

void Triangle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(triangle, states);
}