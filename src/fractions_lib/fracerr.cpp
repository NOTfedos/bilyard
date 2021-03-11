#include "fracerr.h"

using std::overflow_error;

// Constructors
FractionErr::FractionErr(long val_x, long val_y, long err_x, long err_y){
    if ((val_y == 0) || (err_y == 0)){
        throw overflow_error("Zero denominator error");
    }
    this->val = Fraction(val_x, val_y);
    this->err = Fraction(err_x, err_y);
}

FractionErr::FractionErr(Fraction val, Fraction err /*=Fraction(0, 1)*/){
    this->val = val;
    this->err = err;
}


// Methods
Fraction FractionErr::get_value() const{
    // TODO: проверить!!!!
    return this->val;
}

Fraction FractionErr::get_error() const{
    // TODO: проверить!!!!
    return this->err;
}

void FractionErr::set_error(Fraction err){
    this->err = err;
}

// Definition of operators

//-------------------------------------Сложение-------------------------------------------
FractionErr operator+(const FractionErr& left, const FractionErr& right){
    return FractionErr(left.get_value() + right.get_value(), 
    (left.get_error() * left.get_value() + right.get_value() * right.get_error())/(left.get_value() + right.get_value()));
}

//-------------------------------------Вычитание------------------------------------------
FractionErr operator-(const FractionErr& left, const FractionErr& right){
    return FractionErr(left.get_value() - right.get_value(), 
    (left.get_error() * left.get_value() + right.get_value() * right.get_error())/(left.get_value() + right.get_value()));
}

//-------------------------------------Умножение на дробь----------------------------------
FractionErr operator*(const FractionErr& left, const FractionErr& right){
    return FractionErr(left.get_value() * right.get_value(), left.get_error() + right.get_error());
}

//-------------------------------------Деление на дробь------------------------------------
FractionErr operator/(const FractionErr& left, const FractionErr& right){
    return FractionErr(left.get_value() / right.get_value(), left.get_error() + right.get_error());
}

//-------------------------------------Умножение на число----------------------------------
FractionErr operator*(const FractionErr& left, long c){
    return FractionErr(left.get_value() * c, left.get_error());
}

//-------------------------------------Возведение в целую степень--------------------------
FractionErr& FractionErr::pow(int n){
    this->val = this->val.pow(n);
    this->err = this->err * n;
    return *this;
}

//-------------------------------------Вывод (отладочный)----------------------------------
ostream& operator<<(ostream& out, const FractionErr& frac){
	out << "fe: " << frac.get_value() << " er: " << frac.get_error();
	return out;
} 