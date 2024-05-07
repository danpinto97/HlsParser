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

////////////////////////////////////////////////////////////////////////////////////
// Sorts for video vectors
// Sort video vector by bandwidth
// Could operator overload
void ParsedData::SortVideoOnBandWidthAsc() {
	// std::sort is nlogn
	std::sort(m_videoVector.begin(), m_videoVector.end(), [](const std::unique_ptr<VideoType>& lhs, const std::unique_ptr<VideoType>& rhs) {
		return lhs->GetBandwidth() < rhs->GetBandwidth();
	});
}

void ParsedData::SortVideoOnBandWidthDesc() {
	std::sort(m_videoVector.begin(), m_videoVector.end(), [](const std::unique_ptr<VideoType>& lhs, const std::unique_ptr<VideoType>& rhs) {
		return lhs->GetBandwidth() > rhs->GetBandwidth();
		});
}

void ParsedData::SortVideoOnAvgBandWidthAsc() {
	std::sort(m_videoVector.begin(), m_videoVector.end(), [](const std::unique_ptr<VideoType>& lhs, const std::unique_ptr<VideoType>& rhs) {
		return lhs->GetBandwidth() < rhs->GetBandwidth();
		});
}

void ParsedData::SortVideoOnAvgBandWidthDesc() {
	std::sort(m_videoVector.begin(), m_videoVector.end(), [](const std::unique_ptr<VideoType>& lhs, const std::unique_ptr<VideoType>& rhs) {
		return lhs->GetBandwidth() > rhs->GetBandwidth();
		});
}

void ParsedData::SortVideoOnFrameRateAsc() {
	std::sort(m_videoVector.begin(), m_videoVector.end(), [](const std::unique_ptr<VideoType>& lhs, const std::unique_ptr<VideoType>& rhs) {
		return lhs->GetFrameRate() < rhs->GetFrameRate();
		});
}

void ParsedData::SortVideoOnFrameRateDesc() {
	std::sort(m_videoVector.begin(), m_videoVector.end(), [](const std::unique_ptr<VideoType>& lhs, const std::unique_ptr<VideoType>& rhs) {
		return lhs->GetFrameRate() > rhs->GetFrameRate();
		});
}
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// Sorts for image vectors
void ParsedData::SortImageOnBandWidthAsc() {
	// std::sort is nlogn
	std::sort(m_imageVector.begin(), m_imageVector.end(), [](const std::unique_ptr<ImageType>& lhs, const std::unique_ptr<ImageType>& rhs) {
		return lhs->GetBandwidth() < rhs->GetBandwidth();
		});
}

void ParsedData::SortImageOnBandWidthDesc() {
	std::sort(m_imageVector.begin(), m_imageVector.end(), [](const std::unique_ptr<ImageType>& lhs, const std::unique_ptr<ImageType>& rhs) {
		return lhs->GetBandwidth() > rhs->GetBandwidth();
		});
}
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// Sorts for audio vectors
void ParsedData::SortAudioOnLanguageAsc() {
	std::sort(m_audioVector.begin(), m_audioVector.end(), [](const std::unique_ptr<AudioType>& lhs, const std::unique_ptr<AudioType>& rhs) {
		return lhs->GetLanguage() < rhs->GetLanguage();
		});
}

void ParsedData::SortAudioOnLanguageDesc() {
	std::sort(m_audioVector.begin(), m_audioVector.end(), [](const std::unique_ptr<AudioType>& lhs, const std::unique_ptr<AudioType>& rhs) {
		return lhs->GetLanguage() > rhs->GetLanguage();
		});
}

void ParsedData::SortAudioOnNameAsc() {
	std::sort(m_audioVector.begin(), m_audioVector.end(), [](const std::unique_ptr<AudioType>& lhs, const std::unique_ptr<AudioType>& rhs) {
		return lhs->GetName() < rhs->GetName();
		});
}

void ParsedData::SortAudioOnNameDesc() {
	std::sort(m_audioVector.begin(), m_audioVector.end(), [](const std::unique_ptr<AudioType>& lhs, const std::unique_ptr<AudioType>& rhs) {
		return lhs->GetName() > rhs->GetName();
		});
}

void ParsedData::SortAudioOnGroupAsc() {
	std::sort(m_audioVector.begin(), m_audioVector.end(), [](const std::unique_ptr<AudioType>& lhs, const std::unique_ptr<AudioType>& rhs) {
		return lhs->GetGroupID() < rhs->GetGroupID();
		});
}
void ParsedData::SortAudioOnGroupDesc() {
	std::sort(m_audioVector.begin(), m_audioVector.end(), [](const std::unique_ptr<AudioType>& lhs, const std::unique_ptr<AudioType>& rhs) {
		return lhs->GetGroupID() > rhs->GetGroupID();
		});
}
////////////////////////////////////////////////////////////////////////////////////

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
	return this->m_imageVector;
}
