#include "Config.h"

USING_NS_CC;

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

void Config::setDafaultLanguage(std::string lang, std::string voice)
{
	sqlite3 *pdb = NULL;//1
	std::string path = FileUtils::getInstance()->getWritablePath() + "config.db";//2

	std::string sql;
	int result;
	result = sqlite3_open(path.c_str(), &pdb);//3
	if (result != SQLITE_OK)
		log("open database failed,  number%d", result);
	sql = "create table if not exists language(no integer primary key autoincrement,lang text,voice text)";//1
	result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);//1
	if (result != SQLITE_OK)
		log("create table failed");

	sql = "delete from language";
	result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (result != SQLITE_OK)
		log("truncate language failed!");

	sql = "insert into language(lang,voice)  values('" + lang + "','" + voice + "')";
	result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (result != SQLITE_OK)
		log("insert language failed!");
	sqlite3_close(pdb);
}

std::string Config::getDefaultTextLanguage()
{
	sqlite3 *pdb = NULL;
	std::string path = FileUtils::getInstance()->getWritablePath() + "config.db";
	std::string res;
	std::string sql;
	int result;
	result = sqlite3_open(path.c_str(), &pdb);
	if (result != SQLITE_OK)
		log("open database failed,  number%d", result);

	char **re;//查询结果
	int r, c;//行、列
	sqlite3_get_table(pdb, "select * from language", &re, &r, &c, NULL);
	if (r < 1)
		res = "none";
	else
		res = re[r*c + 1];

	sqlite3_free_table(re);
	sqlite3_close(pdb);
	return res;
}

std::string Config::getDefaultVoiceLanguage()
{
	sqlite3 *pdb = NULL;
	std::string path = FileUtils::getInstance()->getWritablePath() + "config.db";
	std::string res;
	std::string sql;
	int result;
	result = sqlite3_open(path.c_str(), &pdb);//3
	if (result != SQLITE_OK)
		log("open database failed,  number%d", result);

	char **re;//查询结果
	int r, c;//行、列
	sqlite3_get_table(pdb, "select * from language", &re, &r, &c, NULL);
	if (r < 1)
		res = "none";
	else
		res = re[r*c + 2];

	sqlite3_free_table(re);
	sqlite3_close(pdb);
	return res;
}