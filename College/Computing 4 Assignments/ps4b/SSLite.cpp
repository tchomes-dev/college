/*
  Copyright 2015 Fred Martin, 
  Y. Rykalova, 2020
*/
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <math.h>
#include <limits.h>

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>

#include "CircularBuffer.h"
#include "StringSound.h"

#define CONCERT_A 220.0
#define SAMPLES_PER_SEC 44100

using sf::Keyboard;

vector<sf::Int16> makeSamplesFromString(StringSound& gs) {
    std::vector<sf::Int16> samples;
    gs.pluck();
    int duration = 8;  // seconds
    int i;
    for (i = 0; i < SAMPLES_PER_SEC * duration; i++) {
        gs.tic();
        samples.push_back(gs.sample());
    }
    return samples;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(300, 200), "SFML String Sound Lite");
    sf::Event event;
    double freq;
    vector<sf::Sound> sounds;
    sf::SoundBuffer* buf;

    //keys
    Keyboard::Key keys[] = { Keyboard::Q, Keyboard::Num2, Keyboard::W, 
        Keyboard::E, Keyboard::Num4, Keyboard::R, Keyboard::Num5, Keyboard::T,
        Keyboard::Y, Keyboard::Num7, Keyboard::U, Keyboard::Num8, Keyboard::I,
        Keyboard::Num9, Keyboard::O, Keyboard::P, Keyboard::Dash, 
        Keyboard::LBracket, Keyboard::Equal, Keyboard::Z, Keyboard::X, 
        Keyboard::D, Keyboard::C, Keyboard::F, Keyboard::V, Keyboard::G, 
        Keyboard::B, Keyboard::N, Keyboard::J, Keyboard::M, Keyboard::K, 
        Keyboard::Comma, Keyboard::Period, Keyboard::SemiColon, 
        Keyboard::Slash, Keyboard::Quote, Keyboard::Space
    };

    for (int i = 0; i < 37; i++) {
        //creates samples
        vector<sf::Int16> sample;
        freq = 440 * pow(2, (i - 24) / 12);
        StringSound ss(freq);
        sample = makeSamplesFromString(ss);
        //loads samples to buffer
        buf = new sf::SoundBuffer;
        if (!buf->loadFromSamples(&sample[0], sample.size(), 2, SAMPLES_PER_SEC))
            throw std::runtime_error("sf::SoundBuffer: failed to load from samples.");
        //sets buffer to sound
        sf::Sound sound;
        sound.setBuffer(*buf);
        sounds.push_back(sound);
    }

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                for (int i = 0; i < 37; ++i) {
                    if (event.key.code == keys[i])
                        sounds[i].play();
                }
                break;
            default:
                break;
            }
            window.clear();
            window.display();
        }
    }
    return 0;
}
