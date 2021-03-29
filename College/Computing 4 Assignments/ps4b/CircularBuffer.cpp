// Copyright [2021] <Tony Choma>

#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(int capacity) {
    if (capacity < 0) {
        throw invalid_argument(c);
    } else {
        this->capacity = capacity;
        this->bufferSize = 0;

        this->buffer = new int16_t[capacity];
        front.index = 0;
        back.index = 0;
        if (capacity > 0) {
            front.pointer = buffer[0];
        }
    }
}

CircularBuffer::~CircularBuffer() {
    delete[] buffer;
}

int CircularBuffer::getCurrSize() {
    return bufferSize;
}

bool CircularBuffer::isEmpty() {
    return getCurrSize() == 0;
}

bool CircularBuffer::isFull() {
    return getCurrSize() == capacity;
}

void CircularBuffer::empty() {
    front.index = 0;
    back.index = 0;
    bufferSize = 0;
    front.pointer = buffer[front.index];
    back.pointer = buffer[back.index];
}

void CircularBuffer::enqueue(int16_t x) {
    if (isFull())
        throw runtime_error(e);
    if (isEmpty()) {
        buffer[front.index] = x;
        front.pointer = buffer[front.index];
    } else {
        back.index = (back.index + 1) % capacity;
        buffer[back.index] = x;
    }
    bufferSize++;
    back.pointer = buffer[back.index];
}

int16_t CircularBuffer::dequeue() {
    if (isEmpty()) throw runtime_error(d);
    int16_t old_front = buffer[front.index];
    buffer[front.index] = 0;
    bufferSize--;
    front.index = (front.index + 1) % capacity;
    front.pointer = buffer[front.index];
    return old_front;
}

int16_t CircularBuffer::peek() {
    if (isEmpty()) throw runtime_error("peek: can't peek from an empty ring");
    return front.pointer;
}
