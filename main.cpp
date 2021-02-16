#include <iostream>
#include <gmpxx.h>
#include <ctime>
#include <fstream>
#include <iomanip>


double PI = 3.141592653589793238462;

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::setprecision;


// Вычисление факториала целого числа
long get_factorial(long x){
	if (x == 1){
		return 1;
	}

	if (x == 0){
		return 1;
	}

	return x * get_factorial(x - 1);

}


// Вычисление целой степени большого числа
mpf_class get_pow(mpf_class x, int n){
	if (n == 1){
		return x;
	}

	if (n == 0){
		return 1;
	}

	if ((n % 2) == 0){
		mpf_class res;
		res = get_pow(x, n / 2);
		return res * res;
	}else{
		return x * get_pow(x, n - 1);
	}
}


// Вычисление синуса угла с помощью формулы маклорена
mpf_class get_sin(mpf_class x){
	mpf_class res, pres;
	res = 0;
	pres = 0;
	for (int n = 0; n < 10; n++){
		pres = get_pow(x, 2*n+1) / get_factorial(2*n+1);
		if((n % 2) == 1){
			pres = -pres;
		}
		res += pres;
	}
	return res;
}


// Вычисление косинуса угла с помощью формулы маклорена
mpf_class get_cos(mpf_class x){
	mpf_class res, pres;
	res = 0;
	pres = 0;
	for (int n = 0; n < 10; n++){
		pres = get_pow(x, 2*n) / get_factorial(2*n);
		if((n % 2) == 1){
			pres = -pres;
		}
		res += pres;
	}
	return res;
}


// Проверка на НЕпересечение с лузой
bool loose(mpf_class x, mpf_class y){

	if ((abs(x - 0) < 0.025) && (abs(y - 0) < 0.025)){
		return false;
	}

	if ((abs(x - 1) < 0.025) && (abs(y - 0) < 0.025)){
		return false;
	}

	if ((abs(x - 2) < 0.025) && (abs(y - 0) < 0.025)){
		return false;
	}

	if ((abs(x - 0) < 0.025) && (abs(y - 1) < 0.025)){
		return false;
	}

	if ((abs(x - 1) < 0.025) && (abs(y - 1) < 0.025)){
		return false;
	}

	if ((abs(x - 2) < 0.025) && (abs(y - 1) < 0.025)){
		return false;
	}

	return true;
}


// Вычисление тангенса наклона прямой
mpf_class get_k(mpf_class a){
	if (get_cos(a) == 0){
		mpf_class r;
		r = 2;
		r = get_pow(r, 20);  // определяем бесконечность
		return r;
	}
	return get_sin(a) / get_cos(a);
}


// Вычисление длины траектории
mpf_class get_len(mpf_class a){
	mpf_class res; res = 0;


	mpf_class k;
	k = get_k(a);

	//cout << "Angle a = " << a << " k = " << k << endl;

	if (k == 0){
		return 1;
	}


	mpf_class x; x = 0;
	mpf_class y; y = 0;
	mpf_class y1; y1 = 0;
	mpf_class x1; x1 = 0;

	mpf_class new_value; new_value = 0;

	// TODO: добавить вычисление пройденного расстояния
	do{
		//cout << x << " " << y << " " << k << endl;

		int coll_count = 0;  // техническая информация(для проверки работоспособности алгоритма)

		new_value = k * (0 - x) + y; 
		if (!(new_value == y)){
			if ((0 < new_value) && (new_value < 1)){
				x1 = 0;
				y1 = new_value;
				coll_count++;
			}
		}

		new_value = k * (2 - x) + y;
		if (!(new_value == y)){
			if ((0 < new_value) && (new_value < 1)){
				x1 = 2;
				y1 = new_value;
				coll_count++;
			}
		}

		// TODO: проверить деление на ноль
		new_value = (0 - y) / k + x;
		if (!(new_value == x)){
			if ((0 < new_value) && (new_value < 2)){
				x1 = new_value;
				y1 = 0;
				coll_count++;
			}
		}

		new_value = (1 - y) / k + x;
		if (!(new_value == x)){
			if ((0 < new_value) && (new_value < 2)){
				x1 = new_value;
				y1 = 1;
				coll_count++;
			}
		}

		if (coll_count != 1){
			cout << "ALERT: a = " << a << endl;
		}


		k = -k;  // меняем угол наклона луча

		res += sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));  // суммируем пройденное расстояние

		x = x1; y = y1;  // перемещаем бильярдный шар

		//cout << "ball set to x1 = " << x1 << ", y1 = " << y1 << endl;


	}while(loose(x, y));

	return res;
}


int main ()
{
    int n = 1000, dn = 2;
    
    ofstream outf("output.txt");
    if (!outf){
    	return 1;
    }

    mpf_class a, res;
    mp_exp_t exp(-10);
    res = 0;
    a = 0;

    int start = clock();  // засекаем время начала работы программы

    for(int iter_count = 1; iter_count <= 10; iter_count++){
    	res = 0;
	    for(int i = 0; i < n; i++){
	    	a = i * PI / n / 2;  // Вычисление угла броска шара
	    	res += get_len(a);  // Вычисление длины траектории
	    	//cout << "Progress for " << iter_count << "/" << 10;
	    	//cout << " " << i / n * 100 << "%" << endl;
	    }
	    res = res / n;
	    cout << "| " << iter_count << " | N = " << n << " | " << setprecision(20) << res << endl;
	    outf << "| " << iter_count << " | N = " << n << " | " << setprecision(20) << res << endl;
	    n *= dn;
	}

	int end = clock();
	cout << "Calculating ended in " << (end - start) / CLOCKS_PER_SEC << " seconds" << endl;

	return 0;
}