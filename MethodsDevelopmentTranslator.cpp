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

bool isSeparators(int elem)
{
	return elem == 40 || elem == 41 || elem == 91 || elem == 93 || elem == 123 || elem == 125 || elem == 59 ? true : false;
}

//\t\a\b...
bool isServiceSymbols(int elem)
{
	return elem == 7 || elem == 8 || elem == 9 || elem == 10 || elem == 11 || elem == 12 || elem == 13 ? true : false;
}

int main()
{
	ifstream fileC;
	ofstream fileAnalysis("lexical.txt");
	fileC.exceptions(ifstream::badbit);
	try
	{
		fileC.open("C.txt");

		if (fileC.is_open())
		{
			while (!fileC.eof())
			{
				string stringC = "";
				string temp = "";
				getline(fileC, stringC);
				for (int i = 0; i < stringC.length(); i++)
				{
					if (isServiceSymbols((int)stringC[i]) == true)
						continue;
							
					if (isSeparators((int)stringC[i]) == true && temp[0] != '\"')
					{
						if (temp.length() != 0)
							fileAnalysis << getCodeWord(temp) << " ";
						temp = stringC[i];
						fileAnalysis << getCodeWord(temp) << " ";
						temp = "";
						continue;
					}
					
					// <library.h>
					if (stringC[i] == '<' || stringC[i] == '\"')
					{
						int posClose = 0;
						int countSymbols = 0;
						if (stringC[i] == '<')
						{
							posClose = stringC.find(">", 1);
							if (posClose != -1)
							{
								countSymbols = stringC.length() - i;
								temp.assign(stringC, i, countSymbols);
							}
							
						}
						else
						{
							posClose = stringC.rfind('\"');
							if (posClose != -1)
							{
								countSymbols = posClose+1 - i;
								temp.assign(stringC, i, countSymbols);
							}
							
						}						
						if (temp.find(".h") != -1)
						{
							fileAnalysis << getCodeWord(temp) << " ";
							temp = "";
							
						}
						else
						{
							if (temp[0] == '\"')
							{
								if (temp != "" && (int)temp[temp.length() - 2] != 92)
								{
									fileAnalysis << getCodeWord(temp) << " ";
								}
							}
							else
							{
								string temp2 = "";
								temp2 += stringC[i];
								fileAnalysis << getCodeWord(temp2) << " ";
							}

							temp = "";
							if (stringC[posClose + 1] == '\0')
								break;
							else
								i = posClose;
							continue;
						}
					}
					
					if (stringC[i] != ' ')
					{
						if (isLetter((int)stringC[i]) == true && (isLetter((int)stringC[i+1])==false && isDigit((int)stringC[i+1])==false))
						{
							if (temp[0] == '\"')
							{
								if (stringC[i] == '\"' && stringC[i + 1] == ' ' && stringC[i + 1] == '\0')
								{
									temp += stringC[i];
									fileAnalysis << getCodeWord(temp) << " ";
									temp = "";
									continue;
								}
								else
								{
									temp += stringC[i];
									continue;
								}
							}
							else
							{
								temp += stringC[i];
								fileAnalysis << getCodeWord(temp) << " ";
								temp = "";
								continue;
							}
						}
						else
						{
							if (stringC[i] == '#')
							{
								temp += stringC[i];
								continue;
							}
							
						}
						temp += stringC[i];
					}
					else
					{
						if (stringC[i] == ' ' && temp == "\0")
							continue;
						else
							if (stringC[i] == ' ')
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