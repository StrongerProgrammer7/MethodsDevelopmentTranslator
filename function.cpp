//#include "table.h"
#include <iostream>

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

bool isComment(int const &slash, int const& star)
{
	return slash == 47 && star == 42? true : false;
}
bool isOneStringComment(int const& slash, int const& slash2)
{
	return slash == 47 && slash2 == 47 ? true : false;
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

bool isLibrary_header(std::string const &word)
{
	return (int)word[0] == 34 && (int)word[word.length() - 1] == 34 && (int)word[word.length() - 2] == 104 && (int)word[word.length() - 3] == 46 ? true : false;
}

bool isType(std::string const& word)
{
	return word == "int" || word == "float" || word == "double" || word == "char";
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