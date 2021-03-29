#include "StringSound.h"

#define SAMPLERATE 44100

StringSound::StringSound(double frequency){
    double length = SAMPLERATE / frequency;
    _cb = new CircularBuffer(ceil(length));
    for (int i = 0; i < length; i++) {
        _cb->enqueue(0);
    }
    _cb->empty();
    _time = 0;
}

StringSound::StringSound(vector<sf::Int16> init){
    _cb = new CircularBuffer(init.size());
    for (auto obj : init) {
        _cb->enqueue(obj);
    }
    _time = 0;
}

StringSound::~StringSound() {
    delete _cb;
}

void StringSound::pluck() {
    if (_cb->isFull()) _cb->empty();
    while (!_cb->isFull()){
        std::random_device rd;
        std::mt19937 gen{ rd() };
        std::uniform_int_distribution<int16_t> dist(-32768, 32767);
        _cb->enqueue(dist(gen));
    }
}

void StringSound::tic(){
    sf::Int16 temp = _cb->dequeue();
    _cb->enqueue(.996 * 0.5 * (temp + _cb->peek()));
    _time++;
}

sf::Int16 StringSound::sample(){
    return _cb->peek();
}

int StringSound::time(){
    return _time;
}