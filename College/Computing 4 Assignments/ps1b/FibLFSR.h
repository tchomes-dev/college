#include <string>
#include <array>
#include <valarray>
#include <sstream>

using namespace std;

class FibLFSR {
public:
    FibLFSR(string seed); // constructor to create LFSR with
    // the given initial seed and tap
    int step(); // simulate one step and return the
    // new bit as 0 or 1
    int generate(int k); // simulate k steps and return
    // k-bit integer
    void convertStringtoArray(string& s); //converts seed into an array of ints

    void shiftLeft(int arr[], int result); //made own function to shift elements in an array

    int getArray();

private:
    int seedArray[16]; //array comprised of each number in the seed
};