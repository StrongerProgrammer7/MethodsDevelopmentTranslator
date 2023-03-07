#include "translate_csharp.h"
#include "function.h"


Translate_csharp::Translate_csharp()
{
}


Translate_csharp::~Translate_csharp()
{
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
	std::string declare = "\t\tstatic ";
	if(isSpaceInEndString(line))
		line.erase(line.rfind(" "), 1);
	while ((pos = line.find(' ')) != std::string::npos || line.length() != 0)
	{
		if (i == 2)
			break;
		declare += line.substr(0, pos) + " ";
		line.erase(0, pos + 1);
		i++;
	}

	declare += "(" + line + ")";
	declare.erase(declare.find("(") - 1, 1);
	return declare;

}
std::string Translate_csharp::declareFunctionExpression(std::string line,int countArg)
{
	line.erase(line.rfind(" "), 1);
	if (isSpaceInEndString(line))
		line.erase(line.rfind(" "), 1);
	std::string temp = line.substr(0, line.find(" "));
	line.erase(0, line.find(" ") + 1);
	temp += "(";
	if (countArg > 2)
		while (line.length() != 0)
			if (line.find(" ") != std::string::npos)
			{
				temp += line.substr(0, line.find(" ")) + ",";
				line.erase(0, line.find(" ") + 1);
			}
			else
				break;
	temp += line + ")";
	
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
	if (nameCondition == "for")
		return correctCycleFor(nameCondition + "(" + line + ")");
	else
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

std::string Translate_csharp::replaceCodeToName(std::string line,char const& name)
{
	std::string toReplace = "";
	if (name != 'W' && name != 'I' && name != 'N' && name != 'C')
		return line;

	size_t pos = 0, posEnd = 0;
	pos = line.find(name);
	posEnd = line.find(" ", pos);
	toReplace = line.substr(pos, posEnd);
	std::string num = "";
	if (name == 'I')
		num = getNameByCode(identifier, toReplace);
	else
		if (name == 'W')
			num = getServiceWord(toReplace,false);
		else
			if (name == 'N')
				num = getNameByCode(numberConst, toReplace);
			else
				num = getNameByCode(symbolsConst, toReplace);
	if(num!="")
		line.replace(pos, toReplace.length(), num);
	return line;
}

void replacePercentAtTheCurclyBracketWithNum(std::string& print)
{
	int num = 0;
	do
	{
		size_t pos = 0;
		pos = print.find("%d");
		if (pos == std::string::npos)
			pos = print.find("%f");
		if (pos == std::string::npos)
			break;
		print.replace(pos, 2, "{" + std::to_string(num) + "}");
		num++;
	} while (true);
}

std::string Translate_csharp::replaceCodeToName(std::string line)
{
	size_t pos = 0;
	std::string line_name = "";
	if (line.find("printf") == std::string::npos)
	{
		while ((pos = line.find(' ')) != std::string::npos || line.length() != 0)
		{
			std::string token = "";
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
			line_name += replaceCodeToName(token, token[0]) + " ";
		}
		return line_name;
	}
	else
	{
		line_name = "Console.WriteLine(";
		line.erase(0, line.find("(") + 1);
		for (int i = 0; i < line.length() - 1; i++)
		{
			if (line[i] == ',' || isSeparators(line[i])==true)
				line_name += line[i];
			if ((line[i] == 'N' || line[i] == 'C' || line[i] == 'W' || line[i] == 'I') && isLetter((int)line[i + 1]) == false)
			{
				for (int j = i + 1; j < line.length() - 1; j++)
				{
					if (line[j] == ' ' || isLetter(line[j]) )
						break;
					if (isSeparators(line[j]))
						line_name += line[j];
					if (isDigit(line[j]) && (isDigit(line[j + 1]) || line[j + 1] == ' ' || line[j+1] == ',' || isSeparators(line[j+1])))
					{
						int count = 1;
						if (isDigit(line[j + 1]))
						{
							j++;
							count++;
						}
						std::string temp = line.substr(i, count+1);
						line_name += replaceCodeToName(temp,temp[0]);
						
					}
					i = j;
				}
			}
			replacePercentAtTheCurclyBracketWithNum(line_name);
		}
		line_name += ")";
		return line_name;
	}
}


std::string Translate_csharp::replaceMalloc(std::string const& line)
{
	std::string temp = "",type="";
	bool declareArray = false;
	size_t begin = line.find("*") + 1;
	nameArrayForReturn = line.substr(begin, line.find("=") - 1 - begin);
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] != '*')
			temp += line[i];
		if (line[i] == '*')
			if (type != "")
				break;
			else
			{
				type = temp;
				temp += "[]";
			}
		if (line[i] == '=')
		{
			i = line.find("malloc") + 6;
			temp += " new " + type + "[";
			declareArray = false;
		}
	}
	temp.erase(temp.rfind(" "), 1);
	temp += "] ";
	return temp;
}

void Translate_csharp::replaceTypeToTypeArrayFunction(std::string& block_function)
{
	size_t pos = block_function.find(" ") + 1;
	pos = block_function.find(" ", pos);
	std::string tempSeparator = "[] ", tempStar = "*";
	block_function.replace(pos, tempStar.length(), tempSeparator);
	nameArrayForReturn = "";
	std::string temp = block_function.substr(0, block_function.find("(") + 1);
	pos = temp.rfind("(");
	size_t posEnd = temp.rfind(" ", pos) + 1;
	nameFunctionReturnArray = temp.substr(posEnd, pos - posEnd);
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
		bool isPrint = false;
		std::string block_function = "";
		nameArrayForReturn = "";
		nameFunctionReturnArray = "";
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
					lineRPN = replaceCodeToName(lineRPN);
					fileAnalysis << "\t\t//" + lineRPN + "\n";
					continue;
				}
				if (lineRPN.find("W4") != std::string::npos)
				{
					block_function += "\t\tstatic void Main(string[] args)\n\t\t{\n";
					mainFunctionRecorded = true;
					continue;
				}
				if (lineRPN.find("W20") != std::string::npos)
				{
					if (lineForRecordInFile.length() != 0)
					{
						lineForRecordInFile.erase(lineForRecordInFile.rfind(" "), 1);
						block_function += "\t\t\t" + lineForRecordInFile + ";\n";
						lineForRecordInFile = "";
					}
					continue;
				}
				
				if (lineRPN.find("W11") != std::string::npos)
				{
					if (lineForRecordInFile.length() != 0)
					{
						lineForRecordInFile.erase(lineForRecordInFile.rfind(" "), 1);
						block_function += "\t\t\t" + lineForRecordInFile + ";\n";
						lineForRecordInFile = "";
					}
					if (mainFunctionRecorded == true)
					{
						block_function += "\n";
						continue;
					}
					lineRPN = reverseExpression(lineRPN);
					lineRPN = replaceCodeToName(lineRPN);
					lineRPN.erase(lineRPN.rfind(" "), 1);
					if (nameArrayForReturn!= "" && lineRPN.find(nameArrayForReturn) != std::string::npos)
						replaceTypeToTypeArrayFunction(block_function);

					block_function += "\t\t\t" + lineRPN + ";\n";
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
					fileAnalysis << lineRPN << std::endl;
					if (lineRPN.find("*/") != std::string::npos)
						manyLineComment = false;
					continue;
				}

				if (lineRPN.find("ÍÏ") != std::string::npos)
				{
					if (mainFunctionRecorded == true)
						continue;
					lineForRecordInFile = reverseExpression(lineForRecordInFile);
					lineForRecordInFile = declareFunction(lineForRecordInFile);
					block_function += lineForRecordInFile + "\n\t\t{\n";
					lineForRecordInFile = "";
					continue;
				}
				else
				{
					if (lineRPN == "ÊÏ")
					{
						block_function += "\t\t}\n";
						fileAnalysis << block_function;
						lineForRecordInFile = "";
						if (mainFunctionRecorded == true)
							mainFunctionRecorded = false;
						block_function = "";
						nameArrayForReturn = "";
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
									lineForRecordInFile = declareCondition(lineForRecordInFile, "for");
								else
									lineForRecordInFile = declareCondition(lineForRecordInFile, "if");

							block_function += "\t\t\t" + lineForRecordInFile + "\n\t\t\t{\n";
							lineForRecordInFile = "";
							continue;
							
						}
						if (lineRPN.find("ÀÝÌ") == std::string::npos)
						{
							if (isPrint == false)
								lineForRecordInFile = reverseExpression(lineForRecordInFile);
							else
								isPrint = false;

							if (lineForRecordInFile.find("malloc") != std::string::npos)
								lineForRecordInFile = replaceMalloc(lineForRecordInFile);

							if (lineForRecordInFile != "")
								block_function += "\t\t\t\t" + lineForRecordInFile + ";\n";

							lineForRecordInFile = "";
							block_function += "\t\t\t}\n";

							continue;
						}
						
					}
					else
					{
						if (lineForRecordInFile.length() != 0)
						{
							if (isPrint == false)
								lineForRecordInFile = reverseExpression(lineForRecordInFile);
							else
								isPrint = false;
							if (lineForRecordInFile.find("malloc") != std::string::npos)
								lineForRecordInFile = replaceMalloc(lineForRecordInFile);
								
							lineForRecordInFile.erase(lineForRecordInFile.rfind(" "), 1);
							block_function += "\t\t\t" + lineForRecordInFile + ";\n";
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

					if(isPrint==false)
						token = replaceCodeToName(token,token[0]);
					if (token.find("printf") != std::string::npos)
						isPrint = true;

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
						lineForRecordInFile = declareFunctionExpression(lineForRecordInFile,countArg);
						if (isPrint == true)
							lineForRecordInFile = replaceCodeToName(lineForRecordInFile);
						stack.push(lineForRecordInFile);
						continue;
					}
					if (token.find("O") != std::string::npos)
					{
						lineForRecordInFile = stack.top();
						
						if (getOperations(token,false) == "++" || getOperations(token,false) == "--")
						{
							lineForRecordInFile += getOperations(token,false) + " ";
							lineForRecordInFile = reverseExpression(lineForRecordInFile);
						}
						else
						{
							lineForRecordInFile += " ";
							lineForRecordInFile += getOperations(token,false) + " ";
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
						if (stack.top() == "sizeof")
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
				if (nameFunctionReturnArray != "" && lineForRecordInFile.find(nameFunctionReturnArray) != std::string::npos)
				{
					size_t pos = lineForRecordInFile.rfind("*");
					lineForRecordInFile.replace(pos, 1, "[]");
				}
			}
			if(block_function!="")
				fileAnalysis << block_function;
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
