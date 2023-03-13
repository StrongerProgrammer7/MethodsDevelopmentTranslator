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
	bool is_declareFunction(std::string code);
	bool declareMainFunction(std::string& main);
	bool setArguments(std::string& code);
	bool checkReturnExpression(std::string& expr);
	bool operators(std::string& code, std::string token);
	bool operatorDeclareData(std::string& code);
	bool operatorEqual(std::string& code);
	bool operatorCondition(std::string& code);
	bool operatorFor(std::string& code);
	bool parseExpression(std::string& fragment, bool condition);
	int isRepeatWordByCode(bool (*pFunctByCode)(std::string), std::stack<std::string>& temp_stack, std::string token);
	bool breachOfCodition(std::string const& token, std::stack<std::string>const& temp_stack);
	bool breachOfExpressionWithNumberConst(std::string const& token, std::stack<std::string>const& temp_stack, std::string nextCommand);
};

