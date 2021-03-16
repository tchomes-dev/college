#include "Universe.h"

int main() {
    Universe milkyway("planets.txt");
    RenderWindow window(VideoMode(1600, 900), "Planets");
    window.setFramerateLimit(60);

    for (auto planet : milkyway.getUniverse()) {
        planet.get()->updatePosition(window.getSize().x, window.getSize().y, milkyway.getRadius());
    }

    Texture texture;
    if (!texture.loadFromFile("space.jpg"))
        return -1;
    Sprite background(texture);

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
        for (auto planet : milkyway.getUniverse()) {
            window.draw(*planet);
        }
        window.display();

    }
    return 0;
}