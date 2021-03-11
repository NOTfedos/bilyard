#ifndef FRACERR_H
#define FRACERR_H

#include "fracnum.h"

// Class Fraction with Error

class FractionErr{
public:
    FractionErr(Fraction val, Fraction err=Fraction(0, 1));

    FractionErr(long val_x, long val_y, long err_x, long err_y);

    // Getters
    Fraction get_value() const;

    Fraction get_error() const;

    // Setters
    void set_error(Fraction err);

    friend FractionErr operator+(const FractionErr& left, const FractionErr& right);

    friend FractionErr operator-(const FractionErr& left, const FractionErr& right);

    friend FractionErr operator*(const FractionErr& left, long c);

    friend FractionErr operator*(const FractionErr& left, const FractionErr& right);

    friend FractionErr operator/(const FractionErr& left, const FractionErr& right);

    FractionErr& pow(int n);

    friend ostream& operator<<(ostream& out, const FractionErr& frac);

private:
    Fraction val, err;  // val - значение дроби, err - её относительная погрешность
};

#endif