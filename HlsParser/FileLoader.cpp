#include "FileLoader.h"

FileLoader::FileLoader(const LPCWSTR &url, const LPCWSTR &destination) : m_url(url), m_destination(destination) {
	/*
	* Constructor for file loader.
	* Args: 
	* LPCWSTR url: url of desired download
	* LPCWSTR destination: where to put the file we download locally
	* Returns:
	* New FileLoader object
	*/
}

void FileLoader::SetUrl(LPCWSTR url) {
	/*
	* Setter for url member variable
	* Args: 
	* LPCWSTR url: url of desired download
	* Returns:
	* N/a
	*/
	this->m_url = url;
}

const LPCWSTR& FileLoader::GetUrl() const {
	/*
	* Getter for url member variable
	* Args:
	* N/a
	* Returns:
	* LPCWSTR: This object's url
	*/
	// Const, we are not modifying our object
	return this->m_url;
}

// Setter for destination member variable
void FileLoader::SetDestination(LPCWSTR destination) {
	/*
	* Setter for destination member variable
	* Args:
	* LPCWSTR destination: where to put the file we download locally
	* Returns:
	* N/a
	*/
	this->m_destination = destination;
}

const LPCWSTR& FileLoader::GetDestination() const {
	/*
	* Getter for destination member variable
	* Args:
	* N/a
	* Returns:
	* LPCWSTR: This object's destination
	*/
	// Const, we are not modifying our object
	return this->m_destination;
}

bool FileLoader::DownloadFile() const {
	/*
	* Method for downloading the desired file
	* Args:
	* N/a
	* Returns:
	* bool gotFile: true if download was successful, false otherwise
	*/
	bool gotFile = false;

	// Maybe in the future could use last arg for callback to monitor download progress
	if (S_OK == URLDownloadToFile(NULL, this->m_url, this->m_destination, 0, NULL)) {
		gotFile = true;
	}
	return gotFile;
}
