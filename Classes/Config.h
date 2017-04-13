#ifndef  __CONFIG_H__
#define  __CONFIG_H__

#include "cocos2d.h"
#include <vector>
#include "sqlite3/include/sqlite3.h"
#pragma comment(lib, "F:/cocos/FictionNovelCore/cocos2d/external/sqlite3/libraries/win32/sqlite3.lib")

class Config
{
public:
	const static int conversationHeight = 200;
	const static int titleHeight = 100;
	~Config();
	static Config* getInstance();
	std::string getLocalLanguage();
	std::string getVoiceLanguage();
	std::vector<std::string>* getSupportLanguage();
	std::string getGameName();
	void setLocalLanguage(std::string);
	void setVoiceLanguage(std::string);
	void setSupportLanguage(std::vector<std::string>*);
	void setGameName(std::string);
	void setDafaultLanguage(std::string,std::string);
	std::string getDefaultTextLanguage();
	std::string getDefaultVoiceLanguage();
private:
	static Config* instance;
	Config();
	std::string localLanguage="en";
	std::string voiceLanguage="en";
	std::vector<std::string>* supportLanguage;
	std::string gameName = "game";
};
#endif // __CONFIG_H__

