/****************************************************************************
Copyright (c) 2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "js_SpriteWithBase64Str_bindings.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "cocos/network/HttpClient.h"
#include "cocos/base/base64.h"

USING_NS_CC;

// 1. Create object normal in C++
class SpriteWithBase64Str : public Sprite
{
public:
	SpriteWithBase64Str();
	~SpriteWithBase64Str();

	static SpriteWithBase64Str* create(const std::string& strBase64encode);
protected:
	bool initWithBase64String(const std::string& strBase64encode);
};

SpriteWithBase64Str::SpriteWithBase64Str()
{
}

SpriteWithBase64Str::~SpriteWithBase64Str()
{
}

SpriteWithBase64Str* SpriteWithBase64Str::create(const std::string& stdBase64Encode)
{
	log("SpriteWithBase64Str : create");
	SpriteWithBase64Str* sprite = new (std::nothrow) SpriteWithBase64Str();
	if (sprite && sprite->initWithBase64String(stdBase64Encode))
	{
		sprite->autorelease();
		return sprite;
	}
	else
	{
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
}

bool SpriteWithBase64Str::initWithBase64String(const std::string& strBase64encode)
{
	log("SpriteWithBase64Str : initWithBase64String");

	int len = 0;
	unsigned char * buffer = nullptr;
	len = base64Decode((unsigned char*)strBase64encode.c_str(), (unsigned int)strBase64encode.length(), &buffer);

	auto img = new Image();
	if (!img->initWithImageData(buffer, len))
	{
		return false;
	}

	auto *texture = new Texture2D();
	texture->initWithImage(img);

	if (!texture)
	{
		return false;
	}

	return this->initWithTexture(texture);
}

//2. js_binding to create js object
static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	args.rval().setBoolean(true);
	return true;
}

JSClass  *jsb_SpriteWithBase64Str_class;
JSObject *jsb_SpriteWithBase64Str_prototype;

bool js_cocos2dx_SpriteWithBase64Str_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, args.get(0), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_SpriteWithBase64Str_create : Error processing arguments");
        auto ret = SpriteWithBase64Str::create(arg0);
        js_type_class_t *typeClass = js_get_type_from_native<SpriteWithBase64Str>(ret);
        
        // link the native object with the javascript object
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "SpriteWithBase64Str"));
        
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_SpriteWithBase64Str_create : wrong number of arguments");
    return false;
}

void js_SpriteWithBase64Str_finalize(JSFreeOp *fop, JSObject *obj) {
	CCLOGINFO("jsbindings: finalizing JS object %p (SpriteWithBase64Str)", obj);
}

bool jsb_SpriteWithBase64Str_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	bool ok = true;
    
	SpriteWithBase64Str* cobj = new (std::nothrow) SpriteWithBase64Str();
    
    js_type_class_t *typeClass = js_get_type_from_native<SpriteWithBase64Str>(cobj);
    
    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "SpriteWithBase64Str"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocos2d_Sprite_prototype;

void js_register_cocos2dx_SpriteWithBase64Str(JSContext *cx, JS::HandleObject global) {
	jsb_SpriteWithBase64Str_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_SpriteWithBase64Str_class->name = "SpriteWithBase64Str";
	jsb_SpriteWithBase64Str_class->addProperty = JS_PropertyStub;
	jsb_SpriteWithBase64Str_class->delProperty = JS_DeletePropertyStub;
	jsb_SpriteWithBase64Str_class->getProperty = JS_PropertyStub;
	jsb_SpriteWithBase64Str_class->setProperty = JS_StrictPropertyStub;
	jsb_SpriteWithBase64Str_class->enumerate = JS_EnumerateStub;
	jsb_SpriteWithBase64Str_class->resolve = JS_ResolveStub;
	jsb_SpriteWithBase64Str_class->convert = JS_ConvertStub;
	jsb_SpriteWithBase64Str_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		JS_PS_END
	};

	static JSFunctionSpec funcs[]{
		JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_SpriteWithBase64Str_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

     JS::RootedObject parent_proto(cx, jsb_cocos2d_Sprite_prototype);
	jsb_SpriteWithBase64Str_prototype = JS_InitClass(
		cx, global,
		parent_proto,
		jsb_SpriteWithBase64Str_class,
		jsb_SpriteWithBase64Str_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	
    JS::RootedObject proto(cx, jsb_SpriteWithBase64Str_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "SpriteWithBase64Str"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<SpriteWithBase64Str>(cx, jsb_SpriteWithBase64Str_class, proto, parent_proto);
}

void register_SpriteWithBase64Str_bindings(JSContext *cx, JS::HandleObject global)
{
	JS::RootedObject ccobj(cx);
	get_or_create_js_obj(cx, global, "cc", &ccobj);
	js_register_cocos2dx_SpriteWithBase64Str(cx, ccobj);
}






