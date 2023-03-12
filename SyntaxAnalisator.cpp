#include "Translator_LanguageC.h"
#include "SyntaxAnalisator.h"
#include "function.h"


SyntaxAnalisator::SyntaxAnalisator()
{
}


SyntaxAnalisator::~SyntaxAnalisator()
{
}

bool isIdentifierByCode(std::string token)
{
	return token[0] == 'I' ? true : false;
}

bool isOperationByCode(std::string token)
{
	return token[0] == 'O' ? true : false;
}

bool isSymbolConst(std::string token)
{
	return token[0] == 'C' ? true : false;
}

bool isNumberConstByCode(std::string token)
{
	return token[0] == 'N' ? true : false;
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
		std::ifstream lexicalFile("./translator_file/lexical.txt");
		if (lexicalFile.is_open())
		{
			std::string temp = "";
			bool isDeclareFunction = false,isCycle = false, isIFElse = false, manyLineComment = false;;
			while (!lexicalFile.eof())
			{
				std::string code = "";
				getline(lexicalFile, code);

				if (code.find("W8") == 0)
				{
					if (countFunction <= this->countInclude)
						countInclude++;
					else
						return false;
					continue;
				}

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

				if (code.find("R5") == 0)
				{
					if (isDeclareFunction == false && isCycle == false && isIFElse == false)
						return false;
					if (isDeclareFunction == true)
						isDeclareFunction = false;
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
				int countInclude = 0, countFunction = 0;
				
				while ((pos = code.find(' ')) != std::string::npos || code.length() != 0)
				{
					token = getToken(code);

					if (isInclude(token) == true || token=="W9" || token =="W10")
						return false;
	
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
							return false;
					}

					if (isTypeDeclarationByCode(token)==true)
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
						}
						if (token == "W12")
						{
							if (operators(code, "for") == false)
								return false;
						}
						if (isIdentifierByCode(token) == true)
						{
							if (operators(code, "Id") == false)
								return false;
						}
						else
							return false;
					}
				}
			}
			return true;
		}
		else
		{
			System::Windows::Forms::MessageBox::Show("File don't open", "Error", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
			return false;
		}
	}
	catch (const std::exception&)
	{
		System::Windows::Forms::MessageBox::Show("Problem with file to Syntaxanalisator", "Error",System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
	}
	
	
}



bool SyntaxAnalisator::setArguments(std::string& code)
{
	__int64 pos = 0;
	std::string temp = code.substr(0, code.find("R4"));
	code.erase(0, code.find("R4") + 3);
	bool type_ident = false;
	while ((pos = temp.find(' ')) != std::string::npos || temp.length() != 0)
	{
		std::string token = temp.substr(0, pos);
		temp.erase(0, pos + 1);
		if (token == "R8")
			continue;
		if (isTypeDeclarationByCode(token) == true && type_ident == false)
		{
			type_ident = true;
			continue;
		}
		else
			if (isTypeDeclarationByCode(token) == true)
				return false;

		if (isIdentifierByCode(token)==true && type_ident == true)
		{
			type_ident = false;
			continue;
		}
		else
			if (isIdentifierByCode(token)==true)
				return false;
	}
	return true;
}

bool is_declareFunction(std::string code)
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
			if (token == "R3" && countSpace == 3)
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
	if (isTypeDeclarationByCode(code.substr(0, code.find(" ") - 1)) == true)
	{
		code.erase(0, code.find(" ")+1);
		temp = code.substr(0, code.find("R7") + 2);
		code.erase(0, code.find("R7") + 3);
		if (operatorEqual(temp) == false)
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
		if (token == "R7" && ident_comma == true)
			break;
		else
			if (token == "R7")
				return false;

		if (isIdentifierByCode(token) == true && ident_comma == false)
		{
			ident_comma = true;
			continue;
		}
		else
			if (isIdentifierByCode(token) == true)
				return false;
		
		if (token == "R8" && ident_comma == true)
		{
			ident_comma = false;
			continue;
		}
		else
			if (token == "R8")
				return false;

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
		__int64 posComma = code.find('R8');
		if (posComma != std::string::npos && code.find("O5", posComma) != std::string::npos)
		{
			fragmentBeforeComma = code.substr(0, posComma);
			code.erase(0, posComma + 1);
			if(parseExpression(fragmentBeforeComma,false)==false)
				return false;
			
			if(isTypeDeclarationByCode(code.substr(0,2))==true || isOperationByCode(code.substr(0, 2))==true || isSymbolConst(code.substr(0, 2))==true
				|| isCloseAnyBracket(code.substr(0, 2))==true || isOpenAnyBracket(code.substr(0, 2))==true)
				return false;
			continue;
		}

		if (code.find('R7') != std::string::npos)
		{
			if (parseExpression(code,false) == false)
				return false;
			return true;
		}

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
	bool (*pFunction_Id_Num_Sym_OperByCode)(std::string) = NULL;

	while ((pos = fragment.find(' ')) != std::string::npos || fragment.length() != 0)
	{
		token = getToken(fragment);
		fragment.erase(0, pos + 1);
		if (temp_stack.size() == 0)
			temp_stack.push(token);
		if (token == "R7" && condition==false)
			return true;
		if (condition == true && token == "R4" && fragment.length() == 0)
			return true;

		if (positionTypeConversion(fragment) == 0)
		{
			pushStackAndPop(temp_stack,fragment.substr(0, 2));
			pushStackAndPop(temp_stack, fragment.substr(3, fragment.find("R4") - 2));
			pushStackAndPop(temp_stack, fragment.substr(fragment.find("R4"), 2));
			fragment.erase(0, 10);
			token = getToken(fragment);
		}
		if (isOpenAnyBracket(token) == true && isCloseAnyBracket(temp_stack.top()) == false)
		{
			pushStackAndPop(temp_stack, token);
			continue;
		}
		else
			if (isOpenAnyBracket(token) == true)
				return false;

		if (isCloseAnyBracket(token) == true && temp_stack.top() != "R8")
		{
			pushStackAndPop(temp_stack, token);
			continue;
		}
		else
			if (isCloseAnyBracket(token) == true && temp_stack.top() != "R8")
				return false;
			
		pFunction_Id_Num_Sym_OperByCode = &isIdentifierByCode;
		if (checkToken(pFunction_Id_Num_Sym_OperByCode, temp_stack, token) == 0)
			return false;
		else
		{
			pFunction_Id_Num_Sym_OperByCode = &isNumberConstByCode;
			if (checkToken(pFunction_Id_Num_Sym_OperByCode, temp_stack, token) == 0)
				return false;
			else
			{
				pFunction_Id_Num_Sym_OperByCode = &isSymbolConst;
				if (checkToken(pFunction_Id_Num_Sym_OperByCode, temp_stack, token) == 0)
					return false;
				else
				{
					pFunction_Id_Num_Sym_OperByCode = &isOperationByCode;
					if (checkToken(pFunction_Id_Num_Sym_OperByCode, temp_stack, token) == 0)
						return false;
					else
						pushStackAndPop(temp_stack, token);
				}
			}
		}
		
		
	
		/*if (isIdentifierByCode(token) == true && isIdentifierByCode(temp_stack.top()) == false)
		{
			pushStackAndPop(temp_stack, token);
			continue;
		}
		else
			if (isIdentifierByCode(token)==true)
				return false;

		if (isNumberConstByCode(token) == true && isNumberConstByCode(temp_stack.top()) == false)
		{
			pushStackAndPop(temp_stack, token);
			continue;
		}
		else
			if (isNumberConstByCode(token))
				return false;

		if (isSymbolConst(token) == true && isSymbolConst(temp_stack.top()) == false)
		{
			pushStackAndPop(temp_stack, token);
			continue;
		}
		else
			if (isSymbolConst(token)==true)
				return false;
		if (isOperationByCode(token) == true && isOperationByCode(temp_stack.top()) == false)
		{
			pushStackAndPop(temp_stack, token);
			continue;
		}
		else
			if (isOperationByCode(token))
				return false;*/
		
	}

	return true;
}


int checkToken(bool (*pFunctByCode)(std::string), std::stack<std::string>& temp_stack, std::string token)
{
	if ((*pFunctByCode)(token) == true && (*pFunctByCode)(temp_stack.top()) == false)
	{
		//pushStackAndPop(temp_stack, token);
		return 1;
	}
	else
		if ((*pFunctByCode)(token) == true)
			return 0;
	return 1;
}