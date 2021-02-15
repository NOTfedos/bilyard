#include <iostream>
#include <gmpxx.h>
using std::cout;
int main ()
{
    mpz_class a, b, c;
    a = 1234;
    b = "-567000000000000000000000008";
    c = a+b;
    cout << "sum is " << c << "\n";
    cout << "absolute value is " << abs(c) << "\n";
    return 0;
}