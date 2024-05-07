#ifndef __FILE_LOADER__
#define __FILE_LOADER__
#include <urlmon.h>
#include <iostream>
/*
* Class for downloading the file from a url
*/
class FileLoader {
private:
	LPCWSTR m_url;
	LPCWSTR m_destination;
public:
	FileLoader(const LPCWSTR &url, const LPCWSTR &destination);

	void SetUrl(LPCWSTR url);
	const LPCWSTR& GetUrl() const;

	void SetDestination(LPCWSTR destination);
	const LPCWSTR& GetDestination() const;

	bool DownloadFile() const;
};
#endif
