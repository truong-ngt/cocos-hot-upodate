#include "cocos2d.h"

#include "scripting/js-bindings/manual/spidermonkey_specifics.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"

#include "jsb_UpdateManager.h"

#include "UpdateManager.h"
#include "EventUpdateManager.h"
#include "EventListenerUpdateManager.h"

JSClass  *jsb_UpdateManager_class;
JSObject *jsb_UpdateManager_prototype;

bool js_UpdateManager_getUpdateState(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	UpdateManager* cobj = (UpdateManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_UpdateManager_getUpdateState : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getUpdateState();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		
		args.rval().set(jsret);
		return true;
	}

	JS_ReportError(cx, "js_UpdateManager_getUpdateState : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_UpdateManager_checkUpdate(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	UpdateManager* cobj = (UpdateManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_UpdateManager_checkUpdate : Invalid Native Object");
	if (argc == 0) {
		cobj->checkUpdate();
		args.rval().setUndefined();
		return true;
	}

	JS_ReportError(cx, "js_UpdateManager_checkUpdate : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_UpdateManager_getStoragePath(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	UpdateManager* cobj = (UpdateManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_UpdateManager_getStoragePath : Invalid Native Object");
	if (argc == 0) {
		const std::string& ret = cobj->getStoragePath();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		args.rval().set(jsret);
		return true;
	}

	JS_ReportError(cx, "js_UpdateManager_getStoragePath : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_UpdateManager_retain(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	UpdateManager* cobj = (UpdateManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_UpdateManager_retain : Invalid Native Object");
	if (argc == 0) {
		cobj->retain();
		args.rval().setUndefined();
		return true;
	}

	JS_ReportError(cx, "js_UpdateManager_retain : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_UpdateManager_release(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	UpdateManager* cobj = (UpdateManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_UpdateManager_release : Invalid Native Object");
	if (argc == 0) {
		cobj->release();
		args.rval().setUndefined();
		return true;
	}

	JS_ReportError(cx, "js_UpdateManager_release : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_UpdateManager_update(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	UpdateManager* cobj = (UpdateManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_UpdateManager_update : Invalid Native Object");
	if (argc == 0) {
		cobj->update();
		args.rval().setUndefined();
		return true;
	}

	JS_ReportError(cx, "js_UpdateManager_update : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_UpdateManager_downloadFailedAssets(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	UpdateManager* cobj = (UpdateManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_UpdateManager_downloadFailedAssets : Invalid Native Object");
	if (argc == 0) {
		cobj->downloadFailedAssets();
		args.rval().setUndefined();
		return true;
	}

	JS_ReportError(cx, "js_UpdateManager_downloadFailedAssets : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_UpdateManager_setUpdateInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	UpdateManager* cobj = (UpdateManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_UpdateManager_setUpdateInfo : Invalid Native Object");

	bool ok = true;
	if (argc == 1)
	{
		std::string arg0("");
		ok &= jsval_to_std_string(cx, args.get(0), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_UpdateManager_setUpdateInfo : Error processing arguments");

		cobj->setUpdateInfo(arg0);
		args.rval().setUndefined();
		return true;
	}

	JS_ReportError(cx, "js_UpdateManager_setUpdateInfo : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_UpdateManager_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, args.get(0), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_UpdateManager_create : Error processing arguments");
		auto ret = UpdateManager::create(arg0);
        
        js_type_class_t *typeClass = js_get_type_from_native<UpdateManager>(ret);
        
        // link the native object with the javascript object
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "UpdateManager"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
	}
	JS_ReportError(cx, "js_UpdateManager_create : wrong number of arguments");
	return false;
}

bool js_UpdateManager_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	bool ok = true;
	std::string arg0;
	ok &= jsval_to_std_string(cx, args.get(0), &arg0);
	JSB_PRECONDITION2(ok, cx, false, "js_UpdateManager_constructor : Error processing arguments");
	UpdateManager* cobj = new (std::nothrow) UpdateManager(arg0);
    
    js_type_class_t *typeClass = js_get_type_from_native<UpdateManager>(cobj);
    
    // link the native object with the javascript object
	 JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "UpdateManager"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	args.rval().setBoolean(true);
	return true;
}

void js_UpdateManager_finalize(JSFreeOp *fop, JSObject *obj) {
	CCLOGINFO("jsbindings: finalizing JS object %p (UpdateManager)", obj);
}

void register_jsb_UpdateManager(JSContext *cx, JS::HandleObject global) {
	jsb_UpdateManager_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_UpdateManager_class->name = "UpdateManager";
	jsb_UpdateManager_class->addProperty = JS_PropertyStub;
	jsb_UpdateManager_class->delProperty = JS_DeletePropertyStub;
	jsb_UpdateManager_class->getProperty = JS_PropertyStub;
	jsb_UpdateManager_class->setProperty = JS_StrictPropertyStub;
	jsb_UpdateManager_class->enumerate = JS_EnumerateStub;
	jsb_UpdateManager_class->resolve = JS_ResolveStub;
	jsb_UpdateManager_class->convert = JS_ConvertStub;
	jsb_UpdateManager_class->finalize = js_UpdateManager_finalize;
	jsb_UpdateManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_PS_END
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getUpdateState", js_UpdateManager_getUpdateState, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("checkUpdate", js_UpdateManager_checkUpdate, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setUpdateInfo", js_UpdateManager_setUpdateInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getStoragePath", js_UpdateManager_getStoragePath, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("update", js_UpdateManager_update, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("retain", js_UpdateManager_retain, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("release", js_UpdateManager_release, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("downloadFailedAssets", js_UpdateManager_downloadFailedAssets, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_UpdateManager_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_UpdateManager_prototype = JS_InitClass(
		cx, global,
		JS::NullPtr(),
		jsb_UpdateManager_class,
		js_UpdateManager_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	
    JS::RootedObject proto(cx, jsb_UpdateManager_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "UpdateManager"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<UpdateManager>(cx, jsb_UpdateManager_class, proto, JS::NullPtr());
}

JSClass  *jsb_EventUpdateManager_class;
JSObject *jsb_EventUpdateManager_prototype;

bool js_EventUpdateManager_getUpdateManager(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EventUpdateManager* cobj = (EventUpdateManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_EventUpdateManager_getUpdateManager : Invalid Native Object");
	if (argc == 0) {
		UpdateManager* ret = cobj->getUpdateManager();
		jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<UpdateManager>(cx, (UpdateManager*)ret));
        } else {
            jsret = JSVAL_NULL;
        }
	
		args.rval().set(jsret);
		return true;
	}

	JS_ReportError(cx, "js_EventUpdateManager_getUpdateManager : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_EventUpdateManager_getAssetId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EventUpdateManager* cobj = (EventUpdateManager*)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_EventUpdateManager_getAssetId : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getAssetId();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		args.rval().set(jsret);
		return true;
	}

	JS_ReportError(cx, "js_EventUpdateManager_getAssetId : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_EventUpdateManager_getCURLECode(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EventUpdateManager* cobj = (EventUpdateManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_EventUpdateManager_getCURLECode : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getCURLECode();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		args.rval().set(jsret);
		return true;
	}

	JS_ReportError(cx, "js_EventUpdateManager_getCURLECode : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_EventUpdateManager_getMessage(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EventUpdateManager* cobj = (EventUpdateManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_EventUpdateManager_getMessage : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getMessage();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		args.rval().set(jsret);
		return true;
	}

	JS_ReportError(cx, "js_EventUpdateManager_getMessage : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_EventUpdateManager_getCURLMCode(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EventUpdateManager* cobj = (EventUpdateManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_EventUpdateManager_getCURLMCode : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getCURLMCode();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		args.rval().set(jsret);
		return true;
	}

	JS_ReportError(cx, "js_EventUpdateManager_getCURLMCode : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_EventUpdateManager_getPercentByFile(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EventUpdateManager* cobj = (EventUpdateManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_EventUpdateManager_getPercentByFile : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getPercentByFile();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		args.rval().set(jsret);
		return true;
	}

	JS_ReportError(cx, "js_EventUpdateManager_getPercentByFile : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_EventUpdateManager_getEventCode(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EventUpdateManager* cobj = (EventUpdateManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_cocos2dx_extension_EventAssetsManagerEx_getEventCode : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getEventCode();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		args.rval().set(jsret);
		return true;
	}

	JS_ReportError(cx, "js_EventUpdateManager_getEventCode : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_EventUpdateManager_getPercent(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	EventUpdateManager* cobj = (EventUpdateManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_EventUpdateManagerx_getPercent : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getPercent();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		args.rval().set(jsret);
		return true;
	}

	JS_ReportError(cx, "js_EventUpdateManager_getPercent : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_EventUpdateManager_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	bool ok = true;
	std::string arg0;
    UpdateManager* arg1 = nullptr;
	EventUpdateManager::EventCode arg2;
    do {
        if (args.get(1).isNull()) { arg1 = nullptr; break; }
        if (!args.get(1).isObject()) { ok = false; break; }
        js_proxy_t *jsProxy;
        JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
        jsProxy = jsb_get_js_proxy(tmpObj);
        arg1 = (UpdateManager*)(jsProxy ? jsProxy->ptr : NULL);
        JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
    } while (0);
    ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
	JSB_PRECONDITION2(ok, cx, false, "js_EventUpdateManager_constructor : Error processing arguments");
	EventUpdateManager* cobj = new (std::nothrow) EventUpdateManager(arg0, arg1, arg2);

    js_type_class_t *typeClass = js_get_type_from_native<EventUpdateManager>(cobj);
    
    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "EventUpdateManager"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocos2d_EventCustom_prototype;

void js_EventUpdateManager_finalize(JSFreeOp *fop, JSObject *obj) {
	CCLOGINFO("jsbindings: finalizing JS object %p (EventUpdateManager)", obj);
}

void register_jsb_EventUpdateManager(JSContext *cx, JS::HandleObject global) {
	jsb_EventUpdateManager_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_EventUpdateManager_class->name = "EventUpdateManager";
	jsb_EventUpdateManager_class->addProperty = JS_PropertyStub;
	jsb_EventUpdateManager_class->delProperty = JS_DeletePropertyStub;
	jsb_EventUpdateManager_class->getProperty = JS_PropertyStub;
	jsb_EventUpdateManager_class->setProperty = JS_StrictPropertyStub;
	jsb_EventUpdateManager_class->enumerate = JS_EnumerateStub;
	jsb_EventUpdateManager_class->resolve = JS_ResolveStub;
	jsb_EventUpdateManager_class->convert = JS_ConvertStub;
	jsb_EventUpdateManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		JS_PS_END
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getUpdateManager", js_EventUpdateManager_getUpdateManager, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getAssetId", js_EventUpdateManager_getAssetId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCURLECode", js_EventUpdateManager_getCURLECode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getMessage", js_EventUpdateManager_getMessage, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCURLMCode", js_EventUpdateManager_getCURLMCode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPercentByFile", js_EventUpdateManager_getPercentByFile, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getEventCode", js_EventUpdateManager_getEventCode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPercent", js_EventUpdateManager_getPercent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;
    
    JS::RootedObject parent_proto(cx, jsb_cocos2d_EventCustom_prototype);
	jsb_EventUpdateManager_prototype = JS_InitClass(
		cx, global,
		JS::RootedObject(cx, jsb_cocos2d_EventCustom_prototype),
		jsb_EventUpdateManager_class,
		js_EventUpdateManager_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
    
    JS::RootedObject proto(cx, jsb_EventUpdateManager_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "EventUpdateManager"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<EventUpdateManager>(cx, jsb_EventUpdateManager_class, proto, parent_proto);
}

JSClass  *jsb_EventListenerUpdateManager_class;
JSObject *jsb_EventListenerUpdateManager_prototype;

bool js_EventListenerUpdateManager_init(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    EventListenerUpdateManager* cobj = (EventListenerUpdateManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2(cobj, cx, false, "js_EventListenerUpdateManager_init : Invalid Native Object");
    if (argc == 2) {
        const UpdateManager* arg0 = nullptr;
        std::function<void (EventUpdateManager *)> arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (const UpdateManager*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if(JS_TypeOfValue(cx, args.get(1)) == JSTYPE_FUNCTION)
            {
                JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(1)));
                auto lambda = [=](EventUpdateManager* larg0) -> void {
                    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                    jsval largv[1];
                    do {
                        if (larg0) {
                            js_type_class_t* typeClass = js_get_type_from_native<EventUpdateManager>(larg0);
                            largv[0] = OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(cx, larg0, typeClass, "EventUpdateManager"));
                        } else {
                            largv[0] = JSVAL_NULL;
                        }
                    } while (0);
                    JS::RootedValue rval(cx);
                    bool succeed = func->invoke(1, &largv[0], &rval);
                    if (!succeed && JS_IsExceptionPending(cx)) {
                        JS_ReportPendingException(cx);
                    }
                    removeJSObject(cx, larg0);
                };
                arg1 = lambda;
            }
            else
            {
                arg1 = nullptr;
            }
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_EventListenerUpdateManager_init : Error processing arguments");
        bool ret = cobj->init(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    
    JS_ReportError(cx, "js_EventListenerUpdateManager_init : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}

bool js_EventListenerUpdateManager_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        UpdateManager* arg0 = nullptr;
        std::function<void(EventUpdateManager *)> arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (UpdateManager*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if(JS_TypeOfValue(cx, args.get(1)) == JSTYPE_FUNCTION)
            {
                JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(1)));
                auto lambda = [=](EventUpdateManager* larg0) -> void {
                    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                    jsval largv[1];
                    do {
                        if (larg0) {
                            js_type_class_t* typeClass = js_get_type_from_native<EventUpdateManager>(larg0);
                            largv[0] = OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(cx, larg0, typeClass, "EventUpdateManager"));
                        } else {
                            largv[0] = JSVAL_NULL;
                        }
                    } while (0);
                    JS::RootedValue rval(cx);
                    bool succeed = func->invoke(1, &largv[0], &rval);
                    if (!succeed && JS_IsExceptionPending(cx)) {
                        JS_ReportPendingException(cx);
                    }
                    removeJSObject(cx, larg0);
                };
                arg1 = lambda;
            }
            else
            {
                arg1 = nullptr;
            }
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_EventListenerUpdateManager_create : Error processing arguments");
        EventListenerUpdateManager* ret = EventListenerUpdateManager::create(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        if (ret) {
            JS::RootedObject jsobj(cx, js_get_or_create_jsobject<EventListenerUpdateManager>(cx, ret));
            jsret = OBJECT_TO_JSVAL(jsobj);
        } else {
            jsret = JSVAL_NULL;
        }
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_EventListenerUpdateManager_create : wrong number of arguments");
    return false;
}

extern JSObject *jsb_cocos2d_EventListenerCustom_prototype;

void js_EventListenerUpdateManager_finalize(JSFreeOp *fop, JSObject *obj) {
	CCLOGINFO("jsbindings: finalizing JS object %p (js_EventListenerUpdateManager)", obj);
}

void register_jsb_EventListenerUpdateManager(JSContext *cx, JS::HandleObject global) {
	jsb_EventListenerUpdateManager_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_EventListenerUpdateManager_class->name = "EventListenerUpdateManager";
	jsb_EventListenerUpdateManager_class->addProperty = JS_PropertyStub;
	jsb_EventListenerUpdateManager_class->delProperty = JS_DeletePropertyStub;
	jsb_EventListenerUpdateManager_class->getProperty = JS_PropertyStub;
	jsb_EventListenerUpdateManager_class->setProperty = JS_StrictPropertyStub;
	jsb_EventListenerUpdateManager_class->enumerate = JS_EnumerateStub;
	jsb_EventListenerUpdateManager_class->resolve = JS_ResolveStub;
	jsb_EventListenerUpdateManager_class->convert = JS_ConvertStub;
	jsb_EventListenerUpdateManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		JS_PS_END
	};

    static JSFunctionSpec funcs[] = {
        JS_FN("init", js_EventListenerUpdateManager_init, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("create", js_EventListenerUpdateManager_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    static JSFunctionSpec st_funcs[] = {
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_EventListenerCustom_prototype);
    jsb_EventListenerUpdateManager_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_EventListenerUpdateManager_class,
        NULL, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    
    JS::RootedObject proto(cx, jsb_EventListenerUpdateManager_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "EventListenerUpdateManager"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<EventListenerUpdateManager>(cx, jsb_EventListenerUpdateManager_class, proto, parent_proto);
}
