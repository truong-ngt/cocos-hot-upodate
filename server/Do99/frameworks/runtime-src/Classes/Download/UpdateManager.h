#pragma once
#include "cocos2d.h"
#include "base/CCEventDispatcher.h"
#include "platform/CCFileUtils.h"
#include "json/document.h"

#include <string>
#include <vector>

#include "UpdateConfig.h"
#include "EventUpdateManager.h"
#include "network/CCDownloader.h"

class UpdateManager : public cocos2d::Ref
{
public:	
	//! Update states
	enum class State
	{
		UNCHECKED,
		NEED_UPDATE,
		GEN_ASSETS_FAIL,
		READY_FOR_UPDATE,
		UPDATING,
		UNZIPPING,
		UP_TO_DATE,
		FAIL_TO_UPDATE
	};

	static UpdateManager* create(const std::string& storagePath);

	void setUpdateInfo(const std::string& json);
	void update();
	State getUpdateState() const;

	void checkUpdate();
	void downloadFailedAssets();
	const std::string& getStoragePath() const;

	UpdateManager(const std::string& storagePath);
	virtual ~UpdateManager();

protected:

	void initInformation();
	
	void initGameIdDownload();
	void initLocalConfig();
	void initTemplateConfig();
    void replaceLocalByTemplateConfig();

	void genAssetDiffNeedDownload();

	void setStoragePath(const std::string& storagePath);
	void adjustPath(std::string &path);
	void dispatchUpdateEvent(EventUpdateManager::EventCode code, const std::string &message = "", const std::string &assetId = "", int curle_code = 0, int curlm_code = 0);
	void startUpdate();
	void updateSucceed();
	bool decompressDownloadedZip();
	void updateAssets(const DownloadUnits& assets);
	const DownloadUnits& getFailedAssets() const;
	void destroyDownloadedVersion();

	virtual void onError(const network::DownloadTask& task,
						 int errorCode,
						 int errorCodeInternal,
						 const std::string& errorStr);

	virtual void onProgress(double total, double downloaded, const std::string &url, const std::string &customId);
	virtual void onSuccess(const std::string &srcUrl, const std::string &storagePath, const std::string &customId);

private:

	void batchDownload();

	std::string _eventName;
	std::string _storagePath;
	std::string _localConfigPath;
	std::string _tempConfigPath;
	std::string _jsonInput;
	std::string _idGameDownload;

	std::vector<std::string> _compressedFiles;

	cocos2d::EventDispatcher *_eventDispatcher;
	cocos2d::FileUtils *_fileUtils;

	State _updateState;

	std::shared_ptr<network::Downloader> _downloader;

	UpdateConfig *_localConfig;
	UpdateConfig *_tempConfig;

	DownloadUnits _downloadUnits;
	DownloadUnits _failedUnits;

	float _percent;
	float _percentByFile;
	double _totalSize;
	
	int _totalEnabled;
	int _sizeCollected;
	int _totalToDownload;
	int _totalWaitToDownload;

	bool _initedTemplateConfig;
	bool _initedLocalConfig;
	bool _initedGameIdDownload;

	bool _waitToUpdate;

	std::unordered_map<std::string, double> _downloadedSize;
    std::vector<UpdateConfig::AssetInfo> _lstAssetsNeedDownload;

	rapidjson::Document _jsonContent;
};

