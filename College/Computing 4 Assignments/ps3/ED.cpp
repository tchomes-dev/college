#include "ED.h"

ED::ED(string dna1, string dna2) {
    this->dna1 = dna1;
    this->dna2 = dna2;

}
int ED::penalty(char a, char b) {
    int penalty = 0;
    if (a == b) {
        penalty = 0;
    }
    else {
        if (a == ' ') {
            penalty = 2;
        }
        else if (b == ' ') {
            penalty = 2;
        }
        else {
            penalty = 1;
        }
    }
    return penalty;
}

int ED::min(int a, int b, int c) {
    if (a < b || a < c) {
        return a;
    }
    else if (b < a || b < c) {
        return b;
    }
    else {
        return c;
    }
}

int ED::OptDistance() {

}

string ED::alignment() {

}
string ED::spaceFill