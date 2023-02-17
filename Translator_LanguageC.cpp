#include "Translator_LanguageC.h"
#include "function.h"
#include "SyntaxAnalisator.h"
#include "ReversePolishNotation.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;
std::string fileText_C = "";

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
	}
	try
	{
		StreamReader^ file = File::OpenText(filePathName);
		tb_textC->Text = file->ReadToEnd();
		file->Close();
		marshalString(filePathName, fileText_C);
		btn_analisator->Enabled = true;
	}
	catch (const std::exception&)
	{
		MessageBox::Show(this, "File don't open", "error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

}

bool isExtensionTXT(String^ line)
{
	return line->EndsWith(".txt") ? true : false;
}

System::Void MethodsDevelopmentTranslator::Translator_LanguageC::Btn_analisator_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (tb_nameFileAnylize->Text != "" && isExtensionTXT(tb_nameFileAnylize->Text)==true)
	{
		SyntaxAnalisator analisator;
		std::string fileName = "";
		marshalString(tb_nameFileAnylize->Text, fileName);
		analisator.analyze(fileText_C, fileName);

		StreamReader^ fileAnalyze = File::OpenText(tb_nameFileAnylize->Text);
		tb_syntaxAnalisator->Text = fileAnalyze->ReadToEnd();
		fileAnalyze->Close();
		btn_analisator->Enabled = false;
	}
	else
	{
		MessageBox::Show(this, "Write to file name! Or error to extension file, (.txt uses)", "error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	
}

System::Void MethodsDevelopmentTranslator::Translator_LanguageC::Btn_reversePolishNotation_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}
