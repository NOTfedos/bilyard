#include "fracnum.h"


// Functions

long fast_pow(long x, int n){
	if (n < 0){  // вообще лучше выкидывать исключение
		return 0;
	}

	if (x == 0){
		return 0;
	}

	if (n == 0){
		return 1;
	}

	if (n == 1){
		return x;
	}

	if (n % 2){
		return fast_pow(x, n - 1) * x;
	}else{
		long res = fast_pow(x, n /2);
		return res * res;
	}
}


// Class Fraction

Fraction::Fraction(long x, long y /*=1*/){
    this->x = x;
    this->y = y;
}

Fraction Fraction::cut_frac(const Fraction frac){
    // добавить сокращение дробей
    return frac;
}

long Fraction::get_x() const{
    return this->x;
}

long Fraction::get_y() const{
    return this->y;
}

double Fraction::get_double() const{
    return (double) this->x / (double) this->y;
}

//-------------------------------------Сложение-------------------------------------------
Fraction operator+(const Fraction& left, const Fraction& right){
	// проверить на переполнение!
	return Fraction::cut_frac(Fraction(left.get_x()*right.get_y() + left.get_y()*right.get_x(), left.get_y()*right.get_y()));
}

//-------------------------------------Вычитание------------------------------------------
Fraction operator-(const Fraction& left, const Fraction& right){
	// проверить на переполнение!
	return Fraction::cut_frac(Fraction(left.get_x()*right.get_y() - left.get_y()*right.get_x(), left.get_y()*right.get_y()));
}

//-------------------------------------Умножение на число----------------------------------
Fraction operator*(const Fraction& left, long c){
	// проверить на переполнение!
	return Fraction::cut_frac(Fraction(left.get_x() * c, left.get_y()));
}

//-------------------------------------Умножение на дробь----------------------------------
Fraction operator*(const Fraction& left, const Fraction& right){
	// проверить на переполнение!
	return Fraction::cut_frac(Fraction(left.get_x() * right.get_x(), left.get_y() * right.get_y()));
}

//-------------------------------------Деление на дробь------------------------------------
Fraction operator/(const Fraction& left, const Fraction& right){
	return Fraction::cut_frac(Fraction(left.get_x() * right.get_y(), left.get_y() * right.get_x()));
}

//-------------------------------------Возведение в целую степень--------------------------
Fraction Fraction::pow(int n){
	this->x = fast_pow(x, n);
	this->y = fast_pow(y, n);
	return *this;
}

//-------------------------------------Вывод (отладочный)-----------------------------------------------
ostream& operator<<(ostream& out, const Fraction& frac){
	out << "f " << frac.get_x() << "/" << frac.get_y();
	return out;
} 