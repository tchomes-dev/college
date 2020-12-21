#include <string>
#include <iostream>

using namespace std;

class Person
{
public:
    Person();
    Person(string theName);
    Person(const Person& theObject);

    string getName() const { return this->name; }

    Person& operator=(const Person& other);
    friend istream& operator >>(istream& inStream, Person& personObject);
    friend ostream& operator <<(ostream& outStream, const Person& pObject);

private:
    string name;
};

class Vehicle {
public:
    Vehicle();
    Vehicle(string name, int cylinders, const Person& owner);
    Vehicle(const Vehicle& other);

    string getName() const { return this->name; }
    int getCylinder() const { return this->cylinders; }
    Person getOwner() const { return this->owner; }

    Vehicle& operator=(const Vehicle& other);
    friend ostream& operator <<(ostream& outStream, const Vehicle& vObject);

protected:
    string name;
    int cylinders;
    Person owner;
};

class Truck : public Vehicle {
public:
    Truck();
    Truck(string name, int cylinders, const Person& owner, double capacityTons, int capacityLbs);
    Truck(const Truck& other);

    double getCapacityTons() const{ return this->capacityTons; }
    int getCapacityLbs() const { return this->capacityLbs; }

    Truck& operator=(const Truck& other);
    friend ostream& operator <<(ostream& outStream, const Truck& tObject);

private:
    double capacityTons;
    int capacityLbs;
};

//constructors
//----------------------

//Person
Person::Person() {
    this->name = "none";
}

Person::Person(string theName) {
    this->name = theName;
}

Person::Person(const Person& other) {
    this->name = other.name;
}

//Vehicle
Vehicle::Vehicle() {
    this->name = "Unknown";
    this->cylinders = 0;
    this->owner = Person("Unknown");
}

Vehicle::Vehicle(string name, int cylinders, const Person& owner) {
    this->name = name;
    this->cylinders = cylinders;
    this->owner = owner;
}

Vehicle::Vehicle(const Vehicle& other) {
    this->name = other.name;
    this->cylinders = other.cylinders;
    this->owner = other.owner;
}

//Truck
Truck::Truck() : Vehicle() {
    this->capacityTons = 0.0;
    this->capacityLbs = 0;
}

Truck::Truck(string name, int cylinders, const Person& owner, double capacityTons, int capacityLbs) : Vehicle(name, cylinders, owner) {
    this->capacityTons = capacityTons;
    this->capacityLbs = capacityLbs;
}

Truck::Truck(const Truck& other) : Vehicle(other.getName(), other.getCylinder(), other.getOwner()){
    this->capacityTons = other.capacityTons;
    this->capacityLbs = other.capacityLbs;
}

//overloaded operators
//---------------------
Person& Person::operator=(const Person& other) {
    this->name = other.name;
    return *this;
}

Vehicle& Vehicle::operator=(const Vehicle& other) {
    this->name = other.name;
    this->cylinders = other.cylinders;
    this->owner = other.owner;
    return *this;
}

Truck& Truck::operator=(const Truck& other) {
    this->capacityTons = other.capacityTons;
    this->capacityLbs = other.capacityLbs;
    return *this;
}

istream& operator>>(istream& inStream, Person& pObject) {
    cout << "Enter your name: ";
    inStream >> pObject.name;
    return inStream;
}


ostream& operator<<(ostream& outStream, const Person& pObject) {
    outStream << pObject.getName();
    return outStream;
}

ostream& operator<<(ostream& outStream, const Vehicle& vObject) {
    outStream << vObject.getName() << ", " << vObject.getCylinder() << " cylinders, belongs to: " << vObject.getOwner();
    return outStream;
}

ostream& operator<<(ostream& outStream, const Truck& tObject) {
    outStream << tObject.getName() << ", " << tObject.getCylinder() << " cylinders, belongs to: " << tObject.getOwner() <<
        ", load capacity: " << tObject.getCapacityTons() << ", towing capacity: " << tObject.getCapacityLbs();
    return outStream;
}

int main(int argv, char argc[]) {
    cout << "////////////////// Testing Person Class ///////////////////" << endl;
    Person personDefault;
    cout << "Testing default constructor: the person is: " << personDefault << endl;
    Person person1("Tony");
    cout << "Testing constructor(string): I am: " << person1 << endl;
    Person copyPerson1(person1);
    cout << "Testing copy constructor: another me is: " << copyPerson1 << endl;
    Person person2;
    cin >> person2;
    cout << "You're: " << person2 << endl;
    Person copyPerson2 = person2;
    cout << "Testing = overloading: Another you is: " << copyPerson2 << endl;

    cout << "///////////////// Testing Vehicle Class ////////////////" << endl;
    Vehicle vehicleDefault;
    cout << "Testing default constructor: the Vehicle is:" << endl;
    cout << vehicleDefault << endl;
    Vehicle vehicle1("Ford Van", 8, person1);
    cout << "Testing constructor(args): for my car:" << endl;
    cout << vehicle1 << endl;
    Vehicle copyVehicle1(vehicle1);
    cout << "Testing copy constructor: my second same car:" << endl;
    cout << copyVehicle1 << endl;
    Vehicle copyVehicle2 = vehicle1;
    cout << "Testing = overloading:" << endl;
    cout << "Your car is: " << vehicle1;
    cout << "Your second car is: " << copyVehicle2 << endl;

    cout << "///////////////// Testing Truck Class ////////////////" << endl;
    Truck truckDefault;
    cout << "Testing default constructor: the Truck is:" << endl;
    cout << truckDefault << endl;
    Truck truck1("Toyota", 6, Person("Fred"), 250, 2000);
    cout << "Testing constructor(args): for a truck:" << endl;
    cout << truck1 << endl;
    Truck truckCopy1(truck1);
    cout << "Testing copy constructor: copied truck:" << endl;
    cout << truckCopy1 << endl;
    Truck truck2("Toyota", 8, Person("Fred"), 500, 5000);
    Truck truckCopy2 = truck2;
    cout << "Testing = overloading:" << endl;
    cout << "Your truck is: " << truck2 << endl;
    cout << "Your second truck is: " << truckCopy2 << endl;
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
Date:   11-10-2020  
Name:   Tony Choma
*/