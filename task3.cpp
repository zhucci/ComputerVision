/*
	�������� ������� ���������� ������� ��� ������� ���������� ��������� ������(getopt).
	��������, ��� ��� ��������� ��������� ������, ���������� ������� ��������� ���������� ����� ���������� ���������� ���� - ������, �����, ����� � ��������� ������ � �.�., � ����� �������, �������� �� ���� �������� ������������.
	��������, ��� ��������� ����� ������������ ������ � "�������" ������� � ������������ "--" ����� ������ ���������(�� ���� "--my-option-name my-option-val", "--my-option-name=my-option-val", "--my-boolean-option").
	���������� ����� ���� ���������.
	������� ������ ����������� ����� ������������ �������� "--help" (���� �� ������ � ������ ���������� ��� ������ �������), ��������� ������ �������������(�������������� ��������� ������ ���������� � ���������� �������).
	���������� ��������� �� �++ � / ��� Python.
	C++
*/


#include <iostream>
#include <cstdlib>
#include <string>

#define PARM_LENG�TH 100


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
	char *name = new char[PARM_LENG�TH];
	char *value = new char[PARM_LENG�TH];
	bool nameInit = false;
	bool valueInit = false;
	
	for (int i = 1; i < argc;i++){
	//��������� ������, ���� ��� ���� �����
		char *eqPos = strchr(argv[i], '=');
		if(eqPos!=NULL){
			int size = eqPos - argv[i];
			char *namePart = new char[size+1];
			strncpy_s(namePart, size+1, argv[i],size);
			if(sscanf_s(namePart, "--%s", name, PARM_LENG�TH))
				nameInit = true;
			if (sscanf_s(++eqPos, "%s", value, PARM_LENG�TH))
				valueInit = true;
		}
		//������ �������� �������� ��������
		else if (!nameInit){
			if(sscanf_s(argv[i], "--%s", name, PARM_LENG�TH))
					nameInit=true;
		}
		// ������ �������� ��������
		else if (!valueInit){
			if (sscanf_s(argv[i], "%s", value, PARM_LENG�TH)){
				valueInit = true;
			}
		}
		// ������� �������������
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
				// ��������� ��������� �� �������� ��� ����� ��������
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