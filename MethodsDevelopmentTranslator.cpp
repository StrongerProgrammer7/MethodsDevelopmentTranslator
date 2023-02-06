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


int main()
{
	ifstream fileC;
	ofstream fileAnalysis;
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
				for (int i = 0; i < stringC.length()-1; i++)
				{
					if (i != 0 && stringC[i] == '*' && isLetter((int)stringC[i - 1]) == true)
						fileAnalysis << getCodeWord(stringC[i-1]+"*");
					if (stringC[i] != ' ')
					{
						if (isLetter((int)stringC[i]) == true && (isLetter((int)stringC[i+1])==false || isDigit((int)stringC[i+1])==false))
						{
							temp += stringC[i];
							fileAnalysis << getCodeWord(temp) << " ";
							temp = "";
							continue;
						}
						else
						{
							if(stringC[0] == '#')
								temp += stringC[i];
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

