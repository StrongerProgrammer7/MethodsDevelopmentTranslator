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

bool ReversePolishNotation::isExistsSymbolToTable(std::string word)
{
	for (auto& item : priority)
		if (item.first == word)
			return true;
	return false;
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
			std::string temp = "";
			while (!lexical.eof())
			{
				std::string lineLexical = "";
				getline(lexical, lineLexical);
				if (lineLexical.length() > 2 && (isComment((int)lineLexical[0],(int)lineLexical[1]) || isOneStringComment((int)lineLexical[0], (int)lineLexical[1])))
					continue;

				size_t pos = 0;
				std::string token="", tempReadFunction="";
				bool readFunction = false;
				while ((pos = lineLexical.find(' ')) != std::string::npos || lineLexical.length() !=0)
				{
					if (pos == std::string::npos)
					{
						token = lineLexical.substr(0, lineLexical.length());
						lineLexical = "";
					}
					else
					{
						token = lineLexical.substr(0, pos);
						lineLexical.erase(0, pos + 1);
					}
					if (tempReadFunction != "")
					{
						if (tempReadFunction[0] == 'I' && token == "R3")
							readFunction = true;
						else
							tempReadFunction = token;
					}else
						tempReadFunction = token;


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
							if (token == "R3")
							{
								if (readFunction == false)
								{
									std::map<std::string, int> tempMap;
									tempMap.insert(std::pair<std::string, int>(token, 0));
									stack.push_back(tempMap);
									continue;
								}
								else
								{
									std::map<std::string, int> tempMap;
									tempMap.insert(std::pair<std::string, int>("Ô", 1));
									stack.push_back(tempMap);
									continue;
								}
								
							}
							if (token == "R4")
							{
								std::string end = "R3";
								if (readFunction == true)
									end = "Ô";
								while (stack.size() != 0 && stack.back().rbegin()->first != end)
								{
									auto upElemStack = stack.back().rbegin();
									fileAnalysis << upElemStack->first << " ";
									stack.pop_back();
								}
								if (readFunction == true && stack.size() !=0)
								{
									auto upElemStack = stack.back().rbegin();
									upElemStack->second++;
									fileAnalysis << upElemStack->second << upElemStack->first << " ";
									readFunction = false;
								}
								stack.pop_back();
								continue;
							}
							if (token == "R1")
							{
								std::map<std::string, int> tempMap;
								tempMap.insert(std::pair<std::string, int>("ÀÝÌ", 2));
								stack.push_back(tempMap);
								continue;
							}
							if (token == "R8")
							{
								if (readFunction == false)
								{
									auto upElemStack = stack.back().rbegin();
									while (stack.size() != 0 && upElemStack->first != "ÀÝÌ")
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
									auto upElemStack = stack.back().rbegin();
									while (stack.size() != 0 && upElemStack->first != "Ô")
									{
										fileAnalysis << upElemStack->first << " ";
										stack.pop_back();
										if (stack.size() != 0)
											upElemStack = stack.back().rbegin();
									}
									upElemStack->second++;
									continue;
								}
								
							}
							if (token == "R2")
							{
								auto upElemStack = stack.back().rbegin();
								while (stack.size() != 0 && upElemStack->first != "ÀÝÌ" )
								{
									fileAnalysis << upElemStack->first << " ";
									stack.pop_back();
									if (stack.size() != 0)
										upElemStack = stack.back().rbegin();
								}
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
						fileAnalysis << token << " ";
					}
				}
				
				if (stack.size() != 0)
				{
					auto upElemStack = stack.back().rbegin();
					while (stack.size() != 0)
					{
						fileAnalysis << upElemStack->first << " ";
						stack.pop_back();
						if (stack.size() != 0)
							upElemStack = stack.back().rbegin();
						

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
	}

	lexical.close();
	fileAnalysis.close();
}

