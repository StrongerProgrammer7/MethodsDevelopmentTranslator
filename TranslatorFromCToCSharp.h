#pragma once
#include "translate_csharp.h"
class TranslatorFromCToCSharp :	public Translate_csharp
{
public:
	TranslatorFromCToCSharp();
	~TranslatorFromCToCSharp();
	void makeTranslate(std::string source_file);
private:
	
};

