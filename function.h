#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>

std::string getServiceWordCode(std::string);
std::string getOperationsCode(std::string str);
std::string getSeparatorsCode(std::string str);
std::string getIdentifierCode(std::string str);
std::string getNumberConstCode(std::string str);
std::string getSymbolsConstCode(std::string str);
#endif