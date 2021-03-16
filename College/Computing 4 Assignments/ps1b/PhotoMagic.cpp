// pixels.cpp: 
// using SFML to load a file, manipulate its pixels, write it to disk


// g++ -o pixels pixels.cpp -lsfml-graphics -lsfml-window

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "FibLFSR.h"

void transform(sf::Image& image, FibLFSR* lfsr) {
	sf::Color p;

	for (int x = 0; x < (signed)image.getSize().x; x++) {
		for (int y = 0; y < (signed)image.getSize().y; y++) {
			p = image.getPixel(x, y);
			p.r ^= lfsr->generate(8);
			p.g ^= lfsr->generate(8);
			p.b ^= lfsr->generate(8);
			image.setPixel(x, y, p);
		}
	}
}

int main(int argc, char* argv[])
{
	sf::Image input, output;
	if (!input.loadFromFile(argv[0]))
		return -1;
	FibLFSR* lsfr = new FibLFSR(argv[2]);

	sf::Vector2u size = input.getSize();
	sf::RenderWindow window1(sf::VideoMode(size.x, size.y), "Source Photo");
	sf::RenderWindow window2(sf::VideoMode(size.x, size.y), "Encrypted Photo");

	sf::Texture texture1, texture2;
	texture1.loadFromImage(input);
	transform(input, lsfr);
	output = input;
	texture2.loadFromImage(output);

	sf::Sprite sprite1, sprite2;
	sprite1.setTexture(texture1);
	sprite2.setTexture(texture2);

	while (window1.isOpen() && window2.isOpen())
	{
		sf::Event event;
		while (window1.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window1.close();
		}
		while (window2.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window2.close();
		}

		window1.clear(sf::Color::White);
		window1.draw(sprite1);
		window1.display();
		window2.clear();
		window2.draw(sprite2);
		window2.display();
	}

	// fredm: saving a PNG segfaults for me, though it does properly
	//   write the file
	if (!output.saveToFile(argv[1]))
		return -1;

	return 0;
}