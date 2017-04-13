#include "Local.h"

std::string Local::back="back";
std::string Local::save="save";
std::string Local::load="load";

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