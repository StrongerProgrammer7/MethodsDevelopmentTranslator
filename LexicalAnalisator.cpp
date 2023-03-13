#include "Translator_LanguageC.h"
#include "LexicalAnalisator.h"
#include "function.h"

LexicalAnalisator::LexicalAnalisator()
{
}


LexicalAnalisator::~LexicalAnalisator()
{
}

bool isEqual = false;

void LexicalAnalisator::addCode(std::string str, std::map<std::string, std::string>& table, int numTable)
{
	std::string result = fillTable(str, table, numTable);
	if (result.find("Error") != std::string::npos)
	{
		System::String^ temp = StlWStringToString(str);
		System::String^ tempResult = StlWStringToString(result);
		System::Windows::Forms::MessageBox::Show(tempResult, temp, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
	}
}

int LexicalAnalisator::checkStringSingleElem(std::string const& word)
{
	if (isDigit((int)word[0]) == true)
		return 1;
	if (isOperation((int)word[0]) == true || isLogicalSingleOperation((int)word[0]) == true)
		return 2;
	if (isSeparators((int)word[0]) == true)
		return 3;
	if (isLetter((int)word[0]) == true)
		return 4;
	return 0;
}

std::string LexicalAnalisator::getCodeWordLength_1(std::string word)
{
	switch (checkStringSingleElem(word))
	{
	case 1:
		if (getCodeByName(numberConst,word) == "\0")
			addCode(word, numberConst, 2);
		return getCodeByName(numberConst, word);
	case 2:
		return getOperations(word,true);
	case 3:
		return getSeparators(word,true);
	case 4:
		if (getCodeByName(identifier, word) == "\0")
		{
			if (isEqual == false)
				addCode(word, identifier, 1);
			else
			{
				problemDetected("Expected known identifier!");
				return "error!";
			}
		}
		return getCodeByName(identifier, word);
	default:
		return "";
	}
}


std::string LexicalAnalisator::getCodeWordLengthGreaterOne(std::string word)
{
	std::string code = getServiceWord(word,true);
	if (code == "\0")
		code = getOperations(word,true);
	if (code == "\0")
	{
		if (isNumber(word) == true)
		{
			if (getCodeByName(numberConst, word) == "\0")
				addCode(word, numberConst, 2);
			return getCodeByName(numberConst, word);
		}
		else
		{
			if ((int)word[0] == 34)// \"
			{
				if (isLibrary_header(word) == false)
				{
					if (getCodeByName(symbolsConst, word) == "\0")
						addCode(word, symbolsConst, 3);
					return getCodeByName(symbolsConst, word);
				}
			}
			if (getCodeByName(identifier, word) == "\0")
			{
				if(isEqual == false)
					addCode(word, identifier, 1);
				else
				{
					problemDetected("Expected known identifier!");
					return "error!";
				}
			}
			return getCodeByName(identifier, word);
		}
	}
	else
		return code;
}

std::string LexicalAnalisator::getCodeWord(std::string word)
{
	if (word.length() == 1)
	{
		std::string temp = getCodeWordLength_1(word);
		if (temp == "R7")
			isEqual = false;
		return temp;
	}
	else
		return getCodeWordLengthGreaterOne(word);
}

bool LexicalAnalisator::skipAnalyzeOneLineComment(bool readComment, std::string line, __int64 index,std::ofstream& file)
{
	if (readComment == false && isOneStringComment((int)line[index], (int)line[index + 1]) == true)
	{
		std::string oneLineComment = "";
		oneLineComment.assign(line, index, line.length() - index);
		file << oneLineComment << " ";
		return true;
	}
	return false;
}

bool LexicalAnalisator::skipAnalyzeComment(bool& readComment, std::string line, __int64& index, std::ofstream& file, std::string& word)
{
	if (readComment == true && isComment((int)line[index + 1], (int)line[index]) == true)
	{
		readComment = false;
		word += line[index];
		word += line[index + 1];
		if (word != "\0" && word != "")
			file << word << " ";
		word = "";
		index++;
		return true;
	}
	return false;
}
bool LexicalAnalisator::isLibrary_header(std::string const& word)
{
	return (int)word[0] == 34 && (int)word[word.length() - 1] == 34 && (int)word[word.length() - 2] == 104 && (int)word[word.length() - 3] == 46 ? true : false;
}

void LexicalAnalisator::makeLexicalAnalyze(std::string filePathOrName_C, std::string fileName_Path_SaveAnalis)
{
	std::ifstream fileC;
	std::ofstream fileAnalysis(fileName_Path_SaveAnalis);
	fileC.exceptions(std::ifstream::badbit);
	try
	{
		isEqual = false;
		fileC.open(filePathOrName_C);
		if (fileC.is_open())
		{
			bool readComment = false;
			std::string word = "";
			while (!fileC.eof())
			{
				std::string stringLanguageC = "";
				getline(fileC, stringLanguageC);
				for (__int64 i = 0; i < stringLanguageC.length(); i++)
				{
					if (isServiceSymbols((int)stringLanguageC[i]) == true)
						continue;
					if (isComment((int)stringLanguageC[i], (int)stringLanguageC[i + 1]) == true)
						readComment = true;
					if (skipAnalyzeOneLineComment(readComment,stringLanguageC,i,fileAnalysis)==true)
						break;

					if (skipAnalyzeComment(readComment, stringLanguageC, i, fileAnalysis,word))
						continue;

					if (readComment == false)
					{
						if (isSeparators((int)stringLanguageC[i]) == true && word[0] != '\"')
						{
							if (word.length() != 0)
								fileAnalysis << getCodeWord(word) << " ";
							word = stringLanguageC[i];
							fileAnalysis << getCodeWord(word) << " ";
							word = "";
							continue;
						}

						// <library.h> and "string"
						if (stringLanguageC[i] == '<' || stringLanguageC[i] == '\"')
						{
							int posClose = 0;
							int countSymbols = 0;
							if (stringLanguageC[i] == '<')
								posClose = stringLanguageC.find(">", 1);
							else
								posClose = stringLanguageC.rfind('\"');

							if (posClose != -1)
							{
								countSymbols = posClose + 1 - i;
								word.assign(stringLanguageC, i, countSymbols);
								if (word.find(".h") != -1)
								{
									fileAnalysis << getCodeWord(word) << " ";
									word = "";
									if (stringLanguageC[static_cast<__int64>(posClose) + 1] == '\0')
										break;
									else
										i = posClose;
								}
								else
								{
									if (word[0] == '\"')
									{
										fileAnalysis << getCodeWord(word) << " ";
										i = static_cast<__int64>(posClose) + 1;

									}
								}
								word = "";
							}
						}

						if (isOperation((int)stringLanguageC[i]) == true || isLogicalSingleOperation((int)stringLanguageC[i]) == true)
						{
							if (isIncrement((int)stringLanguageC[i], (int)stringLanguageC[i + 1]) == true ||
								isDoubleOperation((int)stringLanguageC[i], (int)stringLanguageC[i + 1]) == true ||
								isLogicalDoubleOperation((int)stringLanguageC[i], (int)stringLanguageC[i + 1]) == true)
							{
								word += stringLanguageC[i];
								i++;
							}
							word += stringLanguageC[i];
							if (word == "=")
								isEqual = true;
							fileAnalysis << getCodeWord(word) << " ";
							word = "";
							continue;
						}

						if (stringLanguageC[i] != ' ')
						{
							if (isLetter((int)stringLanguageC[i]) == true && (isLetter((int)stringLanguageC[i + 1]) == false && isDigit((int)stringLanguageC[i + 1]) == false))
							{
								word += stringLanguageC[i];
								if (isTypeDeclaration(word) && (stringLanguageC[i + 1] == '*' || stringLanguageC[i + 2] == '*'))
								{
									word += '*';
									if (stringLanguageC[i + 2] == '*')
										i += 2;
									else
										i++;
								}
								std::string check_err = getCodeWord(word);
								if (check_err.find("error!")!=std::string::npos)
									return;


								fileAnalysis << check_err << " ";
								word = "";
								continue;
							}
							else
							{
								if (stringLanguageC[i] == '#')
								{
									word += stringLanguageC[i];
									continue;
								}

							}
							word += stringLanguageC[i];
						}
						else
						{
							if (word == "\0")
								continue;
							else
							{
								fileAnalysis << getCodeWord(word) << " ";
								word = "";
							}
						}
					}
					else
					{
						word += stringLanguageC[i];
					}

				}
				if (word != "\0")
				{
					if (readComment == false)
						fileAnalysis << getCodeWord(word);
					else
						word += '\n';
				}
				if (readComment == false)
					fileAnalysis << "\n";
			}
		}

	}
	catch (const std::ifstream::failure & exep)
	{
		std::cout << " Exception opening/reading file";
		std::cout << exep.what();
		System::Windows::Forms::MessageBox::Show("File don't open", "error", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
	}

	fileC.close();
	fileAnalysis.close();
}



