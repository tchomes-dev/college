#include "CircularBuffer.h"
#include <SFML/System.hpp>
#include <vector>
#include <random>

using std::vector;

class StringSound {
public:
    explicit StringSound(double frequency);
    explicit StringSound(vector<sf::Int16> init);
    StringSound(const StringSound& obj) {};
    ~StringSound();
    void pluck();
    void tic();
    sf::Int16 sample();
    int time();
private:
    CircularBuffer* _cb;
    int _time;
};