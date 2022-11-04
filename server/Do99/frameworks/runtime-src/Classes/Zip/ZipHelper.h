#pragma once

#include "cocos2d.h"
#include <string>

using namespace std;

class ZipHelper
{
public:
	static bool decompress(const std::string &strZipPath, const std::string& strExtractPath);
	static bool decompress(const std::string &zip);
	static std::string basename(const std::string& path);
};

