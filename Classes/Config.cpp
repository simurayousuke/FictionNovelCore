#include "Config.h"

Config* Config::instance = NULL;

Config* Config::getInstance()
{
	if (instance == NULL)
		instance = new Config();
	return instance;
}

std::string Config::getLocalLanguage()
{
	return localLanguage;
}
std::string Config::getVoiceLanguage()
{
	return voiceLanguage;
}

void Config::setLocalLanguage(std::string lang)
{
	localLanguage = lang;
}
void Config::setVoiceLanguage(std::string lang)
{
	voiceLanguage = lang;
}

Config::~Config()
{
	delete instance;
}