#include "TranslatorFromCToCSharp.h"



TranslatorFromCToCSharp::TranslatorFromCToCSharp()
{
}

void TranslatorFromCToCSharp::makeTranslate(std::string source_file)
{
	makeSyntaxAnalyze(source_file, "./translator_file/lexical.txt");
	reversePolishNotationAnalyze("./translator_file/lexical.txt", "./translator_file/RPN.txt");
	transalteToCSharp("./translator_file/RPN.txt", "./translator_file/CodeCSharp.cs");
}


TranslatorFromCToCSharp::~TranslatorFromCToCSharp()
{
}
