#ifndef __HLSPARSER__
#define __HLSPARSER__

#include "HlsTypes.h"
#include "Parser.h"
#include <fstream> 
#include <iostream> 
#include <string> 
#include <vector>
#include "ParsedData.h"

class HlsParser : Parser<ParsedData> {
public:
	HlsParser();
	~HlsParser();
	void Parse(const LPCWSTR& fileLocation, ParsedData& parsedData);
	std::unique_ptr<VideoType> ParseVideoLine(const std::string &line, const std::string &newLine);
	std::unique_ptr<ImageType> ParseImageLine(const std::string &line);
	std::unique_ptr<AudioType> ParseAudioLine(const std::string &line);
	
};
#endif
