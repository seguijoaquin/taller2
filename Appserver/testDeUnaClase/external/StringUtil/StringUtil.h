#ifndef STRING_UTIL_H_
#define STRING_UTIL_H_

#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <ctype.h>
#include <wchar.h>
#include <vector>
#include <string.h>

using namespace std;

class StringUtil {

public:

	static string toLower(string str);
	
	static string toUpper(string str);

	static string int2string(int value);

	static string double2string(double value);

    static string float2string(float value);

    static const char*  stringToChar(string number);

    static string charToString(char* number);


	// TODO MOVERLA A OTRO LUGAR. ESTA FUNCION NO PERTENECE A ESTA CLASE UTILITARIA
	static bool file_exists(const char * filename);

	static int str2int (string string);

	static float str2float (const char* string);

	static double str2double (const char* string);

	static bool isInteger(const char* value);

	static bool isFloat(const char* value);

	static char* longToChar(long number);

	 static long charToLong(char* number);

	static std::vector<std::string> split(const std::string &s, char delim);

	static std::vector<std::string> splitNew(vector<char> input, char delim);

private:
	static std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
};

#endif
