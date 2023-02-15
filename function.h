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
bool isComment(int const& slash, int const& star);
bool isOneStringComment(int const& slash, int const& slash2);
bool isDigit(int const &);
bool isLetter(int const &);
bool isLibrary_header(std::string const &);
bool isNumber(std::string const& num);
#endif