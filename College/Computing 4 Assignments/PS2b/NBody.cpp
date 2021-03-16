#include "Universe.h"



int main(int argv, char* argc[]) {

    double steptime, runtime;

    steptime = stod(argc[2]);

    runtime = stod(argc[1]);

    Universe milkyway("planets.txt", argc[2], argc[1]);

    RenderWindow window(VideoMode(1600, 900), "Planets");

    window.setFramerateLimit(60);



    Texture texture;

    if (!texture.loadFromFile("space.jpg"))

        return -1;

    Sprite background(texture);



    for (auto planet : milkyway.getUniverse()) {

        planet.get()->updatePosition(window.getSize().x, window.getSize().y, milkyway.getRadius());

    }

    while (window.isOpen())

    {

        Event event;

        while (window.pollEvent(event))

        {

            if (event.type == Event::Closed)

                window.close();

        }

        window.clear();

        window.draw(background);

        milkyway.step(steptime, window);

        for (auto planet : milkyway.getUniverse()) {

            window.draw(*planet);

        }

        window.display();

        runtime -= steptime;

    }

    return 0;

}