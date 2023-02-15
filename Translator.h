#pragma once
#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "include.h"

class Translator
{
public:
	Translator();
	~Translator();
protected:
#define SIZE_serviceWord 11
#define SIZE_separators 9
#define SIZE_operation 20
#define SIZE_columns 2
	string const serviceWord[SIZE_serviceWord][SIZE_columns] =
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
		{"return","W11"}
	};
	string const separators[SIZE_separators][SIZE_columns] =
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
	string const operations[SIZE_operation][SIZE_columns] =
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
};

#endif