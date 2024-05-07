#ifndef __HLS_TYPES__
#define __HLS_TYPES__
#include <iostream>
#include <vector>
// EXT-X-MEDIA:TYPE=AUDIO = audio
// EXT-X-STREAM-INF:BANDWIDTH = video
// EXT-X-I-FRAME-STREAM-INF:BANDWIDTH = images
// EXT-X-MEDIA:TYPE=SUBTITLES = subtitles

class HlsType {
private:
	std::string m_type;
public:
	// Default constructor should just set the type
	HlsType(std::string type);
	std::string GetType();
	std::string GetOriginalLine();
	virtual void Print() = 0;

};

// EXT-X-STREAM-INF:TYPE=AUDIO
class AudioType : public HlsType {
private:
	std::string m_groupId;
	std::string m_name;
	std::string m_language;
	std::string m_default; // These could be bools
	std::string m_autoSelect;
	std::string m_channels;
	std::string m_uri;
public:
	~AudioType() {};
	AudioType(std::string groupId, std::string language, std::string name, std::string defau, std::string autoSelect, std::string channels, std::string uri);
	void Print();
};

/*
* Subtitles isn't in the provided file - come back to this if needed
class SubtitlesType : HlsType {
private:

};
*/

// EXT-X-STREAM-INF
class VideoType : public HlsType {
private:
	uint32_t m_bandwidth;
	uint32_t m_avgBandwidth;
	std::string m_codecs; // could maybe be vector of codecs
	std::string m_resolution;
	double m_frameRate;
	std::string m_videoRange;
	std::string m_audio;
	std::string m_closedCaptions;
	std::string m_attachment;
public:
	~VideoType() {};
	VideoType(uint32_t bandwidth, uint32_t avgBandwidth, std::string codecs, std::string resolution, double frameRate,
		std::string videoRange, std::string audio, std::string closedCaptions, std::string attachment);
	void Print();
	uint32_t GetBandwidth() const;
};

// EXT-X-I-FRAME-STREAM-INF
// Image type can technically inherit from videotype
class ImageType : public HlsType{
private:
	uint32_t m_bandwidth;

	std::string m_codecs; // could maybe be vector of codecs
	std::string m_resolution;
	std::string m_videoRange;
	std::string m_closedCaptions;
public:
	void Print();
	~ImageType() {};
	ImageType(uint32_t bandwidth, std::string codecs, std::string resolution, std::string videoRange, std::string closedCaptions);
};
#endif
