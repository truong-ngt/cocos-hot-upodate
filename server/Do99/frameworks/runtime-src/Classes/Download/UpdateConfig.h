#pragma once
#include "cocos2d.h"
USING_NS_CC;

#include <string>
#include <vector>

#include "json/document.h"

struct DownloadUnit
{
	std::string srcUrl;
	std::string storagePath;
	std::string customId;
};
typedef std::unordered_map<std::string, DownloadUnit> DownloadUnits;

class UpdateConfig : public Ref
{
public:

	friend class UpdateManager;

	enum class DownloadState {
		UNSTARTED,
		DOWNLOADING,
		SUCCESSED
	};

	//! Asset object
	struct Asset {
		std::string urlLink;
		std::string packageName;
		bool compressed;
		DownloadState downloadState;
	};
    
    struct AssetInfo
    {
        std::string info;
        Asset asset;
        
        AssetInfo (std::string const& _info, Asset& _asset)
        {
            info = _info;
            asset = _asset;
        }
    };

	struct GameInfo
	{
		int id;
		std::string hostURL;
		std::vector<AssetInfo> lstAssets;
	};

	bool isLoaded() const;
protected:

	UpdateConfig(const std::string& path = "");
	~UpdateConfig();

	void setAssetDownloadState(const std::string &key, const DownloadState &state);
	void genResumeAssetsList(DownloadUnits *units) const;

	// new design
	void clear();

	bool initInformation();
	bool initInformation(const std::string& strJson);

	void saveToFile();
	void removeFile();
	
	GameInfo getGameInfoDownload() const;
private:
	std::string getname(const std::string& path) const;

	bool _loaded;

	//! Reference to the global file utils
	FileUtils *_fileUtils;

	std::string _storagePath;
	std::string _path;

	rapidjson::Document _jsonContent;
	
	GameInfo _gameInfoDownload;
};


