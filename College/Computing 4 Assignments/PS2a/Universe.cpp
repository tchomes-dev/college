#include "Universe.h"

Universe::Universe(string file) {
    ifstream infile(file);
    readFile(infile);
}

void Universe::readFile(istream& in) {
    in >> numPlanets >> radius;
    for (int i = 0; i < numPlanets; i++)
    {
        shared_ptr<CelestialBody> temp(new CelestialBody);
        in >> *temp;
        temp.get()->loadImage();
        system.push_back(temp);
    }
}

void Universe::CelestialBody::loadImage() {
    if (!planet_texture.loadFromFile(this->fileName)) {
        cout << "ERROR\n";
        exit(-1);
    }
    planet.setTexture(planet_texture);
}

Sprite Universe::CelestialBody::getPlanet(){
    return this->planet;
}

float Universe::CelestialBody::getXPos() {
    return this->xPos;
}

float Universe::CelestialBody::getYPos() {
    return this->yPos;
}

void Universe::CelestialBody::updatePosition(float x, float y, float scale) {
    xPos = xPos / scale * (x / 2) + (x / 2);
    yPos = yPos / scale * (y / 2) + (y / 2);
    planet.setPosition(xPos, yPos);
}

vector<shared_ptr<Universe::CelestialBody>> Universe::getUniverse() {
    return this->system;
}

istream& operator>>(istream& in, Universe::CelestialBody& obj) {
    in >> obj.xPos >> obj.yPos >> obj.xVel >> obj.yVel >> obj.mass >> obj.fileName;
    return in;
}

void Universe::CelestialBody::draw(RenderTarget& target, RenderStates states) const {
    target.draw(planet, states);
}