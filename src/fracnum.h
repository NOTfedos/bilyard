#ifndef FRACNUM_H
#define FRACNUM_H

#include <iostream>

using std::ostream;



// Classes
class Fraction{
public:
    Fraction(long x, long y =1);

    static Fraction cut_frac(const Fraction frac);

    long get_x() const;

    long get_y() const;

    double get_double() const;

    friend Fraction operator+(const Fraction& left, const Fraction& right);

    friend Fraction operator-(const Fraction& left, const Fraction& right);

    friend Fraction operator*(const Fraction& left, long c);

    friend Fraction operator*(const Fraction& left, const Fraction& right);

    friend Fraction operator/(const Fraction& left, const Fraction& right);

    Fraction pow(int n);

    friend ostream& operator<<(ostream& out, const Fraction& frac);

private:
    long x, y;
};


// Functions
long fast_pow(long x, int n);

#endif