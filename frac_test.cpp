#include "fracnum.hpp"


int main(){
	Fraction a = Fraction(1, 2);
	Fraction b = Fraction(2, 3);
	cout << a + b << endl;
	cout << a * b << endl;
	cout << a / b << endl;
	cout << a.pow(3) << endl;
	cout << a*4 << endl;
	return 0;
}