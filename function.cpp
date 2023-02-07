#include "table.h"
#include "function.h"

// ( ) [  ]  {  } ;
bool isSeparators(int const &elem)
{
	return elem == 40 || elem == 41 || elem == 91 || elem == 93 || elem == 123 || elem == 125 || elem == 59 ? true : false;
}

// \a \b \t \n \v \f \r
bool isServiceSymbols(int const &elem)
{
	return elem == 7 || elem == 8 || elem == 9 || elem == 10 || elem == 11 || elem == 12 || elem == 13 ? true : false;
}
/* +- * / % */
bool isOperation(string const &str, int const &ind)
{
	return str[ind] == '+' || str[ind] == '-' || str[ind] == '/' || str[ind] == '*' || str[ind]== '=' || str[ind] == '%' ? true : false;
}

/*  < > == >= <= !=  */
bool isLogicalOperation(string const& str, int const& ind)
{
	return str[ind] == '<' || str[ind] == '>' || (str[ind] == '=' && str[ind + 1] == '=') ||
		(str[ind] == '>' && str[ind + 1] == '=') || (str[ind] == '<' && str[ind + 1] == '=') || (str[ind] == '!' && str[ind + 1] == '=') ? true : false;
}

//++ --
bool isIncrement(string const& str, int const& ind)
{
	return (str[ind] == '+' && str[ind + 1] == '+') || (str[ind] == '-' && str[ind + 1] == '-') ? true : false;
}

/* += -= *= /= */
bool isDoubleOperation(string const& str, int const& ind)
{
	return (str[ind] == '+' && str[ind + 1] == '=') || (str[ind] == '-' && str[ind + 1] == '=') ||
		(str[ind] == '*' && str[ind + 1] == '=') || (str[ind] == '/' && str[ind + 1] == '=') ? true : false;
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

bool isNumber(string const &num)
{
	for (unsigned int i = 0; i < num.length(); i++)
		if (isDigit((int)num[i]) == false)
			return false;
	return true;
}

bool isLibrary_header(string const &word)
{
	return (int)word[0] == 34 && (int)word[word.length() - 1] == 34 && (int)word[word.length() - 2] == 104 && (int)word[word.length() - 3] == 46 ? true : false;
}

string getServiceWordCode(string str)
{
	for (int i = 0; i < SIZE_serviceWord; i++)
		if (serviceWord[i][0] == str)
			return serviceWord[i][1];
	return "\0";
}

string getOperationsCode(string str)
{
	for (int i = 0; i < SIZE_operation; i++)
		if (operations[i][0] == str)
			return operations[i][1];
	return "\0";
}

string getSeparatorsCode(string str)
{
	for (int i = 0; i < SIZE_separators; i++)
		if (separators[i][0] == str)
			return separators[i][1];
	return "\0";
}

string getIdentifierCode(string str)
{
	for (const auto& word : identifier)
		if (word.first == str)
			return word.second;
	return "\0";
}

string getNumberConstCode(string str)
{
	for (const auto& word : numberConst)
		if (word.first == str)
			return word.second;
	return "\0";
}

string getSymbolsConstCode(string str)
{
	for (const auto& word : symbolsConst)
		if (word.first == str)
			return word.second;
	return "\0";
}

void addCode(string str, map<string, string> &table, int numTable)
{
	int indexCode = 0;
	for (const auto& word : table)
	{
		indexCode++;
	}
	indexCode++;
	if(numTable==1)
		table.insert(pair<string, string>(str, "I" + to_string(indexCode)));
	if(numTable==2)
		table.insert(pair<string, string>(str, "N" + to_string(indexCode)));
	if(numTable==3)
		table.insert(pair<string, string>(str, "C" + to_string(indexCode)));
}


string getCodeWordLength_1(string word)
{
	string code = getOperationsCode(word);
	if (code == "\0")
		code = getSeparatorsCode(word);
	if (code=="\0")
	{
		if (isDigit((int)word[0]) == true)
		{
			code = getNumberConstCode(word);
			if(code =="\0")
				addCode(word, numberConst, 2);
			return getNumberConstCode(word);
		}
		if (isLetter((int)word[0]) == true)
		{
			code = getIdentifierCode(word);
			if(code=="\0")
				addCode(word,identifier,1);
			return getIdentifierCode(word);
		}
	}
	else
	{
		return code;
	}
}


string getCodeWordLengthGreaterOne(string word)
{
	/*if (word == "p*")
	{
		word.erase(0, 1);
		return getSeparatorsCode(word);
	}*/
	string code = getServiceWordCode(word);
	if (code == "\0")
		code = getOperationsCode(word);
	if (code == "\0")
	{
		if (isNumber(word) == true)
		{
			code = getNumberConstCode(word);
			if(code=="\0")
				addCode(word, numberConst, 2);
			return getNumberConstCode(word);
		}
		else
		{
			if ((int)word[0] == 34)// \"
			{
				if (isLibrary_header(word) == false)
				{
					code = getSymbolsConstCode(word);
					if (code == "\0")
						addCode(word, symbolsConst, 3);
					return getSymbolsConstCode(word);
				}
				else
					goto addCodeIdentifier;				
			}
			else
			{
addCodeIdentifier:
				code = getIdentifierCode(word);
				if (code == "\0")
					addCode(word, identifier, 1);
				return getIdentifierCode(word);
			}
			
		}
	}
	else
		return code;
}

string getCodeWord(string word)
{
	if (word.length() == 1)
		return getCodeWordLength_1(word);
	else
		return getCodeWordLengthGreaterOne(word);
}