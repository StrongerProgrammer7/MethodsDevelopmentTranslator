#include "Translator_LanguageC.h"
#include "function.h"
#include "TranslatorFromCToCSharp.h"
#include <direct.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;

std::string fileText_C = "";
TranslatorFromCToCSharp translator;

[STAThreadAttribute]
void main(array<String^>^ args)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	MethodsDevelopmentTranslator::Translator_LanguageC form;
	Application::Run(% form);
}

void marshalString(String^ s, std::string& std_string)
{
	using namespace Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	std_string = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}


System::Void MethodsDevelopmentTranslator::Translator_LanguageC::Btn_loadFile_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ filePathName = "";
	if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
	{
		filePathName = openFileDialog1->FileName;
		try
		{	
			StreamReader^ file = File::OpenText(filePathName);
			tb_textC->Text = file->ReadToEnd();
			file->Close();
			marshalString(filePathName, fileText_C);
			btn_analisator->Enabled = true;
			mkdir("translator_file");
		}
		catch (const std::exception&)
		{
			MessageBox::Show(this, "File don't open", "error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}

bool isExtensionTXT(String^ line)
{
	return line->EndsWith(".txt") ? true : false;
}

System::Void MethodsDevelopmentTranslator::Translator_LanguageC::Btn_analisator_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*std::string fileName = "";
	marshalString(tb_nameFileAnylize->Text, fileName);*/
	translator.lexicalAnalyze(fileText_C);
	StreamReader^ fileAnalyze = File::OpenText("./translator_file/lexical.txt");
	tb_syntaxAnalisator->Text = fileAnalyze->ReadToEnd();
	fileAnalyze->Close();
	btn_analisator->Enabled = false;
	btn_reversePolishNotation->Enabled = true;
}

System::Void MethodsDevelopmentTranslator::Translator_LanguageC::Btn_reversePolishNotation_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*std::string file = "";
	marshalString(tb_nameFileAnylize->Text, file);*/
	translator.reversePolishNotAnalyze();
	StreamReader^ fileAnalyze = gcnew StreamReader("./translator_file/RPN.txt", System::Text::Encoding::GetEncoding(1251));
	tb_reversePolishNotation->Text = fileAnalyze->ReadToEnd();
	fileAnalyze->Close();
	btn_reversePolishNotation->Enabled = false;
	btn_syntax_analisator->Enabled = true;
}

System::Void MethodsDevelopmentTranslator::Translator_LanguageC::Btn_toCSharp_Click(System::Object^ sender, System::EventArgs^ e)
{
	translator.translateToCSharp();
	StreamReader^ fileAnalyze = gcnew StreamReader("./translator_file/CodeCSharp.cs", System::Text::Encoding::GetEncoding(1251));
	tb_codeCSharp->Text = fileAnalyze->ReadToEnd();
	fileAnalyze->Close();
	btn_toCSharp->Enabled = false;

}

System::Void MethodsDevelopmentTranslator::Translator_LanguageC::Btn_syntax_analisator_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (translator.syntaxAnalyze() == true)
	{
		MessageBox::Show("No problem", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
		btn_syntax_analisator->Enabled = false;
		btn_toCSharp->Enabled = true;
	}
	else
	{
		tb_reversePolishNotation->Text = "";
		tb_syntaxAnalisator->Text = "";
		btn_syntax_analisator->Enabled = false;
		btn_toCSharp->Enabled = false;
	}
		
}