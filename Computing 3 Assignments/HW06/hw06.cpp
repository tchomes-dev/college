/***********************************************
Author: <Tony Choma>
Date: <10-16-2020>
Purpose: <>
Sources of Help: <>
Time Spent: <>
***********************************************/

#include <string>
#include <iostream>

using namespace std;

class DynamicStringArray {
public:
    //constructor
    DynamicStringArray() {
        this->dynamicArray = new string[0];
        this->arraySize = 0;
    }
    DynamicStringArray(const DynamicStringArray& old);
    ~DynamicStringArray();

    DynamicStringArray operator=(const DynamicStringArray& old);

    //member functions
    int getSize() const { return this->arraySize; }
    void addEntry(string entry);
    bool deleteEntry(string entry);
    string getEntry(int index) const;
    

private:
    int arraySize;
    string* dynamicArray;    
};
DynamicStringArray::DynamicStringArray(const DynamicStringArray& old) {

}
DynamicStringArray::~DynamicStringArray() {

}
DynamicStringArray DynamicStringArray::operator=(const DynamicStringArray& old) {
   
    return *this;
}
void DynamicStringArray::addEntry(string entry) {
    string* temp = new string[arraySize + 1];

    if (arraySize == 0) {
        temp[0] = entry;
        arraySize++;
    } else {
        for (int i = 0; i <= arraySize; i++) {
            if (i == arraySize) {
                temp[i] = entry;
                cout << temp[i] << endl;
            } else {
                temp[i] = this->dynamicArray[i];
            }
        }
        arraySize++;
    }
    this->dynamicArray = temp;

}
bool DynamicStringArray::deleteEntry(string entry) {
    return false;
}
string DynamicStringArray::getEntry(int index) const{
    if (index > this->getSize()) {
        return "nullptr";
    }
    return this->dynamicArray[index];
}

int main(int argv, char argc[]) {
    DynamicStringArray test1;
    test1.addEntry("one");
    test1.addEntry("two");
    test1.addEntry("three");
    cout << test1.getEntry(0) << endl;
    cout << test1.getEntry(1) << endl;
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