/***********************************************
Author: <Tony Choma>
Date: <10-16-2020>
Purpose: <>
Sources of Help: <>
Time Spent: <>
***********************************************/

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
    DynamicStringArray(const DynamicStringArray& old);
    ~DynamicStringArray();

    DynamicStringArray operator=(const DynamicStringArray& old);

    //member functions
    int getSize() { return this->size; }
    void addEntry(string entry);
    bool deleteEntry(string entry);
    string getEntry(int index) {};
    

private:
    vector<string> dynamicArray;
    int size;    
};
DynamicStringArray::DynamicStringArray(const DynamicStringArray& old) {
    for (int i = 0; i <= size; i++) {
        this->dynamicArray.push_back(old.dynamicArray.at(i));
    }
    this->size = old.size;
}
DynamicStringArray::~DynamicStringArray() {

}
DynamicStringArray DynamicStringArray::operator=(const DynamicStringArray& old) {
    for (int i = 0; i <= size; i++) {
        this->dynamicArray.push_back(old.dynamicArray.at(i));
    }
    this->size = old.size;
}
void DynamicStringArray::addEntry(string entry) {
    vector<string> newArray;
    newArray.push_back(entry);
    size++;
    dynamicArray = newArray;
}
bool DynamicStringArray::deleteEntry(string entry) {
    vector<string> newArray;
    for (int i = 0; i < size; i++) {
        if (dynamicArray.at(i) != entry) {
            continue;
        } else {
            newArray.push_back(dynamicArray.at(i));
        }
    }
    
}
string DynamicStringArray::getEntry(int index) {
    if (index > size) {
        return nullptr;
    }
    return dynamicArray[index];
}

/*
Computing III -- COMP.2010 Honor Statement
The practice of good ethical behavior is essential for maintaining
good order in the classroom, providing an enriching learning
experience for students, and as training as a practicing computing
professional upon graduation. This practice is manifested in the
University’s Academic Integrity policy. Students are expected to
strictly avoid academic dishonesty and adhere to the Academic
Integrity policy as outlined in the course catalog. Violations will
be dealt with as outlined therein.
All programming assignments in this class are to be done by the
student alone. No outside help is permitted except the instructor and
approved tutors.
I certify that the work submitted with this assignment is mine and was
generated in a manner consistent with this document, the course
academic policy on the course website on Blackboard, and the UMass
Lowell academic code.
Date:   10-18-2020
Name:   Tony Choma
*/