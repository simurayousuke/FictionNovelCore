#ifndef _LOCAL_H
#define _LOCAL_H

#include "cocos2d.h"
#include "Config.h"

class Local
{
public:
	static std::string getDefaultFont();
	static std::string start;
	static std::string load;
	static std::string settings;
	static std::string exit;
	static std::string about;
	static std::string getDefaultFont(std::string lang);
};
#endif _LOCAL_H