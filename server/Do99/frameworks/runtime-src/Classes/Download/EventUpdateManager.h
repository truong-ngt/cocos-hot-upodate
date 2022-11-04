#pragma once
#include "cocos2d.h"

#include "base/CCEvent.h"
#include "base/CCEventCustom.h"

class UpdateManager;

class EventUpdateManager : public cocos2d::EventCustom
{
public:

	friend class UpdateManager;

	//! Update events code
	enum class EventCode
	{
		ALREADY_UP_TO_DATE,
		UPDATE_PROGRESSION,
		UPDATE_FINISHED,
		UPDATE_FAILED,
		ASSETS_UPDATED,
		ERROR_UPDATING,
		ERROR_DECOMPRESS,
	};

	inline EventCode getEventCode() const { return _code; };

	inline int getCURLECode() const { return _curle_code; };

	inline int getCURLMCode() const { return _curlm_code; };

	inline std::string getMessage() const { return _message; };

	inline std::string getAssetId() const { return _assetId; };

	inline UpdateManager* getUpdateManager() const { return _manager; };

	inline float getPercent() const { return _percent; };

	inline float getPercentByFile() const { return _percentByFile; };

CC_CONSTRUCTOR_ACCESS:
	/** Constructor */
	EventUpdateManager(const std::string& eventName, UpdateManager *manager, const EventCode &code, float percent = 0, float percentByFile = 0, const std::string& assetId = "", const std::string& message = "", int curle_code = 0, int curlm_code = 0);
    
private:
	EventCode _code;

	UpdateManager *_manager;

	std::string _message;

	std::string _assetId;

	int _curle_code;

	int _curlm_code;

	float _percent;

	float _percentByFile;
};

