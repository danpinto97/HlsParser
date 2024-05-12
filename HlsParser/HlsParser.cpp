// HlsParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "FileLoader.h"
#include "HlsParser.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include "ParsedData.h"
#include <unordered_map>
// Parser Destructor
HlsParser::~HlsParser() {}

// Parser constructor
HlsParser::HlsParser() {}

// Helps to find the key in the string and cut out the corresponding value to return. If value is quoted, pass quoted as true. Defaults to false.
static std::string FinderHelper(const std::string& line, const std::string& target, bool quoted = false) {
	unsigned start = line.find(target); // Find where we need to start
	std::string newLine = line.substr(start + target.length(), line.length()); // cut out the "target" key
	unsigned end;
	if (quoted)
		end = newLine.find("\""); // Find next quotation mark
	else
		end = newLine.find(","); // Find next comma
	return newLine.substr(0, end); // Grab from the start to the quotation mark or comma
}

// Parsing function for Audio Lines
std::unique_ptr<AudioType> HlsParser::ParseAudioLine(const std::string &line) {
	std::string id = FinderHelper(line, "ID=\"", true);
	std::string name = FinderHelper(line, "NAME=\"", true);
	std::string language = FinderHelper(line, "LANGUAGE=\"", true);
	std::string def = FinderHelper(line, "DEFAULT=");
	std::string autoSelect = FinderHelper(line, "AUTOSELECT=");
	std::string channels = FinderHelper(line, "CHANNELS=\"", true);
	std::string uri = FinderHelper(line, "URI=\"", true);

	// Create the new audio type and push it back onto our list
	std::unique_ptr<AudioType> audioType = std::make_unique<AudioType>(id,name,language,def,autoSelect,channels,uri);
	// Compiler should try to automatically "move" this if possible
	return audioType;
}

// Parsing function for Image Lines
std::unique_ptr<ImageType> HlsParser::ParseImageLine(const std::string& line) {
	uint32_t bandwidth = std::stoi(FinderHelper(line, "BANDWIDTH="));
	std::string codecs = FinderHelper(line, "CODECS=\"", true);
	std::string resolution = FinderHelper(line, "RESOLUTION=");
	std::string videoRange = FinderHelper(line, "VIDEO-RANGE=");
	std::string uri = FinderHelper(line, "URI=\"", true);

	// Create the new image type and push it back onto our list
	std::unique_ptr<ImageType> imageType = std::make_unique<ImageType>(bandwidth, codecs, resolution, videoRange, uri);
	return imageType;
}

// Parsing function for Video Lines 
std::unique_ptr<VideoType> HlsParser::ParseVideoLine(const std::string& line, const std::string& nextLine) {
	uint32_t bandwidth = std::stoi(FinderHelper(line, "BANDWIDTH="));
	uint32_t averageBandwidth = std::stoi(FinderHelper(line, "AVERAGE-BANDWIDTH="));
	std::string codecs = FinderHelper(line, "CODECS=\"", true);
	std::string resolution = FinderHelper(line, "RESOLUTION=");
	double frameRate = std::stod(FinderHelper(line, "FRAME-RATE="));
	std::string videoRange = FinderHelper(line, "VIDEO-RANGE=");
	std::string audio = FinderHelper(line, "AUDIO=\"", true);
	std::string closedCaptions = FinderHelper(line, "CLOSED-CAPTIONS=");
	
	// Create the new video type and push it back onto our list
	std::unique_ptr<VideoType> videoType = std::make_unique<VideoType>(bandwidth, averageBandwidth, codecs, resolution, frameRate, videoRange, audio, closedCaptions, nextLine);
	return videoType;
}

// For printing out any vector of HlsType
template <typename T>
static void PrintHlsType(const std::vector<T> &hlsVector) {
	for (const auto& data : hlsVector) {
		data->Print();
	}
}

// Takes in file to Parse, and data structure (by ref) to fill data out for
void HlsParser::Parse(const LPCWSTR& fileLocation, ParsedData& parsedData){
	std::string line;
	std::ifstream hlsFile(fileLocation);
	if (hlsFile.is_open())
	{
		// Iterate over lines of file
		while (std::getline(hlsFile, line))
		{
			std::string delimiter = ":";
			std::string token = line.substr(0, line.find(delimiter));
			// Check what type of media we have
			// Could be switch
			// Could implement map to function pointers
			if (token == "#EXT-X-MEDIA") {
				// Audio
				parsedData.AppendAudio(ParseAudioLine(line));
			}
			else if (token == "#EXT-X-STREAM-INF") {
				// Video
				// Need to get attachment too
				std::string nextLine; 
				std::getline(hlsFile, nextLine);
				parsedData.AppendVideo(ParseVideoLine(line, nextLine));
			}
			else if (token == "#EXT-X-I-FRAME-STREAM-INF") {
				// Image
				parsedData.AppendImage( ParseImageLine(line));
			}
		}
		hlsFile.close();
	}

	else std::cout << "Unable to open file";
}

// Typedefs for string->sorting fxn map
typedef void (ParsedData::*sorting_method)(void);
typedef std::unordered_map<std::string, sorting_method> sorting_map;

static void BuildSortingMap(sorting_map& m) {
	// Video Sorters
	m["video:bandwidth:asc"] = &ParsedData::SortVideoOnBandWidthAsc;
	m["video:bandwidth:desc"] = &ParsedData::SortVideoOnBandWidthDesc;
	m["video:avgbandwidth:asc"] = &ParsedData::SortVideoOnAvgBandWidthAsc;
	m["video:avgbandwidth:desc"] = &ParsedData::SortVideoOnAvgBandWidthDesc;
	m["video:framerate:asc"] = &ParsedData::SortVideoOnFrameRateAsc;
	m["video:framerate:desc"] = &ParsedData::SortVideoOnFrameRateDesc;
	m["image:bandwidth:asc"] = &ParsedData::SortImageOnBandWidthAsc;
	m["image:bandwidth:desc"] = &ParsedData::SortImageOnBandWidthDesc;
	m["audio:language:asc"] = &ParsedData::SortAudioOnLanguageAsc;
	m["audio:language:desc"] = &ParsedData::SortAudioOnLanguageDesc;
	m["audio:name:asc"] = &ParsedData::SortAudioOnNameAsc;
	m["audio:name:desc"] = &ParsedData::SortAudioOnNameDesc;
	m["audio:group:asc"] = &ParsedData::SortAudioOnGroupAsc;
	m["audio:group:desc"] = &ParsedData::SortAudioOnGroupDesc;
}


int main()
{
	// Set up our url and destination
	// Maybe in the future this could pull from user input or json/xml file
	LPCWSTR url = L"https://lw.bamgrid.com/2.0/hls/vod/bam/ms02/hls/dplus/bao/master_unenc_hdr10_all.m3u8";
	LPCWSTR destination = L".\\dl.txt";

	// Create the file downloader with this url and destination
	FileLoader fileLoader(url, destination);
	
	// Download the file
	bool downloaded = fileLoader.DownloadFile();
	
	if (!downloaded)
	{
		std::cout << "File failed to download, double check URL and destination.\nExiting!\n";
		exit(0);
	}
	// Initialize parsed data
	ParsedData parsedData;

	// Initialize parser
	HlsParser hlsParser;

	// Actually parse data and store in our ParsedData object
	hlsParser.Parse(destination, parsedData);

	std::cout << "Data downloaded and parsed.\n";
	std::string userInput;

	// Declare unordered map of string to functions
	sorting_map m;
	BuildSortingMap(m);

	// Main loop for user input
	while(true) {
		std::cout << "How would you like to sort ? Enter e to exit.\n";
		std::cin >> userInput;
		// If e exit
		if (userInput == "e")
			break;
		else {
			// Otherwise try to lookup function
			sorting_map::iterator it = m.find(userInput);
			if (it != m.end()) {
				// Call corresponding sorting function
				(parsedData.*(it->second))();
				// Don't like this at all, would rather also have string->fxn map or something
				if (userInput[0] == 'v')
					PrintHlsType(parsedData.GetVideoVector());
				else if (userInput[0] == 'i')
					PrintHlsType(parsedData.GetImageVector());
				else if (userInput[0] == 'a')
					PrintHlsType(parsedData.GetAudioVector());
			}
			else
				std::cout << "Sorry, unsupported command.\n";
		}
	} 
	
	return 0;
    
}
