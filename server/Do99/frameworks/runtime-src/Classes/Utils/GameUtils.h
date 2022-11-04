#pragma once

#include "cocos2d.h"
#include "jsapi.h"
#include "jsfriendapi.h"

#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpClient.h"

#include "scripting/js-bindings/manual/js_bindings_config.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/jsb_helper.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"

#include <string>
#include <sstream>
#include <vector>

USING_NS_CC;
using namespace network;
using namespace std;

class GameUtils : public Ref
{
public:
    GameUtils();
    ~GameUtils();
    
    enum class DownloadStatus {
        DOWNLOAD_FILE_FAILED = 0,
        DOWNLOAD_FILE_COMPLETED
    };
    
    JS_BINDED_CLASS_GLUE(GameUtils);
    JS_BINDED_CONSTRUCTOR(GameUtils);
    
    JS_BINDED_PROP_ACCESSOR(GameUtils, onDownloadFileCompleted);
    JS_BINDED_PROP_ACCESSOR(GameUtils, onDownloadFileFailed);
    
    JS_BINDED_PROP_ACCESSOR(GameUtils, onDownloadZipFileCompleted);
    JS_BINDED_PROP_ACCESSOR(GameUtils, onDownloadZipFileFailed);
    
    JS_BINDED_PROP_ACCESSOR(GameUtils, onInstallGameCompleted);
    JS_BINDED_PROP_ACCESSOR(GameUtils, onInstallGameFailed);
    
    JS_BINDED_FUNC(GameUtils, downloadFile);
    JS_BINDED_FUNC(GameUtils, downloadZipFile);
    
    JS_BINDED_FUNC(GameUtils, installGame);
    
    
private:
    
    void _notify(JSObject * callback, const string& strMsg = "");
    
    void _downloadFile(int nFileID,const string& strURL, const string& strPath);
    void _downloadZipFile(int nFileId, const string& strFileURL, const string& strFilePath);
    
    void _onFileDownloaded(HttpClient *pSender, HttpResponse *pResponse);
    void _onZipFileDownloaded(HttpClient *pSender, HttpResponse *pResponse);
    
    void _installGame(const std::string& strFilePath, const string& strExtractPath, int nId = -1);
    void _afterInstalledGame(void * param);
    
    void split(const string &s, char delim, vector<string> &elems);
    vector<string> split(const string &s, char delim);
    string getFileNameFromUrl(const string& strURL);
    
private:
    JSContext*					_cx;
    
    JS::Heap<JSObject*>			_onDownloadFileCompletedCallback;
    JS::Heap<JSObject*>			_onDownloadFileFailedCallback;
  
    JS::Heap<JSObject*>			_onDownloadZipFileCompletedCallback;
    JS::Heap<JSObject*>			_onDownloadZipFileFailedCallback;
    
    JS::Heap<JSObject*>			_onInstallGameCompletedCallback;
    JS::Heap<JSObject*>			_onInstallGameFailedCallback;
    
    FileUtils*                  _fileUtils;
};
