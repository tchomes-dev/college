#define _USE_MATH_DEFINES


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <math.h>

using namespace std;
class Triangle : public sf::Drawable
{
public:
    Triangle(double L, sf::Vector2f center);
    void fTree(int N, sf::Vector2f absCenter);
private:
    sf::ConvexShape triangle;
    double length;
    double height;
};

