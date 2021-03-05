#include "fracnum.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main(){
	Fraction a = Fraction(1, 2);
	Fraction b = Fraction(2, 3);
	cout << (a + b).pow(3) << endl;
	cout << a * b << endl;
	cout << a / b << endl;
	cout << a.pow(3) << endl;
	cout << a*4 << endl;
	return 0;
}