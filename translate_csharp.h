#pragma once
#include "Translator.h"

class Translate_csharp : public Translator
{
public:
	Translate_csharp();
	~Translate_csharp();
	void transalteToCSharp(std::string fileName_RPN, std::string fileName_CSharp);

private:
	std::stack<std::string> stack;
	std::string reverseExpression(std::string expression);
	std::string declareFunction(std::string line);
	std::string declareCondition(std::string line, std::string nameCondition);
	std::string declareFunctionExpression(std::string line,int countArg);
	std::string strArray(std::string line);
	std::string correctCycleFor(std::string for_line);
	std::string getSymbolOperationByCode(std::string sign);
	std::string getNameServiceWordByCode(std::string service);
	std::string getNameByCode(std::map<std::string, std::string>& table, std::string code);
	std::string replaceCodeToName(std::string line, char name);
	std::string replaceCodeToName(std::string line);

};

