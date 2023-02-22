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
	//priority
	for (auto& item : priority)
	{
		if (item.first == word)
			return item.second;
	}
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
		if ((token == "W1" || token == "W2" || token == "W3" || token == "W14") && count==0) // INT FLOAT CHAR DOUBLE
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
bool ReversePolishNotation::isTypeDeclaration(std::string word)
{
	return word=="W1" || word=="W2" || word=="W3" || word=="W14" || word == "W15" || word == "W16" || word == "W17" || 
		word=="W18" || word=="W19" || word=="W13" || word == "W19 W1"
		|| word == "W19 W2" || word == "W19 W3" || word == "W19 W17" || word == "W19 W18" || word == "W19 W16" || word == "W19 W15" ? true : false;
}
bool ReversePolishNotation::isCycle(std::string word)
{
	return word == "W7" || word == "W12" ? true : false;
}

bool ReversePolishNotation::isIFCondition(std::string word)
{
	return word == "W5" ? true : false;
}
bool ReversePolishNotation::isELSECondition(std::string word)
{
	return word == "W6" ? true : false;
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
	return word[0] == 'I' || word == "W9" || word == "W10" ? true : false;
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

std::string ReversePolishNotation::nameType(std::string token)
{
	if (token == "W1")
		return "int";
	if (token == "W2")
		return "float";
	if (token == "W3")
		return "char";
	if (token == "W14")
		return "double";
	if (token == "W15")
		return "int*";
	if (token == "W16")
		return "float*";
	if (token == "W17")
		return "double*";
	if (token == "W18")
		return "char*";
	if (token == "W19 W1")
		return "const int";
	if (token == "W19 W2")
		return "const float";
	if (token == "W19 W3")
		return "const char";
	if (token == "W19 W14")
		return "const double";
	if (token == "W19 W15")
		return "const int*";
	if (token == "W19 W16")
		return "const float*";
	if (token == "W19 W17")
		return "const double*";
	if (token == "W19 W18")
		return "const char*";
	return "";
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
				if (lineLexical.length() > 2 && isComment((int)lineLexical[0], (int)lineLexical[1]) && lineLexical.find("*/") == std::string::npos)
					manyLineComment = true;
				if (lineLexical.length() > 2 && (isComment((int)lineLexical[0], (int)lineLexical[1]) || isOneStringComment((int)lineLexical[0], (int)lineLexical[1])))
					continue;
				if (manyLineComment == true)
				{
					if (lineLexical.find("*/") == std::string::npos)
						continue;
					else
					{
						manyLineComment = false;
						continue;
					}
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
							if (token == "R1")
								isEmptyArrayCurrent = isEmptyArray(lineLexical);
							lineLexical.erase(0, pos + 1);
						}
						
					}

					if (token != "R5")
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
								fileAnalysis << std::endl << "лж" << stack.back().rbegin()->second << " сок" << " ";
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
							std::map<std::string, int> tempMap;
							tempMap.insert(std::pair<std::string,int>(token, 0));
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

							if (token== "R5") //{
							{
								auto upElemStack = stack.back().rbegin();
								if (upElemStack->first == "PROC")
								{
									fileAnalysis << upElemStack->second << " мо" << " ";
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
									fileAnalysis << "лж" << upElemStack->second << " сок" << " ";
									if (lastCommndIFFORWHILE_withoutTHEN == "Cycle")
										lastCommndIFFORWHILE_withoutTHEN = "";
									continue;
								}
							}
							if (token=="R6") //}
							{
								auto upElemStack = stack.back().rbegin();
								if(isIFCondition(upElemStack->first)==true)
									fileAnalysis << "л" << upElemStack->second << ":";
								if(isCycle(upElemStack->first)==true)
									fileAnalysis << "лж" << upElemStack->second << ":";
								if (upElemStack->first == "PROC")
									fileAnalysis << "йо" << std::endl;
								stack.pop_back();
								continue;
							}
							if (token == "R7")//;
							{
								auto upElemStack = stack.back().rbegin();
								while (stack.size() != 0 && upElemNotNameExpression(upElemStack->first)==true)
								{
									if (isFor == true && upElemStack->first == "R3")
										break;
									if (isTypeDeclaration(upElemStack->first) == true)
										fileAnalysis << upElemStack->second << " " << nameType(upElemStack->first) << " ";
									else
										fileAnalysis << upElemStack->first << " ";

									stack.pop_back();
									if (stack.size() != 0)
										upElemStack = stack.back().rbegin();
								}
								if (stack.size() != 0 && upElemStack->first == "DCL")
								{
									stack.pop_back();
									upElemStack = stack.back().rbegin();
									fileAnalysis << upElemStack->second << " йн";
								}
								if (stack.size() != 0 && isFor==false && lastCommndIFFORWHILE_withoutTHEN.find("End") != std::string::npos)
								{
									
									if (isIFCondition(stack.back().rbegin()->first) == true && lastCommndIFFORWHILE_withoutTHEN == "End IF")
									{
										fileAnalysis << std::endl << "л" << stack.back().rbegin()->second << ":" << " ";
										stack.pop_back();
									}
									if (isCycle(stack.back().rbegin()->first) == true && lastCommndIFFORWHILE_withoutTHEN == "End Cycle")
									{
										fileAnalysis << std::endl << "лж" << stack.back().rbegin()->second << ":" << " ";
										stack.pop_back();
									}
									lastCommndIFFORWHILE_withoutTHEN = "";
									
								}
								continue;
							}
							if (token == "R3")//(
							{
								std::map<std::string, int> tempMap;
								if (isReadFunctionInExpresiion == false)
									tempMap.insert(std::pair<std::string, int>(token, 0));
								else
									tempMap.insert(std::pair<std::string, int>("т", 1));

								stack.push_back(tempMap);
								continue;
							}
							if (token == "R4")//)
							{
								std::string end = "R3";
								if (isReadFunctionInExpresiion == true)
									end = "т";
								while (stack.size() != 0 && stack.back().rbegin()->first != end)
								{
									
									auto upElemStack = stack.back().rbegin();
									if (isTypeDeclaration(upElemStack->first)==true)
										fileAnalysis << upElemStack->second << " " << nameType(upElemStack->first) << " ";
									else
										fileAnalysis << upElemStack->first << " ";
									stack.pop_back();
								}
								if(stack.size()!=0)
									if(stack.back().rbegin()->first == "R3")
										stack.pop_back();
								if (isReadFunctionInExpresiion == true && stack.size() != 0)
								{
									if (stack.size() != 0 && stack.back().rbegin()->first == "т")
										fileAnalysis << ++stack.back().rbegin()->second << " " << stack.back().rbegin()->first << " ";
									stack.pop_back();
									isReadFunctionInExpresiion = isExistsFunctionExpression(stack);
								}
	

								if (isDeclareFunction == true)
								{
									while (stack.size() != 0)
									{
										auto upElemStack = stack.back().rbegin();
										if (isTypeDeclaration(upElemStack->first)==true)
											fileAnalysis << upElemStack->second << " " << nameType(upElemStack->first) << " ";
										else
											fileAnalysis << upElemStack->first << " ";
											
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
							if (token == "R1")
							{
								std::map<std::string, int> tempMap;
								tempMap.insert(std::pair<std::string, int>("ющл", 2));
								stack.push_back(tempMap);
								continue;
							}
							if (token == "R8")//,
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
											while (stack.size() != 0 && upElemStack->first != "R3")
											{
												std::string temp = "";
												if (isTypeDeclaration(upElemStack->first))
													temp = nameType(upElemStack->first);

												if (temp == "")
													fileAnalysis << upElemStack->first << " ";
												else
													fileAnalysis << upElemStack->second << temp << " ";
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
												if (isTypeDeclaration(upElemStack->first))
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
							if (token == "R2")
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
							if (isTypeDeclaration(stack.back().rbegin()->first) == true && isDeclareSomeVarOneType == false)
							{
								auto upElemStack = stack.back().rbegin();
								//fileAnalysis << upElemStack->second << " " << nameType(upElemStack->first) << " "; stack.pop_back();
								while (stack.size() != 0 && upElemNotNameExpression(upElemStack->first)==true)
								{
									if (isFor == true && upElemStack->first == "R3")
										break;
									if (isTypeDeclaration(upElemStack->first) == true)
										fileAnalysis << upElemStack->second << " " << nameType(upElemStack->first) << " ";
									else
										fileAnalysis << upElemStack->first << " ";

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
						if (token == "W19")
						{
							pos = lineLexical.find(' ');
							token += " " + lineLexical.substr(0, pos);
							lineLexical.erase(0, pos + 1);
						}
						if (isDeclareFunction == true && isTypeDeclaration(token) == true)
						{
							tempMap.insert(std::pair<std::string, int>(token, 1));
							stack.push_back(tempMap);
						}else
							if (isTypeDeclaration(token) == true)
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

