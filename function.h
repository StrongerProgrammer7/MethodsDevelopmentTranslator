#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H
#include "include.h"

bool isDigit(char);
bool isLetter(char);
string getServiceWordCode(string);
string getOperationsCode(string str);
string getSeparatorsCode(string str);
string getIdentifierCode(string str);
string getNumberConstCode(string str);
string getSymbolsConstCode(string str);
#endif