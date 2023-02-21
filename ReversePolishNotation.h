#pragma once
#ifndef REVERSEPOLISHNOTATION_H
#define REVERSEPOLISHNOTATION_H
#include "Translator.h"

typedef std::vector<std::map<std::string, int>> mystack;

class ReversePolishNotation : public Translator
{
public:
	ReversePolishNotation();
	~ReversePolishNotation();
	void reversePolishNotationAnalyze(std::string fileName_lexical, std::string fileName_RPN);
private:
	mystack stack;
	int getPriority(std::string word);
	bool isExistsSymbolToTable(std::string word);
	
};

#endif
