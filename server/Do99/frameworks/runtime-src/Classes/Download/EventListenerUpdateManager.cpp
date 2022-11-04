#include "EventListenerUpdateManager.h"

#include "EventUpdateManager.h"
#include "UpdateManager.h"

const std::string EventListenerUpdateManager::LISTENER_ID = "__update_manager_";

EventListenerUpdateManager::EventListenerUpdateManager()
: _onUpdateManagerEvent(nullptr)
, _UpdateManager(nullptr)
{
}

EventListenerUpdateManager* EventListenerUpdateManager::create(UpdateManager *pUpdateManager, const std::function<void(EventUpdateManager*)>& callback)
{
	EventListenerUpdateManager* ret = new (std::nothrow) EventListenerUpdateManager();
	if (ret && ret->init(pUpdateManager, callback))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool EventListenerUpdateManager::init(const UpdateManager *pUpdateManager, const std::function<void(EventUpdateManager*)>& callback)
{
	bool ret = false;

	_UpdateManager = pUpdateManager;
	_onUpdateManagerEvent = callback;

	auto func = [this](cocos2d::EventCustom *event) -> void
	{
		EventUpdateManager *eventUpdateManager = dynamic_cast<EventUpdateManager*>(event);
		_onUpdateManagerEvent(eventUpdateManager);
	};
	std::string pointer = cocos2d::StringUtils::format("%p", pUpdateManager);
	if (EventListenerCustom::init(LISTENER_ID + pointer, func))
	{
		ret = true;
	}
	return ret;
}

EventListenerUpdateManager* EventListenerUpdateManager::clone()
{
	EventListenerUpdateManager* ret = new (std::nothrow) EventListenerUpdateManager();
	if (ret && ret->init(_UpdateManager, _onUpdateManagerEvent))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool EventListenerUpdateManager::checkAvailable()
{
	bool ret = false;
	if (EventListener::checkAvailable() && _UpdateManager != nullptr && _onUpdateManagerEvent != nullptr)
	{
		ret = true;
	}
	return ret;
}
