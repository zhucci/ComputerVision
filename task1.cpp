/*
	Напишите функцию, которая перебирает натуральные числа от 1 до N включительно и раскладывает каждое число на простые множители. Результат можно выводить на экран либо копить в любой структуре данных.
	Реализация требуется на С++ и/или Python.
	C++
*/


#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <list>
#include <map>

typedef long integer;
typedef	std::map < integer, integer > factorization;

int main(int argc, char **argv){

	if (argc < 2)
		return 0;

	integer n = std::atol(argv[1]);

	if (n<0){
		return 0;
	}
	
	factorization *FactorCollection = new factorization[n + 1];

	integer * arrayOfDegree = new integer[n+1];
	memset(arrayOfDegree, 0, sizeof(integer)*(n+1));

	for (integer num = 2; num <= n; ++num){
		//проверка числа num на простоту
		if (!FactorCollection[num].size()){
		//вычисление степеней этого числа в разложениях всех чисел
			for (integer fact=num; fact <=n; fact*=num)
				for (integer j = fact; j <= n; j += fact)
					arrayOfDegree[j] +=1;
		//Сохранение результата в вектор структур factor
			for (integer i = 1; i <= n; i++){
				static integer degree;
				if (degree = arrayOfDegree[i]){
					FactorCollection[i].emplace(num,degree);
					arrayOfDegree[i] = 0;
				}
			}
		}
	}
	//вывод результата
	for (integer i = 1; i <= n; i++){
		auto end = FactorCollection[i].end();
		std::cout << i << " : ";
		bool second=false;
		for (auto iter = FactorCollection[i].begin(); iter != end; iter++){
			if (second)
				std::cout << " x ";
			else 
				second =true;
			std::cout << iter->first << "^" << iter->second ;
			
		}
		std::cout << '\n';
	}

	delete[] arrayOfDegree;
	delete[] FactorCollection;

	return 0;
}