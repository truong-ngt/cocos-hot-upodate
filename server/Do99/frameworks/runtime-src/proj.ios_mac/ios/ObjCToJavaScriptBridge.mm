//
//  Bridge.mm
//  HelloWorld
//
//  Created by Quoc Khanh on 7/20/15.
//
//

#include "ObjCToJavaScriptBridge.h"
#include "cocos2d.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"

void evalString(const char* str)
{
    ScriptingCore::getInstance()->evalString(str);
}
