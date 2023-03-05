#include "Translator.h"

Translator::Translator()
{
}


Translator::~Translator()
{
}

bool Translator::isTypeDeclarationByCode(std::string code_type)
{
	return code_type == "W1" || code_type == "W2" || code_type == "W3" || code_type == "W14" || code_type == "W15" || code_type == "W16" || code_type == "W17" ||
		code_type == "W18" || code_type == "W19" || code_type == "W13" || code_type == "W19 W1"
		|| code_type == "W19 W2" || code_type == "W19 W3" || code_type == "W19 W17" || code_type == "W19 W18" || code_type == "W19 W16" || code_type == "W19 W15" ? true : false;
}
bool Translator::isTypeDeclaration(std::string type)
{
	return type == "int" || type == "float" || type == "char" || type == "const int" || type == "double" || type == "int*" || type == "double*" ||
		type == "float*" || type == "const" || type == "char*" || type == "const float"
		|| type == "const double" || type == "const char" || type == "const float*" || type == "const double*" 
		|| type == "const char*" || type == "const int*" ? true : false;
}
bool Translator::isConst(std::string const_type)
{
	return const_type == "const" ? true : false;
}
bool Translator::isCycle(std::string word)
{
	return word == "W7" || word == "W12" ? true : false;
}

bool Translator::isIFCondition(std::string word)
{
	return word == "W5" ? true : false;
}
bool Translator::isELSECondition(std::string word)
{
	return word == "W6" ? true : false;
}