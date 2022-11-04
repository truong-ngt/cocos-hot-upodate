#pragma once
#include "cocos2d.h"

#include "base/CCEventListener.h"
#include "base/CCEventListenerCustom.h"

class EventUpdateManager;
class UpdateManager;

class EventListenerUpdateManager : public cocos2d::EventListenerCustom
{
public:
	friend class UpdateManager;

	static EventListenerUpdateManager* create(UpdateManager* pUpdateManager, const std::function<void(EventUpdateManager*)>& callback);

	/// Overrides
	virtual bool checkAvailable() override;
	virtual EventListenerUpdateManager* clone() override;

CC_CONSTRUCTOR_ACCESS:
	/** Constructor */
	EventListenerUpdateManager();

	/** Initializes event with type and callback function */
	bool init(const UpdateManager *pUpdateManager, const std::function<void(EventUpdateManager*)>& callback);

protected:
	static const std::string LISTENER_ID;

	std::function<void(EventUpdateManager*)> _onUpdateManagerEvent;

	const UpdateManager*_UpdateManager;
};

