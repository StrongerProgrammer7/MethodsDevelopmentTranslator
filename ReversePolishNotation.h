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
	bool isFunctionDeclaration(std::string line);
	bool isExistsComma(std::string line);
	size_t positionTypeConversion(std::string line);
	bool upElemNotNameExpression(std::string upElem);
	bool isBeginFunctionName(std::string word);
	bool isExistsFunctionExpression(std::vector<std::map<std::string, int>>& stack);
	bool isEmptyArray(std::string line);
	void recordFileFromStack(std::ofstream& file, std::map<std::string, int>::reverse_iterator upElemStack);
	
};

#endif
