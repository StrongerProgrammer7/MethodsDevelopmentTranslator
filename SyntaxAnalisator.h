#pragma once
#ifndef SYNTAXANALISATOR_H
#define SYNTAXANALISATOR_H

#include "Translator.h"
class SyntaxAnalisator :
	public Translator
{
public:
	SyntaxAnalisator();
	~SyntaxAnalisator();
	string getCodeWord(string word);
private:
	string getServiceWordCode(string str);
	string getOperationsCode(string str);
	string getSeparatorsCode(string str);
	string getIdentifierCode(string str);
	string getNumberConstCode(string str);
	string getSymbolsConstCode(string str);
	void addCode(string str, map<string, string>& table, int numTable);
	int checkStringSingleElem(string const& word);
	string getCodeWordLength_1(string word);
	string getCodeWordLengthGreaterOne(string word);
};
#endif