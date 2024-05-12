#ifndef __PARSER__
#define __PARSER__
#include "ParsedData.h"

template <typename T>
class Parser {
	// Pure virtual function to overwrite for our specific parser
	virtual void Parse(const LPCWSTR& fileLocation, T& parsedData) = 0;
};
#endif
