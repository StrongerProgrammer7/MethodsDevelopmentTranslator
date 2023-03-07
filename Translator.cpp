#include "Translator.h"
#include "function.h"

Translator::Translator()
{
}


Translator::~Translator()
{
}

std::map<std::string, std::string> Translator::getIdentifier()
{
	return identifier;
}

std::map<std::string, std::string> Translator::getNumbers()
{
	return numberConst;
}

std::map<std::string, std::string> Translator::getSymbols()
{
	return symbolsConst;
}

void Translator::initialize(std::map<std::string, std::string> identifier, std::map<std::string, std::string> numberConst, std::map<std::string, std::string> symbolsConst)
{
	this->identifier = identifier;
	this->symbolsConst = symbolsConst;
	this->numberConst = numberConst;
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
	return const_type == "const" ? true : false;
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

std::string Translator::nameType(std::string token)
{
	bool isConst = false;
	if (token.length() > 3)
	{
		token.erase(0, 4);
		isConst = true;
	}
	for (int i = 0; i < SIZE_serviceWord; i++)
		if (serviceWord[i][1] == token)
			if (isConst ==true)
				return "const " + serviceWord[i][0];
			else
				return serviceWord[i][0];
	return "";
}


std::string Translator::fillTable(std::string str, std::map<std::string, std::string>& table, int numTable)
{
	/*int indexCode = 0;
	for (const auto& word : table)
	{
		indexCode++;
	}
	indexCode++;*/
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