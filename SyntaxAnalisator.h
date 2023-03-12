#pragma once
#include "ReversePolishNotation.h"


class SyntaxAnalisator : public ReversePolishNotation
{
public:
	SyntaxAnalisator();
	~SyntaxAnalisator();
protected:
	bool makeSyntaxAnalyze();
	/*std::string readFromFileToString();*/
private:
	bool setArguments(std::string& code);
	bool operators(std::string& code, std::string token);
	bool operatorDeclareData(std::string& code);
	bool operatorEqual(std::string& code);
	bool operatorCondition(std::string& code);
	bool operatorFor(std::string& code);
	bool parseExpression(std::string& fragment, bool condition);
};

