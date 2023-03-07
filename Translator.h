#pragma once
#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "include.h"

class Translator
{
public:
	Translator();
	~Translator();
	virtual std::map<std::string, std::string> getIdentifier();
	virtual std::map<std::string, std::string> getNumbers();
	virtual std::map<std::string, std::string> getSymbols();
	virtual void initialize(std::map<std::string, std::string> identifier, std::map<std::string, std::string> numberConst, std::map<std::string, std::string> symbolsConst);
protected:
#define SIZE_serviceWord 19
#define SIZE_separators 9
#define SIZE_operation 20
#define SIZE_columns 2
	std::string const serviceWord[SIZE_serviceWord][SIZE_columns] =
	{
		{"int","W1"},
		{"float","W2"},
		{"char","W3"},
		{"main","W4"},
		{"if","W5"},
		{"else","W6"},
		{"while","W7"},
		{"#include","W8"},
		{"malloc","W9"},
		{"sizeof","W10"},
		{"return","W11"},
		{"for","W12"},
		{"void","W13"},
		{"double","W14"},
		{"int*","W15"},
		{"float*","W16"},
		{"double*","W17"},
		{"char*","W18"},
		{"const","W19"}
	};
	std::string const separators[SIZE_separators][SIZE_columns] =
	{
		{"[","R1"},
		{"]","R2"},
		{"(","R3"},
		{")","R4"},
		{"{","R5"},
		{"}","R6"},
		{";","R7"},
		{",","R8"},
		//{"*","R9"},
		{"","R9"}
	};
	std::string const operations[SIZE_operation][SIZE_columns] =
	{
		{"+","O1"},
		{"-","O2"},
		{"*","O3"},
		{"/","O4"},
		{"=","O5"},
		{"%","O6"},
		{">","O7"},
		{"<","O8"},
		{"==","O9"},
		{"!=","O10"},
		{">=","O11"},
		{"<=","O12"},
		{"/=","O13"},
		{"+=","O14"},
		{"-=","O15"},
		{"*=","O16"},
		{"&&","O17"},
		{"||","O18"},
		{"--","O19"},
		{"++","O20"}
	};
	std::map<std::string, std::string> identifier;
	std::map<std::string, std::string> numberConst;
	std::map<std::string, std::string> symbolsConst;
	std::map<std::string, int> priority =
	{
		// if		(			[		ÀÝÌ			Ô		while			for
		{"W5",0}, { "R3",0 },{ "R1",0 },{ "ÀÝÌ",0 },{ "Ô",0 },{"W7", 0},{"W12", 0},
		// {		,			;			)		]			else
		{"R5", 1},{ "R8",1 },{ "R7",1 },{ "R4",1 },{"R2", 1},{"W6", 1},{":",1},
		// =
		{"O5", 2},
		// |
		{"|", 3},
		// &
		{"&", 4},
		// not		  &&		||
		{"not", 5}, {"O17", 5},{"O18", 5},
		// <		>		  <=			>=		==			!=		 
		{"O8", 6},{"O7", 6},{"O12", 6},{"O11", 6},{"O9", 6},{"O10", 6},
		//+			-			++		--		-=			+=			*=		/=
		{"O1", 7},{"O2", 7},{"O20", 7},{"O19", 7},{"O15", 7},{"O14", 7},{"O16", 7},{"O13", 7},
		//*			/		%
		{"O3", 8},{"O4", 8},{"O6", 8},
		// }			return
		{"R6", 9},{"W11", 9},{"DCL",9}
	};

	bool isTypeDeclarationByCode(std::string code_type);
	bool isComment(int const& slash, int const& star);
	bool isOneStringComment(int const& slash, int const& slash2);
	bool isCycle(std::string word);
	bool isIFCondition(std::string word);
	bool isELSECondition(std::string word);
	bool isConst(std::string const_type);
	std::string nameType(std::string token);
	std::string Translator::fillTable(std::string str, std::map<std::string, std::string>& table, int numTable);
};

#endif