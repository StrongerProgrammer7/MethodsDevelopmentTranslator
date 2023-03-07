#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>

bool isSeparators(int const &);
bool isServiceSymbols(int const &elem);
bool isOperation(int const& elem);
bool isLogicalSingleOperation(int const& elem);
bool isLogicalDoubleOperation(int const& elem, int const& nextElem);
bool isIncrement(int const& elem, int const& nextElem);
bool isDoubleOperation(int const& elem, int const& nextElem);
bool isDigit(int const &);
bool isLetter(int const &);
bool isLibrary_header(std::string const &);
bool isNumber(std::string const& num);
bool isTypeDeclaration(std::string type);
bool isIdentifier(std::string const& word);
std::string intToStrWithSpace(int num);
bool isSpaceInEndString(std::string line);
#endif