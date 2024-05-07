#include "ParsedData.h"
#include <algorithm>

// ParsedData constructor
ParsedData::ParsedData() :
	m_videoVector(),
	m_imageVector(),
	m_audioVector() {}

// Append to video vector
void ParsedData::AppendVideo(std::unique_ptr<VideoType> videoType) {
	m_videoVector.push_back(std::move(videoType));
}

// Sort video vector by bandwidth
// Could operator overload
void ParsedData::SortVideoOnBandWidth() {
	// std::sort is nlogn
	std::sort(m_videoVector.begin(), m_videoVector.end(), [](const std::unique_ptr<VideoType>& lhs, const std::unique_ptr<VideoType>& rhs) {
		return lhs->GetBandwidth() < rhs->GetBandwidth();
	});
}

// Append to image vector 
void ParsedData::AppendImage(std::unique_ptr<ImageType> imageType) {
	m_imageVector.push_back(std::move(imageType));
}

// Append to audio vector
void ParsedData::AppendAudio(std::unique_ptr<AudioType> audioType) {
	m_audioVector.push_back(std::move(audioType));
}

// Getters for all vectors
 const std::vector<std::unique_ptr<VideoType>>& ParsedData::GetVideoVector() {
	return this->m_videoVector;
}
 
const std::vector<std::unique_ptr<AudioType>>& ParsedData::GetAudioVector() {
	return this->m_audioVector;
}
const std::vector<std::unique_ptr<ImageType>>& ParsedData::GetImageVector() {
	//return this->m_audioVector;
}
