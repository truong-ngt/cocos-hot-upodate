#include "VTCUtils.h"

VTCUtils::VTCUtils()
: _cx(ScriptingCore::getInstance()->getGlobalContext())
, _onCaptureScreenCompletedCallback(nullptr)
, _onCaptureScreenFailedCallback(nullptr)

{
    _fileUtils = cocos2d::FileUtils::getInstance();
    _captureScreenPath = "";
}

VTCUtils::~VTCUtils()
{
    JS::RootedValue callback(_cx);
    if (_onCaptureScreenCompletedCallback)
    {
        callback.set(OBJECT_TO_JSVAL(_onCaptureScreenCompletedCallback));
        js_remove_object_root(callback);
    }
    if (_onCaptureScreenFailedCallback)
    {
        callback.set(OBJECT_TO_JSVAL(_onCaptureScreenFailedCallback));
        js_remove_object_root(callback);
    }
}

/**
*  @brief Initialize Object and needed properties.
*
*/
JS_BINDED_CLASS_GLUE_IMPL(VTCUtils);

/**
*  @brief Implementation for the Javascript Constructor
*
*/
JS_BINDED_CONSTRUCTOR_IMPL(VTCUtils)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    VTCUtils* req = new (std::nothrow) VTCUtils();
    
    JS::RootedObject proto(cx, VTCUtils::js_proto);
    JS::RootedObject parentProto(cx, VTCUtils::js_parent);
    JS::RootedObject obj(cx, JS_NewObject(cx, &VTCUtils::js_class, proto, parentProto));
    js_proxy_t *p = jsb_new_proxy(req, obj);
    
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    CC_UNUSED_PARAM(p);
    js_add_FinalizeHook(cx, obj);
    // don't retain it, already retained
#if COCOS2D_DEBUG > 1
    CCLOG("++++++RETAINED++++++ Cpp(XMLHttpRequest): %p - JS: %p", req, obj.get());
#endif // COCOS2D_DEBUG
#else
    // autorelease it
    req->autorelease();
    JS::AddNamedObjectRoot(cx, &p->obj, "XMLHttpRequest");
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
#define GETTER_SETTER_FOR_CALLBACK_PROP(x,y) JS_BINDED_PROP_GET_IMPL(VTCUtils, x)\
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
JS_BINDED_PROP_SET_IMPL(VTCUtils, x)\
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

GETTER_SETTER_FOR_CALLBACK_PROP(onCaptureScreenCompleted, _onCaptureScreenCompletedCallback)
GETTER_SETTER_FOR_CALLBACK_PROP(onCaptureScreenFailed, _onCaptureScreenFailedCallback)

JS_BINDED_PROP_GET_IMPL(VTCUtils, captureScreenPath)
{
	jsval strVal = std_string_to_jsval(cx, _captureScreenPath);

	if (strVal != JSVAL_NULL)
	{
		args.rval().set(strVal);
		return true;
	}
	else
	{
		JS_ReportError(cx, "Error trying to create JSString from data");
		return false;
	}
}

/**
*  @brief destructor for Javascript
*
*/
static void basic_object_finalize(JSFreeOp *freeOp, JSObject *obj)
{
	CCLOG("basic_object_finalize %p ...", obj);
}

void VTCUtils::_notify(JSObject * callback, const std::string& strMsg /*= ""*/)
{
    js_proxy_t * p;
    void* ptr = (void*)this;
    p = jsb_get_native_proxy(ptr);
    
    if(p)
    {
        if (callback)
        {
            JS::RootedObject obj(_cx, p->obj);
            JSAutoCompartment ac(_cx, obj);
            //JS_IsExceptionPending(cx) && JS_ReportPendingException(cx);
            JS::RootedValue callbackVal(_cx, OBJECT_TO_JSVAL(callback));
            JS::RootedValue out(_cx);
            JS_CallFunctionValue(_cx, JS::NullPtr(), callbackVal, JS::HandleValueArray::empty(), &out);
        }
        
    }
}

JS_BINDED_FUNC_IMPL(VTCUtils, captureScreen)
{
	if (argc == 1)
	{
		JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

		JSString* jsPath = JS::ToString(cx, args.get(0));
		JSStringWrapper w1(jsPath);

		std::string strPath = w1.get();
		this->_captureScreen(strPath);

		return true;
	}
	return false;
}

JS_BINDED_FUNC_IMPL(VTCUtils, openURL)
{
	if (argc == 1)
	{
		JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

		JSString* jsURL = JS::ToString(cx, args.get(0));
		JSStringWrapper w1(jsURL);

		std::string strURL = w1.get();
		this->_openURL(strURL);

		return true;
	}
	return false;
}

JS_BINDED_FUNC_IMPL(VTCUtils, retainManual)
{
	if (argc == 0)
	{
		this->retain();

		return true;
	}
	return false;
}

JS_BINDED_FUNC_IMPL(VTCUtils, releaseManual)
{
	if (argc == 0)
	{
		this->release();

		return true;
	}
	return false;
}

/**
*  @brief Register XMLHttpRequest to be usable in JS and add properties and Mehtods.
*  @param cx   Global Spidermonkey JS Context.
*  @param global   Global Spidermonkey Javascript object.
*/
void VTCUtils::_js_register(JSContext *cx, JS::HandleObject global)
{
	JSClass jsclass = {
		"VTCUtils", JSCLASS_HAS_PRIVATE, JS_PropertyStub,
		JS_DeletePropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub,
		basic_object_finalize
	};

	VTCUtils::js_class = jsclass;
	static JSPropertySpec props[] = {

		JS_BINDED_PROP_DEF_ACCESSOR(VTCUtils, onCaptureScreenCompleted),
		JS_BINDED_PROP_DEF_ACCESSOR(VTCUtils, onCaptureScreenFailed),

		JS_BINDED_PROP_DEF_GETTER(VTCUtils, captureScreenPath),

		JS_PS_END
	};

	static JSFunctionSpec funcs[] = {
		JS_BINDED_FUNC_FOR_DEF(VTCUtils, captureScreen),
		JS_BINDED_FUNC_FOR_DEF(VTCUtils, openURL),
		JS_BINDED_FUNC_FOR_DEF(VTCUtils, retainManual),
		JS_BINDED_FUNC_FOR_DEF(VTCUtils, releaseManual),

		JS_FS_END
	};

	VTCUtils::js_parent = nullptr;
	VTCUtils::js_proto = JS_InitClass(cx, global, JS::NullPtr(), &VTCUtils::js_class, VTCUtils::_js_constructor, 0, props, funcs, nullptr, nullptr);
}

// C++ handle
void VTCUtils::_captureScreen(const std::string& strPath) 
{
	cocos2d::log("_captureScreen() called");
	std::string strDir = getDirectory(strPath);
	if (!_fileUtils->isDirectoryExist(strDir))
		_fileUtils->createDirectory(strDir);

	cocos2d::utils::captureScreen(CC_CALLBACK_2(VTCUtils::_afterCapture, this), strPath);
};

void VTCUtils::_afterCapture(bool succeed, const std::string& outputFile)
{
	cocos2d::log("_afterCapture() called");

	if (succeed)
	{
		cocos2d::log("Capture screen success with path: %s !", outputFile.c_str());
		_notify(_onCaptureScreenCompletedCallback, outputFile);
	}
	else
	{
		cocos2d::log("Capture screen failed.");
		_notify(_onCaptureScreenFailedCallback);
	}
}

void VTCUtils::_openURL(const std::string& strURL)
{
	cocos2d::log("_openURL() called : url = %s", strURL.c_str());
	cocos2d::Application::getInstance()->openURL(strURL);
}

std::string VTCUtils::getDirectory(const std::string& path)
{
	size_t found = path.find_last_of("/\\");

	if (std::string::npos != found)
	{
		return path.substr(0, found + 1);
	}
	else
	{
		return path;
	}
}





