#include "ReversePolishNotation.h"
#include "function.h"

ReversePolishNotation::ReversePolishNotation()
{
}
ReversePolishNotation::~ReversePolishNotation()
{
}

void ReversePolishNotation::reversePolishNotationAnalyze(std::string filePathOrName_C, std::string fileName_Path_SaveAnalis)
{

}

int ReversePolishNotation::getPriority(std::string word)
{
	//priority
	for (auto& item : priority)
	{
		if (item.first == word)
			return item.second;
	}
	return -1;
}
}
