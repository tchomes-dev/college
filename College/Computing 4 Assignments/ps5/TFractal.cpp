#include "Triangle.h"

void fTree(std::vector<Triangle> shapes, int N, double L, sf::Vector2f center);

int main(int argc, char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Planets");

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        sf::Vector2f center(window.getSize().x / 2, window.getSize().y / 2);
        std::vector<Triangle> shapes;
        int N = 4;
        int L = 400;
        fTree(shapes, N, L, center);
        for(auto s : shapes) window.draw(s);
        window.display();
    }
}

void fTree(std::vector<Triangle> shapes, int N, double L, sf::Vector2f center) {
    int H = L * cosf(M_PI / 6);
    if (N <= 0) return;
    else {
        shapes.push_back(Triangle(L, center));
        fTree(shapes, N-1, L/2, sf::Vector2f(center.x - L / 2, center.y - (2 / 3) * H));
        fTree(shapes, N-1, L/2, sf::Vector2f(center.x + (3 / 4) * L, center.y - (1 / 6) * H));
        fTree(shapes, N - 1, L / 2, sf::Vector2f(center.x - (1 / 4) * L, center.y + (5 / 6) * H));
    }
}