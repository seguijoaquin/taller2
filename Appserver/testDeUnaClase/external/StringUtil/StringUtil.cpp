#include "StringUtil.h"

string StringUtil::toLower(string str){
	char* lower = (char*)str.c_str();
	int i = 0;
	char c;

	while (str[i]){
		c = str[i];
		lower[i] = tolower(c);
		i++;
	}

	return (string)lower;
}

string StringUtil::toUpper(string str){
	char* upper = (char*)str.c_str();
	int i = 0;
	char c;

	while (str[i]){
		c = str[i];
		upper[i] = toupper(c);
		i++;
	}

	return (string)upper;
}

string StringUtil::int2string(int value){
	std::string s;
	std::stringstream out;
	out << value;
	s = out.str();

	return s;
}

const char*  StringUtil::stringToChar(string number){
	return number.c_str();
}

string StringUtil::charToString(char* number){
	return number;
}

long charToLong(char* number){
	return atol(number) ;
}

char* longToChar(long number){
	std::ostringstream oss;
	oss <<  number;
	char* writable = new char[oss.str().size() + 1];
	std::copy(oss.str().begin(), oss.str().end(), writable);
	writable[oss.str().size()] = '\0'; // don't forget the terminating 0
	return writable;
}

string StringUtil::double2string(double value){
	std::string s;
	std::stringstream out;
	out << value;
	s = out.str();

	return s;
}

string StringUtil::float2string(float value){
	std::string s;
	std::stringstream out;
	out << value;
	s = out.str();

	return s;
}

bool StringUtil::file_exists(const char * filename){
	if (FILE * file = fopen(filename, "r")){
		fclose(file);
		return true;
	}
	return false;
}

int StringUtil::str2int (string string) {
	std::istringstream ss(string.c_str());
	int i;
	ss >> i;
	return i;
}

float StringUtil::str2float (const char* string) {
	std::istringstream ss(string);
	float i;
	ss >> i;
	return i;
}

double StringUtil::str2double(const char* string) {
	std::istringstream ss(string);
	double i;
	ss >> i;
	return i;
}

bool StringUtil::isInteger(const char* value){
	string str = (string)value;
	for(unsigned int i = 0; i < str.size(); i++){
		if(!isdigit(value[i])){
			return false;
		}
	}
	return true;
}

bool StringUtil::isFloat(const char* value){
	string str = (string)value;

	//el primer caracter no puede ser el punto
	if(value[0] == '.'){
		return false;
	}

	//el ultimo caracter no puede ser el punto
	if(value[str.size() - 1] == '.'){
		return false;
	}

	//el '.' aparece solo una vez, 
	int countPunto = 0;

	for(unsigned int i = 0; i < str.size(); i++){
		if(!isdigit(value[i]) && value[i] != '.'){
			return false;
		}
		if(value[i] == '.'){
			countPunto++;
		}
	}
	if(countPunto > 1){	//el '.' aparece solo una vez, 
		return false;
	}
	return true;
}

std::vector<std::string>& StringUtil::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> StringUtil::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return StringUtil::split(s, delim, elems);
}

std::vector<std::string> StringUtil::splitNew(vector<char> input, char delim){
	std::string newAux(input.begin(),input.end());
	return StringUtil::split(newAux,delim);
	//	int size=input.size();
//	std::vector<std::string> result;
//	int index=0;
//	std::vector<char> aux;// = (char*)malloc(sizeof(char)*4000);
//	for(int i=0;i<size;i++){
//		if(input.at(i)==delim){
//			aux.push_back('\0');
//			std::string newAux(aux.begin(),aux.end());
//			result.push_back(newAux);
//			aux.clear();
//			index=0;
//		}else{
//			aux.push_back(input.at(i));
//			index++;
//		}
//	}
//	aux.push_back('\0');
//	std::string newAux2(aux.begin(),aux.end());
//	result.push_back(newAux2);
//	/*
//	if(aux[size]!=delim){
//		aux[index+1]='\0';
//		result.push_back(aux);
//	}*/
//	return result;
}
