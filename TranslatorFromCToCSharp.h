#pragma once
#include "translate_csharp.h"
class TranslatorFromCToCSharp :	public Translate_csharp
{
public:
	TranslatorFromCToCSharp();
	~TranslatorFromCToCSharp();
	void lexicalAnalyze(std::string source_file);
	void reversePolishNotAnalyze();
	void translateToCSharp();
	bool syntaxAnalyze();
private:
	bool lexicalAnalyzeIsCompleted = false;
	bool reversePolishNotationIsCompleted = false;
	bool syntaxAnalyzeIsCompleted = false;
};

