#include "SyntaxAnalisator.h"
#include "function.h"

SyntaxAnalisator::SyntaxAnalisator()
{
}


SyntaxAnalisator::~SyntaxAnalisator()
{
}

int numberString = 0;

bool isIdentifierByCode(std::string token)
{
	return token[0] == 'I' && isDigit((int)token[1]) == true ? true : false;
}

bool isOperationByCode(std::string token)
{
	return token[0] == 'O' && isDigit((int)token[1]) == true ? true : false;
}

bool isSymbolConst(std::string token)
{
	return token[0] == 'C' && isDigit((int)token[1]) == true ? true : false;
}

bool isNumberConstByCode(std::string token)
{
	return token[0] == 'N' && isDigit((int)token[1]) == true ? true : false;
}



//std::string SyntaxAnalisator::readFromFileToString()
//{
//	std::string code = "";
//	try
//	{
//		std::ifstream lexicalFile("./translator_file/lexical.txt");
//		if (lexicalFile.is_open())
//		{
//			std::string temp = "";
//			while (!lexicalFile.eof())
//			{
//				temp = "";
//				getline(lexicalFile, temp);
//				if (isSpaceInEndString(temp) == true)
//					temp.replace(temp.rfind(" "), 1, "");
//
//				for (__int64 i = 0; i < temp.length(); i++)
//				{
//					if (isServiceSymbols((int)temp[i]) == false)
//						code += temp[i];
//				}
//				code += " ";
//
//			}
//			return code;
//		}
//		else
//		{
//			System::Windows::Forms::MessageBox::Show("File don't open", "Error", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
//		}
//	}
//	catch (const std::exception&)
//	{
//		System::Windows::Forms::MessageBox::Show("Problem with file to Syntaxanalisator", "Error",System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
//	}
//	
//}

std::string getToken(std::string& line)
{
	std::string token = "";
	__int64 pos = line.find(' ');
	if (pos == std::string::npos)
	{
		token = line.substr(0, line.length());
		line = "";
	}
	else
	{
		token = line.substr(0, pos);
		line.erase(0, pos + 1);
	}
	return token;
}


bool SyntaxAnalisator::makeSyntaxAnalyze()
{
	try
	{
		numberString = 0;
		std::ifstream lexicalFile("./translator_file/lexical.txt");
		if (lexicalFile.is_open())
		{
			std::string temp = "";
			int countInclude = 0, countFunction = 0;
			
			bool isDeclareFunction = false, isCycle = false, isIFElse = false, manyLineComment = false, mainFunctionChecked = false;
			while (!lexicalFile.eof())
			{
				std::string code = "";
				getline(lexicalFile, code);
				numberString++;
				if (code == "")
					continue;

				if (code.length() > 2 && isComment((int)code[0], (int)code[1]) && code.find("*/") == std::string::npos)
					manyLineComment = true;

				if (code.length() > 2 && (isComment((int)code[0], (int)code[1]) || isOneStringComment((int)code[0], (int)code[1])))
					continue;

				if (manyLineComment == true)
				{
					if (code.find("*/") != std::string::npos)
						manyLineComment = false;
					continue;
				}

				if (code.find("W8") == 0)
				{
					if (countInclude < this->countInclude)
						countInclude++;
					else
					{
						problemDetected("Detected #include excess!\n line:" + std::to_string(numberString));
						return false;
					}
					continue;
				}
				if (code.find("W11") == 0)
				{
					checkReturnExpression(code);
					continue;
				}
				if (code.find("W20") == 0)
				{
					code.erase(0, 7);
					if (isIdentifierByCode(code.substr(0, code.find(" "))) == false)
					{
						problemDetected("Method free accepts only identifier! \nline:" + std::to_string(numberString));
						return false;
					}
					code.erase(0, code.find(" ")+1);
					if (code.find("I") != std::string::npos)
					{
						problemDetected("Methods free accepts only one argument!\n line:" + std::to_string(numberString));
						return false;
					}
					continue;
				}

				if (code.find("W4") != std::string::npos && mainFunctionChecked == false)
				{
					mainFunctionChecked = true;
					countFunction++;
					isDeclareFunction = true;
					if (declareMainFunction(code) == false)
					{
						problemDetected("Problem with declare main function!\nline:" + std::to_string(numberString));
						return false;
					}
					continue;
				}
				else
					if (code.find("W4") != std::string::npos)
					{
						problemDetected("Detected excess main function!\n line:" + std::to_string(numberString));
						return false;
					}

				if (code.find("R5") == 0)
				{
					if (isDeclareFunction == false && isCycle == false && isIFElse == false)
					{
						problemDetected("Detected excess figure brackets!\n line: " + std::to_string(numberString));
						return false;
					}
					if (isDeclareFunction == true)
					{
						isDeclareFunction = false;
						if (countFunction > this->countFunction)
						{
							problemDetected("Detected excess function!\n line: " + std::to_string(numberString) +" all: " + std::to_string(this->countFunction) + " detected: " + std::to_string(countFunction));
							return false;
						}
					}
					
					if (isCycle == true)
						isCycle = false;
					if (isIFElse == true)
						isIFElse = false;
					continue;
				}

				if (code.find("R6") == 0)
					continue;
				__int64 pos = 0;
				std::string token = "";
				
				
				while ((pos = code.find(' ')) != std::string::npos || code.length() != 0)
				{
					token = getToken(code);

					if (isInclude(token) == true || token == "W9" || token == "W10")
					{
						problemDetected("Detected don't right declare/use function !\n line:" + std::to_string(numberString));
						return false;
					}
	
					if ((isTypeDeclarationByCode(token) == true || token=="W13") && is_declareFunction(code) == true)
					{
						countFunction++;
						isDeclareFunction = true;
						token = code.substr(0, 2);
						code.erase(0, 3);
						if (isIdentifierByCode(token) == true)
						{
							if (setArguments(code) == true)
							{
								continue;
							}
							else
								return false;
						}
						else
						{
							problemDetected("It is not identifier!\n line: " + std::to_string(numberString));
							return false;
						}
					}

					if (isTypeDeclarationByCode(token)==true && (code[0] == 'I' || code[0] == 'R'))
					{
						if (operators(code, "type") == false)
							return false;
					}
					else
					{
						if (isIFCondition(token) == true || token == "W7" == true || isELSECondition(token)==true)
						{
							if (operators(code, "condition") == false)
								return false;
							if (isIFCondition(token) == true || isELSECondition(token) == true)
								isIFElse = true;
							if (token == "W7")
								isCycle = true;
							continue;
						}
						if (token == "W12")
						{
							if (operators(code, "for") == false)
								return false;
							isCycle = true;
							continue;
						}
						if (isIdentifierByCode(token) == true)
						{
							if (operators(code, "Id") == false)
								return false;
							if (isIFElse == true)
								isIFElse = false;
							if (isCycle == true)
								isCycle = false;
							continue;
						}
						else
						{
							problemDetected("Detected unidentified symbol!\nline: " + std::to_string(numberString));
							return false;
						}
					}
				}
			}
			return true;
		}
		else
		{
			problemDetected("File don't open");
			return false;
		}
	}
	catch (const std::exception&)
	{
		System::Windows::Forms::MessageBox::Show("Problem with file to Syntaxanalisator", "Error",System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
	}
	
	
}

bool SyntaxAnalisator::declareMainFunction(std::string& main)
{
	std::string token = getToken(main);
	if (isTypeDeclarationByCode(token) == false)
		return false;
	main.erase(0, 3);
	if (setArguments(main) == false)
		return false;
	return true;

}


bool SyntaxAnalisator::setArguments(std::string& code)
{
	__int64 pos = 0;
	std::string fragment = code.substr(0, code.find("R4"));
	code.erase(0, code.find("R4") + 3);
	bool type_ident = false;
	while ((pos = fragment.find(' ')) != std::string::npos || fragment.length() != 0)
	{
		std::string token = getToken(fragment);
		if (token == "")
			continue;
		if (token.length() < 2)
		{
			problemDetected("Detected unindefined symbol (setArguments): " + token +"\nline: " + std::to_string(numberString));
			return false;
		}
		if (token == "W19")
			token += " " + getToken(fragment);
		
		if (token == "R8")
			continue;
		if (token == "R1")
		{
			std::string temp = fragment.substr(0, fragment.find("R2") - 1);
			if (operatorDeclareData(temp) == false)
				return false;

			fragment.erase(0, fragment.find("R2") + 2);
			continue;
		}
		if (isTypeDeclarationByCode(token) == true && type_ident == false)
		{
			type_ident = true;
			continue;
		}
		else
			if (isTypeDeclarationByCode(token) == true)
			{
				problemDetected("Expected identifer, but get type!\n line: " + std::to_string(numberString));
				return false;
			}

		if (isIdentifierByCode(token)==true && type_ident == true)
		{
			type_ident = false;
			continue;
		}
		else
			if (isIdentifierByCode(token)==true)
			{
				problemDetected("Expected type, but get identifier!\n line: " + std::to_string(numberString));
				return false;
			}
	}
	return true;
}

bool SyntaxAnalisator::is_declareFunction(std::string code)
{
	__int64 pos = 0;
	int countSpace = 0;
	while ((pos = code.find(' ')) != std::string::npos || code.length() != 0)
	{
		std::string token = code.substr(0, pos);
		code.erase(0, pos + 1);
		countSpace++;
		if (token == "R3" && countSpace > 3)
			return false;
		else
			if (token == "R3" && countSpace == 2)
				return true;
		if (countSpace > 3)
			return false;
	}
	return false;
}


bool SyntaxAnalisator::operators(std::string& code, std::string token)
{
	__int64 pos = 0;
	if (token == "type")
		return operatorDeclareData(code);
	if (token == "Id")
		return operatorEqual(code);
	if (token == "condition")
		return operatorCondition(code);
	if (token == "for")
		return operatorFor(code);
	return false;

}

bool SyntaxAnalisator::operatorCondition(std::string& code)
{
	code.erase(0, 3);
	if (parseExpression(code, true) == false)
		return false;
	return true;
}

bool SyntaxAnalisator::operatorFor(std::string& code)
{
	code.erase(0, 3);
	std::string temp = "";
	if (isTypeDeclarationByCode(code.substr(0, code.find(" "))) == true)
	{
		code.erase(0, code.find(" ")+1);
		temp = code.substr(0, code.find("R7") + 2);
		code.erase(0, code.find("R7") + 3);
		if (operatorEqual(temp) == false)
			return false;
	}
	else
	{
		problemDetected("Expected type, but get "+ code.substr(0, code.find(" ")) +"!\n line: " + std::to_string(numberString));
		return false;
	}
	temp = code.substr(0, code.find("R7") + 2);
	code.erase(0, code.find("R7") + 3);
	if (parseExpression(temp, true) == false)
		return false;
	temp = code.substr(0, code.find("R4")-1);
	code = "";
	if (operatorEqual(temp) == false)
		return false;

	return true;
}

bool SyntaxAnalisator::operatorDeclareData(std::string& code)
{
	if (code.find("O5") != std::string::npos)
		if (operatorEqual(code) == false)
			return false;
		else
			return true;

	__int64 pos = 0;
	std::string token = "";
	bool ident_comma = false;
	while ((pos = code.find(' ')) != std::string::npos || code.length() != 0)
	{
		token = getToken(code);
		if (token == "")
			continue;
		if (token.length() < 2)
		{
			problemDetected("Detected unindefined symbol (operatorDeclareData): " + token + "\nline: " + std::to_string(numberString));
			return false;
		}
		if (token == "R7" && ident_comma == true)
			break;
		else
			if (token == "R7")
			{
				problemDetected("Before similcon detected ','!\n line: " + std::to_string(numberString));
				return false;
			}

		if (isIdentifierByCode(token) == true && ident_comma == false)
		{
			ident_comma = true;
			continue;
		}
		else
			if (isIdentifierByCode(token) == true)
			{
				problemDetected("Expected ',', but get type !\n line: " + std::to_string(numberString));
				return false;
			}
		
		if (token == "R8" && ident_comma == true)
		{
			ident_comma = false;
			continue;
		}
		else
			if (token == "R8")
			{
				problemDetected("Expected type, but get ',' !\n line: " + std::to_string(numberString));
				return false;
			}
		
	}
	return true;

}

bool SyntaxAnalisator::operatorEqual(std::string& code)
{
	__int64 pos = 0;
	std::string token = "";
	
	while ((pos = code.find(' ')) != std::string::npos || code.length() != 0)
	{
		std::string fragmentBeforeComma = "";
		__int64 posComma = code.find("R8"); 
		if (posComma != std::string::npos && code.find("O5", posComma) != std::string::npos)
		{
			fragmentBeforeComma = code.substr(0, posComma);
			code.erase(0, posComma + 1);
			if(parseExpression(fragmentBeforeComma,false)==false)
				return false;
			
			if (isTypeDeclarationByCode(code.substr(0, code.find(" "))) == true || isOperationByCode(code.substr(0, code.find(" "))) == true || isSymbolConst(code.substr(0, code.find(" "))) == true
				|| isCloseAnyBracket(code.substr(0, 2)) == true || isOpenAnyBracket(code.substr(0, 2)) == true)
			{
				problemDetected("Get " + code.substr(0, code.find(" ")) + " expected identifier\nline: " + std::to_string(numberString));
				return false;
			}
			continue;
		}

		if (parseExpression(code, false) == false)
			return false;
		else
			return true;
		

	}
	return true;
}

void pushStackAndPop(std::stack<std::string>& stack,std::string token)
{
	stack.pop();
	stack.push(token);
}

bool SyntaxAnalisator::parseExpression(std::string& fragment,bool condition)
{
	std::stack<std::string> temp_stack;
	__int64 pos = 0;
	std::string token = "";
	//<typeFunction> (*pFunction)(<type_arg>) = NULL;
	//pFunction = &isIdentifierByCode;
	//arg function -> <typeFunction> (*pFunction)(<type_arg>)
	while ((pos = fragment.find(' ')) != std::string::npos || fragment.length() != 0)
	{
		token = getToken(fragment);
		if (token == "")
			continue;
		if (token.length() < 2)
		{
			problemDetected("Detected unindefined symbol (expression): " + token + "\nline: " + std::to_string(numberString));
			return false;
		}
		if (token == "R1")
		{
			std::string temp = fragment.substr(0, fragment.find("R2") - 1);
			if (operatorDeclareData(temp) == false)
				return false;

			fragment.erase(0, fragment.find("R2") + 2);
			continue;
		}
		if (temp_stack.size() == 0)
		{
			if (condition == true && (token[0]=='I' || token[0]=='N' || token[0]=='C'))
				temp_stack.push(token);
			else
				if (condition == true)
				{
					problemDetected("It is if/while/else expected next I_/N_/C_, but get: " + token + "\nline: " + std::to_string(numberString));
					return false;
				}
				else
					temp_stack.push(token);
			continue;
		}
		if (token == "R7" && condition == false)
		{
			if (isOperationByCode(temp_stack.top()) == true && (temp_stack.top()!= "O20" && temp_stack.top() != "O19"))
			{
				problemDetected("Before ; get: " + temp_stack.top() + "\nline: " + std::to_string(numberString));
				return false;
			}
			return true;
		}
		if (condition == true && token == "R4" && fragment.length() == 0)
			return true;
		if (condition == true)
		{
			if (breachOfCodition(token,temp_stack)==true)
			{
				problemDetected("It is if/while/else expected in stack I_/N_/C_, but get: " + temp_stack.top() + "\nline: " + std::to_string(numberString));
				return false;
			}

		}
		else
		{
			std::string nextCode = fragment.substr(0, fragment.find(" "));
			if (nextCode != "R7")
			{
				if (breachOfExpressionWithNumberConst(token, temp_stack, nextCode) == true )
				{
					problemDetected("there is problem with expression " + token + " expected operation, but get: before " + temp_stack.top() + "/ after " + nextCode + "\nline: " + std::to_string(numberString));
					return false;
				}
			}
			
		}

		
		
		if (isOpenAnyBracket(token) == true && isCloseAnyBracket(temp_stack.top()) == false)
		{
			pushStackAndPop(temp_stack, token);
			continue;
		}
		else
			if (isOpenAnyBracket(token) == true)
			{
				problemDetected("Detected )(\nline: " + std::to_string(numberString));
				return false;
			}

		if (isCloseAnyBracket(token) == true && temp_stack.top() != "R7")
		{
			pushStackAndPop(temp_stack, token);
			continue;
		}
		else
			if (isCloseAnyBracket(token) == true)
			{
				problemDetected("Detected ;) in expression: \nline: " + std::to_string(numberString));
				return false;
			}
			
		
		if (isRepeatWordByCode(&isIdentifierByCode, temp_stack, token) == 0)
			return false;
		else
		{
			if (isRepeatWordByCode(&isNumberConstByCode, temp_stack, token) == 0)
				return false;
			else
			{
				if (isRepeatWordByCode(&isSymbolConst, temp_stack, token) == 0)
					return false;
				else
				{
					if (isRepeatWordByCode(&isOperationByCode, temp_stack, token) == 0)
						return false;
					else
						pushStackAndPop(temp_stack, token);
				}
			}
		}
		if (positionTypeConversion(fragment) == 0)
		{
			pushStackAndPop(temp_stack, fragment.substr(0, 2));
			pushStackAndPop(temp_stack, fragment.substr(3, fragment.find("R4") - 2));
			pushStackAndPop(temp_stack, fragment.substr(fragment.find("R4"), 2));
			fragment.erase(0, 10);
			//token = getToken(fragment);
		}
				
	}

	return true;
}

bool SyntaxAnalisator::breachOfCodition(std::string const& token,std::stack<std::string>const& temp_stack)
{
	return (isOperationByCode(token) == true && (isIdentifierByCode(temp_stack.top()) == false && isNumberConstByCode(temp_stack.top()) == false && isSymbolConst(temp_stack.top()) == false && isCloseAnyBracket(temp_stack.top()) == false)) || ((isIdentifierByCode(token) == true || isNumberConstByCode(token) == true || isSymbolConst(token) == true) && isOperationByCode(temp_stack.top()) == false);
}
bool SyntaxAnalisator::breachOfExpressionWithNumberConst(std::string const& token, std::stack<std::string>const& temp_stack,std::string nextCommand)
{
	bool isWordConst = (isNumberConstByCode(token) == true || isSymbolConst(token) == true);
	if (isWordConst == false)
		return false;
	if (temp_stack.top() == "R8" || nextCommand == "R8")
		return false;
	bool operation_word = isOperationByCode(temp_stack.top()) == true;
	bool word_operation =  isOperationByCode(nextCommand) == true;
	bool bracket_word =  temp_stack.top() == "R3";
	bool word_bracket =  nextCommand == "R4";
	bool breach = !((operation_word == true && word_operation == true) || (bracket_word == true && word_bracket == true));
	return breach == true;
}

int SyntaxAnalisator::isRepeatWordByCode(bool (*pFunctWordByCode)(std::string), std::stack<std::string>& temp_stack, std::string token)
{
	if ((*pFunctWordByCode)(token) == true && (*pFunctWordByCode)(temp_stack.top()) == true)
	{
		problemDetected("Detected repeat word! "+token+ "   stack: " + temp_stack.top() + "\nline:"+ std::to_string(numberString));
		return false;
	}
	return 1;
}

bool SyntaxAnalisator::checkReturnExpression(std::string& expr)
{
	expr.erase(0, 3);
	if (parseExpression(expr,false) == false)
		return false;
	return true;
}