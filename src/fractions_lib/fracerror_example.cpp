#include "fracerr.h"
#include <iostream>

using std::cout;
using std::endl;

int main(){

    Fraction a = Fraction(1, 2);
    Fraction b = Fraction(2, 3);

    FractionErr ax = FractionErr(a);
    FractionErr bx = FractionErr(b, a);

    cout << ax.pow(3) << endl;
    cout << ax + bx << endl;
    cout << ax*bx << endl;

    return 0;
}