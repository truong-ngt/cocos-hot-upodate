#include "GameUtils.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ZipHelper.h"
#else
#include "Zip/ZipHelper.h"
#endif

struct AsyncDataZipFile
{
    int     nId;
    bool    bIsDecompressed;
    string  strFilePath;
    string  strExtractPath;
};

GameUtils::GameUtils()
: _cx(ScriptingCore::getInstance()->getGlobalContext())

, _onDownloadFileCompletedCallback(nullptr)
, _onDownloadFileFailedCallback(nullptr)

, _onDownloadZipFileCompletedCallback(nullptr)
, _onDownloadZipFileFailedCallback(nullptr)

, _onInstallGameCompletedCallback(nullptr)
, _onInstallGameFailedCallback(nullptr)
{
    _fileUtils = FileUtils::getInstance();
}

GameUtils::~GameUtils()
{
    JS::RootedValue callback(_cx);
    
    if (_onDownloadFileCompletedCallback)
    {
        callback.set(OBJECT_TO_JSVAL(_onDownloadFileCompletedCallback));
        js_remove_object_root(callback);
    }
    if (_onDownloadFileFailedCallback)
    {
        callback.set(OBJECT_TO_JSVAL(_onDownloadFileFailedCallback));
        js_remove_object_root(callback);
    }
    
    if (_onDownloadZipFileCompletedCallback)
    {
        callback.set(OBJECT_TO_JSVAL(_onDownloadZipFileCompletedCallback));
        js_remove_object_root(callback);
    }
    if (_onDownloadZipFileFailedCallback)
    {
        callback.set(OBJECT_TO_JSVAL(_onDownloadZipFileFailedCallback));
        js_remove_object_root(callback);
    }
    
    if (_onInstallGameCompletedCallback)
    {
        callback.set(OBJECT_TO_JSVAL(_onInstallGameCompletedCallback));
        js_remove_object_root(callback);
    }
    if (_onInstallGameFailedCallback)
    {
        callback.set(OBJECT_TO_JSVAL(_onInstallGameFailedCallback));
        js_remove_object_root(callback);
    }
}

// For JavaScript Bindings
/**
 *  @brief Initialize Object and needed properties.
 *
 */
JS_BINDED_CLASS_GLUE_IMPL(GameUtils);

/**
 *  @brief Implementation for the Javascript Constructor
 *
 */
JS_BINDED_CONSTRUCTOR_IMPL(GameUtils)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    GameUtils* req = new (std::nothrow) GameUtils();
    JS::RootedObject proto(cx, GameUtils::js_proto);
    JS::RootedObject parentProto(cx, GameUtils::js_parent);
    JS::RootedObject obj(cx, JS_NewObject(cx, &GameUtils::js_class, proto, parentProto));
    
    js_proxy_t *p = jsb_new_proxy(req, obj);
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    CC_UNUSED_PARAM(p);
    js_add_FinalizeHook(cx, obj);
    // don't retain it, already retained
#if COCOS2D_DEBUG > 1
    CCLOG("++++++RETAINED++++++ Cpp(GameUtils): %p - JS: %p", req, obj.get());
#endif // COCOS2D_DEBUG
#else
    // autorelease it
    req->autorelease();
    JS::AddNamedObjectRoot(cx, &p->obj, "GameUtils");
#endif
    
    jsval out;
    if (obj)
    {
        JS_SetPrivate(obj, req);
        out = OBJECT_TO_JSVAL(obj);
    }
    else
    {
        out = JS::NullValue();
    }
    args.rval().set(out);
    return true;
}

/**
 *  @brief Get Callback function for Javascript
 *  @brief Set Callback function coming from Javascript
 *
 */

#define GETTER_SETTER_FOR_CALLBACK_PROP(x,y) JS_BINDED_PROP_GET_IMPL(GameUtils, x)\
{\
    if (y)\
    {\
        JS::RootedValue out(cx, OBJECT_TO_JSVAL(y));\
        args.rval().set(out);\
    }\
    else\
    {\
        args.rval().set(JSVAL_NULL);\
    }\
    return true;\
}\
JS_BINDED_PROP_SET_IMPL(GameUtils, x)\
{\
    JS::RootedValue callback(cx, args.get(0));\
    if (!callback.isNullOrUndefined())\
    {\
        if (y)\
        {\
            JS::RootedValue oldCallback(cx, OBJECT_TO_JSVAL(y));\
            js_remove_object_root(oldCallback);\
        }\
        js_add_object_root(callback);\
        y = callback.toObjectOrNull();\
    }\
    return true;\
}

GETTER_SETTER_FOR_CALLBACK_PROP(onDownloadFileCompleted, _onDownloadFileCompletedCallback)
GETTER_SETTER_FOR_CALLBACK_PROP(onDownloadFileFailed, _onDownloadFileFailedCallback)

GETTER_SETTER_FOR_CALLBACK_PROP(onDownloadZipFileCompleted, _onDownloadZipFileCompletedCallback)
GETTER_SETTER_FOR_CALLBACK_PROP(onDownloadZipFileFailed, _onDownloadZipFileFailedCallback)

GETTER_SETTER_FOR_CALLBACK_PROP(onInstallGameCompleted, _onInstallGameCompletedCallback)
GETTER_SETTER_FOR_CALLBACK_PROP(onInstallGameFailed, _onInstallGameFailedCallback)

/**
 *  @brief destructor for Javascript
 *
 */
static void basic_object_finalize(JSFreeOp *freeOp, JSObject *obj)
{
    CCLOG("basic_object_finalize %p ...", obj);
}

void GameUtils::_notify(JSObject * callback, const std::string& strMsg /*= ""*/)
{
    js_proxy_t * p;
    void* ptr = (void*)this;
    p = jsb_get_native_proxy(ptr);
    
    if (p)
    {
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        
        if (callback)
        {
            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
            //JS_IsExceptionPending(cx) && JS_ReportPendingException(cx);
            JS::RootedValue fval(cx, OBJECT_TO_JSVAL(callback));
            JS::RootedValue out(cx);
            
            jsval senderVal = std_string_to_jsval(cx, strMsg);
            
            JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(1, &senderVal);
            
            JS_CallFunctionValue(cx, JS::NullPtr(), fval, args, &out);
        }
    }
}

JS_BINDED_FUNC_IMPL(GameUtils, downloadFile)
{
    if (argc >= 2)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        
        JSString* jsFileUrl = JS::ToString(cx, args.get(1));
        JSStringWrapper w1(jsFileUrl);
        
        JSString* jsFilePath = JS::ToString(cx, args.get(2));
        JSStringWrapper w2(jsFilePath);
        
        int nFileId = args.get(0).toInt32();
        std::string strUrl = w1.get();
        std::string strPath = w2.get();
        
        _downloadFile(nFileId,strUrl, strPath);
        
        return true;
    }
    return false;
}

JS_BINDED_FUNC_IMPL(GameUtils, downloadZipFile)
{
    if (argc == 3)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        
        JSString* jsFileUrl = JS::ToString(cx, args.get(1));
        JSStringWrapper w1(jsFileUrl);
        
        JSString* jsFilePath = JS::ToString(cx, args.get(2));
        JSStringWrapper w2(jsFilePath);
        
        int nFileId = args.get(0).toInt32();
        std::string strUrl = w1.get();
        std::string strPath = w2.get();
        
        _downloadZipFile(nFileId, strUrl, strPath);
        
        return true;
    }
    return false;
}


JS_BINDED_FUNC_IMPL(GameUtils, installGame)
{
    if (argc == 3)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        
        JSString* jsZipFilePath = JS::ToString(cx, args.get(0));
        JSStringWrapper w1(jsZipFilePath);
        
        JSString* jsExtractPath = JS::ToString(cx, args.get(1));
        JSStringWrapper w2(jsExtractPath);
        
        int nId = args.get(2).toInt32();
        std::string strZipFilePath = cocos2d::FileUtils::getInstance()->fullPathForFilename(w1.get());
        std::string strExtractPath = w2.get();
        
        this->_installGame(strZipFilePath, strExtractPath, nId);
        
        return true;
    }
    return false;
}

/**
 *  @brief Register XMLHttpRequest to be usable in JS and add properties and Mehtods.
 *  @param cx   Global Spidermonkey JS Context.
 *  @param global   Global Spidermonkey Javascript object.
 */
void GameUtils::_js_register(JSContext *cx, JS::HandleObject global)
{
    JSClass jsclass = {
        "GameUtils", JSCLASS_HAS_PRIVATE, JS_PropertyStub,
        JS_DeletePropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
        JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub,
        basic_object_finalize
    };
    
    GameUtils::js_class = jsclass;
    static JSPropertySpec props[] = {
        JS_BINDED_PROP_DEF_ACCESSOR(GameUtils, onDownloadFileCompleted),
        JS_BINDED_PROP_DEF_ACCESSOR(GameUtils, onDownloadFileFailed),
        
        JS_BINDED_PROP_DEF_ACCESSOR(GameUtils, onDownloadZipFileCompleted),
        JS_BINDED_PROP_DEF_ACCESSOR(GameUtils, onDownloadZipFileFailed),
        
        JS_BINDED_PROP_DEF_ACCESSOR(GameUtils, onInstallGameCompleted),
        JS_BINDED_PROP_DEF_ACCESSOR(GameUtils, onInstallGameFailed),
        
        JS_PS_END
    };
    
    static JSFunctionSpec funcs[] = {
        JS_BINDED_FUNC_FOR_DEF(GameUtils, downloadFile),
        JS_BINDED_FUNC_FOR_DEF(GameUtils, downloadZipFile),
        JS_BINDED_FUNC_FOR_DEF(GameUtils, installGame),
        
        JS_FN("retain", js_cocos2dx_retain, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("release", js_cocos2dx_release, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        
        JS_FS_END
    };
    
    GameUtils::js_parent = nullptr;
    GameUtils::js_proto = JS_InitClass(cx, global, JS::NullPtr(), &GameUtils::js_class, GameUtils::_js_constructor, 0, props, funcs, nullptr, nullptr);
}

// C++ handle
// Download Normal File
void GameUtils::_downloadFile(int nFileID,const std::string& strURL, const std::string& strPath)
{
    std::string strFilePath = strPath;
    strFilePath.append(getFileNameFromUrl(strURL).c_str());
    
    std::string strTag = StringUtils::format("%s@%d", strFilePath.c_str(), nFileID);
    
    HttpRequest *request = new HttpRequest();
    request->setUrl(strURL.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(GameUtils::_onFileDownloaded));
    request->setTag(strTag.c_str());
    
    HttpClient::getInstance()->send(request);
    request->release();
}

void GameUtils::_onFileDownloaded(HttpClient * pSender, HttpResponse * pResponse)
{
    HttpResponse *response = pResponse;
    
    std::string strTag = response->getHttpRequest()->getTag();
    std::vector<string> lstTag = split(strTag.c_str(), '@');
    std::string strFilePath = lstTag[0];
    int nFileID = atoi(lstTag[1].c_str());
    if (!response || !response->isSucceed())
    {
        string strJsonMsg = StringUtils::format("%d", nFileID);
        _notify(_onDownloadFileFailedCallback,strJsonMsg);
        return;
    }
    
    // Save file to device
    std::vector<char>*buffer = response->getResponseData();
    FILE *pFile;
    pFile = fopen(strFilePath.c_str(), "wb");
    fwrite(buffer->data(), sizeof(char), buffer->size(), pFile);
    fclose(pFile);
    string strJsonMsg = StringUtils::format("{\"FileId\": %d, \"FilePath\": \"%s\"}", nFileID, strFilePath.c_str());
    _notify(_onDownloadFileCompletedCallback, strJsonMsg);
    
}

// Download Zip File
void GameUtils::_downloadZipFile(int nFileId, const std::string &strFileURL, const std::string &strFilePath)
{
    string strFP = strFilePath;
    strFP.append(getFileNameFromUrl(strFileURL).c_str());
    
    string strTag = StringUtils::format("%s@%d", strFP.c_str(), nFileId);
    
    HttpRequest *request = new HttpRequest();
    request->setUrl(strFileURL.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(GameUtils::_onZipFileDownloaded));
    request->setTag(strTag.c_str());
    
    HttpClient::getInstance()->send(request);
    request->release();
}

void GameUtils::_onZipFileDownloaded(HttpClient *pSender, HttpResponse *pResponse)
{
    HttpResponse *response = pResponse;
    
    // Get file info
    string strTag = response->getHttpRequest()->getTag();
    vector<string> vFileInfo = split(strTag.c_str(), '@');
    
    string strFilePath = vFileInfo[0];
    int nFileId = atoi(vFileInfo[1].c_str());
    
    if (!response || !response->isSucceed())
    {
        string strJsonMsg = StringUtils::format("%d", nFileId);
        _notify(_onDownloadZipFileFailedCallback, strJsonMsg);
        
        return;
    }
    
    // Save file to device
    std::vector<char>*buffer = response->getResponseData();
    FILE *pFile;
    pFile = fopen(strFilePath.c_str(), "wb");
    fwrite(buffer->data(), sizeof(char), buffer->size(), pFile);
    fclose(pFile);
    
    if (!ZipHelper::decompress(strFilePath)) {
        string strJsonMsg = StringUtils::format("%d", nFileId);
        _notify(_onDownloadZipFileFailedCallback, strJsonMsg);
    } else {
        // Create Json String Message
        string strJsonMsg = StringUtils::format("{\"FileId\": %d, \"FilePath\": \"%s\"}", nFileId, strFilePath.c_str());
        _notify(_onDownloadZipFileCompletedCallback, strJsonMsg);
    }
    
    // Remove zip file after decompress
    if (_fileUtils->isFileExist(strFilePath)) {
        _fileUtils->removeFile(strFilePath);
    }
}

// Install Game
void GameUtils::_installGame(const string& strFilePath, const string& strExtractPath, int nId /*= -1*/)
{
    AsyncDataZipFile *asyncData = new (std::nothrow) AsyncDataZipFile();
    asyncData->bIsDecompressed = false;
    asyncData->nId = nId;
    asyncData->strFilePath = strFilePath;
    asyncData->strExtractPath = strExtractPath;
    
    AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_IO, CC_CALLBACK_1(GameUtils::_afterInstalledGame, this), (void*) asyncData, [this, asyncData] ()
                                          {
                                              std::string zipFile = asyncData->strFilePath;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                                              auto data = _fileUtils->getDataFromFile(asyncData->strFilePath);
                                              
                                              zipFile = asyncData->strExtractPath + "game.zip";
                                              
                                              FILE* dest = fopen(zipFile.c_str(), "wb");
                                              fwrite(data.getBytes(), 1, data.getSize(), dest);
                                              fclose(dest);
#endif
                                              asyncData->bIsDecompressed = ZipHelper::decompress(zipFile, asyncData->strExtractPath);
                                          });
}

void GameUtils::_afterInstalledGame(void *param) {
    AsyncDataZipFile *asyncData = (AsyncDataZipFile *)param;
    
    if (asyncData) {
        string strJsonMsg = StringUtils::format("{\"GameId\": %d, \"GamePath\": \"%s\"}", asyncData->nId, asyncData->strFilePath.c_str());
        if (asyncData->bIsDecompressed) {
            _notify(_onInstallGameCompletedCallback, strJsonMsg);
        } else {
            _notify(_onInstallGameFailedCallback, strJsonMsg);
        }
    }
}

// Extension
std::string GameUtils::getFileNameFromUrl(const std::string& strURL)
{
    std::string ret = strURL;
    std::size_t found = ret.find_last_of("/");
    ret = ret.substr(found + 1);
    
    return ret;
}

void GameUtils::split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> GameUtils::split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}
