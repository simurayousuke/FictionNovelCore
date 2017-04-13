#include "Local.h"

std::string Local::back="back";
std::string Local::save="save";
std::string Local::load="load";
std::string Local::loading = "loading";
std::string Local::loadingConfig = "loading config";
std::string Local::loadingLocal = "loading localization";
std::string Local::loadingSound = "loading sound";
std::string Local::loadingMainTitle = "loading main title";
std::string Local::loadingSettingsScene = "loadding setting scene";
std::string Local::loadingStages = "loading stages";

std::string Local::getDefaultFont()
{
	auto local = Config::getInstance()->getLocalLanguage();
	if (local == "en")
		return "Marker Felt.ttf";
	if (local == "cn")
		return "stfangsong.ttf";
	if (local == "jp")
		return "yumin.ttf";
	return "Marker Felt.ttf";
}

std::string Local::getDefaultFont(std::string lang)
{
	if (lang == "en")
		return "Marker Felt.ttf";
	if (lang == "cn")
		return "stfangsong.ttf";
	if (lang == "jp")
		return "yumin.ttf";
	return "Marker Felt.ttf";
}