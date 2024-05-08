#ifndef __PARSER__
#define __PARSER__
#include "ParsedData.h"
class Parser {
	// Pure virtual function to overwrite for our specific parser
	virtual void Parse(const LPCWSTR& fileLocation, ParsedData& parsedData) = 0;
};
#endif
