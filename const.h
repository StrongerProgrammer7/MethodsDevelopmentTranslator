#pragma once
#include <iostream>
#define SIZE_serviceWord 8
#define SIZE_separators 9
#define SIZE_operation 11
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
	{"return","W8"}
};

std::string const operations[SIZE_operation][SIZE_columns] =
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
	{"<=","O11"}
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
	{".","R8"},
	{"","R9"}
};