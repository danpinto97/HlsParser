#include "HlsTypes.h"

// Constructor for base class
HlsType::HlsType(std::string type) : m_type(type){}

// Getter for type
std::string HlsType::GetType() {
	return this->m_type;
}

// Constructor for audio type
AudioType::AudioType(std::string groupId, std::string language, std::string name, std::string defau, std::string autoSelect,std::string channels, std::string uri) :
	HlsType("AUDIO"),
	m_groupId(groupId),
	m_name(name),
	m_language(language),
	m_default(defau),
	m_autoSelect(autoSelect),
	m_channels(channels),
	m_uri(uri) {}

const std::string AudioType::GetLanguage() const {
	return this->m_language;
}
const std::string AudioType::GetName() const {
	return this->m_name;
}
const std::string AudioType::GetGroupID() const {
	return this->m_groupId;
}

void AudioType::Print() {
	std::cout << "Type: " << this->GetType() << ", Group ID: " << m_groupId << ",Name: " << m_name << ", Language: " << m_language
		<< ", Default: " << m_default << ", AutoSelect: " << m_autoSelect << ", Channels: " << m_channels << ", URI: " << m_uri << "\n";
}

// Constructor for video type
VideoType::VideoType(uint32_t bandwidth, uint32_t avgBandwidth, std::string codecs, std::string resolution, double frameRate,
	std::string videoRange, std::string audio, std::string closedCaptions, std::string attachment) :
	HlsType("VIDEO"),
	m_bandwidth(bandwidth),
	m_avgBandwidth(avgBandwidth),
	m_codecs(codecs),
	m_resolution(resolution),
	m_frameRate(frameRate),
	m_videoRange(videoRange),
	m_audio(audio),
	m_closedCaptions(closedCaptions),
	m_attachment(attachment) {}

void VideoType::Print() {
	std::cout << "Type: " << this->GetType() << ", Bandwidth: " << m_bandwidth << ", Avg Bandwidth: " << m_avgBandwidth <<  ", Codecs: " << m_codecs
		<< ", Resolution: " << m_resolution << ", FrameRate: " << m_frameRate << ", Video Range: " << m_videoRange << ", Audio: " << m_audio
		<< ", Closed Captions: " << m_closedCaptions << ", Attachment: " << m_attachment <<"\n";
}

uint32_t VideoType::GetBandwidth() const {
	return this->m_bandwidth;
}

uint32_t VideoType::GetAvgBandwidth() const {
	return this->m_avgBandwidth;
}

double VideoType::GetFrameRate() const {
	return this->m_frameRate;
}

// Constructor for image type
ImageType::ImageType(uint32_t bandwidth, std::string codecs, std::string resolution, std::string videoRange,
	std::string closedCaptions) :
	HlsType("IMAGE"),
	m_bandwidth(bandwidth),
	m_codecs(codecs),
	m_resolution(resolution),
	m_videoRange(videoRange),
	m_closedCaptions(closedCaptions) {}

const uint32_t ImageType::GetBandwidth() const {
	return this->m_bandwidth;
}

void ImageType::Print() {
	std::cout << "Type: " << this->GetType() << ", Bandwidth: " << m_bandwidth << ", Codecs: " << m_codecs
		<< ", Resolution: " << m_resolution << ", Video Range: " << m_videoRange
		<< ", Closed Captions: " << m_closedCaptions <<  "\n";
}
