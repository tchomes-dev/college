#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>

using namespace std;
class Triangle : public sf::Drawable
{
public:
    Triangle(double L, sf::Vector2f center);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::ConvexShape triangle;
    int length;
    int height;
};

