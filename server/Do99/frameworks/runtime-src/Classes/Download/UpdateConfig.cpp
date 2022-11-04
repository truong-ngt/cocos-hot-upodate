#include "UpdateConfig.h"
#include "json/filereadstream.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"

#include <fstream>

#define KEY_ID			"id"
#define KEY_HOST		"host"
#define KEY_PACKAGES	"packages"


UpdateConfig::UpdateConfig(const std::string& path)
: _loaded(false)
, _storagePath("")
, _path(path)
{
	// Init variables
	_fileUtils = FileUtils::getInstance();

	// Register the local storage path 
	size_t found = path.find_last_of("/\\");
	if (found != std::string::npos)
	{
		_storagePath = path.substr(0, found + 1);
	}

}

UpdateConfig::~UpdateConfig()
{
}

bool UpdateConfig::isLoaded() const
{
	return _loaded;
}

std::string UpdateConfig::getname(const std::string& path) const
{
	size_t found = path.find_last_of("/\\");

	if (std::string::npos != found)
	{
		return path.substr(found + 1);
	}
	else
	{
		return path;
	}
}

void UpdateConfig::clear()
{
	if (_loaded)
	{
        if (!_jsonContent.IsNull()) {
            _jsonContent.SetNull();
        }
		_loaded = false;
	}
}

void UpdateConfig::saveToFile()
{
	cocos2d::log("save config to file");

	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	if (!_jsonContent.IsNull())
		_jsonContent.Accept(writer);

	std::ofstream output(_path, std::ofstream::out);
	if (!output.bad())
		output << buffer.GetString() << std::endl;
}

void UpdateConfig::removeFile()
{
	if (_fileUtils->isFileExist(_path))
	{
		_fileUtils->removeFile(_path);
		clear();
	}
}

bool UpdateConfig::initInformation()
{
	//clear 
	clear();

	if (!_fileUtils)
		return false;

	if (!_fileUtils->isFileExist(_path))
		return false;

	// Load content config file
	std::string content = _fileUtils->getStringFromFile(_path);
	if (content.size() == 0)
	{
		CCLOG("Fail to retrieve local file content: %s\n", _path.c_str());
		return false;
	}
	// Parse file with rapid json
	_jsonContent.Parse<0>(content.c_str());
	// Print error
	if (this->_jsonContent.HasParseError()) {
		size_t offset = this->_jsonContent.GetErrorOffset();
		if (offset > 0)
			offset--;
		std::string errorSnippet = content.substr(offset, 10);
		log("File parse error %u at <%s>\n", this->_jsonContent.GetParseError(), errorSnippet.c_str());
		return false;
	}

	// Get game info from json content
	if (!this->_jsonContent.IsObject())
		return false;

    if (_jsonContent.HasMember("id"))
    {
        _gameInfoDownload.id = _jsonContent["id"].GetInt();
    }
    if (_jsonContent.HasMember("host"))
    {
        _gameInfoDownload.hostURL = _jsonContent["host"].GetString();
    }

	const rapidjson::Value& packages = _jsonContent[KEY_PACKAGES];
	if (!packages.IsArray())
			return false;
	for (rapidjson::SizeType i = 0; i < packages.Size(); i++)
	{
		Asset asset;
		asset.packageName = packages[i].GetString();
		asset.compressed = true;
		asset.downloadState = DownloadState::UNSTARTED;
		asset.urlLink = _gameInfoDownload.hostURL + "/" + asset.packageName;

        AssetInfo assetInfo(asset.packageName, asset);
		_gameInfoDownload.lstAssets.push_back(assetInfo);
	}

	_loaded = true;
	return true;
}

bool UpdateConfig::initInformation(const std::string& strJson)
{
	bool ret = true;

	// clear
	clear();

	if (strJson.size() == 0) {
		CCLOG("Fail to retrieve local file from json content: %s\n", _path.c_str());
		return false;
	}

	// Parse file with rapid json
	_jsonContent.Parse<0>(strJson.c_str());
	// Print error
	if (_jsonContent.HasParseError()) {
		size_t offset = _jsonContent.GetErrorOffset();
		if (offset > 0)
			offset--;
		std::string errorSnippet = strJson.substr(offset, 10);
		log("File parse error %u at <%s>\n", _jsonContent.GetParseError(), errorSnippet.c_str());
		return false;
	}

	// Get game info from json content
	if (!_jsonContent.IsObject())
		return false;

	_gameInfoDownload.id = _jsonContent["id"].GetInt();
	_gameInfoDownload.hostURL = _jsonContent["host"].GetString();

	const rapidjson::Value& packages = _jsonContent[KEY_PACKAGES];
	if (!packages.IsArray())
		return false;
	for (rapidjson::SizeType i = 0; i < packages.Size(); i++)
	{
		Asset asset;
		asset.packageName = packages[i].GetString();
		asset.compressed = true;
		asset.downloadState = DownloadState::UNSTARTED;
		asset.urlLink = _gameInfoDownload.hostURL + asset.packageName;

		cocos2d::log("Asset Package Name: %s", asset.packageName.c_str());
        
        AssetInfo assetInfo(asset.packageName, asset);
		_gameInfoDownload.lstAssets.push_back(assetInfo);
	}

	saveToFile();

	_loaded = true;
	return true;
}

UpdateConfig::GameInfo UpdateConfig::getGameInfoDownload() const
{
	return _gameInfoDownload;
}

