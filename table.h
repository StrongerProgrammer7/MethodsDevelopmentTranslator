#pragma once
#ifndef TABLE_H
#define TABLE_H

#include "include.h"

#define SIZE_serviceWord 8
#define SIZE_separators 10
#define SIZE_operation 12
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
	{"return","W8"}
};

string const operations[SIZE_operation][SIZE_columns] =
{
	{"+","O1"},
	{"-","O2"},
	{"*","O3"},
	{"/","O4"},
	{"=","O5"},
	{">","O6"},
	{"<","O7"},
	{"==","O8"},
	{"!=","O9"},
	{">=","O10"},
	{"<=","O11"},
	{"++","O12"}
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
	{".","R8"},
	{"*","R9"},
	{"","R10"}
};

map<string, string> identifier;
map<string, string> numberConst;
map<string, string> symbolsConst;


#endif