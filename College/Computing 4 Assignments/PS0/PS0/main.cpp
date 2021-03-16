#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void processInput(sf::RenderWindow& window, sf::CircleShape& object);
void processInput(RenderWindow& window, Sprite& obj);
void processInput(int& x);

int main()
{
    RenderWindow window(VideoMode(1600, 900), "SFML works!");
    window.setFramerateLimit(300);
    int object = 1;

    CircleShape circle(100.f);
    circle.setFillColor(Color::Green);

    string file = "earth.gif";
    Texture spriteTexture;
    if (!spriteTexture.loadFromFile(file))
        return EXIT_FAILURE;
    Sprite gnome(spriteTexture);

    Font font;
    if (!font.loadFromFile("./RobotoCondensed-Light.ttf"))
        return EXIT_FAILURE;

    Text text("Press 1 to move circle or press 2 to move the gnome\n W,A,S,D to move, R to rotate the selected image", font, 30);
    text.setPosition(1000, 0);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        processInput(object);
        if (object == 1)
            processInput(window, circle);
        else if (object == 2)
            processInput(window, gnome);
        window.draw(circle);
        window.draw(gnome);
        window.draw(text);
        window.display();

    }

    return 0;
}

void processInput(RenderWindow& window, CircleShape& obj) {
    if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
        if (obj.getPosition().x >= 0)
            obj.move(-1, 0);
        return;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
        if (obj.getPosition().x + obj.getRadius() * 2 <= window.getSize().x)
            obj.move(1, 0);
        return;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
        if (obj.getPosition().y + obj.getRadius() * 2 <= window.getSize().y)
            obj.move(0, 1);
        return;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
        if (obj.getPosition().y >= 0)
            obj.move(0, -1);
        return;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::R)) {
        obj.setRotation(obj.getRotation() + 90);
        return;
    }
}

void processInput(RenderWindow& window, Sprite& obj) {
    if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
        if (obj.getPosition().x >= 0)
            obj.move(-1, 0);
        return;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
        if (obj.getPosition().x + obj.getLocalBounds().width <= window.getSize().x)
            obj.move(1, 0);
        return;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
        if (obj.getPosition().y + obj.getLocalBounds().height <= window.getSize().y)
            obj.move(0, 1);
        return;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
        if (obj.getPosition().y >= 0)
            obj.move(0, -1);
        return;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::R)) {
        obj.setRotation(obj.getRotation() + 90);
        return;
    }
}

void processInput(int& x) {
    if (Keyboard::isKeyPressed(Keyboard::Key::Num1))
        x = 1;
    else if (Keyboard::isKeyPressed(Keyboard::Key::Num2))
        x = 2;
    else return;
}
