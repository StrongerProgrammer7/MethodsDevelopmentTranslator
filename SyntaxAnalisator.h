#pragma once
#ifndef SYNTAXANALISATOR_H
#define SYNTAXANALISATOR_H

#include "Translator.h"

class SyntaxAnalisator : public Translator
{
public:
	SyntaxAnalisator();
	~SyntaxAnalisator();
	void analyze(std::string filePathOrName_C, std::string fileName_Path_SaveAnalis);
	void initialize();
private:
	std::string getServiceWordCode(std::string str);
	std::string getOperationsCode(std::string str);
	std::string getSeparatorsCode(std::string str);
	std::string getIdentifierCode(std::string str);
	std::string getNumberConstCode(std::string str);
	std::string getSymbolsConstCode(std::string str);
	void addCode(std::string str, std::map<std::string, std::string>& table, int numTable);
	int checkStringSingleElem(std::string const& word);
	std::string getCodeWordLength_1(std::string word);
	std::string getCodeWordLengthGreaterOne(std::string word);
	std::string getCodeWord(std::string word);
	bool skipAnalyzeComment(bool& readComment, std::string line, __int64& index, std::ofstream& file, std::string& word);
	bool skipAnalyzeOneLineComment(bool readComment, std::string line, __int64 index, std::ofstream& file);
	bool isLibrary_header(std::string const& word);
};
#endif
