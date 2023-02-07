#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H
#include "include.h"

bool isSeparators(int const &);
bool isServiceSymbols(int const &elem);
bool isOperation(string const &str, int const &ind);
bool isLogicalOperation(string const& str, int const& ind);
bool isIncrement(string const& str, int const& ind);
bool isDoubleOperation(string const& str, int const& ind);
bool isDigit(int const &);
bool isLetter(int const &);
bool isLibrary_header(string const &);
string getServiceWordCode(string);
string getOperationsCode(string str);
string getSeparatorsCode(string str);
string getIdentifierCode(string str);
string getNumberConstCode(string str);
string getSymbolsConstCode(string str);
string getCodeWord(string );
#endif