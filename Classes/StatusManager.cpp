#include "StatusManager.h"

USING_NS_CC;

StatusManager* StatusManager::instance = NULL;

StatusManager* StatusManager::getInstance()
{
	if (instance == NULL)
		instance = new StatusManager();
	return instance;
}
StatusManager::StatusManager() {}
StatusManager::~StatusManager() {}

Stage* StatusManager::getCurrentStage()
{
	return currentStage;
}
int StatusManager::getCurrentId()
{
	return currentId;
}
std::string StatusManager::getCurrentBgm()
{
	return currentBgm;
}
unsigned int StatusManager::getCurrentVoice()
{
	return currentVoice;
}

void StatusManager::setCurrentStage(Stage* stg)
{
	currentStage = stg;
}
void StatusManager::setCurrentId(int id)
{
	currentId = id;
}
void StatusManager::setCurrentBgm(std::string bgm)
{
	currentBgm = bgm;
}
void StatusManager::setCurrentVoice(unsigned int voice)
{
	currentVoice = voice;
}

void StatusManager::save()
{
	sqlite3 *pdb = NULL;//1
	std::string path = FileUtils::getInstance()->getWritablePath() + "save.db";//2
	
	std::string sql;
	int result;
	result = sqlite3_open(path.c_str(), &pdb);//3
	if (result != SQLITE_OK)
		log("open database failed,  number%d", result);
	sql = "create table if not exists savings(no integer primary key autoincrement,id int,time text,bg text)";//1
	result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);//1
	if (result != SQLITE_OK)
		log("create table failed");

	sql = "insert into savings(id)  values(" + std::to_string(currentId) + ")";
	result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (result != SQLITE_OK)
		log("insert data failed!");
	sqlite3_close(pdb);
}

void StatusManager::load()
{
	sqlite3 *pdb = NULL;//1
	std::string path = FileUtils::getInstance()->getWritablePath() + "save.db";//2

	std::string sql;
	int result;
	result = sqlite3_open(path.c_str(), &pdb);//3
	if (result != SQLITE_OK)
		log("open database failed,  number%d", result);

	char **re;//查询结果
	int r, c;//行、列
	sqlite3_get_table(pdb, "select * from savings", &re, &r, &c, NULL);//1
	//log("row is %d,column is %d", r, c);	
	//log("%s", re[r*c + 2]);
	if (r < 1)
		return;
	//log(re[r*c + 1]);
	currentId = std::stoi(re[r*c + 1]);
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	GameCore::getInstance()->nextStage(currentId);

	sqlite3_free_table(re);
	sqlite3_close(pdb);
}