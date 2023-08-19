#pragma once
#include <iostream>
#include <string>

extern bool hasException;

long long gcdEuclideanAlgo(long long, long long);

class Fraction {
public:
    Fraction();
    Fraction(const long long&, const long long&);
    Fraction(const char*);
    void operator=(const std::string&);
    void operator=(const Fraction&);
    void operator=(const long long&);
    friend std::ostream& operator<<(std::ostream&, const Fraction&);
    friend void operator>>(std::istream&, Fraction&);
    Fraction operator+(const Fraction&);
    Fraction operator+(const long long&);
    Fraction operator+=(const Fraction&);
    Fraction operator-(const Fraction&);
    Fraction operator-=(const Fraction&);
    Fraction operator*(const Fraction&);
    Fraction operator*(const long long&);
    Fraction operator*=(const Fraction&);
    Fraction operator*=(const long long&);
    Fraction operator/(const Fraction&);
    Fraction operator/=(const Fraction&);
    Fraction operator/=(const long long&);
    bool operator==(const std::string&);
    bool operator==(const long long&);
    bool operator<(const long long&);
    bool operator>(const long long&);
    bool operator!=(const long long&);

private:
    long long m_fraction[2];
};
