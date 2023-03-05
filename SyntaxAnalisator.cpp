#include "Translator_LanguageC.h"
#include "SyntaxAnalisator.h"
#include "function.h"

SyntaxAnalisator::SyntaxAnalisator()
{
}


SyntaxAnalisator::~SyntaxAnalisator()
{
}

System::String^ StlWStringToString(std::string const& os)
{
	System::String^ str = gcnew System::String(os.c_str());
	//String^ str = gcnew String("");
	return str;
}

std::string SyntaxAnalisator::getServiceWordCode(std::string str)
{
	for (int i = 0; i < SIZE_serviceWord; i++)
		if (serviceWord[i][0] == str)
			return serviceWord[i][1];
	return "\0";
}

std::string SyntaxAnalisator::getOperationsCode(std::string str)
{
	for (int i = 0; i < SIZE_operation; i++)
		if (operations[i][0] == str)
			return operations[i][1];
	return "\0";
}

std::string SyntaxAnalisator::getSeparatorsCode(std::string str)
{
	for (int i = 0; i < SIZE_separators; i++)
		if (separators[i][0] == str)
			return separators[i][1];
	return "\0";
}

std::string SyntaxAnalisator::getIdentifierCode(std::string str)
{
	for (const auto& word : identifier)
		if (word.first == str)
			return word.second;
	return "\0";
}

std::string SyntaxAnalisator::getNumberConstCode(std::string str)
{
	for (const auto& word : numberConst)
		if (word.first == str)
			return word.second;
	return "\0";
}

std::string SyntaxAnalisator::getSymbolsConstCode(std::string str)
{
	for (const auto& word : symbolsConst)
		if (word.first == str)
			return word.second;
	return "\0";
}


void SyntaxAnalisator::addCode(std::string str, std::map<std::string, std::string> & table, int numTable)
{
	int indexCode = 0;
	for (const auto& word : table)
	{
		indexCode++;
	}
	indexCode++;
	if (numTable == 1)
	{
		if(isIdentifier(str)==true)
			table.insert(std::pair<std::string, std::string>(str, "I" + std::to_string(indexCode)));
		else
		{
			
			System::String^ temp = StlWStringToString(str);
			System::Windows::Forms::MessageBox::Show("Error with identifier", temp, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
			return;
		}
	}
	if (numTable == 2)
	{
		if(isNumber(str)==true)
			table.insert(std::pair<std::string, std::string>(str, "N" + std::to_string(indexCode)));
		else
		{
			System::String^ temp = StlWStringToString(str);
			System::Windows::Forms::MessageBox::Show("Error with number", temp, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
			return;
		}
	}
	if (numTable == 3)
		table.insert(std::pair<std::string, std::string>(str, "C" + std::to_string(indexCode)));
}

int SyntaxAnalisator::checkStringSingleElem(std::string const& word)
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

std::string SyntaxAnalisator::getCodeWordLength_1(std::string word)
{
	switch (checkStringSingleElem(word))
	{
	case 1:
		if (getNumberConstCode(word) == "\0")
			addCode(word, numberConst, 2);
		return getNumberConstCode(word);
	case 2:
		return getOperationsCode(word);
	case 3:
		return getSeparatorsCode(word);
	case 4:
		if (getIdentifierCode(word) == "\0")
			addCode(word, identifier, 1);
		return getIdentifierCode(word);
	default:
		return "";
	}
}


std::string SyntaxAnalisator::getCodeWordLengthGreaterOne(std::string word)
{
	std::string code = getServiceWordCode(word);
	if (code == "\0")
		code = getOperationsCode(word);
	if (code == "\0")
	{
		if (isNumber(word) == true)
		{
			if (getNumberConstCode(word) == "\0")
				addCode(word, numberConst, 2);
			return getNumberConstCode(word);
		}
		else
		{
			if ((int)word[0] == 34)// \"
			{
				if (isLibrary_header(word) == false)
				{
					if (getSymbolsConstCode(word) == "\0")
						addCode(word, symbolsConst, 3);
					return getSymbolsConstCode(word);
				}
			}
			if (getIdentifierCode(word) == "\0")
				addCode(word, identifier, 1);
			return getIdentifierCode(word);
		}
	}
	else
		return code;
}

std::string SyntaxAnalisator::getCodeWord(std::string word)
{
	if (word.length() == 1)
		return getCodeWordLength_1(word);
	else
		return getCodeWordLengthGreaterOne(word);
}

bool SyntaxAnalisator::skipAnalyzeOneLineComment(bool readComment, std::string line, __int64 index,std::ofstream& file)
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

bool skipAnalyzeComment(bool& readComment, std::string line, __int64& index, std::ofstream& file, std::string& word)
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


void SyntaxAnalisator::analyze(std::string filePathOrName_C, std::string fileName_Path_SaveAnalis)
{
	std::ifstream fileC;
	std::ofstream fileAnalysis(fileName_Path_SaveAnalis);
	fileC.exceptions(std::ifstream::badbit);
	try
	{
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
							fileAnalysis << getCodeWord(word) << " ";
							word = "";
							continue;
						}

						if (stringLanguageC[i] != ' ')
						{
							if (isLetter((int)stringLanguageC[i]) == true && (isLetter((int)stringLanguageC[i + 1]) == false && isDigit((int)stringLanguageC[i + 1]) == false))
							{
								word += stringLanguageC[i];
								if (isType(word) && (stringLanguageC[i + 1] == '*' || stringLanguageC[i + 2] == '*'))
								{
									word += '*';
									if (stringLanguageC[i + 2] == '*')
										i += 2;
									else
										i++;
								}
								fileAnalysis << getCodeWord(word) << " ";
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