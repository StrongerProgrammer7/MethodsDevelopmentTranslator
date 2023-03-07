//#include "table.h"
#include <iostream>
#include <string>
// ( ) [  ]  {  } ;
bool isSeparators(int const &elem)
{
	return elem == 40 || elem == 41 || elem == 91 || elem == 93 || elem == 123 || elem == 125 || elem == 59 || elem == 44 ? true : false;
}

// \a \b \t \n \v \f \r
bool isServiceSymbols(int const &elem)
{
	return elem == 7 || elem == 8 || elem == 9 || elem == 10 || elem == 11 || elem == 12 || elem == 13 ? true : false;
}
/* +- * / % = */
bool isOperation(int const& elem)
{
	return elem == 43 || elem  == 45 || elem == 47 || elem == 42 || elem  == 61 || elem ==  37 ? true : false;
}

/*  < >  */
bool isLogicalSingleOperation(int const& elem)
{
	return elem == 60 || elem == 62 ? true : false;
}
/*== >= <= != && ||*/
bool isLogicalDoubleOperation(int const& elem, int const& nextElem)
{
	return (elem == 61 && nextElem == 61) || (elem == 62 && nextElem == 61) || (elem == 60 && nextElem == 61)
		|| (elem == 33 && nextElem == 61) || (elem == 38 && nextElem == 38) || (elem == 124 && nextElem == 124) ? true : false;
}

//++ --
bool isIncrement(int const& elem, int const& nextElem)
{
	return (elem == '+' && nextElem == '+') || (elem == '-' && nextElem == '-') ? true : false;
}

/* += -= *= /= */
bool isDoubleOperation(int const& elem, int const& nextElem)
{
	return (elem == '+' && nextElem == '=') || (elem == '-' && nextElem == '=') ||
		(elem == '*' && nextElem == '=') || (elem == '/' && nextElem == '=') ? true : false;
}

bool isLetter(int const &elem)
{
	return (elem >= 65 && elem <= 90) || (elem >= 97 && elem <= 122) ? true : false;
}

bool isDigit(int const &elem)
{
	return elem >= 48 && elem <= 57 ? true : false;
}

bool isNumber(std::string const &num)
{
	if (std::count(num.begin(), num.end(), '.') > 1)
		return false;
	for (unsigned int i = 0; i < num.length(); i++)
	{
		if (num[i] == '.')
			continue;
		if (isDigit((int)num[i]) == false)
			return false;
	}
	return true;
}

bool isTypeDeclaration(std::string type)
{
	return type == "int" || type == "float" || type == "char" || type == "const int" || type == "double" || type == "int*" || type == "double*" ||
		type == "float*" || type == "const" || type == "char*" || type == "const float"
		|| type == "const double" || type == "const char" || type == "const float*" || type == "const double*"
		|| type == "const char*" || type == "const int*" ? true : false;
}

bool isIdentifier(std::string const& word)
{
	if (word.find('%') != std::string::npos || word.find('-') != std::string::npos || word.find('*') != std::string::npos
		|| word.find('/') != std::string::npos || word.find('\\') != std::string::npos || word.find('[') != std::string::npos
		|| word.find(']') != std::string::npos || word.find('(') != std::string::npos || word.find(')') != std::string::npos
		|| word.find('{') != std::string::npos || word.find('}') != std::string::npos)
		return false;
	return true;
}

std::string intToStrWithSpace(int num)
{
	std::string temp = "";
	while (num != 0)
	{
		int t = num % 10;
		temp += std::to_string(t) + " ";
		num /= 10;
	}
	temp.erase(temp.length() - 1, 1);
	reverse(temp.begin(), temp.end());
	return temp;
}

bool isSpaceInEndString(std::string line)
{
	return line.rfind(" ") == line.length() - 1 ? true : false;
}


