/***********************************************
Author: <Tony Choma>
Date: <10-16-2020>
Purpose: <A dynamic array that changes size when entries are added or deleted>
Sources of Help: <geeksforgeeks, cplusplus>
Time Spent: <5>
***********************************************/

#include <string>
#include <iostream>

using namespace std;

class DynamicStringArray {
public:
    //constructor
    DynamicStringArray() {
        this->dynamicArray = nullptr;
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
DynamicStringArray::DynamicStringArray(const DynamicStringArray& other) {
    this->dynamicArray = other.dynamicArray;
    this->arraySize = other.arraySize;
}
DynamicStringArray::~DynamicStringArray() {
    
}
DynamicStringArray DynamicStringArray::operator=(const DynamicStringArray& other) {
    string* temp = new string[other.arraySize];
    for (int i = 0; i < other.arraySize; i++) {
        temp[i] = other.dynamicArray[i];
    }
    this->dynamicArray = temp;
    this->arraySize = other.arraySize;
    return *this;
}
void DynamicStringArray::addEntry(string entry) {
    string* temp = new string[arraySize + 1];

    for (int i = 0; i <= arraySize; i++) {
        if (i == arraySize) {
            temp[i] = entry;
        } else {     
            temp[i] = this->dynamicArray[i];
        }
    }
    arraySize++;
    this->dynamicArray = temp;
}
bool DynamicStringArray::deleteEntry(string entry) {
    bool found = false;
    int count = 0;
    for (int i = 0; i < arraySize; i++) {
        if (this->getEntry(i) == entry) {
            count++;
            found = true;
        }
    }
    string* temp = new string[arraySize - count];
    int tempIndex = 0;
    for (int i = 0; i < this->arraySize; i++) {
        if (this->dynamicArray[i] != entry) {
            temp[tempIndex] = this->dynamicArray[i];
            tempIndex++;
        }
    }
    this->dynamicArray = temp;
    this->arraySize = arraySize - count;
    return found;
}
string DynamicStringArray::getEntry(int index) const{
    if (index > this->getSize() || index < 0) {
        return nullptr;
    }
    return this->dynamicArray[index];
}

int main(int argv, char argc[]) {
    DynamicStringArray test1;
    DynamicStringArray test2;
    for (int i = 0; i <= 10; i++) {
        test1.addEntry(to_string(i)); 
        //cout << test1.getEntry(i) << endl;
    }
    for (int i = 10; i >= 0; i--) {
        test2.addEntry(to_string(i));
        //cout << test1.getEntry(i) << endl;
    }
    test1 = test2;
    for (int i = 0; i < test1.getSize(); i++) {
        cout << test1.getEntry(i) << endl;
    }
    cout << test1.getEntry(-1) << endl;
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