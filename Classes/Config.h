#ifndef  _CONFIG_H_
#define  _CONFIG_H_

#include "cocos2d.h"

class Config
{
public:
	const static int conversationHeight = 200;
	~Config();
	static Config* getInstance();
	std::string getLocalLanguage();
	std::string getVoiceLanguage();
	void setLocalLanguage(std::string);
	void setVoiceLanguage(std::string);

private:
	static Config* instance;
	Config();
	std::string localLanguage;
	std::string voiceLanguage;
};

#endif // _CONFIG_H_

