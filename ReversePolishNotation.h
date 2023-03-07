#pragma once
#ifndef REVERSEPOLISHNOTATION_H
#define REVERSEPOLISHNOTATION_H
#include "SyntaxAnalisator.h"

typedef std::vector<std::map<std::string, int>> mystack;

class ReversePolishNotation : public SyntaxAnalisator
{
public:
	ReversePolishNotation();
protected:
	void reversePolishNotationAnalyze(std::string from_file_lexical, std::string to_file_RPN);
	~ReversePolishNotation();
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
