/*
* Created by James Chen
* Copyright (c) 2013-2014 Chukong Technologies Inc.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

//#include "scripting/js-bindings/manual/network/jsb_websocket.h"
#include "jsb_CustomWebsocket.h"
#include "base/ccUTF8.h"
#include "base/CCDirector.h"
#include "CustomWebSocket.h"
#include "platform/CCPlatformMacros.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/manual/spidermonkey_specifics.h"

using namespace mNetwork;

/*
[Constructor(in DOMString url, in optional DOMString protocols)]
[Constructor(in DOMString url, in optional DOMString[] protocols)]
interface CustomWebSocket {
readonly attribute DOMString url;

// ready state
const unsigned short CONNECTING = 0;
const unsigned short OPEN = 1;
const unsigned short CLOSING = 2;
const unsigned short CLOSED = 3;
readonly attribute unsigned short readyState;
readonly attribute unsigned long bufferedAmount;

// networking
attribute Function onopen;
attribute Function onmessage;
attribute Function onerror;
attribute Function onclose;
readonly attribute DOMString protocol;
void send(in DOMString data);
void close();
};
CustomWebSocket implements EventTarget;
*/

class JSB_CustomWebSocketDelegate : public CustomWebSocket::Delegate
{
public:

	JSB_CustomWebSocketDelegate()
	{
		JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		_JSDelegate.construct(cx);
	}

	~JSB_CustomWebSocketDelegate()
	{
		_JSDelegate.destroyIfConstructed();
	}

	virtual void onOpen(CustomWebSocket* ws)
	{
		js_proxy_t * p = jsb_get_native_proxy(ws);
		if (!p) return;

		if (cocos2d::Director::getInstance() == nullptr || cocos2d::ScriptEngineManager::getInstance() == nullptr)
			return;

		JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

		JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		JS::RootedObject jsobj(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
		JS::RootedValue vp(cx);
		vp = c_string_to_jsval(cx, "open");
		JS_SetProperty(cx, jsobj, "type", vp);

		jsval args = OBJECT_TO_JSVAL(jsobj);

		ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate.ref()), "onopen", 1, &args);
	}

	virtual void onMessage(CustomWebSocket* ws, const CustomWebSocket::Data& data)
	{
		js_proxy_t * p = jsb_get_native_proxy(ws);
		if (p == nullptr) return;

		if (cocos2d::Director::getInstance() == nullptr || cocos2d::ScriptEngineManager::getInstance() == nullptr)
			return;

		JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

		JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		JS::RootedObject jsobj(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
		JS::RootedValue vp(cx);
		vp = c_string_to_jsval(cx, "message");
		JS_SetProperty(cx, jsobj, "type", vp);

		JS::RootedValue args(cx, OBJECT_TO_JSVAL(jsobj));
		if (data.isBinary)
		{// data is binary
			JS::RootedObject buffer(cx, JS_NewArrayBuffer(cx, static_cast<uint32_t>(data.len)));
			if (data.len > 0)
			{
				uint8_t* bufdata = JS_GetArrayBufferData(buffer);
				memcpy((void*)bufdata, (void*)data.bytes, data.len);
			}
			JS::RootedValue dataVal(cx);
			dataVal = OBJECT_TO_JSVAL(buffer);
			JS_SetProperty(cx, jsobj, "data", dataVal);
		}
		else
		{// data is string
			JS::RootedValue dataVal(cx);
			if (strlen(data.bytes) == 0 && data.len > 0)
			{// String with 0x00 prefix
				dataVal = STRING_TO_JSVAL(JS_NewStringCopyN(cx, data.bytes, data.len));
			}
			else
			{// Normal string
				dataVal = c_string_to_jsval(cx, data.bytes);
			}
			if (dataVal.isNullOrUndefined())
			{
				ws->closeAsync();
				return;
			}
			JS_SetProperty(cx, jsobj, "data", dataVal);
		}

		ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate.ref()), "onmessage", 1, args.address());
	}

	virtual void onClose(CustomWebSocket* ws)
	{
		js_proxy_t * p = jsb_get_native_proxy(ws);
		if (!p) return;

		if (cocos2d::Director::getInstance() != nullptr && cocos2d::Director::getInstance()->getRunningScene() && cocos2d::ScriptEngineManager::getInstance() != nullptr)
		{
			JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

			JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
			JS::RootedObject jsobj(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
			JS::RootedValue vp(cx);
			vp = c_string_to_jsval(cx, "close");
			JS_SetProperty(cx, jsobj, "type", vp);

			JS::RootedValue args(cx, OBJECT_TO_JSVAL(jsobj));
			ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate.ref()), "onclose", 1, args.address());

			auto copy = &p->obj;
			JS::RemoveObjectRoot(cx, copy);
			jsb_remove_proxy(p);
		}

		// Delete CustomWebSocket instance
		CC_SAFE_DELETE(ws);
		// Delete self at last while websocket was closed.
		delete this;
	}

	virtual void onError(CustomWebSocket* ws, const CustomWebSocket::ErrorCode& error)
	{
		js_proxy_t * p = jsb_get_native_proxy(ws);
		if (!p) return;

		if (cocos2d::Director::getInstance() == nullptr || cocos2d::ScriptEngineManager::getInstance() == nullptr)
			return;

		JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

		JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		JS::RootedObject jsobj(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
		JS::RootedValue vp(cx);
		vp = c_string_to_jsval(cx, "error");
		JS_SetProperty(cx, jsobj, "type", vp);

		JS::RootedValue args(cx, OBJECT_TO_JSVAL(jsobj));

		ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate.ref()), "onerror", 1, args.address());
	}

	void setJSDelegate(JS::HandleObject pJSDelegate)
	{
		_JSDelegate.ref() = pJSDelegate;
	}
private:
	mozilla::Maybe<JS::PersistentRootedObject> _JSDelegate;
};

JSClass  *js_cocos2dx_customwebsocket_class;
JSObject *js_cocos2dx_customwebsocket_prototype;

void js_cocos2dx_CustomWebSocket_finalize(JSFreeOp *fop, JSObject *obj)
{
	CCLOG("jsbindings: finalizing JS object %p (CustomWebSocket)", obj);
}

bool js_cocos2dx_CustomWebSocket_send(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs argv = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, argv.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	CustomWebSocket* cobj = (CustomWebSocket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "Invalid Native Object");

	if (argc == 1)
	{
		if (argv[0].isString())
		{
			ssize_t len = JS_GetStringLength(argv[0].toString());
			std::string data;
			jsval_to_std_string(cx, argv[0], &data);

			if (data.empty() && len > 0)
			{
				CCLOGWARN("Text message to send is empty, but its length is greater than 0!");
				//FIXME: Note that this text message contains '0x00' prefix, so its length calcuted by strlen is 0.
				// we need to fix that if there is '0x00' in text message,
				// since javascript language could support '0x00' inserted at the beginning or the middle of text message
			}

			cobj->send(data);
		}
		else if (argv[0].isObject())
		{
			uint8_t *bufdata = NULL;
			uint32_t len = 0;

			JS::RootedObject jsobj(cx, argv[0].toObjectOrNull());
			if (JS_IsArrayBufferObject(jsobj))
			{
				bufdata = JS_GetArrayBufferData(jsobj);
				len = JS_GetArrayBufferByteLength(jsobj);
			}
			else if (JS_IsArrayBufferViewObject(jsobj))
			{
				bufdata = (uint8_t*)JS_GetArrayBufferViewData(jsobj);
				len = JS_GetArrayBufferViewByteLength(jsobj);
			}

			cobj->send(bufdata, len);
		}
		else
		{
			JS_ReportError(cx, "data type to be sent is unsupported.");
			return false;
		}

		argv.rval().setUndefined();

		return true;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return true;
}

bool js_cocos2dx_CustomWebSocket_close(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	CustomWebSocket* cobj = (CustomWebSocket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "Invalid Native Object");

	if (argc == 0)
	{
		cobj->closeAsync();
		args.rval().setUndefined();
		return true;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_cocos2dx_CustomWebSocket_exists(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	if (obj && argc == 0)
	{
		if (proxy)
		{
			jsval jsret = JSVAL_NULL;
			jsret = BOOLEAN_TO_JSVAL(true);
			args.rval().set(jsret);
			return true;
		}
	}

	jsval jsret = JSVAL_NULL;
	jsret = BOOLEAN_TO_JSVAL(false);
	args.rval().set(jsret);
	return false;
}

bool js_cocos2dx_CustomWebSocket_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

	if (argc == 1 || argc == 2 || argc == 3)
	{
		std::string url("");

		do
		{
			bool ok = jsval_to_std_string(cx, args.get(0), &url);
			JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		} while (0);

		JS::RootedObject proto(cx, js_cocos2dx_customwebsocket_prototype);
		JS::RootedObject obj(cx, JS_NewObject(cx, js_cocos2dx_customwebsocket_class, proto, JS::NullPtr()));
		//JS::RootedObject obj(cx, JS_NewObjectForConstructor(cx, js_cocos2dx_customwebsocket_class, args));

		CustomWebSocket* cobj = new (std::nothrow) CustomWebSocket();
		JSB_CustomWebSocketDelegate* delegate = new (std::nothrow) JSB_CustomWebSocketDelegate();
		delegate->setJSDelegate(obj);

		if (argc == 2)
		{
			std::vector<std::string> protocols;

			if (args.get(1).isString())
			{
				std::string cookie("");
				do
				{
					bool ok = jsval_to_std_string(cx, args.get(1), &cookie);
					JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
				} while (0);
				cobj->init(*delegate, url, cookie, nullptr);
			}
			else if (args.get(1).isObject())
			{
				bool ok = true;
				JS::RootedObject arg2(cx, args.get(1).toObjectOrNull());
				JSB_PRECONDITION(JS_IsArrayObject(cx, arg2), "Object must be an array");

				uint32_t len = 0;
				JS_GetArrayLength(cx, arg2, &len);

				for (uint32_t i = 0; i< len; i++)
				{
					JS::RootedValue valarg(cx);
					JS_GetElement(cx, arg2, i, &valarg);
					std::string protocol;
					do
					{
						ok = jsval_to_std_string(cx, valarg, &protocol);
						JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
					} while (0);

					protocols.push_back(protocol);
				}
				cobj->init(*delegate, url, &protocols);
			}
		}
		else if (argc == 3)
		{
			std::vector<std::string> protocols;
			std::string cookie("");
			if (args.get(1).isString())
			{
				do
				{
					bool ok = jsval_to_std_string(cx, args.get(2), &cookie);
				} while (0);
			}

			if (args.get(2).isObject())
			{
				bool ok = true;
				JS::RootedObject arg2(cx, args.get(2).toObjectOrNull());
				JSB_PRECONDITION(JS_IsArrayObject(cx, arg2), "Object must be an array");

				uint32_t len = 0;
				JS_GetArrayLength(cx, arg2, &len);

				for (uint32_t i = 0; i < len; i++)
				{
					JS::RootedValue valarg(cx);
					JS_GetElement(cx, arg2, i, &valarg);
					std::string protocol("");
					do
					{
						ok = jsval_to_std_string(cx, valarg, &protocol);
						JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
					} while (0);
					protocols.push_back(protocol);
				}
			}
			cobj->init(*delegate, url, cookie, &protocols);
		}
		else
		{
			cobj->init(*delegate, url);
		}

		JS_DefineProperty(cx, obj, "URL", args.get(0), JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_READONLY);

		JS_DefineProperty(cx, obj, "COOKIE", args.get(1), JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_READONLY);
		//protocol not support yet (always return "")
		JS::RootedValue jsprotocol(cx, c_string_to_jsval(cx, ""));
		JS_DefineProperty(cx, obj, "protocol", jsprotocol, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_READONLY);

		// link the native object with the javascript object
		js_proxy_t *p = jsb_new_proxy(cobj, obj);
		JS::AddNamedObjectRoot(cx, &p->obj, "CustomWebSocket");

		args.rval().set(OBJECT_TO_JSVAL(obj));
		return true;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

static bool js_cocos2dx_CustomWebSocket_get_readyState(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject jsobj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
	CustomWebSocket* cobj = (CustomWebSocket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "Invalid Native Object");

	if (cobj)
	{
		args.rval().set(INT_TO_JSVAL((int)cobj->getReadyState()));
		return true;
	}
	else
	{
		JS_ReportError(cx, "Error: CustomWebSocket instance is invalid.");
		return false;
	}
}

void register_jsb_CustomWebSocket(JSContext *cx, JS::HandleObject global)
{
	js_cocos2dx_customwebsocket_class = (JSClass *)calloc(1, sizeof(JSClass));
	js_cocos2dx_customwebsocket_class->name = "CustomWebSocket";
	js_cocos2dx_customwebsocket_class->addProperty = JS_PropertyStub;
	js_cocos2dx_customwebsocket_class->delProperty = JS_DeletePropertyStub;
	js_cocos2dx_customwebsocket_class->getProperty = JS_PropertyStub;
	js_cocos2dx_customwebsocket_class->setProperty = JS_StrictPropertyStub;
	js_cocos2dx_customwebsocket_class->enumerate = JS_EnumerateStub;
	js_cocos2dx_customwebsocket_class->resolve = JS_ResolveStub;
	js_cocos2dx_customwebsocket_class->convert = JS_ConvertStub;
	js_cocos2dx_customwebsocket_class->finalize = js_cocos2dx_CustomWebSocket_finalize;
	js_cocos2dx_customwebsocket_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		JS_PSG("readyState", js_cocos2dx_CustomWebSocket_get_readyState, JSPROP_ENUMERATE | JSPROP_PERMANENT),
		JS_PS_END
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("send", js_cocos2dx_CustomWebSocket_send, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("close", js_cocos2dx_CustomWebSocket_close, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("exists", js_cocos2dx_CustomWebSocket_exists, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FS_END
	};

	js_cocos2dx_customwebsocket_prototype = JS_InitClass(
		cx, global,
		JS::NullPtr(),
		js_cocos2dx_customwebsocket_class,
		js_cocos2dx_CustomWebSocket_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);

	JS::RootedObject jsclassObj(cx, anonEvaluate(cx, global, "(function () { return CustomWebSocket; })()").toObjectOrNull());

	JS_DefineProperty(cx, jsclassObj, "CONNECTING", (int)CustomWebSocket::State::CONNECTING, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_READONLY);
	JS_DefineProperty(cx, jsclassObj, "OPEN", (int)CustomWebSocket::State::OPEN, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_READONLY);
	JS_DefineProperty(cx, jsclassObj, "CLOSING", (int)CustomWebSocket::State::CLOSING, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_READONLY);
	JS_DefineProperty(cx, jsclassObj, "CLOSED", (int)CustomWebSocket::State::CLOSED, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_READONLY);
}
