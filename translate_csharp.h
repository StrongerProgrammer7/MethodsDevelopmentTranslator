#pragma once
#include "ReversePolishNotation.h"

class Translate_csharp : public ReversePolishNotation
{
public:
	Translate_csharp();
protected:
	void transalteToCSharp(std::string from_file_RPN, std::string to_file_CSharp);
	~Translate_csharp();
private:
	std::string nameArrayForReturn = "", nameFunctionReturnArray = "";
	std::stack<std::string> stack;
	std::string reverseExpression(std::string expression);
	std::string declareFunction(std::string line);
	std::string declareCondition(std::string line, std::string nameCondition);
	std::string declareFunctionExpression(std::string line,int countArg);
	std::string strArray(std::string line);
	std::string correctCycleFor(std::string for_line);
	std::string replaceCodeToName(std::string line, char const& name);
	std::string replaceCodeToName(std::string line);
	std::string replaceMalloc(std::string const& line);
	void replaceTypeToTypeArrayFunction(std::string& block_function);

};

