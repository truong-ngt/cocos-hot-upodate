#pragma once

#include "jsapi.h"
#include "jsfriendapi.h"

void register_jsb_UpdateManager(JSContext* cx, JS::HandleObject global);
void register_jsb_EventUpdateManager(JSContext *cx, JS::HandleObject global);
void register_jsb_EventListenerUpdateManager(JSContext *cx, JS::HandleObject global);



