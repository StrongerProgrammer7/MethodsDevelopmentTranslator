#include "TranslatorFromCToCSharp.h"



TranslatorFromCToCSharp::TranslatorFromCToCSharp()
{
}

void TranslatorFromCToCSharp::makeTranslate(std::string source_file)
{
	makeLexicalAnalyze(source_file, "./translator_file/lexical.txt");
	reversePolishNotationAnalyze("./translator_file/lexical.txt", "./translator_file/RPN.txt");
	if(makeSyntaxAnalyze()==true)
		transalteToCSharp("./translator_file/RPN.txt", "./translator_file/CodeCSharp.cs");
}


TranslatorFromCToCSharp::~TranslatorFromCToCSharp()
{
}
