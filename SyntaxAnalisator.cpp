#include "SyntaxAnalisator.h"
#include "function.h"


SyntaxAnalisator::SyntaxAnalisator()
{
}


SyntaxAnalisator::~SyntaxAnalisator()
{
}
string SyntaxAnalisator::getServiceWordCode(string str)
{
	for (int i = 0; i < SIZE_serviceWord; i++)
		if (serviceWord[i][0] == str)
			return serviceWord[i][1];
	return "\0";
}

string SyntaxAnalisator::getOperationsCode(string str)
{
	for (int i = 0; i < SIZE_operation; i++)
		if (operations[i][0] == str)
			return operations[i][1];
	return "\0";
}

string SyntaxAnalisator::getSeparatorsCode(string str)
{
	for (int i = 0; i < SIZE_separators; i++)
		if (separators[i][0] == str)
			return separators[i][1];
	return "\0";
}

string SyntaxAnalisator::getIdentifierCode(string str)
{
	for (const auto& word : identifier)
		if (word.first == str)
			return word.second;
	return "\0";
}

string SyntaxAnalisator::getNumberConstCode(string str)
{
	for (const auto& word : numberConst)
		if (word.first == str)
			return word.second;
	return "\0";
}

string SyntaxAnalisator::getSymbolsConstCode(string str)
{
	for (const auto& word : symbolsConst)
		if (word.first == str)
			return word.second;
	return "\0";
}

void SyntaxAnalisator::addCode(string str, map<string, string> & table, int numTable)
{
	int indexCode = 0;
	for (const auto& word : table)
	{
		indexCode++;
	}
	indexCode++;
	if (numTable == 1)
		table.insert(pair<string, string>(str, "I" + to_string(indexCode)));
	if (numTable == 2)
		table.insert(pair<string, string>(str, "N" + to_string(indexCode)));
	if (numTable == 3)
		table.insert(pair<string, string>(str, "C" + to_string(indexCode)));
}

int SyntaxAnalisator::checkStringSingleElem(string const& word)
{
	if (isDigit((int)word[0]) == true)
		return 1;
	if (isOperation((int)word[0]) == true || isLogicalSingleOperation((int)word[0]) == true)
		return 2;
	if (isSeparators((int)word[0]) == true)
		return 3;
	if (isLetter((int)word[0]) == true)
		return 4;
	return 0;
}

string SyntaxAnalisator::getCodeWordLength_1(string word)
{
	switch (checkStringSingleElem(word))
	{
	case 1:
		if (getNumberConstCode(word) == "\0")
			addCode(word, numberConst, 2);
		return getNumberConstCode(word);
	case 2:
		return getOperationsCode(word);
	case 3:
		return getSeparatorsCode(word);
	case 4:
		if (getIdentifierCode(word) == "\0")
			addCode(word, identifier, 1);
		return getIdentifierCode(word);
	default:
		return "";
	}
	/*
	string code = getOperationsCode(word);
	if (code == "\0")
		code = getSeparatorsCode(word);
	if (code=="\0")
	{
		if (isDigit((int)word[0]) == true)
		{
			if (getNumberConstCode(word) == "\0")
				addCode(word, numberConst, 2);
			return getNumberConstCode(word);
		}
		if (isLetter((int)word[0]) == true)
		{
			if(getIdentifierCode(word) =="\0")
				addCode(word,identifier,1);
			return getIdentifierCode(word);
		}
	}
	else
		return code;*/
}


string SyntaxAnalisator::getCodeWordLengthGreaterOne(string word)
{
	string code = getServiceWordCode(word);
	if (code == "\0")
		code = getOperationsCode(word);
	if (code == "\0")
	{
		if (isNumber(word) == true)
		{
			if (getNumberConstCode(word) == "\0")
				addCode(word, numberConst, 2);
			return getNumberConstCode(word);
		}
		else
		{
			if ((int)word[0] == 34)// \"
			{
				if (isLibrary_header(word) == false)
				{
					if (getSymbolsConstCode(word) == "\0")
						addCode(word, symbolsConst, 3);
					return getSymbolsConstCode(word);
				}
			}
			if (getIdentifierCode(word) == "\0")
				addCode(word, identifier, 1);
			return getIdentifierCode(word);
		}
	}
	else
		return code;
}

string SyntaxAnalisator::getCodeWord(string word)
{
	if (word.length() == 1)
		return getCodeWordLength_1(word);
	else
		return getCodeWordLengthGreaterOne(word);
}