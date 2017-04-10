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
std::vector<std::string>* Config::getSupportLanguage()
{
	return supportLanguage;
}
std::string Config::getGameName()
{
	return gameName;
}

void Config::setLocalLanguage(std::string lang)
{
	localLanguage = lang;
}
void Config::setVoiceLanguage(std::string lang)
{
	voiceLanguage = lang;
}
void Config::setSupportLanguage(std::vector<std::string>* sptl)
{
	supportLanguage = sptl;
}
void Config::setGameName(std::string name)
{
	gameName = name;
}

Config::Config() {}
Config::~Config()
{
	delete instance;
}