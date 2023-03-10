#include "Translator.h"
#include "function.h"

Translator::Translator()
{
}


Translator::~Translator()
{
}

System::String^ Translator::StlWStringToString(std::string const& os)
{
	System::String^ str = gcnew System::String(os.c_str());
	//String^ str = gcnew String("");
	return str;
}

void Translator::problemDetected(std::string problem)
{
	System::Windows::Forms::MessageBox::Show(StlWStringToString(problem), "Error", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
}

bool Translator::isTypeDeclarationByCode(std::string type_code)
{
	return type_code == "W1" || type_code == "W2" || type_code == "W3" || type_code == "W14" || type_code == "W15" || type_code == "W16" || type_code == "W17" ||
		type_code == "W18" || type_code == "W19" || type_code == "W13" || type_code == "W19 W1"
		|| type_code == "W19 W2" || type_code == "W19 W3" || type_code == "W19 W17" || type_code == "W19 W18" || type_code == "W19 W16" || type_code == "W19 W15" ? true : false;
}

bool Translator::isComment(int const& slash, int const& star)
{
	return slash == 47 && star == 42 ? true : false;
}
bool Translator::isOneStringComment(int const& slash, int const& slash2)
{
	return slash == 47 && slash2 == 47 ? true : false;
}
bool Translator::isConst(std::string const_type)
{
	return const_type == "const" || const_type == "W19" ? true : false;
}
bool Translator::isCycle(std::string word)
{
	return word == "W7" || word == "W12" ? true : false;
}

bool Translator::isIFCondition(std::string word_code)
{
	return word_code == "W5" ? true : false;
}
bool Translator::isELSECondition(std::string word_code)
{
	return word_code == "W6" ? true : false;
}

bool Translator::isInclude(std::string word_code)
{
	return word_code == "W8" ? true : false;
}

bool Translator::isOpenAnyBracket(std::string token)
{
	return token == "R3" || token == "R5" ? true : false;
}

bool Translator::isCloseAnyBracket(std::string token)
{
	return token == "R4" || token == "R6" ? true : false;
}

std::string Translator::nameType(std::string token)
{
	if (token.find("W19")!=std::string::npos)
		return "const " + getServiceWord(token.erase(0,4), false);
	else
		return getServiceWord(token, false);
}

std::string Translator::getServiceWord(std::string str,bool get_code)
{
	int number = get_code;
	for (int i = 0; i < SIZE_serviceWord; i++)
		if (serviceWord[i][!number] == str)
			return serviceWord[i][number];
	return "\0";
}

std::string Translator::getOperations(std::string str, bool get_code)
{
	int number = get_code;
	for (int i = 0; i < SIZE_operation; i++)
		if (operations[i][!number] == str)
			return operations[i][number];
	return "\0";
}
std::string Translator::getSeparators(std::string str, bool get_code)
{
	int number = get_code;
	for (int i = 0; i < SIZE_separators; i++)
		if (separators[i][!number] == str)
			return separators[i][number];
	return "\0";
}
std::string Translator::getNameByCode(std::map<std::string, std::string>& table, std::string code)
{
	for(const auto& item : table) 
		if (item.second == code)
			return item.first;
	return "\0";
}
std::string Translator::getCodeByName(std::map<std::string, std::string>& table,std::string str)
{
	for (const auto& word : table)
		if (word.first == str)
			return word.second;
	return "\0";
}

std::string Translator::fillTable(std::string str, std::map<std::string, std::string>& table, int numTable)
{
	if (numTable == 1)
	{
		if (isIdentifier(str) == true)
			identifier.insert(std::pair<std::string, std::string>(str, "I" + std::to_string(identifier.size())));
		else
			return "Error with identifier";
	}
	if (numTable == 2)
	{
		if (isNumber(str) == true)
			numberConst.insert(std::pair<std::string, std::string>(str, "N" + std::to_string(numberConst.size())));
		else
			return "Error with number";
	}
	if (numTable == 3)
		symbolsConst.insert(std::pair<std::string, std::string>(str, "C" + std::to_string(symbolsConst.size())));
	return "Success";
}