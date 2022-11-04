#include "base/CCDirector.h"

#include <stdio.h>
#include "base/CCAsyncTaskPool.h"

#include "UpdateManager.h"
#include "EventListenerUpdateManager.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ZipHelper.h"
#else
#include "Zip/ZipHelper.h"
#endif

USING_NS_CC;
using namespace std;

#define TEMP_JSON_FILENAME_  ".json.temp"
#define JSON_FILENAME_       ".json"

#define DEFAULT_CONNECTION_TIMEOUT_ 8

UpdateManager::UpdateManager(const std::string& storagePath)
	: _updateState(State::UNCHECKED)
	
	, _storagePath("")
	, _jsonInput("")
	
	, _waitToUpdate(false)

	, _percent(0)
	, _percentByFile(0)
	, _totalToDownload(0)
	, _totalWaitToDownload(0)

	, _localConfigPath("")
	, _tempConfigPath("")

	, _initedGameIdDownload(false)
	, _initedLocalConfig(false)
	, _initedTemplateConfig(false)

	, _localConfig(nullptr)
	, _tempConfig(nullptr)

{
	// Init variables
	_eventDispatcher = Director::getInstance()->getEventDispatcher();
	std::string pointer = StringUtils::format("%p", this);
	_eventName = EventListenerUpdateManager::LISTENER_ID + pointer;
	_fileUtils = FileUtils::getInstance();
	_updateState = State::UNCHECKED;

	_downloader = std::shared_ptr<network::Downloader>(new network::Downloader);

	_downloader->onTaskError = bind(&UpdateManager::onError, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
    
	_downloader->onTaskProgress = [this](const network::DownloadTask& task,
		int64_t bytesReceived,
		int64_t totalBytesReceived,
		int64_t totalBytesExpected)
	{
		this->onProgress(totalBytesExpected, totalBytesReceived, task.requestURL, task.identifier);
	};
    
	_downloader->onFileTaskSuccess = [this](const network::DownloadTask& task)
	{
		this->onSuccess(task.requestURL, task.storagePath, task.identifier);
	};
	
	setStoragePath(storagePath);
}


UpdateManager::~UpdateManager()
{
	_downloader->onTaskError = (nullptr);
	_downloader->onFileTaskSuccess = (nullptr);
	_downloader->onTaskProgress = (nullptr);

	_idGameDownload = "";
	_lstAssetsNeedDownload.clear();

	CC_SAFE_RELEASE(_localConfig);
	CC_SAFE_RELEASE(_tempConfig);
}

UpdateManager* UpdateManager::create(const std::string& storagePath)
{
	UpdateManager* ret = new (std::nothrow) UpdateManager(storagePath);
	if (ret)
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

void UpdateManager::setUpdateInfo(const std::string& json)
{
	this->_updateState = State::NEED_UPDATE;
	this->_jsonInput = json;

	// init information
	initInformation();

	// gen assets need download
	genAssetDiffNeedDownload();
}

void UpdateManager::initGameIdDownload()
{
	_initedGameIdDownload = true;

	if (_jsonInput.size() == 0) {
		log("Fail to retrieve local file from json content: %s\n", _jsonInput.c_str());
		_initedGameIdDownload = false;
		return;
	}

	// Parse file with rapid json
	_jsonContent.Parse<0>(_jsonInput.c_str());
	// Print error
	if (_jsonContent.HasParseError()) {
		size_t offset = _jsonContent.GetErrorOffset();
		if (offset > 0)
			offset--;
		std::string errorSnippet = _jsonInput.substr(offset, 10);
		log("File parse error %u at <%s>\n", _jsonContent.GetParseError(), errorSnippet.c_str());
		
		_initedGameIdDownload = false;
		return;
	}

	// Get game info from json content
	if (!_jsonContent.IsObject()) {
		_initedGameIdDownload = false;
		return;
	}
		
	// init path
	_idGameDownload = StringUtils::toString(_jsonContent["id"].GetInt());
	_localConfigPath = _storagePath + _idGameDownload + JSON_FILENAME_;
	_tempConfigPath = _storagePath + _idGameDownload + TEMP_JSON_FILENAME_;
}

void UpdateManager::initInformation()
{
	initGameIdDownload();

	if (_initedGameIdDownload)
	{
		initLocalConfig();
		initTemplateConfig();
	}
}

void UpdateManager::initLocalConfig()
{
	_initedLocalConfig = true;

	_localConfig = new (std::nothrow) UpdateConfig(_localConfigPath);
    if (_localConfig) {
        _initedLocalConfig = _localConfig->initInformation();
    } else {
        _initedLocalConfig = false;
    }
		
    if (!_initedLocalConfig) {
        CC_SAFE_DELETE(_localConfig);
    }
}

void UpdateManager::initTemplateConfig()
{
	_initedTemplateConfig = true;

	_tempConfig = new (std::nothrow) UpdateConfig(_tempConfigPath);
    if (_tempConfig) {
        _initedTemplateConfig = _tempConfig->initInformation(_jsonInput);
    } else {
         _initedTemplateConfig = false;
    }
		
    if (!_initedTemplateConfig) {
        CC_SAFE_DELETE(_tempConfig);
    }
}

void UpdateManager::replaceLocalByTemplateConfig()
{
    cocos2d::log("replaceLocalByTemplateConfig");
    
    if (_fileUtils->isFileExist(_tempConfigPath)) {
        _fileUtils->renameFile(_storagePath, _idGameDownload + TEMP_JSON_FILENAME_, _idGameDownload + JSON_FILENAME_);
        
        if (_localConfig != nullptr)
        {
            _localConfig->release();
            _localConfig = nullptr;
        }
        
        if (_tempConfig != nullptr)
        {
            _tempConfig->release();
            _tempConfig = nullptr;
        }
    }
}

void UpdateManager::setStoragePath(const std::string& storagePath)
{
	_storagePath = storagePath;
	adjustPath(_storagePath);
	_fileUtils->createDirectory(_storagePath);
}

void UpdateManager::adjustPath(std::string &path)
{
	if (path.size() > 0 && path[path.size() - 1] != '/')
	{
		path.append("/");
	}
}

void UpdateManager::dispatchUpdateEvent(EventUpdateManager::EventCode code, const std::string &assetId/* = ""*/, const std::string &message/* = ""*/, int curle_code/* = CURLE_OK*/, int curlm_code/* = CURLM_OK*/)
{
	EventUpdateManager event(_eventName, this, code, _percent, _percentByFile, assetId, message, curle_code, curlm_code);
	_eventDispatcher->dispatchEvent(&event);
}

bool UpdateManager::decompressDownloadedZip()
{
	bool ret = true;
	if (_compressedFiles.size() == 0) return ret;

	// Decompress all compressed files
	for (int i = 0; i < _compressedFiles.size(); i++) {
		std::string zipfile = _compressedFiles.at(i);
		cocos2d::log("ZipFile: %s", zipfile.c_str());

		if (!ZipHelper::decompress(zipfile))
		{
			ret = false;
			dispatchUpdateEvent(EventUpdateManager::EventCode::ERROR_DECOMPRESS, "", "Unable to decompress file " + zipfile);
		}
		_fileUtils->removeFile(zipfile);
	}
	_compressedFiles.clear();

	return ret;
}

UpdateManager::State UpdateManager::getUpdateState() const
{
	return _updateState;
}

void UpdateManager::genAssetDiffNeedDownload()
{
	_lstAssetsNeedDownload.clear();

	if (!_initedGameIdDownload)
	{
		cocos2d::log(" Init Game ID failed !");
		_updateState = State::GEN_ASSETS_FAIL;

		return;
	}

	if (!_initedTemplateConfig)
	{
		cocos2d::log(" Init Template Config failed !");
		_updateState = State::GEN_ASSETS_FAIL;

		return;
	}

	UpdateConfig::GameInfo templateGameInfoDownload = _tempConfig->getGameInfoDownload();
	if (!_initedLocalConfig)
		_lstAssetsNeedDownload = templateGameInfoDownload.lstAssets;
	else
	{
		UpdateConfig::GameInfo localGameInfoDownload = _localConfig->getGameInfoDownload();
		
        std::vector<UpdateConfig::AssetInfo> templateAssetInfos = templateGameInfoDownload.lstAssets;
		std::vector<UpdateConfig::AssetInfo> localAssetInfos = localGameInfoDownload.lstAssets;
	
		std::string key;
        
		UpdateConfig::Asset valueLocal;
		UpdateConfig::Asset valueTemplate;

		// gen list asset need download
        for ( int i = 0; i < templateAssetInfos.size(); i++)
		{
            auto assetInfoTmp = templateAssetInfos.at(i);
            
			key = assetInfoTmp.info;
			valueTemplate = assetInfoTmp.asset;

			// Check to find asset need download
            bool find = false;
            for (int i = 0; i < localAssetInfos.size(); i++)
            {
                auto assetInfoLocal = localAssetInfos.at(i);
                auto localKey = assetInfoLocal.info;
                if (strcmp(key.c_str(), localKey.c_str()) == 0)
                {
                    find = true;
                    break;
                }
            }
            
            if (!find)
            {
                UpdateConfig::Asset assetDownload = valueTemplate;
                UpdateConfig::AssetInfo assetInfoDownload(key, assetDownload);
                
                _lstAssetsNeedDownload.push_back(assetInfoDownload);
                
            }
			
		}
	}

	if (_lstAssetsNeedDownload.size() == 0)
    {
        replaceLocalByTemplateConfig();
        
        _updateState = State::UP_TO_DATE;
    }
    else
    {
        _updateState = State::READY_FOR_UPDATE;
    }
}

void UpdateManager::startUpdate()
{
	if (_updateState != State::READY_FOR_UPDATE) return;
	_updateState = State::UPDATING;

	// Clean up before update
	_failedUnits.clear();
	_downloadUnits.clear();
	_compressedFiles.clear();
	_totalWaitToDownload = _totalToDownload = 0;
	_percent = _percentByFile = _sizeCollected = _totalSize = 0;
	_downloadedSize.clear();
	_totalEnabled = false;

	for (int i = 0; i < _lstAssetsNeedDownload.size(); i++)
	{
		UpdateConfig::Asset assetDownload = _lstAssetsNeedDownload.at(i).asset;

		std::string unitLink = assetDownload.urlLink;
		std::string unitPath = assetDownload.packageName;
		cocos2d::log("Pack Name: %s", unitPath.c_str());

		DownloadUnit unit;
        unit.customId = _lstAssetsNeedDownload.at(i).info;
		unit.srcUrl = unitLink;
		unit.storagePath = _storagePath + unitPath;

		_compressedFiles.push_back(unit.storagePath);
		_downloadUnits.insert(std::pair<std::string, DownloadUnit> (unit.customId, unit));
	}
	
	_totalWaitToDownload = _totalToDownload = (int)_downloadUnits.size();
	this->batchDownload();

	std::string msg = StringUtils::format("Start to update %d files from remote package.", _totalToDownload);
	dispatchUpdateEvent(EventUpdateManager::EventCode::UPDATE_PROGRESSION, "", msg);
	
	_waitToUpdate = false;
}

void UpdateManager::updateSucceed()
{
	if (_compressedFiles.size() == 0) return;
	_updateState = State::UNZIPPING;

	struct AsyncData
	{
		std::vector<std::string> compressedFiles;
		std::string errorCompressedFile;
	};

	AsyncData* asyncData = new AsyncData;
	asyncData->compressedFiles = _compressedFiles;
	_compressedFiles.clear();

	std::function<void(void*)> mainThread = [this](void* param) {
		AsyncData* asyncData = (AsyncData*)param;
		if (asyncData->errorCompressedFile.empty())
		{
            replaceLocalByTemplateConfig();

			_updateState = State::UP_TO_DATE;
			dispatchUpdateEvent(EventUpdateManager::EventCode::UPDATE_FINISHED);
		}
		else
		{
			if (_localConfig != nullptr)
			{
				_localConfig->release();
				_localConfig = nullptr;
			}

			if (_tempConfig != nullptr)
			{
				_tempConfig->removeFile();
				_tempConfig->release();
				_tempConfig = nullptr;
			}

			_updateState = State::FAIL_TO_UPDATE;
			dispatchUpdateEvent(EventUpdateManager::EventCode::ERROR_DECOMPRESS, "", "Unable to decompress file " + asyncData->errorCompressedFile);
		}

		delete asyncData;
	};
	AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_OTHER, mainThread, (void*)asyncData, [this, asyncData]() {
		// Decompress all compressed files
		for (int i = 0; i < asyncData->compressedFiles.size(); i++) 
		{
			std::string zipfile = asyncData->compressedFiles.at(i);
			cocos2d::log("Extract file: %s", zipfile.c_str());
			if (!ZipHelper::decompress(zipfile))
			{
				cocos2d::log("Extract Fail !");
				asyncData->errorCompressedFile = zipfile;
				break;
			}
			else
			{
				cocos2d::log("Extract OK !");
			}
			_fileUtils->removeFile(zipfile);
		}
	});
}

void UpdateManager::checkUpdate()
{
	switch (_updateState) 
	{
		case State::UNCHECKED:
			break;
            
		case State::GEN_ASSETS_FAIL:
			dispatchUpdateEvent(EventUpdateManager::EventCode::UPDATE_FAILED);
			break;
            
		case State::UP_TO_DATE:
			dispatchUpdateEvent(EventUpdateManager::EventCode::ALREADY_UP_TO_DATE);
			break;
            
		case State::FAIL_TO_UPDATE:
			dispatchUpdateEvent(EventUpdateManager::EventCode::UPDATE_FAILED);
            break;
            
		case State::NEED_UPDATE:
			break;
            
		default:
			break;
	}
}

void UpdateManager::update()
{
	if (!_initedGameIdDownload)
	{
		log("UpdateManager : Game ID init failed !\n");
		return;
	}

	if (!_initedTemplateConfig)
	{
		log("UpdateManager : Template Config init failed !\n");
		return;
	}

	if (!_initedLocalConfig)
	{
		log("UpdateManager : No Local config file found !\n");
	}

	_waitToUpdate = true;

	switch (_updateState)
	{
		case State::GEN_ASSETS_FAIL:
			dispatchUpdateEvent(EventUpdateManager::EventCode::UPDATE_FAILED);
			break;

		case State::READY_FOR_UPDATE:
			startUpdate();
			break;
		
		case State::UP_TO_DATE:
			dispatchUpdateEvent(EventUpdateManager::EventCode::ALREADY_UP_TO_DATE);
			break;

		case State::UPDATING:
			_waitToUpdate = false;
			break;

		default:
			break;
	}
}

void UpdateManager::updateAssets(const DownloadUnits& assets)
{
	if (!_initedGameIdDownload)
	{
		log("UpdateManager : Init Game ID failed !\n");
		return;
	}

	if (!_initedTemplateConfig)
	{
		log("UpdateManager : Template Config init failed !\n");
		return;
	}

	if (!_initedLocalConfig)
	{
		log("UpdateManager : No Local config file found !\n");
	}

	if (_updateState != State::UPDATING && _localConfig->isLoaded() && _tempConfig->isLoaded())
	{
		int size = (int)(assets.size());
		if (size > 0)
		{
			_updateState = State::UPDATING;
			_downloadUnits.clear();
			_downloadUnits = assets;
			this->batchDownload();
		}
		else if (size == 0 && _totalWaitToDownload == 0)
		{
			updateSucceed();
		}
	}
}

const DownloadUnits& UpdateManager::getFailedAssets() const
{
	return _failedUnits;
}

const std::string& UpdateManager::getStoragePath() const
{
	return _storagePath;
}

void UpdateManager::onError(const network::DownloadTask& task, int errorCode, int errorCodeInternal, const std::string& errorStr)
{
	auto unitIt = _downloadUnits.find(task.identifier);
	// Found unit and add it to failed units
	if (unitIt != _downloadUnits.end())
	{
		DownloadUnit unit = unitIt->second;
		_failedUnits.emplace(unit.customId, unit);
	}
    
    _updateState = State::FAIL_TO_UPDATE;
	dispatchUpdateEvent(EventUpdateManager::EventCode::ERROR_UPDATING, task.identifier, errorStr, errorCode, errorCodeInternal);
}

void UpdateManager::onProgress(double total, double downloaded, const std::string &url, const std::string &customId)
{
	// Calculation total downloaded
	bool found = false;
	double totalDownloaded = 0;
	for (auto it = _downloadedSize.begin(); it != _downloadedSize.end(); ++it)
	{
		if (it->first == customId)
		{
			it->second = downloaded;
			found = true;
		}
		totalDownloaded += it->second;
	}
	// Collect information if not register
	if (!found)
	{
		// Set download state to DOWNLOADING, this will run only once in the download process
        for (int i = 0; i < _lstAssetsNeedDownload.size(); i++)
        {
            if (std::strcmp(_lstAssetsNeedDownload.at(i).info.c_str(), customId.c_str()) == 0)
            {
                _lstAssetsNeedDownload.at(i).asset.downloadState = UpdateConfig::DownloadState::DOWNLOADING;
            }
        }
		// Register the download size information
		_downloadedSize.emplace(customId, downloaded);
		_totalSize += total;
		_sizeCollected++;
		// All collected, enable total size
		if (_sizeCollected == _totalToDownload)
		{
			_totalEnabled = true;
		}
	}

	if (_totalEnabled && _updateState == State::UPDATING)
	{
		float currentPercent = 100 * totalDownloaded / _totalSize;
			// Notify at integer level change
		if ((int)currentPercent != (int)_percent) {
			_percent = currentPercent;
			// Notify progression event
			dispatchUpdateEvent(EventUpdateManager::EventCode::UPDATE_PROGRESSION, customId);
		}
	}
}

void UpdateManager::downloadFailedAssets()
{
	log("UpdateManager : Start update %lu failed assets.\n", _failedUnits.size());
	updateAssets(_failedUnits);
}

void UpdateManager::onSuccess(const std::string &srcUrl, const std::string &storagePath, const std::string &customId)
{
    bool assetFind = false;
    int indexFind = -1;
    
    for (int i = 0; i < _lstAssetsNeedDownload.size(); i++)
    {
        auto assetInfo = _lstAssetsNeedDownload.at(i);
        std::string info = assetInfo.info;
        if (strcmp(info.c_str(), customId.c_str()) == 0)
        {
            assetFind = true;
            indexFind = i;
            break;
        }
    }
    
    
    if (assetFind && indexFind > 0)
    {
        _lstAssetsNeedDownload.at(indexFind).asset.downloadState = UpdateConfig::DownloadState::SUCCESSED; // Set download state to SUCCESSED
    }

	auto unitIt = _downloadUnits.find(customId);
	if (unitIt != _downloadUnits.end())
	{
		// Reduce count only when unit found in _downloadUnits
		_totalWaitToDownload--;

		_percentByFile = 100 * (float)(_totalToDownload - _totalWaitToDownload) / _totalToDownload;

		// Notify progression event
		dispatchUpdateEvent(EventUpdateManager::EventCode::UPDATE_PROGRESSION, "");
	}

	// Notify asset updated event
	dispatchUpdateEvent(EventUpdateManager::EventCode::ASSETS_UPDATED, customId);

	unitIt = _failedUnits.find(customId);
	// Found unit and delete it
	if (unitIt != _failedUnits.end())
	{
		// Remove from failed units list
		_failedUnits.erase(unitIt);
	}

	if (_totalWaitToDownload <= 0)
	{
		// Finished with error check
		if (_failedUnits.size() > 0)
		{
			_tempConfig->removeFile();

			_updateState = State::FAIL_TO_UPDATE;
			dispatchUpdateEvent(EventUpdateManager::EventCode::UPDATE_FAILED);
		}
		else
		{
			updateSucceed();
		}
	}
}

void UpdateManager::destroyDownloadedVersion()
{
	_fileUtils->removeFile(_tempConfigPath);
}

void UpdateManager::batchDownload()
{
	for (auto iter : _downloadUnits)
	{
		DownloadUnit& unit = iter.second;
		_downloader->createDownloadFileTask(unit.srcUrl, unit.storagePath, unit.customId);
	}
}

