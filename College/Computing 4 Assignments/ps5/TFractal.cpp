#include "Triangle.h"

void fTree(std::vector<Triangle>* shapes, int N, double L, sf::Vector2f center);

int main(int argc, char* argv[]) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Sierpinski Triangles", sf::Style::Default, settings);

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
        std::vector<Triangle>* shapes = new vector<Triangle>;
        int N = stod(argv[2]);
        int L = stod(argv[1]);
        fTree(shapes, N, L, center);
        for(auto s : *shapes) window.draw(s);
        window.display();
    }
}

void fTree(std::vector<Triangle>* shapes, int N, double L, sf::Vector2f center) {
    int H = L * cosf(M_PI / 6);
    if (N < 0) return;
    else {
        shapes->push_back(Triangle(L, center));
        fTree(shapes, N-1, L/2, sf::Vector2f(center.x - L / 2, center.y - (2 * H) / 3));
        fTree(shapes, N-1, L/2, sf::Vector2f(center.x + (3 * L) / 4, center.y - (1 * H) / 6));
        fTree(shapes, N - 1, L / 2, sf::Vector2f(center.x - (1 * L) / 4, center.y + (5 * H) / 6));
    }
}