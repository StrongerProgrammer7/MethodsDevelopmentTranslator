#include "SyntaxAnalisator.h"
#include "function.h"

SyntaxAnalisator::SyntaxAnalisator()
{
}


SyntaxAnalisator::~SyntaxAnalisator()
{
}
string SyntaxAnalisator::getServiceWordCode(string str)
{
	for (int i = 0; i < SIZE_serviceWord; i++)
		if (serviceWord[i][0] == str)
			return serviceWord[i][1];
	return "\0";
}

string SyntaxAnalisator::getOperationsCode(string str)
{
	for (int i = 0; i < SIZE_operation; i++)
		if (operations[i][0] == str)
			return operations[i][1];
	return "\0";
}

string SyntaxAnalisator::getSeparatorsCode(string str)
{
	for (int i = 0; i < SIZE_separators; i++)
		if (separators[i][0] == str)
			return separators[i][1];
	return "\0";
}

string SyntaxAnalisator::getIdentifierCode(string str)
{
	for (const auto& word : identifier)
		if (word.first == str)
			return word.second;
	return "\0";
}

string SyntaxAnalisator::getNumberConstCode(string str)
{
	for (const auto& word : numberConst)
		if (word.first == str)
			return word.second;
	return "\0";
}

string SyntaxAnalisator::getSymbolsConstCode(string str)
{
	for (const auto& word : symbolsConst)
		if (word.first == str)
			return word.second;
	return "\0";
}

void SyntaxAnalisator::addCode(string str, map<string, string> & table, int numTable)
{
	int indexCode = 0;
	for (const auto& word : table)
	{
		indexCode++;
	}
	indexCode++;
	if (numTable == 1)
		table.insert(pair<string, string>(str, "I" + to_string(indexCode)));
	if (numTable == 2)
		table.insert(pair<string, string>(str, "N" + to_string(indexCode)));
	if (numTable == 3)
		table.insert(pair<string, string>(str, "C" + to_string(indexCode)));
}

int SyntaxAnalisator::checkStringSingleElem(string const& word)
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

string SyntaxAnalisator::getCodeWordLength_1(string word)
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


string SyntaxAnalisator::getCodeWordLengthGreaterOne(string word)
{
	string code = getServiceWordCode(word);
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

string SyntaxAnalisator::getCodeWord(string word)
{
	if (word.length() == 1)
		return getCodeWordLength_1(word);
	else
		return getCodeWordLengthGreaterOne(word);
}

void SyntaxAnalisator::analyze(string filePathOrName_C, string fileName_Path_SaveAnalis)
{
	ifstream fileC;
	ofstream fileAnalysis(fileName_Path_SaveAnalis);
	fileC.exceptions(ifstream::badbit);
	try
	{
		fileC.open(filePathOrName_C);

		if (fileC.is_open())
		{
			bool readComment = false;
			string temp = "";
			while (!fileC.eof())
			{
				string stringLanguageC = "";
				getline(fileC, stringLanguageC);
				for (unsigned int i = 0; i < stringLanguageC.length(); i++)
				{
					if (isServiceSymbols((int)stringLanguageC[i]) == true)
						continue;
					if (isComment((int)stringLanguageC[i], (int)stringLanguageC[i + 1]) == true)
						readComment = true;
					if (readComment == false && isOneStringComment((int)stringLanguageC[i], (int)stringLanguageC[i + 1]) == true)
					{
						string temp2 = "";
						temp2.assign(stringLanguageC, i, stringLanguageC.length() - i);
						fileAnalysis << temp2 << " ";
						break;
					}
					if (readComment == true && isComment((int)stringLanguageC[i + 1], (int)stringLanguageC[i]) == true)
					{
						readComment = false;
						temp += stringLanguageC[i];
						temp += stringLanguageC[i + 1];
						if (temp != "\0" && temp != "/**/")
							fileAnalysis << temp << " ";
						temp = "";
						i++;
						continue;
					}

					if (readComment == false)
					{
						if (isSeparators((int)stringLanguageC[i]) == true && temp[0] != '\"')
						{
							if (temp.length() != 0)
								fileAnalysis << getCodeWord(temp) << " ";
							temp = stringLanguageC[i];
							fileAnalysis << getCodeWord(temp) << " ";
							temp = "";
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
								temp.assign(stringLanguageC, i, countSymbols);
								if (temp.find(".h") != -1)
								{
									fileAnalysis << getCodeWord(temp) << " ";
									temp = "";
									if (stringLanguageC[posClose + 1] == '\0')
										break;
									else
										i = posClose;
								}
								else
								{
									if (temp[0] == '\"')
									{
										fileAnalysis << getCodeWord(temp) << " ";
										i = posClose + 1;

									}
								}
								temp = "";
							}
						}

						if (isOperation((int)stringLanguageC[i]) == true || isLogicalSingleOperation((int)stringLanguageC[i]) == true)
						{
							if (isIncrement((int)stringLanguageC[i], (int)stringLanguageC[i + 1]) == true ||
								isDoubleOperation((int)stringLanguageC[i], (int)stringLanguageC[i + 1] == true) ||
								isLogicalDoubleOperation((int)stringLanguageC[i], (int)stringLanguageC[i + 1]) == true)
							{
								temp += stringLanguageC[i];
								i++;
							}
							temp += stringLanguageC[i];
							fileAnalysis << getCodeWord(temp) << " ";
							temp = "";
							continue;
						}

						if (stringLanguageC[i] != ' ')
						{
							if (isLetter((int)stringLanguageC[i]) == true && (isLetter((int)stringLanguageC[i + 1]) == false && isDigit((int)stringLanguageC[i + 1]) == false))
							{

								temp += stringLanguageC[i];
								fileAnalysis << getCodeWord(temp) << " ";
								temp = "";
								continue;
							}
							else
							{
								if (stringLanguageC[i] == '#')
								{
									temp += stringLanguageC[i];
									continue;
								}

							}
							temp += stringLanguageC[i];
						}
						else
						{
							if (temp == "\0")
								continue;
							else
							{
								fileAnalysis << getCodeWord(temp) << " ";
								temp = "";
							}
						}
					}
					else
					{
						temp += stringLanguageC[i];
					}

				}
				if (temp != "\0")
				{
					if (readComment == false)
						fileAnalysis << getCodeWord(temp);
					else
						temp += '\n';
				}
				if (readComment == false)
					fileAnalysis << "\n";
			}
		}

	}
	catch (const ifstream::failure & exep)
	{
		cout << " Exception opening/reading file";
		cout << exep.what();
	}

	fileC.close();
	fileAnalysis.close();
}