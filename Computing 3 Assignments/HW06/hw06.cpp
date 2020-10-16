#include <string>
#include <vector>

using namespace std;

class DynamicStringArray {
public:
    //constructor
    DynamicStringArray() {
        this->dynamicArray[nullptr];
        this->size = 0;
    }
    //member functions
    int getSize() { return this->size; }
    void addEntry(string entry);
    void deleteEntry(string entry);
    string getEntry(int index);
    

private:
    vector<string> dynamicArray;
    int size;
};