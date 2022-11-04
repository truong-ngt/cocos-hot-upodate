#pragma once

#include "cocos2d.h"

#include "jsapi.h"
#include "jsfriendapi.h"

#include "scripting/js-bindings/manual/js_bindings_config.h"
#include "scripting/js-bindings/manual/jsb_helper.h"

#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"

USING_NS_CC;

class VTCUtils : public Ref
{
public: 
	VTCUtils();
	~VTCUtils();

	JS_BINDED_CLASS_GLUE(VTCUtils);
	JS_BINDED_CONSTRUCTOR(VTCUtils);

	JS_BINDED_PROP_ACCESSOR(VTCUtils, onCaptureScreenCompleted);
	JS_BINDED_PROP_ACCESSOR(VTCUtils, onCaptureScreenFailed);

	JS_BINDED_PROP_GET(VTCUtils, captureScreenPath);

	JS_BINDED_FUNC(VTCUtils, captureScreen);
	JS_BINDED_FUNC(VTCUtils, openURL);
	JS_BINDED_FUNC(VTCUtils, retainManual);
	JS_BINDED_FUNC(VTCUtils, releaseManual);

private:
	void _notify(JSObject * callback, const std::string& strMsg = "");

	void _captureScreen(const std::string& strPath);
	void _afterCapture(bool succeed, const std::string& outputFile);

	void _openURL(const std::string& strURL);

private:
	std::string getDirectory(const std::string& path);

private:
	JSContext*					_cx;

	JS::Heap<JSObject*>			_onCaptureScreenCompletedCallback;
	JS::Heap<JSObject*>			_onCaptureScreenFailedCallback;

    FileUtils*                  _fileUtils;
	
    std::string					_captureScreenPath;
};

