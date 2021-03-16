#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>

using namespace std;
using namespace sf;

class Universe {
public:
    class CelestialBody : public Drawable{
    public:
        void loadImage();
        Sprite getPlanet();
        float getXPos();
        float getYPos();
        void updatePosition(float x, float y, float radius);
        friend istream& operator>>(istream& input, CelestialBody& obj);
        virtual void draw(RenderTarget& target, RenderStates states) const;
    private:
        float xPos, yPos, xVel, yVel, mass;
        string fileName;
        Sprite planet;
        Texture planet_texture;
    };
    Universe(string file);
    void readFile(istream& in);
    float getRadius() { return radius; }
    vector<shared_ptr<CelestialBody>> getUniverse();
private:
    int numPlanets;
    float radius;
    vector<shared_ptr<CelestialBody>> system;
};