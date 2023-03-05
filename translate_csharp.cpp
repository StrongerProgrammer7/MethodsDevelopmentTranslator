#include "translate_csharp.h"
#include "function.h"


Translate_csharp::Translate_csharp()
{
}


Translate_csharp::~Translate_csharp()
{
}

std::string Translate_csharp::getSymbolOperationByCode(std::string sign)
{
	for (int i = 0; i < SIZE_operation; i++)
		if (operations[i][1] == sign)
			return operations[i][0];
	return "";
}
std::string Translate_csharp::getSymbolSeparatorsByCode(std::string separator)
{
	for (int i = 0; i < SIZE_separators; i++)
		if (separators[i][1] == separator)
			return separators[i][0];
	return "";
}
std::string Translate_csharp::getSymbolServiceWordByCode( std::string service)
{
	for (int i = 0; i < SIZE_serviceWord; i++)
		if (serviceWord[i][1] == service)
			return serviceWord[i][0];
	return "";
}

std::string Translate_csharp::getSymbolConst_Identifier_ByCode(std::map<std::string, std::string>& table, std::string code)
{
	std::map <std::string, std::string> ::iterator it = table.begin();
	for (; it!= table.end(); it++)
		if (it->second==code)
			return it->first;
	return "";
}

std::string Translate_csharp::reverseExpression(std::string expression)
{
	std::stringstream expr(expression);
	std::vector < std::string>vec;
	while (expr >> expression) vec.push_back(expression);
	reverse(vec.begin(), vec.end());
	std::string temp = "";
	for (auto item : vec)
		temp += item + " ";
	return temp;
}

std::string Translate_csharp::declareFunction(std::string line)
{
	size_t pos = 0;
	int i = 0;
	std::string declare = "\tpublic ";
	line.erase(line.rfind(" "), 1);
	while ((pos = line.find(' ')) != std::string::npos || line.length() != 0)
	{
		if (i == 2)
			return declare += "(" + line + ")";

		declare += line.substr(0, pos) + " ";
		i++;
		line.erase(0, pos + 1);
	}
	return declare;

}
std::string Translate_csharp::declareFunctionExpression(std::string line)
{
	line.erase(line.rfind(" "), 1);
	std::string temp = line.substr(0, line.find(" "));
	line.erase(0, line.find(" ") + 1);
	temp += "(" + line +") ";
	return temp;
}

std::string Translate_csharp::strArray(std::string line)
{
	line.erase(line.rfind(" "), 1);
	std::string temp = line.substr(0, line.find(" "));
	line.erase(0, line.find(" ") + 1);
	temp += "[" + line + "]";
	return temp;
}

std::string Translate_csharp::declareCondition(std::string line,std::string nameCondition)
{
	line.erase(line.rfind(" "), 1);
	return nameCondition +"(" + line + ")";
}

std::string Translate_csharp::correctCycleFor(std::string for_line)
{
	int countSpace = 0, countSeparator = 0;
	std::string temp = for_line.substr(0, for_line.find(" ")) + " ";
	for_line.erase(0, for_line.find(" ") + 1);
	while (for_line.length() != 0)
	{
		
		if (countSpace == 3)
		{
			temp += ";";
			countSeparator++;
			countSpace = 0;
		}
		if (countSeparator == 2)
			break;
		temp += for_line.substr(0, for_line.find(" ")) + " ";
		for_line.erase(0, for_line.find(" ") + 1);
		countSpace++;
	}
	temp += for_line;
	return temp;
}


void Translate_csharp::transalteToCSharp(std::string fileName_RPN, std::string fileName_CSharp)
{

	std::ifstream rpn;
	std::ofstream fileAnalysis(fileName_CSharp);
	rpn.exceptions(std::ifstream::badbit);
	try
	{
		fileAnalysis << "using System;" << std::endl;
		fileAnalysis << "\n namespace from_C_to_C_Sharp\n{\n\tclass Program\n\t{\n\t";
		rpn.open(fileName_RPN);
	
		if (rpn.is_open())
		{
			bool readComment = false;
			bool manyLineComment = false;
			int numberProc = 1;
			bool mainFunctionRecorded = false;
			std::string lineForRecordInFile = "";
			while (!rpn.eof())
			{
				std::string lineRPN = "";
				getline(rpn, lineRPN);
				if ((lineRPN.length() == 0 || lineRPN == " ") && lineForRecordInFile=="")
					continue;
				if (lineRPN.find("W8") != std::string::npos)
				{
					fileAnalysis << "//" + lineRPN + "\n";
					continue;
				}
				if (lineRPN.find("W4") != std::string::npos)
				{
					fileAnalysis << "\t\tstatic void Main(string[] args)\n\t\t{\n";
					mainFunctionRecorded = true;
					continue;
				}
				if (lineRPN.find("W11") != std::string::npos)
				{
					if (lineForRecordInFile.length() != 0)
					{
						lineForRecordInFile.erase(lineForRecordInFile.rfind(" "), 1);
						fileAnalysis << "\t\t\t" << lineForRecordInFile << ";" << std::endl;
						lineForRecordInFile = "";
					}
					lineRPN = reverseExpression(lineRPN);
					lineRPN.erase(lineRPN.rfind(" "), 1);
					fileAnalysis << "\t\t\t" << lineRPN << ";" << std::endl;
					continue;
				}
				if (lineRPN.length() > 2 && isComment((int)lineRPN[0], (int)lineRPN[1]) && lineRPN.find("*/") == std::string::npos)
					manyLineComment = true;
				if (lineRPN.length() > 2 && (isComment((int)lineRPN[0], (int)lineRPN[1]) || isOneStringComment((int)lineRPN[0], (int)lineRPN[1])))
				{
					fileAnalysis << lineRPN << std::endl;
					continue;
				}
				if (manyLineComment == true)
				{
					if (lineRPN.find("*/") == std::string::npos)
					{
						fileAnalysis << lineRPN << std::endl;
						continue;
					}
					else
					{
						fileAnalysis << lineRPN << std::endl;
						manyLineComment = false;
						continue;
					}
				}

				if (lineRPN.find("ÍÏ") != std::string::npos)
				{
					if (mainFunctionRecorded == true)
						continue;
					lineForRecordInFile = reverseExpression(lineForRecordInFile);
					lineForRecordInFile = declareFunction(lineForRecordInFile);
					fileAnalysis << lineForRecordInFile << std::endl;
					fileAnalysis << "\t\t{\n";
					lineForRecordInFile = "";
					continue;
				}
				else
				{
					if (lineRPN == "ÊÏ")
					{
						fileAnalysis << "\t\t}\n";
						lineForRecordInFile = "";
						if (mainFunctionRecorded == true)
							mainFunctionRecorded = false;
						continue;
					}
					
					if (lineRPN.find("Ì") != std::string::npos)
					{
						if (lineRPN.find("ÓÏË") != std::string::npos)
						{
							lineForRecordInFile.erase(lineForRecordInFile.rfind(" "), 1);
							lineForRecordInFile = reverseExpression(lineForRecordInFile);
							if (lineRPN.find("ÌÖ") != std::string::npos && lineRPN.find("ÌÖÑ") == std::string::npos)
								lineForRecordInFile = declareCondition(lineForRecordInFile,"while");
							else
								if (lineRPN.find("ÌÖÑ") != std::string::npos)
								{
									lineForRecordInFile = declareCondition(lineForRecordInFile, "for");
									lineForRecordInFile = correctCycleFor(lineForRecordInFile);
								}
								else
									lineForRecordInFile = declareCondition(lineForRecordInFile, "if");

							fileAnalysis << "\t\t\t" << lineForRecordInFile << std::endl;
							fileAnalysis << "\t\t\t{\n";
							lineForRecordInFile = "";
							continue;
							
						}
						if (lineRPN.find("ÀÝÌ") == std::string::npos)
						{
							if (lineForRecordInFile != "")
								fileAnalysis << "\t\t\t\t" << lineForRecordInFile << ";\n";
							lineForRecordInFile = "";
							fileAnalysis << "\t\t\t}\n";
							continue;
						}
						
					}
					else
					{
						if (lineForRecordInFile.length() != 0)
						{
							lineForRecordInFile = reverseExpression(lineForRecordInFile);
							lineForRecordInFile.erase(lineForRecordInFile.rfind(" "), 1);
							fileAnalysis << "\t\t\t" << lineForRecordInFile << ";" << std::endl;
							lineForRecordInFile = "";
						}
						
						
					}
				}
				

				size_t pos = 0;
				std::string token = "", nameFunctionInExpression = "";
				while ((pos = lineRPN.find(' ')) != std::string::npos || lineRPN.length() != 0)
				{

					if (pos == std::string::npos)
					{
						token = lineRPN.substr(0, lineRPN.length());
						lineRPN = "";
					}
					else
					{
						token = lineRPN.substr(0, pos);
						lineRPN.erase(0, pos + 1);
					}
					if (token.find("ÀÝÌ") != std::string::npos)
					{
						token.erase(token.find("ÀÝÌ"), 3);
						int countArgArr = stoi(token);
						for (int i = 0; i < countArgArr; i++)
						{
							lineForRecordInFile += stack.top() +" ";
							stack.pop();
						}
						lineForRecordInFile = reverseExpression(lineForRecordInFile);
						lineForRecordInFile = strArray(lineForRecordInFile);
						stack.push(lineForRecordInFile);
						continue;
					}
					if (token.find("Ô") != std::string::npos)
					{
						token.erase(token.find("Ô"), 2);
						int countArg = stoi(token);
						lineForRecordInFile = "";
						for (int i = 0; i < countArg; i++)
						{
							lineForRecordInFile += stack.top() + " ";
							stack.pop();
						}
						lineForRecordInFile = reverseExpression(lineForRecordInFile);
						lineForRecordInFile = declareFunctionExpression(lineForRecordInFile);
						if (countArg > 2)
						{
							std::string temp = lineForRecordInFile.substr(0, lineForRecordInFile.find(" ")) + ",";
							lineForRecordInFile.erase(0, lineForRecordInFile.find(" ") + 1);
							int ind = 1;
							while (lineForRecordInFile.length() != 0)
							{
								if(ind<countArg-2)
									temp += lineForRecordInFile.substr(0, lineForRecordInFile.find(" ")) + ",";
								else
									temp += lineForRecordInFile.substr(0, lineForRecordInFile.find(" ")) + "";
								lineForRecordInFile.erase(0, lineForRecordInFile.find(" ") + 1);
								ind++;
							}
							temp += lineForRecordInFile;
							lineForRecordInFile = temp;
						}
						stack.push(lineForRecordInFile);
						continue;
					}
					if (token.find("O") != std::string::npos)
					{
						lineForRecordInFile = stack.top();
						
						if (getSymbolOperationByCode(token) == "++" || getSymbolOperationByCode(token) == "--")
						{
							lineForRecordInFile += getSymbolOperationByCode(token) + " ";
							lineForRecordInFile = reverseExpression(lineForRecordInFile);
						}
						else
						{
							lineForRecordInFile += " ";
							lineForRecordInFile += getSymbolOperationByCode(token) + " ";
						}

						
						stack.pop();
						if (!stack.empty())
						{
							lineForRecordInFile += stack.top() + " ";
							stack.pop();
						}
						stack.push(lineForRecordInFile);
						continue;
					}
					if (isTypeDeclaration(token)==true)
					{
						int countType = std::stoi(stack.top());
						stack.pop();
						if (stack.top() == "W10")
							if (lineRPN.length() != 0 && lineRPN[1] == 'Ô' || lineRPN[2] == 'Ô')
							{
								stack.push(token);
								continue;
							}
						
						if (isConst(token) == true)
						{
							pos = lineRPN.find(' ');
							token += " " + lineRPN.substr(0, pos);
							lineRPN.erase(0, pos + 1);
						}
						if (lineRPN.find("O5") == 0)
						{
							lineForRecordInFile = "(" + token + ")";
						}else
							lineForRecordInFile = token + " ";
						
						for (int i = 0; i < countType; i++)
						{
							if (countType > 1)
								lineForRecordInFile += stack.top() + ",";
							else
								lineForRecordInFile += stack.top();
							stack.pop();
						}
						lineForRecordInFile = reverseExpression(lineForRecordInFile);
						stack.push(lineForRecordInFile);
						continue;
						
					}

					stack.push(token);
				}
				lineForRecordInFile = "";
				while (!stack.empty()) 
				{
					lineForRecordInFile += stack.top() + " ";
					stack.pop();
				}
			}
		}
	
	}
	catch (const std::ifstream::failure & exep)
	{
		std::cout << " Exception opening/reading file";
		std::cout << exep.what();
		System::Windows::Forms::MessageBox::Show("File don't open", "error", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
	}
	fileAnalysis << "\t}\n}";
	rpn.close();
	fileAnalysis.close();

}