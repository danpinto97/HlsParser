#ifndef __PARSED_DATA__
#define __PARSED_DATA__
#include <vector>
#include "HlsTypes.h"

// Parsed Data class
class ParsedData {
private:
	std::vector<std::unique_ptr<VideoType>> m_videoVector;
	std::vector<std::unique_ptr<ImageType>> m_imageVector;
	std::vector<std::unique_ptr<AudioType>> m_audioVector;
public:
	ParsedData();
	~ParsedData() = default;
	void AppendVideo(std::unique_ptr<VideoType>);
	void AppendImage(std::unique_ptr<ImageType>);
	void AppendAudio(std::unique_ptr<AudioType>);
	

	const std::vector<std::unique_ptr<VideoType>>& GetVideoVector();
	const std::vector<std::unique_ptr<AudioType>>& GetAudioVector();
	const std::vector<std::unique_ptr<ImageType>>& GetImageVector();
	void SortVideoOnBandWidth();
	
};


#endif
