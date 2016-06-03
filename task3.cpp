/*
	Напишите простую реализацию функции для разбора параметров командной строки(getopt).
	Полагаем, что нам требуется структура данных, содержащая заранее известный допустимый набор параметров различного типа - строки, целые, числа с плавающей точкой и т.д., а также признак, является ли этот параметр обязательным.
	Полагаем, что параметры могут передаваться только в "длинном" формате с обязательным "--" перед именем параметра(то есть "--my-option-name my-option-val", "--my-option-name=my-option-val", "--my-boolean-option").
	Параметров может быть несколько.
	Функция должна обязательно уметь обрабатывать параметр "--help" (если он указан в списке параметров при вызове функции), выводящий пример использования(необязательные параметры должны выводиться в квадратных скобках).
	Реализация требуется на С++ и / или Python.
	C++
*/


#include <iostream>
#include <cstdlib>
#include <string>


#define PARM_LENGTH 100



class Data{
public:
	Data() :Married{ false }, Age{ 0 }{}
	int initialize(std::string name, std::string value);
	int initialize(std::string name);
	int getDataFieldSpec(std::ostream *stream);
	int Dump(std::ostream *stream);

private:
	std::string Name;
	std::string SurName;
	int Age;
	bool Married;
	
};
int Data::initialize(std::string name, std::string value){
	if (!name.compare("name")){
		Name = value;
	}
	else if (!name.compare("surname")){
		SurName  = value;
	}
	else if (!name.compare("age")){
		Age = std::stoi(value);
	}
	return 0;
}
int Data::initialize(std::string name){
	if (!name.compare("married")){
		Married = true;
		return 0;
	}
	return -1;
}
int Data::getDataFieldSpec(std::ostream *stream){
	*stream << "progName --name <Name> --surname <SurName> --age <Age> [--married]" << '\n';
	return 0;
}
int Data::Dump(std::ostream *stream){
	*stream << "Name = "<<Name<<'\n';
	*stream << "SurName = " << SurName << '\n';
	*stream << "Age = " << Age << '\n';
	*stream << "Is married : ";
	if (Married)
		*stream << "Yes" << '\n';
	else 
		*stream << "No" << '\n';
	return 0;
}
template< class dataStruct> int my_getopt_long_only(int argc, char ** argv, dataStruct *opts){

	char *name = new char[PARM_LENGTH];
	char *value = new char[PARM_LENGTH];

	bool nameInit = false;
	bool valueInit = false;
	
	for (int i = 1; i < argc;i++){
	//Разделить строку, если там есть равно
		char *eqPos = strchr(argv[i], '=');
		if(eqPos!=NULL){
			int size = eqPos - argv[i];
			char *namePart = new char[size+1];
			strncpy_s(namePart, size+1, argv[i],size);

			if(sscanf_s(namePart, "--%s", name, PARM_LENGTH))
				nameInit = true;
			if (sscanf_s(++eqPos, "%s", value, PARM_LENGTH))

				valueInit = true;
		}
		//читаем отдельно название атрибута
		else if (!nameInit){

			if(sscanf_s(argv[i], "--%s", name, PARM_LENGTH))

					nameInit=true;
		}
		// читаем значение атрибута
		else if (!valueInit){

			if (sscanf_s(argv[i], "%s", value, PARM_LENGTH)){
				valueInit = true;
			}
		}
		// попытка инициализации
		if (valueInit && nameInit){
			opts->initialize(name, value);	
			valueInit = false;
			nameInit = false;
		}
		else if(nameInit){
			if (!std::string(name).compare("help")){
				opts->getDataFieldSpec(&std::cout);
				return -1;
			}
			else {
				// Проверяем требуется ли значение для этого атрибута
				if(!opts->initialize(name))
					nameInit=false;
			}
		}
	}
	return 0;
}
int main(int argc, char **argv){
	Data *data = new Data;
	if (argc>1){
		int ret = my_getopt_long_only(argc, argv,data);
	if (!ret)
		data->Dump(&std::cout);
	}
	exit(EXIT_SUCCESS);
}