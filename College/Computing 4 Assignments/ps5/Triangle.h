#define _USE_MATH_DEFINES


#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

using namespace std;
class Triangle : public sf::Drawable
{
public:
    Triangle(int N, double L, double centerX, double centerY);

private:
    sf::CircleShape triangle;
    double length;
    double height;
};

