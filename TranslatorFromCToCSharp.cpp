#include "TranslatorFromCToCSharp.h"
using namespace System;

TranslatorFromCToCSharp::TranslatorFromCToCSharp()
{
}

TranslatorFromCToCSharp::~TranslatorFromCToCSharp()
{
}

//System::String^ StlWStringToString(std::string const& os)
//{
//	System::String^ str = gcnew System::String(os.c_str());
//	//String^ str = gcnew String("");
//	return str;
//}

void TranslatorFromCToCSharp::lexicalAnalyze(std::string source_file)
{
	
	try
	{
		makeLexicalAnalyze(source_file, "./translator_file/lexical.txt");
		lexicalAnalyzeIsCompleted = true;
	}
	catch (const std::exception&)
	{
		System::Windows::Forms::MessageBox::Show("Problem with lexical analyze", "Error", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
		lexicalAnalyzeIsCompleted = false;
	}
	
}

void TranslatorFromCToCSharp::reversePolishNotAnalyze()
{
	try
	{
		if (lexicalAnalyzeIsCompleted == true)
			reversePolishNotationAnalyze("./translator_file/lexical.txt", "./translator_file/RPN.txt");
		else
		{
			System::Windows::Forms::MessageBox::Show("LexicalAnaylyze don't completed!", "Error", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
			return;
		}
			
		reversePolishNotationIsCompleted = true;
	}
	catch (const std::exception&)
	{
		System::Windows::Forms::MessageBox::Show("Problem with RPN analyze", "Error", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
		reversePolishNotationIsCompleted = false;
	}
}

bool TranslatorFromCToCSharp::syntaxAnalyze()
{
	try
	{
		syntaxAnalyzeIsCompleted = makeSyntaxAnalyze();
		return syntaxAnalyzeIsCompleted;
	}
	catch (const std::exception&)
	{
		System::Windows::Forms::MessageBox::Show("Problem with syntax analyze!", "Error", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
		syntaxAnalyzeIsCompleted = false;
	}
}

void TranslatorFromCToCSharp::translateToCSharp()
{
	try
	{
		if (reversePolishNotationIsCompleted == true && syntaxAnalyzeIsCompleted == true)
		{
			transalteToCSharp("./translator_file/RPN.txt", "./translator_file/CodeCSharp.cs");
		}
		else
		{
			System::Windows::Forms::MessageBox::Show("Don't execution RPN || syntax analyze!", "Error", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
			return;
		}
	}
	catch (std::string err)
	{
		System::Windows::Forms::MessageBox::Show("Problem with translate to C# program!" + StlWStringToString(err), "Error", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
	}
	
}