#ifndef  __CONFIG_H__
#define  __CONFIG_H__

#include "cocos2d.h"
#include <vector>

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
private:
	static Config* instance;
	Config();
	std::string localLanguage="en";
	std::string voiceLanguage="en";
	std::vector<std::string>* supportLanguage;
	std::string gameName = "game";
};
#endif // __CONFIG_H__

