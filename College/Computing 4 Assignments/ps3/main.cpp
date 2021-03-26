#include "ED.h"
#include <fstream>
#include <SFML/System.hpp>

using namespace sf;

void readFile(string file, vector<string>& strings) {
    string thing;
    ifstream in(file);
    for (int i = 0; i < 2; i++) {
        in >> thing;
        strings.push_back(thing);
    }
}

int main(int argc, char* argv[]) {
    Clock clock;
    Time t;

    vector<string> strings;
    readFile("sequence/fli8.txt", strings);
    ED test(strings[0], strings[1]);
    t = clock.getElapsedTime();
    cout << "Execution time is " << t.asSeconds() << " seconds \n";
    return 0;
}

