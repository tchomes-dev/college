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
    friend istream& operator >>(istream& inStream, Vehicle& vObject);
    friend ostream& operator <<(ostream& outStream, const Vehicle& vObject);

private:
    string name;
    int cylinders;
    Person owner;
};

class Truck : public Vehicle {
public:
    Truck();
    Truck(double capacityTons, int capacityLbs);
    Truck(const Truck& other);

    double getCapacityTons() const{ return this->capacityTons; }
    int getCapacityLbs() const { return this->capacityLbs; }

    Truck& operator=(const Truck& other);
    friend istream& operator >>(istream& inStream, Truck& tObject);
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

Truck::Truck(double capacityTons, int capacityLbs) : Vehicle(getName(), getCylinder(), getOwner()) {
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
}

Vehicle& Vehicle::operator=(const Vehicle& other) {
    this->name = other.name;
    this->cylinders = other.cylinders;
    this->owner = other.owner;
}

Truck& Truck::operator=(const Truck& other) {
    this->capacityTons = other.capacityTons;
    this->capacityLbs = other.capacityLbs;
}

int main(int argv, char argc[]) {

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