/***********************************************
Author: <Tony Choma>
Date: <10-6-2020>
Purpose: <Overload operators to support a custom class for rational numbers>
Sources of Help: <stackoverflow, wikipedia, tutorialspoint, geeksforgeeks>
Time Spent: <5 hours>
***********************************************/

#include <iostream>

using namespace std;

class Rational {
public:
    // constructor declarations
    Rational();
    Rational(int initWholeNumber);
    Rational(int initNumerator, int initDenominator);
    // relational operator overload declarations
    bool operator==(const Rational& b);
    bool operator<(const Rational& b);
    bool operator<=(const Rational& b);
    bool operator>(const Rational& b);
    bool operator>=(const Rational& b);
    // arithmtic operator overload declarations
    Rational operator+(Rational& b);
    Rational operator-(Rational& b);
    Rational operator*(Rational& b);
    Rational operator/(Rational& b);
    // input/output operator overload declarations
    friend ostream& operator<<(ostream& out, const Rational& a);
    friend istream& operator>>(istream& in, Rational& a);
    //other

private:
    int numerator = 0;
    int denominator = 0;

    int greatestCommDenom(const Rational& a);
    int greatestCommDenom(int a, int b);
    void simplify(Rational& a);
};

// constructor definition
Rational::Rational() {
    this->numerator = 0;
    this->denominator = 1;
}

Rational::Rational(int initWholeNumber) {
    this->numerator = initWholeNumber;
    this->denominator = 1;
}

Rational::Rational(int initNumerator, int initDenominator) {
    this->numerator = initNumerator;
    this->denominator = initDenominator;
    simplify(*this);
}

// relational operator overload definition
bool Rational::operator==(const Rational& b) { 
    if (this->numerator * b.denominator == this->denominator * b.numerator) {
        return true;
    }
    return false; 
}

bool Rational::operator<(const Rational& b) { 
    if (this->denominator > 0 && b.denominator > 0) {
        if (this->numerator * b.denominator < b.numerator * this->denominator) {
            return true;
        }
    }
    return false; 
}

bool Rational::operator<=(const Rational& b) { 
    if (this->numerator * b.denominator == this->denominator * b.numerator) {
        return true;
    }
    if (this->denominator > 0 && b.denominator > 0) {
        if (this->numerator * b.denominator < b.numerator * this->denominator) {
            return true;
        }
    }
    return false; 
}

bool Rational::operator>(const Rational& b) { 
    if (this->denominator > 0 && b.denominator > 0){
        if (b.numerator * this->denominator < this->numerator * b.denominator) {
            return true;
        }
    }
    return false; 
}

bool Rational::operator>=(const Rational& b) { 
    if (this->numerator * b.denominator == this->denominator * b.numerator) {
        return true;
    }
    if (this->denominator > 0 && b.denominator > 0) {
        if (b.numerator * this->denominator < this->numerator * b.denominator) {
            return true;
        }
    }
    return false; 
}

// arithmetic operator overload definition
Rational Rational::operator+(Rational& b) { 
    Rational result;
    result.numerator = (this->numerator * b.denominator) + (this->denominator * b.numerator);
    result.denominator = this->denominator * b.denominator;
    simplify(result);
    return result;
}

Rational Rational::operator-(Rational& b) { 
    Rational result;
    result.numerator = (this->numerator * b.denominator) - (this->denominator * b.numerator);
    result.denominator = this->denominator * b.denominator;
    simplify(result);
    return result;
}

Rational Rational::operator*(Rational& b) { 
    Rational result;
    result.numerator = this->numerator * b.numerator;
    result.denominator = this->denominator * b.denominator;
    simplify(result);
    return result;
}

Rational Rational::operator/(Rational& b) { 
    Rational result;
    result.numerator = this->numerator * b.denominator;
    result.denominator = this->denominator * b.numerator;
    simplify(result);
    return result;
}

// input/output operator overload definition
ostream& operator<<(ostream& out, const Rational& a) { 
    out << a.numerator << "/" << a.denominator;
    return out; 
}

istream& operator>>(istream& in, Rational& a) { 
    cout << "Enter numerator";
    cin >> a.numerator;
    cout << "Enter denominator";
    cin >> a.denominator;
    return in; 
}

//other 
int Rational::greatestCommDenom(const Rational& fraction) {
    int gcd = greatestCommDenom(fraction.numerator, fraction.denominator);
    int a = fraction.numerator;
    int b = fraction.denominator;

    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return gcd;
}
int Rational::greatestCommDenom(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}
//reduces a rational number to its simplist form
void Rational::simplify(Rational& a) {
    int gcd = greatestCommDenom(a);
    a.numerator /= gcd;
    a.denominator /= gcd;
    if (a.denominator < 0) {
        a.numerator *= -1;
        a.denominator *= -1;
    }
}

int main(int argv, char argc[]) { 
    Rational a(1, -2);
    cout << a << endl;
    Rational b(1, 4);
    a = a + b;
    cout << a << endl;
    return 0; 
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
Date: 10-6-2020
Name: Tony Choma
*/