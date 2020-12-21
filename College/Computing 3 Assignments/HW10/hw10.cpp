//
// HW10.cpp
//
#include <iostream>
#include <string>
#include <exception>

using namespace std;

void testPFArrayD(void);
void testException(void);

//Objects of this class are partially filled arrays of doubles.
class PFArrayD {
public:
    PFArrayD( );
    //Initializes with a capacity of 50.
    
    PFArrayD(int capacityValue);
    
    PFArrayD(const PFArrayD& pfaObject);
    
    void addElement(double element);
    //Precondition: The array is not full.
    //Postcondition: The element has been added.
    
    bool full( ) const { return (capacity == used); }
    //Returns true if the array is full, false otherwise.
    
    int getCapacity( ) const { return capacity; }
    
    int getNumberUsed( ) const { return used; }
    
    void emptyArray( ){ used = 0; }
    //Empties the array.
    
    double& operator[](int index);
    //Read and change access to elements 0 through numberUsed - 1.
    
    PFArrayD& operator=(const PFArrayD& rightSide);
    
    ~PFArrayD( );
private:
    double *a; //for an array of doubles.
    int capacity; //for the size of the array.
    int used; //for the number of array positions currently in use.
    
};

class OutOfRange : exception {
public:
    OutOfRange(string iMess, int iIndex) : indexError(iIndex), errorMessage(iMess) {}
    virtual const int index() noexcept { return indexError; }
    virtual const char* what() const noexcept { return errorMessage.c_str(); }
private:
    int indexError;
    string errorMessage;
};

//constructors
PFArrayD::PFArrayD() {
    a = new double[50];
    capacity = 50;
    used = 0;
}
PFArrayD::PFArrayD(int capacityValue) {
    a = new double[capacityValue];
    capacity = capacityValue;
    used = 0;
}
PFArrayD::PFArrayD(const PFArrayD& pfaObject) {
    a = pfaObject.a;
    capacity = pfaObject.capacity;
    used = pfaObject.used;
}

//destructor
PFArrayD::~PFArrayD() {
    delete a;
}

//member function
void PFArrayD::addElement(double element) {
    if (used == capacity) throw OutOfRange("Array is full\n", used);
    a[used] = element;
    used += 1;
}

//overloaded functions
double& PFArrayD::operator[](int index) {
    if (index > capacity) throw OutOfRange("Index is greater than capacity\n", index);
    return a[index];
}

PFArrayD& PFArrayD::operator=(const PFArrayD& rightSide) {
    a = rightSide.a;
    capacity = rightSide.capacity;
    used = rightSide.used;
    return *this;
}

int main(int argc, char *argv[])
{
     cout << "This program tests the class PFArrayD.\n";
     
     char ans;
     do
     {
         testException();
         cout << "Test again? (y/n) ";
         cin >> ans;
     }while ((ans == 'y') || (ans == 'Y'));
     
    return 0;
}

void testPFArrayD( ) {
    int cap;
    cout << "Enter capacity of this super array: ";
    cin >> cap;
    PFArrayD temp(cap);
    
    cout << "Enter up to " << cap << " nonnegative numbers.\n";
    cout << "Place a negative number at the end.\n";
    
    double next;
    cin >> next;
    while ((next >= 0) && (!temp.full( )))
    {
        temp.addElement(next);
        cin >> next;
    }
    
    cout << "You entered the following "
    << temp.getNumberUsed( ) << " numbers:\n";
    int index;
    int count = temp.getNumberUsed( );
    for (index = 0; index < count; index++)
        cout << temp[index] << " ";
    cout << endl;
    cout << "(plus a sentinel value.)\n";
}

void testException() {
    int cap;
    cout << "Enter capacity of this super array: ";
    cin >> cap;
    PFArrayD temp(cap);

    cout << "Enter up to " << cap << " nonnegative numbers.\n";
    cout << "Place a negative number at the end.\n";

    double next;
    cin >> next;
    try {
        while ((next >= 0))
        {
            temp.addElement(next);
            cin >> next;
        }
    }
    catch (const OutOfRange& er) {
        cout << er.what() << endl;
    }
    cout << "You entered the following "
        << temp.getNumberUsed() << " numbers:\n";
    int index;
    int count = temp.getNumberUsed();
    try {
        cout << temp[10] << " ";
    }
    catch (const OutOfRange& er) {
        cout << er.what() << endl;
    }
    cout << endl;
    cout << "(plus a sentinel value.)\n";
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
Date:   11-23-2020
Name:   Tony Choma
*/