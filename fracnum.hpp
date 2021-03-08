#include <iostream>
#include "fracnum.h"


using std::ostream;


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


class Fraction{
public:

	// конструктор

	Fraction(long x, long y=1){
		this->x = x;
		this->y = y;
	}

	static Fraction cut_frac(const Fraction frac){
		// добавить сокращение дробей
		return frac;
	}

	//-----------------------------------Получение полей(информации об объекте)---------------
	long get_x() const{
		return this->x;
	}

	long get_y() const{
		return this->y;
	}

	double get_double() const{
		return (double) this->x / (double) this->y;
	}

	//-------------------------------------ДЕЙСТВИЯ НАД ОБЪЕКТАМИ-----------------------------

	//-------------------------------------Сложение-------------------------------------------
	friend Fraction operator+(const Fraction& left, const Fraction& right){
		// проверить на переполнение!
		return cut_frac(Fraction(left.get_x()*right.get_y() + left.get_y()*right.get_x(), left.get_y()*right.get_y()));
	}


	//-------------------------------------Вычитание------------------------------------------
	friend Fraction operator-(const Fraction& left, const Fraction& right){
		// проверить на переполнение!
		return cut_frac(Fraction(left.get_x()*right.get_y() - left.get_y()*right.get_x(), left.get_y()*right.get_y()));
	}


	//-------------------------------------Умножение на число----------------------------------
	friend Fraction operator*(const Fraction& left, long c){
		// проверить на переполнение!
		return cut_frac(Fraction(left.get_x() * c, left.get_y()));
	}


	//-------------------------------------Умножение на дробь----------------------------------
	friend Fraction operator*(const Fraction& left, const Fraction& right){
		// проверить на переполнение!
		return cut_frac(Fraction(left.get_x() * right.get_x(), left.get_y() * right.get_y()));
	}


	//-------------------------------------Деление на дробь------------------------------------
	friend Fraction operator/(const Fraction& left, const Fraction& right){
		return cut_frac(Fraction(left.get_x() * right.get_y(), left.get_y() * right.get_x()));
	}

	//-------------------------------------Возведение в целую степень--------------------------
	Fraction pow(int n){
		this->x = fast_pow(x, n);
		this->y = fast_pow(y, n);
		return *this;
	}

	//-------------------------------------Вывод (отладочный)-----------------------------------------------
	friend ostream& operator<<(ostream& out, const Fraction& frac){
		out << "f " << frac.get_x() << "/" << frac.get_y();
		return out;
	} 

private:
	long x, y;
};