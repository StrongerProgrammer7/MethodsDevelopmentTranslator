#pragma once
#ifndef REVERSEPOLISHNOTATION_H
#define REVERSEPOLISHNOTATION_H
#include "Translator.h"

typedef std::vector<std::map<std::string, int>> stack_type;

class ReversePolishNotation : public Translator
{
public:
	ReversePolishNotation();
	~ReversePolishNotation();
	void reversePolishNotationAnalyze(std::string filePathOrName_C, std::string fileName_Path_SaveAnalis);
private:
	stack_type stack;
	int getPriority(std::string word);

	
};

#endif
