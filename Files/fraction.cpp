#include <iostream>
#include <string>
#include <cstring>
#include <limits>
#include "fraction.h"

Fraction::Fraction():
    m_fraction{0, 1}{}

Fraction::Fraction(const long long& numerator, const long long& denominator):
    m_fraction{numerator, denominator}{}

Fraction::Fraction(const char* frac) {
    std::string fraction(frac);
    bool isFraction = false;

    for (int i = 0; i < fraction.length(); i++) {
        if (fraction[i] == '/') {
            isFraction = true;
            break;
        }
    }

    if (isFraction) {
        m_fraction[0] = std::stoi(fraction.substr(0, fraction.find('/')));
        m_fraction[1] = std::stoi(fraction.substr(fraction.find('/') + 1));
    }
    else {
        m_fraction[0] = std::stoi(fraction);
        m_fraction[1] = 1;
    }

    long long gcd = gcdEuclideanAlgo(m_fraction[0], m_fraction[1]);
    m_fraction[0] /= gcd;
    m_fraction[1] /= gcd;
}

void Fraction::operator=(const std::string& fraction) {
    bool isFraction = false;
    for (int i = 0; i < fraction.length(); i++) {
        if (fraction[i] == '/') {
            isFraction = true;
            break;
        }
    }
    if (isFraction) {
        std::string numerator = fraction.substr(0, fraction.find('/'));
        std::string denominator = fraction.substr(fraction.find('/') + 1, fraction.length() - fraction.find('/') - 1);
        m_fraction[0] = std::stoi(numerator);
        m_fraction[1] = std::stoi(denominator);
    }
    else {
        m_fraction[0] = std::stoi(fraction);
        m_fraction[1] = 1;
    }
}

void Fraction::operator=(const Fraction& other) {
    this->m_fraction[0] = other.m_fraction[0];
    this->m_fraction[1] = other.m_fraction[1];
}

void Fraction::operator=(const long long& other) {
    this->m_fraction[0] = other;
    this->m_fraction[1] = 1;
}

std::ostream& operator<<(std::ostream& cout, const Fraction& frac) {
    cout << frac.m_fraction[0];
    if (frac.m_fraction[1] != 1) {
        cout << '/' << frac.m_fraction[1];
    }
    return cout;
}

void operator>>(std::istream& cin, Fraction& frac) {
    std::string input;
    cin >> input;
    frac = input;
}

Fraction Fraction::operator*(const Fraction& other) {
    Fraction temp;

    if (this->m_fraction[0] == 0 || other.m_fraction[0] == 0) {
        temp.m_fraction[0] = 0;
        temp.m_fraction[1] = 1;
    }
    else {
        constexpr double longLongMax = std::numeric_limits<long long>::max();
        double thisNumerator = this->m_fraction[0] < 0 ? this->m_fraction[0] * -1.0 : this->m_fraction[0],
            thisDenominator = this->m_fraction[1],
            otherNumerator = other.m_fraction[0] < 0 ? other.m_fraction[0] * -1.0 : other.m_fraction[0],
            otherDenominator = other.m_fraction[1];

        if ((thisNumerator <= longLongMax / otherNumerator &&
            thisDenominator <= longLongMax / otherDenominator)) {
            temp.m_fraction[0] = this->m_fraction[0] * other.m_fraction[0];
            temp.m_fraction[1] = this->m_fraction[1] * other.m_fraction[1];
            long long gcd = gcdEuclideanAlgo(temp.m_fraction[0], temp.m_fraction[1]);
            temp.m_fraction[0] /= gcd;
            temp.m_fraction[1] /= gcd;
        }
        else {
            hasException = true;
        }
    }
    return temp;
}

Fraction Fraction::operator*(const long long& other) {
    Fraction temp;

    if (this->m_fraction[0] == 0 || other == 0) {
        temp.m_fraction[0] = 0;
        temp.m_fraction[1] = 1;
    }
    else {
        constexpr double longLongMax = std::numeric_limits<long long>::max();
        double thisNumerator = this->m_fraction[0] < 0 ? this->m_fraction[0] * -1.0 : this->m_fraction[0],
            otherLongLong = other < 0 ? other * -1.0 : other;

        if (thisNumerator <= longLongMax / otherLongLong) {
            temp.m_fraction[0] = this->m_fraction[0] * other;
            temp.m_fraction[1] = this->m_fraction[1];

            long long gcd = gcdEuclideanAlgo(temp.m_fraction[0], temp.m_fraction[1]);
            temp.m_fraction[0] /= gcd;
            temp.m_fraction[1] /= gcd;
        }
        else {
            hasException = true;  
        }  
    }

    return temp;
}

Fraction Fraction::operator*=(const Fraction& other) {

    if (this->m_fraction[0] == 0 || other.m_fraction[0] == 0) {
        this->m_fraction[0] = 0;
        this->m_fraction[1] = 1;
    }
    else {
        constexpr double longLongMax = std::numeric_limits<long long>::max();
        double thisNumerator = this->m_fraction[0] < 0 ? this->m_fraction[0] * -1.0 : this->m_fraction[0],
            thisDenominator = this->m_fraction[1],
            otherNumerator = other.m_fraction[0] < 0 ? other.m_fraction[0] * -1.0 : other.m_fraction[0],
            otherDenominator = other.m_fraction[1];

        if (thisDenominator <= longLongMax / otherDenominator &&
            thisNumerator <= longLongMax / otherNumerator) {
            this->m_fraction[0] *= other.m_fraction[0];
            this->m_fraction[1] *= other.m_fraction[1];
            long long gcd = gcdEuclideanAlgo(this->m_fraction[0], this->m_fraction[1]);
            this->m_fraction[0] /= gcd;
            this->m_fraction[1] /= gcd;
        }
        else {
            hasException = true;
        }
    }
    return *this;
}

Fraction Fraction::operator*=(const long long& other) {
    
    if (this->m_fraction[0] == 0 || other == 0) {
        this->m_fraction[0] = 0;
        this->m_fraction[1] = 1;
    }
    else {
        constexpr double longLongMax = std::numeric_limits<long long>::max();
        double thisNumerator = this->m_fraction[0] < 0 ? this->m_fraction[0] * -1.0 : this->m_fraction[0],
            otherLongLong = other < 0 ? other * -1.0 : other;

        if (thisNumerator <= longLongMax / otherLongLong) {
            this->m_fraction[0] = this->m_fraction[0] * other;
            this->m_fraction[1] = this->m_fraction[1];

            long long gcd = gcdEuclideanAlgo(this->m_fraction[0], this->m_fraction[1]);
            this->m_fraction[0] /= gcd;
            this->m_fraction[1] /= gcd;
        }
        else {
            hasException = true;
        }
    }
    return *this;
}

Fraction Fraction::operator/(const Fraction& other) {
    Fraction temp;

    constexpr double longLongMax = std::numeric_limits<long long>::max();
    double thisNumerator = this->m_fraction[0] < 0 ? this->m_fraction[0] * -1.0 : this->m_fraction[0],
            thisDenominator = this->m_fraction[1],
            otherNumerator = other.m_fraction[0] < 0 ? other.m_fraction[0] * -1.0 : other.m_fraction[0],
            otherDenominator = other.m_fraction[1];

    if (thisDenominator <= longLongMax / otherNumerator &&
        thisNumerator <= longLongMax / otherDenominator) {
        temp.m_fraction[0] = this->m_fraction[0] * other.m_fraction[1];
        temp.m_fraction[1] = this->m_fraction[1] * other.m_fraction[0];
        if ((temp.m_fraction[0] >= 0 && temp.m_fraction[1] < 0) ||
            (temp.m_fraction[0] < 0 && temp.m_fraction[1] < 0)) {

            temp.m_fraction[0] *= -1;
            temp.m_fraction[1] *= -1;
        }
        long long gcd = gcdEuclideanAlgo(temp.m_fraction[0], temp.m_fraction[1]);
        temp.m_fraction[0] /= gcd;
        temp.m_fraction[1] /= gcd;
    }
    else {
        hasException = true;
    }
    return temp;
}

Fraction Fraction::operator/=(const Fraction& other) {

    constexpr double longLongMax = std::numeric_limits<long long>::max();
    double thisNumerator = this->m_fraction[0] < 0 ? this->m_fraction[0] * -1.0 : this->m_fraction[0],
        thisDenominator = this->m_fraction[1],
        otherNumerator = other.m_fraction[0] < 0 ? other.m_fraction[0] * -1.0 : other.m_fraction[0],
        otherDenominator = other.m_fraction[1];

    if (thisDenominator <= longLongMax / otherNumerator &&
        thisNumerator <= longLongMax / otherDenominator) {
        this->m_fraction[0] *= other.m_fraction[1];
        this->m_fraction[1] *= other.m_fraction[0];
        if ((this->m_fraction[0] >= 0 && this->m_fraction[1] < 0) ||
            (this->m_fraction[0] < 0 && this->m_fraction[1] < 0)) {

            this->m_fraction[1] *= -1;
            this->m_fraction[0] *= -1;
        }
        long long gcd = gcdEuclideanAlgo(this->m_fraction[0], this->m_fraction[1]);
        this->m_fraction[0] /= gcd;
        this->m_fraction[1] /= gcd;
    }
    else {
        hasException = true;   
    }
    return *this;
}

Fraction Fraction::operator/=(const long long& other) {

    constexpr double longLongMax = std::numeric_limits<long long>::max();
    double thisDenominator = this->m_fraction[1],
        otherLongLong = other < 0 ? other * -1.0 : other;

    if (thisDenominator <= longLongMax / otherLongLong) {
        this->m_fraction[1] *= other;
        if ((this->m_fraction[0] >= 0 && this->m_fraction[1] < 0) ||
            (this->m_fraction[0] < 0 && this->m_fraction[1] < 0)) {

            this->m_fraction[1] *= -1;
            this->m_fraction[0] *= -1;
        }
        long long gcd = gcdEuclideanAlgo(this->m_fraction[0], this->m_fraction[1]);
        this->m_fraction[0] /= gcd;
        this->m_fraction[1] /= gcd;
    }
    else {
        hasException = true;
    }
    return *this;
}

Fraction Fraction::operator+=(const Fraction& other) {

    constexpr double longLongMax = std::numeric_limits<long long>::max();
    double thisNumerator = this->m_fraction[0] < 0 ? this->m_fraction[0] * -1.0 : this->m_fraction[0],
        thisDenominator = this->m_fraction[1],
        otherNumerator = other.m_fraction[0] < 0 ? other.m_fraction[0] * -1.0 : other.m_fraction[0],
        otherDenominator = other.m_fraction[1];

    if (thisDenominator <= longLongMax / otherDenominator) {
        long long lcm = (this->m_fraction[1] * other.m_fraction[1]) / gcdEuclideanAlgo(this->m_fraction[1], other.m_fraction[1]);
        lcm = lcm < 0 ? lcm * -1 : lcm;

        double thisDenomFactor = lcm / this->m_fraction[1], otherDenomFactor = lcm / other.m_fraction[1];

        if ((thisNumerator == 0 || thisDenomFactor <= longLongMax / thisNumerator) &&
            otherNumerator == 0 || otherDenomFactor <= longLongMax / otherNumerator) {
            this->m_fraction[0] = (lcm / this->m_fraction[1]) * this->m_fraction[0] + (lcm / other.m_fraction[1]) * other.m_fraction[0];
            this->m_fraction[1] = lcm;
            long long gcd = gcdEuclideanAlgo(this->m_fraction[0], this->m_fraction[1]);
            this->m_fraction[0] /= gcd;
            this->m_fraction[1] /= gcd;
        }
        else {
            hasException = true;
        }
    }
    else {
        hasException = true;
    }   
    return *this;
}

Fraction Fraction::operator+(const Fraction& other) {
    Fraction temp;

    constexpr double longLongMax = std::numeric_limits<long long>::max();
    double thisNumerator = this->m_fraction[0] < 0 ? this->m_fraction[0] * -1.0 : this->m_fraction[0],
        thisDenominator = this->m_fraction[1],
        otherNumerator = other.m_fraction[0] < 0 ? other.m_fraction[0] * -1.0 : other.m_fraction[0],
        otherDenominator = other.m_fraction[1];

    if (thisDenominator <= longLongMax / otherDenominator) {
        long long lcm = (this->m_fraction[1] * other.m_fraction[1]) / gcdEuclideanAlgo(this->m_fraction[1], other.m_fraction[1]);
        lcm = (lcm < 0) ? lcm * -1 : lcm;

        double thisDenomFactor = lcm / this->m_fraction[1], otherDenomFactor = lcm / other.m_fraction[1];

        if ((thisNumerator == 0 || thisDenomFactor <= longLongMax / thisNumerator) &&
            otherNumerator == 0 || otherDenomFactor <= longLongMax / otherNumerator) {

            temp.m_fraction[0] = (lcm / this->m_fraction[1]) * this->m_fraction[0] + (lcm / other.m_fraction[1]) * other.m_fraction[0];
            temp.m_fraction[1] = lcm;
            long long gcd = gcdEuclideanAlgo(temp.m_fraction[0], temp.m_fraction[1]);
            temp.m_fraction[0] /= gcd;
            temp.m_fraction[1] /= gcd;
        }
        else {
            hasException = true;
        }
    }
    else {
        hasException = true;
    } 
    return temp;
}

Fraction Fraction::operator+(const long long& other) {
    Fraction temp;

    constexpr double longLongMax = std::numeric_limits<long long>::max();
    double thisNumerator = this->m_fraction[0] < 0 ? this->m_fraction[0] * -1 : this->m_fraction[0],
        thisDenominator = this->m_fraction[1],
        otherLongLong = other < 0 ? other * -1 : other;

    if ((otherLongLong <= longLongMax / thisDenominator) && 
        (thisNumerator <= longLongMax - otherLongLong * thisDenominator)) {
        temp.m_fraction[0] = this->m_fraction[0] + other * this->m_fraction[1];
        temp.m_fraction[1] = this->m_fraction[1];
    }
    else {
        hasException = true;
    }
    return temp;
}

Fraction Fraction::operator-=(const Fraction& other) {

    constexpr double longLongMax = std::numeric_limits<long long>::max();
    double thisNumerator = this->m_fraction[0] < 0 ? this->m_fraction[0] * -1.0 : this->m_fraction[0],
        thisDenominator = this->m_fraction[1],
        otherNumerator = other.m_fraction[0] < 0 ? other.m_fraction[0] * -1.0 : other.m_fraction[0],
        otherDenominator = other.m_fraction[1];
    
    if (thisDenominator <= longLongMax / otherDenominator) {
        long long lcm = (this->m_fraction[1] * other.m_fraction[1]) / gcdEuclideanAlgo(this->m_fraction[1], other.m_fraction[1]);
        lcm = (lcm < 0) ? lcm * -1 : lcm;

        double thisDenomFactor = lcm / this->m_fraction[1], 
            otherDenomFactor = lcm / other.m_fraction[1];

        if ((thisNumerator == 0 || thisDenomFactor <= longLongMax / thisNumerator) &&
            otherNumerator == 0 || otherDenomFactor <= longLongMax / otherNumerator) {
            
            this->m_fraction[0] = (lcm / this->m_fraction[1]) * this->m_fraction[0] - (lcm / other.m_fraction[1]) * other.m_fraction[0];
            this->m_fraction[1] = lcm;
            long long gcd = gcdEuclideanAlgo(this->m_fraction[0], this->m_fraction[1]);
            this->m_fraction[0] /= gcd;
            this->m_fraction[1] /= gcd;
        }
        else {
            hasException = true;
        }
    }
    else {
        hasException = true; 
    }
    return *this;
}

Fraction Fraction::operator-(const Fraction& other) {
    Fraction temp;

    constexpr double longLongMax = std::numeric_limits<long long>::max();
    double thisNumerator = this->m_fraction[0] < 0 ? this->m_fraction[0] * -1.0 : this->m_fraction[0],
        thisDenominator = this->m_fraction[1],
        otherNumerator = other.m_fraction[0] < 0 ? other.m_fraction[0] * -1.0 : other.m_fraction[0],
        otherDenominator = other.m_fraction[1];

    if (thisDenominator <= longLongMax / otherDenominator) {
        long long lcm = (this->m_fraction[1] * other.m_fraction[1]) / gcdEuclideanAlgo(this->m_fraction[1], other.m_fraction[1]);
        lcm = (lcm < 0) ? lcm * -1 : lcm;

        double thisDenomFactor = lcm / this->m_fraction[1],
            otherDenomFactor = lcm / other.m_fraction[1];

        if ((thisNumerator == 0 || thisDenomFactor <= longLongMax / thisNumerator) &&
            otherNumerator == 0 || otherDenomFactor <= longLongMax / otherNumerator) {
            temp.m_fraction[0] = (lcm / this->m_fraction[1]) * this->m_fraction[0] - (lcm / other.m_fraction[1]) * other.m_fraction[0];
            temp.m_fraction[1] = lcm;
            long long gcd = gcdEuclideanAlgo(temp.m_fraction[0], temp.m_fraction[1]);
            temp.m_fraction[0] /= gcd;
            temp.m_fraction[1] /= gcd;
        }
        else {
            hasException = true;
        }
    }
    else {
        hasException = true;    
    }
    return temp;
}

bool Fraction::operator==(const std::string& fraction) {
    bool isEqual = false;
    bool isFraction = false;
    
    for (int i = 0; i < fraction.length(); i++) {
        if (fraction[i] == '/') {
            isFraction = true;
            break;
        }
    }
    if (isFraction) {
        std::string numerator = fraction.substr(0, fraction.find('/'));
        std::string denominator = fraction.substr(fraction.find('/') + 1, fraction.length() - fraction.find('/') - 1);
        if (m_fraction[0] == std::stoi(numerator) && m_fraction[1] == std::stoi(denominator)) {
            isEqual = true;
        }  
    }
    else {
        if (m_fraction[0] == stoi(fraction) && m_fraction[1] == 1) {
            isEqual = true;
        } 
    }
    return isEqual;
}

bool Fraction::operator==(const long long& other) {
    if (this->m_fraction[0] == other && this->m_fraction[1] == 1) {
        return true;
    }
    else {
        return false;
    }
}

bool Fraction::operator<(const long long& other) {

    double thisFraction = (this->m_fraction[0] * 1.0) / this->m_fraction[1],
        otherLongLong = other;

    if (thisFraction < otherLongLong) {
        return true;
    }
    else {
        return false;
    }
}

bool Fraction::operator>(const long long& other) {

    double thisFraction = (this->m_fraction[0] * 1.0) / this->m_fraction[1],
        otherLongLong = other;

    if (thisFraction > otherLongLong) {
        return true;
    }
    else {
        return false;
    }
}

bool Fraction::operator!=(const long long& other) {
    if (this->m_fraction[0] == other && this->m_fraction[1] == 1) return false;
    else return true;
}

long long gcdEuclideanAlgo(long long a, long long b) {
    a = (a < 0) ? a * -1 : a;
    // b = (b < 0) ? b * -1 : b;
    long long dividend = (a >= b) ? a : b;
    long long divisor = (a <= b) ? a : b;
    if (divisor == 0) {
        return dividend;
    }
    long long remainder = dividend % divisor;
    if (remainder == 0) {
        return divisor;
    }
    else {
        gcdEuclideanAlgo(remainder, divisor);
    }
}
