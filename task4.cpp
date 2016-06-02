/*
	Имеется простой односвязный список размера N.Необходимо реализовать алгоритм, который перепаковывает список так, чтобы за первым элеметом следовал последний, затем второй, затем предпоследний и т.д.Пример работы алгоритма :
	исходный список : 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8
	перепакованный список : 1 - 8 - 2 - 7 - 3 - 6 - 4 - 5.
	Оценить сложность предложенного алгоритма.
	Реализация требуется на С++ и / или Python.
	C++
*/
#include <iostream>
#include <list>

//Node of linked list
struct someThing{
	int value;
	someThing() :value{ 0 },next{NULL}{}
	someThing *next;
};

int main(int argc, char **argv){
	std::cout << "You can specify an amount elements in array : bash-$ /.prog 10" << '\n';
	int n=8;
	if (argc > 1)
		n = std::atol(argv[1]);

	if (n <= 0){
		return 0;
	}

	someThing * deque = new someThing[n];

	for (int i = 0; i < n-1; i++){
		(deque+i)->value=i+1;
		(deque+i)->next = deque+i+1;
	}
	(deque+n-1)->value=n;
	//Обычная очередь 
	someThing *some = deque;
	while (some){
		std::cout << some->value << "-";
		some = some->next;
	}
	std::cout << '\n';
	//Перетасовка
	int iterAmount = n / 2;
	someThing * cur = deque;

	while (cur->next){
		cur=cur->next;
	}
	someThing *last = cur; 
	cur = deque;
	someThing *curNext = cur->next, *preLast = cur;

	//Общая сложность алгоритма ~O(n*n/4)

	while (curNext != last){ // O(n/2)
		//средняя сложность тела цикла ((n-1+5)+5)/2
		while (preLast->next !=last){ 
			preLast = preLast->next;
		}
		cur->next = last;
		last->next=curNext;
		cur = curNext;
		curNext = curNext->next;
		last = preLast;
	}
	last->next = NULL;
	

	// Перетасованная очередь
	some = deque;
	while (some){
		std::cout << some->value << "-";
		some = some->next;
	}
	std::cout << '\n';
	return 0;
}