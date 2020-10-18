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
        this->dynamicArray[0];
        this->size = 0;
    }
    DynamicStringArray(int size) { 
        this->size = size;
        this->dynamicArray[size];
    }
    DynamicStringArray(const DynamicStringArray& old);
    ~DynamicStringArray();

    DynamicStringArray operator=(const DynamicStringArray& old);

    //member functions
    int getSize() const { return this->size; }
    void addEntry(string entry);
    bool deleteEntry(string entry);
    string getEntry(int index) const;
    

private:
    int size;
    string dynamicArray[];    
};
DynamicStringArray::DynamicStringArray(const DynamicStringArray& old) {
    for (int i = 0; i <= size; i++) {
        this->addEntry(old.getEntry(i));
    }
    this->size = old.size;
}
DynamicStringArray::~DynamicStringArray() {
    cout << "deleting" << endl;
    this->size = 0;
    this->dynamicArray[0] = {};
}
DynamicStringArray DynamicStringArray::operator=(const DynamicStringArray& old) {
    
    for (int i = 0; i <= old.size; i++) {
        this->addEntry(old.getEntry(i));
    }
    this->size = old.size;
    return *this;
}
void DynamicStringArray::addEntry(string entry) {
    DynamicStringArray temp(this->size++);
    temp.dynamicArray[temp.size-1] = entry;
    this = temp;
}
bool DynamicStringArray::deleteEntry(string entry) {
    DynamicStringArray newArray;
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (this->getEntry(i) == entry) {
            found = true;
        } else {
            newArray.addEntry(this->getEntry(i));
        }
    }
    *this = newArray;
    return found;
}
string DynamicStringArray::getEntry(int index) const{
    if (index > size) {
        return "nullptr";
    }
    return dynamicArray[index];
}

int main(int argv, char argc[]) {
    DynamicStringArray test1(2);
    test1.addEntry("hello");

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