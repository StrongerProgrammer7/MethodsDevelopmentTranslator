#include "function.h"

using namespace std;

//Translator from C to C#
/*
	C - input language, include
	Identificator - any seq symbols and digit, begin with word(include _)
	Number const int unsigned
	Number const float #123.45, .25, 25.
	Number const double # 1.23e-25, 1.23E+25 , 1.23e2
	Symbols const: 'char', "string"
	Index: name[12][i][i+1]
	Comment: /*, // to end string
	Users function: F(args)
	Arifmetic operation: +,-,*,/
	Comparison operations: < > == != <= >=
	Assignment operator: =
	Block operator: { .. }
	Based function: int main() { return 0;}
	Type: int,float,char
	Array: arr[size];
	# int a,b,d[3][4];
	IF block: if() { } else {}
	Cycle: while() {..}
*/

int main(int argc, char* argv[])
{
	ifstream fileC;
	ofstream fileAnalysis("C:\\Users\\swat5\\source\\repos\\StrongerProgrammer7\\MethodsDevelopmentTranslator\\lexical.txt");
	fileC.exceptions(ifstream::badbit);
	try
	{
		fileC.open("C:\\Users\\swat5\\source\\repos\\StrongerProgrammer7\\MethodsDevelopmentTranslator\\C.txt");

		if (fileC.is_open())
		{
			while (!fileC.eof())
			{
				string stringLanguageC = "";
				string temp = "";
				getline(fileC, stringLanguageC);
				for (unsigned int i = 0; i < stringLanguageC.length(); i++)
				{
					if (isServiceSymbols((int)stringLanguageC[i]) == true)
						continue;
							
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
									i = posClose;

								}
							}
							temp = "";
							//continue;
						}
					}

					if (isOperation(stringLanguageC, i) == true || isLogicalOperation(stringLanguageC, i) == true)
					{
						if (isIncrement(stringLanguageC, i) == true || isDoubleOperation(stringLanguageC, i) == true)
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
						if (isLetter((int)stringLanguageC[i]) == true && (isLetter((int)stringLanguageC[i+1])==false && isDigit((int)stringLanguageC[i+1])==false))
						{
							/*if (temp[0] == '\"')
							{
								if (stringLanguageC[i] == '\"' && stringLanguageC[i + 1] == ' ' && stringLanguageC[i + 1] == '\0')
								{
									temp += stringLanguageC[i];
									fileAnalysis << getCodeWord(temp) << " ";
									temp = "";
									continue;
								}
								else
								{
									temp += stringLanguageC[i];
									continue;
								}
							}
							else
							{*/
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
				if (temp != "\0")
				{
					fileAnalysis << getCodeWord(temp);
				}
				fileAnalysis << "\n";
			}
		}

	}
	catch (const ifstream::failure& exep)
	{
		cout << " Exception opening/reading file";
	}

	fileC.close();
	fileAnalysis.close();

	return 0;
}


/*
bool isPointer(string word, int index)
{
	if (word[index] == '*' && isLetter((int)word[index - 1]) == true && isLetter((int)word[index + 1]) == false && isDigit((int)word[index + 1]) == false && isSeparators((int)word[index+1])==false)
		return true;
	int pos = 0;
	pos = word.find("=", 1);
	string temp = "";
	temp.assign(word, index + 1, pos - index);
	return word.find("+") == -1 && word.find("-") == -1 && word.find("*") == -1 && word.find("/") == -1 && word.find("+") == -1 ? true : false;
}*/
/*if (i != 0 && stringC[i]=='*')
						if (isPointer(stringC, i) == true)
						{
							fileAnalysis << getCodeWord("p*") << " ";
							continue;
						}*/