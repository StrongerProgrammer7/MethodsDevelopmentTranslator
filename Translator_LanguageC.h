#pragma once

namespace MethodsDevelopmentTranslator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// ������ ��� Translator_LanguageC
	/// </summary>
	public ref class Translator_LanguageC : public System::Windows::Forms::Form
	{
	public:
		Translator_LanguageC(void)
		{
			InitializeComponent();
			btn_analisator->Enabled = false;
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~Translator_LanguageC()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btn_loadFile;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::TextBox^ tb_textC;
	private: System::Windows::Forms::Button^ btn_analisator;
	private: System::Windows::Forms::TextBox^ tb_syntaxAnalisator;
	private: System::Windows::Forms::TextBox^ tb_nameFileAnylize;
	private: System::Windows::Forms::TextBox^ tb_reversePolishNotation;
	private: System::Windows::Forms::Button^ btn_reversePolishNotation;

	protected:

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btn_loadFile = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->tb_textC = (gcnew System::Windows::Forms::TextBox());
			this->btn_analisator = (gcnew System::Windows::Forms::Button());
			this->tb_syntaxAnalisator = (gcnew System::Windows::Forms::TextBox());
			this->tb_nameFileAnylize = (gcnew System::Windows::Forms::TextBox());
			this->tb_reversePolishNotation = (gcnew System::Windows::Forms::TextBox());
			this->btn_reversePolishNotation = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btn_loadFile
			// 
			this->btn_loadFile->Location = System::Drawing::Point(13, 13);
			this->btn_loadFile->Name = L"btn_loadFile";
			this->btn_loadFile->Size = System::Drawing::Size(208, 23);
			this->btn_loadFile->TabIndex = 0;
			this->btn_loadFile->Text = L"Load file";
			this->btn_loadFile->UseVisualStyleBackColor = true;
			this->btn_loadFile->Click += gcnew System::EventHandler(this, &Translator_LanguageC::Btn_loadFile_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// tb_textC
			// 
			this->tb_textC->BackColor = System::Drawing::SystemColors::Info;
			this->tb_textC->Location = System::Drawing::Point(13, 43);
			this->tb_textC->Multiline = true;
			this->tb_textC->Name = L"tb_textC";
			this->tb_textC->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tb_textC->Size = System::Drawing::Size(208, 393);
			this->tb_textC->TabIndex = 1;
			// 
			// btn_analisator
			// 
			this->btn_analisator->Location = System::Drawing::Point(228, 13);
			this->btn_analisator->Name = L"btn_analisator";
			this->btn_analisator->Size = System::Drawing::Size(208, 23);
			this->btn_analisator->TabIndex = 2;
			this->btn_analisator->Text = L"Syntax analisator";
			this->btn_analisator->UseVisualStyleBackColor = true;
			this->btn_analisator->Click += gcnew System::EventHandler(this, &Translator_LanguageC::Btn_analisator_Click);
			// 
			// tb_syntaxAnalisator
			// 
			this->tb_syntaxAnalisator->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->tb_syntaxAnalisator->Location = System::Drawing::Point(228, 73);
			this->tb_syntaxAnalisator->Multiline = true;
			this->tb_syntaxAnalisator->Name = L"tb_syntaxAnalisator";
			this->tb_syntaxAnalisator->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tb_syntaxAnalisator->Size = System::Drawing::Size(208, 362);
			this->tb_syntaxAnalisator->TabIndex = 3;
			// 
			// tb_nameFileAnylize
			// 
			this->tb_nameFileAnylize->BackColor = System::Drawing::Color::OldLace;
			this->tb_nameFileAnylize->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tb_nameFileAnylize->Location = System::Drawing::Point(228, 43);
			this->tb_nameFileAnylize->MaxLength = 2000;
			this->tb_nameFileAnylize->Name = L"tb_nameFileAnylize";
			this->tb_nameFileAnylize->Size = System::Drawing::Size(208, 22);
			this->tb_nameFileAnylize->TabIndex = 4;
			this->tb_nameFileAnylize->Text = L"lexical.txt";
			this->tb_nameFileAnylize->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// tb_reversePolishNotation
			// 
			this->tb_reversePolishNotation->BackColor = System::Drawing::Color::Bisque;
			this->tb_reversePolishNotation->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->tb_reversePolishNotation->Location = System::Drawing::Point(442, 42);
			this->tb_reversePolishNotation->Multiline = true;
			this->tb_reversePolishNotation->Name = L"tb_reversePolishNotation";
			this->tb_reversePolishNotation->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tb_reversePolishNotation->Size = System::Drawing::Size(208, 393);
			this->tb_reversePolishNotation->TabIndex = 5;
			// 
			// btn_reversePolishNotation
			// 
			this->btn_reversePolishNotation->Location = System::Drawing::Point(442, 13);
			this->btn_reversePolishNotation->Name = L"btn_reversePolishNotation";
			this->btn_reversePolishNotation->Size = System::Drawing::Size(208, 23);
			this->btn_reversePolishNotation->TabIndex = 6;
			this->btn_reversePolishNotation->Text = L"Reverse Polish notation";
			this->btn_reversePolishNotation->UseVisualStyleBackColor = true;
			this->btn_reversePolishNotation->Click += gcnew System::EventHandler(this, &Translator_LanguageC::Btn_reversePolishNotation_Click);
			// 
			// Translator_LanguageC
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->BackColor = System::Drawing::Color::MintCream;
			this->ClientSize = System::Drawing::Size(807, 452);
			this->Controls->Add(this->btn_reversePolishNotation);
			this->Controls->Add(this->tb_reversePolishNotation);
			this->Controls->Add(this->tb_nameFileAnylize);
			this->Controls->Add(this->tb_syntaxAnalisator);
			this->Controls->Add(this->btn_analisator);
			this->Controls->Add(this->tb_textC);
			this->Controls->Add(this->btn_loadFile);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"Translator_LanguageC";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Translator";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Btn_loadFile_Click(System::Object^ sender, System::EventArgs^ e);
			 System::Void Btn_analisator_Click(System::Object^ sender, System::EventArgs^ e);
			 System::Void Btn_reversePolishNotation_Click(System::Object^ sender, System::EventArgs^ e);
};
}
