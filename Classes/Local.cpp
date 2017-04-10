#include "Local.h"

std::string Local::getDefaultFont()
{
	auto local = Config::getInstance()->getLocalLanguage();
	if (local == "en")
		return "Marker Felt.ttf";
	if (local == "cn")
		return "stfangsong.ttf";
	if (local == "jp")
		return "yumin.ttf";
}