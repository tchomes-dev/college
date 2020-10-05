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
    Rational* operator+(const Rational b);
    Rational* operator-(const Rational b);
    Rational* operator*(const Rational b);
    Rational* operator/(const Rational b);
    // input/output operator overload declarations
    ostream& operator<<(ostream& out);
    istream& operator>>(istream& in);


private:
    int numerator;
    int denominator;
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
}

// relational operator overload definition
bool Rational::operator==(const Rational& b) { 
    if (this->numerator * b.denominator == this->denominator * b.numerator) {
        return true;
    }
    return false; 
}

bool Rational::operator<(const Rational& b) { 

    return false; 
}

bool Rational::operator<=(const Rational& b) { 
    if (this->numerator * b.denominator == this->denominator * b.numerator) {
        return true;
    }
    return false; 
}

bool Rational::operator>(const Rational& b) { 
    return false; 
}

bool Rational::operator>=(const Rational& b) { 
    if (this->numerator * b.denominator == this->denominator * b.numerator) {
        return true;
    }

    return false; 
}

// arithmetic operator overload definition
Rational* Rational::operator+(const Rational b) { 
    return this;
}

Rational* Rational::operator-(const Rational b) { 
    return this;
}

Rational* Rational::operator*(const Rational b) { 
    return this;
}

Rational* Rational::operator/(const Rational b) { 
    return this;
}

// input/output operator overload definition
ostream& Rational::operator<<(ostream& out) { 
    out << numerator << "/" << denominator;
    return out; 
}

istream& Rational::operator>>(istream& in) { 
    return in; 
}

int main(int argv, char argc[]) { 
    return 0; 
}