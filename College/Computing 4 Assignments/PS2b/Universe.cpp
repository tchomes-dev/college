#include "Universe.h"



Universe::Universe(string file, string t, string T) {

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



vector<shared_ptr<Universe::CelestialBody>> Universe::getUniverse() {

    return this->system;

}



void Universe::step(double t, Window& window) {

    struct force {

        double first, second = 0;

    };

    struct accel {

        double first, second = 0;

    };

    force netForce, F1;

    accel a;

    double G = 0.0000000000667;



    for (auto each : system)

    {

        for (auto p : system)

        {

            if (each == p)continue;//found same value



            //get change in x and y values between particles//

            double deltaX = p->getXPos() - each->getXPos();

            double deltaY = each->getXPos() - p->getYPos();

            //solve for r

            double r = sqrt((deltaX * deltaX) + (deltaY * deltaY));

            //solve for F

            double F = (G * each->getMass() * p->getMass()) / (r * r);

            //solve for Fx and Fy

            F1.first = F * deltaX / r;

            F1.second = F * deltaY / r;

            //set running netforce

            netForce.first = netForce.first + F1.first;

            netForce.second = netForce.second + F1.second;

        }

        //calculate acceleration aX and aY

        a.first = netForce.first / each->getMass();

        a.second = netForce.second / each->getMass();



        //set new velocity given acceleration

        each->setXVel(each->getXVel() + (a.first * t));

        each->setYVel(each->getYVel() + (a.second * t));





        //reset netforce for next iteration

        netForce = { 0.0,0.0 };

    }



    //update each particle postion and set position scale for window//

    for (auto each : system)

    {

        each->setXPos(each->getXPos() - (t * each->getXVel()));

        each->setYPos(each->getYPos() - (t * each->getYVel()));

        each.get()->updatePosition(window.getSize().x, window.getSize().y, this->radius);

    }

}



void Universe::CelestialBody::loadImage() {

    if (!planet_texture.loadFromFile(this->fileName)) {

        cout << "ERROR\n";

        exit(-1);

    }

    planet.setTexture(planet_texture);

}



void Universe::CelestialBody::updatePosition(float x, float y, float scale) {

    double finalXPos, finalYPos;

    finalXPos = xPos / scale * (x / 2) + (x / 2);

    finalYPos = yPos / scale * (y / 2) + (y / 2);



    planet.setPosition(finalXPos, finalYPos);

}



istream& operator>>(istream& in, Universe::CelestialBody& obj) {

    in >> obj.xPos >> obj.yPos >> obj.xVel >> obj.yVel >> obj.mass >> obj.fileName;

    return in;

}



void Universe::CelestialBody::draw(RenderTarget& target, RenderStates states) const {

    target.draw(planet, states);

}