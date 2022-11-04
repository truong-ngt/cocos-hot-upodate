#include "EventUpdateManager.h"
#include "base/ccMacros.h"
#include <functional>

#include "UpdateManager.h"

EventUpdateManager::EventUpdateManager(const std::string& eventName, UpdateManager *manager, const EventCode &code, float percent/* = 0 */, float percentByFile/* = 0*/, const std::string& assetId/* = "" */, const std::string& message/* = "" */, int curle_code/* = CURLE_OK*/, int curlm_code/* = CURLM_OK*/)
	: EventCustom(eventName)
	, _code(code)
	, _manager(manager)
	, _message(message)
	, _assetId(assetId)
	, _curle_code(curle_code)
	, _curlm_code(curlm_code)
	, _percent(percent)
	, _percentByFile(percentByFile)
{
}


