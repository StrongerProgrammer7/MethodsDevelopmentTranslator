#pragma once
#ifndef SYNTAXANALISATOR_H
#define SYNTAXANALISATOR_H

#include "Translator.h"

class LexicalAnalisator : public Translator
{
public:
	LexicalAnalisator();
protected:
	void makeLexicalAnalyze(std::string from_file_C, std::string to_file_lexical);
	~LexicalAnalisator();
private:
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
