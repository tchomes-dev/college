// Copyright [2021] <Tony Choma>
#ifndef _HOME_VM_DOCUMENTS_PS4A_CIRCULARBUFFER_H_
#define _HOME_VM_DOCUMENTS_PS4A_CIRCULARBUFFER_H_
#include <stdint.h>
#include <string>
#include <exception>
#include <stdexcept>

using std::string;
using std::invalid_argument;
using std::runtime_error;


class CircularBuffer {
 public:
    struct Pointer {
        int index;
        int16_t pointer;
    };
    explicit CircularBuffer(int capacity);
    ~CircularBuffer();
    int getCurrSize();
    bool isEmpty();
    bool isFull();
    void enqueue(int16_t x);
    int16_t dequeue();
    int16_t peek();
 private:
    struct Pointer front, back;
    string c = "CircularBuffer constructor: capacity must be greater than 0";
    string e = "enqueue: can't enqueue to a full ring";
    string d = "dequeue: can't dequeue from an empty ring";
    int bufferSize, capacity;
    int16_t* buffer;
};

#endif  // _HOME_VM_DOCUMENTS_PS4A_CIRCULARBUFFER_H_
