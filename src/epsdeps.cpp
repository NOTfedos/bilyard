#include <iostream>
#include <gmpxx.h>
#include <ctime>
#include <fstream>
#include <iomanip>


using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::setprecision;


const double PI = 3.141592653589793238462;
double R = 0.07, R_end = 0.2, dR = 0.0005, R_ball = 0.034;//R_ball = 0.034;

const int n = 4096;


const string output_filename("../data/output_eps2.txt");

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

	if ((abs(x - 0) < R) && (abs(y - 0) < R)){
		return false;
	}

	if ((abs(x - 1) < R) && (abs(y - 0) < R)){
		return false;
	}

	if ((abs(x - 2) < R) && (abs(y - 0) < R)){
		return false;
	}

	if ((abs(x - 0) < R) && (abs(y - 1) < R)){
		return false;
	}

	if ((abs(x - 1) < R) && (abs(y - 1) < R)){
		return false;
	}

	if ((abs(x - 2) < R) && (abs(y - 1) < R)){
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
void get_len(mpf_class a, mpf_class &res_len, mpf_class &res_count){
	res_len = 0; res_count = 0;


	mpf_class k;
	k = get_k(a);


	if (k == 0){
		res_len = 1;
		res_count = 0;
		return;
	}


	mpf_class x; x = R_ball;
	mpf_class y; y = R_ball;
	mpf_class y1; y1 = 0;
	mpf_class x1; x1 = 0;

	mpf_class new_value; new_value = 0;


	int coll_count = 0;  // техническая информация(для проверки работоспособности алгоритма)


	// TODO: добавить вычисление пройденного расстояния
	do{

		//cout << x << " " << y << endl;

		coll_count = 0;

		// left border
		new_value = k * (0 - x) + y + R_ball * k; 
		if (x > R_ball){
			if ((R_ball <= new_value) && (new_value <= (1 - R_ball))){
				x1 = 0 + R_ball;
				y1 = new_value;

				// DEBUG
				// if ((y1 <= R_ball) || (y1 >= (1 - R_ball))){
				// 	cout << x1 << " " << y1 << " 1" << endl;
				// }

				coll_count++;
			}
		}

		// right border
		new_value = k * (2 - x) + y - R_ball * k;
		if (x < (2 - R_ball)){
			if ((R_ball <= new_value) && (new_value <= (1 - R_ball))){
				x1 = 2 - R_ball;
				y1 = new_value;

				// DEBUG
				// if ((y1 <= R_ball) || (y1 >= (1 - R_ball))){
				// 	cout << x1 << " " << y1 << " 2" << endl;
				// }

				coll_count++;
			}
		}

		// bottom border
		new_value = (0 - y) / k + x + R_ball / k;
		if (y > R_ball){
			if ((R_ball <= new_value) && (new_value <= (2 - R_ball))){
				x1 = new_value;
				y1 = 0 + R_ball;

				// DEBUG
				// if (!(R_ball < x1 < (2 - R_ball))){
				// 	cout << x1 << " " << y1 << " 3" << endl;
				// }

				coll_count++;
			}
		}

		// top border
		new_value = (1 - y) / k + x - R_ball / k;
		if (y < (1 - R_ball)){
			if ((R_ball <= new_value) && (new_value <= (2 - R_ball))){
				x1 = new_value;
				y1 = 1 - R_ball;

				// DEBUG
				// if (!(R_ball < x1 < (2 - R_ball))){
				// 	cout << x1 << " " << y1 << " 4" << endl;
				// }

				coll_count++;
			}
		}


		// если зарегали более одной точки столкновения со стенками
		if (coll_count != 1){
			cout << "---------------------------------------------------" << endl;
			cout << x << " " << y << endl;
			cout << "ALERT: a = " << a << " COUNT" << coll_count << endl;
			cout << "---------------------------------------------------" << endl;
		}


		k = -k;  // меняем угол наклона луча

		res_len += sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));  // суммируем пройденное расстояние
		res_count += 1;

		x = x1; y = y1;  // перемещаем бильярдный шар

		//cout << "ball set to x1 = " << x1 << ", y1 = " << y1 << endl;

	}while(loose(x, y));
}


int main ()
{   
    ofstream outf;
    outf.open(output_filename);

    if (!outf){
    	return 1;
    }


    mpf_class a, res_len, res_count, res, count;  // res_len - длина, res_count - кол-во столкновений
    a = 0;

    int start = clock();  // засекаем время начала работы программы

    for(; R <= R_end; R += dR){
    	res_len = 0; res_count = 0;
	    for(int i = 0; i < n; i++){
	    	a = i * PI / n / 2;  // Вычисление угла броска шара
	    	get_len(a, res, count);  // Вычисление длины траектории
	    	res_len += res;
	    	res_count += count;
	    }
	    res_len = res_len / n;
	    res_count = res_count / n;
	    cout << "| " << R << " | N = " << n << " | " << setprecision(20) << res_len << " | " << res_count << endl;
	    outf << R << " " << n << " " << setprecision(20) << res_len << " " << res_count << endl;
	}


	outf.close();  // явно закрываем файл


	int end = clock();
	cout << "Calculating ended in " << (end - start) / CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Data writeen into " << output_filename << endl;

	return 0;
}