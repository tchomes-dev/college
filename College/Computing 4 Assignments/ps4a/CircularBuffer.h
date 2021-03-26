#include <stdint.h>
#include <array>
#include <exception>
#include <stdexcept>

using std::invalid_argument;
using std::runtime_error;

class CircularBuffer
{
public:
    struct Pointer {
        int index;
        int16_t pointer;
    };
    CircularBuffer(int capacity);
    ~CircularBuffer();
    int getCurrSize();
    bool isEmpty();
    bool isFull();
    void enqueue(int16_t x);
    int16_t dequeue();
    int16_t peek();
private:
    
    struct Pointer front, back;
    int bufferSize, capacity;
    int16_t* buffer;
};