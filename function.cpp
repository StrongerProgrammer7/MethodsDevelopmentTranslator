#include "table.h"
#include "function.h"

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
