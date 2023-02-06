#include "table.h"
#include "function.h"

bool isLetter(char elem)
{
	return (elem >= '65' && elem <= '90') || (elem >= '97' && elem <= '122') ? true : false;
}

bool isDigit(char elem)
{
	return elem >= '48' && elem <= '57' ? true : false;
}

bool isNumber(string num)
{
	for (int i = 0; i < num.length(); i++)
		if (isDigit(num[i]) == false)
			return false;
	return true;
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

string getCodeWordLength_1(string word)
{
	string code = getOperationsCode(word);
	if (code == "\0")
		code = getSeparatorsCode(word);
	if (code=="\0")
	{
		if (isDigit(word[0]) == true)
		{
			code = getNumberConstCode(word);
			//TODO: Add constant
		}
		if (isLetter(word[0]) == true)
		{
			code = getIdentifierCode(word);
			//TODO: Add word
		}
	}
	else
	{
		return code;
	}
}

string getCodeWordLengthGreaterOne(string word)
{
	string code = getServiceWordCode(word);
	if (code == "\0")
		code = getOperationsCode(word);
	if (code == "\0")
	{
		if (isNumber(word) == true)
		{
			code = getNumberConstCode(word);
		}
		else
		{
			if (word[0] == '34')
			{
				code = getSymbolsConstCode(word);
				if (code == "\0")
				{
					//TODO:ADD const sym
				}
			}
			else
			{
				code = getIdentifierCode(word);
				if (code == "\0")
				{
					//TODO:ADD id
				}
			}
			
		}
	}
	else
		return code;
}

string getCodeWord(string word)
{
	if (word.length() == 1)
	{
		return getCodeWordLength_1(word);
	}
	else
	{
		return getCodeWordLengthGreaterOne(word);
	}
}