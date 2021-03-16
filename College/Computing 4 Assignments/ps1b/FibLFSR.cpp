#include "FibLFSR.h"

FibLFSR::FibLFSR(string seed) {
    convertStringtoArray(seed);
}

int FibLFSR::step() {
    int result = seedArray[0];
    if (result == seedArray[2]) {
        result = 0;
    }
    else {
        result = 1;
    }
    if (result == seedArray[3]) {
        result = 0;
    }
    else {
        result = 1;
    }
    if (result == seedArray[5]) {
        result = 0;
    }
    else {
        result = 1;
    }
    shiftLeft(seedArray, result);
    return result;
}

int FibLFSR::generate(int k) {
    int result = 0;
    for (int i = 0; i < k; i++) {
        result = (result * 2) + step();
    }
    return result;
}

void FibLFSR::convertStringtoArray(string& s) {
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '1')
            seedArray[i] = 1;
        else if (s[i] == '0')
            seedArray[i] = 0;
    }
}

void FibLFSR::shiftLeft(int arr[], int result) {
    int temp = arr[0], i;
    for (i = 0; i < 16; i++)
        arr[i] = arr[i + 1];
    seedArray[15] = result;
}

int FibLFSR::getArray() {
    return *seedArray;
}