#include "Translator_LanguageC.h"
#include "ReversePolishNotation.h"
#include "function.h"

ReversePolishNotation::ReversePolishNotation()
{
}
ReversePolishNotation::~ReversePolishNotation()
{
}

int ReversePolishNotation::getPriority(std::string word)
{
	for (auto& item : priority)
		if (item.first == word)
			return item.second;
	return -1;
}

bool ReversePolishNotation::isFunctionDeclaration(std::string line)
{
	size_t pos = 0;
	int count = 0;
	while ((pos = line.find(' ')) != std::string::npos)
	{
		std::string token = line.substr(0, pos);
		line.erase(0, pos + 1);
		if (isTypeDeclarationByCode(token) && count==0) // INT FLOAT CHAR DOUBLE
			count++;
		else
		{
			if (count == 1 && (token[0] == 'I' || token == "W4"))
			{
				count++;
				continue;
			}
			if (count == 2 && token == "R3")
				return true;
			
			return false;
		}	
	}
	return false;
}

bool ReversePolishNotation::upElemNotNameExpression(std::string upElem)
{
	
	return upElem != "PROC" && isIFCondition(upElem) == false && isCycle(upElem) == false
		&& upElem != "DCL" ? true : false;
}

bool ReversePolishNotation::isExistsComma(std::string line)
{
	size_t pos = 0;
	if (line.find("R8", 0) != std::string::npos && line.find("O", 0) == std::string::npos &&
		line.find("C", 0) == std::string::npos && line.find("N", 0) == std::string::npos && line.find("R3", 0) == std::string::npos)
		return true;
	return false;
}
bool ReversePolishNotation::isBeginFunctionName(std::string word)
{
	return word[0] == 'I' || word == "W9" || word == "W10" || word == "W20" ? true : false;
}

bool ReversePolishNotation::isExistsFunctionExpression(std::vector<std::map<std::string, int>>& stack)
{
	for (int i = 0; i < stack.size(); i++)
		if (stack[i].count("т") > 0)
			return true;
	return false;
}

bool ReversePolishNotation::isEmptyArray(std::string line)
{
	return line.find("R1 R2") != std::string::npos && line.find("R1 R2") == 0? true : false;
}

size_t ReversePolishNotation::positionTypeConversion(std::string line)
{
	if (line.find("R3 W15 R4", 0) != std::string::npos) 
		return line.find("R3 W15 R4", 0);
	if (line.find("R3 W16 R4", 0) != std::string::npos)
		return line.find("R3 W16 R4", 0);
	if (line.find("R3 W17 R4", 0) != std::string::npos)
		return line.find("R3 W17 R4", 0);
	return -1;
}

void ReversePolishNotation::recordFileFromStack(std::ofstream & file, std::map<std::string, int>::reverse_iterator upElemStack)
{
	if (isTypeDeclarationByCode(upElemStack->first) == true)
		file << upElemStack->second << " " << nameType(upElemStack->first) << " ";
	else
		file << upElemStack->first << " ";
	
};

bool isOpenCurlyBracket(std::string token)
{
	return token == "R5";
}
bool isCloseCurlyBracket(std::string token)
{
	return token == "R6";
}
bool isOpenBracket(std::string token)
{
	return token == "R3";
}
bool isCloseBracket(std::string token)
{
	return token == "R4";
}
bool isOpenSquareBracket(std::string token)
{
	return token == "R1";
}
bool isClosesquareBracket(std::string token)
{
	return token == "R2";
}
bool isComma(std::string token)
{
	return token == "R8";
}
bool isSemicolon(std::string token)
{
	return token == "R7";
}
void recordFileEndCondition(std::ofstream& file, std::string nameCondition, int number)
{
	file << std::endl << nameCondition << number << ":" << " ";
}

void ReversePolishNotation::reversePolishNotationAnalyze(std::string fileName_lexical, std::string fileName_RPN)
{
	std::ifstream lexical;
	std::ofstream fileAnalysis(fileName_RPN);
	lexical.exceptions(std::ifstream::badbit);
	try
	{
		lexical.open(fileName_lexical);

		if (lexical.is_open())
		{
			bool readComment = false;
			std::string temp = "", lastCommndIFFORWHILE_withoutTHEN = "";
			bool manyLineComment = false;
			int numberProc = 1;
			while (!lexical.eof())
			{
				std::string lineLexical = "";
				getline(lexical, lineLexical);
				if (lineLexical.find("W8") != std::string::npos)
				{
					fileAnalysis << lineLexical << std::endl;
					continue;
				}
				if (lineLexical.length() > 2 && (isComment((int)lineLexical[0], (int)lineLexical[1]) || isOneStringComment((int)lineLexical[0], (int)lineLexical[1])))
				{
					fileAnalysis << lineLexical << std::endl;
					continue;

				}
				if (manyLineComment == true)
				{
					fileAnalysis << lineLexical << std::endl;
					if(lineLexical.find("*/") != std::string::npos)
						manyLineComment = false;
					continue;
				}
				size_t pos = 0;
				std::string token="", nameFunctionInExpression="";
				bool isReadFunctionInExpresiion = false, isDeclareFunction = isFunctionDeclaration(lineLexical);
				bool isFor = false, isDeclareSomeVarOneType = isExistsComma(lineLexical);
				bool isEmptyArrayCurrent = false;
				while ((pos = lineLexical.find(' ')) != std::string::npos || lineLexical.length() !=0)
				{
					
					if (pos == std::string::npos)
					{
						token = lineLexical.substr(0, lineLexical.length());
						lineLexical = "";
					}
					else
					{
						if (positionTypeConversion(lineLexical) == 0)
						{
							token = lineLexical.substr(3, 3);
							lineLexical.erase(0,10);
						}
						else
						{
							token = lineLexical.substr(0, pos);
							if (isOpenSquareBracket(token))
								isEmptyArrayCurrent = isEmptyArray(lineLexical);
							lineLexical.erase(0, pos + 1);
						}
						
					}
					//TODO one line comment in expression

					if (isOpenCurlyBracket(token)==false)
					{
						if (stack.size() != 0 && lastCommndIFFORWHILE_withoutTHEN != "")
						{
							if (isIFCondition(stack.back().rbegin()->first) == true && lastCommndIFFORWHILE_withoutTHEN == "IF")
							{
								stack.back().rbegin()->second++;
								fileAnalysis << "л" << stack.back().rbegin()->second << " сок" << std::endl;
								lastCommndIFFORWHILE_withoutTHEN = "End IF";
							}
							if (isCycle(stack.back().rbegin()->first) == true && lastCommndIFFORWHILE_withoutTHEN == "Cycle")
							{
								fileAnalysis << std::endl << "лжя" << stack.back().rbegin()->second << " сок" << " ";
								lastCommndIFFORWHILE_withoutTHEN = "End Cycle";
							}
						}
					}
					else
						lastCommndIFFORWHILE_withoutTHEN = "";

					

					if (isComment((int)token[0], (int)token[1]) || isOneStringComment((int)token[0], (int)token[1]))
						continue;

					if (nameFunctionInExpression != "" && isDeclareFunction == false)
					{
						if (isBeginFunctionName(nameFunctionInExpression)==true && token == "R3")
							isReadFunctionInExpresiion = true;
						else
							nameFunctionInExpression = token;
					}else
						nameFunctionInExpression = token;

					int priorityToken = getPriority(token);

					if (priorityToken > -1)
					{
						if (stack.size() == 0)
						{
							if (isSemicolon(token))
								continue;
							std::map<std::string, int> tempMap;
							if (isReadFunctionInExpresiion == false)
								tempMap.insert(std::pair<std::string, int>(token, 0));
							else
								tempMap.insert(std::pair<std::string, int>("т", 1));
							stack.push_back(tempMap);
							continue;
						}
						else
						{
							if (isIFCondition(token)==true)
							{
								std::map<std::string, int> tempMap;
								tempMap.insert(std::pair<std::string, int>(token, 0));
								stack.push_back(tempMap);
								continue;
							}
							if (isELSECondition(token)==true)
							{
								auto upElemStack = stack.back().rbegin();
								if (isIFCondition(upElemStack->first) == true)
								{
									fileAnalysis << "ао л" << upElemStack->second << ":" << " ";
									upElemStack->second++;
									lastCommndIFFORWHILE_withoutTHEN = "ELSE";
									continue;
								}
							}
							if (isCycle(token)==true)
							{
								std::map<std::string, int> tempMap;
								tempMap.insert(std::pair<std::string, int>(token, 0));
								stack.push_back(tempMap);
								if (token == "W12")
									isFor = true;
								continue;
							}

							if (isOpenCurlyBracket(token)) //{
							{
								auto upElemStack = stack.back().rbegin();
								if (upElemStack->first == "PROC")
								{
									fileAnalysis << intToStrWithSpace(upElemStack->second) << " мо" << " ";
									continue;
								}
								if (isIFCondition(upElemStack->first) == true)
								{
									upElemStack->second++;
									fileAnalysis << "л" << upElemStack->second << " сок" << " ";
									if (lastCommndIFFORWHILE_withoutTHEN == "IF")
										lastCommndIFFORWHILE_withoutTHEN = "";
									continue;
								}
								if (isCycle(upElemStack->first)==true)
								{
									upElemStack->second++;
									if (upElemStack->first == "W12")
									{
										fileAnalysis << "лжя" << upElemStack->second << " сок" << " ";
									}	
									else
										fileAnalysis << "лж" << upElemStack->second << " сок" << " ";
									if (lastCommndIFFORWHILE_withoutTHEN == "Cycle")
										lastCommndIFFORWHILE_withoutTHEN = "";
									continue;
								}
							}
							if (isCloseCurlyBracket(token)) //}
							{
								auto upElemStack = stack.back().rbegin();
								if(isIFCondition(upElemStack->first)==true)
									fileAnalysis << "л" << upElemStack->second << ":";
								if (isCycle(upElemStack->first) == true)
								{
									if(upElemStack->first=="W12")
										fileAnalysis << "лжя" << upElemStack->second << ":";
									else
										fileAnalysis << "лж" << upElemStack->second << ":";
								}
								if (upElemStack->first == "PROC")
									fileAnalysis << "йо" << std::endl;
								stack.pop_back();
								continue;
							}
							if (isSemicolon(token))//;
							{
								std::map<std::string,int>::reverse_iterator upElemStack = stack.back().rbegin();
								while (stack.size() != 0 && upElemNotNameExpression(upElemStack->first)==true)
								{
									if (isFor == true && isOpenBracket(upElemStack->first))
										break;
									recordFileFromStack(fileAnalysis, upElemStack);

									stack.pop_back();
									if (stack.size() != 0)
										upElemStack = stack.back().rbegin();
								}
								if (stack.size() != 0 && upElemStack->first == "DCL")
								{
									stack.pop_back();
									upElemStack = stack.back().rbegin();
									fileAnalysis << intToStrWithSpace(upElemStack->second) << " йн";
								}
								if (stack.size() != 0 && isFor==false && lastCommndIFFORWHILE_withoutTHEN.find("End") != std::string::npos)
								{
									
									if (isIFCondition(stack.back().rbegin()->first) == true && lastCommndIFFORWHILE_withoutTHEN == "End IF")
										recordFileEndCondition(fileAnalysis, "л", stack.back().rbegin()->second);

									if (isCycle(stack.back().rbegin()->first) == true && lastCommndIFFORWHILE_withoutTHEN == "End Cycle")
										recordFileEndCondition(fileAnalysis, "лж", stack.back().rbegin()->second);

									stack.pop_back();
									lastCommndIFFORWHILE_withoutTHEN = "";
								}
								continue;
							}
							if (isOpenBracket(token))//(
							{
								if (isDeclareFunction == true)
								{
									while (stack.size() != 0)
									{
										std::map<std::string, int>::reverse_iterator upElemStack = stack.back().rbegin();
										recordFileFromStack(fileAnalysis, upElemStack);
										stack.pop_back();
									}
								}
								std::map<std::string, int> tempMap;
								
								if (isReadFunctionInExpresiion == false)
									tempMap.insert(std::pair<std::string, int>(token, 0));
								else
									tempMap.insert(std::pair<std::string, int>("т", 1));

								stack.push_back(tempMap);
								continue;
							}
							if (isCloseBracket(token))//)
							{
								std::string end = "R3";
								if (isReadFunctionInExpresiion == true)
									end = "т";
								while (stack.size() != 0 && stack.back().rbegin()->first != end)
								{
									
									std::map<std::string, int>::reverse_iterator upElemStack = stack.back().rbegin();
									recordFileFromStack(fileAnalysis, upElemStack);
									stack.pop_back();
								}
								if(stack.size()!=0)
									if(isOpenBracket(stack.back().rbegin()->first))
										stack.pop_back();
								if (isReadFunctionInExpresiion == true && stack.size() != 0)
								{
									if (stack.size() != 0 && stack.back().rbegin()->first == "т")
										fileAnalysis << ++stack.back().rbegin()->second << "" << stack.back().rbegin()->first << " ";
									stack.pop_back();
									isReadFunctionInExpresiion = isExistsFunctionExpression(stack);
								}
	

								if (isDeclareFunction == true)
								{
									while (stack.size() != 0)
									{
										std::map<std::string, int>::reverse_iterator upElemStack = stack.back().rbegin();
										recordFileFromStack(fileAnalysis, upElemStack);
										stack.pop_back();
									}
									std::map<std::string, int> tempMap;
									
									tempMap.insert(std::pair<std::string, int>("PROC", numberProc*10+1));
									stack.push_back(tempMap);
									numberProc++;
								}
								if (stack.size() != 0 && lastCommndIFFORWHILE_withoutTHEN.find("End") == std::string::npos)
								{
									if (isIFCondition(stack.back().rbegin()->first) == true)
										lastCommndIFFORWHILE_withoutTHEN = "IF";
									if (isCycle(stack.back().rbegin()->first) == true)
										lastCommndIFFORWHILE_withoutTHEN = "Cycle";
								}
								if (isFor == true)
									isFor = false;
								continue;
							}
							if (isOpenSquareBracket(token))
							{
								std::map<std::string, int> tempMap;
								tempMap.insert(std::pair<std::string, int>("ющл", 2));
								stack.push_back(tempMap);
								continue;
							}
							if (isComma(token))//,
							{
								auto upElemStack = stack.back().rbegin();
								if (isReadFunctionInExpresiion == false && isDeclareFunction == false && isDeclareSomeVarOneType == false)
								{
									while (stack.size() != 0 && upElemStack->first != "ющл")
									{
										fileAnalysis << upElemStack->first << " ";
										stack.pop_back();
										if (stack.size() != 0)
											upElemStack = stack.back().rbegin();
									}
									upElemStack->second++;
									continue;
								}
								else
								{
									
									if (isReadFunctionInExpresiion == true)
									{
										while (stack.size() != 0 && upElemStack->first != "т")
										{
											fileAnalysis << upElemStack->first << " ";
											stack.pop_back();
											if (stack.size() != 0)
												upElemStack = stack.back().rbegin();
										}
										upElemStack->second++;
										continue;
									}
									else
									{
										
										if (isDeclareFunction == true)
										{
											while (stack.size() != 0 && isOpenBracket(upElemStack->first)==false)
											{
												recordFileFromStack(fileAnalysis, upElemStack);
												stack.pop_back();
												if (stack.size() != 0)
													upElemStack = stack.back().rbegin();
											}
											//stack.pop_back();
										}
										else
										{
											while (true)
											{
												if (isTypeDeclarationByCode(upElemStack->first))
													break;
												fileAnalysis << upElemStack->first << " ";

												stack.pop_back();
												if (stack.size() != 0)
													upElemStack = stack.back().rbegin();
											}
											upElemStack->second++;
											
										}
										
										continue;
									}
									
								}
								
							}
							if (isClosesquareBracket(token))
							{
								auto upElemStack = stack.back().rbegin();
								while (stack.size() != 0 && upElemStack->first != "ющл" )
								{
									fileAnalysis << upElemStack->first << " ";
									stack.pop_back();
									if (stack.size() != 0)
										upElemStack = stack.back().rbegin();
								}
								if (isEmptyArrayCurrent == true)
								{
									fileAnalysis << --upElemStack->second << upElemStack->first << " ";
									isEmptyArrayCurrent = false;
								}
								else
									fileAnalysis << upElemStack->second << upElemStack->first << " ";
								stack.pop_back();
								continue;
							}
							auto upElemStack = stack.back().rbegin();
							bool upElemDownPriop = false;
							while (stack.size() != 0 && getPriority(upElemStack->first)>=getPriority(token))
							{
								upElemDownPriop = true;
								fileAnalysis << upElemStack->first << " ";
								stack.pop_back();
								if (stack.size() != 0)
									upElemStack = stack.back().rbegin();
							}
							if (stack.size()!=0 && isTypeDeclarationByCode(stack.back().rbegin()->first) == true && isDeclareSomeVarOneType == false)
							{
								std::map<std::string, int>::reverse_iterator upElemStack = stack.back().rbegin();
								while (stack.size() != 0 && upElemNotNameExpression(upElemStack->first)==true)
								{
									if (isFor == true && upElemStack->first == "R3")
										break;
									recordFileFromStack(fileAnalysis, upElemStack);

									stack.pop_back();
									if (stack.size() != 0)
										upElemStack = stack.back().rbegin();
								}
								
							}
							if (upElemDownPriop == true)
							{
								upElemDownPriop = false;
								std::map<std::string, int> tempMap;
								tempMap.insert(std::pair<std::string, int>(token, 0));
								stack.push_back(tempMap);
								continue;
							}

							std::map<std::string, int> tempMap;
							tempMap.insert(std::pair<std::string, int>(token, 0));
							stack.push_back(tempMap);
						
						}
					}
					else
					{
						std::map<std::string, int> tempMap;
						if (isConst(token))
						{
							pos = lineLexical.find(' ');
							token += " " + lineLexical.substr(0, pos);
							lineLexical.erase(0, pos + 1);
						}
						if (isDeclareFunction == true && isTypeDeclarationByCode(token) == true)
						{
							tempMap.insert(std::pair<std::string, int>(token, 1));
							stack.push_back(tempMap);
						}else
							if (isTypeDeclarationByCode(token) == true)
							{
								if (isDeclareSomeVarOneType==true)
								{
									tempMap.insert(std::pair<std::string, int>("DCL", 1));
									stack.push_back(tempMap);
									std::map<std::string, int>::iterator it = tempMap.end();
									it--;
									tempMap.erase(it);
								}
								
								tempMap.insert(std::pair<std::string, int>(token, 1));
								stack.push_back(tempMap);
							}
							else
								fileAnalysis << token << " ";
								
					}
				}
				
				fileAnalysis << std::endl;
			}
		}

	}
	catch (const std::ifstream::failure & exep)
	{
		std::cout << " Exception opening/reading file";
		std::cout << exep.what();
		System::Windows::Forms::MessageBox::Show("File don't open", "error", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
	}

	lexical.close();
	fileAnalysis.close();
}
